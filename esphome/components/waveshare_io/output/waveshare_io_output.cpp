#include "waveshare_io_output.h"

namespace esphome {
namespace waveshare_io {

void WaveshareIOOutput::write_state(float state) { this->parent_->set_pwm_value(static_cast<uint8_t>(state * 255.0f)); }

}  // namespace waveshare_io
}  // namespace esphome
