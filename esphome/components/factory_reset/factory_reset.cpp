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
  ESP_LOGCONFIG(TAG, "Factory Reset by Power Cycle:");
  ESP_LOGCONFIG(TAG,
                "  Max interval between power cycles %" PRIu32 " seconds\n"
                "  Current count: %u\n"
                "  Factory reset after %u fast power cycles",
                this->max_interval_ / 1000, count, this->required_count_);
}

void FactoryResetComponent::save_(uint8_t count) {
  this->flash_.save(&count);
  global_preferences->sync();
  this->increment_callback_.call(count, this->required_count_);
}

void FactoryResetComponent::setup() {
  this->flash_ = global_preferences->make_preference<uint8_t>(FAST_BOOT_MAGIC + 1, true);
  uint8_t count = 0;
  if (was_power_cycled()) {
    // this is a power on reset
    this->flash_.load(&count);
    if (count >= this->required_count_) {
      ESP_LOGW(TAG, "Fast boot reset count reached, resetting device");
      global_preferences->reset();
      // delay to allow log to be sent
      delay(100);         // NOLINT
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
