#pragma once

#include "esphome.h"

#ifdef USE_API
namespace esphome {
namespace custom_api_device_component {

using namespace api;

class CustomAPIDeviceComponent : public Component, public CustomAPIDevice {
 public:
  void setup() override {
    // Register services using CustomAPIDevice
    register_service(&CustomAPIDeviceComponent::on_test_service, "custom_test_service");

    register_service(&CustomAPIDeviceComponent::on_service_with_args, "custom_service_with_args",
                     {"arg_string", "arg_int", "arg_bool", "arg_float"});

    // Test array types
    register_service(&CustomAPIDeviceComponent::on_service_with_arrays, "custom_service_with_arrays",
                     {"bool_array", "int_array", "float_array", "string_array"});
  }

  void on_test_service() { ESP_LOGI("custom_api", "Custom test service called!"); }

  void on_service_with_args(std::string arg_string, int32_t arg_int, bool arg_bool, float arg_float) {
    ESP_LOGI("custom_api", "Custom service called with: %s, %d, %d, %.2f", arg_string.c_str(), arg_int, arg_bool,
             arg_float);
  }

  void on_service_with_arrays(std::vector<bool> bool_array, std::vector<int32_t> int_array,
                              std::vector<float> float_array, std::vector<std::string> string_array) {
    ESP_LOGI("custom_api", "Array service called with %zu bools, %zu ints, %zu floats, %zu strings", bool_array.size(),
             int_array.size(), float_array.size(), string_array.size());

    // Log first element of each array if not empty
    if (!bool_array.empty()) {
      ESP_LOGI("custom_api", "First bool: %d", bool_array[0]);
    }
    if (!int_array.empty()) {
      ESP_LOGI("custom_api", "First int: %d", int_array[0]);
    }
    if (!float_array.empty()) {
      ESP_LOGI("custom_api", "First float: %.2f", float_array[0]);
    }
    if (!string_array.empty()) {
      ESP_LOGI("custom_api", "First string: %s", string_array[0].c_str());
    }
  }
};

}  // namespace custom_api_device_component
}  // namespace esphome
#endif  // USE_API
