#include "api_buffer_test_component.h"
#include "esphome/core/application.h"

namespace esphome {
namespace api_buffer_test_component {

APIBufferTestComponent *global_api_buffer_test_component =
    nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

void APIBufferTestComponent::setup() {
  ESP_LOGD(TAG, "API Buffer Test Component setup");
  this->last_fill_time_ = millis();
  global_api_buffer_test_component = this;

  // For testing, we'll get the API connection through a hack
  // In a real implementation, this would be done properly through the API
  App.scheduler.set_timeout(this, "get_api_connection", 500, [this]() {
    auto *api_server = api::global_api_server;
    if (api_server != nullptr) {
      // This is a hack - in production code, use proper API subscription
      // For testing, we'll assume there's only one connection
      ESP_LOGD(TAG, "Looking for API connection to subscribe to");
    }
  });
}

void APIBufferTestComponent::loop() {
  // Check if API server is ready and has connections
  auto *api_server = api::global_api_server;
  if (api_server == nullptr || !api_server->is_connected()) {
    return;
  }

  // Try to get an API connection if we don't have one
  if (this->api_connection_ == nullptr && !this->tried_subscribe_) {
    this->tried_subscribe_ = true;
    ESP_LOGD(TAG, "API server is connected, buffer test component ready");
    // For testing, we'll work with the fact that send_message is available
    // through the global API server's connection management
  }

  uint32_t now = millis();

  // Auto-fill buffer after delay if configured
  if (this->auto_fill_delay_ > 0 && !this->buffer_filled_ && api_server->is_connected()) {
    if (now - this->last_fill_time_ > this->auto_fill_delay_) {
      ESP_LOGD(TAG, "Auto-filling buffer after %u ms delay", this->auto_fill_delay_);
      // For the test, we'll generate heavy log traffic instead
      this->generate_heavy_traffic();
      this->buffer_filled_ = true;

      // Keep generating traffic for 5 seconds
      this->should_keep_full_ = true;
      this->keep_full_until_ = now + 5000;
    }
  }

  // Keep buffer full if requested
  if (this->should_keep_full_ && now < this->keep_full_until_) {
    // Generate more traffic to keep buffer full
    this->generate_traffic_burst();
  } else if (this->should_keep_full_ && now >= this->keep_full_until_) {
    this->should_keep_full_ = false;
    ESP_LOGD(TAG, "Stopped keeping buffer full");
  }
}

void APIBufferTestComponent::subscribe_api_connection(api::APIConnection *api_connection) {
  if (this->api_connection_ != nullptr) {
    ESP_LOGE(TAG, "Already subscribed to an API connection");
    return;
  }
  this->api_connection_ = api_connection;
  ESP_LOGD(TAG, "Subscribed to API connection");
}

void APIBufferTestComponent::unsubscribe_api_connection(api::APIConnection *api_connection) {
  if (this->api_connection_ != api_connection) {
    return;
  }
  this->api_connection_ = nullptr;
  ESP_LOGD(TAG, "Unsubscribed from API connection");
}

void APIBufferTestComponent::fill_buffer() {
  if (this->api_connection_ == nullptr) {
    ESP_LOGW(TAG, "No API connection available to fill buffer");
    return;
  }

  ESP_LOGD(TAG, "Filling transmit buffer with %zu messages of %zu bytes each", this->fill_count_, this->fill_size_);

  // Create a large text sensor state response to fill the buffer
  api::TextSensorStateResponse resp;
  resp.key = 0x12345678;                            // Dummy key
  resp.state = std::string(this->fill_size_, 'X');  // Large payload
  resp.missing_state = false;

  // Send many messages rapidly to fill the transmit buffer
  size_t sent_count = 0;
  size_t failed_count = 0;

  for (size_t i = 0; i < this->fill_count_; i++) {
    // Modify the string slightly each time
    resp.state[0] = 'A' + (i % 26);

    // Send message directly without batching
    bool sent = this->api_connection_->send_message(resp);

    if (!sent) {
      failed_count++;
      ESP_LOGV(TAG, "Message %zu failed to send - buffer likely full", i);
    } else {
      sent_count++;
    }

    // Log progress
    if (i % 50 == 0) {
      ESP_LOGD(TAG, "Progress: %zu/%zu messages, %zu failed", i, this->fill_count_, failed_count);
    }
  }

  ESP_LOGD(TAG, "Buffer fill complete: %zu sent, %zu failed", sent_count, failed_count);
  this->last_fill_time_ = millis();
}

void APIBufferTestComponent::generate_heavy_traffic() {
  ESP_LOGD(TAG, "Generating heavy traffic to fill transmit buffer");

  // Generate many large log messages rapidly
  // These will be sent over the API if log subscription is active
  std::string large_log(this->fill_size_, 'X');

  for (size_t i = 0; i < this->fill_count_; i++) {
    // Modify the string to ensure each message is unique
    large_log[0] = 'A' + (i % 26);

    // Use VERY_VERBOSE level to ensure it's sent when subscribed
    ESP_LOGVV(TAG, "Buffer fill #%zu: %s", i, large_log.c_str());

    // Progress logging at higher level
    if (i % 50 == 0) {
      ESP_LOGD(TAG, "Traffic generation progress: %zu/%zu", i, this->fill_count_);
    }
  }

  ESP_LOGD(TAG, "Heavy traffic generation complete");
}

void APIBufferTestComponent::generate_traffic_burst() {
  // Generate a burst of medium-sized messages to keep buffer topped up
  std::string medium_log(512, 'K');

  for (int i = 0; i < 5; i++) {
    medium_log[0] = '0' + (i % 10);
    ESP_LOGVV(TAG, "Keep-full burst #%d: %s", i, medium_log.c_str());
  }
}

void APIBufferTestComponent::keep_buffer_full() {
  // Deprecated - use generate_traffic_burst instead
  this->generate_traffic_burst();
}

}  // namespace api_buffer_test_component
}  // namespace esphome