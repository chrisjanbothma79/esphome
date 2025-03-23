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
  if (is_failed()) {
    ESP_LOGE(TAG, "Failed to initialize Mijia Light Bar");
    return;
  }
  this->radio_->disableDynamicPayloads();
  this->radio_->stopListening();
  this->radio_->powerDown();
  ESP_LOGD(TAG, "Mijia Light Bar initialized");
}

void MijiaLightBarComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Mijia Light Bar:");
  ESP_LOGCONFIG(TAG, "  Remote ID: 0x%08X", remote_id_);
  ESP_LOGCONFIG(TAG, "  Repetitions: %d", repetitions_);
  ESP_LOGCONFIG(TAG, "  Delay: %d ms", delay_ms_);
  nrf24::NRF24Device::dump_config();
}

bool MijiaLightBarComponent::queue_command(uint8_t cmd, uint8_t value) {
  if (is_queue_full()) {
    ESP_LOGW(TAG, "Command queue full, dropping command 0x%02X", cmd);
    return false;
  }

  Command &cmd_entry = command_queue_[queue_tail_];
  init_packet(cmd_entry.packet, cmd, value, ++counter_);
  cmd_entry.remaining_repetitions = repetitions_;
  cmd_entry.last_sent = 0;

  queue_tail_ = (queue_tail_ + 1) % MAX_QUEUE_SIZE;
  queue_size_++;
  return true;
}

bool MijiaLightBarComponent::process_next_command() {
  if (is_queue_empty()) {
    return false;
  }

  Command &cmd = command_queue_[queue_head_];
  uint32_t now = millis();

  // Check if it's time to send the next repetition
  if (now - cmd.last_sent >= delay_ms_) {
    if (cmd.remaining_repetitions == repetitions_) {
      this->radio_->powerUp();
    }

    ESP_LOGD(TAG, "Sending command 0x%02X%02X", cmd.packet.cmd, cmd.packet.value);
    ESP_LOGV(TAG, "Packet %s",
             format_hex_pretty(reinterpret_cast<const uint8_t *>(&cmd.packet), sizeof(Packet)).c_str());
    nrf24::NRF24Device::write(reinterpret_cast<const uint8_t *>(&cmd.packet), sizeof(Packet));

    cmd.last_sent = now;
    cmd.remaining_repetitions--;

    if (cmd.remaining_repetitions == 0) {
      // Command completed, remove from queue
      queue_head_ = (queue_head_ + 1) % MAX_QUEUE_SIZE;
      queue_size_--;

      if (queue_size_ == 0) {
        this->radio_->powerDown();
      }
      return true;
    }
  }

  return false;
}

void MijiaLightBarComponent::loop() {
  // Process commands in the queue
  while (process_next_command()) {
    // Process all commands that are ready
  }
}

void MijiaLightBarComponent::write_state(light::LightState *state) {
  bool is_on;
  state->current_values_as_binary(&is_on);

  clear_queue();

  if (is_on != last_state_.is_on) {
    toggle();
    last_state_.is_on = is_on;
  }

  if (is_on) {
    float brightness;
    float color_temp;
    state->current_values_as_ct(&color_temp, &brightness);

    // Convert values to device levels
    uint8_t brightness_level = brightness_to_level(brightness);
    uint8_t color_temp_level = color_temp_to_level(color_temp);

    if (brightness_level != last_state_.brightness) {
      set_brightness(brightness_level);
      last_state_.brightness = brightness_level;
    }

    if (color_temp_level != last_state_.color_temp) {
      set_color_temp(color_temp_level);
      last_state_.color_temp = color_temp_level;
    }
  }
}

void MijiaLightBarComponent::toggle() {
  ESP_LOGD(TAG, "Toggling");
  queue_command(CMD_TOGGLE);
}

void MijiaLightBarComponent::reset() {
  ESP_LOGD(TAG, "Resetting");
  queue_command(CMD_RESET);
}

void MijiaLightBarComponent::cooler() {
  ESP_LOGD(TAG, "Cooler");
  queue_command(CMD_COOLER);
}

void MijiaLightBarComponent::warmer() {
  ESP_LOGD(TAG, "Warmer");
  queue_command(CMD_WARMER);
}

void MijiaLightBarComponent::brighter() {
  ESP_LOGD(TAG, "Brighter");
  queue_command(CMD_BRIGHTER);
}

void MijiaLightBarComponent::dimmer() {
  ESP_LOGD(TAG, "Dimmer");
  queue_command(CMD_DIMMER);
}

void MijiaLightBarComponent::set_brightness(uint8_t brightness) {
  ESP_LOGD(TAG, "Setting brightness: %d", brightness);
  queue_command(CMD_DIMMER, 0xF0);
  queue_command(CMD_BRIGHTER, brightness);
}

void MijiaLightBarComponent::set_color_temp(uint8_t color_temp) {
  ESP_LOGD(TAG, "Setting color temperature: %d", color_temp);
  queue_command(CMD_WARMER, 0xF0);
  queue_command(CMD_COOLER, color_temp);
}

void MijiaLightBarComponent::init_packet(Packet &packet, uint8_t command, uint8_t value, uint8_t counter) {
  // Initialize static parts
  memcpy(packet.preamble, preamble, sizeof(preamble));
  packet.remote_id[0] = (remote_id_ & 0xFF0000) >> 16;
  packet.remote_id[1] = (remote_id_ & 0x00FF00) >> 8;
  packet.remote_id[2] = remote_id_ & 0x0000FF;
  packet.reserved = 0xFF;

  // Set command data
  packet.counter = counter;
  packet.cmd = command;
  packet.value = value;

  // Calculate and set CRC
  uint16_t crc = calculate_crc(reinterpret_cast<const uint8_t *>(&packet), 15);
  packet.crc[0] = (crc & 0xFF00) >> 8;
  packet.crc[1] = crc & 0x00FF;
}

uint16_t MijiaLightBarComponent::calculate_crc(const uint8_t *data, size_t length) {
  return crc16be(data, length, 0xFFFE, 0x1021, false, false);
}

}  // namespace mijia_light_bar
}  // namespace esphome
