#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/touchscreen/touchscreen.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace gt911 {

class GT911ButtonListener {
 public:
  virtual void update_button(uint8_t index, bool state) = 0;
};

class GT911Touchscreen : public touchscreen::Touchscreen, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;

  /**
   * @brief Powers down the GT911 touchscreen controller.
   *
   * Detaches the interrupt pin (if set), reconfigures it as a GPIO output,
   * and drives it low as part of the power-down sequence.
   * Then sends the sleep command to the controller via I2C.
   *
   * Logs an error if the sleep command fails to send.
   *
   * @see
   * https://github.com/lewisxhe/SensorLib/blob/ca67841378c9d5a3fb1adbcbb78ceac68be70170/src/TouchDrvGT911.hpp#L128-L131
   */
  void on_powerdown() override;

  void set_interrupt_pin(InternalGPIOPin *pin) { this->interrupt_pin_ = pin; }
  void set_reset_pin(GPIOPin *pin) { this->reset_pin_ = pin; }
  void register_button_listener(GT911ButtonListener *listener) { this->button_listeners_.push_back(listener); }

 protected:
  void update_touches() override;

  /**
   * @brief Sends a command to the GT911 touchscreen controller.
   *
   * Writes single byte comamnd to the I2C register address 0x8040.
   *
   * @param[in] command The command byte to send.
   * @return true if the I2C write operation completed successfully (i2c::ERROR_OK), false otherwise.
   *
   * @see
   * https://github.com/lewisxhe/SensorLib/blob/ca67841378c9d5a3fb1adbcbb78ceac68be70170/src/TouchDrvGT911.hpp#L507-L512
   */
  bool write_command_(uint8_t command);

  InternalGPIOPin *interrupt_pin_{};
  GPIOPin *reset_pin_{};
  std::vector<GT911ButtonListener *> button_listeners_;
  uint8_t button_state_{0xFF};  // last button state. Initial FF guarantees first update.
};

}  // namespace gt911
}  // namespace esphome
