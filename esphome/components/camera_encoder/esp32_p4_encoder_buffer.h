#pragma once

#ifdef USE_P4_CAMERA_JPEG_ENCODER

#include "encoder_buffer_impl.h"

namespace esphome {
namespace camera_encoder {

class ESP32P4EncoderBuffer : public EncoderBufferImpl {
 public:
  // --- EncoderBuffer interface ---
  bool set_buffer_size(size_t size) override;
  // -------------------------------
};

}  // namespace camera_encoder
}  // namespace esphome

#endif
