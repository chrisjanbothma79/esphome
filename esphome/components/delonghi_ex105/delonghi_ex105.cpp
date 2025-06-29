#include "delonghi_ex105.h"
#include "esphome/components/remote_base/remote_base.h"

namespace esphome {
namespace delonghi_ex105 {

static const char *const TAG = "delonghi.climate";

void DelonghiClimate::setup() {
  this->mode = climate::CLIMATE_MODE_OFF;
  this->target_temperature = 20;
  this->current_temperature = 20;
  this->action = climate::CLIMATE_ACTION_OFF;
  this->publish_state();
}

int mode_to_index(climate::ClimateMode m) {
  switch (m) {
    case climate::CLIMATE_MODE_COOL:     return 0;
    case climate::CLIMATE_MODE_DRY:      return 1;
    case climate::CLIMATE_MODE_FAN_ONLY: return 2;
    default:                              return 0;
  }
}


void DelonghiClimate::control(const climate::ClimateCall &call) {
  // 1) Mode → IR
  if (call.get_mode().has_value()) {
  auto new_mode = *call.get_mode();
  if (new_mode == climate::CLIMATE_MODE_OFF) {
    this->pending_command_ = DELONGHI_POWER_TOGGLE;
    this->transmit_state();
    this->mode   = climate::CLIMATE_MODE_OFF;
    this->action = climate::CLIMATE_ACTION_OFF;
    this->publish_state();
    return;
  }
  int target_i = mode_to_index(new_mode);
  if (this->mode == climate::CLIMATE_MODE_OFF) {
    this->pending_command_ = DELONGHI_POWER_TOGGLE;
    this->transmit_state();
    this->mode   = new_mode;
    this->action = (new_mode == climate::CLIMATE_MODE_COOL
                      ? climate::CLIMATE_ACTION_COOLING
                      : climate::CLIMATE_ACTION_IDLE);
    this->publish_state();
    return;
  }
  int delta = (target_i - this->current_mode_index_ + 3) % 3;
  for (int i = 0; i < delta; ++i) {
    this->pending_command_ = DELONGHI_MODE;
    this->transmit_state();
    delay(200);
  }
  // 4) Update state
  this->current_mode_index_ = target_i;
  this->mode   = new_mode;
  this->action = (new_mode == climate::CLIMATE_MODE_COOL
                    ? climate::CLIMATE_ACTION_COOLING
                    : climate::CLIMATE_ACTION_IDLE);
  this->publish_state();
  return;
}
}




void DelonghiClimate::transmit_state() {
  uint16_t remote_state[2];
  remote_state[0] = DELONGHI_ADDRESS;
  remote_state[1] = this->pending_command_;  // use the one we set above

  auto xmt = this->transmitter_->transmit();
  auto *data = xmt.get_data();
  data->set_carrier_frequency(DELONGHI_IR_FREQUENCY);

  // header
  data->mark(DELONGHI_HEADER_MARK);
  data->space(DELONGHI_HEADER_SPACE);

  // send both words LSB-first
  for (uint16_t word : remote_state) {
    uint8_t lsb = word & 0xFF, msb = (word >> 8) & 0xFF;
    for (uint8_t mask = 1; mask; mask <<= 1) {
      data->mark(DELONGHI_BIT_MARK);
      data->space((lsb & mask) ? DELONGHI_ONE_SPACE : DELONGHI_ZERO_SPACE);
    }
    for (uint8_t mask = 1; mask; mask <<= 1) {
      data->mark(DELONGHI_BIT_MARK);
      data->space((msb & mask) ? DELONGHI_ONE_SPACE : DELONGHI_ZERO_SPACE);
    }
  }

  // stop bit
  data->mark(DELONGHI_BIT_MARK);
  data->space(0);

  xmt.perform();
}

uint16_t DelonghiClimate::fan_speed_() {
  uint16_t fan_speed;
  switch (this->fan_mode.value()) {
    case climate::CLIMATE_FAN_LOW:
      fan_speed = DELONGHI_FAN_LOW;
      break;
    case climate::CLIMATE_FAN_MEDIUM:
      fan_speed = DELONGHI_FAN_MEDIUM;
      break;
    case climate::CLIMATE_FAN_HIGH:
      fan_speed = DELONGHI_FAN_HIGH;
      break;
    case climate::CLIMATE_FAN_AUTO:
    default:
      fan_speed = DELONGHI_FAN_AUTO;
  }
  return fan_speed;
}


}  // namespace delonghi
}  // namespace esphome
