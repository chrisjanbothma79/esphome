#pragma once
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace hdc302x {

class HDC302XComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  void loop() override;
 
  void set_temperature_sensor(sensor::Sensor *a_sensor) { temperature_sensor_ = a_sensor; }
  void set_humidity_sensor(sensor::Sensor *a_sensor) { humidity_sensor_ = a_sensor; }
  void set_last_error_sensor(sensor::Sensor *a_sensor) { last_error_sensor_ = a_sensor; }

  void air_calibration();

 protected:
  void read_data_();
  bool reset_();

  bool writeCommand(uint16_t comm);

  
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *humidity_sensor_{nullptr};
  sensor::Sensor *last_error_sensor_{nullptr};
  enum State : uint8_t {
    IDLE,
    READ_TEMPERATURE,
    READ_HUMIDITY,
  } state_{IDLE};
};

 
template<typename... Ts> class PMWCS3AirCalibrationAction : public Action<Ts...> {
 public:
  PMWCS3AirCalibrationAction(HDC302XComponent *parent) : parent_(parent) {}

  void play(Ts... x) override { this->parent_->air_calibration(); }

 protected:
  HDC302XComponent *parent_;
};

 
} // namespace hdc302x
} // namespace esphome
