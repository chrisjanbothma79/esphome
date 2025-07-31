#pragma once

#include "esphome/core/component.h"
#include "esphome/core/entity_base.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace climate {

#define LOG_HUMDIFIER(prefix, type, obj) \
  if ((obj) != nullptr) { \
    ESP_LOGCONFIG(TAG, "%s%s '%s'", prefix, LOG_STR_LITERAL(type), (obj)->get_name().c_str()); \
  }

class Humdifier;

/** This class is used to encode all control actions on a humdifier device.
 *
 * It is supposed to be used by all code that wishes to control a humdifier device (mqtt, api, lambda etc).
 * Create an instance of this class by calling `id(humdifier_device).make_call();`. Then set all attributes
 * with the `set_x` methods. Finally, to apply the changes call `.perform();`.
 *
 * The integration that implements the humdifier device receives this instance with the `control` method.
 * It should check all the properties it implements and apply them as needed. It should do so by
 * getting all properties it controls with the getter methods in this class. If the optional value is
 * set (check with `.has_value()`) that means the user wants to control this property. Get the value
 * of the optional with the star operator (`*call.get_mode()`) and apply it.
 */
class HumdifierCall {
 public:
  explicit HumdifierCall(Humdifier *parent) : parent_(parent) {}

  /// Set the mode of the humdifier device.
  HumdifierCall &set_mode(HumdifierMode mode);
  /// Set the mode of the humdifier device.
  HumdifierCall &set_mode(optional<HumdifierMode> mode);
  /// Set the mode of the humdifier device based on a string.
  HumdifierCall &set_mode(const std::string &mode);
  /** Set the low point target humidity of the humdifier device
   *
   * For humdifier devices with two point target humidity control
   */
  HumdifierCall &set_target_humidity_low(float target_humidity_low);
  /** Set the low point target humidity of the humdifier device
   *
   * For humdifier devices with two point target humidity control
   */
  HumdifierCall &set_target_humidity_low(optional<float> target_humidity_low);
  /** Set the high point target humidity of the humdifier device
   *
   * For humdifier devices with two point target humidity control
   */
  HumdifierCall &set_target_humidity_high(float target_humidity_high);
  /** Set the high point target humidity of the humdifier device
   *
   * For humdifier devices with two point target humidity control
   */
  HumdifierCall &set_target_humidity_high(optional<float> target_humidity_high);

  void perform();

  const optional<HumdifierMode> &get_mode() const;
  const optional<float> &get_target_humidity_low() const;
  const optional<float> &get_target_humidity_high() const;

 protected:
  void validate_();

  Humdifier *const parent_;
  optional<HumdifierMode> mode_;
  optional<float> target_humidity_low_;
  optional<float> target_humidity_high_;
};

/**
 * HumdifierDevice - This is the base class for all humdifier integrations. Each integration
 * needs to extend this class and implement two functions:
 *
 *  - get_traits() - return the static traits of the humdifier device
 *  - control(HumdifierDeviceCall call) - Apply the given changes from call.
 *
 * To write data to the frontend, the integration must first set the properties using
 * this->property = value; (for example this->current_humidity = 42.0;); then the integration
 * must call this->publish_state(); to send the entire state to the frontend.
 *
 * The entire state of the humdifier device is encoded in public properties of the base class (current_humidity,
 * mode etc). These are read-only for the user and rw for integrations. The reason these are public
 * is for simple access to them from lambdas `if (id(my_humdifier).mode == humdifier::HUMDIFIER_MODE_HEAT_COOL) ...`
 */
class Humdifier : public EntityBase {
 public:
  Humdifier() {}

  /// The active mode of the humdifier device.
  HumdifierMode mode{HUMDIFIER_MODE_OFF};

  /// The active state of the humdifier device.
  HumdifierAction action{HUMDIFIER_ACTION_OFF};

  /// The current humidity of the humdifier device, as reported from the integration.
  float current_humidity{NAN};

  /// The minimum target humidity of the humdifier device, for humdifier devices with split target humidity.
  float target_humidity_low{NAN};
  /// The maximum target humidity of the humdifier device, for humdifier devices with split target humidity.
  float target_humidity_high{NAN};

  /** Add a callback for the humdifier device state, each time the state of the humdifier device is updated
   * (using publish_state), this callback will be called.
   *
   * @param callback The callback to call.
   */
  void add_on_state_callback(std::function<void(Humdifier &)> &&callback);

  /**
   * Add a callback for the humdifier device configuration; each time the configuration parameters of a humdifier device
   * is updated (using perform() of a HumdifierCall), this callback will be called, before any on_state callback.
   *
   * @param callback The callback to call.
   */
  void add_on_control_callback(std::function<void(HumdifierCall &)> &&callback);

  /** Make a humdifier device control call, this is used to control the humdifier device, see the HumdifierCall description
   * for more info.
   * @return A new HumdifierCall instance targeting this humdifier device.
   */
  HumdifierCall make_call();

  /** Publish the state of the humdifier device, to be called from integrations.
   *
   * This will schedule the humdifier device to publish its state to all listeners and save the current state
   * to recover memory.
   */
  void publish_state();

  /** Get the traits of this humdifier device with all overrides applied.
   *
   * Traits are static data that encode the capabilities and static data for a humdifier device such as supported
   * modes, humidity range etc.
   */
  HumdifierTraits get_traits();

  void set_visual_min_humidity_override(float visual_min_humidity_override);
  void set_visual_max_humidity_override(float visual_max_humidity_override);

 protected:
  friend HumdifierCall;

  /** Get the default traits of this humdifier device.
   *
   * Traits are static data that encode the capabilities and static data for a humdifier device such as supported
   * modes, humidity range etc. Each integration must implement this method and the return value must
   * be constant during all of execution time.
   */
  virtual HumdifierTraits traits() = 0;

  /** Control the humdifier device, this is a virtual method that each humdifier integration must implement.
   *
   * See more info in HumdifierCall. The integration should check all of its values in this method and
   * set them accordingly. At the end of the call, the integration must call `publish_state()` to
   * notify the frontend of a changed state.
   *
   * @param call The HumdifierCall instance encoding all attribute changes.
   */
  virtual void control(const HumdifierCall &call) = 0;
  /** Internal method to save the state of the humdifier device to recover memory. This is automatically
   * called from publish_state()
   */
  void save_state_();

  void dump_traits_(const char *tag);

  CallbackManager<void(Humdifier &)> state_callback_{};
  CallbackManager<void(HumdifierCall &)> control_callback_{};
  ESPPreferenceObject rtc_;
  optional<float> visual_min_humidity_override_{};
  optional<float> visual_max_humidity_override_{};
};

}  // namespace humdifier
}  // namespace esphome
