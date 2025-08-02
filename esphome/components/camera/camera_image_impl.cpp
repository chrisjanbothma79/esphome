#include "camera_image_impl.h"

namespace esphome {
namespace camera {

bool CameraImageImpl::set_data_length(size_t data_length) {
  if (data_length > this->capacity_) {
    uint8_t *p = this->allocator_.reallocate(this->data_, data_length);
    if (p == nullptr)
      return false;

    this->data_ = p;
    this->capacity_ = data_length;
  }
  this->length_ = data_length;
  return true;
}

CameraImageImpl::~CameraImageImpl() {
  if (this->data_ != nullptr)
    this->allocator_.deallocate(this->data_, this->capacity_);
}

}  // namespace camera
}  // namespace esphome
