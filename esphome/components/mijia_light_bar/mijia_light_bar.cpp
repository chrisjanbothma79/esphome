#include "mijia_light_bar.h"

#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include <cinttypes>
#include <cstdint>
#include <vector>

namespace esphome
{
  namespace mijia_light_bar
  {

    static const char *const TAG = "mijia_light_bar";

    void MijiaLightBarComponent::setup()
    {
      // Call parent setup first to initialize nRF24
      nrf24::NRF24Device::setup_nrf24();

      if (this->is_failed())
        return;

      ESP_LOGCONFIG(TAG, "Mijia Light Bar initialized");
    }

    void MijiaLightBarComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "Mijia Light Bar:");
      nrf24::NRF24Device::dump_config();
      ESP_LOGCONFIG(TAG, "  Remote ID: 0x%08X", this->remote_id_);
      ESP_LOGCONFIG(TAG, "  Repetitions: %d", this->repetitions_);
      ESP_LOGCONFIG(TAG, "  Delay: %d ms", this->delay_ms_);
    }

    void MijiaLightBarComponent::create_packet(uint8_t* data, uint8_t size, uint16_t command, uint8_t value)
    {
      memcpy(data, MijiaLightBarComponent::preamble, sizeof(MijiaLightBarComponent::preamble));
      data[8] = (this->remote_id_ & 0xFF0000) >> 16;
      data[9] = (this->remote_id_ & 0x00FF00) >> 8;
      data[10] = this->remote_id_ & 0x0000FF;
      data[11] = 0xFF;
      data[12] = ++this->counter_;
      data[13] = command;
      data[14] = value;

      if (this->counter_ > 255)
        this->counter_ = 0;

      // Calculate CRC16 using ESPHome's helper
      uint16_t crc = crc16be(data, size - 2, 0xFFFF, 0x1021, false, false);
      data[15] = (crc & 0xFF00) >> 8;
      data[16] = crc & 0x00FF;
    }

    void MijiaLightBarComponent::send_command(uint16_t command, uint8_t value)
    {
      uint8_t packet[17] = {0};
      create_packet(packet, sizeof(packet), command, value);

      ESP_LOGD(TAG, "Sending command 0x%04X with value %d", command, value);

      for (int i = 0; i < this->repetitions_; ++i)
      {
        nrf24::NRF24Device::write(&packet, sizeof(packet));
        delay(this->delay_ms_);
      }
    }

    void MijiaLightBarComponent::write_state(light::LightState *state)
    {
      float brightness;
      float color_temp;
      bool is_on;
      state->current_values_as_ct(&color_temp, &brightness);
      state->current_values_as_binary(&is_on);

      if (is_on != this->last_state_.state)
      {
        // State changed, send toggle command
        this->send_command(CMD_TOGGLE);
        this->last_state_.state = is_on;

        if (!is_on)
        {
          // If turning off, don't send other commands
          return;
        }
      }

      if (is_on)
      {
        // Convert brightness from 0.0-1.0 to device levels 1-15
        uint8_t brightness_level = brightness_to_level(brightness);
        if (brightness_level != this->last_state_.brightness)
        {
          if (brightness_level > this->last_state_.brightness)
          {
            this->send_command(CMD_BRIGHTER, brightness_level - this->last_state_.brightness);
          }
          else
          {
            this->send_command(CMD_DIMMER, this->last_state_.brightness - brightness_level);
          }
          this->last_state_.brightness = brightness_level;
        }

        // Convert color temperature from mireds to device levels 1-15
        uint8_t color_temp_level = color_temp_to_level(
          color_temp,
          this->get_traits().get_min_mireds(),
          this->get_traits().get_max_mireds()
        );

        if (color_temp_level != this->last_state_.color_temp)
        {
          if (color_temp_level > this->last_state_.color_temp)
          {
            this->send_command(CMD_WARMER, color_temp_level - this->last_state_.color_temp);
          }
          else
          {
            this->send_command(CMD_COOLER, this->last_state_.color_temp - color_temp_level);
          }
          this->last_state_.color_temp = color_temp_level;
        }
      }
    }

    void MijiaLightBarComponent::toggle()
    {
      ESP_LOGD(TAG, "Toggling");
      this->send_command(CMD_TOGGLE);
    }

    void MijiaLightBarComponent::set_brightness(uint8_t brightness)
    {
      ESP_LOGD(TAG, "Setting brightness: %d", brightness);
      this->send_command(CMD_BRIGHTER, brightness);
    }

    void MijiaLightBarComponent::set_color_temp(uint16_t color_temp)
    {
      ESP_LOGD(TAG, "Setting color temperature: %d", color_temp);
      this->send_command(CMD_WARMER, static_cast<uint8_t>(color_temp));
    }

  } // namespace mijia_light_bar
} // namespace esphome
