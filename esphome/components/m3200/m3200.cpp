#include "esphome/core/log.h"
#include "m3200.h"

namespace esphome {
namespace m3200 {

static const char *const TAG = "m3200.sensor";

// Device I2C address. This address is fixed.
static const uint8_t M3200_I2C_ADDR_DEFAULT = 0x28;   //TODO: Is this settable? Should I allow the user to define it?

//Status byte definitions
static const uint8_t M3200_STATUS_OK = 0x00;
static const uint8_t M3200_STATUS_STALE = 0x80;
static const uint8_t M3200_STATUS_FAULT = 0xC0;

// The number of times to retry an I2C transaction before giving up. I have only seen 1
// failure before a successful read.
static const uint8_t M3200_I2C_RETRY_COUNT = 10;

void M3200::setup() {
  //Precalculate the slope of the calibration curve so that we don't need to do it every time.
  this->slope_ = (float(this->fs_pressure_)-(this->min_pressure_))/(15000. - 1000.);
}

void M3200::update() {
  uint8_t i = 0;
  i2c::ErrorCode return_code;
  uint8_t read_buffer[4];
  uint16_t raw_pressure = 0;
  uint16_t raw_temperature = 0;
  
  float pressure;
  float temperature;
  
  for (i=0; i<M3200_I2C_RETRY_COUNT; i++) {
    //Read data from the device
    return_code = this->read(read_buffer, 4);
    
    if ((read_buffer[0] & 0xC0) == M3200_STATUS_OK) {
      //Device indicates the data is good.
      raw_pressure = ((read_buffer[0]&0x3F) << 8) | read_buffer[1];
      raw_temperature = (read_buffer[2] << 3) | ((read_buffer[3] & 0xE0)>>5);
      //ESP_LOGD(TAG, "pressure: %d", raw_pressure);
      //ESP_LOGD(TAG, "temperature: %d", raw_temperature);
      
      pressure = (this->slope_)*(float(raw_pressure)-1000.) + (this->min_pressure_);
      temperature = ((200.)/(2048.))*float(raw_temperature) - 50.;
      
      if (this->pressure_sensor_ != nullptr) {
        this->pressure_sensor_->publish_state(pressure);
      }
      
      if (this->temperature_sensor_ != nullptr) {
        this->temperature_sensor_->publish_state(temperature);
      }

      return;
    } 
    else if ((read_buffer[0] & 0xC0) == M3200_STATUS_STALE) {
      // The device indicates that the data is stale. This means we already read this data. 
      // If this happens, we retry to try to get a good reading.
      //ESP_LOGD(TAG, "Stale Data");
    }
    else if ((read_buffer[0] & 0xC0) == M3200_STATUS_FAULT) {
      // Device indicates a sensor fault. Not sure what this means exactly, but it is probably bad.
      // A power cycle might fix the device in this state.
      ESP_LOGE(TAG, "Sensor Fault");
      this->mark_failed();
      return;
    }
    else {
      // We should never get here. This means that the status bits were invalid (0b01) This probably
      // indicates a fault on the i2c bus. We will retry here and see if it gets better.
      ESP_LOGW(TAG, "Undefined sensor status");
    }
  }
  
  // If we get here, the device tried to get data 10 times and got stale data or an invalid status
  // every time. I have only seen it fail once from stale data, so 10 failures probably indicates a
  // i2c bus problem. If this happens, we log an error but continue. I considered marking the device
  // failed if this happens, but it is possible to recover from a bus failure, so I don't want to 
  // mark the device failed unnessecarially.
  ESP_LOGE(TAG, "Ten read failures in a row. Device is probably failed.");
  //this->mark_failed();
}

void M3200::dump_config() {
  ESP_LOGCONFIG(TAG, "M3200:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    // TODO: The sensor might get failed here.
    ESP_LOGCONFIG(TAG, "  M3200 is indicating a failure. Power cycle might fix it.");
  }
  LOG_UPDATE_INTERVAL(this);
  ESP_LOGCONFIG(TAG, "  Full Scale Pressure: %d psi", this->fs_pressure_);
  ESP_LOGCONFIG(TAG, "  Minimum Pressure: %d psi", this->min_pressure_);
}

}  // namespace m3200
}  // namespace esphome
