#pragma once

#include "esphome/components/output/float_output.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

class NeewerStateOutput : public output::FloatOutput {
 protected:
  void write_state(float state) override {
    // do nothing
  }
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
