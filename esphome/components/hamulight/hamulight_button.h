#pragma once

#include "esphome/components/button/button.h"

namespace esphome {
namespace hamulight {

/**
 * @brief A custom ESPHome button entity for Hamulight.
 *
 * This button calls a C++ callback when pressed, and exposes
 * the entity to Home Assistant. Any YAML on_press automations
 * are also triggered by ESPHome after the press_action.
 */
class HamulightButton : public button::Button {
 public:
  void set_callback(std::function<void()> cb) { cb_ = std::move(cb); }
 protected:
  void press_action() override {
    if (cb_) cb_();
  }
  std::function<void()> cb_;
};

}  // namespace hamulight
}  // namespace esphome
