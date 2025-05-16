#pragma once
#include "sdfs.h"
#include "spi_connector.h"
#ifdef USE_ARDUINO_SPI_FS
// #include "esphome/components/spi/spi.h"
#include <SPI.h>
#include <FS.h>
// #include <SD.h>
#include "FSImpl.h"
// #include "sd_defines.h"

namespace esphome {
namespace sdfs {

typedef enum { CARD_NONE, CARD_MMC, CARD_SD, CARD_SDHC, CARD_UNKNOWN } sdcard_type_t;

//  SD - Esample  https://github.com/espressif/arduino-esp32/issues/6237

class ArduinoSdFatDriver : public fs::FS, public DriverInterface {
 public:
  ArduinoSdFatDriver(fs::FSImplPtr);
  //   void set_spi(uint8_t ss, SPIClass *spi, uint32_t frequency=4000000, const char* mountpoint="/sd");
  void set_spi(uint8_t, SPIClass *, uint32_t, const char *);
  void end();
  void set_parent(SdmmcHost *) override;
  void set_connector(SpiConnector *);
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(bool) override;
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
  uint8_t _pdrv;
  SPIClass *spi_;
  int8_t ssPin_;
  uint32_t frequency_;
  const char *mountpoint_;  // base_path
  unsigned long sectors_;
  bool supports_crc_;
  int status_;
  sdcard_type_t type_;
};

using fs::FS;

}  // namespace sdfs
}  // namespace esphome
#endif