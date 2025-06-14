#pragma once

#include "esphome/components/select/select.h"
#include "../ld2412.h"

namespace esphome {
namespace ld2412 {

class ModeSelect : public select::Select, public Parented<LD2412Component> {
 public:
  ModeSelect() = default;

 protected:
  void control(const std::string &value) override;
};

}  // namespace ld2412
}  // namespace esphome
