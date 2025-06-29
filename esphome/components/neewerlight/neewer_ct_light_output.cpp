#include "neewer_ct_light_output.h"
#include "neewer_state_output.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight {

void NeewerCTLightOutput::dump_config() {
  ESP_LOGCONFIG(TAG, "Neewer CT Light Output:");
  ESP_LOGCONFIG(TAG, "  MAC address        : %s", this->parent_->address_str().c_str());
  ESP_LOGCONFIG(TAG, "  Service UUID       : %s", this->service_uuid_.to_string().c_str());
  ESP_LOGCONFIG(TAG, "  Characteristic UUID: %s", this->char_uuid_.to_string().c_str());
  ESP_LOGCONFIG(TAG, "  Require Response   : %s", this->require_response_ ? "True" : "False");
  ESP_LOGCONFIG(TAG, "  Colour Temperatures: %.2f - %.2f", this->cold_white_temperature_,
                this->warm_white_temperature_);
  LOG_BINARY_OUTPUT(this);
};

// color_temperature is between 0.0 (coldest) and 1.0 (warmest)
void NeewerCTLightOutput::prepare_ct_brightness_msg(float color_temperature, float brightness) {
  // the normalized color_temperature must apply to mireds, it's not linear in Kelvin!
  float mireds = COLD_WHITE - color_temperature * (COLD_WHITE - WARM_WHITE);
  uint8_t ct = (uint8_t) round(1e6f / mireds / 100.f);
  ESP_LOGD(TAG, "Value color_temperature to be set is 0x%1x (%d)", ct, ct);
  uint8_t b = (uint8_t) round(brightness * 100.f);
  ESP_LOGD(TAG, "Value brightness to be set is 0x%1x (%d)", b, b);

  this->orig_msg_clear();

  this->orig_msg_[0] = this->command_prefix_;
  this->orig_msg_[1] = this->ct_brightness_prefix_;
  this->orig_msg_[2] = 2;   // Byte Count = 2 for ct & brightness
  this->orig_msg_[3] = b;   // brightness 0x00 - 0x64
  this->orig_msg_[4] = ct;  // color_temp 0x1B - 0x41 (27 - 65 because of 2700K - 6500K)
  this->orig_msg_len_ = 5;

  NeewerBLEOutput::build_msg_with_checksum();
};

// For whatever reason, the Neewer will only allow brightness alone if CT hasn't changed
void NeewerCTLightOutput::prepare_brightness_msg(float brightness) {
  uint8_t b = (uint8_t) round(brightness * 100.0f);
  ESP_LOGD(TAG, "Value brightness to be set is 0x%1x (%d)", b, b);

  this->orig_msg_clear();

  this->orig_msg_[0] = this->command_prefix_;
  this->orig_msg_[1] = this->ct_brightness_prefix_;
  this->orig_msg_[2] = 1;  // Byte Count = 1 for just brightness
  this->orig_msg_[3] = b;  // brightness 0x00 - 0x64
  this->orig_msg_len_ = 4;

  NeewerBLEOutput::build_msg_with_checksum();
};

void NeewerCTLightOutput::write_state(light::LightState *state) {
  // Call original write state to set new values for each state.
  float color_temperature, brightness;
  state->current_values_as_ct(&color_temperature, &brightness);

  if (color_temperature != this->old_color_temperature_) {
    ESP_LOGD(TAG, "Color temperature changed.");
    if (brightness != this->old_brightness_) {
      ESP_LOGD(TAG, "Brightness changed.");
    }
    this->prepare_ct_brightness_msg(color_temperature, brightness);
  } else if (brightness != this->old_brightness_) {
    ESP_LOGD(TAG, "Only brightness changed.");
    this->prepare_brightness_msg(brightness);
  }

  // We're probably done with the old values now, so let's change them up.
  this->old_color_temperature_ = color_temperature;
  this->old_brightness_ = brightness;

  // Message having been prepared, we can send it off into the sunset.
  NeewerBLEOutput::write_state(1.0);

  // Do whatever else setting the current levels individually accomplishes
  this->color_temperature_->set_level(color_temperature);
  this->brightness_->set_level(brightness);
};

NeewerCTLightOutput::NeewerCTLightOutput() {
  ESP_LOGD(TAG, "NeewerCTLightOutput constructor called");
  this->set_service_uuid_str(SERVICE_UUID);
  this->set_char_uuid_str(CHARACTERISTIC_UUID);

  // Neewer-specific light settings
  this->set_color_temperature(new NeewerStateOutput());
  this->set_brightness(new NeewerStateOutput());
  this->set_cold_white_temperature(COLD_WHITE);
  this->set_warm_white_temperature(WARM_WHITE);

  NeewerBLEOutput();

  // BLE-specific settings
  this->set_require_response(true);
};

}  // namespace neewerlight
}  // namespace esphome

#endif  // USE_ESP32
