#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace activity_led {

class ActivityLED : public Component {
 public:
  explicit ActivityLED(GPIOPin *pin);

  void pre_setup();
  void dump_config() override;
  void loop() override;
  float get_setup_priority() const override;
  float get_loop_priority() const override;

 protected:
  GPIOPin *pin_;
};

extern ActivityLED *global_activity_led;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

}  // namespace activity_led
}  // namespace esphome
