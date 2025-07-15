#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace mipi_dsi {

class DsiBacklight : public light::LightOutput, public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  light::LightTraits get_traits() override;
  void write_state(light::LightState *state) override;
  bool can_proceed() override { return this->setup_completed_; };

 protected:
  bool setup_completed_{false};
};
}  // namespace mipi_dsi
}  // namespace esphome
