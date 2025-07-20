#include "emontx.h"
#include "esphome/core/log.h"
#include "esphome/components/json/json_util.h"

namespace esphome {
namespace emontx {

static const char *const TAG = "emontx";

/**
 * @brief Initializes the EmonTx component.
 *
 * @details Sets up the initial state of the component by:
 * 1. Setting the state machine to OFF
 * 2. Logging the component configuration
 * 3. Registering and logging all configured sensors (when sensor support is enabled)
 *
 * This method is called once during device startup. After setup completes,
 * the component will wait for update() to be called before starting to
 * process any incoming data.
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
 * @brief Resets the state machine to start looking for new JSON data.
 *
 * @details This method is called periodically according to the update_interval configured
 * in the YAML. It prepares the component to receive new data by:
 * 1. Clearing the internal buffer
 * 2. Resetting the state machine from OFF to WAITING_FOR_START
 *
 * After this method is called, the state machine will begin actively looking for
 * the opening brace '{' of a new JSON object in the incoming UART data stream.
 */
void EmonTx::update() {
  ESP_LOGD(TAG, "Updating EmonTx state...");

  if (state_ == OFF) {
    buffer_.clear();  // Clear the buffer for new data
    state_ = WAITING_FOR_START;
  }

  ESP_LOGD(TAG, "EmonTx is now ready to receive data.");
}

/**
 * @brief Reads characters from UART until a specific target character is found.
 *
 * @details This method is used by the JSON parsing state machine to extract complete JSON objects.
 * It operates in two modes controlled by the drop parameter:
 * - When drop=true: Discards all characters except the target (used to find the opening brace)
 * - When drop=false: Collects all characters until the target is found (used to collect JSON content)
 *
 * The method also enforces valid JSON formatting by rejecting any data that contains
 * newline characters, which should not appear within a properly formatted JSON object.
 *
 * @param drop If true, discard all characters except the target character.
 * @param c The target character to look for.
 * @return true If the target character was found.
 * @return false If an error occurred (newline in JSON, buffer overflow) or target not found.
 */
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
 * @brief Implements the main state machine for parsing JSON data from the serial port.
 *
 * @details The state machine transitions through the following states:
 * - OFF: Initial state, waiting for update() to be called.
 * - WAITING_FOR_START: Looks for the opening brace '{' of a JSON object.
 * - COLLECTING_JSON: Collects characters until the closing brace '}' is found.
 *   Any newline characters during this phase will cause the buffer to be discarded.
 * - JSON_COLLECTED: Processes the complete JSON object, updating sensors and
 *   executing callbacks before returning to OFF state.
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

/**
 * @brief Parses a JSON string and updates associated sensors and listeners.
 *
 * @details This method takes a string containing JSON data and attempts to parse it.
 * If parsing is successful, it performs the following operations:
 * 1. Updates all registered sensors that have matching keys in the JSON
 * 2. Updates all registered listeners with their corresponding values
 * 3. Stores the successfully parsed JSON string for use in callbacks
 * 4. Executes all registered JSON callbacks, passing the parsed JsonObject
 *
 * The method handles both sensor updates and general-purpose callbacks, allowing
 * the component to integrate with multiple parts of the ESPHome system.
 *
 * @param data The JSON string to parse
 */
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
 * @brief Logs the EmonTx component configuration details.
 *
 * @details This method is called during startup to output the component's
 * configuration to the log. It provides information about:
 * - The component identification
 * - Number of registered sensors (when sensor support is enabled)
 * - List of all registered sensors with their tag names
 *
 * This information is valuable for debugging and verifying that the
 * component is correctly configured according to the YAML definition.
 * The method is automatically called by ESPHome's core during device startup.
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
 * @details This method iterates through all registered EmonTx listeners and forwards
 * the provided value to any listener whose tag matches the specified tag parameter.
 * This internal helper method is used to distribute received data to the appropriate
 * components within the ESPHome system.
 *
 * @param tag The tag identifier to match against registered listeners.
 * @param val The string value to publish to matching listeners.
 */
void EmonTx::publish_value_(const std::string &tag, const std::string &val) {
  for (auto *element : emontx_listeners_) {
    if (tag != element->tag)
      continue;
    element->publish_val(val);
  }
}

/**
 * @brief Registers a listener to receive updates for specific JSON data tags.
 *
 * @details This method adds the provided listener to the internal list of EmonTx listeners.
 * When JSON data is received and successfully parsed, any listener whose tag matches
 * a key in the JSON will receive the corresponding value through its publish_val() method.
 *
 * This registration mechanism allows other ESPHome components to subscribe to specific
 * data points from the EmonTx JSON stream without having to implement their own parsing logic.
 *
 * @param listener Pointer to the listener object to register. The listener must have a 'tag'
 *                 property that identifies which JSON key it's interested in.
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
