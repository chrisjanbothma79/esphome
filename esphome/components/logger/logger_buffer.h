#pragma once

#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"

#ifdef USE_ESPHOME_LOG_BUFFER

#include <cstddef>
#include <cstring>
#include <memory>
#include <atomic>
#include <freertos/FreeRTOS.h>
#include <freertos/ringbuf.h>

namespace esphome {
namespace logger {

// Size for log message text (power of 2 for efficiency)
// Note: We don't need to add a null terminator since we track the length explicitly
constexpr size_t LOG_MSG_SIZE = 128;
// Size for the text area including temporary null terminator
constexpr size_t LOG_MSG_SIZE_WITH_NULL = LOG_MSG_SIZE + 1;
// Buffer size that includes space for LogMessage header, text content, and temporary null terminator
// This is calculated after the LogMessage struct is defined

class LogBuffer {
 public:
  // Structure for a log message header (text data follows immediately after)
  struct LogMessage {
    const char *tag;          // We store the pointer, assuming tags are static
    const char *thread_name;  // Thread name pointer (or nullptr for main thread)
    uint16_t text_length;     // Length of the message text (up to ~64KB)
    uint16_t line;            // Source code line number
    uint8_t level;            // Log level (0-7)

    // Methods defined inline within the struct
    inline char *text_data() { return reinterpret_cast<char *>(this) + sizeof(LogMessage); }

    inline const char *text_data() const { return reinterpret_cast<const char *>(this) + sizeof(LogMessage); }

    inline size_t total_size() const { return sizeof(LogMessage) + text_length; }
  };

  // Buffer size that includes space for LogMessage struct, text content, and temporary null terminator
  static constexpr size_t LOG_MSG_BUFFER_SIZE = sizeof(LogMessage) + LOG_MSG_SIZE_WITH_NULL;

  // Constructor that takes a total buffer size
  explicit LogBuffer(size_t total_buffer_size);
  ~LogBuffer();

  // Send a message to the ring buffer
  // Returns true if the message was successfully sent, false otherwise
  // Thread-safe - can be called from any thread including interrupts
  bool send_message_thread_safe(uint8_t level, const char *tag, uint16_t line, const char *thread_name,
                                const char *format, va_list args);

  // Borrow the next message from the ring buffer along with its text
  // Returns the message metadata and the message text through the out parameters
  // Returns false if the buffer is empty
  // NOT thread-safe - only to be called from the main loop
  // Also returns a token that must be used with release_message_main_loop
  bool borrow_message_main_loop(LogMessage **message, const char **text, void **received_token);

  // Cancel a message without updating counters
  void cancel_message(void *token);

  // Release a message buffer and update the message counter
  // NOT thread-safe - only to be called from the main loop after borrowing a message
  // This updates internal state tracking for has_messages efficiency
  void release_message_main_loop(void *token);

  // For tracking buffer usage - used by logger.cpp to detect if messages need processing
  // Returns true if there are messages in the buffer ready to be processed
  bool has_messages() const {
    // Use atomic counter for better performance than directly querying the buffer
    return message_counter_.load(std::memory_order_relaxed) != last_processed_counter_;
  }

  // These methods are only used internally, removed to simplify API

 private:
  RingbufHandle_t ring_buffer_{nullptr};  // FreeRTOS ring buffer handle

  // Atomic counter for tracking messages - uint16_t is fine as we only care about changes
  std::atomic<uint16_t> message_counter_{0};    // Incremented when a message is committed
  mutable uint16_t last_processed_counter_{0};  // Last processed message counter

  // We no longer need this function since we use LOG_MSG_BUFFER_SIZE directly
};

}  // namespace logger
}  // namespace esphome

#endif  // USE_ESPHOME_LOG_BUFFER
