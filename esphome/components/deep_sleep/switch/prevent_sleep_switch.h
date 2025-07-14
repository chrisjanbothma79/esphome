#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/deep_sleep/deep_sleep_component.h"
namespace esphome {
namespace deep_sleep {

class PreventSleepSwitch : public switch_::Switch, public Component, public Parented<DeepSleepComponent> {
 public:
  void dump_config() override;

 protected:
  void write_state(bool state) override;
};

}  // namespace deep_sleep
}  // namespace esphome
