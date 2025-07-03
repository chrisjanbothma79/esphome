// #include "sdspi_io.h"
#include "sdmmc_io.h"
#if defined(USE_SDMMC_MODE) && (SOC_SDMMC_HOST_SUPPORTED)
#include "esp_log.h"
#include "diskio.h"
#include "diskio_impl.h"
#include "diskio_sdmmc.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"

namespace esphome {
namespace sdfs {

// #define FF_DRV_NOT_USED 0xFF
static const char *TAG = "sdmmc_io";

/**********************************************************************
 *
 * @brief Construct a new SdmmcIO object. Provide  interface to low level
 * io operations for MMC connection in ARDUINO framework.
 *
 */
SdmmcIO::SdmmcIO() {
  this->last_err_ = 0;

  ESP_LOGD(TAG, "SdfsHost init");
  //   Allocate mem for SPI HOST_CONFIG
  sdmmc_host_t new_config = SDMMC_HOST_DEFAULT();
  this->host_config_ = (sdmmc_host_t *) calloc(sizeof(sdmmc_host_t), 1);
  if (this->host_config_ == NULL) {
    SET_RC(ERR_TYPE_LOCAL, RC_NO_MEM, "Init sdmmc. No mem");
    return;
  }

  memcpy(this->host_config_, &new_config, sizeof(sdmmc_host_t));
  // this->host_config_ = &new_config;

  this->slot_config_ = (sdmmc_slot_config_t *) calloc(sizeof(sdmmc_slot_config_t), 1);
  if (this->slot_config_ == NULL) {
    ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
    SET_RC(ERR_TYPE_LOCAL, RC_NO_MEM, "Init sdmmc. No mem");
    FREE(this->host_config_);
    return;
  }

  //   Allocate mem for Detected  CARD_CONFIG
  this->card_info_ = (sdmmc_card_t *) calloc(sizeof(sdmmc_card_t) + sizeof(sdmmc_host_t), 1);
  if (this->card_info_ == NULL) {
    SET_RC(ERR_TYPE_LOCAL, RC_NO_MEM, "Init sdmmc. No mem");
    FREE(this->host_config_);
    FREE(this->slot_config_);
    return;
  }

  this->mount_config_ = (esp_vfs_fat_mount_config_t *) calloc(sizeof(esp_vfs_fat_mount_config_t), 1);
  if (this->card_info_ == NULL) {
    SET_RC(ERR_TYPE_LOCAL, RC_NO_MEM, "Init sdmmc. No mem");
    FREE(this->host_config_);
    FREE(this->slot_config_);
    FREE(this->card_info_);
    return;
  }
  this->mount_config_->format_if_mount_failed = false;
  this->mount_config_->max_files = 5;
  this->mount_config_->allocation_unit_size = 16 * 1024;

  // #else
  //     SET_RC(ERR_TYPE_LOCAL, RC_NO_MEM, "Init sdmmc. Not supported chip");
  // #endif
}
void SdmmcIO::set_bus_slot(uint8_t slot) { this->bus_slot_ = slot; }
void SdmmcIO::set_bus_width(uint8_t bw) { this->spi_bus_width_ = bw; }

void SdmmcIO::set_wp_pin(gpio_num_t pin) { this->wp_pin_ = pin; }
void SdmmcIO::set_cd_pin(gpio_num_t pin) { this->cd_pin_ = pin; }
void SdmmcIO::set_clk_pin(gpio_num_t pin) { this->clk_pin_ = pin; }
void SdmmcIO::set_cmd_pin(gpio_num_t pin) { this->cmd_pin_ = pin; }
void SdmmcIO::set_data0_pin(gpio_num_t pin) { this->data0_pin_ = pin; }
void SdmmcIO::set_data1_pin(gpio_num_t pin) { this->data1_pin_ = pin; }
void SdmmcIO::set_data2_pin(gpio_num_t pin) { this->data2_pin_ = pin; }
void SdmmcIO::set_data3_pin(gpio_num_t pin) { this->data3_pin_ = pin; }
void SdmmcIO::set_data4_pin(gpio_num_t pin) { this->data4_pin_ = pin; }
void SdmmcIO::set_data5_pin(gpio_num_t pin) { this->data5_pin_ = pin; }
void SdmmcIO::set_data6_pin(gpio_num_t pin) { this->data6_pin_ = pin; }
void SdmmcIO::set_data7_pin(gpio_num_t pin) { this->data7_pin_ = pin; }

/**********************************************************************
 *
 * @brief   Initialise pins,  SDMMC Host and slot
 *          Note: All pins and bus type should be defined before this call.
 *
 * @return uint8_t
 */
bool SdmmcIO::init() {
  ESP_LOGD(TAG, "Init SDMMC");

  // ESP_LOGD(TAG, "Init SDMMC : SOC_SDMMC_HOST_SUPPORTED");

  esp_err_t rc = ESP_OK;
  uint8_t slot_num;
  uint8_t pdrv;

  // host_config->max_freq_khz = SDMMC_FREQ_HIGHSPEED;
  // rc = (*host_config->init)();

  rc = sdmmc_host_init();
  if (rc != ESP_OK) {
    ESP_LOGE(TAG, "Failed to init SDMMC host (0x%x)", rc);
    return false;
  }

  //   Select  drive for mount.
  if (ff_diskio_get_drive(&pdrv) != ESP_OK || pdrv == FF_DRV_NOT_USED) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "the maximum count of volumes is already mounted");
    return false;
  }

  //
  //   Define bus connection pins
  //

  // this->slot_config_->flags = 0;
  this->slot_config_->flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;
  this->slot_config_->width = this->spi_bus_width_;
  if (this->wp_pin_ != GPIO_NUM_NC) {
    this->slot_config_->wp = static_cast<gpio_num_t>(this->wp_pin_);
    // gpio_set_pull_mode(this->slot_config_->wp , GPIO_PULLUP_ONLY);
  } else
    this->slot_config_->wp = SDMMC_SLOT_NO_WP;

  if (this->cd_pin_ != GPIO_NUM_NC) {
    this->slot_config_->cd = static_cast<gpio_num_t>(this->cd_pin_);
    // gpio_set_pull_mode(slot_config->cd , GPIO_PULLUP_ONLY);
  } else
    this->slot_config_->cd = SDMMC_SLOT_NO_CD;

#ifdef SOC_SDMMC_USE_GPIO_MATRIX
  if ((this->clk_pin_ == GPIO_NUM_NC) || (this->cmd_pin_ == GPIO_NUM_NC) || (this->data0_pin_ == GPIO_NUM_NC)) {
    SET_RC(ERR_TYPE_LOCAL, RC_INVALID_ARG, "clk_pin, cmd_pin, data0_pin must be defined.");
    return false;
  }
  this->slot_config_->clk = static_cast<gpio_num_t>(this->clk_pin_);
  this->slot_config_->cmd = static_cast<gpio_num_t>(this->cmd_pin_);
  this->slot_config_->d0 = static_cast<gpio_num_t>(this->data0_pin_);

  if (this->spi_bus_width_ != 1) {
    if ((this->data1_pin_ == GPIO_NUM_NC) || (this->data2_pin_ == GPIO_NUM_NC) || (this->data2_pin_ == GPIO_NUM_NC)) {
      ESP_LOGW(TAG, " For 4bit bus width data1_pin_, data2_pin_, data3_pin_ must be defined. Redefine to 1bit");
      this->spi_bus_width_ = 1;
    } else {
      this->slot_config_->d1 = static_cast<gpio_num_t>(this->data1_pin_);
      this->slot_config_->d2 = static_cast<gpio_num_t>(this->data2_pin_);
      this->slot_config_->d3 = static_cast<gpio_num_t>(this->data3_pin_);
    }

    if (this->spi_bus_width_ == 8 && this->bus_slot_ == 0) {
      this->slot_config_->d4 = static_cast<gpio_num_t>(this->data4_pin_);
      this->slot_config_->d5 = static_cast<gpio_num_t>(this->data5_pin_);
      this->slot_config_->d6 = static_cast<gpio_num_t>(this->data6_pin_);
      this->slot_config_->d7 = static_cast<gpio_num_t>(this->data7_pin_);
    }
  }

  //  Init slot
  //
  slot_num = this->bus_slot_ == 0 ? SDMMC_HOST_SLOT_0 : SDMMC_HOST_SLOT_1;
  rc = sdmmc_host_init_slot(slot_num, this->slot_config_);
  if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "Failed to init slot host");
    return false;
  }
  ESP_LOGI(TAG, "SDMMC Init bus, slot %d, width %d", slot_num, this->slot_config_->width);
  this->host_config_->slot = slot_num;
  this->pdrv_ = pdrv;
  return true;
#else
  return false;
#endif
}

/**********************************************************************
 *
 * @brief  Return low level priver num
 *
 * @return uint8_t
 */
uint8_t SdmmcIO::get_pdrv() { return this->pdrv_; }

/**********************************************************************
 *
 * @brief
 *
 * @return true
 * @return false
 */
bool SdmmcIO::init_slot() {
  uint8_t slot_num = this->bus_slot_ == 0 ? SDMMC_HOST_SLOT_0 : SDMMC_HOST_SLOT_1;
  esp_err_t rc = sdmmc_host_init_slot(slot_num, this->slot_config_);
  if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "Failed to init slot host");
    return false;
  }
  ESP_LOGI(TAG, "Reset slot inicialization, slot %d, width %d", slot_num, this->slot_config_->width);
  this->host_config_->slot = slot_num;
  return true;
}

/**********************************************************************
 *
 * @brief   Check if card present
 *
 * @return true
 * @return false
 */
sdcard_status_t SdmmcIO::get_disk_status() {  //  is_card
  assert(this->card_info_);
  esp_err_t err = sdmmc_get_status(this->card_info_);
  if (unlikely(err != ESP_OK)) {
    ESP_LOGE(TAG, "Check status failed (0x%x)%s", err, esp_err_to_name(err));
    return RET_STATUS_FAIL;
  }
  return RET_STATUS_OK;
}

/**********************************************************************
 *
 * @brief
 *
 * @return init_status_t
 */
sdcard_status_t SdmmcIO::init_card() {  //  attach_card
  esp_err_t rc;
  rc = sdmmc_card_init(this->host_config_, this->card_info_);
  if (rc != ESP_OK) {
    if (rc = ESP_ERR_TIMEOUT) {
      this->last_err_ = (ERR_TYPE_FRAMEWORK << 16) | rc;
      return RET_STATUS_NOCARD;
    } else {
      SET_RC(ERR_TYPE_FRAMEWORK, rc, "Failed to init card");
      return RET_STATUS_FAIL;
    }
  }
  return RET_STATUS_OK;
}

/**********************************************************************
 *
 * @brief Mount FS
 *
 * @param mountpoint
 * @param format
 * @return FATFS*
 */
FATFS *SdmmcIO::mount(std::string mountpoint) {
  mountpoint_ = mountpoint;
  FATFS *fs = NULL;
  esp_err_t rc = ESP_OK;
  FRESULT mount_rc = FR_OK;

  ff_diskio_register_sdmmc(this->pdrv_, this->card_info_);

  char drv[3] = {(char) ('0' + this->pdrv_), ':', 0};
  ESP_LOGD(TAG, "Disk registered. pdrv=%i, drv=%s, path=%s", this->pdrv_, drv, mountpoint_.c_str());

  rc = esp_vfs_fat_register(mountpoint_.c_str(), drv, this->mount_config_->max_files, &fs);
  if (rc == ESP_ERR_INVALID_STATE) {
    // it's okay, already registered with VFS
  } else if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "esp_vfs_fat_register failed");
    goto unregister_fs;
  }

  mount_rc = f_mount(fs, drv, 1);
  if (mount_rc != FR_OK) {
    if ((mount_rc == FR_NO_FILESYSTEM || mount_rc == FR_INT_ERR)) {
      SET_RC(ERR_TYPE_LOCAL, RC_NOT_FORMATED, "Cannot mount");
    }
    SET_RC(ERR_TYPE_FILESYS, mount_rc, "Cannot mount");
    goto unregister_fs;
  }

  return fs;

unregister_fs:
  ESP_LOGD(TAG, "Reset registration");
  esp_vfs_fat_unregister_path(mountpoint_.c_str());
  // FREE(this->mount_config_);
  // this->fs_ = NULL;
  return NULL;
}

/**********************************************************************
 *
 * @brief unmount fs
 *
 * @return true
 * @return false
 */
void SdmmcIO::unmount() {
  esp_err_t rc = ESP_OK;

  //  Unmount filesystem
  char drv[3] = {(char) ('0' + this->pdrv_), ':', 0};
  FRESULT res = f_mount(0, drv, 0);
  if (res != FR_OK) {
    SET_RC(ERR_TYPE_FILESYS, res, "Unmount return");
  }

  //  Clear registration
  rc = esp_vfs_fat_unregister_path(mountpoint_.c_str());
  if ((rc != ESP_OK) && (rc != ESP_ERR_INVALID_STATE)) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "Cannot unregister root path");
  }

  //  Reinit slot
  uint8_t slot_num = this->bus_slot_ == 0 ? SDMMC_HOST_SLOT_0 : SDMMC_HOST_SLOT_1;
  rc = sdmmc_host_init_slot(slot_num, this->slot_config_);
  if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "Failed to init slot host");
    return;
  }
  ESP_LOGI(TAG, "Reset slot inicialization, slot %d, width %d", slot_num, this->slot_config_->width);
  this->host_config_->slot = slot_num;
}

/**********************************************************************
 *
 * @brief format cdcard with fat fs
 *
 * @return true
 * @return false
 */
local_rc_t SdmmcIO::format() {
  char drv[3] = {(char) ('0' + this->pdrv_), ':', 0};
  FRESULT res = FR_OK;
  esp_err_t err;
  const size_t workbuf_size = 4096;
  void *workbuf = NULL;
  ESP_LOGW(TAG, "partitioning card");

  workbuf = ff_memalloc(workbuf_size);
  if (workbuf == NULL) {
    ESP_LOGE(TAG, "not enough mem");
    SET_RC(ERR_TYPE_LOCAL, RC_NO_MEM, "Format. No mem");
    return RC_NO_MEM;
  }

#ifdef USE_ESP_IDF
  ESP_LOGD(TAG, "Formatting. Disk (f_fdisk)");
  LBA_t plist[] = {100, 0, 0, 0};
  res = f_fdisk(this->pdrv_, plist, workbuf);
  if (res != FR_OK) {
    SET_RC(ERR_TYPE_FILESYS, res, "Cannot format disk");
    free(workbuf);
    return RC_NO_CARD;
  }
#endif

  size_t alloc_unit_size = this->mount_config_->allocation_unit_size;
  const size_t max_sectors_per_cylinder = 128;
  const size_t max_size = this->card_info_->csd.sector_size * max_sectors_per_cylinder;
  alloc_unit_size = MAX(alloc_unit_size, this->card_info_->csd.sector_size);
  alloc_unit_size = MIN(alloc_unit_size, max_size);

  ESP_LOGD(TAG, "Prtitioning disk (f_mkfs), Allocation unit size=%d", alloc_unit_size);

#ifdef USE_ESP_IDF
  const MKFS_PARM opt = {(BYTE) FM_ANY, 0, 0, 0, alloc_unit_size};
  res = f_mkfs(drv, &opt, workbuf, workbuf_size);
#else
  res = f_mkfs(drv, FM_ANY, 0, workbuf, workbuf_size);
#endif
  if (res != FR_OK) {
    SET_RC(ERR_TYPE_FILESYS, res, "Cannot make fs");
    free(workbuf);
    return RC_UNKNOWN;
  }

  free(workbuf);
  ESP_LOGD(TAG, "Prtitioning disk %d completed", this->pdrv_);
  return RC_OK;
}

bool SdmmcIO::is_card_mem() { return this->card_info_->is_mem == 1; }
bool SdmmcIO::is_card_sdio() { return this->card_info_->is_sdio == 1; }
bool SdmmcIO::is_card_mmc() { return this->card_info_->is_mmc == 1; }
size_t SdmmcIO::sectors() { return this->card_info_->csd.capacity; }
size_t SdmmcIO::sector_size() { return this->card_info_->csd.sector_size; }

}  // namespace sdfs
}  // namespace esphome
#endif