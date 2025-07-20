#include "emontx.h"
#include "esphome/core/log.h"
#include "esphome/components/json/json_util.h"

namespace esphome {
namespace emontx {

static const char *const TAG = "emontx";

/**
 * @brief Initializes the EmonTx.
 */
void EmonTx::setup() {
  state_ = OFF;

  ESP_LOGCONFIG(TAG, "Setting up EmonTx component");

#ifdef USE_SENSOR
  // Log sensors at setup time
  ESP_LOGCONFIG(TAG, "Currently registered sensors: %u", this->sensors_.size());
  for (const auto &sensor_pair : this->sensors_) {
    ESP_LOGCONFIG(TAG, "  Sensor '%s' registered", sensor_pair.first.c_str());
  }
#else
  ESP_LOGCONFIG(TAG, "Sensor support: DISABLED");
#endif
}

/**
 * @brief Updates the EmonTx state. Resets the buffer index and transitions the state from OFF to ON.
 */
void EmonTx::update() {
  ESP_LOGD(TAG, "Updating EmonTx state...");

  if (state_ == OFF) {
    buffer_.clear();  // Clear the buffer for new data
    state_ = WAITING_FOR_START;
  }

  ESP_LOGD(TAG, "EmonTx is now ready to receive data.");
}

bool EmonTx::read_chars_until_(bool drop, uint8_t c) {
  uint8_t received;
  int j = 0;

  while (available() > 0 && j < 512) {
    j++;
    received = read();

    if (drop && received != c)
      continue;

    // If we're collecting JSON data (not dropping) and receive a newline,
    // consider this invalid and signal to discard the buffer
    if (!drop && (received == '\r' || received == '\n')) {
      ESP_LOGW(TAG, "Newline found within JSON data, discarding buffer");
      buffer_.clear();
      state_ = WAITING_FOR_START;
      return false;
    }

    // Prevent buffer overflow
    if (buffer_.length() > 1024) {
      ESP_LOGW(TAG, "Buffer overflow, clearing buffer");
      buffer_.clear();
      state_ = OFF;
      return false;
    }

    buffer_ += received;

    if (received == c) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Implements the main state machine for processing incoming data.
 *
 * @details The state machine transitions through the following states:
 * - OFF: Does nothing.
 * - ON: Reads characters until the start frame (0x2) is found.
 * - START_FRAME_RECEIVED: Reads characters until the end frame (0x3) is found.
 * - END_FRAME_RECEIVED: Processes the buffer to extract groups, validate CRC, and publish values.
 */
void EmonTx::loop() {
  switch (state_) {
    case OFF:
      // Do nothing, waiting for setup
      break;

    case WAITING_FOR_START:
      if (read_chars_until_(true, '{')) {
        // Start of JSON object detected
        state_ = COLLECTING_JSON;
      }
      // Ignore any other characters
      break;

    case COLLECTING_JSON:
      if (read_chars_until_(false, '}')) {
        state_ = JSON_COLLECTED;
      }
      break;

    case JSON_COLLECTED:
      if (!buffer_.empty()) {
        ESP_LOGI(TAG, "Received data: %s", buffer_.c_str());
        parse_json_(buffer_);
      } else {
        ESP_LOGW(TAG, "Received empty buffer, skipping JSON parsing");
      }
      state_ = OFF;  // Reset state to OFF after processing
      break;
  }
}

void EmonTx::parse_json_(const std::string &data) {
  ESP_LOGV(TAG, "Parsing JSON: %s", data.c_str());
  ESP_LOGV(TAG, "Listener list contains '%d' items", (int) this->emontx_listeners_.size());

  bool success = json::parse_json(data, [this, &data](JsonObject root) {
#ifdef USE_SENSOR
    // Update all registered sensors
    for (auto &sensor_pair : this->sensors_) {
      const std::string &tag = sensor_pair.first;
      sensor::Sensor *sensor = sensor_pair.second;

      if (root[tag].is<JsonVariant>()) {
        float value = root[tag];
        ESP_LOGV(TAG, "Updating sensor '%s' with value: %.2f", tag.c_str(), value);
        sensor->publish_state(value);
      }
    }
#endif

    // Also update all listeners
    ESP_LOGV(TAG, "Listener list contains '%d' items", (int) this->emontx_listeners_.size());
    for (auto *listener : this->emontx_listeners_) {
      if (root[listener->tag].is<JsonVariant>()) {
        const auto value = root[listener->tag].as<std::string>();

        ESP_LOGD(TAG, "  Publish to listener '%s' with value '%s'", listener->tag.c_str(), value.c_str());

        listener->publish_val(value);
      }
    }

    // Save the valid JSON data for callbacks
    this->last_valid_json_ = data;

    // Execute all registered JSON callbacks
    if (!this->json_callbacks_.empty()) {
      ESP_LOGV(TAG, "Executing %d JSON callbacks", (int) this->json_callbacks_.size());
      for (const auto &callback : this->json_callbacks_) {
        callback(root);
      }
    }

    return true;  // Parsing was handled successfully
  });

  if (!success) {
    ESP_LOGW(TAG, "Failed to parse JSON");
  }
}

/**
 * @brief Dumps the EmonTx configuration to the log.
 *
 * @note Logs the UART settings and other configuration details.
 */
void EmonTx::dump_config() {
  ESP_LOGCONFIG(TAG, "EmonTx:");

#ifdef USE_SENSOR
  ESP_LOGCONFIG(TAG, "  Registered sensors: %u", this->sensors_.size());

  // List all registered sensors with their tags
  for (const auto &sensor_pair : this->sensors_) {
    ESP_LOGCONFIG(TAG, "  Sensor: %s", sensor_pair.first.c_str());
  }
#else
  ESP_LOGCONFIG(TAG, "  Sensor support: DISABLED");
#endif
}

/**
 * @brief Publishes a value to all registered listeners that match the given tag.
 *
 * @param tag The tag associated with the value.
 * @param val The value to publish.
 */
void EmonTx::publish_value_(const std::string &tag, const std::string &val) {
  for (auto *element : emontx_listeners_) {
    if (tag != element->tag)
      continue;
    element->publish_val(val);
  }
}

/**
 * @brief Registers a listener to receive updates for specific tags.
 *
 * @param listener Pointer to the listener to register.
 */
#ifdef USE_SENSOR
void EmonTx::register_emontx_listener(EmonTxListener *listener) { emontx_listeners_.push_back(listener); }

void EmonTx::register_sensor(const std::string &tag_name, sensor::Sensor *sensor) {
  ESP_LOGCONFIG(TAG, "Registering sensor for tag: %s", tag_name.c_str());
  this->sensors_[tag_name] = sensor;
}
#endif
}  // namespace emontx
}  // namespace esphome
