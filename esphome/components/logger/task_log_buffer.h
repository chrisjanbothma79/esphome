#pragma once

#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"
#include "logger_common.h"

namespace esphome {
namespace logger {

#ifdef USE_ESPHOME_TASK_LOG_BUFFER

#include <cstddef>
#include <cstring>
#include <memory>
#include <atomic>
#include <freertos/FreeRTOS.h>
#include <freertos/ringbuf.h>

class TaskLogBuffer {
 public:
  // Structure for a log message header (text data follows immediately after)
  struct LogMessage {
    const char *tag;           // We store the pointer, assuming tags are static
    TaskHandle_t task_handle;  // Task handle instead of thread name (0 for main thread)
    uint16_t text_length;      // Length of the message text (up to ~64KB)
    uint16_t line;             // Source code line number
    uint8_t level;             // Log level (0-7)

    // Methods for accessing message contents
    inline char *text_data() { return reinterpret_cast<char *>(this) + sizeof(LogMessage); }

    inline const char *text_data() const { return reinterpret_cast<const char *>(this) + sizeof(LogMessage); }
  };

  // Total buffer size for complete message storage
  static constexpr size_t LOG_MSG_BUFFER_SIZE = sizeof(LogMessage) + LOG_MSG_SIZE_WITH_NULL;

  // Constructor that takes a total buffer size
  explicit TaskLogBuffer(size_t total_buffer_size);
  ~TaskLogBuffer();

  // NOT thread-safe - borrow a message from the ring buffer, only call from main loop
  bool borrow_message_main_loop(LogMessage **message, const char **text, void **received_token);

  // NOT thread-safe - release a message buffer and update the counter, only call from main loop
  void release_message_main_loop(void *token);

  // Thread-safe - send a message to the ring buffer from any thread
  bool send_message_thread_safe(uint8_t level, const char *tag, uint16_t line, TaskHandle_t task_handle,
                                const char *format, va_list args);

  // Check if there are messages ready to be processed using an atomic counter for performance
  inline bool HOT has_messages() const {
    return message_counter_.load(std::memory_order_relaxed) != last_processed_counter_;
  }

 private:
  RingbufHandle_t ring_buffer_{nullptr};  // FreeRTOS ring buffer handle
  StaticRingbuffer_t structure_;          // Static structure for the ring buffer
  uint8_t *storage_{nullptr};             // Pointer to allocated memory
  size_t size_{0};                        // Size of allocated memory

  // Atomic counter for message tracking (only differences matter)
  std::atomic<uint16_t> message_counter_{0};    // Incremented when messages are committed
  mutable uint16_t last_processed_counter_{0};  // Tracks last processed message
};

#endif  // USE_ESPHOME_TASK_LOG_BUFFER

}  // namespace logger
}  // namespace esphome
