#include "light_out_control_select.h"

namespace esphome {
namespace ld2412 {

void LightOutControlSelect::control(const std::string &value) {
  this->publish_state(value);
  this->parent_->set_basic_config();
}

}  // namespace ld2412
}  // namespace esphome
