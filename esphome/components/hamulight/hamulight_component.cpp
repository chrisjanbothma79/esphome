#include "hamulight_component.h"
#include "esphome/core/log.h"          // For logging output in the ESPHome log
#include "esphome/core/helpers.h"      // For delay_microseconds and bitRead

namespace esphome {
namespace hamulight {

// Define a tag for logging output to identify messages from this component
static const char *const TAG = "hamulight";

/**
 * @brief Called once at ESP startup.
 *
 * Initializes the GPIO pins and outputs basic configuration information.
 */
void Hamulight::setup() {
  // Sets the RF transmit pin as an output and ensures it's initially LOW.
  this->rf_transmit_pin_->setup();
  this->rf_transmit_pin_->digital_write(false);

  // If an optional LED pin is configured, initializes it as an output and turns the LED off.
  if (this->led_pin_ != nullptr) {
    this->led_pin_->setup();
    this->led_pin_->digital_write(false);
  }

  // Logs the successful initialization of the component and its configuration.
  ESP_LOGCONFIG(TAG, "Hamulight is being set up...");
  ESP_LOGCONFIG(TAG, "  RF Transmit Pin: GPIO%d", this->rf_transmit_pin_->get_pin());
  ESP_LOGCONFIG(TAG, "  RF Address: 0x%04X", this->rf_address_);
  if (this->led_pin_ != nullptr) {
    ESP_LOGCONFIG(TAG, "  LED Pin: GPIO%d", this->led_pin_->get_pin());
  }
}

/**
 * @brief Outputs the complete configuration of the component to the log.
 *
 * This method is useful for debugging to check if the YAML configuration
 * has been correctly applied by the component.
 */
void Hamulight::dump_config() {
  LOG_LIGHT("", "Hamulight", this); // Standard ESPHome log output for lights
  ESP_LOGCONFIG(TAG, "  RF Transmit Pin: GPIO%d", this->rf_transmit_pin_->get_pin());
  if (this->led_pin_ != nullptr) {
    ESP_LOGCONFIG(TAG, "  LED Pin: GPIO%d", this->led_pin_->get_pin());
  }
  ESP_LOGCONFIG(TAG, "  RF Address: 0x%04X", this->rf_address_);
}

/**
 * @brief Returns the supported features of the light to Home Assistant.
 *
 * This indicates that the light supports on/off and brightness control.
 * Color functions are not relevant in this case.
 * @return light::LightTraits object.
 */
light::LightTraits Hamulight::get_traits() {
  auto traits = light::LightTraits();
  // Supports on/off and brightness control.
  traits.set_supported_color_modes({light::ColorMode::ON_OFF, light::ColorMode::BRIGHTNESS});
  // Mired values (for color temperature) are not relevant here.
  traits.set_min_mireds(0);
  traits.set_max_mireds(0);
  return traits;
}

/**
 * @brief Called by Home Assistant to change the state of the light.
 *
 * This method is responsible for implementing brightness control via the Home Assistant slider.
 * @param state The desired brightness value (0.0 for off, 1.0 for full brightness).
 */
void Hamulight::write_state(float state) {
  // If the brightness value is very low (near 0.0), the power toggle command is sent.
  if (state < 0.05f) { // A small threshold to detect turning off
    this->transmit_rf_command(RF_POWER_COMMAND);
    this->set_power(false); // Updates the internal state of the light to "off"
  } else {
    // 1. Convert Home Assistant float state (0.0 - 1.0) to 0-127 steps.
    // This assumes 128 steps (RF_SLIDE_STEPS) from min to max range, mapping 0% to 0 and 100% to 127.
    uint8_t input_val_0_127 = (uint8_t) round(state * (RF_SLIDE_STEPS - 1));

    // 2. Apply the 'slideValConv' logic from the original C++ code.
    // The original 'val--' part converts a 1-based index to a 0-based index.
    // If input_val_0_127 is 0, it means 0%, so no decrement. Otherwise, decrement.
    uint8_t converted_val_for_offset = input_val_0_127;
    if (converted_val_for_offset > 0) {
      converted_val_for_offset--;
    }

    // Add the offset and calculate the brightness value to transmit.
    uint8_t brightness_to_transmit = RF_SLIDE_START + converted_val_for_offset;

    // Apply boundary checks from the original 'slideValConv'
    if (brightness_to_transmit < RF_SLIDE_RANGE_MIN) {
        // This condition typically indicates an overflow and subsequent correction.
        // Given RF_SLIDE_START might overflow (0x80+0xA8=0x128 becomes 0x28),
        // adding RF_SLIDE_RANGE_MIN (0x80) again effectively shifts it into the desired range.
        brightness_to_transmit = brightness_to_transmit + RF_SLIDE_RANGE_MIN;
    }

    if (brightness_to_transmit > RF_SLIDE_RANGE_MAX) {
        ESP_LOGW(TAG, "Slider input value (0x%02X) exceeding allowed RF range (0x%02X), capping to max (0x%02X).",
                 brightness_to_transmit, RF_SLIDE_RANGE_MAX, RF_SLIDE_RANGE_MAX);
        brightness_to_transmit = RF_SLIDE_RANGE_MAX;
    }

    this->transmit_rf_brightness(brightness_to_transmit); // Sends the brightness command
    this->set_power(true); // Updates the internal state of the light to "on"
    this->set_brightness(state); // Updates the brightness of the light internally
    ESP_LOGD(TAG, "HA state %.2f -> input_val_0_127 %d -> converted_val_for_offset %d -> RF value 0x%02X",
             state, input_val_0_127, converted_val_for_offset, brightness_to_transmit);
  }
}

/**
 * @brief Generates the 32-bit signal sequence and fills the code_sequence_ array.
 *
 * This method implements the logic for creating the RF signal,
 * including checksum calculation and bit conversion into pulse durations.
 * @param command The 8-bit command (e.g., 0x5F for Power, or a brightness value).
 */
void Hamulight::generate_code_sequence(uint8_t command) {
  uint32_t combined = 0;
  // Checksum offset as specified in the original code.
  int8_t cks_offset = 83;
  uint8_t checksum = 0;

  // Splits the 16-bit RF address into two 8-bit bytes.
  uint8_t rf_address_byte0 = (uint8_t)(this->rf_address_ >> 8);   // MSB (Most Significant Byte)
  uint8_t rf_address_byte1 = (uint8_t)(this->rf_address_ & 0xFF); // LSB (Least Significant Byte)

  // Calculates the checksum byte.
  checksum = (rf_address_byte0 + rf_address_byte1 + command - cks_offset);

  // Combines all 4 signal bytes into a 32-bit word.
  // The order is: Address Byte 0, Address Byte 1, Command, Checksum.
  combined = ((uint32_t)rf_address_byte0 << 24) |
             ((uint32_t)rf_address_byte1 << 16) |
             ((uint32_t)command << 8) |
             (uint32_t)checksum;

  ESP_LOGD(TAG, "RF Command: 0x%02X, Combined Signal: 0x%08X", command, combined);

  // Parses the combined 32-bit word bit by bit.
  // Bits are read from LSB (Bit 0) to MSB (Bit 31) and written in reverse order
  // into the code_sequence_ array to mirror the transmission order.
  int n = (sizeof(combined) * 8) - 1; // n = 31 for a 32-bit word
  for (int i = 0; i < (sizeof(combined) * 8); i++) {
    bool b = bitRead(combined, i); // Reads the i-th bit from 'combined'
    // Calculates the position in the code_sequence_ array.
    // (n - i) * 2 reverses the bit order and multiplies by 2, since each bit consists of 2 pulses.
    int current_sequence_pos = (n - i) * 2;
    if (b) { // If the bit is 1, use the BIT1_PULSE values
      code_sequence_[current_sequence_pos] = BIT1_PULSE[0];
      code_sequence_[current_sequence_pos + 1] = BIT1_PULSE[1];
    } else { // If the bit is 0, use the BIT0_PULSE values
      code_sequence_[current_sequence_pos] = BIT0_PULSE[0];
      code_sequence_[current_sequence_pos + 1] = BIT0_PULSE[1];
    }
  }
}

/**
 * @brief Sends the generated RF signal via the RF transmit pin.
 *
 * This method directly controls the GPIO pin to generate the high and low pulses
 * based on the generated sequences.
 */
void Hamulight::send_rf_signal() {
  // Turns on the optional LED, if configured, as visual feedback.
  if (this->led_pin_ != nullptr) {
    this->led_pin_->digital_write(true); // LED ON
  }

  // Repeats the entire signal transmission multiple times for robustness.
  for (int i = 0; i < SIGNAL_REPETITIONS; i++) {

    // Transmission of the start sequence:
    // Iterates in steps of 2 through START_SEQUENCE, as each element pair
    // (HIGH duration, LOW duration) defines a pulse.
    for (int j = 0; j < START_SEQUENCE_SIZE; j += 2) {
      this->rf_transmit_pin_->digital_write(true); // Set pin HIGH
      delay_microseconds(BASE_PULSE * START_SEQUENCE[j]); // Wait for HIGH duration
      this->rf_transmit_pin_->digital_write(false); // Set pin LOW
      delay_microseconds(BASE_PULSE * START_SEQUENCE[j + 1]); // Wait for LOW duration
    }

    // Transmission of the code sequence:
    // Iterates in steps of 2 through code_sequence_, as each element pair
    // (HIGH duration, LOW duration) defines a pulse for a bit.
    for (int k = 0; k < CODE_SEQUENCE_SIZE; k += 2) {
      this->rf_transmit_pin_->digital_write(true); // Set pin HIGH
      delay_microseconds(BASE_PULSE * code_sequence_[k]); // Wait for HIGH duration
      this->rf_transmit_pin_->digital_write(false); // Set pin LOW
      delay_microseconds(BASE_PULSE * code_sequence_[k + 1]); // Wait for LOW duration
    }
  }

  // Ensures the transmit pin is LOW after transmission.
  this->rf_transmit_pin_->digital_write(false);
  // Turns off the LED, if configured.
  if (this->led_pin_ != nullptr) {
    this->led_pin_->digital_write(false); // LED OFF
  }
  ESP_LOGD(TAG, "RF signal transmission completed.");
}

/**
 * @brief Public method for sending a specific RF command.
 *
 * Called by Home Assistant buttons to send predefined commands.
 * @param command The 8-bit command (e.g., RF_POWER_COMMAND, RF_BRIGHT100_COMMAND).
 */
void Hamulight::transmit_rf_command(uint8_t command) {
  this->generate_code_sequence(command); // Generates the sequence for the command
  this->send_rf_signal();                // Sends the signal
}

/**
 * @brief Public method for sending a specific RF brightness value.
 *
 * Called by the write_state method (for the Home Assistant brightness slider).
 * @param brightness_value The 8-bit brightness value (in the range of RF_SLIDE_RANGE_MIN to RF_SLIDE_RANGE_MAX).
 */
void Hamulight::transmit_rf_brightness(uint8_t brightness_value) {
  this->generate_code_sequence(brightness_value); // Generates the sequence for the brightness value
  this->send_rf_signal();                         // Sends the signal
}

} // namespace hamulight
} // namespace esphome
