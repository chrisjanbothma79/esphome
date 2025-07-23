#pragma once

#include <memory>

#ifdef USE_SENSOR
#include "esphome/core/helpers.h"
#include "esphome/components/sensor/sensor.h"

#define SUB_SENSOR_WITH_DEDUP(name, dedup_type) \
 protected: \
  ld24xx::SensorWithDedup<dedup_type> *name##_sensor_{nullptr}; \
\
 public: \
  void set_##name##_sensor(sensor::Sensor *sensor) { \
    this->name##_sensor_ = new ld24xx::SensorWithDedup<dedup_type>(sensor); \
  }
#endif

namespace esphome {
namespace ld24xx {

#ifdef USE_SENSOR
// Helper class to store a sensor with a deduplicator & publish state only when the value changes
template<typename T> class SensorWithDedup {
 public:
  SensorWithDedup(sensor::Sensor *sens = nullptr) : sens(sens) {}

  void publish_state_if_not_dup(T state) {
    if (this->sens != nullptr && (this->publish_dedup.next(state) || this->state_unknown_)) {
      this->sens->publish_state(static_cast<float>(state));
      this->state_unknown_ = false;
    }
  }

  void publish_state_unknown() {
    if (this->sens != nullptr && !this->state_unknown_) {
      this->sens->publish_state(NAN);
      this->state_unknown_ = true;
    }
  }

  sensor::Sensor *sens{nullptr};
  Deduplicator<T> publish_dedup;

 protected:
  bool state_unknown_{false};
};
#endif
}  // namespace ld24xx
}  // namespace esphome
