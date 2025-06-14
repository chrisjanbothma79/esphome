#include "reset_button.h"

namespace esphome {
namespace ld2412 {

void ResetButton::press_action() { this->parent_->factory_reset(); }

}  // namespace ld2412
}  // namespace esphome
