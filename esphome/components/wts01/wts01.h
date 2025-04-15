#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace wts01 {

class WTS01Sensor : public sensor::Sensor, public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  float get_temperature() const { return this->current_temperature_; }
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }
  void set_update_interval(uint32_t update_interval) { this->update_interval_ = update_interval; }

 protected:
  static const uint8_t PACKET_SIZE = 9;
  static const uint8_t HEADER_1 = 0x55;
  static const uint8_t HEADER_2 = 0x01;
  static const uint8_t HEADER_3 = 0x01;
  static const uint8_t HEADER_4 = 0x04;

  uint8_t buffer_[PACKET_SIZE];
  uint8_t buffer_pos_{0};
  float current_temperature_{NAN};
  sensor::Sensor *temperature_sensor_{nullptr};

  uint32_t update_interval_{0};
  uint32_t last_update_{0};

  void handle_char_(uint8_t c);
  void process_packet_();
  void publish_state_();

 private:
  static constexpr const char *TAG = "wts01";
};

}  // namespace wts01
}  // namespace esphome
