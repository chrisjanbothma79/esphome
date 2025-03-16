#include "mijia_light_bar.h"

#include <cinttypes>
#include <cstdint>
#include <vector>

#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mijia_light_bar {

static const char *const TAG = "mijia_light_bar";

void MijiaLightBarComponent::setup() {
  // Call parent setup first to initialize nRF24
  nrf24::NRF24Device::setup_nrf24();

  if (is_failed()) return;

  ESP_LOGCONFIG(TAG, "Mijia Light Bar initialized");
}

void MijiaLightBarComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Mijia Light Bar:");
  ESP_LOGCONFIG(TAG, "  Remote ID: 0x%08X", remote_id_);
  ESP_LOGCONFIG(TAG, "  Repetitions: %d", repetitions_);
  ESP_LOGCONFIG(TAG, "  Delay: %d ms", delay_ms_);
  nrf24::NRF24Device::dump_config();
}

void MijiaLightBarComponent::create_packet(uint8_t *data, uint8_t size,
                                           uint16_t command, uint8_t value) {
  memcpy(data, MijiaLightBarComponent::preamble,
         sizeof(MijiaLightBarComponent::preamble));
  data[8] = (remote_id_ & 0xFF0000) >> 16;
  data[9] = (remote_id_ & 0x00FF00) >> 8;
  data[10] = remote_id_ & 0x0000FF;
  data[11] = 0xFF;
  data[12] = ++counter_;
  data[13] = command;
  data[14] = value;

  if (counter_ > 255) counter_ = 0;

  // Calculate CRC16 using ESPHome's helper
  uint16_t crc = crc16be(data, size - 2, 0xFFFF, 0x1021, false, false);
  data[15] = (crc & 0xFF00) >> 8;
  data[16] = crc & 0x00FF;
}

void MijiaLightBarComponent::send_command(uint16_t command, uint8_t value) {
  uint8_t packet[17] = {0};
  create_packet(packet, sizeof(packet), command, value);

  ESP_LOGD(TAG, "Sending command 0x%04X with value %d", command, value);

  for (int i = 0; i < repetitions_; ++i) {
    nrf24::NRF24Device::write(&packet, sizeof(packet));
    delay(delay_ms_);
  }
}

void MijiaLightBarComponent::write_state(light::LightState *state) {
  float brightness;
  float color_temp;
  bool is_on;
  state->current_values_as_ct(&color_temp, &brightness);
  state->current_values_as_binary(&is_on);

  if (is_on != last_state_.state) {
    // State changed, send toggle command
    send_command(CMD_TOGGLE);
    last_state_.state = is_on;

    if (!is_on) {
      // If turning off, don't send other commands
      return;
    }
  }

  if (is_on) {
    // Convert brightness from 0.0-1.0 to device levels 1-15
    uint8_t brightness_level = brightness_to_level(brightness);
    if (brightness_level != last_state_.brightness) {
      if (brightness_level > last_state_.brightness) {
        send_command(CMD_BRIGHTER, brightness_level - last_state_.brightness);
      } else {
        send_command(CMD_DIMMER, last_state_.brightness - brightness_level);
      }
      last_state_.brightness = brightness_level;
    }

    // Convert color temperature from mireds to device levels 1-15
    uint8_t color_temp_level =
        color_temp_to_level(color_temp, get_traits().get_min_mireds(),
                            get_traits().get_max_mireds());

    if (color_temp_level != last_state_.color_temp) {
      if (color_temp_level > last_state_.color_temp) {
        send_command(CMD_WARMER, color_temp_level - last_state_.color_temp);
      } else {
        send_command(CMD_COOLER, last_state_.color_temp - color_temp_level);
      }
      last_state_.color_temp = color_temp_level;
    }
  }
}

void MijiaLightBarComponent::toggle() {
  ESP_LOGD(TAG, "Toggling");
  send_command(CMD_TOGGLE);
}

void MijiaLightBarComponent::set_brightness(uint8_t brightness) {
  ESP_LOGD(TAG, "Setting brightness: %d", brightness);
  send_command(CMD_BRIGHTER, brightness);
}

void MijiaLightBarComponent::set_color_temp(uint16_t color_temp) {
  ESP_LOGD(TAG, "Setting color temperature: %d", color_temp);
  send_command(CMD_WARMER, static_cast<uint8_t>(color_temp));
}

}  // namespace mijia_light_bar
}  // namespace esphome
