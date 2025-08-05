//
//  This module is based on code from https://github.com/adafruit/Adafruit_HDC302x
//
//
// python3 -m venv venv
// script/setup
//   and/or
// venv/bin/pip3 install -r requirements_test.txt -r requirements.txt
// source venv/bin/activate
// script/test_build_components -c hdc302x

#pragma once
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace hdc302x {

typedef enum {
  HEATER_OFF = 0x0000,
  HEATER_QUARTER_POWER = 0x009F,
  HEATER_HALF_POWER = 0x03FF,
  HEATER_FULL_POWER = 0x3FFF
} HDC302x_HeaterPower;

class HDC302XComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  void set_temperature_sensor(sensor::Sensor *a_sensor) { temperature_sensor_ = a_sensor; }
  void set_humidity_sensor(sensor::Sensor *a_sensor) { humidity_sensor_ = a_sensor; }
  void set_last_error_sensor(text_sensor::TextSensor *a_sensor) { last_error_sensor_ = a_sensor; }
  void set_bus_name(std::string name) { bus_name_ = name; }

 protected:
  i2c::ErrorCode readTemperatureHumidityOnDemand(float *temp, float *RH);

  void clearStatusRegister();
  i2c::ErrorCode writeCommand(uint16_t comm);
  i2c::ErrorCode writeCommandReadData(uint16_t command, uint16_t *data);
  i2c::ErrorCode sendCommandReadTRH(uint16_t command, float *temp, float *RH);

  // unused.  keeping for whenever someone supports the heater
  i2c::ErrorCode writeCommandData(uint16_t cmd, uint16_t data);
  i2c::ErrorCode readStatus(uint16_t *status);
  i2c::ErrorCode isHeaterOn(bool *isOn);
  i2c::ErrorCode heaterEnable(HDC302x_HeaterPower power);

  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *humidity_sensor_{nullptr};
  text_sensor::TextSensor *last_error_sensor_{nullptr};
  std::string bus_name_;
};

}  // namespace hdc302x
}  // namespace esphome
