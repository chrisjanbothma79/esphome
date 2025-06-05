#pragma once
#include "esphome/core/component.h"
#include "esp_ldo_regulator.h"

namespace esphome {
namespace esp_ldo {

class EspLdo : public Component {
 public:
  EspLdo(int channel) : channel_(channel) {}

  void setup() override;
  void dump_config() override;

  void set_millivolts(int millivolts) { this->millivolts_ = millivolts; }
  void set_adjustable(bool adjustable) { this->adjustable_ = adjustable; }

 protected:
  int channel_;
  int millivolts_{2700};
  bool adjustable_{false};
  esp_ldo_channel_handle_t handle_{};
};

}  // namespace esp_ldo
}  // namespace esphome
