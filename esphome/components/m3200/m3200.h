#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/gpio.h"
#include <cstdint>

namespace esphome {
namespace m3200 {

class M3200Component : public PollingComponent {
 public:
  M3200Component() : PollingComponent(5000) {}

  float get_setup_priority() const override { return setup_priority::DATA; }

  void setup() override;
  void update() override;
  void dump_config() override;

  void set_sda_pin(GPIOPin *pin) { this->sda_pin_ = pin; }
  void set_scl_pin(GPIOPin *pin) { this->scl_pin_ = pin; }
  void set_pressure_sensor(sensor::Sensor *pressure_sensor) { this->pressure_sensor_ = pressure_sensor; }
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }
  void set_pressure_range(float min_pressure, float max_pressure) {
    this->min_pressure_ = min_pressure;
    this->max_pressure_ = max_pressure;
  }
  void set_address(uint8_t address) { this->address_ = address; }

 protected:
  // Status code constants from the datasheet
  static const uint8_t STATUS_NORMAL = 0x00;
  static const uint8_t STATUS_RESERVED = 0x40;
  static const uint8_t STATUS_STALE = 0x80;
  static const uint8_t STATUS_FAULT = 0xC0;

  // I2C bit-banging methods with M3200-specific behavior
  void i2c_init();
  void i2c_start();
  void i2c_stop();
  bool i2c_write_byte(uint8_t data);
  uint8_t i2c_read_byte(bool ack);
  void sda_low();
  void sda_high();
  void sda_input();
  void sda_output();
  void scl_low();
  void scl_high();
  bool sda_read();
  void delay_us(uint32_t us);

  // Sensor communication methods
  bool read_sensor_data();

  // Pins and sensor references
  GPIOPin *sda_pin_{nullptr};
  GPIOPin *scl_pin_{nullptr};
  sensor::Sensor *pressure_sensor_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};

  // Sensor configuration
  uint8_t address_{0x28};  // Default I2C address
  float min_pressure_{0.0f};
  float max_pressure_{100.0f};
};

}  // namespace m3200
}  // namespace esphome
