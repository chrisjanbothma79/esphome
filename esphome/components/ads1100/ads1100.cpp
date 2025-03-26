#include "ads1100.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ads1100 {

static const char *const TAG = "ads1100";
static const uint8_t ADS1100_REGISTER_CONVERSION = 0x00;
static const uint8_t ADS1100_REGISTER_CONFIG = 0x01;

void ADS1100Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ADS1110...");
  LOG_I2C_DEVICE(this);

  // Log initial state
  ESP_LOGD(TAG, "Initial state - Gain: %d, Sample Rate: %d", this->gain_, this->sample_rate_);

  // Initial delay to allow device to power up
  delay(100);

  // First, read the current conversion register value to check communication
  uint16_t value;
  if (!this->read_byte_16(ADS1100_REGISTER_CONVERSION, &value)) {
    ESP_LOGE(TAG, "Communication with ADS1110 failed!");
    this->mark_failed();
    return;
  }
  ESP_LOGD(TAG, "ADS1110 communication test successful");
  ESP_LOGD(TAG, "Initial conversion value: 0x%04X", value);

  // For ADS1110, try to read the config register
  uint16_t current_config;
  if (!this->read_byte_16(ADS1100_REGISTER_CONFIG, &current_config)) {
    ESP_LOGD(TAG, "Could not read config register - this is normal for ADS1110");
    // For ADS1110, we might not be able to read the config register
    // This is okay - we'll just use the default config
  } else {
    ESP_LOGD(TAG, "Current config register: 0x%04X", current_config);
  }

  // ADS1110 has a configuration register that can be written to
  // Configure the device based on our requirements
  uint16_t config = 0;

  // Set gain (bits 0-1)
  config |= (this->gain_ & 0x03);

  // Set sample rate (bits 2-3)
  config |= (this->sample_rate_ & 0x03) << 2;

  // Try to write the configuration
  ESP_LOGD(TAG, "Attempting to write config: 0x%04X", config);
  if (!this->write_byte_16(ADS1100_REGISTER_CONFIG, config)) {
    ESP_LOGD(TAG, "Could not write config - using default configuration");
    // This is expected if the chip is truly an ADS1110 and not ADS1100
    // We'll continue and use the default settings
  }

  // Store what we believe the config is
  this->prev_config_ = config;

  // Wait for first conversion to complete based on sample rate
  int delay_ms;
  switch (this->sample_rate_) {
    case ADS1100_SAMPLE_RATE_8_SPS:
      delay_ms = 125;
      break;
    case ADS1100_SAMPLE_RATE_16_SPS:
      delay_ms = 62;
      break;
    case ADS1100_SAMPLE_RATE_32_SPS:
      delay_ms = 31;
      break;
    case ADS1100_SAMPLE_RATE_128_SPS:
    default:
      delay_ms = 8;
      break;
  }
  delay(delay_ms);

  // Try to read a measurement to make sure we can communicate
  float test_voltage = this->request_measurement();
  if (std::isnan(test_voltage)) {
    ESP_LOGE(TAG, "Failed to read initial measurement");
    this->mark_failed();
    return;
  }

  ESP_LOGD(TAG, "Initial measurement: %.4f V", test_voltage);
  this->i2c_initialized_ = true;
  ESP_LOGCONFIG(TAG, "ADS1110 initialized successfully");
}

void ADS1100Component::dump_config() {
  ESP_LOGCONFIG(TAG, "ADS1110:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with ADS1110 failed!");
  }
  ESP_LOGCONFIG(TAG, "  Gain: %d", this->gain_);
  ESP_LOGCONFIG(TAG, "  Sample Rate: %d SPS",
                this->sample_rate_ == ADS1100_SAMPLE_RATE_128_SPS  ? 128
                : this->sample_rate_ == ADS1100_SAMPLE_RATE_32_SPS ? 32
                : this->sample_rate_ == ADS1100_SAMPLE_RATE_16_SPS ? 16
                                                                   : 8);
}

float ADS1100Component::request_measurement() {
  if (!this->i2c_initialized_) {
    ESP_LOGE(TAG, "ADS1110 not initialized");
    return NAN;
  }

  // For ADS1110, we just read the conversion register
  // It operates in continuous conversion mode by default
  uint16_t raw_adc;
  if (!this->read_byte_16(ADS1100_REGISTER_CONVERSION, &raw_adc)) {
    ESP_LOGE(TAG, "Failed to read ADC value");
    return NAN;
  }

  ESP_LOGVV(TAG, "Raw ADC value: 0x%04X", raw_adc);

  // Convert raw ADC value to voltage
  // The ADS1110 returns a signed 16-bit value
  int16_t value = raw_adc;

  // For ADS1110, according to datasheet:
  // Gain=1: ±2.048V
  // Gain=2: ±1.024V
  // Gain=4: ±0.512V
  // Gain=8: ±0.256V
  float voltage;
  switch (this->gain_) {
    case ADS1100_GAIN_1:
      voltage = value * 2.048f / 32768.0f;
      break;
    case ADS1100_GAIN_2:
      voltage = value * 1.024f / 32768.0f;
      break;
    case ADS1100_GAIN_4:
      voltage = value * 0.512f / 32768.0f;
      break;
    case ADS1100_GAIN_8:
      voltage = value * 0.256f / 32768.0f;
      break;
    default:
      ESP_LOGE(TAG, "Invalid gain setting: %d", this->gain_);
      return NAN;
  }

  ESP_LOGVV(TAG, "Raw ADC: %d, Voltage: %.4f V", value, voltage);
  return voltage;
}

}  // namespace ads1100
}  // namespace esphome