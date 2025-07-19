#include "factory_reset.h"

#include "esphome/core/application.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

#include <cinttypes>

namespace esphome {
namespace factory_reset {

static const char *const TAG = "factory_reset";
static const uint32_t FAST_BOOT_MAGIC = 0xFA57B007;

void FactoryResetComponent::dump_config() {
  uint8_t count = 0;
  this->flash_.load(&count);
  ESP_LOGCONFIG(TAG, "Factory Reset:");
  ESP_LOGCONFIG(TAG,
                "  Max interval between power cycles %" PRIu32 " seconds\n"
                "  Current count: %u\n"
                "  Factory reset after %u fast power cycles",
                this->max_interval_ / 1000, this->required_count_);
}

void FactoryResetComponent::save_(uint8_t count) {
  this->flash_.save(&count);
  this->rtc_.save(&FAST_BOOT_MAGIC);
  global_preferences->sync();
}

void FactoryResetComponent::setup() {
  this->rtc_ = global_preferences->make_preference<uint16_t>(FAST_BOOT_MAGIC, false);
  this->flash_ = global_preferences->make_preference<uint16_t>(FAST_BOOT_MAGIC + 1, true);
  uint32_t rtc_value = 0;
  uint8_t count = 0;
  if (!this->rtc_.load(&rtc_value) || rtc_value != FAST_BOOT_MAGIC) {
    // this is a power on reset
    this->flash_.load(&count);
    if (count >= this->required_count_) {
      ESP_LOGW(TAG, "Fast boot reset count reached, resetting device");
      delay(100);  // NOLINT
      global_preferences->reset();
      App.safe_reboot();  // should not return
    }
    count++;
    ESP_LOGD(TAG, "Power on reset detected, incremented count to %u", count);
    this->set_timeout(this->max_interval_, [this]() {
      ESP_LOGD(TAG, "No reset in the last %" PRIu32 " seconds, resetting count", this->max_interval_ / 1000);
      this->save_(0);  // reset count
    });
  }
  this->save_(count);
}

}  // namespace factory_reset
}  // namespace esphome
