#pragma once

#include "esphome/components/output/float_output.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight {

class NeewerStateOutput : public output::FloatOutput {
 protected:
  void write_state(float state) override {
    // do nothing
  }
};

}  // namespace neewerlight
}  // namespace esphome

#endif  // USE_ESP32