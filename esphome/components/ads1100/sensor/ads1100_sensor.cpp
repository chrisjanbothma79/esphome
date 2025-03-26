#include "ads1100_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ads1100 {

static const char *const TAG = "ads1100.sensor";

void ADS1100Sensor::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ADS1100 Sensor...");
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "ADS1100 parent not set!");
    this->mark_failed();
    return;
  }

  // Propagate settings to parent component
  this->parent_->set_gain(static_cast<ADS1100Gain>(this->gain_));
  this->parent_->set_data_rate(static_cast<ADS1100DataRate>(this->data_rate_));
}

void ADS1100Sensor::dump_config() {
  ESP_LOGCONFIG(TAG, "ADS1100 Sensor:");
  ESP_LOGCONFIG(TAG, "  Gain: %d", this->gain_);
  ESP_LOGCONFIG(TAG, "  Data Rate: %d SPS", this->data_rate_);
  LOG_SENSOR("  ", "Voltage", this);
}

void ADS1100Sensor::update() {
  if (this->parent_ == nullptr) {
    this->status_set_error();
    return;
  }

  float value = this->parent_->request_measurement();
  if (std::isnan(value)) {
    this->status_set_error();
    return;
  }

  this->publish_state(value);
  this->status_clear_error();
}

}  // namespace ads1100
}  // namespace esphome