#pragma once

#include "esphome/components/color_temperature/ct_light_output.h"
#include "neewer_ble_output.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

class NeewerCTLightOutput : public color_temperature::CTLightOutput, public NeewerBLEOutput {
 public:
  explicit NeewerCTLightOutput();
  void dump_config() override;

 protected:
  void write_state(light::LightState *state) override;

  void prepare_ct_brightness_msg(float color_temperature, float brightness);
  void prepare_brightness_msg(float brightness);
  void prepare_turn_on_msg(bool on);

  float old_brightness_ = 0.0;
  float old_color_temperature_ = 0.0;
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32