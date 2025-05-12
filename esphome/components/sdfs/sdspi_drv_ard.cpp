
#include "sdspi_drv_ard.h"
namespace esphome {
namespace sdfs {
#ifdef USE_ARDUINO_SPI_FS
void ArduinoSdFatDriver::set_parent(SdmmcHost *p) { this->parent_ = p; }
void ArduinoSdFatDriver::set_connector(SpiConnector *cn) { this->connector_ = cn; }
bool ArduinoSdFatDriver::init_host(SdConnType) { return true; }
bool ArduinoSdFatDriver::is_card() { return true; }
bool ArduinoSdFatDriver::attach_card() { return true; }
bool ArduinoSdFatDriver::mount(bool) { return true; }
void ArduinoSdFatDriver::unmount() {}
uint32_t ArduinoSdFatDriver::get_last_err() { return this->last_err_; }
#endif
}  // namespace sdfs
}  // namespace esphome
