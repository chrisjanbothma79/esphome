#include "m3200.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace m3200 {

static const char *const TAG = "m3200";

void M3200Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up M3200 Pressure Sensor...");

  // Initialize I2C bus state
  this->i2c_init();

  // Test communication with the sensor
  if (!this->read_sensor_data()) {
    ESP_LOGE(TAG, "Communication with M3200 failed during setup");
  } else {
    ESP_LOGD(TAG, "M3200 setup successfully");
  }
}

void M3200Component::update() {
  // Read sensor data and publish to sensors
  if (!this->read_sensor_data()) {
    ESP_LOGW(TAG, "Failed to read data from M3200");
  }
}

void M3200Component::dump_config() {
  ESP_LOGCONFIG(TAG, "M3200 Pressure Sensor:");
  LOG_PIN("  SDA Pin: ", this->sda_pin_);
  LOG_PIN("  SCL Pin: ", this->scl_pin_);
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  ESP_LOGCONFIG(TAG, "  Pressure Range: %.1f to %.1f", this->min_pressure_, this->max_pressure_);
  LOG_SENSOR("  ", "Pressure", this->pressure_sensor_);
  LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
}

// I2C bit-banging implementation with M3200-specific timings
void M3200Component::i2c_init() {
  // Set pins to output mode and idle state (both high)
  this->sda_high();
  this->scl_high();
  this->sda_output();
}

void M3200Component::i2c_start() {
  // START condition: SDA goes from HIGH to LOW while SCL is HIGH
  this->sda_output();
  this->sda_high();
  this->scl_high();
  this->delay_us(4);
  this->sda_low();
  this->delay_us(4);
  this->scl_low();
}

void M3200Component::i2c_stop() {
  // STOP condition: SDA goes from LOW to HIGH while SCL is HIGH
  this->sda_output();
  this->scl_low();
  this->sda_low();
  this->delay_us(4);
  this->scl_high();
  this->delay_us(4);
  this->sda_high();
  this->delay_us(4);
}

bool M3200Component::i2c_write_byte(uint8_t data) {
  this->sda_output();

  // Send 8 bits, MSB first
  for (int i = 7; i >= 0; i--) {
    this->scl_low();

    if (data & (1 << i))
      this->sda_high();
    else
      this->sda_low();

    this->delay_us(2);
    this->scl_high();
    this->delay_us(2);

    // Peculiarity #3: Special handling for first bit
    if (i == 7) {
      this->scl_low();
      this->delay_us(2);
    }
  }

  // Read ACK bit
  this->scl_low();
  this->sda_high();  // Release SDA for slave ACK
  this->sda_input();
  this->delay_us(2);

  this->scl_high();
  this->delay_us(2);

  bool ack = !this->sda_read();  // ACK = LOW

  this->scl_low();
  this->sda_output();
  this->sda_high();

  return ack;
}

uint8_t M3200Component::i2c_read_byte(bool ack) {
  uint8_t result = 0;

  this->sda_input();

  // Read 8 bits, MSB first
  for (int i = 7; i >= 0; i--) {
    this->scl_low();
    this->delay_us(2);
    this->scl_high();
    this->delay_us(2);

    if (this->sda_read())
      result |= (1 << i);
  }

  // Send ACK/NACK
  this->scl_low();
  this->sda_output();

  if (ack)
    this->sda_low();  // ACK
  else
    this->sda_high();  // NACK

  this->delay_us(2);
  this->scl_high();
  this->delay_us(2);
  this->scl_low();
  this->delay_us(2);

  return result;
}

// GPIO manipulation methods
void M3200Component::sda_low() { this->sda_pin_->digital_write(false); }

void M3200Component::sda_high() { this->sda_pin_->digital_write(true); }

void M3200Component::sda_input() { this->sda_pin_->pin_mode(gpio::FLAG_INPUT | gpio::FLAG_PULLUP); }

void M3200Component::sda_output() { this->sda_pin_->pin_mode(gpio::FLAG_OUTPUT); }

void M3200Component::scl_low() { this->scl_pin_->digital_write(false); }

void M3200Component::scl_high() { this->scl_pin_->digital_write(true); }

bool M3200Component::sda_read() { return this->sda_pin_->digital_read(); }

void M3200Component::delay_us(uint32_t us) { delayMicroseconds(us); }

bool M3200Component::read_sensor_data() {
  // Step 1: Send Measurement Request (MR) command
  this->i2c_start();
  bool success = this->i2c_write_byte(this->address_ << 1 | 1);  // Read address
  if (!success) {
    ESP_LOGE(TAG, "Sensor did not ACK measurement request (MR) command");
    this->i2c_stop();
    return false;
  }
  this->i2c_stop();

  // Delay between commands as required by M3200
  delay(2);  // 2ms delay as in original code

  // Step 2: Read data using Data Fetch (DF4) command
  this->i2c_start();
  success = this->i2c_write_byte(this->address_ << 1 | 1);  // Read address
  if (!success) {
    ESP_LOGE(TAG, "Sensor did not ACK data fetch (DF4) command");
    this->i2c_stop();
    return false;
  }

  // Read 4 bytes of data
  uint8_t data[4];
  data[0] = this->i2c_read_byte(true);   // Bridge data high byte
  data[1] = this->i2c_read_byte(true);   // Bridge data low byte
  data[2] = this->i2c_read_byte(true);   // Temperature high byte
  data[3] = this->i2c_read_byte(false);  // Temperature low byte

  this->i2c_stop();

  // Check status bits
  uint8_t status = data[0] & 0xC0;

  if (status == STATUS_NORMAL) {
    // Extract pressure value (14-bit) - first 6 bits of data[0] + data[1]
    uint16_t p_value = ((data[0] & 0x3F) << 8) | data[1];

    // Extract temperature value (11-bit)
    uint16_t t_value = (data[2] << 3) | (data[3] >> 5);

    // Calculate calibrated values
    float t_scope = 200.0f;   // -50~150°C range
    float t_span = 2048.0f;   // 11-bit
    float p_span = 14000.0f;  // P2-P1 (15000-1000)

    float temperature = t_value * t_scope / t_span - 50.0f;
    float pressure = p_value * (this->max_pressure_ - this->min_pressure_) / p_span + this->min_pressure_;

    ESP_LOGD(TAG, "Raw pressure: %u, Raw temp: %u", p_value, t_value);
    ESP_LOGD(TAG, "Pressure: %.2f, Temperature: %.2f", pressure, temperature);

    // Publish values to sensors
    if (this->pressure_sensor_ != nullptr)
      this->pressure_sensor_->publish_state(pressure);

    if (this->temperature_sensor_ != nullptr)
      this->temperature_sensor_->publish_state(temperature);

    return true;
  } else if (status == STATUS_STALE) {
    ESP_LOGW(TAG, "Stale data: Data has been fetched since last measurement cycle");
  } else if (status == STATUS_FAULT) {
    ESP_LOGE(TAG, "Sensor fault detected");
  } else {
    ESP_LOGW(TAG, "Unknown status bits: 0x%02X", status);
  }

  return false;
}

}  // namespace m3200
}  // namespace esphome
