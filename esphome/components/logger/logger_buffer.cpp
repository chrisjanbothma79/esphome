#include "logger_buffer.h"

#ifdef USE_ESPHOME_LOG_BUFFER

#include "esphome/core/log.h"

namespace esphome {
namespace logger {

static const char *const TAG = "logger_buffer";

LogBuffer::LogBuffer(size_t total_buffer_size) {
  // Create a no-split buffer for acquire/complete operations
  // The size is guaranteed to be at least 1024 bytes by the config validation
  ring_buffer_ = xRingbufferCreate(total_buffer_size, RINGBUF_TYPE_NOSPLIT);
}

LogBuffer::~LogBuffer() {
  // Delete the ring buffer (frees the memory automatically)
  vRingbufferDelete(ring_buffer_);
  ring_buffer_ = nullptr;
}

char *LogBuffer::prepare_message(uint8_t level, const char *tag, uint16_t line, const char *thread_name,
                                 size_t &capacity, void **message_token) {
  // Calculate maximum size needed for a full message
  size_t max_size = message_size_for(MAX_MESSAGE_TEXT_SIZE);

  // Try to acquire space in the ring buffer for a new message
  void *acquired_item = nullptr;

  // Request space for maximum possible message size to ensure we have enough space
  BaseType_t result = xRingbufferSendAcquire(ring_buffer_, &acquired_item, max_size, 0);
  if (result != pdTRUE || acquired_item == nullptr) {
    // Failed to acquire space in the ring buffer
    capacity = 0;
    *message_token = nullptr;
    return nullptr;
  }

  // We successfully acquired space for our message - use full max size since NOSPLIT
  // ring buffer will allocate the entire requested size
  size_t item_size = max_size;

  // We have successfully acquired space in the ring buffer
  // Set up the message header at the start of the acquired space
  LogMessage *msg = static_cast<LogMessage *>(acquired_item);
  msg->level = level;
  msg->tag = tag;
  msg->line = line;
  msg->thread_name = thread_name;
  msg->text_length = 0;  // Will be filled in commit

  // Calculate available capacity for text
  capacity = item_size - sizeof(LogMessage) - 1;  // -1 for null terminator

  // Cap capacity to a reasonable maximum
  if (capacity > MAX_MESSAGE_TEXT_SIZE) {
    capacity = MAX_MESSAGE_TEXT_SIZE;
  }

  // Store the acquired item pointer in the token for later use in commit
  *message_token = acquired_item;

  // Return a pointer to where the text should be written
  return msg->text_data();
}

void LogBuffer::commit_message(size_t text_length, void *message_token) {
  // Check if we have a valid message token to commit
  if (message_token == nullptr || text_length == 0) {
    // Nothing to commit or zero text length, cancel the preparation
    if (message_token != nullptr) {
      cancel_message(message_token);
    }
    return;
  }

  // Get the message header from the token
  LogMessage *msg = static_cast<LogMessage *>(message_token);

  // Set the text length in the message header
  msg->text_length = text_length;

  // Add null terminator
  msg->text_data()[text_length] = '\0';

  // Commit the message to the ring buffer
  xRingbufferSendComplete(ring_buffer_, message_token);

  // Increment the message counter to notify the logger task
  message_counter_.fetch_add(1, std::memory_order_relaxed);

  // Logging complete
}

bool LogBuffer::borrow_message_main_loop(LogMessage **message, const char **text, void **received_token) {
  // Check for valid output parameters
  if (message == nullptr || text == nullptr || received_token == nullptr) {
    return false;
  }

  // Try to receive an item from the ring buffer - no timeout to avoid blocking
  size_t item_size = 0;
  void *received_item = xRingbufferReceive(ring_buffer_, &item_size, 0);
  // xRingbufferReceive returns NULL if no items are available, otherwise returns a pointer to the received item

  if (received_item == nullptr) {
    return false;
  }

  if (item_size < sizeof(LogMessage)) {
    // Item too small to be valid
    vRingbufferReturnItem(ring_buffer_, received_item);
    return false;
  }

  // Cast to LogMessage
  LogMessage *msg = static_cast<LogMessage *>(received_item);

  // Skip validation of total size since we're using fixed allocation with NOSPLIT buffer
  // This avoids potential issues with how the message size is calculated

  // Just check that text_length is reasonable
  if (msg->text_length > MAX_MESSAGE_TEXT_SIZE) {
    // Text length exceeds expected range
    // At this point, received_item is guaranteed to be non-null from earlier checks
    vRingbufferReturnItem(ring_buffer_, received_item);
    return false;
  }

  // Set the output parameters
  *message = msg;
  *text = msg->text_data();
  *received_token = received_item;

  return true;
}

void LogBuffer::cancel_message(void *token) {
  // Check if there's a valid token to cancel
  if (token != nullptr) {
    // Return the item to the ring buffer without committing
    vRingbufferReturnItem(ring_buffer_, token);
  }
}

void LogBuffer::release_message_main_loop(void *token) {
  // Check if there's a valid token to release
  if (token != nullptr) {
    // Return the item to the ring buffer
    vRingbufferReturnItem(ring_buffer_, token);

    // Update the last processed counter to match the current message counter
    // This marks all messages as processed up to the current point
    last_processed_counter_ = message_counter_.load(std::memory_order_relaxed);
  }
}

}  // namespace logger
}  // namespace esphome

#endif  // USE_ESPHOME_LOG_BUFFER
