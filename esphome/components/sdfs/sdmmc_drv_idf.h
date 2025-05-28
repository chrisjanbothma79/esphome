
#pragma once
#include "esphome/core/defines.h"
#ifdef USE_ESP_IDF
#include "sdfs.h"
#include "esphome/core/gpio.h"
#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
// #include "esp_vfs.h"
#include "esp_vfs_fat.h"
// #include "esphome/components/spi_device/spi_device.h"
#include "driver/sdspi_host.h"

#if defined(SOC_SDMMC_HOST_SUPPORTED)
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_types.h"
#endif
#include "diskio_impl.h"

namespace esphome {
namespace sdfs {

// #define FREE(ptr) \
//   { \
//     free(ptr); \
//     ptr = NULL; \
//   }

// #define IS_LAST_ERR(x, y) (((this->last_err_ >> 16) == x) && ((this->last_err_ & 0x0000ffff) == y))

// #define FW_ERR 1  // Errors from framework
// #define FS_ERR 2  // Errors from filesysytems
// #define LC_ERR 3  // Local errors

// #define RC_OK 0x1
// #define RC_NO_NMEM 0x2
// #define RC_INVALID_ARG 0x4
// #define RC_NO_CARD 0x8

// #define SET_RC(x, y, str) \
//   do { \
//     this->last_err_ = (x << 16) | y; \
//     ESP_LOGE(TAG, str " (0x%x).", y); \
//   } while (0)

// struct FilePtr {
//   FILE *FL;
// };

// #define RET_STATUS_OK 0
// #define RET_STATUS_FAIL 1
// #define RET_STATUS_NOTCRITICAL 2

class SdmmcHost;

/******************************************************************************
 *
 * @brief  Driver for serve slot initializing,  card check, mout and unmount fs
 *         in esp_idf framework
 *
 */
class SdmmcIdfDriver : public DriverInterface {
 public:
  void set_parent(SdmmcHost *) override;
#if defined(USE_SDSPI_MODE)
  void set_connector(SpiConnector *);
#endif
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(std::string, bool) override;
  FATFS *mount_sdmmc(uint8_t, std::string, bool);
  FATFS *mount_sdspi(uint8_t, std::string, bool);
  void unmount() override;
  void unmount_sdmmc(uint8_t, std::string);
  void unmount_sdspi(uint8_t, std::string);
  uint32_t get_last_err() override;
  bool test() override;

 protected:
#if defined(USE_SDSPI_MODE)
  SpiConnector *connector_;
#endif
  SdConnType bus_type_;
  BYTE pdrv_ = FF_DRV_NOT_USED;
  FATFS *fs_ = NULL;
  std::string mountpoint_;

  bool sdmmc_allocate();
  // bool sdspi_allocate();

  uint8_t init_sdmmc(sdmmc_host_t *);
  uint8_t init_sdspi();
  sdmmc_host_t *host_config_{nullptr};
  sdmmc_card_t *card_info_{nullptr};

#if defined(SOC_SDMMC_HOST_SUPPORTED)
  sdmmc_slot_config_t *slot_config_{nullptr};
#endif
  esp_vfs_fat_mount_config_t *mount_config_;
  spi_bus_config_t *spi_bus_config_{nullptr};
  sdspi_device_config_t *spi_dev_config_{nullptr};
};

}  // namespace sdfs
}  // namespace esphome
#endif