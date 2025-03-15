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
      ESP_LOGD(TAG, "Setting up MijiaLightBar...");
      this->spi_setup();
      // self.radio = pyrf24.RF24()
      // if not self.radio.begin(ce_pin, csn_pin):
      //     raise OSError("nRF24L01 hardware is not responding")
      // self.radio.channel = 6  # 6, 15, 43, 68 (or +1) -> 2406 MHz, 2015 MHz, 2043 MHz, 2068 MHz
      // self.radio.pa_level = pyrf24.RF24_PA_LOW
      // self.radio.data_rate = pyrf24.RF24_2MBPS
      // self.radio.set_retries(0, 0)  # no repetitions, done manually in method send
      // self.radio.listen = False
      // self.radio.dynamic_payloads = False
      // self.radio.payload_size = 17
      // self.radio.open_tx_pipe(bytes(5*[0x55]))  # Address, really sync sequence

      this->radio_ = RF24(spi::Utility::get_pin_no(this->ce_), spi::Utility::get_pin_no(this->cs_), this->data_rate_);
      if (this->radio_.begin()) {
        ESP_LOGD(TAG, "RF24 radio ready for initialization");
      }
      else
      {
        ESP_LOGE(TAG, "RF24 initialization failed");
        return;
      }
      this->radio_.setChannel(68);
      this->radio_.setPALevel(rf24_pa_dbm_e::RF24_PA_HIGH);
      this->radio_.setDataRate(rf24_datarate_e::RF24_2MBPS);
      this->radio_.setRetries(15, 15);
      this->radio_.setAutoAck(false);
      this->radio_.setPayloadSize(17);
      this->radio_.disableCRC();
      this->radio_.disableDynamicPayloads();
      uint8_t address[] = {0x55, 0x55, 0x55, 0x55, 0x55};
      this->radio_.openWritingPipe(address);
      this->radio_.stopListening();

      ESP_LOGCONFIG(TAG, "MijiaLightBar started!");
    }

    void MijiaLightBarComponent::dump_config()
    {
      ESP_LOGCONFIG(TAG, "MijiaLightBar");
      LOG_PIN("  CS pin: ", this->cs_);
      LOG_PIN("  CE pin: ", this->ce_);
      ESP_LOGCONFIG(TAG, "  Mode: %d", this->mode_);
      if (this->data_rate_ < 1000000)
      {
        ESP_LOGCONFIG(TAG, "  Data rate: %" PRId32 "kHz", this->data_rate_ / 1000);
      }
      else
      {
        ESP_LOGCONFIG(TAG, "  Data rate: %" PRId32 "MHz", this->data_rate_ / 1000000);
      }
      char buffer[870] = {'\0'};
      uint16_t used_chars = this->radio_.sprintfPrettyDetails(buffer);
      ESP_LOGCONFIG(TAG, "  %s", buffer);
    }

    float MijiaLightBarComponent::get_setup_priority() const { return setup_priority::DATA; }

    void MijiaLightBarComponent::turn_on()
    {
      ESP_LOGD(TAG, "Turning on MijiaLightBar...");
      this->send_command(0x0100);
    }

    void MijiaLightBarComponent::turn_off()
    {
      ESP_LOGD(TAG, "Turning off MijiaLightBar...");
      this->send_command(0x0100);
    }

    // CRC16 implementation based on the provided configuration
    uint16_t MijiaLightBarComponent::calculateCRC16(const std::vector<uint8_t> &data)
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

    std::vector<uint8_t> MijiaLightBarComponent::packet(uint32_t id, uint16_t command, uint8_t counter)
    {
      std::vector<uint8_t> data;

      // preamble (8 bytes)
      uint64_t preamble = 0x533914DD1C493412;
      for (int i = 7; i >= 0; --i)
      {
        data.push_back(static_cast<uint8_t>((preamble >> (i * 8)) & 0xFF));
      }

      // remote id (3 bytes)
      for (int i = 2; i >= 0; --i)
      {
        data.push_back(static_cast<uint8_t>((id >> (i * 8)) & 0xFF));
      }

      // separator (1 byte)
      uint8_t separator = 0xFF;
      data.push_back(separator);

      // sequence counter (1 byte)
      data.push_back(counter);

      // command id (2 bytes)
      for (int i = 1; i >= 0; --i)
      {
        data.push_back(static_cast<uint8_t>((command >> (i * 8)) & 0xFF));
      }

      // CRC16 (2 bytes)
      uint16_t crc = calculateCRC16(data);
      for (int i = 1; i >= 0; --i)
      {
        data.push_back(static_cast<uint8_t>((crc >> (i * 8)) & 0xFF));
      }

      return data;
    }

    void MijiaLightBarComponent::send_command(uint16_t command)
    {
      this->counter_++;
      if (this->counter_ > 255)
      {
        this->counter_ = 0;
      }
      ESP_LOGD(TAG, "Sending command: 0x%04X", command);
      std::vector<uint8_t> data = packet(this->id_, command, this->counter_);
      ESP_LOGD(TAG, "Packet data: ");
      std::string data_str = "";
      for (const auto &byte : data)
      {
        char buffer[4];
        snprintf(buffer, sizeof(buffer), "%02X ", byte);
        data_str += buffer;
      }
      ESP_LOGD(TAG, "%s", data_str.c_str());
      for (int i = 0; i < this->repetitions_; ++i)
      {
        this->radio_.write(data.data(), data.size(), true);
        delay(this->delay_ms_);
      }
    }

  } // namespace mijia_light_bar
} // namespace esphome
