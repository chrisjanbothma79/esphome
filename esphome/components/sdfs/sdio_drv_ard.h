#pragma once

// #if defined(USE_ARDUINO)
#ifdef USE_ARDUINO_SPI_FS
#define SPI_DRIVER_SELECT 3
#define SD_CHIP_SELECT_MODE 0
#include "sdfs.h"
#include "esphome/components/spi/spi.h"
#include "SdFat.h"
// #include "SpiDriver/SdSpiDriver.h"
#include "SpiDriver/SdSpiBaseClass.h"

namespace esphome {
namespace sdfs {

class SdmmcHost;

class SdArduinoDriver : public SdmmcDriver {
 public:
  SdArduinoDriver(SdmmcHost *);
  void set_connector(EspHomeConnector *);
  bool init_host(SdConnType) override;
  bool is_card() override;
  bool attach_card() override;
  bool mount(bool) override;
  void unmount() override;

 protected:
  bool init_sdspi();
  SdConnType bus_type_;
  SdCard *card_ = NULL;
  EspHomeConnector *connector_;
  SdSpiConfig *arduino_spi_config;
};

// class EspHomeConnector;

// class SdmmcDriver;

// This is a simple driver based on the the standard SPI.h library.
// You can write a driver entirely independent of SPI.h.
// It can be optimized for your board or a different SPI port can be used.
// The driver must be derived from SdSpiBaseClass.
// See: SdFat/src/SpiDriver/SdSpiBaseClass.h
class EspHomeConnector : public SdSpiBaseClass,
                         public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                               spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_40MHZ>

{
 public:
  // EspHomeConnector(){};
  EspHomeConnector();
  // EspHomeConnector(spi::SPIComponent *parent, GPIOPin *cs_pin);
  // spi::SPIClient(BIT_ORDER, Utility::get_mode(CLOCK_POLARITY, CLOCK_PHASE), DATA_RATE) {}
  // EspHomeConnector(spi::SPIComponent* parent, GPIOPin*cs_pin){
  //   this->set_spi_parent(parent);
  //   this->set_cs_pin(cs_pin);
  //   this->set_mode(spi::MODE0);
  // };

  // Activate SPI hardware with correct speed and mode.
  void activate();

  // Initialize the SPI bus.
  void begin(SdSpiConfig config);

  // Deactivate SPI hardware.
  void deactivate();

  // Receive a byte.
  uint8_t receive();

  // Receive multiple bytes.
  // Replace this function if your board has multiple byte receive.
  uint8_t receive(uint8_t *buf, size_t count);

  // Send a byte.
  void send(uint8_t data);
  // Send multiple bytes.
  // Replace this function if your board has multiple byte send.
  void send(const uint8_t *buf, size_t count);

  // Save SPISettings for new max SCK frequency
  void setSckSpeed(uint32_t maxSck) { this->maxSck_ = maxSck; };

 private:
  SPISettings m_spiSettings;
  uint32_t maxSck_ = spi::DATA_RATE_40MHZ;
};
}  // namespace sdfs
}  // namespace esphome
#endif
