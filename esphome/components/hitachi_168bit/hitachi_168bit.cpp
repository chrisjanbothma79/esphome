#include "hitachi_168bit.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hitachi_168bit {

static const char *const TAG = "hitachi_168bit.climate";

// Timing & protocol constants
constexpr uint16_t kHeaderMark = 9000;
constexpr uint16_t kHeaderSpace = 4494;
constexpr uint16_t kBitMark = 610;
constexpr uint16_t kOneSpace = 1680;
constexpr uint16_t kZeroSpace = 565;
constexpr uint32_t kGap = 8007;
constexpr uint32_t kCarrierFrequency = 38000;

// Frame structure
constexpr uint8_t kStateLength = 21;

// Mode nibble values
constexpr uint8_t kModeHeat = 0;
constexpr uint8_t kModeDry = 3;
constexpr uint8_t kModeCool = 2;
constexpr uint8_t kModeFan = 4;
constexpr uint8_t kModeAuto = 1;

// Fan values (2 LSBits of byte[2])
constexpr uint8_t kFanAuto = 0;
constexpr uint8_t kFanHigh = 1;
constexpr uint8_t kFanMed = 2;
constexpr uint8_t kFanLow = 3;

// Swing & power flags
constexpr uint8_t kSwingMask = 0x80;  // TBD on Hitachi; matches your current mapping
constexpr uint8_t kPowerFlag = 0x04;

void hitachi_168bitClimate::transmit_state() {
  this->last_transmit_time_ = millis();  // timestamp last transmission

  uint8_t remote_state[kStateLength] = {0};
  remote_state[0] = 0x95;
  remote_state[1] = 0x9A;
  remote_state[6] = 0x01;
  // MODEL DG11J1-91
  remote_state[18] = 0x1C;  // (or 0x14?) keep as discovered

  const bool powered_on = (this->mode != climate::CLIMATE_MODE_OFF);
  if (powered_on != this->powered_on_assumed) {
    // Set power toggle command
    remote_state[2] = kPowerFlag;
    remote_state[15] = 1;
    this->powered_on_assumed = powered_on;
  }

  // Mode
  switch (this->mode) {
    case climate::CLIMATE_MODE_HEAT_COOL:
      remote_state[3] = kModeAuto;  // auto mode
      remote_state[15] = 0x17;
      break;
    case climate::CLIMATE_MODE_HEAT:
      remote_state[3] = kModeHeat;
      remote_state[15] = 6;
      break;
    case climate::CLIMATE_MODE_COOL:
      remote_state[3] = kModeCool;
      remote_state[15] = 6;
      break;
    case climate::CLIMATE_MODE_DRY:
      remote_state[3] = kModeDry;
      remote_state[15] = 6;
      break;
    case climate::CLIMATE_MODE_FAN_ONLY:
      remote_state[3] = kModeFan;
      remote_state[15] = 6;
      break;
    case climate::CLIMATE_MODE_OFF:
    default:
      break;
  }

  // Temperature nibble (upper 4 bits of byte[3])
  const uint8_t temp =
      static_cast<uint8_t>(roundf(clamp(this->target_temperature, this->temperature_min_(), this->temperature_max_())));
  remote_state[3] |= static_cast<uint8_t>(temp - this->temperature_min_()) << 4;

  // Fan speed (lower 2 bits of byte[2])
  switch (this->fan_mode.value()) {
    case climate::CLIMATE_FAN_HIGH:
      remote_state[2] |= kFanHigh;
      break;
    case climate::CLIMATE_FAN_MEDIUM:
      remote_state[2] |= kFanMed;
      break;
    case climate::CLIMATE_FAN_LOW:
      remote_state[2] |= kFanLow;
      break;
    default:
      // auto: leave as 0
      break;
  }

  // Swing (toggle semantics on this protocol)
  ESP_LOGV(TAG, "send swing %s", this->send_swing_cmd_ ? "true" : "false");
  if (this->send_swing_cmd_) {
    if (this->swing_mode == climate::CLIMATE_SWING_VERTICAL || this->swing_mode == climate::CLIMATE_SWING_OFF) {
      remote_state[2] |= kSwingMask;
      remote_state[8] |= 0x40;
    }
  }

  // Checksums
  for (uint8_t i = 2; i < 13; i++)
    remote_state[13] ^= remote_state[i];
  for (uint8_t i = 14; i < 20; i++)
    remote_state[20] ^= remote_state[i];

  ESP_LOGV(TAG,
           "Sending: %02X %02X %02X %02X   %02X %02X %02X %02X   %02X %02X %02X %02X   %02X %02X %02X %02X   %02X %02X "
           "%02X %02X   %02X",
           remote_state[0], remote_state[1], remote_state[2], remote_state[3], remote_state[4], remote_state[5],
           remote_state[6], remote_state[7], remote_state[8], remote_state[9], remote_state[10], remote_state[11],
           remote_state[12], remote_state[13], remote_state[14], remote_state[15], remote_state[16], remote_state[17],
           remote_state[18], remote_state[19], remote_state[20]);

  // Transmit
  auto transmit = this->transmitter_->transmit();
  auto *data = transmit.get_data();

  data->set_carrier_frequency(kCarrierFrequency);

  // Header
  data->mark(kHeaderMark);
  data->space(kHeaderSpace);

  // Data
  uint8_t bytes_sent = 0;
  for (uint8_t i : remote_state) {
    for (uint8_t j = 0; j < 8; j++) {
      data->mark(kBitMark);
      const bool bit = (i & (1 << j)) != 0;
      data->space(bit ? kOneSpace : kZeroSpace);
    }
    bytes_sent++;
    if (bytes_sent == 6 || bytes_sent == 14) {
      // Divider
      data->mark(kBitMark);
      data->space(kGap);
    }
  }

  // Footer
  data->mark(kBitMark);

  transmit.perform();
}

bool hitachi_168bitClimate::on_receive(remote_base::RemoteReceiveData data) {
  // Ignore if we recently transmitted (debounce)
  if (millis() - this->last_transmit_time_ < 500) {
    ESP_LOGV(TAG, "Blocked receive because of current transmission");
    return false;
  }

  // Header
  if (!data.expect_item(kHeaderMark, kHeaderSpace)) {
    ESP_LOGV(TAG, "Header fail");
    return false;
  }

  uint8_t remote_state[kStateLength] = {0};

  // Read all bytes
  for (int i = 0; i < kStateLength; i++) {
    // Divider positions
    if (i == 6 || i == 14) {
      if (!data.expect_item(kBitMark, kGap))
        return false;
    }
    for (int j = 0; j < 8; j++) {
      if (data.expect_item(kBitMark, kOneSpace)) {
        remote_state[i] |= 1 << j;
      } else if (!data.expect_item(kBitMark, kZeroSpace)) {
        ESP_LOGV(TAG, "Byte %d bit %d fail", i, j);
        return false;
      }
    }
    ESP_LOGVV(TAG, "Byte %d %02X", i, remote_state[i]);
  }

  // Footer
  if (!data.expect_mark(kBitMark)) {
    ESP_LOGV(TAG, "Footer fail");
    return false;
  }

  // Checksums
  uint8_t checksum13 = 0;
  uint8_t checksum20 = 0;
  for (uint8_t i = 2; i < 13; i++)
    checksum13 ^= remote_state[i];
  for (uint8_t i = 14; i < 20; i++)
    checksum20 ^= remote_state[i];

  if (checksum13 != remote_state[13] || checksum20 != remote_state[20]) {
    ESP_LOGVV(TAG, "Checksum fail");
    return false;
  }

  ESP_LOGV(
      TAG,
      "Received: %02X %02X %02X %02X   %02X %02X %02X %02X   %02X %02X %02X %02X   %02X %02X %02X %02X   %02X %02X "
      "%02X %02X   %02X",
      remote_state[0], remote_state[1], remote_state[2], remote_state[3], remote_state[4], remote_state[5],
      remote_state[6], remote_state[7], remote_state[8], remote_state[9], remote_state[10], remote_state[11],
      remote_state[12], remote_state[13], remote_state[14], remote_state[15], remote_state[16], remote_state[17],
      remote_state[18], remote_state[19], remote_state[20]);

  // Verify header remote code (protocol ID)
  if (remote_state[0] != 0x83 || remote_state[1] != 0x06)
    return false;

  // Power toggle
  ESP_LOGV(TAG, "Power: %02X", (remote_state[2] & kPowerFlag));
  if ((remote_state[2] & kPowerFlag) == kPowerFlag) {
    const bool powered_on = (this->mode != climate::CLIMATE_MODE_OFF);
    if (powered_on) {
      this->mode = climate::CLIMATE_MODE_OFF;
      this->powered_on_assumed = false;
    } else {
      this->powered_on_assumed = true;
    }
  }

  // If powered on, parse mode
  if (this->powered_on_assumed) {
    const uint8_t mode = remote_state[3] & 0x07;
    ESP_LOGV(TAG, "Mode: %02X", mode);
    switch (mode) {
      case kModeHeat:
        this->mode = climate::CLIMATE_MODE_HEAT;
        break;
      case kModeCool:
        this->mode = climate::CLIMATE_MODE_COOL;
        break;
      case kModeDry:
        this->mode = climate::CLIMATE_MODE_DRY;
        break;
      case kModeFan:
        this->mode = climate::CLIMATE_MODE_FAN_ONLY;
        break;
      case kModeAuto:
        this->mode = climate::CLIMATE_MODE_HEAT_COOL;
        break;
      default:
        break;
    }
  }

  // Temperature
  int temp = remote_state[3] & 0xF0;
  ESP_LOGVV(TAG, "Temperature Raw: %02X", temp);
  temp = static_cast<uint8_t>(temp) >> 4;
  temp += static_cast<int>(this->temperature_min_());
  ESP_LOGVV(TAG, "Temperature Climate: %u", temp);
  this->target_temperature = static_cast<float>(temp);

  // Fan
  const uint8_t fan = remote_state[2] & 0x03;
  ESP_LOGVV(TAG, "Fan: %02X", fan);
  switch (fan) {
    case kFanHigh:
      this->fan_mode = climate::CLIMATE_FAN_HIGH;
      break;
    case kFanMed:
      this->fan_mode = climate::CLIMATE_FAN_MEDIUM;
      break;
    case kFanLow:
      this->fan_mode = climate::CLIMATE_FAN_LOW;
      break;
    case kFanAuto:
    default:
      this->fan_mode = climate::CLIMATE_FAN_AUTO;
      break;
  }

  // Swing toggle detection
  if ((remote_state[2] & kSwingMask) == kSwingMask && remote_state[8] == 0x40) {
    ESP_LOGVV(TAG, "Swing toggle pressed");
    if (this->swing_mode == climate::CLIMATE_SWING_OFF) {
      this->swing_mode = climate::CLIMATE_SWING_VERTICAL;
    } else {
      this->swing_mode = climate::CLIMATE_SWING_OFF;
    }
  }

  this->publish_state();
  return true;
}

}  // namespace hitachi_168bit
}  // namespace esphome
