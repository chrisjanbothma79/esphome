#include "factory_reset.h"

#include "esphome/core/application.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

#include <cinttypes>

#if !defined(USE_RP2040) && !defined(USE_HOST)

namespace esphome {
namespace factory_reset {

static const char *const TAG = "factory_reset";
static const uint32_t POWER_CYCLES_KEY = 0xFA5C0DE;

static bool was_power_cycled() {
#ifdef USE_ESP32
  return esp_reset_reason() == ESP_RST_POWERON;
#endif
#ifdef USE_ESP8266
  auto reset_reason = ESP.getResetReason();
  return strcasecmp(reset_reason.c_str(), "power On") == 0 || strcasecmp(reset_reason.c_str(), "external system") == 0;
#endif
#ifdef USE_LIBRETINY
  return lt_reboot_get_reboot_reason() == REBOOT_REASON_POWER;
#endif
}

static bool was_external_reset() {
#ifdef USE_ESP32
  return esp_reset_reason() == ESP_RST_EXT;
#endif
#ifdef USE_ESP8266
  return strcasecmp(ESP.getResetReason().c_str(), "external system") == 0;
#endif
#ifdef USE_LIBRETINY
  return lt_reboot_get_reboot_reason() == REBOOT_REASON_HARDWARE;
#endif
}

void FactoryResetComponent::dump_config() {
  uint8_t count = 0;
  this->flash_.load(&count);
  ESP_LOGCONFIG(TAG, "Factory Reset by Power Cycle:");
  ESP_LOGCONFIG(TAG,
                "  External resets counted: %s\n"
                "  Max interval between power cycles %" PRIu32 " seconds\n"
                "  Current count: %u\n"
                "  Factory reset after %u fast power cycles",
                YESNO(this->count_external_resets_), this->max_interval_ / 1000, count, this->required_count_);
}

void FactoryResetComponent::save_(uint8_t count) {
  this->flash_.save(&count);
  global_preferences->sync();
  this->increment_callback_.call(count, this->required_count_);
}

void FactoryResetComponent::setup() {
  this->flash_ = global_preferences->make_preference<uint8_t>(POWER_CYCLES_KEY, true);
  uint8_t count = 0;
  this->flash_.load(&count);
  if (was_power_cycled() || (this->count_external_resets_ && was_external_reset())) {
    // this is a power on reset
    count++;
    if (count == this->required_count_) {
      ESP_LOGW(TAG, "Fast boot reset count reached, resetting device");
      global_preferences->reset();
      // delay to allow log to be sent
      delay(100);         // NOLINT
      App.safe_reboot();  // should not return
    }
    this->save_(count);
    ESP_LOGD(TAG, "Power on reset detected, incremented count to %u", count);
  }
  if (count != 0) {
    this->set_timeout(this->max_interval_, [this]() {
      ESP_LOGD(TAG, "No reset in the last %" PRIu32 " seconds, resetting count", this->max_interval_ / 1000);
      this->save_(0);  // reset count
    });
  }
}

}  // namespace factory_reset
}  // namespace esphome

#endif  // !defined(USE_RP2040) && !defined(USE_HOST)
