#include "uln2003_pump.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uln2003 {

static const char *const TAG = "uln2003.pump";

void ULN2003Pump::setup() {
  this->control_pin_->setup();
  this->control_pin_->digital_write(false);  // Start OFF
}

void ULN2003Pump::write_state(bool state) {
  this->control_pin_->digital_write(state);
  ESP_LOGD(TAG, "Pump turned %s", state ? "ON" : "OFF");
  this->publish_state(state);
}

void ULN2003Pump::dump_config() {
  ESP_LOGCONFIG(TAG, "ULN2003 Pump Mode:");
  LOG_PIN("  Control Pin: ", this->control_pin_);
}

}  // namespace uln2003
}  // namespace esphome
