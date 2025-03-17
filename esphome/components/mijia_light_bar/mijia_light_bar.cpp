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
  ESP_LOGD(TAG, "Mijia Light Bar initialized");
}

void MijiaLightBarComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Mijia Light Bar:");
  ESP_LOGCONFIG(TAG, "  Remote ID: 0x%08X", remote_id_);
  ESP_LOGCONFIG(TAG, "  Repetitions: %d", repetitions_);
  ESP_LOGCONFIG(TAG, "  Delay: %d ms", delay_ms_);
  nrf24::NRF24Device::dump_config();
}

void MijiaLightBarComponent::create_packet(uint8_t *data, uint8_t size,
                                           uint8_t command, uint8_t value) {
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
  uint16_t crc = crc16be(data, size - 2, 0xFFFE, 0x1021, false, false);
  data[15] = (crc & 0xFF00) >> 8;
  data[16] = crc & 0x00FF;
}

void MijiaLightBarComponent::send_command(uint8_t command, uint8_t value) {
  uint8_t packet[17] = {0};
  create_packet(packet, payload_size_, command, value);

  ESP_LOGD(TAG, "Sending command 0x%02X%02X", command, value);
  ESP_LOGD(TAG, "Packet %s", format_hex_pretty(packet, payload_size_).c_str());

  for (int i = 0; i < repetitions_; ++i) {
    nrf24::NRF24Device::write(&packet, payload_size_);
    delay(delay_ms_);
  }
}

void MijiaLightBarComponent::write_state(light::LightState *state) {
  bool is_on;
  state->current_values_as_binary(&is_on);

  if (is_on != last_state_.state) {
    // State changed, send toggle command
    toggle();
    last_state_.state = is_on;
  }

  if (is_on) {
    float brightness;
    float color_temp;
    state->current_values_as_ct(&color_temp, &brightness);

    // Convert brightness from 0.0-1.0 to device levels 1-15
    uint8_t brightness_level = brightness_to_level(brightness);
    if (brightness_level != last_state_.brightness) {
      set_brightness(brightness_level);
      last_state_.brightness = brightness_level;
    }

    // Convert color temperature from mireds to device levels 1-15
    uint8_t color_temp_level =
        color_temp_to_level(color_temp, get_traits().get_min_mireds(),
                            get_traits().get_max_mireds());

    if (color_temp_level != last_state_.color_temp) {
      set_color_temp(color_temp_level);
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
  send_command(CMD_DIMMER, 0xF0);
  send_command(CMD_BRIGHTER, brightness);
}

void MijiaLightBarComponent::set_color_temp(uint8_t color_temp) {
  ESP_LOGD(TAG, "Setting color temperature: %d", color_temp);
  send_command(CMD_WARMER, 0xF0);
  send_command(CMD_COOLER, color_temp);
}

}  // namespace mijia_light_bar
}  // namespace esphome
