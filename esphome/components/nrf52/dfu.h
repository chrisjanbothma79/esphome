#pragma once

#include "esphome/core/defines.h"
#ifdef USE_NRF52_DFU
#include "esphome/components/output/binary_output.h"
#include "esphome/core/component.h"

namespace esphome {
namespace nrf52 {
class DeviceFirmwareUpdate : public Component {
 public:
  void setup() override;
  void loop() override;
  void set_reset_output(output::BinaryOutput *reset_output) { this->reset_output_ = reset_output; }

 protected:
  output::BinaryOutput *reset_output_;
};

}  // namespace nrf52
}  // namespace esphome

#endif
