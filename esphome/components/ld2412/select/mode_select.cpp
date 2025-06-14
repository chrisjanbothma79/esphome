#include "mode_select.h"

namespace esphome {
namespace ld2412 {

void ModeSelect::control(const std::string &value) {
  this->publish_state(value);
  this->parent_->set_mode(state);
}

}  // namespace ld2412
}  // namespace esphome
