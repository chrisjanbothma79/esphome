#include "esp_ldo.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace esp_ldo {

static const char *const TAG = "esp_ldo";
void EspLdo::setup() {
  esp_ldo_channel_config_t config{};
  config.chan_id = this->channel_;
  config.voltage_mv = this->millivolts_;
  config.flags.adjustable = this->adjustable_;
  auto err = esp_ldo_acquire_channel(&config, &this->handle_);
  if (err != ESP_OK) {
    auto msg = str_sprintf("Failed to acquire LDO channel %d with voltage %d mV", this->channel_, this->millivolts_);
    this->mark_failed(msg.c_str());
  } else {
    ESP_LOGD(TAG, "Acquired LDO channel %d with voltage %d mV", this->channel_, this->millivolts_);
  }
}
void EspLdo::dump_config() {
  ESP_LOGCONFIG(TAG, "ESP LDO Channel %d:", this->channel_);
  ESP_LOGCONFIG(TAG, "  Voltage: %d mV", this->millivolts_);
  ESP_LOGCONFIG(TAG, "  Adjustable: %s", this->adjustable_ ? "YES" : "NO");
}

}  // namespace esp_ldo
}  // namespace esphome
