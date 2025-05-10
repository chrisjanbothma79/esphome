#include "camera_image_impl.h"

namespace esphome {
namespace camera {

CameraImageImpl::CameraImageImpl(size_t max_data_length) { this->data_.reserve(max_data_length); }

void CameraImageImpl::set_requesters(uint8_t requesters) { this->requesters_ = requesters; }

void CameraImageImpl::set_data_length(size_t data_length) { this->data_.resize(data_length); }

size_t CameraImageImpl::get_max_data_length() { return this->data_.capacity(); }

uint8_t *CameraImageImpl::get_data_buffer() { return this->data_.data(); }

size_t CameraImageImpl::get_data_length() { return this->data_.size(); }

bool CameraImageImpl::was_requested_by(camera::CameraRequester requester) const {
  return (this->requesters_ & (1 << requester)) != 0;
}

}  // namespace camera
}  // namespace esphome
