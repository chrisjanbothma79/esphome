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
  void set_parent(SdmmcHost *) override;
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(std::string, bool) override;
  uint32_t get_last_err() override;
  void unmount() override;
  bool test() override;

 protected:
  SpiConnector *connector_ = NULL;
  SdSpiImpl *spi_impl_;
  SdConnType bus_type_;
  uint32_t last_err_ = 0;
  SdmmcHost *parent_;
  SdfsSpiCard *sd_card = NULL;
  FsVolume *vol;
};

class SdSpiImpl : public SdSpiBaseClass {
 public:
  SdSpiImpl();
  void set_spi(SpiConnector *);
  void begin(SdSpiConfig config) override;
  void activate() override;
  void deactivate() override;
  // void end() override;
  uint8_t receive() override;
  uint8_t receive(uint8_t *buf, size_t count) override;
  void send(uint8_t data) override;
  void send(const uint8_t *buf, size_t count) override;
  void setSckSpeed(uint32_t) override;

 private:
  // SpiConnector *m_spi;
  // SPISettings m_spiSettings;
  SpiConnector *connector_{NULL};
};

}  // namespace sdfs
}  // namespace esphome
#endif