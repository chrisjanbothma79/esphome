#pragma once

#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "ld2412.h"

namespace esphome {
namespace ld2412 {

template<typename... Ts> class BluetoothPasswordSetAction : public Action<Ts...> {
 public:
  explicit BluetoothPasswordSetAction(LD2412Component *LD2412_comp) : LD2412_comp_(LD2412_comp) {}
  TEMPLATABLE_VALUE(std::string, password)

  void play(Ts... x) override { this->LD2412_comp_->set_bluetooth_password(this->password_.value(x...)); }

 protected:
  LD2412Component *LD2412_comp_;
};

}  // namespace ld2412
}  // namespace esphome
