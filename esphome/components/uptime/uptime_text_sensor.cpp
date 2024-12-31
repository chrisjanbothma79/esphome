#include "uptime_text_sensor.h"

#ifdef USE_TEXT_SENSOR
#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uptime {

static const char *const TAG = "uptime.sensor";

void UptimeTextSensor::setup() { this->last_ms_ = millis(); }

void UptimeTextSensor::update() {
  const auto now = millis();
  const uint32_t delta = (now - this->last_ms_) / 1000;
  if (delta == 0)
    return;
  this->last_ms_ = now - (now % 1000);
  this->uptime_ += delta;
  auto seconds = this->uptime_;
  unsigned days = seconds / (24 * 3600);
  seconds = seconds % (24 * 3600);
  unsigned hours = seconds / 3600;
  seconds = seconds % 3600;
  unsigned minutes = seconds / 60;
  unsigned secs = seconds % 60;
  if (days != 0) {
    this->publish_state(str_sprintf("%dd%dh%dm%ds", days, hours, minutes, secs));
  } else if (hours != 0) {
    this->publish_state(str_sprintf("%dh%dm%ds", hours, minutes, secs));
  } else if (minutes != 0) {
    this->publish_state(str_sprintf("%dm%ds", minutes, secs));
  } else {
    this->publish_state(str_sprintf("%ds", secs));
  }
}

std::string UptimeTextSensor::unique_id() { return get_mac_address() + "-uptime-text"; }
float UptimeTextSensor::get_setup_priority() const { return setup_priority::HARDWARE; }
void UptimeTextSensor::dump_config() { LOG_TEXT_SENSOR("", "Uptime Text Sensor", this); }

}  // namespace uptime
}  // namespace esphome
#endif  // USE_TEXT_SENSOR
