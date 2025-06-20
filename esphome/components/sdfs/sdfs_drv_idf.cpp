#include "sdfs.h"

#if defined(USE_ESP_IDF)
#include "diskio_impl.h"
#include "esphome/core/log.h"
// #include "esp_vfs.h"
#include "sdmmc_cmd.h"
#include "diskio_sdmmc.h"

#include "driver/sdmmc_host.h"
#include "driver/sdmmc_types.h"
#if defined(SOC_SDMMC_HOST_SUPPORTED)
#include "sdmmc_io.h"
#endif
#include "driver/sdspi_host.h"
// #include "diskio_impl.h"
#include "hal/spi_types.h"
#include "esp_vfs_fat.h"
#include "vfs_fat_internal.h"
#include "sdfs_drv_idf.h"
#include "stdio.h"

#if defined(USE_SDSPI_MODE)
#include "sdspi_io.h"
#endif

// #include "driver/sdmmc_defs.h"
// #ifdef USE_ESP32_FRAMEWORK_ARDUINO
// #include "esp32-hal-spi.h"
// #endif
//
//
//  Pin assignements  for SDSPI
//  https://github.com/espressif/esp-idf/blob/master/examples/storage/sd_card/sdspi/README.md
//
//  Initialize  SDSPI
//  https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/sdspi_host.html
//
//  Initialize SDMMC
//  https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/sdmmc_host.html
//
//  Card Detect
//  https://esp32.com/viewtopic.php?t=15604
//
//  FAT mount
//  https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/storage/fatfs.html#_CPPv423esp_vfs_fat_sdspi_mountPKcPK12sdmmc_host_tPK21sdspi_device_config_tPK26esp_vfs_fat_mount_config_tPP12sdmmc_card_t
//
//  ESP32  ping assignement
//  https://github.com/espressif/esp-idf/blob/master/examples/storage/sd_card/sdmmc/README.md
//
//
//  https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/protocols/esp_sdio_slave_protocol.html
//
//
//  https://my-esp-idf.readthedocs.io/en/latest/api-reference/storage/sdmmc.html
//
//    ARDUINO
//    https://www.instructables.com/SD-Card-Module-With-ESP8266/
//
namespace esphome {
namespace sdfs {

#ifdef USE_ESP32_FRAMEWORK_ARDUINO
// #define SPI_BUS_COUNT  SPI_COUNT   //SOC_SPI_PERIPH_NUM
#define SPI_BUS_COUNT SOC_SPI_PERIPH_NUM  // SOC_SPI_PERIPH_NUM
#else
#define SPI_BUS_COUNT SPI_HOST_MAX
#endif

static const char *TAG = "sdmmc_drv_idf";

uint16_t partition_card(const esp_vfs_fat_mount_config_t *, const char *, sdmmc_card_t *, BYTE);

static void call_host_deinit_(const sdmmc_host_t *host_config) {
  if (host_config->flags & SDMMC_HOST_FLAG_DEINIT_ARG) {
    host_config->deinit_p(host_config->slot);
  } else {
    host_config->deinit();
  }
}

/***********************************************************************************
 * @brief   Save pointer to parentclass (host controller)
 *
 * @param p
 */

void SdfsIdfDriver::set_parent(SdfsHost *p) { this->parent_ = p; }
#if defined(USE_SDSPI_MODE)
void SdfsIdfDriver::set_connector(SpiConnector *conn) { this->connector_ = conn; }
#endif
uint32_t SdfsIdfDriver::get_last_err() { return this->last_err_; }

// bool SdfsIdfDriver::sdspi_allocate() {
//   ESP_LOGD(TAG, "SdfsHost init");
//   //   Allocate mem for SPI HOST_CONFIG
//   sdmmc_host_t new_config = SDSPI_HOST_DEFAULT();
//   this->host_config_ = (sdmmc_host_t *) calloc(sizeof(sdmmc_host_t), 1);
//   if (this->host_config_ == NULL) {
//     ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
//     FREE(this->host_config_);
//     return false;
//   }
//   memcpy(this->host_config_, &new_config, sizeof(sdmmc_host_t));

//   // spi_bus_config_t *spi_bus_config_{nullptr};

//   this->spi_dev_config_ = (sdspi_device_config_t *) calloc(sizeof(sdspi_device_config_t), 1);
//   if (this->spi_dev_config_ == NULL) {
//     ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
//     FREE(this->host_config_);
//     return false;
//   }

//   //   Allocate mem for Detected  CARD_CONFIG
//   // this->card_info_ = (sdmmc_card_t *) calloc(sizeof(sdmmc_card_t), 1);
//   // if (this->card_info_ == NULL) {
//   //   ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
//   //   FREE(this->host_config_);
//   //   FREE(this->spi_dev_config_);
//   //   return false;
//   // }
//   return true;
// }

/***********************************************************************************
 * @brief  Allocate required emory vof SDIO host structures
 *
 * @return true
 * @return false  if no mem
 */
bool SdfsIdfDriver::sdmmc_allocate() {
#if defined(SOC_SDMMC_HOST_SUPPORTED)
  ESP_LOGD(TAG, "SdfsHost init");
  //   Allocate mem for SPI HOST_CONFIG
  sdmmc_host_t new_config = SDMMC_HOST_DEFAULT();
  this->host_config_ = (sdmmc_host_t *) calloc(sizeof(sdmmc_host_t), 1);
  if (this->host_config_ == NULL) {
    ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
    return false;
  }
  memcpy(this->host_config_, &new_config, sizeof(sdmmc_host_t));
  // this->host_config_ = &new_config;

  this->slot_config_ = (sdmmc_slot_config_t *) calloc(sizeof(sdmmc_slot_config_t), 1);
  if (this->slot_config_ == NULL) {
    ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
    FREE(this->host_config_);
    return false;
  }

  //   Allocate mem for Detected  CARD_CONFIG
  this->card_info_ = (sdmmc_card_t *) calloc(sizeof(sdmmc_card_t) + sizeof(sdmmc_host_t), 1);
  if (this->card_info_ == NULL) {
    ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
    FREE(this->host_config_);
    FREE(this->slot_config_);
    return false;
  }
  return true;
#else
  return false;
#endif
}

/***********************************************************************************
 * @brief  Initialize perpirals driver
 *
 */
bool SdfsIdfDriver::init_host(SdConnType bus_type) {
  this->bus_type_ = bus_type;
  uint8_t ret_status = 0;

  if (this->bus_type_ == SD_MMC) {
    if (!sdmmc_allocate())
      return false;
    ret_status = init_sdmmc(this->host_config_);
  } else {
    ret_status = init_sdspi();
  }

  if (ret_status == RET_STATUS_FAIL) {
    ESP_LOGD(TAG, "Init host RET_STATUS_FAIL");
    return false;
  }
  ESP_LOGD(TAG, "Init host TRUE");
  return true;
}

/***********************************************************************************
 * @brief  Initd sd card perphiral driver in  SDMMC mode
 *
 * @return sdmmc_host_t*
 */
uint8_t SdfsIdfDriver::init_sdmmc(sdmmc_host_t *host_config) {
  ESP_LOGD(TAG, "Init SDMMC");
#if defined(SOC_SDMMC_HOST_SUPPORTED)
  ESP_LOGD(TAG, "Init SDMMC : SOC_SDMMC_HOST_SUPPORTED");

  esp_err_t rc = ESP_OK;
  uint8_t slot_num;
  uint8_t pdrv;

  // host_config->max_freq_khz = SDMMC_FREQ_HIGHSPEED;
  // rc = (*host_config->init)();

  rc = sdmmc_host_init();
  if (rc != ESP_OK) {
    ESP_LOGE(TAG, "Failed to init SDMMC host (0x%x)", rc);
    return RET_STATUS_FAIL;
  }

  //   Select  drive for mount.
  if (ff_diskio_get_drive(&pdrv) != ESP_OK || pdrv == FF_DRV_NOT_USED) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "the maximum count of volumes is already mounted");
    return RET_STATUS_FAIL;
  }
  this->pdrv_ = pdrv;

  //
  //   Define bus connection pins
  //

  // this->slot_config_->flags = 0;
  this->slot_config_->flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;
  this->slot_config_->width = this->parent_->spi_bus_width_;
  if (this->parent_->wp_pin_ < 255) {
    this->slot_config_->wp = static_cast<gpio_num_t>(this->parent_->wp_pin_);
    // gpio_set_pull_mode(this->slot_config->wp , GPIO_PULLUP_ONLY);
  } else
    this->slot_config_->wp = SDMMC_SLOT_NO_WP;
  if (this->parent_->cd_pin_ < 255) {
    this->slot_config_->cd = static_cast<gpio_num_t>(this->parent_->cd_pin_);
    // gpio_set_pull_mode(slot_config->cd , GPIO_PULLUP_ONLY);
  } else
    this->slot_config_->cd = SDMMC_SLOT_NO_CD;

#ifdef SOC_SDMMC_USE_GPIO_MATRIX
  this->slot_config_->clk = static_cast<gpio_num_t>(this->parent_->clk_pin_);
  this->slot_config_->cmd = static_cast<gpio_num_t>(this->parent_->cmd_pin_);
  this->slot_config_->d0 = static_cast<gpio_num_t>(this->parent_->data0_pin_);

  if (this->parent_->spi_bus_width_ != 1) {
    this->slot_config_->d1 = static_cast<gpio_num_t>(this->parent_->data1_pin_);
    this->slot_config_->d2 = static_cast<gpio_num_t>(this->parent_->data2_pin_);
    this->slot_config_->d3 = static_cast<gpio_num_t>(this->parent_->data3_pin_);

    if (this->parent_->spi_bus_width_ == 8 && this->parent_->bus_slot_ == 0) {
      this->slot_config_->d4 = static_cast<gpio_num_t>(this->parent_->data4_pin_);
      this->slot_config_->d5 = static_cast<gpio_num_t>(this->parent_->data5_pin_);
      this->slot_config_->d6 = static_cast<gpio_num_t>(this->parent_->data6_pin_);
      this->slot_config_->d7 = static_cast<gpio_num_t>(this->parent_->data7_pin_);
    }
  }
#endif

  //  Init slot
  //
  slot_num = this->parent_->bus_slot_ == 0 ? SDMMC_HOST_SLOT_0 : SDMMC_HOST_SLOT_1;
  rc = sdmmc_host_init_slot(slot_num, this->slot_config_);
  if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "Failed to init slot host");
    return RET_STATUS_FAIL;
  }
  ESP_LOGI(TAG, "SDMMC Init bus, slot %d, width %d", slot_num, this->slot_config_->width);
  this->host_config_->slot = slot_num;

  //   Check for card and load host params
  //
  bool ret = this->attach_card();
  if (!this->attach_card()) {
    // if (this->is_last_err(LC_ERR, ESP_ERR_TIMEOUT))
    //   return RET_STATUS_NOTCRITICAL;
    if (IS_LAST_ERR(ERR_TYPE_LOCAL, ESP_ERR_TIMEOUT)) {
      return RET_STATUS_NOTCRITICAL;
    } else {
      return RET_STATUS_FAIL;
    }
  }
  ESP_LOGI(TAG, "SDMMC got card status %s", TRUEFALSE(ret));
  return RET_STATUS_OK;
#else
  return RET_STATUS_FAIL;
#endif
}

/***********************************************************************************
 * @brief   Configure sdcard driver as SDSPI
 *
 * @return sdmmc_host_t*
 */
uint8_t SdfsIdfDriver::init_sdspi() {
#if defined(USE_SDSPI_MODE)
  ESP_LOGD(TAG, "Init SDSPI");
  this->connector_->begin();

  this->pdrv_ = sdspi_init(this->connector_);
  if (this->pdrv_ == 0xFF)
    return RET_STATUS_FAIL;

  DSTATUS res = ff_sd_initialize(this->pdrv_);
  if (res & STA_NOINIT) {
    return RET_STATUS_NOTCRITICAL;
  }
#endif
  return RET_STATUS_OK;
}

/***********************************************************************************
 * @brief   Check card status. (is card present in slot)
 *
 * @return true  card present and status ok
 * @return false  eny error
 */
bool SdfsIdfDriver::is_card() {
  //
  //   Check state if disk mounted
  //
  ESP_LOGD(TAG, "Check card. pdrv=%d, FS type = %s", this->pdrv_,
           this->fs_ == NULL ? "NO FS" : fat_type2str[this->fs_->fs_type]);

  //  For SDMMC
  if (this->bus_type_ == SD_MMC) {
    if ((this->fs_ != NULL) && (this->fs_->fs_type != 0)) {
      DSTATUS status = ff_disk_status(this->pdrv_);
      ESP_LOGV(TAG, "Disk retstat 0x%X", status);
      if (status & STA_NOINIT) {
        ESP_LOGD(TAG, "Seems disk ejected");
        unmount();
        return false;
      }
    } else
      return attach_card();
  }
  //  For SDSPI
  else {
#if defined(USE_SDSPI_MODE)
    if ((this->fs_ != NULL) && (this->fs_->fs_type != 0)) {
      connector_->beginTransaction();
      bool res = sdGetSectorsCount(this->pdrv_) != 0;
      connector_->endTransaction();
      if (!res) {
        unmount();
        return false;
      }
    } else
      return attach_card();
#endif
  }
  ESP_LOGD(TAG, "Check card OK");
  return true;
}

/***********************************************************************************
 *
 * @brief  Check and Initialize SD card in card slot.
 *
 * @return  bool   True if card attached
 *     //https://github.com/espressif/esp-idf/blob/master/components/sdmmc/sdmmc_init.c
 */
bool SdfsIdfDriver::attach_card() {
  ESP_LOGD(TAG, "Attach card.");

  esp_err_t rc = ESP_OK;
  bool is_card = false;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI)
    is_card = !(ff_sd_initialize(this->pdrv_) & STA_NOINIT);
#endif

#if defined(SOC_SDMMC_HOST_SUPPORTED) && defined(USE_SDMMC_MODE)
  if (this->bus_type_ == SD_MMC) {
    rc = sdmmc_card_init(this->host_config_, this->card_info_);
    is_card = rc == ESP_OK;

    //  Process result
    if (is_card) {
      int freq, sl_width;
      rc = sdmmc_host_get_real_freq(this->host_config_->slot, &freq);
      sl_width = sdmmc_host_get_slot_width(this->host_config_->slot);
      // freq = this->card_info_->real_freq_khz;
      // sl_width = this->card_info_->log_bus_width;

      ESP_LOGI(TAG, "Init SDCARD, slot %d, bus width %d bit, freq=%d khz", this->host_config_->slot, sl_width, freq);

    } else if (rc == ESP_ERR_TIMEOUT) {  // Timout. Lookslike no card in slot
      SET_RC(ERR_TYPE_LOCAL, RC_NO_CARD, "Card timeout.");
      is_card = false;
    } else {
      SET_RC(ERR_TYPE_FRAMEWORK, rc, "Cannot init card");
      is_card = false;
    }
  }
#endif

  ESP_LOGD(TAG, "Attach card. ret=%s", TRUEFALSE(is_card));
  return is_card;
}

/****************************************************************
 *
 * @brief   Testing connected driver. Open and list root dir.
 *
 * @return true
 * @return false
 */
bool SdfsIdfDriver::test() {
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

/***********************************************************************************
 *
 * @brief  Mount sd card as FAT
 *
 * @param format  true - format cd card  if no file structure found.
 * @return true
 * @return false
 */
bool SdfsIdfDriver::mount(std::string mountpoint, bool format) {
  ESP_LOGV(TAG, "Mount FS. pdrv=%d, Mountpoint %s", this->pdrv_, mountpoint.c_str());

  if (this->bus_type_ == SD_MMC) {
    this->fs_ = mount_sdmmc(this->pdrv_, mountpoint, format);
  } else {
    this->fs_ = mount_sdspi(this->pdrv_, mountpoint, format);
  }

  if (this->fs_ != NULL) {
    ESP_LOGD(TAG, "Disk mounnted. pdrv=%d, fs type %d", this->pdrv_, this->fs_->fs_type);
    return true;
  } else {
    ESP_LOGD(TAG, "Disk mount fail. pdrv=%d", this->pdrv_);
    return false;
  }
}

/***********************************************************************************
 *
 * @brief  Mount card drom sdspi bus
 *
 * @param pdrv
 * @param mountpoint
 * @param format
 * @return fsys_t*
 */
fsys_t *SdfsIdfDriver::mount_sdspi(uint8_t pdrv, std::string mountpoint, bool format) {
#if defined(USE_SDAPI_MODE)
  fsys_t *fs = NULL;
  mountpoint_ = mountpoint;
  fs = sdcard_mount(pdrv, mountpoint.c_str(), 5, format);
  // _impl->mountpoint(mountpoint.c_str());
  if (fs == NULL) {
    ESP_LOGE(TAG, "Cannot mount");
    sdcard_unmount(pdrv);
    // _impl->mountpoint(NULL);
  }
  return fs;
#else
  return NULL;
#endif
}
/***********************************************************************************
 *
 * @brief Mount card from sdmmc bus
 *
 * @param pdrv
 * @param mountpoint
 * @param format
 * @return fsys_t*
 */
fsys_t *SdfsIdfDriver::mount_sdmmc(uint8_t pdrv, std::string mountpoint, bool format) {
  mountpoint_ = mountpoint;
  fsys_t *fs = NULL;
  esp_err_t rc = ESP_OK;
  FRESULT mount_rc = FR_OK;

  this->mount_config_ = (esp_vfs_fat_mount_config_t *) calloc(sizeof(esp_vfs_fat_mount_config_t), 1);
  this->mount_config_->format_if_mount_failed = format;
  this->mount_config_->max_files = 5;
  this->mount_config_->allocation_unit_size = 16 * 1024;

  if (this->mount_config_ == NULL) {
    SET_RC(ERR_TYPE_LOCAL, RC_NO_MEM, "Mount. Not enough memory");
    return NULL;
  }

  ff_diskio_register_sdmmc(pdrv, this->card_info_);

  ff_sdmmc_set_disk_status_check(pdrv, true);

  char drv[3] = {(char) ('0' + pdrv), ':', 0};
  ESP_LOGD(TAG, "Disk registered. pdrv=%i, drv=%s, path=%s", pdrv, drv, mountpoint_.c_str());

  rc = esp_vfs_fat_register(mountpoint_.c_str(), drv, this->mount_config_->max_files, &fs);
  if (rc == ESP_ERR_INVALID_STATE) {
    // it's okay, already registered with VFS
  } else if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "esp_vfs_fat_register failed");
    goto unregister_fs;
  }

  mount_rc = f_mount(fs, drv, 1);
  if ((mount_rc != FR_OK) && (!format)) {
    SET_RC(ERR_TYPE_FILESYS, mount_rc, "Cannot mount");
    goto unregister_fs;

  } else if (format) {  // this->mount_config_->format_if_mount_failed
    bool need_mount_again = (mount_rc == FR_NO_FILESYSTEM || mount_rc == FR_INT_ERR);
    if (!need_mount_again) {
      SET_RC(ERR_TYPE_FILESYS, mount_rc, "Cannot format");
      goto unregister_fs;
    }
    ESP_LOGD(TAG, "FAT Prtitioning");
    if (!partition_card(this->mount_config_, drv, this->card_info_, pdrv)) {
      goto unregister_fs;
    }

    ESP_LOGD(TAG, "FAT mount again");
    mount_rc = f_mount(fs, drv, 1);
    if (mount_rc != FR_OK) {
      SET_RC(ERR_TYPE_FILESYS, mount_rc, "f_mount failed after formatting");
      goto unregister_fs;
    }
  }

  return fs;

unregister_fs:
  ESP_LOGD(TAG, "Reset registration");
  esp_vfs_fat_unregister_path(mountpoint_.c_str());
  FREE(this->mount_config_);
  // this->fs_ = NULL;
  return NULL;
}

/***********************************************************************************
 * @brief  Unmount and reset all mem blocks.
 *
 */
void SdfsIdfDriver::unmount() {
  ESP_LOGV(TAG, "Unmount FS, pdrv=%d, path=%s", this->pdrv_, this->mountpoint_.c_str());

  if (this->bus_type_ == SD_MMC) {
    unmount_sdmmc(this->pdrv_, this->mountpoint_);
  } else {
    unmount_sdspi(this->pdrv_, this->mountpoint_);
  }
  this->fs_ = NULL;
  // this->pdrv_ = FF_DRV_NOT_USED;
}

/***********************************************************************************
 *
 * @brief Unmount fatsf for card in sdmmc mode
 *
 * @param pdrv
 * @param mountpoint
 */
void SdfsIdfDriver::unmount_sdmmc(uint8_t pdrv, std::string mountpoint) {
  esp_err_t rc = ESP_OK;

  //  Unmount filesystem
  char drv[3] = {(char) ('0' + pdrv), ':', 0};
  FRESULT res = f_mount(0, drv, 0);
  if (res != FR_OK) {
    SET_RC(ERR_TYPE_FILESYS, res, "Unmount return");
  }
  //  Clear registration
  ff_diskio_register(pdrv, NULL);
  rc = esp_vfs_fat_unregister_path(mountpoint_.c_str());
  if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "Cannot unregister root path");
  }
  FREE(this->mount_config_);

  //
  //  Reinit slot
  //
#if defined(SOC_SDMMC_HOST_SUPPORTED)
  uint8_t slot_num = this->parent_->bus_slot_ == 0 ? SDMMC_HOST_SLOT_0 : SDMMC_HOST_SLOT_1;
  rc = sdmmc_host_init_slot(slot_num, this->slot_config_);
  if (rc != ESP_OK) {
    SET_RC(ERR_TYPE_FRAMEWORK, rc, "Failed to init slot host");
    return;
  }
  ESP_LOGI(TAG, "Reset slot inicialization, slot %d, width %d", slot_num, this->slot_config_->width);
  this->host_config_->slot = slot_num;
#endif
}

/***********************************************************************************
 *
 * @brief  Unmount fatsf for card in sdspi mode
 *
 * @param pdrv
 * @param mountpoint
 */
void SdfsIdfDriver::unmount_sdspi(uint8_t pdrv, std::string mountpoint) {
#if defined(USE_SDSPI_MODE)
  sdspi_unmount(pdrv);
#endif
  this->fs_ = NULL;
}

/***********************************************************************************
 * @brief  Create default partition table  for new card.
 *
 * @param mount_config
 * @param drv
 * @param card
 * @param pdrv
 * @return FRESULT
 */
uint16_t partition_card(const esp_vfs_fat_mount_config_t *mount_config, const char *drv, sdmmc_card_t *card,
                        BYTE pdrv) {
  FRESULT res = FR_OK;
  esp_err_t err;
  const size_t workbuf_size = 4096;
  void *workbuf = NULL;
  ESP_LOGW(TAG, "partitioning card");

  workbuf = ff_memalloc(workbuf_size);
  if (workbuf == NULL) {
    ESP_LOGE(TAG, "not enough mem");
    return ERR_TYPE_FRAMEWORK << 8 | ESP_ERR_NO_MEM;
  }

#ifdef USE_ESP_IDF
  LBA_t plist[] = {100, 0, 0, 0};
  res = f_fdisk(pdrv, plist, workbuf);
  if (res != FR_OK) {
    err = ESP_FAIL;
    ESP_LOGD(TAG, "f_fdisk failed (%d)", res);
    free(workbuf);
    return ERR_TYPE_FILESYS << 8 | err;
  }
#endif

  size_t alloc_unit_size =
      esp_vfs_fat_get_allocation_unit_size(card->csd.sector_size, mount_config->allocation_unit_size);
  ESP_LOGW(TAG, "formatting card, allocation unit size=%d", alloc_unit_size);

#ifdef USE_ESP_IDF
  const MKFS_PARM opt = {(BYTE) FM_ANY, 0, 0, 0, alloc_unit_size};
  res = f_mkfs(drv, &opt, workbuf, workbuf_size);
#else
  res = f_mkfs(drv, FM_ANY, 0, workbuf, workbuf_size);
#endif
  if (res != FR_OK) {
    err = ESP_FAIL;
    ESP_LOGD(TAG, "f_mkfs failed (%d)", res);
    free(workbuf);
    return ERR_TYPE_FILESYS << 8 | err;
  }

  free(workbuf);
  return 0;
}

/***********************************************************************************
 *   Convert filesystem errors to string
 *
 */
// const char *fs_err_str(FRESULT rc) {
//   switch (rc) {
//     case FR_DISK_ERR:
//       return "A hard error occurred in the low level disk I/O layer";
//     case FR_INT_ERR:
//       return "Assertion failed";
//     case FR_NOT_READY:
//       return "The physical drive cannot work";
//     case FR_NO_FILE:
//       return "Could not find the file";
//     case FR_NO_PATH:
//       return "Could not find the path ";
//     case FR_INVALID_NAME:
//       return "The path name format is invalid";
//     case FR_DENIED:
//       return "Access denied due to prohibited access or directory full";
//     case FR_EXIST:
//       return "Access denied due to prohibited access";
//     case FR_INVALID_OBJECT:
//       return "The file/directory object is invalid";
//     case FR_WRITE_PROTECTED:
//       return "The physical drive is write protected";
//     case FR_INVALID_DRIVE:
//       return "The logical drive number is invalid";
//     case FR_NOT_ENABLED:
//       return "The volume has no work area";
//     case FR_NO_FILESYSTEM:
//       return "There is no valid FAT volume ";
//     case FR_MKFS_ABORTED:
//       return "The f_mkfs() aborted due to any problem";
//     case FR_TIMEOUT:
//       return "Could not get a grant to access the volume within defined period";
//     case FR_LOCKED:
//       return "The operation is rejected according to the file sharing policy";
//     case FR_NOT_ENOUGH_CORE:
//       return "LFN working buffer could not be allocated";
//     case FR_TOO_MANY_OPEN_FILES:
//       return "Number of open files > FF_FS_LOCK";
//     case FR_INVALID_PARAMETER:
//       return "Given parameter is invalid";
//     default:
//       return "Unknown";
//   }
// }

}  // namespace sdfs
}  // namespace esphome
   // #endif

#endif