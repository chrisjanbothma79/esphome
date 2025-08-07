//
// ref: https://github.com/adafruit/Adafruit_HDC302x/blob/main/Adafruit_HDC302x.cpp
//      https://github.com/esphome/esphome/blob/dev/esphome/components/pmwcs3/pmwcs3.cpp
//
// UTILITIES
// From https://github.com/adafruit/Adafruit_HDC302x/blob/main/Adafruit_HDC302x.cpp
//

#include "hdc302x.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"
#include <string>

namespace esphome {
namespace hdc302x {

static const char *const TAG = "hdc302x";

enum HDC302xCommands {
  SOFT_RESET = 0x30A2,
  READ_MANUFACTURER_ID = 0x3781,
  READ_NIST_ID_SERIAL_BYTES_5_4 = 0x3683,  // Command to read bytes 5 and 4 of the NIST ID
  READ_NIST_ID_SERIAL_BYTES_3_2 = 0x3684,  // Command to read bytes 3 and 2 of the NIST ID
  READ_NIST_ID_SERIAL_BYTES_1_0 = 0x3685,  // Command to read bytes 1 and 0 of the NIST ID
  ACCESS_OFFSETS = 0xA004,                 // Command to write/read offsets
  SET_HEATER_POWER = 0x306E,               // Command to set heater power
  ENABLE_HEATER = 0x306D,                  // Command to enable heater
  DISABLE_HEATER = 0x3066,                 // Command to disable heater
  READ_STATUS_REGISTER = 0xF32D,           // Command to read the status register
  CLEAR_STATUS_REGISTER = 0x3041,          // Command to clear the status register
  MEASUREMENT_READOUT_AUTO_MODE = 0xE000,  // Measurement Readout Auto Mode
  SET_LOW_ALERT = 0x6100,                  // Configure ALERT Thresholds for Set Low Alert
  SET_HIGH_ALERT = 0x611D,                 // Configure ALERT Thresholds for Set High Alert
  CLR_LOW_ALERT = 0x610B,                  // Configure ALERT Thresholds for Clear Low Alert
  CLR_HIGH_ALERT = 0x6116                  // Configure ALERT Thresholds for Clear High Alert
};
enum HdcTriggerMode {
  TRIGGERMODE_LP0 = 0x2400,  // Trigger-On Demand Mode, Low Power Mode 0
  TRIGGERMODE_LP1 = 0x240B,  // Trigger-On Demand Mode, Low Power Mode 1
  TRIGGERMODE_LP2 = 0x2416,  // Trigger-On Demand Mode, Low Power Mode 2
  TRIGGERMODE_LP3 = 0x24FF   // Trigger-On Demand Mode, Low Power Mode 3
};

// I wish we could use std::format here, but the esp8266 platform apparently isn't compiled with c++20 yet,
// so we need to do the snprintf route.  And, incase ESP_LOGW can handle more than 256 chars, we
// separate out the calls to ESP_LOGW from the snprintf code.
#define WARN(format, ...) \
  { \
    char msg[256] = ""; \
    if (this->bus_name_.empty()) { \
      snprintf(msg, 256, format, __VA_ARGS__); \
      ESP_LOGW(TAG, format, __VA_ARGS__); \
    } else { \
      snprintf(msg, 256, "%s " format, this->bus_name_.c_str(), __VA_ARGS__); \
      ESP_LOGW(TAG, "%s " format, this->bus_name_.c_str(), __VA_ARGS__); \
    } \
    if (this->last_error_sensor_) { \
      this->last_error_sensor_->publish_state(msg); \
    } \
  }

/**
 * @brief Calculates the CRC-8 for the given data.
 *
 * This function calculates the CRC-8 for the given data array using the
 * polynomial 0x31.
 *
 * @param data Pointer to the data array.
 * @param len Length of the data array.
 * @return uint8_t The calculated CRC-8 value.
 */
static uint8_t calculate_CRC8(const uint8_t *data, int len) {
  uint8_t crc = 0xFF;  // Typical initial value
  for (int i = 0; i < len; i++) {
    crc ^= data[i];                // XOR byte into least sig. byte of crc
    for (int j = 8; j > 0; j--) {  // Loop over each bit
      if (crc & 0x80) {            // If the uppermost bit is 1...
        crc = (crc << 1) ^ 0x31;   // Polynomial used by HDC302x
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;  // Final XOR value can also be applied if specified by device
}

void HDC302XComponent::setup() {
  i2c::ErrorCode ec = this->write_command(HDC302xCommands::SOFT_RESET);
  if (ec != i2c::NO_ERROR) {
    WARN("setup: Reset command failed (i2c::ErrorCode %d)", ec);
    return;
  }
  this->clear_status_register();

  uint16_t manufacturerID = 0;
  ec = this->write_command_read_data(HDC302xCommands::READ_MANUFACTURER_ID, &manufacturerID);
  if (ec != i2c::NO_ERROR) {
    WARN("setup: Read manufacturerID failed (i2c::ErrorCode %d)", ec);
  } else if (manufacturerID != 0x3000) {
    WARN("setup: Wrong manufacturer ID (got 0x%x expected 0x%x)", manufacturerID, 0x3000);
  }

  // setAutoMode(EXIT_AUTO_MODE);
}
void HDC302XComponent::update() {
  // ESP_LOGI(TAG, "Update starting on %s", bus_name_.c_str());
  this->start_read_temperature_RH();
  // ESP_LOGI(TAG, "Update done. Got temp=%.1f C rh=%.1f %%", temp, rh);
}
void HDC302XComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "HDC302X");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
  }
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "temperature", this->temperature_sensor_);
  LOG_SENSOR("  ", "humidity", this->humidity_sensor_);
  LOG_TEXT_SENSOR("  ", "last_error", this->last_error_sensor_);
}

void HDC302XComponent::start_read_temperature_RH() {
  HdcTriggerMode mode = TRIGGERMODE_LP0;  // LP0 is lowest noise
  uint16_t command = static_cast<uint16_t>(mode);
  // Trigger the temperature and humidity measurement
  i2c::ErrorCode ec = this->write_command(command);
  if (ec != i2c::NO_ERROR) {
    WARN("startReadTemperatureRH: write command (i2c::ErrorCode %d)", ec);
    return;
  }
  // Wait for conversion (tmeas in datasheet table 7.5  LP0 takes 12.5ms.  Add a bit more to be sure)
  set_timeout("wait_temprh", 20 /*ms*/, [this]() { this->finish_read_temperature_RH(); });
}

void HDC302XComponent::finish_read_temperature_RH() {
  // Read results
  uint8_t buffer[6];
  i2c::ErrorCode ec = this->read(buffer, 6);
  if (ec != i2c::NO_ERROR) {
    WARN("finishReadTemperatureRH: read failed (i2c::ErrorCode %d)", ec);
    return;
  }

  // Validate CRC for temperature data
  if (calculate_CRC8(buffer, 2) != buffer[2]) {
    WARN("finishReadTemperatureRH: temp checksum failed (i2c::ErrorCode %d)", ec);
    return;
  }

  // Validate CRC for humidity data
  if (calculate_CRC8(buffer + 3, 2) != buffer[5]) {
    WARN("finishReadTemperatureRH: humidity checksum failed (i2c::ErrorCode %d)", ec);
    return;
  }

  uint16_t raw_temperature = (buffer[0] << 8) | buffer[1];
  uint16_t raw_humidity = (buffer[3] << 8) | buffer[4];

  // Convert raw temperature data to degrees C
  float temp = ((raw_temperature / 65535.0) * 175.0) - 45.0;

  // Convert raw humidity data to percentage
  float RH = (raw_humidity / 65535.0) * 100.0;

  if (this->temperature_sensor_)
    this->temperature_sensor_->publish_state(temp);
  if (this->humidity_sensor_)
    this->humidity_sensor_->publish_state(RH);
}

void HDC302XComponent::clear_status_register() {
  i2c::ErrorCode ec = this->write_command(HDC302xCommands::CLEAR_STATUS_REGISTER);
  if (ec != i2c::NO_ERROR) {
    WARN("Clear status reg command failed (i2c::ErrorCode %d)", ec);
  }
}

i2c::ErrorCode HDC302XComponent::write_command(uint16_t command) {
  uint8_t buffer[2];
  buffer[0] = (uint8_t) (command >> 8);    // High byte
  buffer[1] = (uint8_t) (command & 0xFF);  // Low byte
  return this->write(buffer, 2);
}

i2c::ErrorCode HDC302XComponent::write_command_read_data(uint16_t command, uint16_t *data) {
  uint8_t cmd_buffer[2];
  uint8_t data_buffer[3];  // Two bytes for data, one for CRC

  cmd_buffer[0] = (uint8_t) (command >> 8);    // High byte of the command
  cmd_buffer[1] = (uint8_t) (command & 0xFF);  // Low byte of the command

  // Write the command and read the data + CRC
  i2c::ErrorCode ec = this->write(cmd_buffer, 2, false /* stop */);
  if (ec != i2c::NO_ERROR) {
    return ec;
  }
  ec = this->read(data_buffer, 3);
  if (ec != i2c::NO_ERROR) {
    return ec;
  }

  // Calculate CRC
  uint8_t calculated_crc = calculate_CRC8(data_buffer, 2);
  // Check if calculated CRC matches the received CRC
  if (calculated_crc != data_buffer[2]) {
    return i2c::ERROR_CRC;  // CRC mismatch
  }

  // CRC checks out, return the data
  *data = (uint16_t) (data_buffer[0] << 8 | data_buffer[1]);
  return i2c::NO_ERROR;
}

}  // namespace hdc302x
}  // namespace esphome
