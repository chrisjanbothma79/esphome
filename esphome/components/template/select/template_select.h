#pragma once

#include "esphome/components/select/select.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace template_ {

class TemplateSelect : public select::Select, public PollingComponent {
 public:
  void set_template(std::function<optional<std::string>()> &&f) { this->f_ = f; }
  void set_options_template(std::function<std::vector<std::string>()> &&f) { this->options_f_ = f; }

  void setup() override;
  void update() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  Trigger<std::string> *get_set_trigger() const { return this->set_trigger_; }
  void set_optimistic(bool optimistic) { this->optimistic_ = optimistic; }
  void set_initial_option(const std::string &initial_option) { this->initial_option_ = initial_option; }
  void set_restore_value(bool restore_value) { this->restore_value_ = restore_value; }

  /// Update the options list at runtime
  void set_options(const std::vector<std::string> &options);

  /// Add an option at runtime
  void add_option(const std::string &option);

  /// Remove an option at runtime
  void remove_option(const std::string &option);

  /// Clear all options and set new ones
  void clear_and_set_options(const std::vector<std::string> &options);

 protected:
  void control(const std::string &value) override;
  /// Update options from lambda if available
  void update_options_from_lambda_();

  bool optimistic_ = false;
  std::string initial_option_;
  bool restore_value_ = false;
  Trigger<std::string> *set_trigger_ = new Trigger<std::string>();
  optional<std::function<optional<std::string>()>> f_;
  optional<std::function<std::vector<std::string>()>> options_f_;

  ESPPreferenceObject pref_;
};

}  // namespace template_
}  // namespace esphome
