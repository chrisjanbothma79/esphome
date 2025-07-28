// ref: https://github.com/adafruit/Adafruit_HDC302x/blob/main/Adafruit_HDC302x.cpp
//      https://github.com/esphome/esphome/blob/dev/esphome/components/pmwcs3/pmwcs3.cpp
//

#include "hdc302x.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hdc302x {

static const char *const TAG = "hdc302x";

enum HDC302x_Commands {
  SOFT_RESET = 0x30A2,
  READ_MANUFACTURER_ID = 0x3781,
  READ_NIST_ID_SERIAL_BYTES_5_4 =
      0x3683, // Command to read bytes 5 and 4 of the NIST ID
  READ_NIST_ID_SERIAL_BYTES_3_2 =
      0x3684, // Command to read bytes 3 and 2 of the NIST ID
  READ_NIST_ID_SERIAL_BYTES_1_0 =
      0x3685,                    // Command to read bytes 1 and 0 of the NIST ID
  ACCESS_OFFSETS = 0xA004,       // Command to write/read offsets
  SET_HEATER_POWER = 0x306E,     // Command to set heater power
  ENABLE_HEATER = 0x306D,        // Command to enable heater
  DISABLE_HEATER = 0x3066,       // Command to disable heater
  READ_STATUS_REGISTER = 0xF32D, // Command to read the status register
  CLEAR_STATUS_REGISTER = 0x3041, // Command to clear the status register
  MEASUREMENT_READOUT_AUTO_MODE = 0xE000, // Measurement Readout Auto Mode
  SET_LOW_ALERT = 0x6100,  // Configure ALERT Thresholds for Set Low Alert
  SET_HIGH_ALERT = 0x611D, // Configure ALERT Thresholds for Set High Alert
  CLR_LOW_ALERT = 0x610B,  // Configure ALERT Thresholds for Clear Low Alert
  CLR_HIGH_ALERT = 0x6116  // Configure ALERT Thresholds for Clear High Alert
};
typedef enum {
  TRIGGERMODE_LP0 = 0x2400, // Trigger-On Demand Mode, Low Power Mode 0
  TRIGGERMODE_LP1 = 0x240B, // Trigger-On Demand Mode, Low Power Mode 1
  TRIGGERMODE_LP2 = 0x2416, // Trigger-On Demand Mode, Low Power Mode 2
  TRIGGERMODE_LP3 = 0x24FF  // Trigger-On Demand Mode, Low Power Mode 3
} hdcTriggerMode_t;
  
void HDC302XComponent::setup() {
  i2c::ErrorCode ec = writeCommand(HDC302x_Commands::SOFT_RESET);
  if (ec != i2c::NO_ERROR) {
    status_set_warning("Reset command failed");
    ESP_LOGW(TAG, "Reset command failed (i2c::ErrorCode %d)", ec);
    return;
  }
  clearStatusRegister();

  uint16_t manufacturerID = 0;
  ec = writeCommandReadData(HDC302x_Commands::READ_MANUFACTURER_ID, manufacturerID);
  if (ec != i2c::NO_ERROR) {
    status_set_warning("Read manufacturerID failed");
    ESP_LOGW(TAG, "Read manufacturerID failed (i2c::ErrorCode %d)", ec);
  } else if (manufacturerID != 0x3000) {
    status_set_warning("Got wrong manufacturer id");
    ESP_LOGW(TAG, "Wrong manufacturer ID (got %x expected %x)", manufacturerID, 0x3000);
  }

  setAutoMode(EXIT_AUTO_MODE);
}

bool Adafruit_HDC302x::readTemperatureHumidityOnDemand(double &temp, double &RH) {
  hdcTriggerMode_t mode = TRIGGERMODE_LP0; // LP0 is lowest noise
  return sendCommandReadTRH(static_cast<uint16_t>(mode), temp, RH);
}
  
  // UTILITIES
  // From https://github.com/adafruit/Adafruit_HDC302x/blob/main/Adafruit_HDC302x.cpp
  //
  
void HDC302XComponent::clearStatusRegister() {
  i2c::ErrorCode ec = writeCommand(HDC302x_Commands::CLEAR_STATUS_REGISTER);
  if (ec != i2c::NO_ERROR) {
    status_set_warning("Clear status register command failed");
    ESP_LOGW(TAG, "Clear status reg command failed (i2c::ErrorCode %d)", ec);
  }
}
void HDC302XComponent::setAutoMode(hdcAutoMode_t mode) {
  i2c::ErrorCode ec = writeCommand(mode);
  if (ec != i2c::NO_ERROR) {
    status_set_warning("Set auto mode failed");
    ESP_LOGW(TAG, "Set auto mode failed (i2c::ErrorCode %d)", ec);
  }
}
 
i2c::ErrorCode HDC302XComponent::writeCommand(uint16_t comm) {
  uint8_t buffer[2];
  buffer[0] = (uint8_t)(command >> 8);   // High byte
  buffer[1] = (uint8_t)(command & 0xFF); // Low byte
  return write(buffer, 2);
}
i2c::ErrorCode Adafruit_HDC302x::writeCommandReadData(uint16_t command, uint16_t &data) {
  uint8_t cmd_buffer[2];
  uint8_t data_buffer[3]; // Two bytes for data, one for CRC

  cmd_buffer[0] = (uint8_t)(command >> 8);   // High byte of the command
  cmd_buffer[1] = (uint8_t)(command & 0xFF); // Low byte of the command

  // Write the command and read the data + CRC
  i2c::ErrorCode ec = write(cmd_buffer, 2, false /* stop */);
  if (ec != i2c::NO_ERROR) {
    return ec;
  }
  ec = read(data_buffer, 3);
  if (ec != i2c::NO_ERROR) {
    return ec;
  }
  
  // Calculate CRC
  uint8_t calculated_crc = calculateCRC8(data_buffer, 2);
  // Check if calculated CRC matches the received CRC
  if (calculated_crc != data_buffer[2]) {
    return i2c::ERROR_CRC; // CRC mismatch
  }

  // CRC checks out, return the data
  data = (uint16_t)(data_buffer[0] << 8 | data_buffer[1]);
  return i2c::NO_ERROR;
}

i2c::ErrorCode Adafruit_HDC302x::writeCommandData(uint16_t cmd, uint16_t data) {
  uint8_t buffer[5];
  buffer[0] = (uint8_t)(cmd >> 8);          // High byte of the command
  buffer[1] = (uint8_t)(cmd & 0xFF);        // Low byte of the command
  buffer[2] = (uint8_t)(data >> 8);         // High byte of the data
  buffer[3] = (uint8_t)(data & 0xFF);       // Low byte of the data
  buffer[4] = calculateCRC8(buffer + 2, 2); // Calculate CRC for the data

  i2c::ErrorCode ec = write(buffer, 5);
  return ec;
}

  
i2c::ErrorCode Adafruit_HDC302x::sendCommandReadTRH(uint16_t command, double &temp, double &RH) {
  // Trigger the temperature and humidity measurement
  i2c::ErrorCode ec = writeCommand(command);
  if (ec != i2c::NO_ERROR) {
    //ESP_LOGW(TAG, "Set auto mode failed (i2c::ErrorCode %d)", ec);
    return ec;
  }

  // Wait for conversion (tmeas in datasheet table 7.5  LP0 takes 12.5ms.  Add a bit more to be sure)
  delay(20);

  // Read results
  uint8_t buffer[6];
  ec = read(buffer, 6);
  if (ec != i2c::NO_ERROR) {
    return ec;
  }

  // Validate CRC for temperature data
  if (calculateCRC8(buffer, 2) != buffer[2]) {
    return i2c::ERROR_CRC; // CRC mismatch
  }

  // Validate CRC for humidity data
  if (calculateCRC8(buffer + 3, 2) != buffer[5]) {
    return i2c::ERROR_CRC; // CRC mismatch
  }

  uint16_t rawTemperature = (buffer[0] << 8) | buffer[1];
  uint16_t rawHumidity = (buffer[3] << 8) | buffer[4];

  // Convert raw temperature data to degrees Celsius
  temp = ((rawTemperature / 65535.0) * 175.0) - 45.0;

  // Convert raw humidity data to percentage
  RH = (rawHumidity / 65535.0) * 100.0;

  return i2c::NO_ERROR;
}

bool Adafruit_HDC302x::isHeaterOn() {
  uint16_t status = readStatus();
  return (status & (1UL << 13));
}

bool Adafruit_HDC302x::heaterEnable(HDC302x_HeaterPower power) {
  if (power == HEATER_OFF) {
    return writeCommand(HDC302x_Commands::DISABLE_HEATER);
  } else {
    if (!writeCommand(HDC302x_Commands::ENABLE_HEATER)) {
      return false;
    }
    return writeCommandData(HDC302x_Commands::SET_HEATER_POWER, power);
  }
}

uint16_t Adafruit_HDC302x::readStatus() {
  uint16_t status = 0;
  writeCommandReadData(HDC302x_Commands::READ_STATUS_REGISTER, status);
  return status;
}

uint16_t Adafruit_HDC302x::readManufacturerID() {
  uint16_t manufacturerID = 0;
  if (!writeCommandReadData(HDC302x_Commands::READ_MANUFACTURER_ID,
                            manufacturerID)) {
    return 0; // Return 0 if there is an error
  }
  return manufacturerID;
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
uint8_t Adafruit_HDC302x::calculateCRC8(const uint8_t *data, int len) {
  uint8_t crc = 0xFF; // Typical initial value
  for (int i = 0; i < len; i++) {
    crc ^= data[i];               // XOR byte into least sig. byte of crc
    for (int j = 8; j > 0; j--) { // Loop over each bit
      if (crc & 0x80) {           // If the uppermost bit is 1...
        crc = (crc << 1) ^ 0x31;  // Polynomial used by HDC302x
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc; // Final XOR value can also be applied if specified by device
}  

void PMWCS3Component::update() { this->read_data_(); }

float PMWCS3Component::get_setup_priority() const { return setup_priority::DATA; }

void PMWCS3Component::dump_config() {
  ESP_LOGCONFIG(TAG, "PMWCS3");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
  }
  LOG_UPDATE_INTERVAL(this);
  LOG_SENSOR("  ", "e25", this->e25_sensor_);
  LOG_SENSOR("  ", "ec", this->ec_sensor_);
  LOG_SENSOR("  ", "temperature", this->temperature_sensor_);
  LOG_SENSOR("  ", "vwc", this->vwc_sensor_);
}

  
}
}

