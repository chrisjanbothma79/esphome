#pragma once

#include "neewer_light_output.h"
#include "esphome/components/color_temperature/ct_light_output.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight {

class NeewerCTLightOutput : public color_temperature::CTLightOutput, public NeewerBLEOutput {
 public:
  explicit NeewerCTLightOutput();
  void dump_config() override;

 protected:
  float old_brightness_ = 0.0;
  float old_color_temperature_ = 0.0;

  const char *const TAG = "neewer_ct_light_output";

  void prepare_ct_brightness_msg(float color_temperature, float brightness);
  void prepare_brightness_msg(float brightness);

  void write_state(light::LightState *state) override;
};

}  // namespace neewerlight
}  // namespace esphome

#endif  // USE_ESP32