// climate_ir_sanyo.cpp

#include "climate_ir_sanyo.h"
#include "esphome/core/log.h"
#include <cstring>

namespace esphome {
namespace climate_ir_sanyo {

const char *const TAG = "climate.climate_ir_sanyo";
const uint8_t TEMP_MIN = 18;
const uint8_t TEMP_MAX = 28;

Frame::Frame() { this->clear(); }

#if VERIFY_GENERATION
void Frame::compare(const Frame &other) {
  char buf[256];

  ESP_LOGD(TAG, "Nibble   :     0     1     2     3     4     5     6     7     8     9    10    11");

  // First line: Hex Nibbles - "Ours"
  ESP_LOGD(TAG, "Expected :     %X     %X     %X     %X     %X     %X     %X     %X     %X     %X     %X     %X",
           nibbles[0], nibbles[1], nibbles[2], nibbles[3], nibbles[4], nibbles[5], nibbles[6], nibbles[7], nibbles[8],
           nibbles[9], nibbles[10], nibbles[11]);

  // Second line: Hex Nibbles - "Theirs"
  ESP_LOGD(TAG, "Generated:     %X     %X     %X     %X     %X     %X     %X     %X     %X     %X     %X     %X",
           other.nibbles[0], other.nibbles[1], other.nibbles[2], other.nibbles[3], other.nibbles[4], other.nibbles[5],
           other.nibbles[6], other.nibbles[7], other.nibbles[8], other.nibbles[9], other.nibbles[10],
           other.nibbles[11]);

  // Fourth line: Binary with mismatches shown as *
  snprintf(buf, sizeof(buf), "Binary   : ");
  for (int i = 0; i < 12; ++i) {
    uint8_t a = nibbles[i];
    uint8_t b = other.nibbles[i];

    char bin[32] = "";
    for (int bit = 3; bit >= 0; --bit) {
      int a_bit = (a >> bit) & 1;
      int b_bit = (b >> bit) & 1;

      if (a_bit == b_bit)
        snprintf(bin + strlen(bin), sizeof(bin) - strlen(bin), "%d", a_bit);
      else
        strncat(bin, "*", sizeof(bin) - strlen(bin) - 1);
    }
    char tmp[8];
    snprintf(tmp, sizeof(tmp), " %s ", bin);
    strncat(buf, tmp, sizeof(buf) - strlen(buf) - 1);
  }

  ESP_LOGD(TAG, "%s", buf);
}
#endif

void Frame::clear() {
  std::memset(this->nibbles, 0, sizeof(this->nibbles));
  nibbles[0] = 0xA;
  nibbles[1] = 0x6;
}

#define TEMPERATURE_BITS (BIT1 | BIT0)

void Frame::set_target_temperature(float temp) {
  int value = int(temp) + 28;
  nibbles[2] = value & 0x0F;
  nibbles[3] = BIT2 | (value >> 4) & TEMPERATURE_BITS;
}

float Frame::get_target_temperature() {
  int8_t temperature = nibbles[2] & 0x0F;
  temperature |= (nibbles[3] & TEMPERATURE_BITS) << 4;
  return float(temperature - 28);
}

void Frame::set_room_temperature(float temp) {
  int value = int(temp) + 28;
  nibbles[4] = value & 0x0F;
  nibbles[5] = BIT2 | (value >> 4) & TEMPERATURE_BITS;
}

float Frame::get_room_temperature() {
  int8_t temperature = nibbles[4] & 0x0F;
  temperature |= (nibbles[5] & TEMPERATURE_BITS) << 4;
  return float(temperature - 28);
}

#define NIGHT_SETBACK_BIT (BIT1)

// Night Setback has the AC gradually increase/reduce the target temperature over a few hours to minimise power
void Frame::set_night_setback(bool on) {
  if (on)
    nibbles[10] |= NIGHT_SETBACK_BIT;
  else
    nibbles[10] &= ~NIGHT_SETBACK_BIT;
}

bool Frame::get_night_setback() { return (nibbles[10] & NIGHT_SETBACK_BIT) != 0; }

#define POWER_BITS_10 (BIT2 | BIT3)
#define POWER_BIT_10 (BIT3)
#define POWER_OFF_BIT_10 (BIT2)

void Frame::set_power(bool on) {
  nibbles[10] &= ~POWER_BITS_10;

  if (on) {
    nibbles[10] |= POWER_BIT_10;
  } else {
    // Weird outlier where this bit of the temperature is cleared when turned off
    nibbles[3] &= ~BIT0;

    nibbles[6] = 0x00;
    nibbles[7] = 0x00;
    nibbles[10] |= POWER_OFF_BIT_10;

    set_target_temperature(4);
  }
}

bool Frame::get_power() { return (nibbles[10] & POWER_BIT_10) != 0; }

#define CLIMATE_MODE_BITS_9 (BIT0 | BIT1)

void Frame::set_mode(climate::ClimateMode mode) {
  nibbles[9] &= ~CLIMATE_MODE_BITS_9;
  nibbles[10] &= ~POWER_BITS_10;

  switch (mode) {
    case climate::CLIMATE_MODE_FAN_ONLY:
      set_power(true);
      nibbles[9] |= 0x0;
      nibbles[10] |= BIT3;
      break;
    case climate::CLIMATE_MODE_COOL:
      set_power(true);
      nibbles[9] |= BIT0;
      nibbles[10] |= BIT3;
      break;
    case climate::CLIMATE_MODE_HEAT:
      set_power(true);
      nibbles[9] |= BIT0 | BIT1;
      nibbles[10] |= BIT3;
      break;
    case climate::CLIMATE_MODE_HEAT_COOL:
    case climate::CLIMATE_MODE_AUTO:
    default:
      set_power(true);
      nibbles[9] |= BIT1;
      nibbles[10] |= BIT3;
      break;
  }
}

climate::ClimateMode Frame::get_mode() {
  uint8_t mode = nibbles[9] & CLIMATE_MODE_BITS_9;
  switch (mode) {
    case 0x0:
      return climate::CLIMATE_MODE_FAN_ONLY;
      break;
    case 0x1:
      return climate::CLIMATE_MODE_COOL;
      break;
    case 0x2:
      return climate::CLIMATE_MODE_HEAT_COOL;
      break;
    case 0x3:
      return climate::CLIMATE_MODE_HEAT;
      break;
    default:
      ESP_LOGW(TAG, "Unknown mode = %u", mode);
      return climate::CLIMATE_MODE_HEAT_COOL;
      break;
  }
}

#define FAN_MODE_BITS (BIT0 | BIT1)

void Frame::set_fan_mode(climate::ClimateFanMode fan) {
  switch (fan) {
    case climate::CLIMATE_FAN_AUTO:
      nibbles[8] = (nibbles[8] & ~FAN_MODE_BITS) | 0x00;
      break;
    case climate::CLIMATE_FAN_HIGH:
      nibbles[8] = (nibbles[8] & ~FAN_MODE_BITS) | BIT0;
      break;
    case climate::CLIMATE_FAN_LOW:
      nibbles[8] = (nibbles[8] & ~FAN_MODE_BITS) | BIT1;
      break;
    case climate::CLIMATE_FAN_MEDIUM:
      nibbles[8] = (nibbles[8] & ~FAN_MODE_BITS) | BIT0 | BIT1;
      break;
  }
}

climate::ClimateFanMode Frame::get_fan_mode() {
  switch (nibbles[8] & FAN_MODE_BITS) {
    case 0x0:
      return climate::CLIMATE_FAN_AUTO;
    case 0x1:
      return climate::CLIMATE_FAN_HIGH;
    case 0x2:
      return climate::CLIMATE_FAN_LOW;
    case 0x3:
      return climate::CLIMATE_FAN_MEDIUM;
  }
}

#define SWING_MODE_BITS (BIT0)

void Frame::set_swing_mode(climate::ClimateSwingMode swing) {
  switch (swing) {
    case climate::CLIMATE_SWING_VERTICAL:
      nibbles[10] |= SWING_MODE_BITS;
      break;
    default:
      nibbles[10] &= ~SWING_MODE_BITS;
  }
}

climate::ClimateSwingMode Frame::get_swing_mode() {
  return (nibbles[10] & SWING_MODE_BITS) ? climate::CLIMATE_SWING_VERTICAL : climate::CLIMATE_SWING_OFF;
}

#define ROOM_SENSING_BIT (BIT2)

void Frame::set_room_sensing(bool on) {
  if (on)
    nibbles[9] |= ROOM_SENSING_BIT;
  else
    nibbles[9] &= ~ROOM_SENSING_BIT;
}
bool Frame::get_room_sensing() { return (nibbles[9] & ROOM_SENSING_BIT) != 0; }

remote_base::NECLikeData Frame::to_bits() {
  this->update_checksum();

  remote_base::NECLikeData data;
  data.bits_.reserve(12 * 4);
  for (int i = 0; i < 12; ++i)
    for (int bit = 0; bit < 4; ++bit)
      data.bits_.push_back((nibbles[i] & (1u << bit)) != 0);
  return data;
}

bool Frame::from_bits(const remote_base::NECLikeData &data_bits) {
  for (int i = 0; i < 12; ++i) {
    nibbles[i] = 0;
    for (int j = 0; j < 4; ++j)
      nibbles[i] = (nibbles[i] >> 1) | (data_bits.bits_[i * 4 + j] ? (1 << 3) : 0);
  }

  uint8_t checksum = calculate_checksum();
  if (checksum == nibbles[11])
    return true;

  ESP_LOGW(TAG, "Invalid checksum: Got %1X, expected %1X", checksum, nibbles[11]);
}

uint8_t Frame::calculate_checksum() {
  uint8_t sum = 0;
  for (int i = 2; i < 11; ++i)
    sum += nibbles[i] & 0x0F;
  return sum & 0x0F;
}

void Frame::update_checksum() { nibbles[11] = calculate_checksum(); }

// SanyoIrClimate implementation
SanyoIrClimate::SanyoIrClimate()
    : climate_ir::ClimateIR(
          TEMP_MIN, TEMP_MAX, 1.0f, false, true,
          {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH},
          {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL}) {}

void SanyoIrClimate::set_room_sensing(bool on) { frame.set_room_sensing(on); }

bool SanyoIrClimate::get_room_sensing() { return frame.get_room_sensing(); }

void SanyoIrClimate::set_night_setback(bool on) { frame.set_night_setback(on); }

bool SanyoIrClimate::get_night_setback() { return frame.get_night_setback(); }

void SanyoIrClimate::transmit_state() {
  // Remove this clear after testing
  frame.clear();
  frame.set_target_temperature(this->target_temperature);
  frame.set_room_temperature(this->current_temperature);

  bool on = this->mode != climate::CLIMATE_MODE_OFF;
  if (on) {
    // Don't clobber the previous mode when we turn off
    frame.set_mode(this->mode);
  }
  frame.set_power(on);
  frame.set_fan_mode(this->fan_mode.value());
  frame.set_swing_mode(this->swing_mode);
  auto data = frame.to_bits();
  remote_base::NECLikeProtocol protocol;
  auto tx = this->transmitter_->transmit();
  protocol.encode(tx.get_data(), data);
  tx.perform();
}

bool SanyoIrClimate::on_receive(remote_base::RemoteReceiveData src) {
  auto opt = remote_base::NECLikeProtocol().decode(src);
  if (!opt.has_value())
    return false;
  if (!frame.from_bits(*opt)) {
    return false;
  }

  if (frame.get_power() && frame.get_mode() != climate::CLIMATE_MODE_FAN_ONLY) {
    this->target_temperature = frame.get_target_temperature();
  }
  this->current_temperature = frame.get_room_temperature();

  // Mode and power are tracked independantly
  this->mode = frame.get_mode();
  if (!frame.get_power()) {
    this->mode = climate::CLIMATE_MODE_OFF;
  }

  this->fan_mode = frame.get_fan_mode();
  this->swing_mode = frame.get_swing_mode();
  this->set_room_sensing(frame.get_room_sensing());
  this->publish_state();
  this->dump_state_();

#if VERIFY_GENERATION
  {
    Frame test_frame;
    test_frame.clear();
    test_frame.set_target_temperature(frame.get_target_temperature());
    test_frame.set_room_temperature(frame.get_room_temperature());
    test_frame.set_mode(frame.get_mode());
    test_frame.set_power(frame.get_power());
    test_frame.set_fan_mode(frame.get_fan_mode());
    test_frame.set_swing_mode(frame.get_swing_mode());
    test_frame.set_room_sensing(frame.get_room_sensing());
    test_frame.set_night_setback(frame.get_night_setback());
    test_frame.to_bits();
    frame.compare(test_frame);
  }
#endif

  return true;
}

void SanyoIrClimate::dump_state_() {
  ESP_LOGD(TAG, "Sanyo state: target=%.1f°C, room=%.1f°C, mode=%u, fan=%u, swing=%u, room_sensing=%s night_setback=%s",
           this->target_temperature, this->current_temperature, static_cast<uint32_t>(this->mode),
           static_cast<uint32_t>(this->fan_mode.value()), static_cast<uint32_t>(this->swing_mode),
           this->get_room_sensing() ? "true" : "false", this->get_night_setback() ? "true" : "false");
}

}  // namespace climate_ir_sanyo
}  // namespace esphome
