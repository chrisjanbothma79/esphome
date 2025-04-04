#include "activity_led.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace activity_led {

static const char *const TAG = "activity_led";

ActivityLED *global_activity_led = nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

ActivityLED::ActivityLED(GPIOPin *pin) : pin_(pin) { global_activity_led = this; }
void ActivityLED::pre_setup() {
  ESP_LOGCONFIG(TAG, "Setting up Activity LED...");
  this->pin_->setup();
  this->pin_->digital_write(false);
}
void ActivityLED::dump_config() {
  ESP_LOGCONFIG(TAG, "Activity LED:");
  LOG_PIN("  Pin: ", this->pin_);
}
void ActivityLED::loop() {
  if ((App.get_app_state() & ACTIVITY_LED_BUSSY) != 0u) {
    this->pin_->digital_write(millis() % 250u < 150u);
  } else if ((App.get_app_state() & ACTIVITY_LED_ACTIVE) != 0u) {
    this->pin_->digital_write(millis() % 1500u < 250u);
  } else {
    this->pin_->digital_write(false);
  }
}
float ActivityLED::get_setup_priority() const { return setup_priority::HARDWARE; }
float ActivityLED::get_loop_priority() const { return 50.0f; }

}  // namespace activity_led
}  // namespace esphome
