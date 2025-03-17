#pragma once

#include "esphome/components/light/light_output.h"
#include "esphome/components/light/light_traits.h"
#include "esphome/components/nrf24/nrf24.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace mijia_light_bar {

enum MijiaLightBarCommand {
  CMD_TOGGLE = 0x01,
  CMD_COOLER = 0x02,
  CMD_WARMER = 0x03,
  CMD_BRIGHTER = 0x04,
  CMD_DIMMER = 0x05,
  CMD_RESET = 0x06,
};

class MijiaLightBarComponent : public Component,
                               public nrf24::NRF24Device,
                               public light::LightOutput {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const { return setup_priority::IO; }
  void mark_nrf24_failed() override { mark_failed(); }

  void set_remote_id(uint32_t id) { remote_id_ = id; }
  void set_repetitions(uint8_t repetitions) { repetitions_ = repetitions; }
  void set_delay_ms(uint8_t delay_ms) { delay_ms_ = delay_ms; }

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes(
        {light::ColorMode::BRIGHTNESS, light::ColorMode::COLOR_TEMPERATURE});
    traits.set_min_mireds(153);  // ~6500K
    traits.set_max_mireds(370);  // ~2700K
    return traits;
  }

  void write_state(light::LightState *state) override;

  // Light control methods
  void toggle();
  void cooler();
  void warmer();
  void brighter();
  void dimmer();
  void reset();
  void set_brightness(uint8_t brightness);
  void set_color_temp(uint16_t color_temp);

 protected:
  void create_packet(uint8_t *data, uint8_t size, uint8_t command,
                     uint8_t value = 0);
  void send_command(uint8_t command, uint8_t value = 0);

  // Convert brightness (0.0-1.0) to device levels (1-15)
  uint8_t brightness_to_level(float brightness) {
    return static_cast<uint8_t>(brightness * 14.0f) + 1;
  }

  // Convert color temperature (mireds) to device levels (1-15)
  uint8_t color_temp_to_level(float color_temp, float min_mireds,
                              float max_mireds) {
    return static_cast<uint8_t>(
               ((color_temp - min_mireds) / (max_mireds - min_mireds)) *
               14.0f) +
           1;
  }

  uint32_t remote_id_{0};
  uint8_t repetitions_{3};
  uint8_t delay_ms_{20};
  uint8_t counter_{0};

  // Store last known state (even though device can't report it)
  struct {
    bool state{false};
    uint8_t brightness{15};
    uint8_t color_temp{8};
  } last_state_;

  static constexpr byte preamble[8] = {0x53, 0x39, 0x14, 0xDD,
                                       0x1C, 0x49, 0x34, 0x12};
};

template <typename... Ts>
class ToggleAction : public Action<Ts...> {
 public:
  explicit ToggleAction(MijiaLightBarComponent *parent) : parent_(parent) {}

  TEMPLATABLE_VALUE(uint32_t, transition_length)

  void play(Ts... x) override {
    auto *state = parent_->last_state_;
    if (state != nullptr) {
      state->toggle().perform();
    }
  }

 protected:
  MijiaLightBarComponent *parent_;
};

}  // namespace mijia_light_bar
}  // namespace esphome
