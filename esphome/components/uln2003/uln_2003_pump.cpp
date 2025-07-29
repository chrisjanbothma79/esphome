#include "uln2003_pump.h"
#include "esphome.h"
#include "uln2003.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uln2003 {

static const char *const TAG = "uln2003.pump";

ULN2003Mode parse_mode(std::string mode_str) {
  if (mode_str == "pump") {
    return ULN2003Mode::PUMP;
  }
  return ULN2003Mode::STEPPER;
}

switch_::Switch *setup_uln2003_switch(const std::map<std::string, esphome::BaseType> &config) {
  auto mode = ULN2003Mode::STEPPER;
  if (config.count("mode")) {
    mode = parse_mode(config.at("mode").as<std::string>());
  }

  if (mode == ULN2003Mode::PUMP) {
    auto *pump = new ULN2003Pump();
    pump->set_control_pin(config.at("control_pin").as<GPIOPin>());
    App.register_component(pump);
    ESP_LOGCONFIG(TAG, "Setting up ULN2003 Pump");
    return pump;
  }

  // Default stepper creation, needs pins setup as before
  auto *stepper = new ULN2003Component();
  // Set pins from config as before (e.g., 4 stepper pins)
  App.register_component(stepper);
  ESP_LOGCONFIG(TAG, "Setting up ULN2003 Stepper");
  return stepper;
}

}  // namespace uln2003
}  // namespace esphome
