#pragma once

#include <list>

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace vl53l1x {

enum DistanceMode { SHORT, MEDIUM, LONG, UNKNOWN };

enum RangeStatus : uint8_t {
  RANGE_VALID = 0,

  // "sigma estimator check is above the internal defined threshold"
  // (sigma = standard deviation of measurement)
  SIGMA_FAIL = 1,

  // "signal value is below the internal defined threshold"
  SIGNAL_FAIL = 2,

  // "Target is below minimum detection threshold."
  RANGE_VALID_MIN_RANGE_CLIPPED = 3,

  // "phase is out of bounds"
  // (nothing detected in range; try a longer distance mode if applicable)
  OUT_OF_BOUNDS_FAIL = 4,

  // "HW or VCSEL failure"
  HARDWARE_FAIL = 5,

  // "The Range is valid but the wraparound check has not been done."
  RANGE_VALID_NO_WRAP_CHECK_FAIL = 6,

  // "Wrapped target, not matching phases"
  // "no matching phase in other VCSEL period timing."
  WRAP_TARGET_FAIL = 7,

  // "Specific to lite ranging."
  // should never occur with this lib (which uses low power auto ranging,
  // as the API does)
  XTALK_SIGNAL_FAIL = 9,

  // "1st interrupt when starting ranging in back to back mode. Ignore
  // data."
  // should never occur with this lib
  SYNCHRONIZATION_INT = 10,

  // "Target is below minimum detection threshold."
  MIN_RANGE_FAIL = 13,

  // "No Update."
  NONE = 255,
};

enum SetupState {
  SETUP_STATE_INIT,
  SETUP_STATE_AWAIT_ENABLE,
  SETUP_STATE_BEGIN_SOFT_RESET,
  SETUP_STATE_AWAIT_SOFT_RESET,
  SETUP_STATE_AWAIT_FIRMWARE_STATUS,
  SETUP_STATE_COMPLETE,
  SETUP_STATE_FAILED
};

#pragma pack(push, 1)
struct ResultBuffer {
  uint8_t range_status;
  uint8_t report_status;  // not used
  uint8_t stream_count;
  uint16_t dss_actual_effective_spads_sd0;
  uint16_t peak_signal_count_rate_mcps_sd0;  // not used
  uint16_t ambient_count_rate_mcps_sd0;
  uint16_t sigma_sd0;  // not used
  uint16_t phase_sd0;  // not used
  uint16_t final_crosstalk_corrected_range_mm_sd0;
  uint16_t peak_signal_count_rate_crosstalk_corrected_mcps_sd0;
};
#pragma pack(pop)

struct RangingData {
  uint16_t range_mm;
  RangeStatus range_status;
  float peak_signal_count_rate_mcps;
  float ambient_count_rate_mcps;
};

class VL53L1XSensor : public sensor::Sensor, public PollingComponent, public i2c::I2CDevice {
 public:
  VL53L1XSensor();

  void setup() override;

  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  void update() override;

  void loop() override;

  void set_timeout_us(uint32_t timeout_us) { this->timeout_us_ = timeout_us; }
  void set_distance_mode(DistanceMode distance_mode) { this->distance_mode_ = distance_mode; }
  void set_measurement_timing_budget_us(uint32_t budget_us) { this->measurement_timing_budget_us_ = budget_us; }
  void set_enable_pin(GPIOPin *enable) { this->enable_pin_ = enable; }
  void set_region_of_interest(uint8_t width, uint8_t height) {
    this->roi_width_ = width;
    this->roi_height_ = height;
  }
  void set_region_of_interest_center_spad(uint8_t center_spad) { this->roi_center_spad_ = center_spad; }

 protected:
  void next_setup_task_();
  bool check_timeout_(uint32_t timeout_us);

  bool apply_distance_mode_();
  bool apply_measurement_timing_budget_(uint32_t budget_us);
  uint32_t get_measurement_timing_budget_();
  void apply_roi_size_();
  void apply_roi_center_();
  void setup_manual_calibration_();
  ResultBuffer read_results_();
  void update_dss_(const ResultBuffer &results);
  RangingData get_ranging_data_(const ResultBuffer &results);

  uint32_t decode_timeout_(uint16_t reg_val);
  uint16_t encode_timeout_(uint32_t timeout_mclks);
  uint32_t timeout_mclks_to_microseconds_(uint32_t timeout_mclks, uint32_t macro_period_us);
  uint32_t timeout_microseconds_to_mclks_(uint32_t timeout_us, uint32_t macro_period_us);
  uint32_t calc_macro_period_(uint8_t vcsel_period);
  float count_rate_fixed_to_float_(uint16_t count_rate_fixed);
  bool data_ready_();

  uint16_t read_register16_16_(uint16_t reg);
  void write_register16_16_(uint16_t reg, uint16_t value);

  SetupState current_setup_state_{SETUP_STATE_INIT};
  uint32_t last_setup_task_us_{0};
  uint8_t final_address_{0};

  GPIOPin *enable_pin_{nullptr};
  bool waiting_for_interrupt_{false};
  bool calibrated_{false};

  uint16_t fast_osc_frequency_;

  uint16_t timeout_us_{};
  DistanceMode distance_mode_{LONG};              // default to long range
  uint32_t measurement_timing_budget_us_{50000};  // default 50ms
  uint8_t roi_width_{16}, roi_height_{16};        // default to 16x16 ROI
  uint8_t roi_center_spad_{199};                  // default to center spad

  static std::list<VL53L1XSensor *> vl53_sensors;   // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
  static bool enable_pin_setup_complete;            // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
  static VL53L1XSensor *currently_enabling_sensor;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
};

}  // namespace vl53l1x
}  // namespace esphome
