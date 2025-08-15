#include "waveshare_io.h"
#include "esphome/core/log.h"

namespace esphome {
namespace waveshare_io {

static const uint8_t IO_EXTENSION_MODE = 0x02;
static const uint8_t IO_EXTENSION_IO_OUTPUT_ADDR = 0x03;
static const uint8_t IO_EXTENSION_IO_INPUT_ADDR = 0x04;
static const uint8_t IO_EXTENSION_PWM_ADDR = 0x05;
static const uint8_t IO_EXTENSION_ADC_ADDR = 0x06;

static const uint8_t MAX_PWM_VALUE = 0.97 * 255;  // 0.97 * 255 = 247.35

static const char *const TAG = "waveshare_io";

void WaveshareIOComponent::setup() {
  this->mode_mask_ = 0xFF;    // Set all pins to output mode
  this->output_mask_ = 0xFF;  // Set all pins to high (output mode)

  bool step1 = this->write_gpio_modes_();
  bool step2 = this->write_gpio_outputs_();

  if (!step1 || !step2) {
    ESP_LOGE(TAG, "Failed to initialize Waveshare IO expander");
    this->mark_failed();
    return;
  }

  ESP_LOGCONFIG(TAG, "Initialization complete. Warning: %d, Error: %d", this->status_has_warning(),
                this->status_has_error());
}

void WaveshareIOComponent::pin_mode(uint8_t pin, gpio::Flags flags) {
  // bits: 0 = input, 1 = output
  if (flags == gpio::FLAG_INPUT) {
    // Clear mode mask bit
    this->mode_mask_ &= ~(1 << pin);
  } else if (flags == gpio::FLAG_OUTPUT) {
    // Set mode mask bit
    this->mode_mask_ |= 1 << pin;
  }
  this->write_gpio_modes_();
}

void WaveshareIOComponent::loop() { this->reset_pin_cache_(); }

void WaveshareIOComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "WaveshareIO:");
  LOG_I2C_DEVICE(this)
  if (this->is_failed()) {
    ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
  }
}

uint16_t WaveshareIOComponent::get_adc_value() {
  if (this->is_failed())
    return 0;

  uint8_t data[2];
  if (!this->read_bytes(IO_EXTENSION_ADC_ADDR, data, 2)) {
    this->status_set_warning("Failed to read ADC register");
    return 0;
  }
  uint16_t adc_value = (data[1] << 8) | data[0];
  this->status_clear_warning();
  return adc_value;
}

void WaveshareIOComponent::set_pwm_value(uint8_t value) {
  if (this->is_failed())
    return;

  // limit PWM level, might be connected with circuit schematic
  // as per Waveshare IO library function "void IO_EXTENSION_Pwm_Output(uint8_t Value)"
  if (value > MAX_PWM_VALUE) {
    value = MAX_PWM_VALUE;
  }

  uint8_t data[2] = {IO_EXTENSION_PWM_ADDR, value};
  if (!this->write_bytes(data[0], &data[1], 1)) {
    this->status_set_warning("Failed to set PWM duty cycle");
    return;
  }

  this->status_clear_warning();
}

bool WaveshareIOComponent::write_gpio_modes_() {
  if (this->is_failed())
    return false;
  if (!this->write_byte(IO_EXTENSION_MODE, this->mode_mask_)) {
    this->status_set_warning("Failed to write mode register");
    return false;
  }
  this->status_clear_warning();
  return true;
}

bool WaveshareIOComponent::write_gpio_outputs_() {
  if (this->is_failed())
    return false;
  if (!this->write_byte(IO_EXTENSION_IO_OUTPUT_ADDR, this->output_mask_)) {
    this->status_set_warning("Failed to write output register");
    return false;
  }
  this->status_clear_warning();
  return true;
}

bool WaveshareIOComponent::digital_read_hw(uint8_t pin) {
  if (this->is_failed())
    return false;

  uint8_t data = 0;
  if (!this->read_bytes(IO_EXTENSION_IO_INPUT_ADDR, &data, 1)) {
    this->status_set_warning("Failed to read input register");
    return false;
  }
  this->input_mask_ = data;

  this->status_clear_warning();
  return true;
}

void WaveshareIOComponent::digital_write_hw(uint8_t pin, bool value) {
  if (this->is_failed())
    return;

  if (value) {
    this->output_mask_ |= (1 << pin);
  } else {
    this->output_mask_ &= ~(1 << pin);
  }

  uint8_t data = this->output_mask_;
  if (!this->write_byte(IO_EXTENSION_IO_OUTPUT_ADDR, data)) {
    this->status_set_warning("Failed to write output register");
    return;
  }

  this->status_clear_warning();
}

bool WaveshareIOComponent::digital_read_cache(uint8_t pin) { return this->input_mask_ & (1 << pin); }
float WaveshareIOComponent::get_setup_priority() const { return setup_priority::IO; }

// Run our loop() method very early in the loop, so that we cache read values
// before other components call our digital_read() method.
float WaveshareIOComponent::get_loop_priority() const { return 9.0f; }  // Just after WIFI

void WaveshareIOGPIOPin::pin_mode(gpio::Flags flags) { this->parent_->pin_mode(this->pin_, flags); }
bool WaveshareIOGPIOPin::digital_read() { return this->parent_->digital_read(this->pin_) ^ this->inverted_; }

void WaveshareIOGPIOPin::digital_write(bool value) {
  this->parent_->digital_write(this->pin_, value ^ this->inverted_);
}

std::string WaveshareIOGPIOPin::dump_summary() const { return str_sprintf("EXIO%u via WaveshareIO", pin_); }
void WaveshareIOGPIOPin::set_flags(gpio::Flags flags) {
  flags_ = flags;
  this->parent_->pin_mode(this->pin_, flags);
}

}  // namespace waveshare_io
}  // namespace esphome
