#pragma once
#include "esphome/core/defines.h"
#ifdef USE_DFU
#include "esphome/core/component.h"
#ifdef USE_OUTPUT
#include "esphome/components/output/binary_output.h"
#endif

namespace esphome {
namespace nrf52 {
class DeviceFirmwareUpdate : public Component {
 public:
  void setup() override;
  void loop() override;
#ifdef USE_OUTPUT
  void set_reset_output(output::BinaryOutput *reset_output) { this->reset_output_ = reset_output; }
#endif
 protected:
#ifdef USE_OUTPUT
  output::BinaryOutput *reset_output_;
#endif
};
}  // namespace nrf52
}  // namespace esphome
#endif
