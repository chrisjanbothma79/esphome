#include "humdifier.h"
#include "esphome/core/macros.h"

namespace esphome {
namespace humdifier {

static const char *const TAG = "humdifier";

void HumdifierCall::perform() {
  this->parent_->control_callback_.call(*this);
  ESP_LOGD(TAG, "'%s' - Setting", this->parent_->get_name().c_str());
  this->validate_();
  if (this->mode_.has_value()) {
    const LogString *mode_s = humdifier_mode_to_string(*this->mode_);
    ESP_LOGD(TAG, "  Mode: %s", LOG_STR_ARG(mode_s));
  }
  if (this->target_humidity_low_.has_value()) {
    ESP_LOGD(TAG, "  Target Humidity Low: %.2f", *this->target_humidity_low_);
  }
  if (this->target_humidity_high_.has_value()) {
    ESP_LOGD(TAG, "  Target Humidity High: %.2f", *this->target_humidity_high_);
  }
  this->parent_->control(*this);
}
void HumdifierCall::validate_() {
  auto traits = this->parent_->get_traits();
  if (this->mode_.has_value()) {
    auto mode = *this->mode_;
    if (!traits.supports_mode(mode)) {
      ESP_LOGW(TAG, "  Mode %s is not supported by this device!", LOG_STR_ARG(humdifier_mode_to_string(mode)));
      this->mode_.reset();
    }
  }
  if (this->target_humidity_low_.has_value() || this->target_humidity_high_.has_value()) {
    if (!traits.get_supports_two_point_target_humidity()) {
      ESP_LOGW(TAG, "  Cannot set low/high target humidity for this device!");
      this->target_humidity_low_.reset();
      this->target_humidity_high_.reset();
    }
  }
  if (this->target_humidity_low_.has_value() && std::isnan(*this->target_humidity_low_)) {
    ESP_LOGW(TAG, "  Target humidity low must not be NAN!");
    this->target_humidity_low_.reset();
  }
  if (this->target_humidity_high_.has_value() && std::isnan(*this->target_humidity_high_)) {
    ESP_LOGW(TAG, "  Target humidity low must not be NAN!");
    this->target_humidity_high_.reset();
  }
  if (this->target_humidity_low_.has_value() && this->target_humidity_high_.has_value()) {
    float low = *this->target_humidity_low_;
    float high = *this->target_humidity_high_;
    if (low > high) {
      ESP_LOGW(TAG, "  Target humidity low %.2f must be smaller than target humidity high %.2f!", low, high);
      this->target_humidity_low_.reset();
      this->target_humidity_high_.reset();
    }
  }
}
HumdifierCall &HumdifierCall::set_mode(HumdifierMode mode) {
  this->mode_ = mode;
  return *this;
}
HumdifierCall &HumdifierCall::set_mode(const std::string &mode) {
  if (str_equals_case_insensitive(mode, "OFF")) {
    this->set_mode(HUMDIFIER_MODE_OFF);
  } else if (str_equals_case_insensitive(mode, "ON")) {
    this->set_mode(HUMDIFIER_MODE_ON);
  } else {
    ESP_LOGW(TAG, "'%s' - Unrecognized mode %s", this->parent_->get_name().c_str(), mode.c_str());
  }
  return *this;
}
HumdifierCall &HumdifierCall::set_target_humidity_low(float target_humidity_low) {
  this->target_humidity_low_ = target_humidity_low;
  return *this;
}
HumdifierCall &HumdifierCall::set_target_humidity_high(float target_humidity_high) {
  this->target_humidity_high_ = target_humidity_high;
  return *this;
}

const optional<HumdifierMode> &HumdifierCall::get_mode() const { return this->mode_; }
const optional<float> &HumdifierCall::get_target_humidity_low() const { return this->target_humidity_low_; }
const optional<float> &HumdifierCall::get_target_humidity_high() const { return this->target_humidity_high_; }
HumdifierCall &HumdifierCall::set_target_humidity_high(optional<float> target_humidity_high) {
  this->target_humidity_high_ = target_humidity_high;
  return *this;
}
HumdifierCall &HumdifierCall::set_target_humidity_low(optional<float> target_humidity_low) {
  this->target_humidity_low_ = target_humidity_low;
  return *this;
}
HumdifierCall &HumdifierCall::set_mode(optional<HumdifierMode> mode) {
  this->mode_ = mode;
  return *this;
}

void Humdifier::add_on_state_callback(std::function<void(Humdifier &)> &&callback) {
  this->state_callback_.add(std::move(callback));
}

void Humdifier::add_on_control_callback(std::function<void(HumdifierCall &)> &&callback) {
  this->control_callback_.add(std::move(callback));
}

void Humdifier::save_state_() {
  state.mode = this->mode;
  //auto traits = this->get_traits();
  //if (traits.get_supports_two_point_target_humidity()) {
  state.target_humidity_low = this->target_humidity_low;
  state.target_humidity_high = this->target_humidity_high;
  this->rtc_.save(&state);
}
void Humdifier::publish_state() {
  ESP_LOGD(TAG, "'%s' - Sending state:", this->name_.c_str());
  auto traits = this->get_traits();

  ESP_LOGD(TAG, "  Mode: %s", LOG_STR_ARG(humdifier_mode_to_string(this->mode)));
  if (traits.get_supports_action()) {
    ESP_LOGD(TAG, "  Action: %s", LOG_STR_ARG(humdifier_action_to_string(this->action)));
  }
  if (traits.get_supports_current_humidity()) {
    ESP_LOGD(TAG, "  Current Humidity: %.2f°C", this->current_humidity);
  }
  ESP_LOGD(TAG, "  Target Humidity: Low: %.2f°C High: %.2f°C", this->target_humidity_low,
           this->target_humidity_high);
  if (traits.get_supports_current_humidity()) {
    ESP_LOGD(TAG, "  Current Humidity: %.0f%%", this->current_humidity);
  }

  // Send state to frontend
  this->state_callback_.call(*this);
  // Save state
  this->save_state_();
}

HumdifierTraits Humdifier::get_traits() {
  auto traits = this->traits();
  if (this->visual_min_humidity_override_.has_value()) {
    traits.set_visual_min_humidity(*this->visual_min_humidity_override_);
  }
  if (this->visual_max_humidity_override_.has_value()) {
    traits.set_visual_max_humidity(*this->visual_max_humidity_override_);
  }
  if (this->visual_target_humidity_step_override_.has_value()) {
    traits.set_visual_target_humidity_step(*this->visual_target_humidity_step_override_);
    traits.set_visual_current_humidity_step(*this->visual_current_humidity_step_override_);
  }
  if (this->visual_min_humidity_override_.has_value()) {
    traits.set_visual_min_humidity(*this->visual_min_humidity_override_);
  }
  if (this->visual_max_humidity_override_.has_value()) {
    traits.set_visual_max_humidity(*this->visual_max_humidity_override_);
  }

  return traits;
}

void Humdifier::set_visual_min_humidity_override(float visual_min_humidity_override) {
  this->visual_min_humidity_override_ = visual_min_humidity_override;
}
void Humdifier::set_visual_max_humidity_override(float visual_max_humidity_override) {
  this->visual_max_humidity_override_ = visual_max_humidity_override;
}
void Humdifier::set_visual_humidity_step_override(float target, float current) {
  this->visual_target_humidity_step_override_ = target;
  this->visual_current_humidity_step_override_ = current;
}
void Humdifier::set_visual_min_humidity_override(float visual_min_humidity_override) {
  this->visual_min_humidity_override_ = visual_min_humidity_override;
}
void Humdifier::set_visual_max_humidity_override(float visual_max_humidity_override) {
  this->visual_max_humidity_override_ = visual_max_humidity_override;
}

HumdifierCall Humdifier::make_call() { return HumdifierCall(this); }

HumdifierCall HumdifierDeviceRestoreState::to_call(Humdifier *humdifier) {
  auto call = humdifier->make_call();
  auto traits = humdifier->get_traits();
  call.set_mode(this->mode);
  if (traits.get_supports_two_point_target_humidity()) {
    call.set_target_humidity_low(this->target_humidity_low);
    call.set_target_humidity_high(this->target_humidity_high);
  } else {
    call.set_target_humidity(this->target_humidity);
  }
  if (traits.get_supports_target_humidity()) {
    call.set_target_humidity(this->target_humidity);
  }
  if (traits.get_supports_fan_modes() || !traits.get_supported_custom_fan_modes().empty()) {
    call.set_fan_mode(this->fan_mode);
  }
  if (traits.get_supports_presets() || !traits.get_supported_custom_presets().empty()) {
    call.set_preset(this->preset);
  }
  if (traits.get_supports_swing_modes()) {
    call.set_swing_mode(this->swing_mode);
  }
  return call;
}
void HumdifierDeviceRestoreState::apply(Humdifier *humdifier) {
  auto traits = humdifier->get_traits();
  humdifier->mode = this->mode;
  if (traits.get_supports_two_point_target_humidity()) {
    humdifier->target_humidity_low = this->target_humidity_low;
    humdifier->target_humidity_high = this->target_humidity_high;
  } else {
    humdifier->target_humidity = this->target_humidity;
  }
  if (traits.get_supports_target_humidity()) {
    humdifier->target_humidity = this->target_humidity;
  }
  if (traits.get_supports_fan_modes() && !this->uses_custom_fan_mode) {
    humdifier->fan_mode = this->fan_mode;
  }
  if (!traits.get_supported_custom_fan_modes().empty() && this->uses_custom_fan_mode) {
    // std::set has consistent order (lexicographic for strings), so this is ok
    const auto &modes = traits.get_supported_custom_fan_modes();
    std::vector<std::string> modes_vec{modes.begin(), modes.end()};
    if (custom_fan_mode < modes_vec.size()) {
      humdifier->custom_fan_mode = modes_vec[this->custom_fan_mode];
    }
  }
  if (traits.get_supports_presets() && !this->uses_custom_preset) {
    humdifier->preset = this->preset;
  }
  if (!traits.get_supported_custom_presets().empty() && uses_custom_preset) {
    // std::set has consistent order (lexicographic for strings), so this is ok
    const auto &presets = traits.get_supported_custom_presets();
    std::vector<std::string> presets_vec{presets.begin(), presets.end()};
    if (custom_preset < presets_vec.size()) {
      humdifier->custom_preset = presets_vec[this->custom_preset];
    }
  }
  if (traits.get_supports_swing_modes()) {
    humdifier->swing_mode = this->swing_mode;
  }
  humdifier->publish_state();
}

template<typename T1, typename T2> bool set_alternative(optional<T1> &dst, optional<T2> &alt, const T1 &src) {
  bool is_changed = alt.has_value();
  alt.reset();
  if (is_changed || dst != src) {
    dst = src;
    is_changed = true;
  }
  return is_changed;
}

bool Humdifier::set_fan_mode_(HumdifierFanMode mode) {
  return set_alternative(this->fan_mode, this->custom_fan_mode, mode);
}

bool Humdifier::set_custom_fan_mode_(const std::string &mode) {
  return set_alternative(this->custom_fan_mode, this->fan_mode, mode);
}

bool Humdifier::set_preset_(HumdifierPreset preset) { return set_alternative(this->preset, this->custom_preset, preset); }

bool Humdifier::set_custom_preset_(const std::string &preset) {
  return set_alternative(this->custom_preset, this->preset, preset);
}

void Humdifier::dump_traits_(const char *tag) {
  auto traits = this->get_traits();
  ESP_LOGCONFIG(tag, "HumdifierTraits:");
  ESP_LOGCONFIG(tag,
                "  [x] Visual settings:\n"
                "      - Min humidity: %.1f\n"
                "      - Max humidity: %.1f\n"
                "      - Humidity step:\n"
                "          Target: %.1f",
                traits.get_visual_min_humidity(), traits.get_visual_max_humidity(),
                traits.get_visual_target_humidity_step());
  if (traits.get_supports_current_humidity()) {
    ESP_LOGCONFIG(tag, "          Current: %.1f", traits.get_visual_current_humidity_step());
  }
  if (traits.get_supports_target_humidity() || traits.get_supports_current_humidity()) {
    ESP_LOGCONFIG(tag,
                  "      - Min humidity: %.0f\n"
                  "      - Max humidity: %.0f",
                  traits.get_visual_min_humidity(), traits.get_visual_max_humidity());
  }
  if (traits.get_supports_two_point_target_humidity()) {
    ESP_LOGCONFIG(tag, "  [x] Supports two-point target humidity");
  }
  if (traits.get_supports_current_humidity()) {
    ESP_LOGCONFIG(tag, "  [x] Supports current humidity");
  }
  if (traits.get_supports_target_humidity()) {
    ESP_LOGCONFIG(tag, "  [x] Supports target humidity");
  }
  if (traits.get_supports_current_humidity()) {
    ESP_LOGCONFIG(tag, "  [x] Supports current humidity");
  }
  if (traits.get_supports_action()) {
    ESP_LOGCONFIG(tag, "  [x] Supports action");
  }
  if (!traits.get_supported_modes().empty()) {
    ESP_LOGCONFIG(tag, "  [x] Supported modes:");
    for (HumdifierMode m : traits.get_supported_modes())
      ESP_LOGCONFIG(tag, "      - %s", LOG_STR_ARG(humdifier_mode_to_string(m)));
  }
  if (!traits.get_supported_fan_modes().empty()) {
    ESP_LOGCONFIG(tag, "  [x] Supported fan modes:");
    for (HumdifierFanMode m : traits.get_supported_fan_modes())
      ESP_LOGCONFIG(tag, "      - %s", LOG_STR_ARG(humdifier_fan_mode_to_string(m)));
  }
  if (!traits.get_supported_custom_fan_modes().empty()) {
    ESP_LOGCONFIG(tag, "  [x] Supported custom fan modes:");
    for (const std::string &s : traits.get_supported_custom_fan_modes())
      ESP_LOGCONFIG(tag, "      - %s", s.c_str());
  }
  if (!traits.get_supported_presets().empty()) {
    ESP_LOGCONFIG(tag, "  [x] Supported presets:");
    for (HumdifierPreset p : traits.get_supported_presets())
      ESP_LOGCONFIG(tag, "      - %s", LOG_STR_ARG(humdifier_preset_to_string(p)));
  }
  if (!traits.get_supported_custom_presets().empty()) {
    ESP_LOGCONFIG(tag, "  [x] Supported custom presets:");
    for (const std::string &s : traits.get_supported_custom_presets())
      ESP_LOGCONFIG(tag, "      - %s", s.c_str());
  }
  if (!traits.get_supported_swing_modes().empty()) {
    ESP_LOGCONFIG(tag, "  [x] Supported swing modes:");
    for (HumdifierSwingMode m : traits.get_supported_swing_modes())
      ESP_LOGCONFIG(tag, "      - %s", LOG_STR_ARG(humdifier_swing_mode_to_string(m)));
  }
}

}  // namespace humdifier
}  // namespace esphome
