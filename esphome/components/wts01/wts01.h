#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace wts01 {

class WTS01Sensor : public Component, public uart::UARTDevice {
 public:
  void loop() override;
  void dump_config() override;

  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }

  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  static const uint8_t PACKET_SIZE = 9;
  static const uint8_t HEADER_1 = 0x55;
  static const uint8_t HEADER_2 = 0x01;
  static const uint8_t HEADER_3 = 0x01;
  static const uint8_t HEADER_4 = 0x04;

  uint8_t buffer_[PACKET_SIZE];
  uint8_t buffer_pos_{0};

  sensor::Sensor *temperature_sensor_{nullptr};
  float current_temperature_{NAN};  // Current temperature value from sensor

  void handle_char_(uint8_t c);
  void process_packet_();

 private:
  static constexpr const char *TAG = "wts01";
};

}  // namespace wts01
}  // namespace esphome
