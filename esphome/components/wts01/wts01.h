#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace wts01 {

class WTS01Sensor : public PollingComponent {
 public:
  WTS01Sensor() : PollingComponent(15000) {} // Default update interval 15s
  
  // Constructor with uart component
  void construct(uart::UARTComponent *uart) { this->uart_ = uart; }

  void setup() override {
    // Empty setup - initialization is handled in the loop function
  }

  void update() override {
    // Publish the latest temperature value at the configured update interval
    if (this->temperature_sensor_ != nullptr && !isnan(this->current_temperature_)) {
      // Only log when publishing if the value has changed significantly since last publish
      if (isnan(this->last_published_temperature_) || 
          fabsf(this->current_temperature_ - this->last_published_temperature_) >= 0.1f) {
        ESP_LOGD(TAG, "Temperature: %.2f°C", this->current_temperature_);
      }
      
      this->last_published_temperature_ = this->current_temperature_;
      this->temperature_sensor_->publish_state(this->current_temperature_);
    }
  }

  void loop() override {
    while (this->uart_->available()) {
      uint8_t c;
      if (this->uart_->read_byte(&c)) {
        this->handle_char_(c);
      }
    }
  }

  void dump_config() override {
    ESP_LOGCONFIG(TAG, "WTS01 Sensor:");
    LOG_SENSOR("  ", "Temperature", this->temperature_sensor_);
    LOG_UPDATE_INTERVAL(this);
  }

  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { 
    this->temperature_sensor_ = temperature_sensor; 
  }

  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  static const uint8_t PACKET_SIZE = 9;
  static const uint8_t HEADER_1 = 0x55;
  static const uint8_t HEADER_2 = 0x01;
  static const uint8_t HEADER_3 = 0x01;
  static const uint8_t HEADER_4 = 0x04;
  
  uint8_t buffer_[PACKET_SIZE];
  uint8_t buffer_pos_{0};
  
  uart::UARTComponent *uart_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};
  float last_published_temperature_{NAN};  // Last temperature value published to HA
  float current_temperature_{NAN};  // Current temperature value from sensor
  
  void handle_char_(uint8_t c) {
    // Reset buffer if we're at the start of a new packet
    if (c == HEADER_1 && buffer_pos_ == 0) {
      buffer_[buffer_pos_++] = c;
      return;
    }
    
    // Check header sequence
    if (buffer_pos_ == 1 && c != HEADER_2) {
      buffer_pos_ = 0;
      return;
    }
    
    if (buffer_pos_ == 2 && c != HEADER_3) {
      buffer_pos_ = 0;
      return;
    }
    
    if (buffer_pos_ == 3 && c != HEADER_4) {
      buffer_pos_ = 0;
      return;
    }
    
    // Add byte to buffer
    buffer_[buffer_pos_++] = c;
    
    // Process complete packet
    if (buffer_pos_ == PACKET_SIZE) {
      process_packet_();
      buffer_pos_ = 0;
    }
  }
  
  void process_packet_() {
    // Based on Tasmota implementation
    // Format: 55 01 01 04 01 11 16 12 95
    // header            T  Td Ck  - T = Temperature, Td = Temperature decimal, Ck = Checksum
    
    // Check if packet is valid (we could add checksum verification here if needed)
    if (buffer_[0] == HEADER_1 && buffer_[1] == HEADER_2 && 
        buffer_[2] == HEADER_3 && buffer_[3] == HEADER_4) {
      
      // Extract temperature value
      uint8_t temp = buffer_[6];
      int sign = 1;
      
      // Handle negative temperatures
      if (temp > 127) {
        temp -= 128;
        sign = -1;
      }
      
      // Calculate temperature (temp + decimal/100)
      float temperature = sign * ((float)temp + ((float)buffer_[7] / 100.0f));
      
      // Store the temperature value but don't publish yet - wait for update() to be called
      this->current_temperature_ = temperature;
    }
  }

 private:
  static constexpr const char *TAG = "wts01";
};

}  // namespace wts01
}  // namespace esphome
