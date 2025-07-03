#include "sdfs_drv.h"
#include "sdfs_defines.h"
#include "esphome/core/log.h"

#ifndef USE_ESP8266
#include "esp_vfs_fat.h"

//#define 	CONFIG_FATFS_CODEPAGE
/* This option specifies the OEM code page to be used on the target system.
/  Incorrect code page setting can cause a file open failure.
*/

//
//   Arduino
//
#if defined(USE_ARDUINO)
#include "dirent.h"
#include "esp_system.h"
extern "C" {
#include "ff.h"
}

#if defined(USE_SDSPI_MODE)
#include "sdspi_io.h"
#endif

#if defined(_HAS_SDMMC_)
#include "SD_MMC.h"
#include "sdmmc_io.h"

#endif

//
//   ESP-IDF
//
#elif defined(USE_ESP_IDF)
#include "stdio.h"

#if defined(USE_SDSPI_MODE)
#include "sdspi_io.h"
#endif

#if defined(_HAS_SDMMC_)
#include "sdmmc_io.h"
#endif

#endif

namespace esphome {
namespace sdfs {

static const char *const TAG = "sdspi_drv_ard";

SdfsDriver::SdfsDriver() {
  this->pdrv_ = 0xFF;
#if defined(_HAS_SDMMC_)
  this->mmc_io = new SdmmcIO();
#endif
}

void SdfsDriver::set_parent(SdfsHost *p) { this->parent_ = p; }
#if defined(USE_SDSPI_MODE)
void SdfsDriver::set_connector(SpiConnector *cn) { this->connector_ = cn; }
#endif

/****************************************************************
 *
 * @brief Start SPI snd SD card slot.
 *
 * @return true
 * @return false
 */
bool SdfsDriver::init_host(SdConnType bus_type) {
  this->bus_type_ = bus_type;
  bool ret = false;
  // if (this->parent_->pw_ctrl_pin_ != NULL) pw_ctrl_pin_ = this->parent_->pw_ctrl_pin_;
  // if (this->parent_->cd_pin_ != NULL) cd_pin_ = this->parent_->cd_pin_;

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
#if defined(_HAS_SDMMC_)
  // TODO:  set pins
  if (this->bus_type_ == SD_MMC) {
    this->mmc_io->set_bus_slot(this->parent_->bus_slot_);
    this->mmc_io->set_bus_width(this->parent_->spi_bus_width_);
    // this->mmc_io->set_cd_pin(static_cast<gpio_num_t>(this->parent_->cd_pin_->get_pin()));
    this->mmc_io->set_wp_pin(static_cast<gpio_num_t>(this->parent_->cd_pin_));

    this->mmc_io->set_wp_pin(static_cast<gpio_num_t>(this->parent_->wp_pin_));
    this->mmc_io->set_clk_pin(static_cast<gpio_num_t>(this->parent_->clk_pin_));
    this->mmc_io->set_cmd_pin(static_cast<gpio_num_t>(this->parent_->cmd_pin_));
    this->mmc_io->set_data0_pin(static_cast<gpio_num_t>(this->parent_->data0_pin_));
    this->mmc_io->set_data1_pin(static_cast<gpio_num_t>(this->parent_->data1_pin_));
    this->mmc_io->set_data2_pin(static_cast<gpio_num_t>(this->parent_->data2_pin_));
    this->mmc_io->set_data3_pin(static_cast<gpio_num_t>(this->parent_->data3_pin_));
    this->mmc_io->set_data4_pin(static_cast<gpio_num_t>(this->parent_->data4_pin_));
    this->mmc_io->set_data5_pin(static_cast<gpio_num_t>(this->parent_->data5_pin_));
    this->mmc_io->set_data6_pin(static_cast<gpio_num_t>(this->parent_->data6_pin_));
    this->mmc_io->set_data7_pin(static_cast<gpio_num_t>(this->parent_->data7_pin_));

    ret = this->mmc_io->init();
    this->pdrv_ = this->mmc_io->get_pdrv();
    if (ret) {
      if (this->mmc_io->init_card() != RET_STATUS_OK) {
        ret = false;
      }
    }
  }
#endif

  return ret;
}

// TODO: Add destructor
void SdfsDriver::end() {
#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    sdspi_uninit(this->pdrv_);
  }
#endif
}
/****************************************************************
 *
 * @brief Check if filesystem is mounted (defined)
 *
 * @return true
 * @return false
 */
bool SdfsDriver::is_mount() { return (this->fs_ != NULL) && (this->fs_->fs_type != 0); }

/****************************************************************
 *
 * @brief  if cars mounted get sectors count.  if not, just try attach
 * thia check card status.
 * @return true
 * @return false
 */
bool SdfsDriver::is_card() {
  bool ret = false;
  if (is_mount()) {
    //
    //   Check state if disk mounted
    //
    ESP_LOGD(TAG, "Check card. pdrv=%d, FS type = %s", this->pdrv_,
             this->fs_ == NULL ? "NO FS" : fat_type2str[this->fs_->fs_type]);
#if defined(USE_SDSPI_MODE)
    if (this->bus_type_ == SD_SPI) {
      connector_->beginTransaction();
      ret = sdGetSectorsCount(this->pdrv_) != 0;
      connector_->endTransaction();
      if (!ret) {
        unmount();
      }
    }
#endif
#if defined(_HAS_SDMMC_)
    if (this->bus_type_ == SD_MMC) {
      ret = this->mmc_io->get_disk_status() == RET_STATUS_OK;
      if (!ret) {
        this->mmc_io->unmount();
      }
    }
#endif
  } else {
    ret = attach_card();
  }
  ESP_LOGD(TAG, "Check card. Card found %s", TRUEFALSE(ret));
  return ret;
}

/****************************************************************
 *
 * @brief  Try to access the card.  This check is card present
 *
 * @return true
 * @return false
 */
bool SdfsDriver::attach_card() {
  bool is_card = false;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    is_card = !(ff_sd_initialize(pdrv_) & STA_NOINIT);
  }
#endif
#if defined(_HAS_SDMMC_)
  if (this->bus_type_ == SD_MMC) {
    // init_status_t status = this->mmc_io->init_card();
    // if ( status == SDMMC_RET_STATUS_OK )
    is_card = this->mmc_io->init_card() == RET_STATUS_OK;
  }
#endif
  ESP_LOGD(TAG, "Attach card. ret=%s", TRUEFALSE(is_card));
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
bool SdfsDriver::mount(std::string mountpoint, bool format) {
  // ESP_LOGV(TAG, "Mount FS. pdrv=%d, Mountpoint %s", this->pdrv_, mountpoint.c_str());
#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    this->fs_ = sdspi_mount(this->pdrv_, mountpoint.c_str(), 5, format);
    if (this->fs_ == NULL) {
      sdspi_unmount(this->pdrv_);
    }
  }
#endif

#if defined(_HAS_SDMMC_)
  if (this->bus_type_ == SD_MMC) {
    this->fs_ = this->mmc_io->mount(mountpoint);
    if ((this->fs_ != NULL) && (IS_LAST_ERR(ERR_TYPE_LOCAL, RC_NOT_FORMATED)) && format) {
      ESP_LOGD(TAG, "Disk mount fail.  Will formated pdrv=%d", this->pdrv_);
      local_rc_t format_res = this->mmc_io->format();
      if (format_res == RC_OK) {
        this->fs_ = this->mmc_io->mount(mountpoint);
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
bool SdfsDriver::test() {
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
void SdfsDriver::unmount() {
  // _impl->mountpoint(NULL);
#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    sdspi_unmount(this->pdrv_);
  }
#endif
#if defined(_HAS_SDMMC_)
  if (this->bus_type_ == SD_MMC) {
    this->mmc_io->unmount();
  }
#endif
  this->fs_ = NULL;
}

card_type_t SdfsDriver::card_type() {
  card_type_t type = C_NONE;
  if (!is_mount())
    return type;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    type = ff_sd_type(this->pdrv_);
  }
#endif
#if defined(_HAS_SDMMC_)
  if (this->bus_type_ == SD_MMC) {
    if (this->mmc_io->is_card_mem())
      type = C_UNKNOWN;
    else if (this->mmc_io->is_card_sdio())
      type = C_SD;
    else if (this->mmc_io->is_card_mmc())
      type = C_MMC;
    else
      type = C_UNKNOWN;
  }
#endif
  return type;
}

uint64_t SdfsDriver::card_size() {
  if (!is_mount())
    return 0;
  return (uint64_t) num_sectors();
}

size_t SdfsDriver::num_sectors() {
  size_t sectors = 0;
  if (!is_mount())
    return 0;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    sectors = ff_sd_sectors(this->pdrv_);
  }
#endif
#if defined(_HAS_SDMMC_)
  if (this->bus_type_ == SD_MMC) {
    sectors = this->mmc_io->sectors();
  }
#endif
  return sectors;
}

size_t SdfsDriver::sector_size() {
  size_t size = 0;
  if (!is_mount())
    return 0;

#if defined(USE_SDSPI_MODE)
  if (this->bus_type_ == SD_SPI) {
    size = FF_SS_SDCARD;
  }
#endif
#if defined(_HAS_SDMMC_)
  if (this->bus_type_ == SD_MMC) {
    size = this->mmc_io->sector_size();
  }
#endif
  return size;
}

uint64_t SdfsDriver::total_bytes() {
  uint64_t size = 0;
  if (is_mount()) {
    DWORD fre_clust;
    char drv[3] = {(char) ('0' + this->pdrv_), ':', 0};
    if (f_getfree(drv, &fre_clust, &this->fs_) != 0)
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

uint64_t SdfsDriver::used_bytes() {
  uint64_t size = 0;
  if (is_mount()) {
    DWORD fre_clust;
    char drv[3] = {(char) ('0' + this->pdrv_), ':', 0};
    if (f_getfree(drv, &fre_clust, &this->fs_) != 0)
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