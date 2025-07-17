#include "template_select.h"
#include "esphome/core/log.h"
#include <algorithm>

namespace esphome {
namespace template_ {

static const char *const TAG = "template.select";

void TemplateSelect::setup() {
  // Update options from lambda first if available
  this->update_options_from_lambda_();

  if (this->f_.has_value())
    return;

  std::string value;
  ESP_LOGD(TAG, "Setting up");
  if (!this->restore_value_) {
    value = this->initial_option_;
    ESP_LOGD(TAG, "State from initial: %s", value.c_str());
  } else {
    size_t index;
    this->pref_ = global_preferences->make_preference<size_t>(this->get_object_id_hash());
    if (!this->pref_.load(&index)) {
      value = this->initial_option_;
      ESP_LOGD(TAG, "State from initial (could not load stored index): %s", value.c_str());
    } else if (!this->has_index(index)) {
      value = this->initial_option_;
      ESP_LOGD(TAG, "State from initial (restored index %d out of bounds): %s", index, value.c_str());
    } else {
      value = this->at(index).value();
      ESP_LOGD(TAG, "State from restore: %s", value.c_str());
    }
  }

  this->publish_state(value);
}

void TemplateSelect::update() {
  // Update options from lambda if available
  this->update_options_from_lambda_();

  if (!this->f_.has_value())
    return;

  auto val = (*this->f_)();
  if (!val.has_value())
    return;

  if (!this->has_option(*val)) {
    ESP_LOGE(TAG, "Lambda returned an invalid option: %s", (*val).c_str());
    return;
  }

  this->publish_state(*val);
}

void TemplateSelect::control(const std::string &value) {
  this->set_trigger_->trigger(value);

  if (this->optimistic_)
    this->publish_state(value);

  if (this->restore_value_) {
    auto index = this->index_of(value);
    this->pref_.save(&index.value());
  }
}

void TemplateSelect::dump_config() {
  LOG_SELECT("", "Template Select", this);
  LOG_UPDATE_INTERVAL(this);
  if (this->f_.has_value())
    return;
  ESP_LOGCONFIG(TAG,
                "  Optimistic: %s\n"
                "  Initial Option: %s\n"
                "  Restore Value: %s",
                YESNO(this->optimistic_), this->initial_option_.c_str(), YESNO(this->restore_value_));
}

void TemplateSelect::set_options(const std::vector<std::string> &options) {
  this->traits.set_options(options);
  ESP_LOGD(TAG, "Updated options list with %d items", options.size());

  // Validate current state is still valid after options change
  if (!this->state.empty() && !this->has_option(this->state)) {
    ESP_LOGW(TAG, "Current state '%s' is no longer a valid option after options update", this->state.c_str());
    if (!options.empty()) {
      ESP_LOGD(TAG, "Setting state to first available option: %s", options[0].c_str());
      this->publish_state(options[0]);
    }
  }
}

void TemplateSelect::add_option(const std::string &option) {
  auto current_options = this->traits.get_options();

  // Check if option already exists
  for (const auto &existing_option : current_options) {
    if (existing_option == option) {
      ESP_LOGD(TAG, "Option '%s' already exists", option.c_str());
      return;
    }
  }

  current_options.push_back(option);
  this->traits.set_options(current_options);
  ESP_LOGD(TAG, "Added option: %s", option.c_str());
}

void TemplateSelect::remove_option(const std::string &option) {
  auto current_options = this->traits.get_options();
  auto it = std::find(current_options.begin(), current_options.end(), option);

  if (it == current_options.end()) {
    ESP_LOGW(TAG, "Cannot remove option '%s' - not found", option.c_str());
    return;
  }

  current_options.erase(it);
  this->traits.set_options(current_options);
  ESP_LOGD(TAG, "Removed option: %s", option.c_str());

  // If the removed option was the current state, update to first available option
  if (this->state == option && !current_options.empty()) {
    ESP_LOGD(TAG, "Removed option was current state, setting to: %s", current_options[0].c_str());
    this->publish_state(current_options[0]);
  }
}

void TemplateSelect::clear_and_set_options(const std::vector<std::string> &options) {
  this->traits.set_options(options);
  ESP_LOGD(TAG, "Cleared and set %d new options", options.size());

  // Update state to first option if current state is invalid
  if (!options.empty() && (this->state.empty() || !this->has_option(this->state))) {
    ESP_LOGD(TAG, "Setting state to first option: %s", options[0].c_str());
    this->publish_state(options[0]);
  }
}

void TemplateSelect::update_options_from_lambda_() {
  if (!this->options_f_.has_value())
    return;

  auto new_options = (*this->options_f_)();
  if (new_options.empty()) {
    ESP_LOGW(TAG, "Options lambda returned empty list");
    return;
  }

  // Check if options have actually changed to avoid unnecessary updates
  auto current_options = this->traits.get_options();
  if (current_options != new_options) {
    ESP_LOGD(TAG, "Options updated from lambda");
    this->set_options(new_options);
  }
}

}  // namespace template_
}  // namespace esphome
