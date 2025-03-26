#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace ads1100 {

class ADS1100Sensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  void update() override;

  void set_gain(uint8_t gain) { this->gain_ = gain; }
  void set_data_rate(uint8_t data_rate) { this->data_rate_ = data_rate; }

 protected:
  uint8_t gain_{1};
  uint8_t data_rate_{128};
};

}  // namespace ads1100
}  // namespace esphome