#pragma once
#include "esphome/core/defines.h"
#include "sdfs.h"
#include "sdfs_defines.h"

#ifndef USE_ESP8266

#if defined(USE_SDMMC_MODE) && defined(SOC_SDMMC_HOST_SUPPORTED)
#define _HAS_SDMMC_
#elif defined(USE_SDMMC_MODE) && !defined(SOC_SDMMC_HOST_SUPPORTED)
#error MMC mode does not supported by SoC
#endif

//
//   Arduino
//
#if defined(USE_ARDUINO)
#if defined(USE_SDSPI_MODE)
#include "spi_connector.h"
// #include "sdspi_io.h"
#endif
extern "C" {
#include "ff.h"
}
#if defined(_HAS_SDMMC_)
#include "sdmmc_io.h"
#endif

//
//  ESP-IDF
//
#elif defined(USE_ESP_IDF)
// #include "esp_vfs_fat.h"
#if defined(USE_SDSPI_MODE)
// #include "driver/sdspi_host.h"
#endif
#if defined(_HAS_SDMMC_)
// #include "sdmmc_cmd.h"
// #include "driver/sdmmc_host.h"
// #include "driver/sdmmc_types.h"
#include "sdmmc_io.h"
#endif
// #include "diskio_impl.h"

#else
#error Unknown platform definition.  Use USE_ARDUINO or USE_ESP_IDF
#endif

namespace esphome {
namespace sdfs {

class SdfsDriver : public DriverInterface {
 public:
  SdfsDriver();
  void end();
  void set_parent(SdfsHost *) override;
#if defined(USE_SDSPI_MODE)
  void set_connector(SpiConnector *);
#endif
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(std::string, bool) override;
  bool is_mount();
  bool test() override;
  void unmount() override;

  card_type_t card_type() override;
  uint64_t card_size() override;
  size_t num_sectors() override;
  size_t sector_size() override;
  uint64_t total_bytes() override;
  uint64_t used_bytes() override;

  fsys_t *get_fs() override { return fs_; };
  uint32_t get_last_err() override { return this->last_err_; };

 protected:
#if defined(USE_SDSPI_MODE)
  SpiConnector *connector_ = {NULL};
#else
  SdmmcIO *mmc_io = {NULL};
#endif
  fsys_t *fs_ = NULL;
  uint8_t pdrv_;
  uint32_t frequency_;
  bool format_if_empty_ = false;
  std::string mountpoint_;  // base_path
  unsigned long sectors_;
  bool supports_crc_;
  card_type_t type_;
  uint32_t last_err_ = 0;
};

// using fs::FS;

}  // namespace sdfs
}  // namespace esphome
#endif