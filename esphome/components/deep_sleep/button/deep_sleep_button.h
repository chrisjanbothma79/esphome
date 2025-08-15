#pragma once

#include "esphome/core/component.h"
#include "esphome/components/button/button.h"
#include "esphome/components/deep_sleep/deep_sleep_component.h"

namespace esphome {
namespace deep_sleep {

class DeepSleepButton : public button::Button, public Component, public Parented<DeepSleepComponent> {
 public:
  void dump_config() override;
  void set_override(bool value) { this->override_ = value; }

 protected:
  void press_action() override;
  bool override_{false};
};

}  // namespace deep_sleep
}  // namespace esphome
