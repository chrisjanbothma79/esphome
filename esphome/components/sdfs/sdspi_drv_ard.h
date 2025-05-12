#pragma once

#include "sdfs.h"
#include "spi_connector.h"

namespace esphome {
namespace sdfs {
#ifdef USE_ARDUINO_SPI_FS
class ArduinoSdFatDriver : public DriverInterface {
 public:
  void set_parent(SdmmcHost *) override;
  void set_connector(SpiConnector *);
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(bool) override;
  void unmount() override;
  uint32_t get_last_err() override;

 protected:
  SpiConnector *connector_;
};
#endif
}  // namespace sdfs
}  // namespace esphome
