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

/****************************************************************
 *
 *             SdfsDriver
 *
 * @brief  Drived forprocession cd card interaction. if can process card oves SPI or MMC interface.
 *         Used on all ESP32  platform variants.
 *         For SPI it use esphome SPI implementation. For MMC  if work throught native (HAL) calls.
 */
class SdfsDriver : public DriverInterface {
 public:
  SdfsDriver();
  void end();
  /**
   * @brief Save pointer to parent (caller) class
   *
   * @param parent
   */
  void set_parent(SdfsHost *parent) override;

#if defined(USE_SDSPI_MODE)
  /**
   * @brief For use with SPI save the link to spi implmentation
   *
   * @param connector
   */
  void set_connector(SpiConnector *connector);
#endif
  /**
   * @brief Initialize sd card connection and all required structures
   *
   * @param type  SDMMC or SDSPI
   * @return true Success
   * @return false  Has error. See get_last_error
   */
  bool init_host(SdConnType type) override;

  /**
   * @brief Check current card status or status changes
   *
   * @return true  card present and mount
   * @return false  anuy other state
   */
  bool is_card() override;

  /**
   * @brief Prform card  reset and initialization
   *
   * @return true
   * @return false
   */
  bool attach_card() override;

  /**
   * @brief  Mount card if present
   *
   * @param path  the mount point
   * @param format  format in no fat fs on the card
   * @return true  mmounted
   * @return false  Has error. See get_last_error
   */
  bool mount(std::string path, bool format) override;

  /**
   * @brief Check is card mount
   *
   * @return true
   * @return false
   */
  bool is_mount();

  /**
   * @brief  Lost cards root directory to debug output& for testing purposes.
   *
   * @return true
   * @return false
   */
  bool test() override;

  /**
   * @brief Unmount FS and clear FAT cache
   *
   */
  void unmount() override;

  /**
   * @brief  Retrun card type
   *
   * @return card_type_t
   */
  card_type_t card_type() override;

  uint64_t card_size() override;
  /**
   * @brief return card capacity in sectors
   *
   * @return size_t
   */
  size_t num_sectors() override;

  /**
   * @brief return one sector size. Usualy 512
   *
   * @return size_t
   */
  size_t sector_size() override;

  /**
   * @brief Return card capacity in bytes
   *
   * @return uint64_t
   */
  uint64_t total_bytes() override;

  /**
   * @brief  Return used space on card in bytes
   *
   * @return uint64_t
   */
  uint64_t used_bytes() override;

  /**
   * @brief Get pointer folesystem driver  for working with files
   *
   * @return fsys_t*
   */
  fsys_t *get_fs() override { return fs_; };

  /**
   * @brief Retrun error ocurred during last operation.
   *
   * @return uint32_t
   */
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