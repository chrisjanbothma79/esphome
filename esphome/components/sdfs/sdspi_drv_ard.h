#pragma once
#include "esphome/core/defines.h"
#include "sdfs.h"
#if defined(USE_ARDUINO)
#include "spi_connector.h"
// #include "esphome/components/spi/spi.h"
// #include <SPI.h>
// #include <FS.h>
// #include <SD.h>
// #include "FSImpl.h"
// #include "sd_defines.h"
extern "C" {
#include "ff.h"
}
#include "sdspi_io.h"

namespace esphome {
namespace sdfs {

#define FREE(ptr) \
  { \
    free(ptr); \
    ptr = NULL; \
  }

#define IS_LAST_ERR(x, y) (((this->last_err_ >> 16) == x) && ((this->last_err_ & 0x0000ffff) == y))

#define IDF_ERR 1    // Errors from framework
#define FS_ERR 2     // Errors from filesysytems
#define LOCAL_ERR 3  // Local errors

#define RC_OK 0x1
#define RC_NO_NMEM 0x2
#define RC_INVALID_ARG 0x4
#define RC_NO_CARD 0x8

#define SET_RC(x, y, str) \
  do { \
    this->last_err_ = (x << 16) | y; \
    ESP_LOGE(TAG, str " (0x%x).", y); \
  } while (0)

//  SD - Esample  https://github.com/espressif/arduino-esp32/issues/6237

class ArduinoSdFatDriver : public DriverInterface {
 public:
  ArduinoSdFatDriver();
  void end();
  void set_parent(SdmmcHost *) override;
  void set_connector(SpiConnector *);
  bool init_host(SdConnType) override;
  bool is_card() override;
  // bool init_card();
  bool attach_card() override;
  bool mount(std::string, bool) override;
  FATFS *mount_sdspi(uint8_t, std::string, bool);
  bool is_mount();
  bool test() override;
  void unmount() override;
  uint32_t get_last_err() override;

  sdcard_type_t cardType();
  uint64_t cardSize();
  size_t numSectors();
  size_t sectorSize();
  uint64_t totalBytes();
  uint64_t usedBytes();
  bool readRAW(uint8_t *buffer, uint32_t sector);
  bool writeRAW(uint8_t *buffer, uint32_t sector);

 protected:
  SpiConnector *connector_;
  FATFS *fs_ = NULL;
  uint8_t pdrv_;
  uint32_t frequency_;
  bool format_if_empty_ = false;
  std::string mountpoint_;  // base_path
  unsigned long sectors_;
  bool supports_crc_;
  sdcard_type_t type_;
  uint32_t last_err_ = 0;
};

// using fs::FS;

}  // namespace sdfs
}  // namespace esphome
#endif