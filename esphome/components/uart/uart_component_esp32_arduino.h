#pragma once

#ifdef USE_ESP32_FRAMEWORK_ARDUINO

#include <driver/uart.h>
#include <HardwareSerial.h>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include "uart_component.h"

namespace esphome {
namespace uart {

/// Clock source options for ESP32 UART - comprehensive support for all ESP32 variants
enum ESP32UARTClockSource {
  ESP32_UART_CLOCK_SOURCE_DEFAULT = 0,   ///< Default clock source (varies by chip)
  ESP32_UART_CLOCK_SOURCE_REF_TICK = 1,  ///< REF_TICK clock source (1MHz) - ESP32, ESP32-S2
  ESP32_UART_CLOCK_SOURCE_APB = 2,       ///< APB clock source (80MHz) - ESP32, ESP32-S2, ESP32-C3, ESP32-S3
  ESP32_UART_CLOCK_SOURCE_XTAL = 3,  ///< XTAL clock source (40MHz) - ESP32-C2, ESP32-C3, ESP32-C5, ESP32-C6, ESP32-C61,
                                     ///< ESP32-H2, ESP32-S3, ESP32-P4
  ESP32_UART_CLOCK_SOURCE_RTC =
      4,  ///< RTC clock source - ESP32-C2, ESP32-C3, ESP32-C5, ESP32-C6, ESP32-C61, ESP32-H2, ESP32-S3, ESP32-P4
  ESP32_UART_CLOCK_SOURCE_PLL_F40M = 5,  ///< PLL F40M clock source (40MHz) - ESP32-C2
  ESP32_UART_CLOCK_SOURCE_PLL_F48M = 6,  ///< PLL F48M clock source (48MHz) - ESP32-H2
  ESP32_UART_CLOCK_SOURCE_PLL_F80M = 7,  ///< PLL F80M clock source (80MHz) - ESP32-C5, ESP32-C6, ESP32-C61, ESP32-P4
};

class ESP32ArduinoUARTComponent : public UARTComponent, public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::BUS; }

  void write_array(const uint8_t *data, size_t len) override;

  bool peek_byte(uint8_t *data) override;
  bool read_array(uint8_t *data, size_t len) override;

  int available() override;
  void flush() override;

  uint32_t get_config();

  HardwareSerial *get_hw_serial() { return this->hw_serial_; }
  uint8_t get_hw_serial_number() { return this->number_; }

  /// Set the clock source for the UART peripheral
  /// @param clock_source The clock source to use (REF_TICK or APB)
  void set_clock_source(ESP32UARTClockSource clock_source) { this->clock_source_ = clock_source; }

  /// Get the currently configured clock source
  /// @return The configured clock source
  ESP32UARTClockSource get_clock_source() const { return this->clock_source_; }

  /**
   * Load the UART with the current settings.
   * @param dump_config (Optional, default `true`): True for displaying new settings or
   * false to change it quietly
   *
   * Example:
   * ```cpp
   * id(uart1).load_settings();
   * ```
   *
   * This will load the current UART interface with the latest settings (baud_rate, parity, etc).
   */
  void load_settings(bool dump_config) override;
  void load_settings() override { this->load_settings(true); }

 protected:
  void check_logger_conflict() override;

  HardwareSerial *hw_serial_{nullptr};
  uint8_t number_{0};
  ESP32UARTClockSource clock_source_{
      ESP32_UART_CLOCK_SOURCE_DEFAULT};  ///< Default to DEFAULT for backward compatibility
};

}  // namespace uart
}  // namespace esphome

#endif  // USE_ESP32_FRAMEWORK_ARDUINO
