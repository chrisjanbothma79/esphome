#include "vl53l1x_sensor.h"
#include "esphome/core/log.h"

/*
 * Most of the code in this integration is based on the VL53L1x library
 * by Pololu (Pololu Corporation), which in turn is based on the VL53L1X
 * API from ST.
 *
 * For more information about licensing, please view the included LICENSE.txt file
 * in the vl53l1x integration directory.
 */

namespace esphome {
namespace vl53l1x {

static const char *const TAG = "vl53l1x";

static const uint32_t TIMING_GUARD = 4528;
static const uint16_t TARGET_RATE = 0x0A00;

// register addresses from API vl53l1x_register_map.h
enum RegAddr : uint16_t {
  SOFT_RESET = 0x0000,
  I2C_SXXXX_DEVICE_ADDRESS = 0x0001,
  OSC_MEASURED_FAST_OSC_FREQUENCY = 0x0006,
  OSC_MEASURED_FAST_OSC_FREQUENCY_HI = 0x0006,
  OSC_MEASURED_FAST_OSC_FREQUENCY_LO = 0x0007,
  VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND = 0x0008,
  VHV_CONFIG_INIT = 0x000B,
  ALGO_PART_TO_PART_RANGE_OFFSET_MM = 0x001E,
  ALGO_PART_TO_PART_RANGE_OFFSET_MM_HI = 0x001E,
  ALGO_PART_TO_PART_RANGE_OFFSET_MM_LO = 0x001F,
  MM_CONFIG_OUTER_OFFSET_MM = 0x0022,
  MM_CONFIG_OUTER_OFFSET_MM_HI = 0x0022,
  MM_CONFIG_OUTER_OFFSET_MM_LO = 0x0023,
  DSS_CONFIG_TARGET_TOTAL_RATE_MCPS = 0x0024,
  DSS_CONFIG_TARGET_TOTAL_RATE_MCPS_HI = 0x0024,
  DSS_CONFIG_TARGET_TOTAL_RATE_MCPS_LO = 0x0025,
  PAD_I2C_HV_EXTSUP_CONFIG = 0x002E,
  GPIO_TIO_HV_STATUS = 0x0031,
  SIGMA_ESTIMATOR_EFFECTIVE_PULSE_WIDTH_NS = 0x0036,
  SIGMA_ESTIMATOR_EFFECTIVE_AMBIENT_WIDTH_NS = 0x0037,
  ALGO_CROSSTALK_COMPENSATION_VALID_HEIGHT_MM = 0x0039,
  ALGO_RANGE_IGNORE_VALID_HEIGHT_MM = 0x003E,
  ALGO_RANGE_MIN_CLIP = 0x003F,
  ALGO_CONSISTENCY_CHECK_TOLERANCE = 0x0040,
  CAL_CONFIG_VCSEL_START = 0x0047,
  PHASECAL_CONFIG_TIMEOUT_MACROP = 0x004B,
  PHASECAL_CONFIG_OVERRIDE = 0x004D,
  DSS_CONFIG_ROI_MODE_CONTROL = 0x004F,
  SYSTEM_THRESH_RATE_HIGH = 0x0050,
  SYSTEM_THRESH_RATE_HIGH_HI = 0x0050,
  SYSTEM_THRESH_RATE_HIGH_LO = 0x0051,
  SYSTEM_THRESH_RATE_LOW = 0x0052,
  SYSTEM_THRESH_RATE_LOW_HI = 0x0052,
  SYSTEM_THRESH_RATE_LOW_LO = 0x0053,
  SYSTEM_INTERRUPT_CLEAR = 0x0086,
  DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT = 0x0054,
  DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_HI = 0x0054,
  DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT_LO = 0x0055,
  DSS_CONFIG_APERTURE_ATTENUATION = 0x0057,
  MM_CONFIG_TIMEOUT_MACROP_A = 0x005A,
  MM_CONFIG_TIMEOUT_MACROP_A_HI = 0x005A,
  MM_CONFIG_TIMEOUT_MACROP_A_LO = 0x005B,
  MM_CONFIG_TIMEOUT_MACROP_B = 0x005C,
  MM_CONFIG_TIMEOUT_MACROP_B_HI = 0x005C,
  MM_CONFIG_TIMEOUT_MACROP_B_LO = 0x005D,
  RANGE_CONFIG_TIMEOUT_MACROP_A = 0x005E,
  RANGE_CONFIG_TIMEOUT_MACROP_A_HI = 0x005E,
  RANGE_CONFIG_TIMEOUT_MACROP_A_LO = 0x005F,
  RANGE_CONFIG_VCSEL_PERIOD_A = 0x0060,
  RANGE_CONFIG_TIMEOUT_MACROP_B = 0x0061,
  RANGE_CONFIG_TIMEOUT_MACROP_B_HI = 0x0061,
  RANGE_CONFIG_TIMEOUT_MACROP_B_LO = 0x0062,
  RANGE_CONFIG_VCSEL_PERIOD_B = 0x0063,
  RANGE_CONFIG_SIGMA_THRESH = 0x0064,
  RANGE_CONFIG_SIGMA_THRESH_HI = 0x0064,
  RANGE_CONFIG_SIGMA_THRESH_LO = 0x0065,
  RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS = 0x0066,
  RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_HI = 0x0066,
  RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS_LO = 0x0067,
  RANGE_CONFIG_VALID_PHASE_HIGH = 0x0069,
  SYSTEM_GROUPED_PARAMETER_HOLD_0 = 0x0071,
  SYSTEM_SEED_CONFIG = 0x0077,
  SD_CONFIG_WOI_SD0 = 0x0078,
  SD_CONFIG_WOI_SD1 = 0x0079,
  SD_CONFIG_INITIAL_PHASE_SD0 = 0x007A,
  SD_CONFIG_INITIAL_PHASE_SD1 = 0x007B,
  SYSTEM_GROUPED_PARAMETER_HOLD_1 = 0x007C,
  SD_CONFIG_QUANTIFIER = 0x007E,
  ROI_CONFIG_USER_ROI_CENTRE_SPAD = 0x007F,
  ROI_CONFIG_USER_ROI_REQUESTED_GLOBAL_XY_SIZE = 0x0080,
  SYSTEM_SEQUENCE_CONFIG = 0x0081,
  SYSTEM_GROUPED_PARAMETER_HOLD = 0x0082,
  SYSTEM_MODE_START = 0x0087,
  RESULT_RANGE_STATUS = 0x0089,
  RESULT_REPORT_STATUS = 0x008A,
  RESULT_STREAM_COUNT = 0x008B,
  RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0 = 0x008C,
  RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_HI = 0x008C,
  RESULT_DSS_ACTUAL_EFFECTIVE_SPADS_SD0_LO = 0x008D,
  RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0 = 0x008E,
  RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_HI = 0x008E,
  RESULT_PEAK_SIGNAL_COUNT_RATE_MCPS_SD0_LO = 0x008F,
  RESULT_AMBIENT_COUNT_RATE_MCPS_SD0 = 0x0090,
  RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_HI = 0x0090,
  RESULT_AMBIENT_COUNT_RATE_MCPS_SD0_LO = 0x0091,
  RESULT_SIGMA_SD0 = 0x0092,
  RESULT_SIGMA_SD0_HI = 0x0092,
  RESULT_SIGMA_SD0_LO = 0x0093,
  RESULT_PHASE_SD0 = 0x0094,
  RESULT_PHASE_SD0_HI = 0x0094,
  RESULT_PHASE_SD0_LO = 0x0095,
  RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0 = 0x0096,
  RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_HI = 0x0096,
  RESULT_FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0_LO = 0x0097,
  RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0 = 0x0098,
  RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_HI = 0x0098,
  RESULT_PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0_LO = 0x0099,
  PHASECAL_RESULT_VCSEL_START = 0x00D8,
  FIRMWARE_SYSTEM_STATUS = 0x00E5,
  IDENTIFICATION_MODEL_ID = 0x010F,
};

std::list<VL53L1XSensor *> VL53L1XSensor::vl53_sensors;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
bool VL53L1XSensor::enable_pin_setup_complete = false;   // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
VL53L1XSensor *VL53L1XSensor::currently_enabling_sensor =
    nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

VL53L1XSensor::VL53L1XSensor() { VL53L1XSensor::vl53_sensors.push_back(this); }

void VL53L1XSensor::dump_config() {
  LOG_SENSOR("", "VL53L1X", this);
  LOG_UPDATE_INTERVAL(this);
  LOG_I2C_DEVICE(this);
  if (this->enable_pin_ != nullptr) {
    LOG_PIN("  Enable Pin: ", this->enable_pin_);
  }
  ESP_LOGCONFIG(TAG, "  Timeout: %u%s", this->timeout_us_, this->timeout_us_ > 0 ? "us" : " (no timeout)");
  switch (this->distance_mode_) {
    case SHORT:
      ESP_LOGCONFIG(TAG, "Distance Mode: Short");
      break;
    case MEDIUM:
      ESP_LOGCONFIG(TAG, "Distance Mode: Medium");
      break;
    case LONG:
      ESP_LOGCONFIG(TAG, "Distance Mode: Long");
      break;
    default:
      ESP_LOGE(TAG, "Invalid distance mode selection!");
      break;
  }
  ESP_LOGCONFIG(TAG, "  Measurement Timing Budget: %uus", this->measurement_timing_budget_us_);
}

// Initialize sensor using settings taken mostly from VL53L1_DataInit() and
// VL53L1_StaticInit().
void VL53L1XSensor::setup() {
  if (!VL53L1XSensor::enable_pin_setup_complete) {
    for (auto &vl53_sensor : vl53_sensors) {
      if (vl53_sensor->enable_pin_ != nullptr) {
        // Set enable pin as OUTPUT and disable the enable pin to force vl53 to HW Standby mode
        vl53_sensor->enable_pin_->setup();
        vl53_sensor->enable_pin_->digital_write(false);
      }
    }
  }

  this->next_setup_task_();
}

void VL53L1XSensor::next_setup_task_() {
  uint16_t model_id = 0;

  switch (this->current_setup_state_) {
    case SETUP_STATE_INIT:
      if (this->enable_pin_ != nullptr) {
        if (VL53L1XSensor::currently_enabling_sensor != nullptr) {
          // Have to wait for another sensor to finiish enabling before
          // we can go
          return;
        }
        // Enable the enable pin to cause FW boot (to get back to 0x29 default address)
        this->enable_pin_->digital_write(true);
        this->last_setup_task_us_ = micros();
        this->current_setup_state_ = SETUP_STATE_AWAIT_ENABLE;
        return;
      }
      this->current_setup_state_ = SETUP_STATE_BEGIN_SOFT_RESET;
      this->next_setup_task_();  // synchronously start the next task; we had nothing to do
      break;
    case SETUP_STATE_AWAIT_ENABLE:
      // wait at least 100 ms
      if (!this->check_timeout_(100000)) {
        return;
      }
      this->current_setup_state_ = SETUP_STATE_BEGIN_SOFT_RESET;
      this->next_setup_task_();  // synchronously start the next task; we had nothing to do
      break;
    case SETUP_STATE_BEGIN_SOFT_RESET:
      // Save the i2c address we want and force it to use the default 0x29
      // until we finish setup, then re-address to final desired address.
      this->final_address_ = address_;
      this->set_i2c_address(0x29);

      // check model ID and module type registers (values specified in datasheet)
      model_id = this->read_register16_16_(IDENTIFICATION_MODEL_ID);
      if (model_id != 0xEACC) {
        ESP_LOGE(TAG, "'%s' - model ID mismatch: %04x", this->name_.c_str(), model_id);
        this->current_setup_state_ = SETUP_STATE_FAILED;
        this->mark_failed();
        return;
      }

      // VL53L1_software_reset() begin

      this->reg16(SOFT_RESET) = 0x00;
      this->last_setup_task_us_ = micros();
      this->current_setup_state_ = SETUP_STATE_AWAIT_SOFT_RESET;
      break;
    case SETUP_STATE_AWAIT_SOFT_RESET:
      // wait at least 100 ms
      if (!this->check_timeout_(100000)) {
        return;
      }
      this->reg16(SOFT_RESET) = 0x01;
      this->last_setup_task_us_ = micros();
      this->current_setup_state_ = SETUP_STATE_AWAIT_FIRMWARE_STATUS;
      break;
    case SETUP_STATE_AWAIT_FIRMWARE_STATUS:
      // give it some time to boot; otherwise the sensor NACKs during the readReg()
      // call below and the Arduino 101 doesn't seem to handle that well
      if (!this->check_timeout_(1000000)) {
        return;
      }

      // VL53L1_poll_for_boot_completion() begin
      if ((this->reg16(FIRMWARE_SYSTEM_STATUS).get() & 0x01) == 0x00) {
        return;
      }

      // VL53L1_poll_for_boot_completion() end

      // VL53L1_software_reset() end

      // VL53L1_DataInit() begin

      // sensor uses 1V8 mode for I/O by default; switch to 2V8 mode
      this->reg16(PAD_I2C_HV_EXTSUP_CONFIG) |= 0x01;

      // store oscillator info for later use
      fast_osc_frequency_ = this->read_register16_16_(OSC_MEASURED_FAST_OSC_FREQUENCY);

      // VL53L1_DataInit() end

      // VL53L1_StaticInit() begin

      // Note that the API does not actually apply the configuration settings below
      // when VL53L1_StaticInit() is called: it keeps a copy of the sensor's
      // register contents in memory and doesn't actually write them until a
      // measurement is started. Writing the configuration here means we don't have
      // to keep it all in memory and avoids a lot of redundant writes later.

      // the API sets the preset mode to LOWPOWER_AUTONOMOUS here:
      // VL53L1_set_preset_mode() begin

      // VL53L1_preset_mode_standard_ranging() begin

      // values labeled "tuning parm default" are from vl53l1_tuning_parm_defaults.h
      // (API uses these in VL53L1_init_tuning_parm_storage_struct())

      // static config
      // API resets PAD_I2C_HV_EXTSUP_CONFIG here, but maybe we don't want to do
      // that? (seems like it would disable 2V8 mode)
      this->write_register16_16_(DSS_CONFIG_TARGET_TOTAL_RATE_MCPS,
                                 TARGET_RATE);  // should already be this value after reset
      this->reg16(GPIO_TIO_HV_STATUS) = 0x02;
      this->reg16(SIGMA_ESTIMATOR_EFFECTIVE_PULSE_WIDTH_NS) = 8;     // tuning parm default
      this->reg16(SIGMA_ESTIMATOR_EFFECTIVE_AMBIENT_WIDTH_NS) = 16;  // tuning parm default
      this->reg16(ALGO_CROSSTALK_COMPENSATION_VALID_HEIGHT_MM) = 0x01;
      this->reg16(ALGO_RANGE_IGNORE_VALID_HEIGHT_MM) = 0xff;
      this->reg16(ALGO_RANGE_MIN_CLIP) = 0;               // tuning parm default
      this->reg16(ALGO_CONSISTENCY_CHECK_TOLERANCE) = 2;  // tuning parm default

      // general config
      this->write_register16_16_(SYSTEM_THRESH_RATE_HIGH, 0x0000);
      this->write_register16_16_(SYSTEM_THRESH_RATE_LOW, 0x0000);
      this->reg16(DSS_CONFIG_APERTURE_ATTENUATION) = 0x38;

      // timing config
      // most of these settings will be determined later by distance and timing
      // budget configuration
      this->write_register16_16_(RANGE_CONFIG_SIGMA_THRESH, 360);                   // tuning parm default
      this->write_register16_16_(RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT_MCPS, 192);  // tuning parm default

      // dynamic config

      this->reg16(SYSTEM_GROUPED_PARAMETER_HOLD_0) = 0x01;
      this->reg16(SYSTEM_GROUPED_PARAMETER_HOLD_1) = 0x01;
      this->reg16(SD_CONFIG_QUANTIFIER) = 2;  // tuning parm default

      // VL53L1_preset_mode_standard_ranging() end

      // from VL53L1_preset_mode_timed_ranging_*
      // GPH is 0 after reset, but writing GPH0 and GPH1 above seem to set GPH to 1,
      // and things don't seem to work if we don't set GPH back to 0 (which the API
      // does here).
      this->reg16(SYSTEM_GROUPED_PARAMETER_HOLD) = 0x00;
      this->reg16(SYSTEM_SEED_CONFIG) = 1;  // tuning parm default

      // from VL53L1_config_low_power_auto_mode
      this->reg16(SYSTEM_SEQUENCE_CONFIG) = 0x8b;  // VHV, PHASECAL, DSS1, RANGE
      this->write_register16_16_(DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT, 200 << 8);
      this->reg16(DSS_CONFIG_ROI_MODE_CONTROL) = 2;  // REQUESTED_EFFFECTIVE_SPADS

      // VL53L1_set_preset_mode() end

      // default to 50 ms timing budget
      // note that this is different than what the API defaults to
      this->apply_distance_mode_();
      this->apply_measurement_timing_budget_(measurement_timing_budget_us_);
      this->apply_roi_size_();
      this->apply_roi_center_();

      // VL53L1_StaticInit() end

      // the API triggers this change in VL53L1_init_and_start_range() once a
      // measurement is started; assumes MM1 and MM2 are disabled
      this->write_register16_16_(ALGO_PART_TO_PART_RANGE_OFFSET_MM,
                                 this->read_register16_16_(MM_CONFIG_OUTER_OFFSET_MM) * 4);

      // Set the sensor to the desired final address
      // The following is different for VL53L0X vs VL53L1X
      // I2C_SXXXX_DEVICE_ADDRESS = 0x8A for VL53L0X
      // I2C_SXXXX_DEVICE_ADDRESS = 0x0001 for VL53L1X
      if (this->final_address_ != 0x29) {
        this->reg16(I2C_SXXXX_DEVICE_ADDRESS) = this->final_address_ & 0x7F;
        this->set_i2c_address(this->final_address_);
      }

      this->current_setup_state_ = SETUP_STATE_COMPLETE;
      VL53L1XSensor::currently_enabling_sensor = nullptr;
      break;
    default:
      // failed
      return;
  }
}

bool VL53L1XSensor::check_timeout_(uint32_t timeout_us) {
  uint32_t now = micros();

  if (now - this->last_setup_task_us_ < timeout_us) {
    return true;
  }
  if (this->timeout_us_ == 0) {
    return true;
  }

  // we subtract out the expected length of time for the given step
  uint32_t elapsed = now - timeout_us - this->last_setup_task_us_;
  if (elapsed > this->timeout_us_) {
    ESP_LOGE(TAG, "'%s' - setup timeout in step %d", this->name_.c_str(), this->current_setup_state_);
    this->mark_failed();
    this->current_setup_state_ = SETUP_STATE_FAILED;
    return false;
  }
  return true;
}

void VL53L1XSensor::update() {
  if (this->current_setup_state_ != SETUP_STATE_COMPLETE && this->current_setup_state_ != SETUP_STATE_FAILED) {
    return;
  }
  if (this->waiting_for_interrupt_) {
    this->publish_state(NAN);
    this->status_momentary_warning("update", 5000);
    ESP_LOGW(TAG, "%s - update called before prior reading complete - waiting_for_interrupt:%d", this->name_.c_str(),
             this->waiting_for_interrupt_);
    return;
  }

  ESP_LOGD(TAG, "Starting single shot read");

  // initiate single shot measurement
  this->reg16(SYSTEM_INTERRUPT_CLEAR) = 0x01;  // sys_interrupt_clear_range
  this->reg16(SYSTEM_MODE_START) = 0x10;       // mode_range_single_shot

  this->waiting_for_interrupt_ = true;
}

void VL53L1XSensor::loop() {
  if (this->current_setup_state_ != SETUP_STATE_COMPLETE) {
    this->next_setup_task_();
    return;
  }

  if (!this->waiting_for_interrupt_) {
    return;
  }

  if (!this->data_ready_()) {
    return;
  }

  ResultBuffer results = this->read_results_();

  if (!this->calibrated_) {
    this->setup_manual_calibration_();
    this->calibrated_ = true;
  }

  this->update_dss_(results);

  RangingData ranging_data = this->get_ranging_data_(results);

  this->reg16(SYSTEM_INTERRUPT_CLEAR) = 0x01;  // sys_interrupt_clear_range

  float range_m = ranging_data.range_mm / 1e3f;
  ESP_LOGD(TAG, "'%s' - Got distance %.3f m", this->name_.c_str(), range_m);
  this->publish_state(range_m);
  this->waiting_for_interrupt_ = false;
  ;
}

bool VL53L1XSensor::apply_distance_mode_() {
  // save existing timing budget
  uint32_t budget_us = this->get_measurement_timing_budget_();

  switch (distance_mode_) {
    case SHORT:
      // from VL53L1_preset_mode_standard_ranging_short_range()

      // timing config
      this->reg16(RANGE_CONFIG_VCSEL_PERIOD_A) = 0x07;
      this->reg16(RANGE_CONFIG_VCSEL_PERIOD_B) = 0x05;
      this->reg16(RANGE_CONFIG_VALID_PHASE_HIGH) = 0x38;

      // dynamic config
      this->reg16(SD_CONFIG_WOI_SD0) = 0x07;
      this->reg16(SD_CONFIG_WOI_SD1) = 0x05;
      this->reg16(SD_CONFIG_INITIAL_PHASE_SD0) = 6;  // tuning parm default
      this->reg16(SD_CONFIG_INITIAL_PHASE_SD1) = 6;  // tuning parm default

      break;

    case MEDIUM:
      // from VL53L1_preset_mode_standard_ranging()

      // timing config
      this->reg16(RANGE_CONFIG_VCSEL_PERIOD_A) = 0x0b;
      this->reg16(RANGE_CONFIG_VCSEL_PERIOD_B) = 0x09;
      this->reg16(RANGE_CONFIG_VALID_PHASE_HIGH) = 0x78;

      // dynamic config
      this->reg16(SD_CONFIG_WOI_SD0) = 0x0b;
      this->reg16(SD_CONFIG_WOI_SD1) = 0x09;
      this->reg16(SD_CONFIG_INITIAL_PHASE_SD0) = 10;  // tuning parm default
      this->reg16(SD_CONFIG_INITIAL_PHASE_SD1) = 10;  // tuning parm default

      break;

    case LONG:  // long
      // from VL53L1_preset_mode_standard_ranging_long_range()

      // timing config
      this->reg16(RANGE_CONFIG_VCSEL_PERIOD_A) = 0x0f;
      this->reg16(RANGE_CONFIG_VCSEL_PERIOD_B) = 0x0d;
      this->reg16(RANGE_CONFIG_VALID_PHASE_HIGH) = 0xb8;

      // dynamic config
      this->reg16(SD_CONFIG_WOI_SD0) = 0x0f;
      this->reg16(SD_CONFIG_WOI_SD1) = 0x0d;
      this->reg16(SD_CONFIG_INITIAL_PHASE_SD0) = 14;  // tuning parm default
      this->reg16(SD_CONFIG_INITIAL_PHASE_SD1) = 14;  // tuning parm default

      break;

    default:
      // unrecognized mode - do nothing
      return false;
  }

  // reapply timing budget
  this->apply_measurement_timing_budget_(budget_us);

  return true;
}

// Set the measurement timing budget in microseconds, which is the time allowed
// for one measurement. A longer timing budget allows for more accurate
// measurements.
// based on VL53L1_SetMeasurementTimingBudgetMicroSeconds()
bool VL53L1XSensor::apply_measurement_timing_budget_(uint32_t budget_us) {
  if (budget_us <= TIMING_GUARD) {
    return false;
  }

  uint32_t range_config_timeout_us = budget_us - TIMING_GUARD;
  if (range_config_timeout_us > 1100000) {  // FDA_MAX_TIMING_BUDGET_US * 2
    return false;
  }

  range_config_timeout_us /= 2;

  // VL53L1_calc_timeout_register_values() begin

  uint32_t macro_period_us;

  // "Update Macro Period for Range A VCSEL Period"
  macro_period_us = this->calc_macro_period_(this->reg16(RANGE_CONFIG_VCSEL_PERIOD_A).get());

  // "Update Phase timeout - uses Timing A"
  // Timeout of 1000 is tuning parm default (TIMED_PHASECAL_CONFIG_TIMEOUT_US_DEFAULT)
  // via VL53L1_get_preset_mode_timing_cfg().
  uint32_t phasecal_timeout_mclks = this->timeout_microseconds_to_mclks_(1000, macro_period_us);
  if (phasecal_timeout_mclks > 0xFF) {
    phasecal_timeout_mclks = 0xFF;
  }
  this->reg16(PHASECAL_CONFIG_TIMEOUT_MACROP) = phasecal_timeout_mclks;

  // "Update MM Timing A timeout"
  // Timeout of 1 is tuning parm default (LOWPOWERAUTO_MM_CONFIG_TIMEOUT_US_DEFAULT)
  // via VL53L1_get_preset_mode_timing_cfg(). With the API, the register
  // actually ends up with a slightly different value because it gets assigned,
  // retrieved, recalculated with a different macro period, and reassigned,
  // but it probably doesn't matter because it seems like the MM ("mode
  // mitigation"?) sequence steps are disabled in low power auto mode anyway.
  this->write_register16_16_(MM_CONFIG_TIMEOUT_MACROP_A,
                             this->encode_timeout_(this->timeout_microseconds_to_mclks_(1, macro_period_us)));

  // "Update Range Timing A timeout"
  this->write_register16_16_(RANGE_CONFIG_TIMEOUT_MACROP_A, this->encode_timeout_(this->timeout_microseconds_to_mclks_(
                                                                range_config_timeout_us, macro_period_us)));

  // "Update Macro Period for Range B VCSEL Period"
  macro_period_us = this->calc_macro_period_(this->reg16(RANGE_CONFIG_VCSEL_PERIOD_B).get());

  // "Update MM Timing B timeout"
  // (See earlier comment about MM Timing A timeout.)
  this->write_register16_16_(MM_CONFIG_TIMEOUT_MACROP_B,
                             this->encode_timeout_(this->timeout_microseconds_to_mclks_(1, macro_period_us)));

  // "Update Range Timing B timeout"
  this->write_register16_16_(RANGE_CONFIG_TIMEOUT_MACROP_B, this->encode_timeout_(this->timeout_microseconds_to_mclks_(
                                                                range_config_timeout_us, macro_period_us)));

  // VL53L1_calc_timeout_register_values() end

  // set_sequence_step_timeout() end

  return true;
}

// Get the measurement timing budget in microseconds
// based on VL53L1_SetMeasurementTimingBudgetMicroSeconds()
uint32_t VL53L1XSensor::get_measurement_timing_budget_() {
  // assumes PresetMode is LOWPOWER_AUTONOMOUS and these sequence steps are
  // enabled: VHV, PHASECAL, DSS1, RANGE

  // VL53L1_get_timeouts_us() begin

  // "Update Macro Period for Range A VCSEL Period"
  uint32_t macro_period_us = this->calc_macro_period_(this->reg16(0x0060).get());

  // "Get Range Timing A timeout"

  uint32_t range_config_timeout_us =
      this->timeout_mclks_to_microseconds_(this->decode_timeout_(this->read_register16_16_(0x005e)), macro_period_us);

  // VL53L1_get_timeouts_us() end

  return 2 * range_config_timeout_us + TIMING_GUARD;
}

// Set the width and height of the region of interest
// based on VL53L1X_SetROI() from STSW-IMG009 Ultra Lite Driver
//
// ST user manual UM2555 explains ROI selection in detail, so we recommend
// reading that document carefully.
void VL53L1XSensor::apply_roi_size_() {
  this->reg16(ROI_CONFIG_USER_ROI_REQUESTED_GLOBAL_XY_SIZE) = (this->roi_height_ - 1) << 4 | (this->roi_width_ - 1);
}

// Set the center SPAD of the region of interest (ROI)
// based on VL53L1X_SetROICenter() from STSW-IMG009 Ultra Lite Driver
//
// ST user manual UM2555 explains ROI selection in detail, so we recommend
// reading that document carefully. Here is a table of SPAD locations from
// UM2555 (199 is the default/center):
//
// 128,136,144,152,160,168,176,184,  192,200,208,216,224,232,240,248
// 129,137,145,153,161,169,177,185,  193,201,209,217,225,233,241,249
// 130,138,146,154,162,170,178,186,  194,202,210,218,226,234,242,250
// 131,139,147,155,163,171,179,187,  195,203,211,219,227,235,243,251
// 132,140,148,156,164,172,180,188,  196,204,212,220,228,236,244,252
// 133,141,149,157,165,173,181,189,  197,205,213,221,229,237,245,253
// 134,142,150,158,166,174,182,190,  198,206,214,222,230,238,246,254
// 135,143,151,159,167,175,183,191,  199,207,215,223,231,239,247,255
//
// 127,119,111,103, 95, 87, 79, 71,   63, 55, 47, 39, 31, 23, 15,  7
// 126,118,110,102, 94, 86, 78, 70,   62, 54, 46, 38, 30, 22, 14,  6
// 125,117,109,101, 93, 85, 77, 69,   61, 53, 45, 37, 29, 21, 13,  5
// 124,116,108,100, 92, 84, 76, 68,   60, 52, 44, 36, 28, 20, 12,  4
// 123,115,107, 99, 91, 83, 75, 67,   59, 51, 43, 35, 27, 19, 11,  3
// 122,114,106, 98, 90, 82, 74, 66,   58, 50, 42, 34, 26, 18, 10,  2
// 121,113,105, 97, 89, 81, 73, 65,   57, 49, 41, 33, 25, 17,  9,  1
// 120,112,104, 96, 88, 80, 72, 64,   56, 48, 40, 32, 24, 16,  8,  0 <- Pin 1
//
// This table is oriented as if looking into the front of the sensor (or top of
// the chip). SPAD 0 is closest to pin 1 of the VL53L1X, which is the corner
// closest to the VDD pin on the Pololu VL53L1X carrier board:
//
//   +--------------+
//   |             O| GPIO1
//   |              |
//   |             O|
//   | 128    248   |
//   |+----------+ O|
//   ||+--+  +--+|  |
//   |||  |  |  || O|
//   ||+--+  +--+|  |
//   |+----------+ O|
//   | 120      0   |
//   |             O|
//   |              |
//   |             O| VDD
//   +--------------+
//
// However, note that the lens inside the VL53L1X inverts the image it sees
// (like the way a camera works). So for example, to shift the sensor's FOV to
// sense objects toward the upper left, you should pick a center SPAD in the
// lower right.
void VL53L1XSensor::apply_roi_center_() { this->reg16(ROI_CONFIG_USER_ROI_CENTRE_SPAD) = this->roi_center_spad_; }

// "Setup ranges after the first one in low power auto mode by turning off
// FW calibration steps and programming static values"
// based on VL53L1_low_power_auto_setup_manual_calibration()
void VL53L1XSensor::setup_manual_calibration_() {
  // "save original vhv configs"
  uint8_t saved_vhv_init = this->reg16(VHV_CONFIG_INIT).get();
  uint8_t saved_vhv_timeout = this->reg16(VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND).get();

  // "disable VHV init"
  this->reg16(VHV_CONFIG_INIT) = saved_vhv_init & 0x7F;

  // "set loop bound to tuning param"
  this->reg16(VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND) =
      (saved_vhv_timeout & 0x03) + (3 << 2);  // tuning parm default (LOWPOWERAUTO_VHV_LOOP_BOUND_DEFAULT)

  // "override phasecal"
  this->reg16(PHASECAL_CONFIG_OVERRIDE) = 0x01;
  this->reg16(CAL_CONFIG_VCSEL_START) = this->reg16(PHASECAL_RESULT_VCSEL_START).get();
}

// read measurement results into buffer
ResultBuffer VL53L1XSensor::read_results_() {
  ResultBuffer results;
  this->read_register16(RESULT_RANGE_STATUS, (uint8_t *) &results, sizeof(results));
  results.dss_actual_effective_spads_sd0 = i2c::i2ctohs(results.dss_actual_effective_spads_sd0);
  results.ambient_count_rate_mcps_sd0 = i2c::i2ctohs(results.ambient_count_rate_mcps_sd0);
  results.final_crosstalk_corrected_range_mm_sd0 = i2c::i2ctohs(results.final_crosstalk_corrected_range_mm_sd0);
  results.peak_signal_count_rate_crosstalk_corrected_mcps_sd0 =
      i2c::i2ctohs(results.peak_signal_count_rate_crosstalk_corrected_mcps_sd0);

  return results;
}

// perform Dynamic SPAD Selection calculation/update
// based on VL53L1_low_power_auto_update_DSS()
void VL53L1XSensor::update_dss_(const ResultBuffer &results) {
  uint16_t spad_count = results.dss_actual_effective_spads_sd0;

  if (spad_count != 0) {
    // "Calc total rate per spad"

    uint32_t total_rate_per_spad =
        (uint32_t) results.peak_signal_count_rate_crosstalk_corrected_mcps_sd0 + results.ambient_count_rate_mcps_sd0;

    // "clip to 16 bits"
    if (total_rate_per_spad > 0xFFFF) {
      total_rate_per_spad = 0xFFFF;
    }

    // "shift up to take advantage of 32 bits"
    total_rate_per_spad <<= 16;

    total_rate_per_spad /= spad_count;

    if (total_rate_per_spad != 0) {
      // "get the target rate and shift up by 16"
      uint32_t required_spads = ((uint32_t) TARGET_RATE << 16) / total_rate_per_spad;

      // "clip to 16 bit"
      if (required_spads > 0xFFFF) {
        required_spads = 0xFFFF;
      }

      // "override DSS config"
      this->write_register16_16_(DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT, required_spads);
      // DSS_CONFIG_ROI_MODE_CONTROL should already be set to REQUESTED_EFFFECTIVE_SPADS

      return;
    }
  }

  // If we reached this point, it means something above would have resulted in a
  // divide by zero.
  // "We want to gracefully set a spad target, not just exit with an error"

  // "set target to mid point"
  this->write_register16_16_(DSS_CONFIG_MANUAL_EFFECTIVE_SPADS_SELECT, 0x8000);
}

// get range, status, rates from results buffer
// based on VL53L1_GetRangingMeasurementData()
RangingData VL53L1XSensor::get_ranging_data_(const ResultBuffer &results) {
  // VL53L1_copy_sys_and_core_results_to_range_results() begin
  RangingData ranging_data;

  uint16_t range = results.final_crosstalk_corrected_range_mm_sd0;

  // "apply correction gain"
  // gain factor of 2011 is tuning parm default (VL53L1_TUNINGPARM_LITE_RANGING_GAIN_FACTOR_DEFAULT)
  // Basically, this appears to scale the result by 2011/2048, or about 98%
  // (with the 1024 added for proper rounding).
  ranging_data.range_mm = ((uint32_t) range * 2011 + 0x0400) / 0x0800;

  // VL53L1_copy_sys_and_core_results_to_range_results() end

  // set range_status in ranging_data based on value of RESULT_RANGE_STATUS register
  // mostly based on ConvertStatusLite()
  switch (results.range_status) {
    case 17:  // MULTCLIPFAIL
    case 2:   // VCSELWATCHDOGTESTFAILURE
    case 1:   // VCSELCONTINUITYTESTFAILURE
    case 3:   // NOVHVVALUEFOUND
      // from SetSimpleData()
      ranging_data.range_status = HARDWARE_FAIL;
      break;

    case 13:  // USERROICLIP
              // from SetSimpleData()
      ranging_data.range_status = MIN_RANGE_FAIL;
      break;

    case 18:  // GPHSTREAMCOUNT0READY
      ranging_data.range_status = SYNCHRONIZATION_INT;
      break;

    case 5:  // RANGEPHASECHECK
      ranging_data.range_status = OUT_OF_BOUNDS_FAIL;
      break;

    case 4:  // MSRCNOTARGET
      ranging_data.range_status = SIGNAL_FAIL;
      break;

    case 6:  // SIGMATHRESHOLDCHECK
      ranging_data.range_status = SIGMA_FAIL;
      break;

    case 7:  // PHASECONSISTENCY
      ranging_data.range_status = WRAP_TARGET_FAIL;
      break;

    case 12:  // RANGEIGNORETHRESHOLD
      ranging_data.range_status = XTALK_SIGNAL_FAIL;
      break;

    case 8:  // MINCLIP
      ranging_data.range_status = RANGE_VALID_MIN_RANGE_CLIPPED;
      break;

    case 9:  // RANGECOMPLETE
      // from VL53L1_copy_sys_and_core_results_to_range_results()
      if (results.stream_count == 0) {
        ranging_data.range_status = RANGE_VALID_NO_WRAP_CHECK_FAIL;
      } else {
        ranging_data.range_status = RANGE_VALID;
      }
      break;

    default:
      ranging_data.range_status = NONE;
  }

  // from SetSimpleData()
  ranging_data.peak_signal_count_rate_mcps =
      this->count_rate_fixed_to_float_(results.peak_signal_count_rate_crosstalk_corrected_mcps_sd0);
  ranging_data.ambient_count_rate_mcps = this->count_rate_fixed_to_float_(results.ambient_count_rate_mcps_sd0);
  return ranging_data;
}

// Decode sequence step timeout in MCLKs from register value
// based on VL53L1_decode_timeout()
uint32_t VL53L1XSensor::decode_timeout_(uint16_t reg_val) {
  return ((uint32_t) (reg_val & 0xFF) << (reg_val >> 8)) + 1;
}

// Encode sequence step timeout register value from timeout in MCLKs
// based on VL53L1_encode_timeout()
uint16_t VL53L1XSensor::encode_timeout_(uint32_t timeout_mclks) {
  // format: "(LSByte * 2^MSByte) + 1"
  uint32_t ls_byte = 0;
  uint16_t ms_byte = 0;

  if (timeout_mclks <= 0)
    return 0;

  ls_byte = timeout_mclks - 1;

  while ((ls_byte & 0xFFFFFF00) > 0) {
    ls_byte >>= 1;
    ms_byte++;
  }

  return (ms_byte << 8) | (ls_byte & 0xFF);
}

// Convert sequence step timeout from macro periods to microseconds with given
// macro period in microseconds (12.12 format)
// based on VL53L1_calc_timeout_us()
uint32_t VL53L1XSensor::timeout_mclks_to_microseconds_(uint32_t timeout_mclks, uint32_t macro_period_us) {
  return ((uint64_t) timeout_mclks * macro_period_us + 0x800) >> 12;
}

// Convert sequence step timeout from microseconds to macro periods with given
// macro period in microseconds (12.12 format)
// based on VL53L1_calc_timeout_mclks()
uint32_t VL53L1XSensor::timeout_microseconds_to_mclks_(uint32_t timeout_us, uint32_t macro_period_us) {
  return (((uint32_t) timeout_us << 12) + (macro_period_us >> 1)) / macro_period_us;
}

// Calculate macro period in microseconds (12.12 format) with given VCSEL period
// assumes fast_osc_frequency has been read and stored
// based on VL53L1_calc_macro_period_us()
uint32_t VL53L1XSensor::calc_macro_period_(uint8_t vcsel_period) {
  // from VL53L1_calc_pll_period_us()
  // fast osc frequency in 4.12 format; PLL period in 0.24 format
  uint32_t pll_period_us = ((uint32_t) 0x01 << 30) / this->fast_osc_frequency_;

  // from VL53L1_decode_vcsel_period()
  uint8_t vcsel_period_pclks = (vcsel_period + 1) << 1;

  // VL53L1_MACRO_PERIOD_VCSEL_PERIODS = 2304
  uint32_t macro_period_us = (uint32_t) 2304 * pll_period_us;
  macro_period_us >>= 6;
  macro_period_us *= vcsel_period_pclks;
  macro_period_us >>= 6;

  return macro_period_us;
}

float VL53L1XSensor::count_rate_fixed_to_float_(uint16_t count_rate_fixed) {
  return (float) count_rate_fixed / (1 << 7);
}

// check if sensor has new reading available
// assumes interrupt is active low (GPIO_HV_MUX_CTRL bit 4 is 1)
bool VL53L1XSensor::data_ready_() { return (this->reg16(GPIO_TIO_HV_STATUS).get() & 0x01) == 0; }

uint16_t VL53L1XSensor::read_register16_16_(uint16_t reg) {
  uint16_t value = 0;
  this->read_register16(reg, (uint8_t *) &value, sizeof(value));
  return i2c::i2ctohs(value);
}

void VL53L1XSensor::write_register16_16_(uint16_t reg, uint16_t value) {
  value = i2c::htoi2cs(value);
  this->write_register16(reg, (uint8_t *) &value, sizeof(value));
}

}  // namespace vl53l1x
}  // namespace esphome
