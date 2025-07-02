#include "ld2412.h"
#include "esphome/core/helpers.h"

#include <utility>
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif

#define CHECK_BIT(var, pos) (((var) >> (pos)) & 1)
#define highbyte(val) (uint8_t)((val) >> 8)
#define lowbyte(val) (uint8_t)((val) &0xff)

namespace esphome {
namespace ld2412 {

static const char *const TAG = "ld2412";
static const char *const NO_MAC = "08:05:04:03:02:01";
static const char *const UNKNOWN_MAC = "unknown";
static const char *const VERSION_FMT = "%u.%02X.%02X%02X%02X%02X";

enum BaudRateStructure : uint8_t {
  BAUD_RATE_9600 = 1,
  BAUD_RATE_19200 = 2,
  BAUD_RATE_38400 = 3,
  BAUD_RATE_57600 = 4,
  BAUD_RATE_115200 = 5,
  BAUD_RATE_230400 = 6,
  BAUD_RATE_256000 = 7,
  BAUD_RATE_460800 = 8
};

enum DistanceResolutionStructure : uint8_t {
  DISTANCE_RESOLUTION_0_2 = 0x03,
  DISTANCE_RESOLUTION_0_5 = 0x01,
  DISTANCE_RESOLUTION_0_75 = 0x00
};

// enum LightFunctionStructure : uint8_t {
//   LIGHT_FUNCTION_OFF = 0x00,
//   LIGHT_FUNCTION_BELOW = 0x01,
//   LIGHT_FUNCTION_ABOVE = 0x02
// };

enum ModeStructure : uint8_t {
  NORMAL_MODE = 1,
  ENGINEERING_MODE = 2,
  BACKGROUND_INIT_MODE = 3,
};

enum OutPinLevelStructure : uint8_t {
  OUT_PIN_LEVEL_LOW = 0x01,
  OUT_PIN_LEVEL_HIGH = 0x00,
};

/*
Data Type: 6th byte
Target states: 9th byte
    Moving target distance: 10~11th bytes
    Moving target energy: 12th byte
    Still target distance: 13~14th bytes
    Still target energy: 15th byte
    Detect distance: 16~17th bytes
*/
enum PeriodicDataStructure : uint8_t {
  DATA_TYPES = 6,
  TARGET_STATES = 8,
  MOVING_TARGET_LOW = 9,
  MOVING_TARGET_HIGH = 10,
  MOVING_ENERGY = 11,
  STILL_TARGET_LOW = 12,
  STILL_TARGET_HIGH = 13,
  STILL_ENERGY = 14,
  MOVING_SENSOR_START = 17,
  STILL_SENSOR_START = 31,
  LIGHT_SENSOR = 45,
  OUT_PIN_SENSOR = 38,
};

enum PeriodicDataValue : uint8_t {
  HEAD = 0XAA,
  END = 0x55,
  CHECK = 0x00,
};

enum AckDataStructure : uint8_t {
  COMMAND = 6,
  COMMAND_STATUS = 7,
};

// Memory-efficient lookup tables
struct StringToUint8 {
  const char *str;
  uint8_t value;
};

struct Uint8ToString {
  uint8_t value;
  const char *str;
};

constexpr StringToUint8 BAUD_RATES_BY_STR[] = {
    {"9600", BAUD_RATE_9600},     {"19200", BAUD_RATE_19200},   {"38400", BAUD_RATE_38400},
    {"57600", BAUD_RATE_57600},   {"115200", BAUD_RATE_115200}, {"230400", BAUD_RATE_230400},
    {"256000", BAUD_RATE_256000}, {"460800", BAUD_RATE_460800},
};

constexpr StringToUint8 MODE_BY_STR[] = {
    {"Normal", NORMAL_MODE},
    {"Engineering", ENGINEERING_MODE},
    {"Dynamic background correction", BACKGROUND_INIT_MODE},
};

constexpr StringToUint8 DISTANCE_RESOLUTIONS_BY_STR[] = {
    {"0.2m", DISTANCE_RESOLUTION_0_2},
    {"0.5m", DISTANCE_RESOLUTION_0_5},
    {"0.75m", DISTANCE_RESOLUTION_0_75},
};

constexpr Uint8ToString DISTANCE_RESOLUTIONS_BY_UINT[] = {
    {DISTANCE_RESOLUTION_0_2, "0.2m"},
    {DISTANCE_RESOLUTION_0_5, "0.5m"},
    {DISTANCE_RESOLUTION_0_75, "0.75m"},
};

// constexpr StringToUint8 LIGHT_FUNCTION_BY_STR[] = {
//     {"off", LIGHT_FUNCTION_OFF},
//     {"below", LIGHT_FUNCTION_BELOW},
//     {"above", LIGHT_FUNCTION_ABOVE},
// };

// constexpr Uint8ToString LIGHT_FUNCTION_BY_UINT[] = {
//     {LIGHT_FUNCTION_OFF, "off"},
//     {LIGHT_FUNCTION_BELOW, "below"},
//     {LIGHT_FUNCTION_ABOVE, "above"},
// };

constexpr StringToUint8 OUT_PIN_LEVELS_BY_STR[] = {
    {"low", OUT_PIN_LEVEL_LOW},
    {"high", OUT_PIN_LEVEL_HIGH},
};

constexpr Uint8ToString OUT_PIN_LEVELS_BY_UINT[] = {
    {OUT_PIN_LEVEL_LOW, "low"},
    {OUT_PIN_LEVEL_HIGH, "high"},
};

// Helper functions for lookups
template<size_t N> uint8_t find_uint8(const StringToUint8 (&arr)[N], const std::string &str) {
  for (const auto &entry : arr) {
    if (str == entry.str)
      return entry.value;
  }
  return 0xFF;  // Not found
}

template<size_t N> const char *find_str(const Uint8ToString (&arr)[N], uint8_t value) {
  for (const auto &entry : arr) {
    if (value == entry.value)
      return entry.str;
  }
  return "";  // Not found
}

// Commands
static const uint8_t CMD_ENABLE_CONF = 0xFF;
static const uint8_t CMD_DISABLE_CONF = 0xFE;
static const uint8_t CMD_ENABLE_ENG = 0x62;
static const uint8_t CMD_DISABLE_ENG = 0x63;
static const uint8_t CMD_MAXDIST_DURATION = 0x60;
static const uint8_t CMD_QUERY = 0x12;
static const uint8_t CMD_BASIC_CONF = 0x02;
static const uint8_t CMD_GATE_SENS = 0x64;
static const uint8_t CMD_VERSION = 0xA0;
static const uint8_t CMD_QUERY_DISTANCE_RESOLUTION = 0x11;
static const uint8_t CMD_SET_DISTANCE_RESOLUTION = 0x01;
static const uint8_t CMD_QUERY_LIGHT_CONTROL = 0xAE;
static const uint8_t CMD_SET_LIGHT_CONTROL = 0xAD;
static const uint8_t CMD_SET_BAUD_RATE = 0xA1;
static const uint8_t CMD_BT_PASSWORD = 0xA9;
static const uint8_t CMD_MAC = 0xA5;
static const uint8_t CMD_RESET = 0xA2;
static const uint8_t CMD_RESTART = 0xA3;
static const uint8_t CMD_BLUETOOTH = 0xA4;
static const uint8_t CMD_DYNAMIC_BACKGROUND_CORRECTION = 0x0B;
static const uint8_t CMD_QUEY_DYNAMIC_BACKGROUND_CORRECTION = 0x1B;
static const uint8_t CMD_MOTION_GATE_SENS = 0x03;
static const uint8_t CMD_QUERY_MOTION_GATE_SENS = 0x13;
static const uint8_t CMD_STATIC_GATE_SENS = 0x04;
static const uint8_t CMD_QUERY_STATIC_GATE_SENS = 0x14;
static const uint8_t CMD_NONE = 0x00;
// Commands values
static const uint8_t CMD_MAX_MOVE_VALUE = 0x00;
static const uint8_t CMD_MAX_STILL_VALUE = 0x01;
static const uint8_t CMD_DURATION_VALUE = 0x02;
// Header & Footer size
static const uint8_t HEADER_FOOTER_SIZE = 4;
// Command Header & Footer
static const uint8_t CMD_FRAME_HEADER[HEADER_FOOTER_SIZE] = {0xFD, 0xFC, 0xFB, 0xFA};
static const uint8_t CMD_FRAME_FOOTER[HEADER_FOOTER_SIZE] = {0x04, 0x03, 0x02, 0x01};
// Data Header & Footer
static const uint8_t DATA_FRAME_HEADER[HEADER_FOOTER_SIZE] = {0xF4, 0xF3, 0xF2, 0xF1};
static const uint8_t DATA_FRAME_FOOTER[HEADER_FOOTER_SIZE] = {0xF8, 0xF7, 0xF6, 0xF5};

static int two_byte_to_int(char firstbyte, char secondbyte) { return (int16_t) (secondbyte << 8) + firstbyte; }

static bool validate_header_footer(const uint8_t *header_footer, const uint8_t *buffer) {
  for (uint8_t i = 0; i < HEADER_FOOTER_SIZE; i++) {
    if (header_footer[i] != buffer[i]) {
      return false;  // Mismatch in header/footer
    }
  }
  return true;  // Valid header/footer
}

void LD2412Component::dump_config() {
  ESP_LOGCONFIG(TAG, "LD2412:");
#ifdef USE_BINARY_SENSOR
  LOG_BINARY_SENSOR("  ", "TargetBinarySensor", this->target_binary_sensor_);
  LOG_BINARY_SENSOR("  ", "MovingTargetBinarySensor", this->moving_target_binary_sensor_);
  LOG_BINARY_SENSOR("  ", "StillTargetBinarySensor", this->still_target_binary_sensor_);
  LOG_BINARY_SENSOR("  ", "OutPinPresenceStatusBinarySensor", this->out_pin_presence_status_binary_sensor_);
#endif
#ifdef USE_SWITCH
//  LOG_SWITCH("  ", "EngineeringModeSwitch", this->engineering_mode_switch_);
//  LOG_SWITCH("  ", "BluetoothSwitch", this->bluetooth_switch_);
#endif
#ifdef USE_BUTTON
  LOG_BUTTON("  ", "ResetButton", this->reset_button_);
  LOG_BUTTON("  ", "RestartButton", this->restart_button_);
  LOG_BUTTON("  ", "QueryButton", this->query_button_);
#endif
#ifdef USE_SENSOR
  // LOG_SENSOR("  ", "LightSensor", this->light_sensor_);
  LOG_SENSOR("  ", "MovingTargetDistanceSensor", this->moving_target_distance_sensor_);
  LOG_SENSOR("  ", "StillTargetDistanceSensor", this->still_target_distance_sensor_);
  LOG_SENSOR("  ", "MovingTargetEnergySensor", this->moving_target_energy_sensor_);
  LOG_SENSOR("  ", "StillTargetEnergySensor", this->still_target_energy_sensor_);
  LOG_SENSOR("  ", "DetectionDistanceSensor", this->detection_distance_sensor_);
  // for (sensor::Sensor *s : this->gate_still_sensors_) {
  //   LOG_SENSOR("  ", "NthGateStillSesnsor", s);
  // }
  // for (sensor::Sensor *s : this->gate_move_sensors_) {
  //   LOG_SENSOR("  ", "NthGateMoveSesnsor", s);
  // }
#endif
#ifdef USE_TEXT_SENSOR
  LOG_TEXT_SENSOR("  ", "VersionTextSensor", this->version_text_sensor_);
  LOG_TEXT_SENSOR("  ", "MacTextSensor", this->mac_text_sensor_);
#endif
#ifdef USE_SELECT
  //  LOG_SELECT("  ", "LightFunctionSelect", this->light_function_select_);
  LOG_SELECT("  ", "OutPinLevelSelect", this->out_pin_level_select_);
  // LOG_SELECT("  ", "DistanceResolutionSelect", this->distance_resolution_select_);
  LOG_SELECT("  ", "BaudRateSelect", this->baud_rate_select_);
  LOG_SELECT("  ", "ModeSelect", this->mode_select_);
#endif
#ifdef USE_NUMBER
  //  LOG_NUMBER("  ", "LightThresholdNumber", this->light_threshold_number_);
  LOG_NUMBER("  ", "MaxDistanceGateNumber", this->max_distance_gate_number_);
  LOG_NUMBER("  ", "MinDistanceGateNumber", this->min_distance_gate_number_);
  LOG_NUMBER("  ", "TimeoutNumber", this->timeout_number_);
  // for (number::Number *n : this->gate_still_threshold_numbers_) {
  //   LOG_NUMBER("  ", "Still Thresholds Number", n);
  // }
  // for (number::Number *n : this->gate_move_threshold_numbers_) {
  //   LOG_NUMBER("  ", "Move Thresholds Number", n);
  // }
#endif
  ESP_LOGCONFIG(TAG,
                "  Throttle: %ums\n"
                "  MAC address: %s\n"
                "  Firmware version: %s",
                this->throttle_, this->mac_ == NO_MAC ? UNKNOWN_MAC : this->mac_.c_str(), this->version_.c_str());
}

void LD2412Component::setup() {
  ESP_LOGCONFIG(TAG, "Running setup");
  this->read_all_info();
}

void LD2412Component::read_all_info() {
  this->set_config_mode_(true);
  this->get_version_();
  delay(10);  // NOLINT
  this->get_mac_();
  delay(10);  // NOLINT
  this->get_distance_resolution_();
  delay(10);  // NOLINT
  // this->get_light_control_();
  this->query_parameters_();
  delay(10);  // NOLINT
  this->query_dynamic_background_correction_();
  delay(10);  // NOLINT
#ifdef USE_NUMBER
  this->get_gate_threshold();
  delay(10);  // NOLINT
#endif
  this->set_config_mode_(false);
#ifdef USE_SELECT
  const auto baud_rate = std::to_string(this->parent_->get_baud_rate());
  if (this->baud_rate_select_ != nullptr && this->baud_rate_select_->state != baud_rate) {
    this->baud_rate_select_->publish_state(baud_rate);
  }
#endif
}

void LD2412Component::restart_and_read_all_info() {
  this->set_config_mode_(true);
  this->restart_();
  this->set_timeout(1000, [this]() { this->read_all_info(); });
}

void LD2412Component::loop() {
  while (this->available()) {
    this->readline_(this->read());
  }
}

void LD2412Component::send_command_(uint8_t command, const uint8_t *command_value, uint8_t command_value_len) {
  ESP_LOGV(TAG, "Sending COMMAND %02X", command);
  // frame start bytes
  this->write_array(CMD_FRAME_HEADER, HEADER_FOOTER_SIZE);
  // length bytes
  uint8_t len = 2;
  if (command_value != nullptr) {
    len += command_value_len;
  }
  uint8_t len_cmd[] = {lowbyte(len), highbyte(len), command, 0x00};
  this->write_array(len_cmd, sizeof(len_cmd));

  // command value bytes
  if (command_value != nullptr) {
    for (uint8_t i = 0; i < command_value_len; i++) {
      this->write_byte(command_value[i]);
    }
  }
  // frame end bytes
  this->write_array(CMD_FRAME_FOOTER, HEADER_FOOTER_SIZE);
  // FIXME to remove
  delay(50);  // NOLINT
}

void LD2412Component::handle_periodic_data_() {
  // 4 frame start bytes + 2 length bytes + 1 data end byte + 1 crc byte + 4 frame end bytes
  // data head=0xAA, data end=0x55, crc=0x00
  if (this->buffer_pos_ < 12 || !ld2412::validate_header_footer(DATA_FRAME_HEADER, this->buffer_data_) ||
      this->buffer_data_[7] != HEAD || this->buffer_data_[this->buffer_pos_ - 6] != END)
    return;

  /*
    Reduce data update rate to prevent home assistant database size grow fast
  */
  int32_t current_millis = millis();
  if (current_millis - last_periodic_millis_ < this->throttle_)
    return;
  last_periodic_millis_ = current_millis;

  /*
    Data Type: 7th
    0x01: Engineering mode
    0x02: Normal mode
  */
  bool engineering_mode = this->buffer_data_[DATA_TYPES] == 0x01;
#ifdef USE_SELECT
  if (this->mode_select_ != nullptr) {
    if (this->mode_select_->state == "Engineering" && !engineering_mode) {
      this->mode_select_->publish_state("Normal");
    }
    if (this->mode_select_->state == "Normal" && engineering_mode) {
      this->mode_select_->publish_state("Engineering");
    }
  }
#endif

  //#ifdef USE_SWITCH
  //  if (this->engineering_mode_switch_ != nullptr &&
  //      current_millis - last_engineering_mode_change_millis_ > this->throttle_) {
  //    this->engineering_mode_switch_->publish_state(engineering_mode);
  //  }
  //#endif
  char target_state = this->buffer_data_[TARGET_STATES];
#ifdef USE_BINARY_SENSOR
  /*
    Target states: 9th
    0x00 = No target
    0x01 = Moving targets
    0x02 = Still targets
    0x03 = Moving+Still targets
  */
  if (this->target_binary_sensor_ != nullptr) {
    this->target_binary_sensor_->publish_state(target_state != 0x00);
  }
  if (this->moving_target_binary_sensor_ != nullptr) {
    this->moving_target_binary_sensor_->publish_state(CHECK_BIT(target_state, 0));
  }
  if (this->still_target_binary_sensor_ != nullptr) {
    this->still_target_binary_sensor_->publish_state(CHECK_BIT(target_state, 1));
  }
#endif
  /*
    Moving target distance: 10~11th bytes
    Moving target energy: 12th byte
    Still target distance: 13~14th bytes
    Still target energy: 15th byte
    Detect distance: 16~17th bytes
  */
#ifdef USE_SENSOR
  if (this->moving_target_distance_sensor_ != nullptr) {
    int new_moving_target_distance =
        target_state != 0x00
            ? ld2412::two_byte_to_int(this->buffer_data_[MOVING_TARGET_LOW], this->buffer_data_[MOVING_TARGET_HIGH])
            : 0;
    if (this->moving_target_distance_sensor_->get_state() != new_moving_target_distance)
      this->moving_target_distance_sensor_->publish_state(new_moving_target_distance);
  }
  if (this->moving_target_energy_sensor_ != nullptr) {
    int new_moving_target_energy = target_state != 0x00 ? this->buffer_data_[MOVING_ENERGY] : 0;
    if (this->moving_target_energy_sensor_->get_state() != new_moving_target_energy)
      this->moving_target_energy_sensor_->publish_state(new_moving_target_energy);
  }
  if (this->still_target_distance_sensor_ != nullptr) {
    int new_still_target_distance =
        target_state != 0x00
            ? ld2412::two_byte_to_int(this->buffer_data_[STILL_TARGET_LOW], this->buffer_data_[STILL_TARGET_HIGH])
            : 0;
    if (this->still_target_distance_sensor_->get_state() != new_still_target_distance)
      this->still_target_distance_sensor_->publish_state(new_still_target_distance);
  }
  if (this->still_target_energy_sensor_ != nullptr) {
    int new_still_target_energy = target_state != 0x00 ? this->buffer_data_[STILL_ENERGY] : 0;
    if (this->still_target_energy_sensor_->get_state() != new_still_target_energy)
      this->still_target_energy_sensor_->publish_state(new_still_target_energy);
  }
  if (this->detection_distance_sensor_ != nullptr) {
    int new_detect_distance = 0;
    if (target_state != 0x00 && CHECK_BIT(target_state, 0)) {
      new_detect_distance =
          ld2412::two_byte_to_int(this->buffer_data_[MOVING_TARGET_LOW], this->buffer_data_[MOVING_TARGET_HIGH]);
    } else if (target_state != 0x00) {
      new_detect_distance =
          ld2412::two_byte_to_int(this->buffer_data_[STILL_TARGET_LOW], this->buffer_data_[STILL_TARGET_HIGH]);
    }
    if (this->detection_distance_sensor_->get_state() != new_detect_distance)
      this->detection_distance_sensor_->publish_state(new_detect_distance);
  }
  if (engineering_mode) {
    /*
      Moving distance range: 18th byte
      Still distance range: 19th byte
      Moving enery: 20~28th bytes
    */
    for (std::vector<sensor::Sensor *>::size_type i = 0; i != this->gate_move_sensors_.size(); i++) {
      sensor::Sensor *s = this->gate_move_sensors_[i];
      if (s != nullptr) {
        s->publish_state(this->buffer_data_[MOVING_SENSOR_START + i]);
      }
    }
    /*
      Still energy: 29~37th bytes
    */
    for (std::vector<sensor::Sensor *>::size_type i = 0; i != this->gate_still_sensors_.size(); i++) {
      sensor::Sensor *s = this->gate_still_sensors_[i];
      if (s != nullptr) {
        s->publish_state(this->buffer_data_[STILL_SENSOR_START + i]);
      }
    }
    /*
      Light sensor: 38th bytes
    */
    if (this->light_sensor_ != nullptr) {
      int new_light_sensor = (this->buffer_data_[LIGHT_SENSOR] * 100) / 255;
      if (this->light_sensor_->get_state() != new_light_sensor)
        this->light_sensor_->publish_state(new_light_sensor);
    }
  }
  if (!engineering_mode) {
    for (auto *s : this->gate_move_sensors_) {
      if (s != nullptr && !std::isnan(s->get_state())) {
        s->publish_state(NAN);
      }
    }
    for (auto *s : this->gate_still_sensors_) {
      if (s != nullptr && !std::isnan(s->get_state())) {
        s->publish_state(NAN);
      }
    }
    if (this->light_sensor_ != nullptr && !std::isnan(this->light_sensor_->get_state())) {
      this->light_sensor_->publish_state(NAN);
    }
  }
  //}
#endif
#ifdef USE_BINARY_SENSOR
  if (engineering_mode) {
    if (this->out_pin_presence_status_binary_sensor_ != nullptr) {
      this->out_pin_presence_status_binary_sensor_->publish_state(this->buffer_data_[OUT_PIN_SENSOR] == 0x01);
    }
  } else {
    if (this->out_pin_presence_status_binary_sensor_ != nullptr) {
      this->out_pin_presence_status_binary_sensor_->publish_state(false);
    }
  }
#endif
}

#ifdef USE_NUMBER
std::function<void(void)> set_number_value(number::Number *n, float value) {
  float normalized_value = value * 1.0;
  if (n != nullptr && (!n->has_state() || n->state != normalized_value)) {
    n->state = normalized_value;
    return [n, normalized_value]() { n->publish_state(normalized_value); };
  }
  return []() {};
}
#endif

bool LD2412Component::handle_ack_data_() {
  ESP_LOGV(TAG, "Handling ACK DATA for COMMAND %02X", this->buffer_data_[COMMAND]);
  if (this->buffer_pos_ < 10) {
    ESP_LOGW(TAG, "Incorrect length");
    return true;
  }
  if (!ld2412::validate_header_footer(CMD_FRAME_HEADER, this->buffer_data_)) {
    ESP_LOGW(TAG, "Incorrect header: %s", format_hex_pretty(this->buffer_data_, HEADER_FOOTER_SIZE).c_str());
    // just a patch to handle a strange behavior. better this than have a costant wrong mode
    if (this->dynamic_background_correction_active_) {
      this->query_dynamic_background_correction_();
    }
    return true;
  }
  if (this->buffer_data_[COMMAND_STATUS] != 0x01) {
    ESP_LOGW(TAG, "Invalid status");
    return true;
  }
  if (ld2412::two_byte_to_int(this->buffer_data_[8], this->buffer_data_[9]) != 0x00) {
    ESP_LOGW(TAG, "Invalid command: %02X, %02X", this->buffer_data_[8], this->buffer_data_[9]);
    return true;
  }
  bool dynamic_background_correction_active;
  switch (this->buffer_data_[COMMAND]) {
    case CMD_ENABLE_CONF:
      ESP_LOGV(TAG, "Handled Enable conf command");
      break;
    case CMD_DISABLE_CONF:
      ESP_LOGV(TAG, "Handled Disabled conf command");
      break;
    case CMD_SET_BAUD_RATE:
      ESP_LOGV(TAG, "Handled baud rate change command");
#ifdef USE_SELECT
      if (this->baud_rate_select_ != nullptr) {
        ESP_LOGW(TAG, "Change baud rate to %s and reinstall", this->baud_rate_select_->state.c_str());
      }
#endif
      break;
    case CMD_VERSION:
      this->version_ = str_sprintf(VERSION_FMT, this->buffer_data_[13], this->buffer_data_[12], this->buffer_data_[17],
                                   this->buffer_data_[16], this->buffer_data_[15], this->buffer_data_[14]);
      ESP_LOGV(TAG, "Firmware version: %s", const_cast<char *>(this->version_.c_str()));
#ifdef USE_TEXT_SENSOR
      if (this->version_text_sensor_ != nullptr) {
        this->version_text_sensor_->publish_state(this->version_);
      }
#endif
      break;
    case CMD_QUERY_DISTANCE_RESOLUTION: {
      std::string distance_resolution = find_str(
          DISTANCE_RESOLUTIONS_BY_UINT, ld2412::two_byte_to_int(this->buffer_data_[10], this->buffer_data_[11]));
      ESP_LOGV(TAG, "Distance resolution: %s", const_cast<char *>(distance_resolution.c_str()));
#ifdef USE_SELECT
      if (this->distance_resolution_select_ != nullptr &&
          this->distance_resolution_select_->state != distance_resolution) {
        this->distance_resolution_select_->publish_state(distance_resolution);
      }
#endif
    } break;
    // case CMD_QUERY_LIGHT_CONTROL: {
    //   this->light_function_ = LIGHT_FUNCTION_INT_TO_ENUM.at(this->buffer_data_[10]);
    //   this->light_threshold_ = this->buffer_data_[11] * 1.0;
    //   this->out_pin_level_ = OUT_PIN_LEVEL_INT_TO_ENUM.at(this->buffer_data_[12]);
    //   ESP_LOGV(TAG, "Light function is: %s", const_cast<char *>(this->light_function_.c_str()));
    //   ESP_LOGV(TAG, "Light threshold is: %f", this->light_threshold_);
    //   ESP_LOGV(TAG, "Out pin level is: %s", const_cast<char *>(this->out_pin_level_.c_str()));
    //  #ifdef USE_SELECT
    //        if (this->light_function_select_ != nullptr && this->light_function_select_->state !=
    //        this->light_function_) {
    //          this->light_function_select_->publish_state(this->light_function_);
    //        }
    //        if (this->out_pin_level_select_ != nullptr && this->out_pin_level_select_->state != this->out_pin_level_)
    //        {
    //          this->out_pin_level_select_->publish_state(this->out_pin_level_);
    //        }
    //  #endif
    //  #ifdef USE_NUMBER
    //        if (this->light_threshold_number_ != nullptr &&
    //            (!this->light_threshold_number_->has_state() ||
    //             this->light_threshold_number_->state != this->light_threshold_)) {
    //          this->light_threshold_number_->publish_state(this->light_threshold_);
    //        }
    //  #endif
    //      } break;
    case CMD_MAC:
      if (this->buffer_pos_ < 20) {
        return false;
      }
      this->mac_ = format_mac_address_pretty(&this->buffer_data_[10]);
      ESP_LOGV(TAG, "MAC address: %s", this->mac_.c_str());
#ifdef USE_TEXT_SENSOR
      if (this->mac_text_sensor_ != nullptr) {
        this->mac_text_sensor_->publish_state(this->mac_ == NO_MAC ? UNKNOWN_MAC : this->mac_);
      }
#endif
#ifdef USE_SWITCH
      if (this->bluetooth_switch_ != nullptr) {
        this->bluetooth_switch_->publish_state(this->mac_ != NO_MAC);
      }
#endif
      break;
    case CMD_SET_DISTANCE_RESOLUTION:
      ESP_LOGV(TAG, "Handled set distance resolution command");
      break;
    case CMD_QUEY_DYNAMIC_BACKGROUND_CORRECTION:
      ESP_LOGV(TAG, "Handled query dynamic background correction");
      dynamic_background_correction_active = (this->buffer_data_[10] == 0x01);
#ifdef USE_SELECT
      if (this->dynamic_background_correction_active_ != dynamic_background_correction_active &&
          dynamic_background_correction_active) {
        this->mode_select_->publish_state("Dynamic background correction");
      } else if (this->dynamic_background_correction_active_ != dynamic_background_correction_active &&
                 !dynamic_background_correction_active) {
        this->mode_select_->publish_state("Normal");
      }
#endif
      this->dynamic_background_correction_active_ = dynamic_background_correction_active;
      if (this->dynamic_background_correction_active_) {
        this->set_timeout(1000, [this]() { this->query_dynamic_background_correction_(); });
      }
      break;
      //    case CMD_GATE_SENS:
      //      ESP_LOGV(TAG, "Handled sensitivity command");
      //      break;
      //    case CMD_BLUETOOTH:
      //      ESP_LOGV(TAG, "Handled bluetooth command");
      //      break;
      //    case CMD_SET_LIGHT_CONTROL:
      //      ESP_LOGV(TAG, "Handled set light control command");
      //      break;
      //    case CMD_BT_PASSWORD:
      //      ESP_LOGV(TAG, "Handled set bluetooth password command");
      //      break;
    case CMD_QUERY_MOTION_GATE_SENS: {
#ifdef USE_NUMBER
      std::vector<std::function<void(void)>> updates;
      updates.reserve(this->gate_still_threshold_numbers_.size());
      for (size_t i = 0; i < this->gate_still_threshold_numbers_.size(); i++) {
        updates.push_back(set_number_value(this->gate_move_threshold_numbers_[i], this->buffer_data_[10 + i]));
      }
      for (auto &update : updates) {
        update();
      }
#endif
      break;
    }
    case CMD_QUERY_STATIC_GATE_SENS: {
#ifdef USE_NUMBER
      std::vector<std::function<void(void)>> updates;
      updates.reserve(this->gate_still_threshold_numbers_.size());
      for (size_t i = 0; i < this->gate_still_threshold_numbers_.size(); i++) {
        updates.push_back(set_number_value(this->gate_still_threshold_numbers_[i], this->buffer_data_[10 + i]));
      }
      for (auto &update : updates) {
        update();
      }
#endif
      break;
    }
    case CMD_QUERY:  // Query parameters response
    {
#ifdef USE_NUMBER
      /*
        Moving distance range: 9th byte
        Still distance range: 10th byte
      */
      std::vector<std::function<void(void)>> updates;
      updates.push_back(set_number_value(this->min_distance_gate_number_, this->buffer_data_[10]));
      updates.push_back(set_number_value(this->max_distance_gate_number_, this->buffer_data_[11] - 1));
      ESP_LOGV(TAG, "min_distance_gate_number_: %u, max_distance_gate_number_ %u", this->buffer_data_[10],
               this->buffer_data_[11]);
      /*
        None Duration: 11~12th bytes
      */
      updates.push_back(set_number_value(this->timeout_number_,
                                         ld2412::two_byte_to_int(this->buffer_data_[12], this->buffer_data_[13])));
      ESP_LOGV(TAG, "timeout_number_: %u", ld2412::two_byte_to_int(this->buffer_data_[12], this->buffer_data_[13]));
      /*
        Output pin configuration: 13th bytes
      */
      this->out_pin_level_ = find_str(OUT_PIN_LEVELS_BY_UINT, this->buffer_data_[14]);
#ifdef USE_SELECT
      if (this->out_pin_level_select_ != nullptr && this->out_pin_level_select_->state != this->out_pin_level_) {
        this->out_pin_level_select_->publish_state(this->out_pin_level_);
      }
#endif
      /*
        Moving Sensitivities: 15~23th bytes
      */
      // for (std::vector<number::Number *>::size_type i = 0; i != this->gate_move_threshold_numbers_.size(); i++) {
      //   updates.push_back(set_number_value(this->gate_move_threshold_numbers_[i], this->buffer_data_[14 + i]));
      // }
      // /*
      //   Still Sensitivities: 24~32th bytes
      // */
      // for (std::vector<number::Number *>::size_type i = 0; i != this->gate_still_threshold_numbers_.size(); i++) {
      //   updates.push_back(set_number_value(this->gate_still_threshold_numbers_[i], this->buffer_data_[23 + i]));
      // }
      for (auto &update : updates) {
        update();
      }
#endif
    } break;
    default:
      break;
  }

  return true;
}

void LD2412Component::readline_(int readch) {
  if (readch < 0) {
    return;  // No data available
  }
  if (this->buffer_pos_ == 0 && readch != DATA_FRAME_HEADER[0] && readch != CMD_FRAME_HEADER[0]) {
    return;
  }
  if (this->buffer_pos_ == 1 && readch != DATA_FRAME_HEADER[1] && readch != CMD_FRAME_HEADER[1]) {
    this->buffer_pos_ = 0;
    return;
  }
  if (this->buffer_pos_ == 2 && readch != DATA_FRAME_HEADER[2] && readch != CMD_FRAME_HEADER[2]) {
    this->buffer_pos_ = 0;
    return;
  }
  if (this->buffer_pos_ == 3 && readch != DATA_FRAME_HEADER[3] && readch != CMD_FRAME_HEADER[3]) {
    this->buffer_pos_ = 0;
    return;
  }
  if (this->buffer_pos_ < MAX_LINE_LENGTH - 1) {
    this->buffer_data_[this->buffer_pos_++] = readch;
    this->buffer_data_[this->buffer_pos_] = 0;
  } else {
    // We should never get here, but just in case...
    ESP_LOGW(TAG, "Max command length exceeded; ignoring");
    this->buffer_pos_ = 0;
  }
  if (this->buffer_pos_ < 4) {
    return;  // Not enough data to process yet
  }
  if (this->buffer_data_[this->buffer_pos_ - 4] == DATA_FRAME_FOOTER[0] &&
      this->buffer_data_[this->buffer_pos_ - 3] == DATA_FRAME_FOOTER[1] &&
      this->buffer_data_[this->buffer_pos_ - 2] == DATA_FRAME_FOOTER[2] &&
      this->buffer_data_[this->buffer_pos_ - 1] == DATA_FRAME_FOOTER[3]) {
    ESP_LOGV(TAG, "Handling Periodic Data: %s", format_hex_pretty(this->buffer_data_, this->buffer_pos_).c_str());
    this->handle_periodic_data_();
    this->buffer_pos_ = 0;  // Reset position index ready for next time
  } else if (this->buffer_data_[this->buffer_pos_ - 4] == CMD_FRAME_FOOTER[0] &&
             this->buffer_data_[this->buffer_pos_ - 3] == CMD_FRAME_FOOTER[1] &&
             this->buffer_data_[this->buffer_pos_ - 2] == CMD_FRAME_FOOTER[2] &&
             this->buffer_data_[this->buffer_pos_ - 1] == CMD_FRAME_FOOTER[3]) {
    ESP_LOGV(TAG, "Handling Ack Data: %s", format_hex_pretty(this->buffer_data_, this->buffer_pos_).c_str());
    if (this->handle_ack_data_()) {
      this->buffer_pos_ = 0;  // Reset position index ready for next time
    } else {
      ESP_LOGV(TAG, "ACK Data incomplete");
    }
  }
}

void LD2412Component::set_config_mode_(bool enable) {
  uint8_t cmd = enable ? CMD_ENABLE_CONF : CMD_DISABLE_CONF;
  const uint8_t cmd_value[2] = {0x01, 0x00};
  this->send_command_(cmd, enable ? cmd_value : nullptr, 2);
}

void LD2412Component::set_bluetooth(bool enable) {
  this->set_config_mode_(true);
  const uint8_t cmd_value[2] = {enable ? (uint8_t) 0x01 : (uint8_t) 0x00, 0x00};
  this->send_command_(CMD_BLUETOOTH, cmd_value, 2);
  this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

void LD2412Component::set_distance_resolution(const std::string &state) {
  this->set_config_mode_(true);
  const uint8_t cmd_value[6] = {find_uint8(DISTANCE_RESOLUTIONS_BY_STR, state), 0x00, 0x00, 0x00, 0x00, 0x00};
  this->send_command_(CMD_SET_DISTANCE_RESOLUTION, cmd_value, 6);
  this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

void LD2412Component::set_baud_rate(const std::string &state) {
  this->set_config_mode_(true);
  const uint8_t cmd_value[2] = {find_uint8(BAUD_RATES_BY_STR, state), 0x00};
  this->send_command_(CMD_SET_BAUD_RATE, cmd_value, 2);
  this->set_timeout(200, [this]() { this->restart_(); });
}

void LD2412Component::set_mode(const std::string &state) {
  this->set_config_mode_(true);
  uint8_t cmd = CMD_NONE;
  switch (find_uint8(MODE_BY_STR, state)) {
    case NORMAL_MODE:
      cmd = CMD_DISABLE_ENG;
      break;
    case ENGINEERING_MODE:
      cmd = CMD_ENABLE_ENG;
      break;
    case BACKGROUND_INIT_MODE:
      cmd = CMD_DYNAMIC_BACKGROUND_CORRECTION;
      break;
  }
  if (cmd != CMD_NONE) {
    this->send_command_(cmd, nullptr, 0);
    this->set_config_mode_(false);
    if (cmd == CMD_DYNAMIC_BACKGROUND_CORRECTION) {
      this->dynamic_background_correction_active_ = true;
      this->set_timeout(1000, [this]() { this->query_dynamic_background_correction_(); });
    }
  }
}

void LD2412Component::query_dynamic_background_correction_() {
  this->set_config_mode_(true);
  this->send_command_(CMD_QUEY_DYNAMIC_BACKGROUND_CORRECTION, nullptr, 0);
  this->set_config_mode_(false);
}

void LD2412Component::set_engineering_mode(bool enable) {
  this->set_config_mode_(true);
  const uint8_t cmd = enable ? CMD_ENABLE_ENG : CMD_DISABLE_ENG;
  this->last_engineering_mode_change_millis_ = millis();
  this->send_command_(cmd, nullptr, 0);
  this->set_config_mode_(false);
}

void LD2412Component::factory_reset() {
  this->set_config_mode_(true);
  this->send_command_(CMD_RESET, nullptr, 0);
#ifdef USE_SELECT
  if (this->baud_rate_select_ != nullptr) {
    this->baud_rate_select_->publish_state("115200");
  }
#endif
  this->set_timeout(2000, [this]() { this->restart_and_read_all_info(); });
}

void LD2412Component::restart_() { this->send_command_(CMD_RESTART, nullptr, 0); }

void LD2412Component::query_parameters_() { this->send_command_(CMD_QUERY, nullptr, 0); }

void LD2412Component::get_version_() { this->send_command_(CMD_VERSION, nullptr, 0); }

void LD2412Component::get_mac_() {
  const uint8_t cmd_value[2] = {0x01, 0x00};
  this->send_command_(CMD_MAC, cmd_value, 2);
}

void LD2412Component::get_distance_resolution_() { this->send_command_(CMD_QUERY_DISTANCE_RESOLUTION, nullptr, 0); }

// void LD2412Component::get_light_control_() { this->send_command_(CMD_QUERY_LIGHT_CONTROL, nullptr, 0); }

#ifdef USE_NUMBER
void LD2412Component::set_basic_config() {
  if (!this->min_distance_gate_number_->has_state() || !this->max_distance_gate_number_->has_state() ||
      !this->timeout_number_->has_state() || !this->out_pin_level_select_->has_state()) {
    return;
  }
  uint8_t value[5] = {
      lowbyte(static_cast<int>(this->min_distance_gate_number_->state)),
      lowbyte(static_cast<int>(this->max_distance_gate_number_->state) + 1),
      lowbyte(static_cast<int>(this->timeout_number_->state)),
      highbyte(static_cast<int>(this->timeout_number_->state)),
#ifdef USE_SELECT
      find_uint8(OUT_PIN_LEVELS_BY_STR, this->out_pin_level_select_->state),
#else
      0x01,  // Default value if not using select
#endif
  };
  this->set_config_mode_(true);
  this->send_command_(CMD_BASIC_CONF, value, 5);
  delay(50);  // NOLINT
  this->set_config_mode_(false);
}

void LD2412Component::set_gate_threshold() {
  if (this->gate_move_threshold_numbers_.empty() && this->gate_still_threshold_numbers_.empty()) {
    return;  // No gate threshold numbers set; nothing to do here
  }
  uint8_t value[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  this->set_config_mode_(true);
  if (!this->gate_move_threshold_numbers_.empty()) {
    for (size_t i = 0; i < this->gate_move_threshold_numbers_.size(); i++) {
      value[i] = lowbyte(static_cast<int>(this->gate_move_threshold_numbers_[i]->state));
    }
    this->send_command_(CMD_MOTION_GATE_SENS, value, 14);
    delay(50);  // NOLINT
  }
  if (!this->gate_still_threshold_numbers_.empty()) {
    for (size_t i = 0; i < this->gate_still_threshold_numbers_.size(); i++) {
      value[i] = lowbyte(static_cast<int>(this->gate_still_threshold_numbers_[i]->state));
    }
    this->send_command_(CMD_STATIC_GATE_SENS, value, 14);
    delay(50);  // NOLINT
  }
  this->set_config_mode_(false);
  // this->query_parameters_();
}

void LD2412Component::get_gate_threshold() {
  this->set_config_mode_(true);
  this->send_command_(CMD_QUERY_MOTION_GATE_SENS, nullptr, 0);
  delay(50);  // NOLINT
  this->send_command_(CMD_QUERY_STATIC_GATE_SENS, nullptr, 0);
  delay(50);  // NOLINT
  this->set_config_mode_(false);
}

void LD2412Component::set_gate_still_threshold_number(uint8_t gate, number::Number *n) {
  this->gate_still_threshold_numbers_[gate] = n;
}

void LD2412Component::set_gate_move_threshold_number(uint8_t gate, number::Number *n) {
  this->gate_move_threshold_numbers_[gate] = n;
}
#endif

void LD2412Component::set_light_out_control() {
// #ifdef USE_NUMBER
//   if (this->light_threshold_number_ != nullptr && this->light_threshold_number_->has_state()) {
//     this->light_threshold_ = this->light_threshold_number_->state;
//   }
// #endif
#ifdef USE_SELECT
  //   if (this->light_function_select_ != nullptr && this->light_function_select_->has_state()) {
  //     this->light_function_ = this->light_function_select_->state;
  //   }
  if (this->out_pin_level_select_ != nullptr && this->out_pin_level_select_->has_state()) {
    this->out_pin_level_ = this->out_pin_level_select_->state;
  }
#endif
  if (this->light_function_.empty() || this->out_pin_level_.empty() || this->light_threshold_ < 0) {
    return;
  }
  this->set_config_mode_(true);
  // uint8_t light_function = LIGHT_FUNCTION_ENUM_TO_INT.at(this->light_function_);
  // uint8_t light_threshold = static_cast<uint8_t>(this->light_threshold_);
  // uint8_t out_pin_level = OUT_PIN_LEVEL_ENUM_TO_INT.at(this->out_pin_level_);
  // uint8_t value[4] = {light_function, light_threshold, out_pin_level, 0x00};
  // this->send_command_(CMD_SET_LIGHT_CONTROL, value, 4);
  // delay(50);  // NOLINT
  // this->get_light_control_();
  this->set_timeout(200, [this]() { this->restart_and_read_all_info(); });
}

#ifdef USE_SENSOR
void LD2412Component::set_gate_move_sensor(uint8_t gate, sensor::Sensor *s) { this->gate_move_sensors_[gate] = s; }
void LD2412Component::set_gate_still_sensor(uint8_t gate, sensor::Sensor *s) { this->gate_still_sensors_[gate] = s; }
#endif

}  // namespace ld2412
}  // namespace esphome
