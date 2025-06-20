#pragma once
#include "esphome/core/defines.h"
#include "sdfs.h"
#include "sdfs_defines.h"
#if defined(USE_ARDUINO) && !defined(USE_ESP8266)
#include "spi_connector.h"
// #include "esphome/components/spi/spi.h"
// #include <SPI.h>
// #include <FS.h>
// #include <SD.h>
// #include "FSImpl.h"

extern "C" {
#include "ff.h"
}
#include "sdspi_io.h"
#include "sdmmc_io.h"

namespace esphome {
namespace sdfs {

//  SD - Esample  https://github.com/espressif/arduino-esp32/issues/6237

class SdfsArduinoDriver : public DriverInterface {
 public:
  SdfsArduinoDriver();
  void end();
  void set_parent(SdfsHost *) override;
#if defined(USE_SDSPI_MODE)
  void set_connector(SpiConnector *);
#endif
  bool init_host(SdConnType) override;
  bool is_card() override;
  // bool init_card();
  bool attach_card() override;
  bool mount(std::string, bool) override;
  // FATFS *mount_sdspi(uint8_t, std::string, bool);
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
  fsys_t *get_fs() { return fs_; };

 protected:
#if defined(USE_SDSPI_MODE)
  SpiConnector *connector_ = {NULL};
#else
  SdmmcIO *mmc_connector = {NULL};
#endif
  fsys_t *fs_ = NULL;
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