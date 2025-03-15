#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/spi/spi.h"
#include <RF24.h>
#include <vector>

namespace esphome {
namespace nrf24 {

enum NRF24PALevel {
  RF24_PA_MIN = 0,
  RF24_PA_LOW,
  RF24_PA_HIGH,
  RF24_PA_MAX,
};

enum NRF24DataRate {
  RF24_1MBPS = 0,
  RF24_2MBPS,
  RF24_250KBPS,
};

enum NRF24CRCLength {
  RF24_CRC_DISABLED = 0,
  RF24_CRC_8,
  RF24_CRC_16
};

struct PipeConfig {
  uint8_t pipe_num;
  uint64_t address;
};

class NRF24Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::IO; }

  void set_ce_pin(GPIOPin *pin) { ce_pin_ = pin; }
  void set_channel(uint8_t channel) { channel_ = channel; }
  void set_pa_level(NRF24PALevel level) { pa_level_ = level; }
  void set_data_rate(NRF24DataRate rate) { data_rate_ = rate; }
  void set_payload_size(uint8_t size) { payload_size_ = size; }
  void set_crc_length(NRF24CRCLength length) { crc_length_ = length; }
  void set_auto_ack(bool enabled) { auto_ack_ = enabled; }
  void set_retries(uint8_t delay, uint8_t count) {
    retry_delay_ = delay;
    retry_count_ = count;
  }
  void set_write_address(uint64_t address) { write_address_ = address; }
  void add_pipe(uint8_t pipe_num, uint64_t address) {
    pipes_.push_back({pipe_num, address});
  }

  // Methods for derived classes
  bool write(const void* buf, uint8_t len);
  bool read(void* buf, uint8_t len);
  bool available();
  void start_listening();
  void stop_listening();

 protected:
  RF24 *radio_{nullptr};
  GPIOPin *ce_pin_{nullptr};
  uint8_t channel_;
  NRF24PALevel pa_level_;
  NRF24DataRate data_rate_;
  uint8_t payload_size_;
  NRF24CRCLength crc_length_;
  bool auto_ack_;
  uint8_t retry_delay_;
  uint8_t retry_count_;
  uint64_t write_address_;
  std::vector<PipeConfig> pipes_;
};

}  // namespace nrf24
}  // namespace esphome