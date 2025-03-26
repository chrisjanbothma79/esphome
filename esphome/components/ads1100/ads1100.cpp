#include "ads1100.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ads1100 {

static const char *const TAG = "ads1100";
static const uint8_t ADS1100_REGISTER_CONVERSION = 0x00;
static const uint8_t ADS1100_REGISTER_CONFIG = 0x01;

void ADS1100Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ADS1100...");
  LOG_I2C_DEVICE(this);

  // Log initial state
  ESP_LOGD(TAG, "Initial state - Gain: %d, Sample Rate: %d", this->gain_, this->sample_rate_);

  // Initial delay to allow device to power up
  delay(100);

  // Simple approach like ADS1115 - first attempt to read a value to check communication
  uint16_t value;
  if (!this->read_byte_16(ADS1100_REGISTER_CONVERSION, &value)) {
    ESP_LOGE(TAG, "Communication with ADS1100 failed!");
    this->mark_failed();
    return;
  }
  ESP_LOGD(TAG, "ADS1100 communication test successful");
  ESP_LOGD(TAG, "Initial conversion value: 0x%04X", value);

  // For ADS1100, we should write directly to the conversion register (0x00)
  // Based on the M5Stack implementation, we should skip directly writing to config
  // and just use the device in its default state

  // Save a default config for later use
  uint16_t config = 0;

  // Set gain (bits 0-1)
  config |= (this->gain_ & 0x03);

  // Set sample rate (bits 2-3)
  config |= (this->sample_rate_ & 0x03) << 2;

  this->prev_config_ = config;
  ESP_LOGD(TAG, "Using default configuration: 0x%04X", config);

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
  ESP_LOGCONFIG(TAG, "ADS1100 initialized successfully");
}

void ADS1100Component::dump_config() {
  ESP_LOGCONFIG(TAG, "ADS1100:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with ADS1100 failed!");
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
    ESP_LOGE(TAG, "ADS1100 not initialized");
    return NAN;
  }

  // In continuous mode, we just read the current conversion result
  uint16_t raw_adc;
  if (!this->read_byte_16(ADS1100_REGISTER_CONVERSION, &raw_adc)) {
    ESP_LOGE(TAG, "Failed to read ADC value");
    return NAN;
  }

  ESP_LOGVV(TAG, "Raw ADC value: 0x%04X", raw_adc);

  // Convert raw ADC value to voltage
  float voltage;
  int16_t value = raw_adc;  // Treat as signed 16-bit integer

  // The ADS1100 has a fixed input range of ±VREF
  // Each gain setting divides this range:
  // Gain=1: ±2.048V, Gain=2: ±1.024V, Gain=4: ±0.512V, Gain=8: ±0.256V

  // Convert to voltage based on gain setting and datasheet values
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