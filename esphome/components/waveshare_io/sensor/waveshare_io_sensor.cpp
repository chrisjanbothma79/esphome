#include "waveshare_io_sensor.h"

#include "esphome/core/log.h"

namespace esphome {
namespace waveshare_io {

static const char *const TAG = "waveshare_io.sensor";

float WaveshareIOSensor::get_setup_priority() const { return setup_priority::DATA; }

void WaveshareIOSensor::dump_config() {
  ESP_LOGCONFIG(TAG,
                "WaveshareIOSensor:\n"
                "  Reference Voltage: %.2fV",
                this->reference_voltage_);
}

float WaveshareIOSensor::sample() {
  uint16_t adc_value = this->parent_->get_adc_value();
  // Convert the ADC value to voltage. 10-bit ADC
  float voltage = adc_value * this->reference_voltage_ / 1023.0f;
  return voltage;
}

void WaveshareIOSensor::update() { this->publish_state(this->sample()); }

}  // namespace waveshare_io
}  // namespace esphome
