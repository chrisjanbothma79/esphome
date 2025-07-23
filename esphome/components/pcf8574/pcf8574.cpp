#include "pcf8574.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace pcf8574 {

static const char *const TAG = "pcf8574";

void IRAM_ATTR HOT PCF8574ComponentStore::gpio_intr(PCF8574ComponentStore *arg) {
  arg->changes = arg->changes + 1;
  // Wake up the component from its disabled loop state
  arg->component->enable_loop_soon_any_context();
  // Try to get our loop() to be called asap
  arg->high_freq.start();
}

void PCF8574Component::setup() {
  ESP_LOGCONFIG(TAG, "Running setup");
  if (!this->read_gpio_()) {
    ESP_LOGE(TAG, "PCF8574 not available under 0x%02X", this->address_);
    this->mark_failed();
    return;
  }

  this->write_gpio_();
  this->read_gpio_();

  if (this->pin_intr_ != nullptr) {
    this->pin_intr_->setup();
    this->store_.pin_intr = this->pin_intr_->to_isr();
    this->store_.component = this;
    this->pin_intr_->attach_interrupt(PCF8574ComponentStore::gpio_intr, &this->store_, gpio::INTERRUPT_RISING_EDGE);
  }
}
void PCF8574Component::loop() {
  if (this->first_loop_) {
    // Set unused ports as outputs
    this->mode_mask_ = this->input_mask_;
    this->write_gpio_();
    this->first_loop_ = false;
    if (!this->mode_mask_) {
      // No need for loop if there are no inputs to read
      ESP_LOGD(TAG, "No inputs, disable loop");
      this->disable_loop();
      return;
    } else {
      this->enable_loop();
    }
  }
  if (this->pin_intr_ != nullptr) {
    // Check if interrupt fired as "no interrupt" means "no need to read device"
    uint16_t changes;
    {
      InterruptLock lock;
      changes = this->store_.changes;
      if (changes > 0) {
        this->store_.changes = 0;
        this->store_.high_freq.stop();
      }
    }
    if (changes == 0) {
      // No changes, disable the loop until the next interrupt
      this->disable_loop();
      return;
    }
#if ESPHOME_LOG_LEVEL >= ESPHOME_LOG_LEVEL_VERY_VERBOSE
    if (changes > 1) {
      ESP_LOGVV(TAG, "Missed %d events", changes - 1);
    }
#endif
  }
  this->read_gpio_();
}
void PCF8574Component::dump_config() {
  ESP_LOGCONFIG(TAG, "PCF8574:");
  LOG_I2C_DEVICE(this)
  ESP_LOGCONFIG(TAG, "  Is PCF8575: %s", YESNO(this->pcf8575_));
  if (this->pin_intr_ != nullptr) {
    LOG_PIN("  Interrupt pin: ", this->pin_intr_);
  } else {
    ESP_LOGCONFIG(TAG, "  Interrupt pin: DISABLED");
  }
  if (this->is_failed()) {
    ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
  }
}
bool PCF8574Component::digital_read(uint8_t pin) {
  return this->input_state_ & (1 << pin);
}
void PCF8574Component::digital_write(uint8_t pin, bool value) {
  if (value) {
    this->output_state_ |= (1 << pin);
  } else {
    this->output_state_ &= ~(1 << pin);
  }

  this->write_gpio_();
}
void PCF8574Component::pin_mode(uint8_t pin, gpio::Flags flags) {
  if (flags == gpio::FLAG_INPUT) {
    // Set mode mask bit
    this->mode_mask_ |= 1 << pin;
    this->input_mask_ |= 1 << pin;
    // Write GPIO to enable input mode
    this->write_gpio_();
  } else if (flags == gpio::FLAG_OUTPUT) {
    // Clear mode mask bit
    this->mode_mask_ &= ~(1 << pin);
    this->input_mask_ &= ~(1 << pin);
  }
  // Pickup runtime changes
  this->first_loop_ = true;
}
bool PCF8574Component::read_gpio_() {
  if (this->is_failed())
    return false;
  bool success;
  uint8_t data[2];
  if (this->pcf8575_) {
    success = this->read_bytes_raw(data, 2);
    this->input_state_ = (uint16_t(data[1]) << 8) | (uint16_t(data[0]) << 0);
  } else {
    success = this->read_bytes_raw(data, 1);
    this->input_state_ = data[0];
  }

  if (!success) {
    this->status_set_warning("read from i2c device failed");
    return false;
  }
  this->status_clear_warning();
  return true;
}
bool PCF8574Component::write_gpio_() {
  if (this->is_failed())
    return false;

  // Combine pins in input mode (that must always be set to HIGH)
  // with pins in output mode where state is HIGH
  uint16_t value = this->mode_mask_ | this->output_state_;

  uint8_t data[2];
  data[0] = value;
  data[1] = value >> 8;
  if (this->write(data, this->pcf8575_ ? 2 : 1) != i2c::ERROR_OK) {
    this->status_set_warning("write to i2c device failed");
    return false;
  }
  this->status_clear_warning();
  return true;
}
float PCF8574Component::get_setup_priority() const { return setup_priority::IO; }

void PCF8574GPIOPin::setup() { pin_mode(flags_); }
void PCF8574GPIOPin::pin_mode(gpio::Flags flags) { this->parent_->pin_mode(this->pin_, flags); }
bool PCF8574GPIOPin::digital_read() { return this->parent_->digital_read(this->pin_) != this->inverted_; }
void PCF8574GPIOPin::digital_write(bool value) { this->parent_->digital_write(this->pin_, value != this->inverted_); }
std::string PCF8574GPIOPin::dump_summary() const {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%u via PCF8574", pin_);
  return buffer;
}

}  // namespace pcf8574
}  // namespace esphome
