
#pragma once
#include "esphome/core/defines.h"
#if defined(USE_ESP_IDF)
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
#include "sdmmc_io.h"
#endif
#include "diskio_impl.h"

namespace esphome {
namespace sdfs {

class SdfsHost;

/******************************************************************************
 *
 * @brief  Driver for serve slot initializing,  card check, mout and unmount fs
 *         in esp_idf framework
 *
 */
class SdfsIdfDriver : public DriverInterface {
 public:
  SdfsIdfDriver();
  void set_parent(SdfsHost *) override;
#if defined(USE_SDSPI_MODE)
  void set_connector(SpiConnector *);
#endif
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(std::string, bool) override;
  // fsys_t *mount_sdmmc(uint8_t, std::string, bool);
  // fsys_t *mount_sdspi(uint8_t, std::string, bool);
  void unmount() override;
  // void unmount_sdmmc(uint8_t, std::string);
  // void unmount_sdspi(uint8_t, std::string);
  uint32_t get_last_err() override;
  bool test() override;
  fsys_t *get_fs() { return fs_; };

 protected:
#if defined(USE_SDSPI_MODE)
  SpiConnector *connector_;
#else
  SdmmcIO *mmc_connector = {NULL};
#endif
  SdConnType bus_type_;
  BYTE pdrv_ = FF_DRV_NOT_USED;
  fsys_t *fs_ = NULL;
  std::string mountpoint_;

  // bool sdmmc_allocate();
  // bool sdspi_allocate();

  uint8_t init_sdmmc();
  uint8_t init_sdspi();
  // sdmmc_host_t *host_config_{nullptr};
  // sdmmc_card_t *card_info_{nullptr};

  // #if defined(SOC_SDMMC_HOST_SUPPORTED)
  //   sdmmc_slot_config_t *slot_config_{nullptr};
  // #endif
  //   esp_vfs_fat_mount_config_t *mount_config_;
  spi_bus_config_t *spi_bus_config_{nullptr};
  sdspi_device_config_t *spi_dev_config_{nullptr};
};

}  // namespace sdfs
}  // namespace esphome
#endif