#pragma once
#include "sdfs.h"
#include "spi_connector.h"
#ifdef USE_ARDUINO_SPI_FS
// #include "esphome/components/spi/spi.h"
#include <SPI.h>
// #include <FS.h>
// #include <SD.h>
// #include "FSImpl.h"
// #include "sd_defines.h"
extern "C" {
#include "ff.h"
}

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

typedef enum { CARD_NONE, CARD_MMC, CARD_SD, CARD_SDHC, CARD_UNKNOWN } sdcard_type_t;
typedef enum { ST_NOTINIT, ST_INIT, ST_MOUNT } slot_status_t;

//  SD - Esample  https://github.com/espressif/arduino-esp32/issues/6237

class ArduinoSdFatDriver : public DriverInterface {
 public:
  ArduinoSdFatDriver();
  //   void set_spi(uint8_t ss, SPIClass *spi, uint32_t frequency=4000000, const char* mountpoint="/sd");
  // void set_spi(uint8_t, SPIClass *, uint32_t, const char *);
  void end();
  void set_parent(SdmmcHost *) override;
  void set_connector(SpiConnector *);
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool init_card();
  bool attach_card() override;
  bool mount(std::string, bool) override;
  void unmount() override;
  uint32_t get_last_err() override;

  sdcard_type_t cardType();
  uint64_t cardSize();
  size_t numSectors();
  size_t sectorSize();
  uint64_t totalBytes();
  uint64_t usedBytes();
  bool test() override;
  bool readRAW(uint8_t *buffer, uint32_t sector);
  bool writeRAW(uint8_t *buffer, uint32_t sector);

 protected:
  SpiConnector *connector_;
  FATFS *fs_ = NULL;
  uint8_t pdrv_;
  // SPIClass *spi_;
  // int8_t ssPin_;
  uint32_t frequency_;
  bool format_if_empty_ = false;
  std::string mountpoint_;  // base_path
  unsigned long sectors_;
  bool supports_crc_;
  slot_status_t status_;
  sdcard_type_t type_;
  uint32_t last_err_ = 0;
};

// using fs::FS;

}  // namespace sdfs
}  // namespace esphome
#endif