#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace gpio {

// Store class for ISR data (no vtables, ISR-safe)
class GPIOBinarySensorStore {
 public:
  void setup(InternalGPIOPin *pin, gpio::InterruptType type);
  void detach();

  static void gpio_intr(GPIOBinarySensorStore *arg);

  bool get_state() const {
    InterruptLock lock;
    return this->state_;
  }

  bool has_changed() {
    InterruptLock lock;
    bool changed = this->changed_;
    this->changed_ = false;
    return changed;
  }

 protected:
  InternalGPIOPin *pin_{nullptr};
  ISRInternalGPIOPin isr_pin_;
  volatile bool state_{false};
  volatile bool last_state_{false};
  volatile bool changed_{false};
};

class GPIOBinarySensor : public binary_sensor::BinarySensor, public Component {
 public:
  ~GPIOBinarySensor() override;

  void set_pin(GPIOPin *pin) { pin_ = pin; }
  void set_use_interrupt(bool use_interrupt) { use_interrupt_ = use_interrupt; }
  void set_interrupt_type(gpio::InterruptType type) { interrupt_type_ = type; }
  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// Setup pin
  void setup() override;
  void dump_config() override;
  /// Hardware priority
  float get_setup_priority() const override;
  /// Check sensor
  void loop() override;

 protected:
  GPIOPin *pin_;
  bool use_interrupt_{true};
  gpio::InterruptType interrupt_type_{gpio::INTERRUPT_ANY_EDGE};
  GPIOBinarySensorStore store_;
};

}  // namespace gpio
}  // namespace esphome
