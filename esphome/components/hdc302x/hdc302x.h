// python3 -m venv venv
// venv/bin/pip3 install -r requirements_test.txt -r requirements.txt
// venv/bin/pytest tests/components/hdc302x


#pragma once
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace hdc302x {

class HDC302XComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
 
  void set_temperature_sensor(sensor::Sensor *a_sensor) { temperature_sensor_ = a_sensor; }
  void set_humidity_sensor(sensor::Sensor *a_sensor) { humidity_sensor_ = a_sensor; }
  void set_last_error_sensor(sensor::Sensor *a_sensor) { last_error_sensor_ = a_sensor; }

  //void air_calibration();

 protected:
  i2c::ErrorCode readTemperatureHumidityOnDemand(float *temp, float *RH);

  void clearStatusRegister();
  i2c::ErrorCode writeCommand(uint16_t comm);
  i2c::ErrorCode writeCommandReadData(uint16_t command, uint16_t *data);
  i2c::ErrorCode sendCommandReadTRH(uint16_t command, double *temp, double *RH);

  // unused
  i2c::ErrorCode writeCommandData(uint16_t cmd, uint16_t data);
  i2c::ErrorCode readStatus(uint16_t* status);
  i2c::ErrorCode isHeaterOn(bool* isOn);
  i2c::ErrorCode heaterEnable(HDC302x_HeaterPower power);


  
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *humidity_sensor_{nullptr};
  text_sensor::TextSensor *last_error_sensor_{nullptr};
  /*
  enum State : uint8_t {
    IDLE,
    READ_TEMPERATURE,
    READ_HUMIDITY,
  } state_{IDLE};
  */
};

 
/*
 template<typename... Ts> class PMWCS3AirCalibrationAction : public Action<Ts...> {
 public:
  PMWCS3AirCalibrationAction(HDC302XComponent *parent) : parent_(parent) {}

  void play(Ts... x) override { this->parent_->air_calibration(); }

 protected:
  HDC302XComponent *parent_;
};
*/
 
} // namespace hdc302x
} // namespace esphome
