#ifndef nrf24_H
#define nrf24_H

#include "esphome.h"
#include <RF24.h>
#include "esphome/components/spi/spi.h"
#include "esphome/components/spi_device/spi_device.h"

namespace esphome {
namespace nrf24 {

enum class nrf24PALevel { LOW, MEDIUM, HIGH, MAX };

class nrf24 : public spi_device::SPIDevice, public Component {
 public:
  nrf24(GPIOPin *ce_pin) : ce_pin_(ce_pin) {}

  void setup() override;
  void loop() override;

  void set_channel(uint8_t channel) { channel_ = channel; }
  void set_pa_level(nrf24PALevel pa_level) { pa_level_ = pa_level; }
  void set_data_rate(rf24_datarate_e data_rate) { data_rate_ = data_rate; }
  void set_payload_size(uint8_t payload_size) { payload_size_ = payload_size; }
  void set_retries(uint8_t delay, uint8_t count) {
    retry_delay_ = delay;
    retry_count_ = count;
  }

  void set_address(uint64_t address) { address_ = address; }

  GPIOPin *get_ce_pin() const { return ce_pin_; }
  GPIOPin *get_cs_pin() const { return this->spi_device_get_chip_select_pin(); }

 protected:
  virtual void process_received_data(const uint8_t *data, uint8_t length);
  RF24 radio{ce_pin_->get_pin(), this->spi_device_get_chip_select_pin()->get_pin()};
  virtual void before_start_listening(){};  // extensibility hook
 private:
  GPIOPin *ce_pin_;
  uint8_t channel_{76};                        // Default channel
  nrf24PALevel pa_level_{nrf24PALevel::HIGH};  // Default PA level
  rf24_datarate_e data_rate_{RF24_1MBPS};      // Default data rate
  uint8_t payload_size_{32};                   // Default payload size
  uint8_t retry_delay_{15};                    // Default retry delay
  uint8_t retry_count_{15};                    // Default retry count
  uint64_t address_{0x1234567890};             // example address
};

}  // namespace nrf24
}  // namespace esphome

#endif