#ifdef USE_P4_CAMERA_JPEG_ENCODER

#include "driver/jpeg_encode.h"

#include "esp32_p4_encoder_buffer.h"

namespace esphome {
namespace camera_encoder {

#ifdef USE_ESP32_VARIANT_ESP32P4
#endif

bool ESP32P4EncoderBuffer::set_buffer_size(size_t size) {
  if (size > this->capacity_) {
    size_t buffer_size = 0;
    jpeg_encode_memory_alloc_cfg_t mem_cfg = {
        .buffer_direction = JPEG_ENC_ALLOC_OUTPUT_BUFFER,
    };

    if (this->data_ != nullptr) {
      heap_caps_free(this->data_);
      this->data_ = nullptr;
      this->capacity_ = 0;
      this->size_ = 0;
    }

    uint8_t *p = (uint8_t *) jpeg_alloc_encoder_mem(size, &mem_cfg, &buffer_size);
    if (p == nullptr)
      return false;

    this->data_ = p;
    this->capacity_ = buffer_size;
  }

  this->size_ = size;
  return true;
}

}  // namespace camera_encoder
}  // namespace esphome

#endif
