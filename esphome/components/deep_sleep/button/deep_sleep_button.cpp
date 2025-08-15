#include "deep_sleep_button.h"
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

static const char *const TAG = "deepsleep.button";

void DeepSleepButton::dump_config() { LOG_BUTTON("", "Deep Sleep Button", this); }
void DeepSleepButton::press_action() { this->parent_->begin_sleep(this->override_); }

}  // namespace deep_sleep
}  // namespace esphome
