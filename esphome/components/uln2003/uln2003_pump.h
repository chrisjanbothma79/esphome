#pragma once

#include "esphome/core/component.h"
#include "esphome/core/gpio.h"

namespace esphome {
namespace uln2003 {

class ULN2003Pump : public Component, {
 public:
  void set_control_pin(GPIOPin *pin) { this->control_pin_ = pin; }

  void setup() override;
  void write_state(bool state) override;

 protected:
  GPIOPin *control_pin_;
};

}  // namespace uln2003
}  // namespace esphome
