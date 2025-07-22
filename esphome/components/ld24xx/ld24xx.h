#pragma once

#include <memory>

#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"

#define SUB_SENSOR_WITH_DEDUP(name, dedup_type) \
 protected: \
  ld24xx::SensorWithDedup<dedup_type> name##_sensor_; \
\
 public: \
  void set_##name##_sensor(sensor::Sensor *sensor) { \
    this->name##_sensor_.sens = sensor; \
    this->name##_sensor_.publish_dedup = std::make_unique<Deduplicator<dedup_type>>(); \
  }
#endif

namespace esphome {
namespace ld24xx {

#ifdef USE_SENSOR
// Helper class to store a sensor with a deduplicator & publish state only when the value changes
template<typename T> class SensorWithDedup {
 public:
  void publish_state_if_not_dup(T state, bool state_unknown = false) {
    if (this->sens != nullptr &&
        ((state_unknown ? false : this->publish_dedup->next(state)) || this->state_unknown_ != state_unknown)) {
      this->sens->publish_state(state_unknown ? NAN : static_cast<float>(state));
      this->state_unknown_ = state_unknown;
    }
  }

  sensor::Sensor *sens{nullptr};
  std::unique_ptr<Deduplicator<T>> publish_dedup;

 protected:
  bool state_unknown_{false};
};
#endif
}  // namespace ld24xx
}  // namespace esphome
