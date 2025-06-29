#include "neewer_ct_light_output.h"
#include "neewer_state_output.h"
#include "utils.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

void NeewerCTLightOutput::dump_config() {
  ESP_LOGCONFIG(TAG, "Neewer CT Light Output:");
  ESP_LOGCONFIG(TAG, "  MAC address        : %s", this->parent_->address_str().c_str());
  ESP_LOGCONFIG(TAG, "  Service UUID       : %s", this->service_uuid_.to_string().c_str());
  ESP_LOGCONFIG(TAG, "  Characteristic UUID: %s", this->char_uuid_.to_string().c_str());
  ESP_LOGCONFIG(TAG, "  Require Response   : %s", this->require_response_ ? "True" : "False");
  ESP_LOGCONFIG(TAG, "  Colour Temperatures: %d K - %d K", utils::mireds_to_kelvin_int(this->warm_white_temperature_),
                utils::mireds_to_kelvin_int(this->cold_white_temperature_));
  LOG_BINARY_OUTPUT(this);
};

// ct_normalized is between 0.0 (coldest) and 1.0 (warmest)
void NeewerCTLightOutput::prepare_ct_brightness_msg(float ct_normalized, float brightness) {
  // normalized color temperature must apply to mireds, it's not linear in Kelvin!
  float ct_mireds =
      this->cold_white_temperature_ - ct_normalized * (this->cold_white_temperature_ - this->warm_white_temperature_);
  float ct_kelvin = utils::mireds_to_kelvin(ct_mireds);

  // neewer light expects value 0x1B (27) for 2700K or 0x41 (65) for 6500K
  uint8_t ct = static_cast<uint8_t>(std::round(ct_kelvin / 100.f));
  ESP_LOGD(TAG, "Color temperature will be set to 0x%1x (%d)", ct, ct);

  // expected value for brightness is 0 - 100 (0x00 - 0x64)
  uint8_t b = static_cast<uint8_t>(std::round(brightness * 100.f));
  ESP_LOGD(TAG, "Brightness will be set to 0x%1x (%d)", b, b);

  this->orig_msg_clear();

  this->orig_msg_[0] = NeewerBLEOutput::COMMAND_PREFIX;
  this->orig_msg_[1] = NeewerBLEOutput::CT_BRIGHTNESS_PREFIX;
  this->orig_msg_[2] = 2;  // Byte Count = 2 for ct & brightness
  this->orig_msg_[3] = b;
  this->orig_msg_[4] = ct;
  this->orig_msg_len_ = 5;

  NeewerBLEOutput::build_msg_with_checksum();
};

// For whatever reason, the Neewer will only allow brightness alone if CT hasn't changed
void NeewerCTLightOutput::prepare_brightness_msg(float brightness) {
  uint8_t b = static_cast<uint8_t>(std::round(brightness * 100.f));
  ESP_LOGD(TAG, "Brightness will be set to 0x%1x (%d)", b, b);

  this->orig_msg_clear();

  this->orig_msg_[0] = NeewerBLEOutput::COMMAND_PREFIX;
  this->orig_msg_[1] = NeewerBLEOutput::CT_BRIGHTNESS_PREFIX;
  this->orig_msg_[2] = 1;  // Byte Count = 1 for just brightness
  this->orig_msg_[3] = b;
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
  this->set_service_uuid_str(SERVICE_UUID);
  this->set_char_uuid_str(CHARACTERISTIC_UUID);
  this->set_color_temperature(new NeewerStateOutput());
  this->set_brightness(new NeewerStateOutput());

  NeewerBLEOutput();

  // BLE-specific settings
  this->set_require_response(true);
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
