#include "sdspi_drv_ard.h"
#if defined(USE_ARDUINO)
#include "dirent.h"
#include "esp_system.h"
extern "C" {
#include "ff.h"
#if ESP_IDF_VERSION_MAJOR > 3
#endif
#include "esp_vfs_fat.h"
}

#if defined(USE_SDSPI_MODE)
#include "sdspi_io.h"
#endif

namespace esphome {
namespace sdfs {

uint32_t IRAM_ATTR HOT millis() { return (uint32_t) (esp_timer_get_time() / 1000ULL); }
static const char *const TAG = "sdspi_drv_ard";
static esp_ardu_sdcard_t *s_cards[FF_VOLUMES] = {NULL};

/****************************************************************
 *
 *             ArduinoSdFatDriver
 *
 * @brief   SD card accessed throug SPI Interface  processin
 *
 * @param impl   FAT.   Esp fs implementation class
 */
ArduinoSdFatDriver::ArduinoSdFatDriver() { this->pdrv_ = 0xFF; }

void ArduinoSdFatDriver::set_parent(SdmmcHost *p) { this->parent_ = p; }
void ArduinoSdFatDriver::set_connector(SpiConnector *cn) { this->connector_ = cn; }

/****************************************************************
 *
 * @brief Start SPI  snd SD card slot.
 *
 * @return true
 * @return false
 */
bool ArduinoSdFatDriver::init_host(SdConnType bus_type) {
  this->bus_type_ = bus_type;

  this->connector_->begin();
  this->pdrv_ = sdspi_init(this->connector_);
  if (this->pdrv_ == 0xFF)
    return false;

  DSTATUS res = ff_sd_initialize(this->pdrv_);
  if (res & STA_NOINIT) {
    return false;
  }
  return true;
}

// TODO: Add destructor
void ArduinoSdFatDriver::end() { sdspi_uninit(this->pdrv_); }
/****************************************************************
 *
 * @brief check if filesystem is mounted
 *
 * @return true
 * @return false
 */
bool ArduinoSdFatDriver::is_mount() { return (this->fs_ != NULL) && (this->fs_->fs_type != 0); }

/****************************************************************
 *
 * @brief  if cars mounted get sectors count.  if not, just try attach
 * thia check card status.
 * @return true
 * @return false
 */
bool ArduinoSdFatDriver::is_card() {
  if (is_mount()) {
    connector_->beginTransaction();
    bool res = sdGetSectorsCount(this->pdrv_) != 0;
    connector_->endTransaction();
    if (!res) {
      unmount();
      return false;
    }
  } else
    return attach_card();
  return true;
}

// bool ArduinoSdFatDriver::init_card() {
//   DSTATUS res = ff_sd_initialize(pdrv_);
//   if ((res & STA_NOINIT) == STA_NOINIT) {

//     ESP_LOGV(TAG, "No card in slot");
//     return false;
//   } else {
//     ESP_LOGV(TAG, "Card in slot");
//     return true;
//   }
// }

/****************************************************************
 *
 * @brief  Try to access the card.  This check is card present
 *
 * @return true
 * @return false
 */
bool ArduinoSdFatDriver::attach_card() {
  bool is_card = !(ff_sd_initialize(pdrv_) & STA_NOINIT);
  ESP_LOGD(TAG, "Attach card. ret=%s", is_card ? "TRUE" : "FALSE");
  return is_card;
}

/****************************************************************
 *
 * @brief  If card init, mount FAT, register mount point
 *
 * @param mountpoint
 * @param format  fromat driver if card empty
 * @return true  Mouned
 * @return false  Not mounted
 */
bool ArduinoSdFatDriver::mount(std::string mountpoint, bool format) {
  ESP_LOGV(TAG, "Mount FS. pdrv=%d, Mountpoint %s", this->pdrv_, mountpoint);
  this->fs_ = mount_sdspi(this->pdrv_, mountpoint, format);

  if (this->fs_ != NULL) {
    ESP_LOGD(TAG, "Disk mounnted. pdrv=%d, fs type %s", this->pdrv_, fat_type2str[this->fs_->fs_type]);
    return true;
  } else {
    ESP_LOGD(TAG, "Disk mount fail. pdrv=%d", this->pdrv_);
    return false;
  }
  return true;
}

/****************************************************************
 *
 * @brief  Mount sdcard in spi mode
 *
 * @param pdrv
 * @param mountpoint
 * @param format
 * @return FATFS*
 */
FATFS *ArduinoSdFatDriver::mount_sdspi(uint8_t pdrv, std::string mountpoint, bool format) {
  FATFS *fs = sdcard_mount(pdrv, mountpoint.c_str(), 5, format);
  if (fs == NULL) {
    ESP_LOGE(TAG, "Cannot mount");
    sdcard_unmount(this->pdrv_);
  }
  return fs;
}

/****************************************************************
 *
 * @brief   Testing connected driver. Open and list root dir.
 *
 * @return true
 * @return false
 */
bool ArduinoSdFatDriver::test() {
  FF_DIR dir;
  FILINFO fno;
  FRESULT res;

  // std::string path = std::string(mountpoint_ + "/");

  ESP_LOGV(TAG, "TEST FS for path %s", "/");
  res = f_opendir(&dir, "/");
  if (res != FR_OK) {
    ESP_LOGE(TAG, "f_opendir: %s", fs_err2str[res]);
    return false;
  }

  do {
    res = f_readdir(&dir, &fno);
    if (res != FR_OK) {
      ESP_LOGE(TAG, "f_readdir: %s", fs_err2str[res]);
      return false;
    }
    if (fno.fname[0] != 0)
      ESP_LOGV(TAG, "File found: %s", fno.fname);  // Print File Name

  } while (fno.fname[0] != 0);

  f_closedir(&dir);
  return true;
}

/****************************************************************
 *
 * @brief Unmount driver. Ckear mount point registration.
 *
 */
void ArduinoSdFatDriver::unmount() {
  // _impl->mountpoint(NULL);
  sdcard_unmount(this->pdrv_);
  this->fs_ = NULL;
}

uint32_t ArduinoSdFatDriver::get_last_err() { return this->last_err_; }

sdcard_type_t ArduinoSdFatDriver::cardType() {
  if (!is_mount())
    return CARD_NONE;
  return s_cards[pdrv_]->type;
}

uint64_t ArduinoSdFatDriver::cardSize() {
  if (!is_mount())
    return 0;
  return (uint64_t) numSectors() * this->sectorSize();
}

size_t ArduinoSdFatDriver::numSectors() {
  if (!is_mount())
    return 0;
  return s_cards[pdrv_]->sectors;
}

size_t ArduinoSdFatDriver::sectorSize() {
  if (!is_mount())
    return 0;
  return FF_SS_SDCARD;
}

uint64_t ArduinoSdFatDriver::totalBytes() {
  uint64_t size = 0;
  if (is_mount()) {
    DWORD fre_clust;
    if (f_getfree("0:", &fre_clust, &this->fs_) != 0)
      return 0;
    size = ((uint64_t) (this->fs_->csize)) * (this->fs_->n_fatent - 2)
#if _MAX_SS != FF_SS_SDCARD
           * (this->fs_->ssize);
#else
           * FF_SS_SDCARD;
#endif
  }
  return size;
}

uint64_t ArduinoSdFatDriver::usedBytes() {
  uint64_t size = 0;
  if (is_mount()) {
    DWORD fre_clust;
    if (f_getfree("0:", &fre_clust, &this->fs_) != 0)
      return 0;
    size = ((uint64_t) (this->fs_->csize)) * ((this->fs_->n_fatent - 2) - (this->fs_->free_clst))
#if _MAX_SS != FF_SS_SDCARD
           * (this->fs_->ssize);
#else
           * FF_SS_SDCARD;
#endif
  }
  return size;
}

}  // namespace sdfs
}  // namespace esphome
#endif