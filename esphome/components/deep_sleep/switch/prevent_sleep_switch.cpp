#include "prevent_sleep_switch.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

#ifdef USE_ESP32
#include <esp_sleep.h>
#endif
#ifdef USE_ESP8266
#include <Esp.h>
#endif

namespace esphome {
namespace deep_sleep {

static const char *const TAG = "prevent_sleep.switch";

void PreventSleepSwitch::dump_config() { LOG_SWITCH("", "Prevent Deep Sleep Switch", this); }
void PreventSleepSwitch::write_state(bool state) {
  // Acknowledge
  this->publish_state(false);
  this->parent_->set_deep_sleep_prevention(state, true);
}

}  // namespace deep_sleep
}  // namespace esphome
