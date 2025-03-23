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

class MijiaLightBarComponent : public Component, public nrf24::NRF24Device, public light::LightOutput {
 public:
  // Component methods
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const { return setup_priority::IO; }

  // LightOutput methods
  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::COLOR_TEMPERATURE});
    traits.set_min_mireds(153);  // ~6500K
    traits.set_max_mireds(370);  // ~2700K
    return traits;
  }

  void write_state(light::LightState *state) override;

  // Custom methods
  void mark_nrf24_failed() override { mark_failed(); }

  void set_remote_id(uint32_t id) { remote_id_ = id; }
  void set_repetitions(uint8_t repetitions) { repetitions_ = repetitions; }
  void set_delay_ms(uint8_t delay_ms) { delay_ms_ = delay_ms; }

  // Light control methods
  void toggle();
  void cooler();
  void warmer();
  void brighter();
  void dimmer();
  void reset();
  void set_brightness(uint8_t brightness);
  void set_color_temp(uint8_t color_temp);

 protected:
  void create_packet(uint8_t *data, uint8_t size, uint8_t command, uint8_t value = 0);
  void send_command(uint8_t command, uint8_t value = 0);

  // Convert brightness (0.0-1.0) to device levels (1-15)
  uint8_t brightness_to_level(float brightness) { return static_cast<uint8_t>(brightness * 14.0f) + 1; }

  // Convert color temperature (0.0-1.0) to device levels (1-15)
  uint8_t color_temp_to_level(float color_temp) { return static_cast<uint8_t>((1.0f - color_temp) * 14.0f + 1.0f); }

  uint32_t remote_id_{0};
  uint8_t repetitions_{20};
  uint8_t delay_ms_{10};
  uint8_t counter_{0};

  // Packet structure with named fields
  struct Packet {
    uint8_t preamble[8];   // 0-7: Fixed preamble
    uint8_t remote_id[3];  // 8-10: Remote ID bytes
    uint8_t reserved;      // 11: Reserved (0xFF)
    uint8_t counter;       // 12: Command counter
    uint8_t cmd;           // 13: Command
    uint8_t value;         // 14: Command value
    uint8_t crc[2];        // 15-16: CRC bytes
  };

  // Command queue structure
  struct Command {
    Packet packet;
    uint8_t remaining_repetitions;
    uint32_t last_sent;
  };

  static constexpr size_t MAX_QUEUE_SIZE = 5;
  std::array<Command, MAX_QUEUE_SIZE> command_queue_;
  size_t queue_head_{0};
  size_t queue_tail_{0};
  size_t queue_size_{0};

  // Store last known state
  struct LightBarState {
    bool is_on{false};
    bool has_changes{false};
    uint8_t brightness{8};
    uint8_t color_temp{8};
  };
  LightBarState last_state_;
  LightBarState pending_state_;
  static constexpr byte preamble[8] = {0x53, 0x39, 0x14, 0xDD, 0x1C, 0x49, 0x34, 0x12};

  // Queue management methods
  bool queue_command(uint8_t cmd, uint8_t value = 0);
  bool process_next_command();
  bool is_queue_full() const { return queue_size_ >= MAX_QUEUE_SIZE; }
  bool is_queue_empty() const { return queue_size_ == 0; }
  void clear_queue() {
    queue_head_ = 0;
    queue_tail_ = 0;
    queue_size_ = 0;
  }

  // Packet creation methods
  void init_packet(Packet &packet, uint8_t command, uint8_t value, uint8_t counter);
  uint16_t calculate_crc(const uint8_t *data, size_t length);
};
}  // namespace mijia_light_bar
}  // namespace esphome
