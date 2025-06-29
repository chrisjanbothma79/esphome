#pragma once

#include "esphome/components/climate_ir/climate_ir.h"

namespace esphome {
namespace delonghi_ex105 {

// Values for DELONGHI EX105 IR Controllers
const uint16_t DELONGHI_ADDRESS = 0xFF1F;



// Temperature
const uint16_t DELONGHI_TEMP_MIN = 18;
const uint16_t DELONGHI_TEMP_MAX = 32;          

// Modes
const uint16_t DELONGHI_MODE = 0x3EC1;
const uint16_t DELONGHI_POWER_TOGGLE = 0x7C83;

// Fan Speed
const uint16_t DELONGHI_FAN_AUTO = 0b00;
const uint16_t DELONGHI_FAN_HIGH = 0b01;
const uint16_t DELONGHI_FAN_MEDIUM = 0b10;
const uint16_t DELONGHI_FAN_LOW = 0b11;

//Temp Control
const uint16_t DELONGHI_TEMP_UP = 0x7B84;
const uint16_t DELONGHI_TEMP_DOWN = 0x7F80;

// IR Transmission - similar to NEC1
const uint32_t DELONGHI_IR_FREQUENCY = 38000;
const uint32_t DELONGHI_HEADER_MARK = 9000;
const uint32_t DELONGHI_HEADER_SPACE = 4500;
const uint32_t DELONGHI_BIT_MARK = 465;
const uint32_t DELONGHI_ONE_SPACE = 1750;
const uint32_t DELONGHI_ZERO_SPACE = 670;

// State Frame size
const uint8_t DELONGHI_STATE_FRAME_SIZE = 8;

class DelonghiClimate : public climate_ir::ClimateIR {
 public:
  DelonghiClimate()
      : climate_ir::ClimateIR(DELONGHI_TEMP_MIN, DELONGHI_TEMP_MAX, 1.0f, true, true,
                              {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM,
                               climate::CLIMATE_FAN_HIGH},
                              {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL,
                               climate::CLIMATE_SWING_HORIZONTAL, climate::CLIMATE_SWING_BOTH}) {}

 protected:
  int current_mode_index_{0};
  void control(const climate::ClimateCall &call) override;
  void transmit_state() override;
  void setup();
  uint8_t operation_mode_();
  uint16_t fan_speed_();
  uint8_t temperature_();
  uint16_t pending_command_{ DELONGHI_POWER_TOGGLE };
    climate::ClimateTraits traits() override {
    climate::ClimateTraits t{};
    t.set_supported_modes({
      climate::CLIMATE_MODE_OFF,
      climate::CLIMATE_MODE_DRY,
      climate::CLIMATE_MODE_COOL,
      climate::CLIMATE_MODE_FAN_ONLY  
    });
    t.set_visual_temperature_step(1.0f);
    // (If you support fan, swing, presets, you can set those here too,
    // or leave them empty/false to hide those controls.)
    return t;
};

};
}  // namespace delonghi
}  // namespace esphome
