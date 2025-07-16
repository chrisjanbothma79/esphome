#include "dsi_backlight.h"
namespace esphome {
namespace mipi_dsi {
static const uint8_t REG_95 = 0x95;
static const uint8_t REG_96 = 0x96;
static const uint8_t REG_PWM = 0x86;

void DsiBacklight::setup() {
  this->write_byte(REG_95, 0x11);
  this->write_byte(REG_95, 0x17);
  this->write_byte(REG_96, 0x00);
  this->set_timeout(100, [this] {
    this->write_byte(REG_96, 0xFF);
    this->setup_completed_ = true;
  });
}
light::LightTraits DsiBacklight::get_traits() {
  auto traits = light::LightTraits();
  traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
  return traits;
}
void DsiBacklight::write_state(light::LightState *state) {
  float bright;
  state->current_values_as_brightness(&bright);
  this->write_byte(REG_PWM, (uint8_t) (bright * 255.0f));
};
}  // namespace mipi_dsi
}  // namespace esphome
