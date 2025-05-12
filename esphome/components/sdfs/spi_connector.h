#pragma once

#include "sdfs.h"
#ifdef USE_ARDUINO_SPI_FS
#include "esphome/components/spi/spi.h"
#include "SpiDriver/SdSpiDriver.h"
#include "SpiDriver/SdSpiBaseClass.h"
#include "SdCard/SdCard.h"

namespace esphome {
namespace sdfs {

// class SdSpiConfig;
// You can write a driver entirely independent of SPI.h.
// It can be optimized for your board or a different SPI port can be used.
// The driver must be derived from SdSpiBaseClass.
// See: SdFat/src/SpiDriver/SdSpiBaseClass.h
class SpiConnector : public SdSpiBaseClass,
                     public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING,
                                           spi::DATA_RATE_40MHZ> {
 public:
  void activate() override;  // Activate SPI hardware with correct speed and mode.
  void begin();
  void begin(SdSpiConfig) override;  // Initialize the SPI bus.
                                     //   void begin(SdSpiConfig config) override; // Initialize the SPI bus.
  void deactivate() override;        // Deactivate SPI hardware.
  uint8_t receive() override;        // Receive a byte.
  uint8_t receive(uint8_t *buf, size_t count) override;  // Receive multiple bytes.
  void send(uint8_t data) override;                      // Send a byte.
  void send(const uint8_t *buf, size_t count) override;  // Send multiple bytes.
  void setSckSpeed(uint32_t maxSck) override;            // Save SPISettings for new max SCK frequency
  void end() override;
  uint8_t get_errCode();
  uint32_t get_status();
  SdSpiConfig *get_config();

 private:
  void set_last_err(uint8_t);
  int last_err_ = 0;
  SdSpiConfig *config_;
  uint32_t maxSck_ = spi::DATA_RATE_40MHZ;
  SdCard *card_;
};

}  // namespace sdfs
}  // namespace esphome
#endif