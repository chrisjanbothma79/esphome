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

#endif
#include "driver/sdspi_host.h"
// #include "diskio_impl.h"
#include "hal/spi_types.h"
#include "esp_vfs_fat.h"
#include "vfs_fat_internal.h"
#include "sdfs.h"
#include "sdmmc_drv_idf.h"
#include "stdio.h"

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

void SdmmcIdfDriver::set_parent(SdmmcHost *p) { this->parent_ = p; }
uint32_t SdmmcIdfDriver::get_last_err() { return this->last_err_; }

bool SdmmcIdfDriver::sdspi_allocate() {
  ESP_LOGD(TAG, "SdmmcHost init");
  //   Allocate mem for SPI HOST_CONFIG
  sdmmc_host_t new_config = SDSPI_HOST_DEFAULT();
  this->host_config_ = (sdmmc_host_t *) calloc(sizeof(sdmmc_host_t), 1);
  if (this->host_config_ == NULL) {
    ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
    FREE(this->host_config_);
    return false;
  }
  memcpy(this->host_config_, &new_config, sizeof(sdmmc_host_t));

  // spi_bus_config_t *spi_bus_config_{nullptr};

  this->spi_dev_config_ = (sdspi_device_config_t *) calloc(sizeof(sdspi_device_config_t), 1);
  if (this->spi_dev_config_ == NULL) {
    ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
    FREE(this->host_config_);
    return false;
  }

  //   Allocate mem for Detected  CARD_CONFIG
  // this->card_info_ = (sdmmc_card_t *) calloc(sizeof(sdmmc_card_t), 1);
  // if (this->card_info_ == NULL) {
  //   ESP_LOGD(TAG, "Not enaught memeory for initialize sdmmc");
  //   FREE(this->host_config_);
  //   FREE(this->spi_dev_config_);
  //   return false;
  // }
  return true;
}

/***********************************************************************************
 * @brief  Allocate required emory vof SDIO host structures
 *
 * @return true
 * @return false  if no mem
 */
bool SdmmcIdfDriver::sdmmc_allocate() {
#if defined(SOC_SDMMC_HOST_SUPPORTED)
  ESP_LOGD(TAG, "SdmmcHost init");
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
bool SdmmcIdfDriver::init_host(SdConnType bus_type) {
  this->bus_type_ = bus_type;
  uint8_t ret_status = 0;

  if (this->bus_type_ == SD_MMC) {
    if (!sdmmc_allocate())
      return false;
    ret_status = init_sdmmc(this->host_config_);
  } else {
    ret_status = init_sdspi(this->host_config_);
  }
  if (ret_status == RET_STATUS_FAIL) {
    return false;
  }
  return true;
}

/***********************************************************************************
 * @brief  Initd sd card perphiral driver in  SDMMC mode
 *
 * @return sdmmc_host_t*
 */
uint8_t SdmmcIdfDriver::init_sdmmc(sdmmc_host_t *host_config) {
#if defined(SOC_SDMMC_HOST_SUPPORTED)

  esp_err_t rc = ESP_OK;
  uint8_t slot_num;

  // host_config->max_freq_khz = SDMMC_FREQ_HIGHSPEED;
  // rc = (*host_config->init)();

  rc = sdmmc_host_init();
  if (rc != ESP_OK) {
    ESP_LOGE(TAG, "Failed to init SDMMC host (0x%x)", rc);
    return RET_STATUS_FAIL;
  }

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

  //
  //  Init slot
  //
  slot_num = this->parent_->bus_slot_ == 0 ? SDMMC_HOST_SLOT_0 : SDMMC_HOST_SLOT_1;
  rc = sdmmc_host_init_slot(slot_num, this->slot_config_);
  if (rc != ESP_OK) {
    SET_RC(FW_ERR, rc, "Failed to init slot host");
    return RET_STATUS_FAIL;
  }
  ESP_LOGI(TAG, "SDSPI Init bus, slot %d, width %d", slot_num, this->slot_config_->width);
  this->host_config_->slot = slot_num;

  //
  //   Check for card and load host params
  //
  if (!this->attach_card()) {
    // if (this->is_last_err(LC_ERR, ESP_ERR_TIMEOUT))
    //   return RET_STATUS_NOTCRITICAL;
    if (IS_LAST_ERR(LC_ERR, ESP_ERR_TIMEOUT))
      return RET_STATUS_NOTCRITICAL;
  } else {
    return RET_STATUS_FAIL;
  }
  //   rc = sdmmc_card_init(this->host_config_, this->card_info_);
  //   // this->host_config_ = &this->card_info_->host;
  //   if (rc == ESP_OK) {
  //     int freq = 0;
  // #ifdef USE_ESP32_FRAMEWORK_ARDUINO
  //     freq = this->card_info_->host.max_freq_khz;
  // #elif USE_ESP_IDF
  //     rc = sdmmc_host_get_real_freq(this->host_config_->slot, &freq);
  // #endif
  //     ESP_LOGI(TAG, "SDSPI card found, slot %d, bus width %d bit, freq=%d khz", this->host_config_->slot,
  //              sdmmc_host_get_slot_width(slot_num), freq);

  //   } else if (rc == ESP_ERR_TIMEOUT) {  // Timout
  //     ESP_LOGD(TAG, "No sd card in slot RC=(0x%x Timeout)", rc);
  //     return RET_STATUS_NOTCRITICAL;
  //   } else
  //     return RET_STATUS_FAIL;

  return RET_STATUS_OK;
#endif
  return RET_STATUS_FAIL;
}

/***********************************************************************************
 * @brief   Configure sdcard driver as SDSPI
 *
 * @return sdmmc_host_t*
 */
uint8_t SdmmcIdfDriver::init_sdspi(sdmmc_host_t *host_config) {
  esp_err_t rc = ESP_OK;
  int card_handle = -1;  // uninitialized
  spi_host_device_t spi_bus_id;
  spi_dma_chan_t dma_chan = SPI_DMA_CH_AUTO;

  ESP_LOGD(TAG, "init_sdspi");

  rc = (*host_config->init)();
  if (rc != ESP_OK) {
    SET_RC(LC_ERR, RC_INVALID_ARG, "Cannot init sd host");
    return RET_STATUS_FAIL;
  }

  rc = sdspi_host_init();
  if (rc != ESP_OK) {
    ESP_LOGE(TAG, "Failed to init SDMMC host (0x%x)", rc);
    return RET_STATUS_FAIL;
  }

  if (this->parent_->bus_slot_ = 0) {
    spi_bus_id = SPI1_HOST;
  }  //< SPI host to use, SPIx_HOST (see spi_types.h).
  if (this->parent_->bus_slot_ = 1) {
    spi_bus_id = SPI2_HOST;
  }
#if SOC_SPI_PERIPH_NUM > 2
  if (this->parent_->bus_slot_ = 2) {
    spi_bus_id = SPI3_HOST;
  }
#endif
  else {
    ESP_LOGE(TAG, "Incorrect spi host id %d", this->parent_->bus_slot_);
    SET_RC(LC_ERR, RC_INVALID_ARG, "Incorect arguments");
    return RET_STATUS_FAIL;
    return false;
  }

#ifdef USE_ESP32_VARIANT_ESP32S2
  dma_chan = spi_bus_id;
#endif

  if ((this->parent_->clk_pin_ < 255) || (this->parent_->miso_pin_ < 255) || (this->parent_->mosi_pin_ < 255)) {
    SET_RC(LC_ERR, RC_INVALID_ARG, "Misconfigured SPI pins");
    return RET_STATUS_FAIL;
  }

  ESP_LOGD(TAG, "Initilize SPI peripheral");
  this->spi_bus_config_->mosi_io_num = this->parent_->mosi_pin_,
  this->spi_bus_config_->miso_io_num = this->parent_->miso_pin_,
  this->spi_bus_config_->sclk_io_num = this->parent_->clk_pin_, this->spi_bus_config_->quadwp_io_num = -1,
  this->spi_bus_config_->quadhd_io_num = -1, this->spi_bus_config_->max_transfer_sz = 4000,

  rc = spi_bus_initialize(spi_bus_id, this->spi_bus_config_, dma_chan);
  if (rc != ESP_OK) {
    SET_RC(FW_ERR, rc, "Failed to initialize SPI bus.");
    return RET_STATUS_FAIL;
  }

  //
  //   Initialize  SPI  Device
  //

  this->spi_dev_config_->host_id = spi_bus_id;
  this->spi_dev_config_->gpio_cs = this->parent_->cs_pin_ < 255 ? static_cast<gpio_num_t>(this->parent_->cs_pin_)
                                                                : GPIO_NUM_13;  ///< GPIO number of CS signal
  this->spi_dev_config_->gpio_cd = this->parent_->cd_pin_ < 255
                                       ? static_cast<gpio_num_t>(this->parent_->cd_pin_)
                                       : SDSPI_SLOT_NO_CD;  ///< GPIO number of card detect signal
  this->spi_dev_config_->gpio_wp = this->parent_->wp_pin_ < 255
                                       ? static_cast<gpio_num_t>(this->parent_->wp_pin_)
                                       : SDSPI_SLOT_NO_WP;  ///< GPIO number of write protect signal
  this->spi_dev_config_->gpio_int = this->parent_->int_pin_ < 255
                                        ? static_cast<gpio_num_t>(this->parent_->int_pin_)
                                        : GPIO_NUM_NC;  ///< GPIO number of interrupt line (input) for SDIO card.

  int out_slot = 0;
  rc = sdspi_host_init_device(this->spi_dev_config_, &out_slot);
  if (rc != ESP_OK) {
    SET_RC(FW_ERR, rc, "Failed to attach sdspi device onto an SPI bus ");
    return RET_STATUS_FAIL;
  }

  this->host_config_->slot = out_slot;

  if (!this->attach_card()) {
    if (IS_LAST_ERR(LC_ERR, ESP_ERR_TIMEOUT))
      return RET_STATUS_NOTCRITICAL;
  } else {
    return RET_STATUS_FAIL;
  }

  //  TODO Attach card

  return RET_STATUS_OK;
}

/***********************************************************************************
 * @brief   Check card status. (is card present in slot)
 *
 * @return true  card present and status ok
 * @return false  eny error
 */
bool SdmmcIdfDriver::is_card() {
  //
  //   Check state if disk mounted
  //

  ESP_LOGVV(TAG, "Check card. FS is %s,  fs type = %d", this->fs_ == NULL ? "NULL" : "NOT NULL",
            this->fs_ == NULL ? 0 : this->fs_->fs_type);

  if ((this->fs_ != NULL) && (this->fs_->fs_type != 0)) {
    DSTATUS status = ff_disk_status(this->pdrv_);
    ESP_LOGV(TAG, "FS is 0x%X", status);

    if (status & STA_NOINIT) {
      ESP_LOGD(TAG, "Seems disk ejected");
      unmount();
      // return attach_card();
      return false;
    }
    return true;
  }
  //
  //   Check card if not mounted
  //
  else {
    return attach_card();
  }
}

/***********************************************************************************
 * @brief  Check and Initialize SD card in card slot.
 *
 * @return  bool   True if card attached
 *     //https://github.com/espressif/esp-idf/blob/master/components/sdmmc/sdmmc_init.c
 */
bool SdmmcIdfDriver::attach_card() {
  esp_err_t rc = ESP_OK;

  rc = sdmmc_card_init(this->host_config_, this->card_info_);
  if (rc == ESP_OK) {
    int freq, sl_width;

#if defined(USE_ESP_IDF)
    freq = this->card_info_->real_freq_khz;
#endif

#if defined(USE_ESP32_FRAMEWORK_ARDUINO) || !defined(SOC_SDMMC_HOST_SUPPORTED)
    freq = this->card_info_->host.max_freq_khz;
    sl_width = this->card_info_->log_bus_width;
#else
    rc = sdmmc_host_get_real_freq(this->host_config_->slot, &freq);
    sl_width = sdmmc_host_get_slot_width(this->host_config_->slot);
#endif
    ESP_LOGI(TAG, "Init SDCARD, slot %d, bus width %d bit, freq=%d khz", this->host_config_->slot, sl_width, freq);

  } else if (rc == ESP_ERR_TIMEOUT) {  // Timout. Lookslike no card in slot
    this->last_err_ = (LC_ERR << 16) | ESP_ERR_TIMEOUT;
    return false;
  } else {
    SET_RC(LC_ERR, RC_NO_CARD, "No sd card in slot");
    return false;
  }

  return true;
}

/***********************************************************************************
 * @brief  Mount sd card fise structure
 *
 * @param format  true - format cd card  if no file structure found.
 * @return true
 * @return false
 */
bool SdmmcIdfDriver::mount(std::string mountpoint, bool format) {
  ESP_LOGD(TAG, "Mount FS");
  mountpoint_ = mountpoint;
  BYTE pdrv = FF_DRV_NOT_USED;
  FATFS *fs = NULL;
  esp_err_t rc = ESP_OK;
  FRESULT mount_rc = FR_OK;

  this->mount_config_ = (esp_vfs_fat_mount_config_t *) calloc(sizeof(esp_vfs_fat_mount_config_t), 1);
  this->mount_config_->format_if_mount_failed = format;
  this->mount_config_->max_files = 5;
  this->mount_config_->allocation_unit_size = 16 * 1024;

  if (this->mount_config_ == NULL) {
    SET_RC(FW_ERR, ESP_ERR_NO_MEM, "Not enough memory");
    return false;
  }

  //   Select  drive for mount.
  if (ff_diskio_get_drive(&pdrv) != ESP_OK || pdrv == FF_DRV_NOT_USED) {
    free(this->mount_config_);
    SET_RC(FW_ERR, rc, "the maximum count of volumes is already mounted");
    return false;
  }

  //
  //   Register path
  //

  ff_diskio_register_sdmmc(pdrv, this->card_info_);
#if defined(USE_ESP_IDF) && defined(USE_ESP32_VARIANT_ESP32)
  ff_sdmmc_set_disk_status_check(pdrv, true);
#endif

  char drv[3] = {(char) ('0' + pdrv), ':', 0};
  ESP_LOGD(TAG, "Disk registered. pdrv=%i, drv=%s, path=%s", pdrv, drv, mountpoint_.c_str());

  rc = esp_vfs_fat_register(mountpoint_.c_str(), drv, this->mount_config_->max_files, &fs);
  if (rc == ESP_ERR_INVALID_STATE) {
    // it's okay, already registered with VFS
  } else if (rc != ESP_OK) {
    SET_RC(FW_ERR, rc, "esp_vfs_fat_register failed");
    goto unregister_fs;
  }

  mount_rc = f_mount(fs, drv, 1);
  if ((mount_rc != FR_OK) && (!format)) {
    SET_RC(FS_ERR, mount_rc, "Cannot mount");
    goto unregister_fs;

  } else if (format) {  // this->mount_config_->format_if_mount_failed
    bool need_mount_again = (mount_rc == FR_NO_FILESYSTEM || mount_rc == FR_INT_ERR);
    if (!need_mount_again) {
      SET_RC(FS_ERR, mount_rc, "Cannot format");
      goto unregister_fs;
    }
    ESP_LOGD(TAG, "FAT Prtitioning");
    if (!partition_card(this->mount_config_, drv, this->card_info_, pdrv)) {
      goto unregister_fs;
    }

    ESP_LOGD(TAG, "FAT mount again");
    mount_rc = f_mount(fs, drv, 1);
    if (mount_rc != FR_OK) {
      SET_RC(FS_ERR, mount_rc, "f_mount failed after formatting");
      goto unregister_fs;
    }
  }

  this->pdrv_ = pdrv;
  this->fs_ = fs;
  ESP_LOGD(TAG, "Disk mounnted. pdrv - %d, fs type %d", this->pdrv_, this->fs_->fs_type);
  return true;

unregister_fs:
  ESP_LOGD(TAG, "Reset registration");
  esp_vfs_fat_unregister_path(mountpoint_.c_str());
  FREE(this->mount_config_);
  this->fs_ = NULL;
  return false;
}

/***********************************************************************************
 * @brief  Unmount and reset all mem blocks.
 *
 */
void SdmmcIdfDriver::unmount() {
  esp_err_t rc = ESP_OK;
  ESP_LOGVV(TAG, "Unmount FS, path %s, pdrv %d", mountpoint_.c_str(), this->pdrv_);

  //  Unmount filesystem
  char drv[3] = {(char) ('0' + this->pdrv_), ':', 0};
  FRESULT res = f_mount(0, drv, 0);
  if (res != FR_OK) {
    SET_RC(FS_ERR, res, "Unmount return");
  }

  //  Clear registration
  ff_diskio_register(this->pdrv_, NULL);

  rc = esp_vfs_fat_unregister_path(mountpoint_.c_str());
  if (rc != ESP_OK) {
    SET_RC(FW_ERR, rc, "Cannot unregister root path");
  }

  this->pdrv_ = FF_DRV_NOT_USED;
  FREE(this->mount_config_);
  // FREE(this->fs_);
  this->fs_ = NULL;

  //
  //  Reinit slot
  //
#if defined(SOC_SDMMC_HOST_SUPPORTED)
  if (this->bus_type_ == SD_MMC) {
    uint8_t slot_num = this->parent_->bus_slot_ == 0 ? SDMMC_HOST_SLOT_0 : SDMMC_HOST_SLOT_1;
    rc = sdmmc_host_init_slot(slot_num, this->slot_config_);
    if (rc != ESP_OK) {
      SET_RC(FW_ERR, rc, "Failed to init slot host");
      return;
    }
    ESP_LOGI(TAG, "Reset slot inicialization, slot %d, width %d", slot_num, this->slot_config_->width);
    this->host_config_->slot = slot_num;
  }
#endif
}
/**
 * @brief   Testing connected driver. Open and list root dir.
 *
 * @return true
 * @return false
 */
bool SdmmcIdfDriver::test() { return true; }

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
    return FW_ERR << 8 | ESP_ERR_NO_MEM;
  }

#ifdef USE_ESP_IDF
  LBA_t plist[] = {100, 0, 0, 0};
  res = f_fdisk(pdrv, plist, workbuf);
  if (res != FR_OK) {
    err = ESP_FAIL;
    ESP_LOGD(TAG, "f_fdisk failed (%d)", res);
    free(workbuf);
    return FS_ERR << 8 | err;
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
    return FS_ERR << 8 | err;
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