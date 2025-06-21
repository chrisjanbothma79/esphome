#pragma once

#include "esphome/core/string_ref.h"

namespace esphome {

class SubDevice {
 public:
  void set_device_id(uint32_t device_id) { device_id_ = device_id; }
  uint32_t get_device_id() { return device_id_; }
  void set_name(std::string name) { name_ = std::move(name); }
  std::string get_name() { return name_; }
  void set_area_id(uint32_t area_id) { area_id_ = area_id; }
  uint32_t get_area_id() { return area_id_; }

 protected:
  uint32_t device_id_{};
  uint32_t area_id_{};
  std::string name_ = "";
};

}  // namespace esphome
