#include "light_out_control_select.h"

namespace esphome::ld2412 {

void LightOutControlSelect::control(const std::string &value) {
  this->publish_state(value);
  this->parent_->set_light_out_control();
}

}  // namespace esphome::ld2412
