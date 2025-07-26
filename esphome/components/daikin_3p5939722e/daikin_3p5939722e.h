#pragma once

#include "esphome/components/climate_ir/climate_ir.h"

namespace esphome {
namespace daikin_3p5939722e {

// Custom Eco+Sleep preset
const std::string DAIKIN_CUSTOM_PRESET_ECO_SLEEP = "Eco + Sleep";

// Values for Daikin 3P593972-2E IR remote
// Temperature
const uint8_t DAIKIN_TEMP_MIN = 18;  // Celsius
const uint8_t DAIKIN_TEMP_MAX = 32;  // Celsius

// Modes
const uint8_t DAIKIN_MODE_AUTO = 0x08;
const uint8_t DAIKIN_MODE_DRY = 0x28;
const uint8_t DAIKIN_MODE_COOL = 0x38;
const uint8_t DAIKIN_MODE_HEAT = 0x48;
const uint8_t DAIKIN_MODE_FAN = 0x68;
const uint8_t DAIKIN_MODE_OFF = 0x00;
const uint8_t DAIKIN_MODE_ON = 0x01;
const uint8_t DAIKIN_MODE_MASK = 0xF8;

// Special temperature values for some modes
const uint8_t DAIKIN_TEMPERATURE_MODE_FAN = 0x32;
const uint8_t DAIKIN_TEMPERATURE_MODE_DRY = 0xC0;

// Fan Speed
const uint8_t DAIKIN_FAN_1 = 0x30;
const uint8_t DAIKIN_FAN_3 = 0x50;
const uint8_t DAIKIN_FAN_5 = 0x70;
const uint8_t DAIKIN_FAN_AUTO = 0xA0;
const uint8_t DAIKIN_FAN_QUIET = 0xB0;

// Swing mode
const uint8_t DAIKIN_SWING_VERTICAL = 0x0F;
const uint8_t DAIKIN_SWING_OFF = 0x00;

// Powerful and sleep mode
const uint8_t DAIKIN_POWERFUL_ON = 0x01;
const uint8_t DAIKIN_SLEEP_ON = 0x04;
const uint8_t DAIKIN_POWERFUL_SLEEP_OFF = 0x00;

// Eco mode
const uint8_t DAIKIN_ECO_ON = 0x04;
const uint8_t DAIKIN_ECO_OFF = 0x00;

// IR Transmission
const uint32_t DAIKIN_IR_FREQUENCY = 38000;
const uint32_t DAIKIN_HEADER_MARK = 3360;
const uint32_t DAIKIN_HEADER_SPACE = 1760;
const uint32_t DAIKIN_BIT_MARK = 520;
const uint32_t DAIKIN_ONE_SPACE = 1370;
const uint32_t DAIKIN_ZERO_SPACE = 360;
const uint32_t DAIKIN_MESSAGE_SPACE = 32300;

// State Frame size
const uint8_t DAIKIN_STATIC_FRAME_SIZE = 8;
const uint8_t DAIKIN_TIME_FRAME_SIZE = 8;
const uint8_t DAIKIN_STATE_FRAME_SIZE = 19;

// Preset values and mapping
const uint8_t DAIKIN_PRESET_NONE = 0x00;
const uint8_t DAIKIN_PRESET_BOOST = 0x01;
const uint8_t DAIKIN_PRESET_SLEEP = 0x04;
const uint8_t DAIKIN_PRESET_BOOST_SLEEP = 0x05;
const uint8_t DAIKIN_PRESET_ECO = 0x40;
const uint8_t DAIKIN_PRESET_ECO_SLEEP = 0x44;
const uint8_t DAIKIN_PRESETS[5] = {DAIKIN_PRESET_NONE,
                                   DAIKIN_PRESET_BOOST,
                                   DAIKIN_PRESET_SLEEP,
                                   DAIKIN_PRESET_BOOST_SLEEP,
                                   DAIKIN_PRESET_ECO};
const esphome::climate::ClimatePreset CLIMATE_PRESETS[5] = {climate::CLIMATE_PRESET_NONE,
                                                            climate::CLIMATE_PRESET_BOOST,
                                                            climate::CLIMATE_PRESET_SLEEP,
                                                            climate::CLIMATE_PRESET_BOOST,
                                                            climate::CLIMATE_PRESET_ECO};

// Frame header for the IR receiver
const uint8_t DAIKIN_FRAME_HEADER[4] = {0x11, 0xDA, 0x27, 0x00};

class Daikin3p5939722eClimate : public climate_ir::ClimateIR {
 public:
  Daikin3p5939722eClimate()
      : climate_ir::ClimateIR(DAIKIN_TEMP_MIN, DAIKIN_TEMP_MAX, 1.0f, true, true,
                              {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_QUIET, climate::CLIMATE_FAN_LOW,
                               climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH},
                              {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL},
                              {climate::CLIMATE_PRESET_NONE, climate::CLIMATE_PRESET_BOOST, climate::CLIMATE_PRESET_ECO,
                               climate::CLIMATE_PRESET_SLEEP}) {}

 protected:
  // Transmit via IR the state of this climate controller.
  void setup() override;
  void control(const climate::ClimateCall &call) override;
  climate::ClimateTraits traits() override;
  void transmit_state() override;
  uint8_t operating_mode_() const;
  uint8_t fan_speed_() const;
  uint8_t swing_() const;
  uint8_t temperature_() const;
  uint8_t map_esphome_to_daikin_preset_() const;
  void map_daikin_to_esphome_preset_(const uint8_t merged_preset);
  bool on_receive(remote_base::RemoteReceiveData data) override;
  bool parse_state_frame_(const uint8_t frame[]);

};

}  // namespace daikin_3p5939722e
}  // namespace esphome
