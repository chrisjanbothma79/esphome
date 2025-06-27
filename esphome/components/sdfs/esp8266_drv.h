#pragma once
#include "esphome/core/defines.h"
#include "sdfs.h"

#if defined(USE_SDSPI_MODE) && defined(USE_ESP8266)

#ifdef SD_CHIP_SELECT_MODE
#define SD_CHIP_SELECT_MODE 2
#endif

#ifndef SPI_DRIVER_SELECT
#define SPI_DRIVER_SELECT 3
#endif

#ifndef USE_BLOCK_DEVICE_INTERFACE
#define USE_BLOCK_DEVICE_INTERFACE 1
#endif

#ifndef SDFAT_FILE_TYPE
#define SDFAT_FILE_TYPE 1
#endif

#ifndef USE_SD_CRC
#define USE_SD_CRC 1
#endif

#include "spi_connector.h"
#include "SpiDriver/SdSpiDriver.h"
#include "SpiDriver/SdSpiBaseClass.h"
// #include "SdCard/SdCardInfo.h"
#include "SdFat.h"
#include "esp8266_cdio.h"
#include "SdCard/SdCardInfo.h"

namespace esphome {
namespace sdfs {

// #undef SD_CARD_ERROR
// #define SD_CARD_ERROR(e, m) case SD_CARD_ERROR_##e: return F(m); break;
// String sd_err2str(uint8_t code) {
//   switch
//   (code) {
//     SD_ERROR_CODE_LIST
//     default: return F("Unknown error");
//   }
// };

#undef SD_CARD_ERROR
#define SD_CARD_ERROR(e, m) \
  case SD_CARD_ERROR_##e: \
    return F(m); \
    break;
String sdcard_err2str(uint8_t code);

class SdSpiImpl;
class esp8266SpiDriver : public DriverInterface {
 public:
  void set_connector(SpiConnector *);
  void set_parent(SdfsHost *) override;
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(std::string, bool) override;
  uint32_t get_last_err() override;
  void unmount() override;
  bool test() override;
  fsys_t *get_fs() override { return vol; };
  bool is_mount() { return this->vol != NULL; };

  card_type_t card_type() override;
  uint64_t card_size() override;
  size_t num_sectors() override;
  size_t sector_size() override;
  uint64_t total_bytes() override;
  uint64_t used_bytes() override;

 protected:
  SpiConnector *connector_ = NULL;
  SdSpiImpl *spi_impl_;
  SdConnType bus_type_;
  uint32_t last_err_ = 0;
  SdfsHost *parent_;
  SdfsSpiCard *sd_card = NULL;
  bool is_card_connected = false;
  FsVolume *vol;
};

}  // namespace sdfs
}  // namespace esphome
#endif