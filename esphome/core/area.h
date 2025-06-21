#pragma once

#include <string>
#include <cstdint>

namespace esphome {

class Area {
 public:
  void set_area_id(uint32_t area_id) { area_id_ = area_id; }
  uint32_t get_area_id() { return area_id_; }
  void set_name(std::string name) { name_ = std::move(name); }
  std::string get_name() { return name_; }

 protected:
  uint32_t area_id_{};
  std::string name_ = "";
};

}  // namespace esphome
