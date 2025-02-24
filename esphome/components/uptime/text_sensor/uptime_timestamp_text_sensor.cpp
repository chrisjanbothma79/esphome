#include "uptime_timestamp_text_sensor.h"

#ifdef USE_TIME

#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uptime {

static const char *const TAG = "uptime.sensor";

void UptimeTimestampTextSensor::setup() {
  this->time_->add_on_time_sync_callback([this]() {
    if (this->has_state_)
      return;  // No need to update the timestamp if it's already set

    auto now = this->time_->now();
    const uint32_t ms = millis();
    if (!now.is_valid())
      return;  // No need to update the timestamp if the time is not valid

    std::string now_string = this->time_->now().strftime("%F %T");

    this->publish_state(now_string);
  });
}

float UptimeTimestampTextSensor::get_setup_priority() const { return setup_priority::HARDWARE; }
void UptimeTimestampTextSensor::dump_config() { LOG_TEXT_SENSOR("", "Uptime Text Sensor", this); }

}  // namespace uptime
}  // namespace esphome

#endif  // USE_TIME
