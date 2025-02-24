#pragma once

#include "esphome/core/defines.h"

#ifdef USE_TIME

#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/component.h"
#include "esphome/components/time/real_time_clock.h"

namespace esphome {
namespace uptime {

class UptimeTimestampTextSensor : public text_sensor::TextSensor, public Component {
 public:
  void dump_config() override;
  void setup() override;

  float get_setup_priority() const override;

  void set_time(time::RealTimeClock *time) { this->time_ = time; }

 protected:
  time::RealTimeClock *time_;
};

}  // namespace uptime
}  // namespace esphome

#endif  // USE_TIME
