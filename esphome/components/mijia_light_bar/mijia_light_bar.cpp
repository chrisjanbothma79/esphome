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
      nrf24::NRF24Component::setup();

      if (this->is_failed())
        return;

      ESP_LOGCONFIG(TAG, "Mijia Light Bar initialized");
    }

    void MijiaLightBarComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "Mijia Light Bar:");
      nrf24::NRF24Component::dump_config();
      ESP_LOGCONFIG(TAG, "  Remote ID: 0x%08X", this->remote_id_);
      ESP_LOGCONFIG(TAG, "  Repetitions: %d", this->repetitions_);
      ESP_LOGCONFIG(TAG, "  Delay: %d ms", this->delay_ms_);
    }

    float MijiaLightBarComponent::get_setup_priority() const { return setup_priority::DATA; }

    uint16_t MijiaLightBarComponent::calculate_crc16_(const std::vector<uint8_t> &data)
    {
      uint16_t crc = 0xFFFE;
      uint16_t polynomial = 0x1021;

      for (uint8_t byte : data)
      {
        crc ^= (static_cast<uint16_t>(byte) << 8);
        for (int i = 0; i < 8; ++i)
        {
          if (crc & 0x8000)
          {
            crc = (crc << 1) ^ polynomial;
          }
          else
          {
            crc <<= 1;
          }
        }
      }
      return crc;
    }

    std::vector<uint8_t> MijiaLightBarComponent::create_packet_(uint16_t command, uint8_t value)
    {
      std::vector<uint8_t> data;

      // Preamble (8 bytes)
      uint64_t preamble = 0x533914DD1C493412;
      for (int i = 7; i >= 0; --i)
      {
        data.push_back(static_cast<uint8_t>((preamble >> (i * 8)) & 0xFF));
      }

      // Remote ID (3 bytes)
      for (int i = 2; i >= 0; --i)
      {
        data.push_back(static_cast<uint8_t>((this->remote_id_ >> (i * 8)) & 0xFF));
      }

      // Separator (1 byte)
      data.push_back(0xFF);

      // Sequence counter (1 byte)
      data.push_back(this->counter_++);
      if (this->counter_ > 255)
        this->counter_ = 0;

      // Command (2 bytes)
      data.push_back(static_cast<uint8_t>((command >> 8) & 0xFF));
      data.push_back(static_cast<uint8_t>(command & 0xFF));

      // Value (if applicable)
      if (value != 0)
      {
        data.push_back(value);
      }

      // CRC16 (2 bytes)
      uint16_t crc = calculate_crc16_(data);
      data.push_back(static_cast<uint8_t>((crc >> 8) & 0xFF));
      data.push_back(static_cast<uint8_t>(crc & 0xFF));

      return data;
    }

    void MijiaLightBarComponent::send_command_(uint16_t command, uint8_t value)
    {
      std::vector<uint8_t> packet = create_packet_(command, value);

      ESP_LOGD(TAG, "Sending command 0x%04X with value %d", command, value);

      for (int i = 0; i < this->repetitions_; ++i)
      {
        this->write(packet.data(), packet.size());
        delay(this->delay_ms_);
      }
    }

    void MijiaLightBarComponent::toggle()
    {
      ESP_LOGD(TAG, "Toggling");
      this->send_command_(CMD_TOGGLE);
    }

    void MijiaLightBarComponent::set_brightness(uint8_t brightness)
    {
      ESP_LOGD(TAG, "Setting brightness: %d", brightness);
      this->send_command_(CMD_BRIGHTER, brightness);
    }

    void MijiaLightBarComponent::set_color_temp(uint16_t color_temp)
    {
      ESP_LOGD(TAG, "Setting color temperature: %d", color_temp);
      this->send_command_(CMD_WARMER, static_cast<uint8_t>(color_temp));
    }

  } // namespace mijia_light_bar
} // namespace esphome
