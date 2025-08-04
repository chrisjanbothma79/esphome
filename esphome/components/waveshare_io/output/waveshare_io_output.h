#pragma once

#include "../waveshare_io.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace waveshare_io {

class WaveshareIOOutput : public output::FloatOutput, public Parented<WaveshareIOComponent> {
 protected:
  void write_state(float state) override;
};

}  // namespace waveshare_io
}  // namespace esphome
