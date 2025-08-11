#include "daikin_3p5939722e.h"
#include "esphome/components/remote_base/remote_base.h"

namespace esphome {
namespace daikin_3p5939722e {

static const char *const TAG = "daikin_3p5939722e.climate";

void Daikin3p5939722eClimate::setup() {
  auto restore = this->restore_state_();
  if (!restore.has_value()) {
    this->custom_preset.reset();
  }
  climate_ir::ClimateIR::setup();
}

void Daikin3p5939722eClimate::control(const climate::ClimateCall &call) {
  if (call.get_preset().has_value()) {
    // Just reset the custom preset, parent method will do the rest
    this->custom_preset.reset();
  } else if (call.get_custom_preset().has_value()) {
    this->custom_preset = *call.get_custom_preset();
    this->preset.reset();
  }
  climate_ir::ClimateIR::control(call);
}

climate::ClimateTraits Daikin3p5939722eClimate::traits() {
  climate::ClimateTraits traits = climate_ir::ClimateIR::traits();
  traits.set_supported_custom_presets({DAIKIN_CUSTOM_PRESET_ECO_SLEEP});
  traits.add_supported_custom_preset(DAIKIN_CUSTOM_PRESET_ECO_SLEEP);
  return traits;
}

void Daikin3p5939722eClimate::transmit_state() {
  /**
   * Static frame
   * Never changes
   * frame[4] = type = 0xC5
   * frame[7] = checksum
   */
  uint8_t static_frame[DAIKIN_STATIC_FRAME_SIZE] = {0x11, 0xDA, 0x27, 0x00, 0xC5, 0x00, 0x00, 0xD7};

  /**
   * Time frame
   * Hardcoded to 00:00
   * frame[5-6] = time in minutes since midnight, uint16_t, little endian
   * frame[7]   = checksum
   */
  uint8_t time_frame[DAIKIN_TIME_FRAME_SIZE] = {0x11, 0xDA, 0x27, 0x00, 0x42, 0x00, 0x00, 0x54};

  /**
   * State frame
   * frame[5]     = Operating mode and on/off timers (not utilized). Last bit is power: 0 = off, 1 = on
   * frame[6]     = Temperature as int*2 (24 C = 48)
   * frame[8]     = Fan speed + swing mode, simple addition of values
   * frame[10-12] = On/off timers (not utilized)
   * frame[13]    = Boost (powerful) or sleep preset
   * frame[16]    = Eco preset
   * frame[18]    = Checksum
   */
  uint8_t state_frame[DAIKIN_STATE_FRAME_SIZE] = {0x11, 0xDA, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x60, 0x00, 0x00, 0xC5, 0x00, 0x08, 0x00};

  state_frame[5] = this->operating_mode_();
  state_frame[6] = this->temperature_();
  state_frame[8] = this->fan_speed_() | this->swing_();
  uint8_t merged_preset = this->map_esphome_to_daikin_preset_();
  state_frame[13] = merged_preset & 0x0F;
  state_frame[16] = merged_preset >> 4 & 0x0F;

  // Calculate state frame checksum
  for (int i = 0; i < 18; i++) {
    state_frame[18] += state_frame[i];
  }

  auto transmit = this->transmitter_->transmit();
  auto *data = transmit.get_data();
  data->set_carrier_frequency(DAIKIN_IR_FREQUENCY);

  data->mark(DAIKIN_HEADER_MARK);
  data->space(DAIKIN_HEADER_SPACE);
  for (int i = 0; i < DAIKIN_STATIC_FRAME_SIZE; i++) {
    for (uint8_t mask = 1; mask > 0; mask <<= 1) {
      data->mark(DAIKIN_BIT_MARK);
      bool bit = static_frame[i] & mask;
      data->space(bit ? DAIKIN_ONE_SPACE : DAIKIN_ZERO_SPACE);
    }
  }
  data->mark(DAIKIN_BIT_MARK);
  data->space(DAIKIN_MESSAGE_SPACE);
  data->mark(DAIKIN_HEADER_MARK);
  data->space(DAIKIN_HEADER_SPACE);

  for (int i = 0; i < DAIKIN_TIME_FRAME_SIZE; i++) {
    for (uint8_t mask = 1; mask > 0; mask <<= 1) {
      data->mark(DAIKIN_BIT_MARK);
      bool bit = time_frame[i] & mask;
      data->space(bit ? DAIKIN_ONE_SPACE : DAIKIN_ZERO_SPACE);
    }
  }
  data->mark(DAIKIN_BIT_MARK);
  data->space(DAIKIN_MESSAGE_SPACE);
  data->mark(DAIKIN_HEADER_MARK);
  data->space(DAIKIN_HEADER_SPACE);

  for (int i = 0; i < DAIKIN_STATE_FRAME_SIZE; i++) {
    for (uint8_t mask = 1; mask > 0; mask <<= 1) {
      data->mark(DAIKIN_BIT_MARK);
      bool bit = state_frame[i] & mask;
      data->space(bit ? DAIKIN_ONE_SPACE : DAIKIN_ZERO_SPACE);
    }
  }
  data->mark(DAIKIN_BIT_MARK);
  data->space(0);

  transmit.perform();
}

uint8_t Daikin3p5939722eClimate::operating_mode_() const {
  uint8_t operating_mode = DAIKIN_MODE_ON;
  switch (this->mode) {
    case climate::CLIMATE_MODE_COOL:
      operating_mode |= DAIKIN_MODE_COOL;
      break;
    case climate::CLIMATE_MODE_DRY:
      operating_mode |= DAIKIN_MODE_DRY;
      break;
    case climate::CLIMATE_MODE_HEAT:
      operating_mode |= DAIKIN_MODE_HEAT;
      break;
    case climate::CLIMATE_MODE_HEAT_COOL:
      operating_mode |= DAIKIN_MODE_AUTO;
      break;
    case climate::CLIMATE_MODE_FAN_ONLY:
      operating_mode |= DAIKIN_MODE_FAN;
      break;
    case climate::CLIMATE_MODE_OFF:
    default:
      operating_mode = DAIKIN_MODE_OFF;
      break;
  }

  return operating_mode;
}

uint8_t Daikin3p5939722eClimate::fan_speed_() const {
  /**
   * Remote always sets fan speed to auto in dry mode, so send that to the AC, but don't
   * update the internal state - remote remembers the previous value for other modes.
   * (Unlike the temperature, remote keeps the same fan speed for all modes.)
   */
  if (this->mode == DAIKIN_MODE_DRY) {
    return DAIKIN_FAN_AUTO;
  }
  switch (this->fan_mode.value()) {
    case climate::CLIMATE_FAN_QUIET:
      return DAIKIN_FAN_QUIET;
    case climate::CLIMATE_FAN_LOW:
      return DAIKIN_FAN_1;
    case climate::CLIMATE_FAN_MEDIUM:
      return DAIKIN_FAN_3;
    case climate::CLIMATE_FAN_HIGH:
      return DAIKIN_FAN_5;
    case climate::CLIMATE_FAN_AUTO:
    default:
      return DAIKIN_FAN_AUTO;
  }
}

uint8_t Daikin3p5939722eClimate::swing_() const {
  switch (this->swing_mode) {
    case climate::CLIMATE_SWING_VERTICAL:
      return DAIKIN_SWING_VERTICAL;
    case climate::CLIMATE_SWING_OFF:
    default:
      return DAIKIN_SWING_OFF;
  }
}

uint8_t Daikin3p5939722eClimate::temperature_() const {
  // Force special temperatures depending on the mode
  switch (this->mode) {
    case climate::CLIMATE_MODE_FAN_ONLY:
      return DAIKIN_TEMPERATURE_MODE_FAN;
    case climate::CLIMATE_MODE_DRY:
      return DAIKIN_TEMPERATURE_MODE_DRY;
    default:
      uint8_t temperature = (uint8_t) roundf(clamp<float>(this->target_temperature, DAIKIN_TEMP_MIN, DAIKIN_TEMP_MAX));
      return temperature << 1;
  }
}

uint8_t Daikin3p5939722eClimate::map_esphome_to_daikin_preset_() const {
  if (this->custom_preset == DAIKIN_CUSTOM_PRESET_ECO_SLEEP) {
    return DAIKIN_PRESET_ECO_SLEEP;
  } else {
    // Simple value mapping implementation
    for (int i = 0; i < sizeof(CLIMATE_PRESETS); i++) {
      if (this->preset == CLIMATE_PRESETS[i]) {
        return DAIKIN_PRESETS[i];
      }
    }
    return 0;
  }
}

void Daikin3p5939722eClimate::map_daikin_to_esphome_preset_(const uint8_t merged_preset) {
  if (merged_preset == DAIKIN_PRESET_ECO_SLEEP) {
    this->custom_preset = DAIKIN_CUSTOM_PRESET_ECO_SLEEP;
    this->preset.reset();
  } else {
    // Simple value mapping implementation
    for (int i = 0; i < sizeof(DAIKIN_PRESETS); i++) {
      if (DAIKIN_PRESETS[i] == merged_preset) {
        this->preset = CLIMATE_PRESETS[i];
        this->custom_preset.reset();
        return;
      }
    }
  }
}

bool Daikin3p5939722eClimate::parse_state_frame_(const uint8_t frame[]) {
  // Calculate checksum
  uint8_t checksum = 0;
  for (int i = 0; i < (DAIKIN_STATE_FRAME_SIZE - 1); i++) {
    checksum += frame[i];
  }
  if (frame[DAIKIN_STATE_FRAME_SIZE - 1] != checksum) {
    ESP_LOGE(TAG, "Bad checksum");
    return false;
  }

  /**
   * The remote can toggle between states even when the AC is off. This is needed for setting on/off timers.
   * ESPHome doesn't separate power and operating mode, so the powered-off mode toggling can't be utilized here.
   */
  uint8_t mode = frame[5];
  if (mode & DAIKIN_MODE_ON) {
    switch (mode & DAIKIN_MODE_MASK) {
      case DAIKIN_MODE_AUTO:
        this->mode = climate::CLIMATE_MODE_HEAT_COOL;
        break;
      case DAIKIN_MODE_DRY:
        this->mode = climate::CLIMATE_MODE_DRY;
        break;
      case DAIKIN_MODE_COOL:
        this->mode = climate::CLIMATE_MODE_COOL;
        break;
      case DAIKIN_MODE_HEAT:
        this->mode = climate::CLIMATE_MODE_HEAT;
        break;
      case DAIKIN_MODE_FAN:
        this->mode = climate::CLIMATE_MODE_FAN_ONLY;
        break;
      default:
        ESP_LOGW(TAG, "Unknown operating mode, ignoring");
        break;
    }
  } else {
    this->mode = climate::CLIMATE_MODE_OFF;
  }

  /**
   * Temperature can be updated even if the mode is off.
   * The remote remembers different temperatures for different modes, therefore,
   * temperature may be updated even when cycling through modes in power off state.
   * But we can't ignore it when powered off because we can't (easily) know in ESPHome if the mode changed.
   */
  uint8_t temperature = frame[6];
  if (temperature != DAIKIN_TEMPERATURE_MODE_DRY && temperature != DAIKIN_TEMPERATURE_MODE_FAN) {
    float target_temperature = static_cast<float>(temperature >> 1);
    this->target_temperature = target_temperature;
  }

  // Get fan speed and swing mode
  uint8_t fan_speed_swing_mode = frame[8];
  switch (fan_speed_swing_mode & 0xF0) {
    case DAIKIN_FAN_1:
      this->fan_mode = climate::CLIMATE_FAN_LOW;
      break;
    case DAIKIN_FAN_3:
      this->fan_mode = climate::CLIMATE_FAN_MEDIUM;
      break;
    case DAIKIN_FAN_5:
      this->fan_mode = climate::CLIMATE_FAN_HIGH;
      break;
    case DAIKIN_FAN_AUTO:
      this->fan_mode = climate::CLIMATE_FAN_AUTO;
      break;
    case DAIKIN_FAN_QUIET:
      this->fan_mode = climate::CLIMATE_FAN_QUIET;
      break;
    default:
      ESP_LOGW(TAG, "Unknown fan speed, ignoring");
      break;
  }
  if (fan_speed_swing_mode & DAIKIN_SWING_VERTICAL) {
    this->swing_mode = climate::CLIMATE_SWING_VERTICAL;
  } else {
    this->swing_mode = climate::CLIMATE_SWING_OFF;
  }

  /**
   * Presets are split into two bytes and they can be combined.
   * Only lower 4 bits are utilized, so these two bytes can be merged into one uint8_t.
   */
  uint8_t powerful_sleep_preset = frame[13];
  uint8_t eco_preset = frame[16];
  uint8_t merged_preset = eco_preset << 4 | powerful_sleep_preset;
  map_daikin_to_esphome_preset_(merged_preset);
  this->publish_state();
  return true;
}

bool Daikin3p5939722eClimate::on_receive(remote_base::RemoteReceiveData data) {
  uint8_t state_frame[DAIKIN_STATE_FRAME_SIZE] = {};
  if (!data.expect_item(DAIKIN_HEADER_MARK, DAIKIN_HEADER_SPACE)) {
    return false;
  }
  for (uint8_t pos = 0; pos < DAIKIN_STATE_FRAME_SIZE; pos++) {
    uint8_t byte = 0;
    for (int8_t bit = 0; bit < 8; bit++) {
      if (data.expect_item(DAIKIN_BIT_MARK, DAIKIN_ONE_SPACE)) {
        byte |= 1 << bit;
      } else if (!data.expect_item(DAIKIN_BIT_MARK, DAIKIN_ZERO_SPACE)) {
        return false;
      }
    }
    state_frame[pos] = byte;
    if (pos < 4) {
      // Frame header
      if (state_frame[pos] != DAIKIN_FRAME_HEADER[pos]) {
        return false;
      }
    } else if (pos == 4 && byte != 0x00) {
      // Not a state frame
      return false;
    }
  }
  ESP_LOGD(TAG, "Received state frame, processing");
  return this->parse_state_frame_(state_frame);
}

}  // namespace daikin_3p5939722e
}  // namespace esphome
