#pragma once

#include "esphome/core/component.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace factory_reset {

/// FastBootComponent provides a safe way to recover from repeated boot failures
class FactoryResetComponent : public Component {
 public:
  FactoryResetComponent(uint8_t required_count, uint32_t max_interval)
      : required_count_(required_count), max_interval_(max_interval) {}

  void dump_config() override;
  void setup() override;

 protected:
  ~FactoryResetComponent() = default;
  void save_(uint8_t count);
  ESPPreferenceObject rtc_{};    // used to distinguish between power cycle and other reboots
  ESPPreferenceObject flash_{};  // saves the number of fast power cycles
  uint32_t max_interval_;        // max interval between power cycles
  uint8_t required_count_;       // The number of boot attempts before fast boot is enabled
};

}  // namespace factory_reset
}  // namespace esphome
