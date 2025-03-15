#pragma once

#include "esphome/components/nrf24/nrf24.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"

namespace esphome
{
  namespace mijia_light_bar
  {

    enum MijiaLightBarCommand {
      CMD_TOGGLE = 0x0100,
      CMD_COOLER = 0x0200,
      CMD_WARMER = 0x0300,
      CMD_BRIGHTER = 0x0400,
      CMD_DIMMER = 0x0500,
      CMD_RESET = 0x0600,
    };

    class MijiaLightBarComponent : public nrf24::NRF24Component
    {
    public:
      void setup() override;
      void dump_config() override;

      float get_setup_priority() const override;

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
      void set_color_temp(uint16_t color_temp);

    protected:
      uint16_t calculate_crc16_(const std::vector<uint8_t> &data);
      std::vector<uint8_t> create_packet_(uint16_t command, uint8_t value = 0);
      void send_command_(uint16_t command, uint8_t value = 0);

      uint32_t remote_id_{0};
      uint8_t repetitions_{3};
      uint8_t delay_ms_{20};
      uint8_t counter_{0};
    };

    template <typename... Ts>
    class ToggleAction : public Action<Ts...>
    {
    public:
      explicit ToggleAction(MijiaLightBarComponent *parent) : parent_(parent) {}

      TEMPLATABLE_VALUE(uint32_t, transition_length)

      void play(Ts... x) override
      {
        this->parent_->toggle();
      }

    protected:
      MijiaLightBarComponent *parent_;
    };

  } // namespace mijia_light_bar
} // namespace esphome
