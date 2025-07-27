#ifdef USE_RP2040
#include "logger.h"
#include "esphome/core/log.h"

namespace esphome::logger {

static const char *const TAG = "logger";

void Logger::pre_setup() {
  if (this->baud_rate_ > 0) {
    switch (this->uart_) {
      case UART_SELECTION_UART0:
        this->hw_serial_ = &Serial1;
        Serial1.begin(this->baud_rate_);
        break;
      case UART_SELECTION_UART1:
        this->hw_serial_ = &Serial2;
        Serial2.begin(this->baud_rate_);
        break;
      case UART_SELECTION_USB_CDC:
        this->hw_serial_ = &Serial;
        Serial.begin(this->baud_rate_);
        break;
    }
  }
  global_logger = this;
  ESP_LOGI(TAG, "Log initialized");
}

void HOT Logger::write_msg_(const char *msg, size_t len) {
  // Arduino's println() writes the message followed by "\r\n" (CRLF).
  // Previously, println() would call write(msg) which uses strlen() internally.
  // By using write(buffer, size) directly, we avoid the strlen() call.
  this->hw_serial_->write(reinterpret_cast<const uint8_t *>(msg), len);
  this->hw_serial_->write(reinterpret_cast<const uint8_t *>("\r\n"), 2);
}

const char *const UART_SELECTIONS[] = {"UART0", "UART1", "USB_CDC"};

const char *Logger::get_uart_selection_() { return UART_SELECTIONS[this->uart_]; }

}  // namespace esphome::logger
#endif  // USE_RP2040
