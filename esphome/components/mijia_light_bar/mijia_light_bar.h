#pragma once

#include "RF24.h"
#include "esphome/components/spi/spi.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome
{
  namespace mijia_light_bar
  {

    class MijiaLightBarComponent
        : public Component,
          public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_HIGH,
                                spi::CLOCK_PHASE_TRAILING, spi::DATA_RATE_1MHZ>
    {
    public:
      void setup() override;
      void dump_config() override;

      float get_setup_priority() const override;

      void set_ce_pin(GPIOPin *ce) { this->ce_ = ce; }
      void set_bar_id(int *id) { this->id_ = *id; }

      void turn_on();
      void turn_off();

    protected:
      RF24 radio_;
      GPIOPin *ce_{nullptr};
      // self.repetitions = 20
      // self.delay_s = 0.01
      // self.counter = 0
      // self.id = remote_id  # Xiaomi remote id, 3-byte int (0x112233)
      int repetitions_ = 20;
      int delay_ms_ = 10;
      int counter_ = 0;
      int id_ = 0xc97e40; // Xiaomi remote id, 3-byte int (0x112233)

      uint16_t calculateCRC16(const std::vector<uint8_t> &data);
      std::vector<uint8_t> packet(uint32_t id, uint16_t command, uint8_t counter);

      void send_command(uint16_t command);
    };

    template <typename... Ts>
    class ToggleAction : public Action<Ts...>
    {
    public:
      explicit ToggleAction(MijiaLightBarComponent *state) : state_(state) {}

      TEMPLATABLE_VALUE(uint32_t, transition_length)

      void play(Ts... x) override
      {
        this->state_->turn_on();
      }

    protected:
      MijiaLightBarComponent *state_;
    };

  } // namespace mijia_light_bar
} // namespace esphome
