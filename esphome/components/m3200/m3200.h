#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace m3200 {


class M3200 : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  void set_fs_pressure(uint16_t fs_pressure) { fs_pressure_ = fs_pressure; };
  void set_min_pressure_(uint16_t min_pressure) { min_pressure_ = min_pressure; };
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { temperature_sensor_ = temperature_sensor; }
  void set_pressure_sensor(sensor::Sensor *pressure_sensor) { pressure_sensor_ = pressure_sensor; }

 //private:
  //uint8_t get_register_(uint8_t register_to_read, uint16_t *register_value);
  //uint8_t set_register_(uint8_t register_to_set, uint16_t value_to_set);
  //uint8_t crc8_(uint8_t *byte_buffer, uint8_t length_of_crc);

 protected:
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *pressure_sensor_{nullptr};
  uint16_t fs_pressure_;
  float min_pressure_;
  float slope_;
  //float intercept_;

};

}  // namespace m3200
}  // namespace esphome
