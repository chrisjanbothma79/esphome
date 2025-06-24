#include "sdfs.h"
#include "sdfs_defines.h"
#if defined(USE_ESP_IDF)
#include "sdfs_drv_idf.h"
#include "esphome/core/log.h"
#include "esp_vfs_fat.h"
#include "stdio.h"

#if defined(USE_SDMMC_MODE) && defined(SOC_SDMMC_HOST_SUPPORTED)
#define _HAS_SDMMC_
#include "sdmmc_io.h"
#endif

// #include "driver/sdspi_host.h"
// #include "diskio_impl.h"
// #include "hal/spi_types.h"

#if defined(USE_SDSPI_MODE)
#include "sdspi_io.h"
#endif

namespace esphome {
namespace sdfs {

#ifdef USE_ESP32_FRAMEWORK_ARDUINO
// #define SPI_BUS_COUNT  SPI_COUNT   //SOC_SPI_PERIPH_NUM
#define SPI_BUS_COUNT SOC_SPI_PERIPH_NUM  // SOC_SPI_PERIPH_NUM
#else
#define SPI_BUS_COUNT SPI_HOST_MAX
#endif

static const char *TAG = "sdmmc_drv_idf";

// uint16_t partition_card(const esp_vfs_fat_mount_config_t *, const char *, sdmmc_card_t *, BYTE);

// static void call_host_deinit_(const sdmmc_host_t *host_config) {
//   if (host_config->flags & SDMMC_HOST_FLAG_DEINIT_ARG) {
//     host_config->deinit_p(host_config->slot);
//   } else {
//     host_config->deinit();
//   }
// }

/***********************************************************************************
 *
 * @brief Construct a new Sdfs Idf Driver:: Sdfs Idf Driver object
 *
 */
SdfsIdfDriver::SdfsIdfDriver() {
  this->pdrv_ = 0xFF;
#if defined(_HAS_SDMMC_)
  this->mmc_connector = new SdmmcIO();
#endif
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

/***********************************************************************************
 * @brief  Initialize perpirals driver
 *
 */
bool SdfsIdfDriver::init_host(SdConnType bus_type) {
  this->bus_type_ = bus_type;
  uint8_t ret_status = 0;

  if (this->bus_type_ == SD_MMC) {
    ret_status = init_sdmmc();
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
uint8_t SdfsIdfDriver::init_sdmmc() {
  uint8_t ret_st = RET_STATUS_FAIL;

#if defined(_HAS_SDMMC_)
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

    bool ret = this->mmc_connector->init();
    this->pdrv_ = this->mmc_connector->get_pdrv();
    if (ret) {
      ret_st = RET_STATUS_OK;
      if (this->mmc_connector->init_card() != SDMMC_RET_STATUS_OK) {
        ret_st = RET_STATUS_NOTCRITICAL;
      }
    }
  }
#endif

  return ret_st;
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
#if defined(_HAS_SDMMC_)
    init_status_t st = this->mmc_connector->get_disk_status();
    if (st = SDMMC_RET_STATUS_OK)
      return true;
    else {
      this->mmc_connector->unmount();
      return false;
    }
    //  For SDSPI
#endif
  } else {
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

#if defined(_HAS_SDMMC_)
  if (this->bus_type_ == SD_MMC) {
    is_card = this->mmc_connector->init_card() == SDMMC_RET_STATUS_OK;
  }
#endif

  ESP_LOGD(TAG, "Attach card. ret=%s", TRUEFALSE(is_card));
  return is_card;
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
#if defined(_HAS_SDMMC_)
    this->fs_ = this->mmc_connector->mount(mountpoint);
    if ((this->fs_ != NULL) && (IS_LAST_ERR(ERR_TYPE_LOCAL, RC_NOT_FORMATED)) && format) {
      ESP_LOGD(TAG, "Disk mount fail.  Will formated pdrv=%d", this->pdrv_);
      local_rc_t format_res = this->mmc_connector->format();
      if (format_res == RC_OK) {
        this->fs_ = this->mmc_connector->mount(mountpoint);
      }
    }
#endif
  } else {
#if defined(USE_SDSPI_MODE)
    mountpoint_ = mountpoint;
    this->fs_ = sdspi_mount(this->pdrv_, mountpoint.c_str(), 5, format);
    if (this->fs_ == NULL) {
      sdspi_unmount(this->pdrv_);
    }
    // TODO:  Add formating
#endif
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
 * @brief  Unmount and reset all mem blocks.
 *
 */
void SdfsIdfDriver::unmount() {
  ESP_LOGV(TAG, "Unmount FS, pdrv=%d, path=%s", this->pdrv_, this->mountpoint_.c_str());

  if (this->bus_type_ == SD_MMC) {
#if defined(_HAS_SDMMC_)
    this->mmc_connector->unmount();
#endif
  } else {
#if defined(USE_SDSPI_MODE)
    sdspi_unmount(this->pdrv_);
#endif
  }
  this->fs_ = NULL;
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

}  // namespace sdfs
}  // namespace esphome
   // #endif

#endif