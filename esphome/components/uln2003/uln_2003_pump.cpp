#include "uln2003.h"
#include "uln2003_pump.h"
#include "esphome/core/log.h"

namespace esphome {
namespace uln2003 {

static const char *const TAG = "uln2003.pump";

ULN2003Mode parse_mode(std::string mode_str) {
  if (mode_str == "pump") return ULN2003Mode::PUMP;
  return ULN2003Mode::STEPPER;
}

ULN2003Pump *create_uln2003_pump(const std::map<std::string, esphome::BaseType> &config) {
  auto *pump = new ULN2003Pump();
  pump->set_control_pin(config.at("control_pin").as<GPIOPin *>());
  App.register_component(pump);
  return pump;
}

Component *create_uln2003_component(const std::map<std::string, esphome::BaseType> &config) {
  ULN2003Mode mode = ULN2003Mode::STEPPER;
  if (config.count("mode")) {
    mode = parse_mode(config.at("mode").as<std::string>());
  }

  if (mode == ULN2003Mode::PUMP) {
    ESP_LOGCONFIG("uln2003", "Setting up pump mode.");
    return create_uln2003_pump(config);
  }

  ESP_LOGCONFIG("uln2003", "Setting up stepper mode.");
  return create_uln2003_stepper(config);
}

}  // namespace uln2003
}  // namespace esphome
