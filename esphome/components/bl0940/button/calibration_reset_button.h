#pragma once

#include "esphome/core/component.h"
#include "esphome/components/button/button.h"

namespace esphome {
namespace bl0940 {

class BL0940;  // Forward declaration of BL0940 class

class CalibrationResetButton : public button::Button, public Component {
 public:
  void dump_config() override;
  void set_bl0940(BL0940 *bl0940) { bl0940_ = bl0940; }

  void press_action() override;

 protected:
  BL0940 *bl0940_{nullptr};
};

}  // namespace bl0940
}  // namespace esphome
