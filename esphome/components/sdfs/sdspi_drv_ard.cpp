#include "sdspi_drv_ard.h"
#include "sd_defines.h"
#if defined(USE_ARDUINO) && !defined(USE_ESP8266)
#include "dirent.h"
#include "esp_system.h"
extern "C" {
#include "ff.h"
#if ESP_IDF_VERSION_MAJOR > 3
#endif
#include "esp_vfs_fat.h"
}
#ifdef USE_SDMMC_MODE
#include "SD_MMC.h"
#endif

#if defined(USE_SDSPI_MODE)
#include "sdspi_io.h"
#else
#include "sdmmc_io.h"
#endif

namespace esphome {
namespace sdfs {

uint32_t IRAM_ATTR HOT millis() { return (uint32_t) (esp_timer_get_time() / 1000ULL); }
static const char *const TAG = "sdspi_drv_ard";

/****************************************************************
 *
 *             ArduinoFatFsDriver
 *
 * @brief Arduino frameework processing interaction with SDMMC and SDSPI card drivers/controllers
 *        in ESP32 platform.
 *        For SDMMC mode it use  SdmmcIO calss for commenication through HAL
 *        For SDSPI mode it use SPIConnector  classfor use esphome dafault SPI interface.
 *                  SPIConnector class defined in upper level in SdmmcHost class
 * @param impl   FAT.   Esp fs implementation class
 */
ArduinoFatFsDriver::ArduinoFatFsDriver() {
  this->pdrv_ = 0xFF;
#if defined(USE_SDMMC_MODE)
  this->mmc_connector = new SdmmcIO();
#endif
}

void ArduinoFatFsDriver::set_parent(SdmmcHost *p) { this->parent_ = p; }
#if defined(USE_SDSPI_MODE)
void ArduinoFatFsDriver::set_connector(SpiConnector *cn) { this->connector_ = cn; }
#endif

/****************************************************************
 *
 * @brief Start SPI snd SD card slot.
 *
 * @return true
 * @return false
 */
bool ArduinoFatFsDriver::init_host(SdConnType bus_type) {
  this->bus_type_ = bus_type;
  bool ret = false;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    this->connector_->begin();
    this->pdrv_ = sdspi_init(this->connector_);

    if (this->pdrv_ != 0xFF) {
      DSTATUS res = ff_sd_initialize(this->pdrv_);
      if (res & STA_NOINIT) {
        ret = false;
      } else {
        ret = true;
      }
    }
  }
#endif
#if defined(USE_SDMMC_MODE)
  // TODO:  set pins
  if (this->bus_type_ == SD_MMC) {
    this->mmc_connector->set_bus_width(this->parent_->spi_bus_width_);
    this->mmc_connector->set_wp_pin(this->parent_->wp_pin_);
    this->mmc_connector->set_cd_pin(this->parent_->cd_pin_);
    this->mmc_connector->set_clk_pin(this->parent_->clk_pin_);
    this->mmc_connector->set_cmd_pin(this->parent_->cmd_pin_);
    this->mmc_connector->set_bus_slot(this->parent_->bus_slot_);
    this->mmc_connector->set_data0_pin(this->parent_->data0_pin_);
    this->mmc_connector->set_data1_pin(this->parent_->data1_pin_);
    this->mmc_connector->set_data2_pin(this->parent_->data2_pin_);
    this->mmc_connector->set_data3_pin(this->parent_->data3_pin_);
    this->mmc_connector->set_data4_pin(this->parent_->data4_pin_);
    this->mmc_connector->set_data5_pin(this->parent_->data5_pin_);
    this->mmc_connector->set_data6_pin(this->parent_->data6_pin_);
    this->mmc_connector->set_data7_pin(this->parent_->data7_pin_);

    ret = this->mmc_connector->init();
    this->pdrv_ = this->mmc_connector->get_pdrv();
    if (ret) {
      if (this->mmc_connector->init_card() != SDMMC_RET_STATUS_OK) {
        ret = false;
      }
    }
  }
#endif

  return ret;
}

// TODO: Add destructor
void ArduinoFatFsDriver::end() {
#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    sdspi_uninit(this->pdrv_);
  }
#endif
}
/****************************************************************
 *
 * @brief check if filesystem is mounted
 *
 * @return true
 * @return false
 */
bool ArduinoFatFsDriver::is_mount() { return (this->fs_ != NULL) && (this->fs_->fs_type != 0); }

/****************************************************************
 *
 * @brief  if cars mounted get sectors count.  if not, just try attach
 * thia check card status.
 * @return true
 * @return false
 */
bool ArduinoFatFsDriver::is_card() {
  if (is_mount()) {
#if defined(USE_SDSPI_MODE)
    if (this->bus_type_ == SD_SPI) {
      connector_->beginTransaction();
      bool res = sdGetSectorsCount(this->pdrv_) != 0;
      connector_->endTransaction();
      if (!res) {
        unmount();
        return false;
      }
    }
#endif
#if defined(USE_SDSMMC_MODE)
    if (this->bus_type_ == SD_MMC) {
      init_status_t st = this->mmc_connector->get_disk_status();
      if (st = SDMMC_RET_STATUS_OK)
        return true;
      else {
        this->mmc_connector->unmount();
        return false;
      }
    }
#endif
  } else {
    return attach_card();
  }
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
bool ArduinoFatFsDriver::attach_card() {
  bool is_card = false;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    is_card = !(ff_sd_initialize(pdrv_) & STA_NOINIT);
    ESP_LOGD(TAG, "Attach card. ret=%s", is_card ? "TRUE" : "FALSE");
  }
#endif
#if defined(USE_SDMMC_MODE)
  if (this->bus_type_ == SD_MMC) {
    // init_status_t status = this->mmc_connector->init_card();
    // if ( status == SDMMC_RET_STATUS_OK )
    is_card = this->mmc_connector->init_card() == SDMMC_RET_STATUS_OK;
  }
#endif
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
bool ArduinoFatFsDriver::mount(std::string mountpoint, bool format) {
  ESP_LOGV(TAG, "Mount FS. pdrv=%d, Mountpoint %s", this->pdrv_, mountpoint);
#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    this->fs_ = sdcard_mount(this->pdrv_, mountpoint.c_str(), 5, format);
    if (this->fs_ == NULL) {
      sdcard_unmount(this->pdrv_);
    }
  }
#endif

#if defined(USE_SDMMC_MODE)
  if (this->bus_type_ == SD_MMC) {
    this->fs_ = this->mmc_connector->mount(mountpoint);
    if ((this->fs_ != NULL) && (IS_LAST_ERR(ERR_TYPE_LOCAL, RC_NOT_FORMATED)) && format) {
      ESP_LOGD(TAG, "Disk mount fail.  Will formated pdrv=%d", this->pdrv_);
      local_rc_t format_res = this->mmc_connector->format();
      if (format_res == RC_OK) {
        this->fs_ = this->mmc_connector->mount(mountpoint);
      }
    }
  }
#endif

  if (this->fs_ == NULL) {
    ESP_LOGD(TAG, "Disk mount fail. pdrv=%d", this->pdrv_);
    return false;
  }
  ESP_LOGD(TAG, "Disk mounnted. pdrv=%d, fs type %s", this->pdrv_, fat_type2str[this->fs_->fs_type]);
  return true;
}

/****************************************************************
 *
 * @brief   Testing connected driver. Open and list root dir.
 *
 * @return true
 * @return false
 */
bool ArduinoFatFsDriver::test() {
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
void ArduinoFatFsDriver::unmount() {
  // _impl->mountpoint(NULL);
#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    sdcard_unmount(this->pdrv_);
  }
#endif
#if defined(USE_SDMMC_MODE)
  if (this->bus_type_ == SD_MMC) {
    this->mmc_connector->unmount();
  }
#endif
  this->fs_ = NULL;
}

uint32_t ArduinoFatFsDriver::get_last_err() { return this->last_err_; }

sdcard_type_t ArduinoFatFsDriver::cardType() {
  sdcard_type_t type = CARD_NONE;
  if (!is_mount())
    return type;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    type = ff_sd_type(this->pdrv_);
  }
#endif
#if defined(USE_SDMMC_MODE)
  if (this->bus_type_ == SD_MMC) {
    if (this->mmc_connector->is_card_mem())
      type = CARD_UNKNOWN;
    else if (this->mmc_connector->is_card_sdio())
      type = CARD_SD;
    else if (this->mmc_connector->is_card_mmc())
      type = CARD_MMC;
    else
      type = CARD_UNKNOWN;
  }
#endif
  return type;
}

uint64_t ArduinoFatFsDriver::cardSize() {
  if (!is_mount())
    return 0;
  return (uint64_t) numSectors() * this->sectorSize();
}

size_t ArduinoFatFsDriver::numSectors() {
  size_t sectors = 0;
  if (!is_mount())
    return 0;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    sectors = ff_sd_sectors(this->pdrv_);
  }
#endif
#if defined(USE_SDMMC_MODE)
  if (this->bus_type_ == SD_MMC) {
    sectors = this->mmc_connector->sectors();
  }
#endif
  return sectors;
}

size_t ArduinoFatFsDriver::sectorSize() {
  size_t size = 0;
  if (!is_mount())
    return 0;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    size = FF_SS_SDCARD;
  }
#endif
#if defined(USE_SDMMC_MODE)
  if (this->bus_type_ == SD_MMC) {
    size = this->mmc_connector->sector_size();
  }
#endif
  return size;
}

uint64_t ArduinoFatFsDriver::totalBytes() {
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

uint64_t ArduinoFatFsDriver::usedBytes() {
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