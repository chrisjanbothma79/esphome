#pragma once
#include "esphome/core/defines.h"
#include "sdfs.h"

#ifdef USE_SDSPI_MODE

#include "esphome/components/spi/spi.h"

namespace esphome {
namespace sdfs {

class SpiConnector : public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING,
                                           spi::DATA_RATE_20MHZ> {
 public:
  SpiConnector();
  virtual void dump_config();
  virtual void begin();
  virtual void end();
  virtual bool is_transaction();
  virtual void beginTransaction();
  virtual void endTransaction();
  virtual void transfer(void *data, uint32_t size);
  virtual uint8_t transfer(uint8_t data);
  virtual uint16_t transfer16(uint16_t data);
  virtual uint32_t transfer32(uint32_t data);

  virtual void transferBytes(const uint8_t *data, uint8_t *out, uint32_t size);
  // virtual void transferBits(uint32_t data, uint32_t * out, uint8_t bits);

  virtual void write(uint8_t data);
  virtual void write16(uint16_t data);
  virtual void write32(uint32_t data);
  virtual void writeBytes(const uint8_t *data, uint32_t size);
  // virtual void writePixels(const void * data, uint32_t size);//ili9341 compatible
  virtual void writePattern(const uint8_t *data, uint8_t size, uint32_t repeat);

 private:
  int trans_level_ = 0;
  void writePattern_(const uint8_t *data, uint8_t size, uint8_t repeat);
  bool in_transaction = false;
};

#if defined(USE_SDSPI_MODE) && defined(USE_ESP8266)

class SdSpiImpl {
 public:
  SdSpiImpl();
  void set_spi(SpiConnector *);
  void begin();
  void end();
  void activate();
  void deactivate();
  // void end() override;
  uint8_t receive();
  uint8_t receive(uint8_t *buf, size_t count);
  void send(uint8_t data);
  void send(const uint8_t *buf, size_t count);
  void setSckSpeed(uint32_t);

 private:
  // SpiConnector *m_spi;
  // SPISettings m_spiSettings;
  SpiConnector *connector_{NULL};
};
#endif

}  // namespace sdfs
}  // namespace esphome
#endif