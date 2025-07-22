#pragma once

#include <memory>

#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"

#define SUB_SENSOR_WITH_DEDUP(name) \
 protected: \
  ld24xx::SensorWithDedup name##_sensor_; \
\
 public: \
  void set_##name##_sensor(sensor::Sensor *sensor) { \
    this->name##_sensor_.sens = sensor; \
    this->name##_sensor_.publish_dedup = std::make_unique<Deduplicator<float>>(); \
  }
#endif

namespace esphome {
namespace ld24xx {

// Used to dedup when engineering mode is off; safe because it is not a valid percentage value
static constexpr float EM_OFF_SENTINEL = -1.0f;

#ifdef USE_SENSOR
// Helper class to store a sensor with a deduplicator & publish state only when the value changes
class SensorWithDedup {
 public:
  void publish_state_if_not_dup(float state, bool use_sentinel = false) {
    if (this->sens != nullptr && this->publish_dedup->next(state)) {
      this->sens->publish_state(use_sentinel && state == EM_OFF_SENTINEL ? NAN : state);
    }
  }

  sensor::Sensor *sens{nullptr};
  std::unique_ptr<Deduplicator<float>> publish_dedup;
};
#endif
}  // namespace ld24xx
}  // namespace esphome
