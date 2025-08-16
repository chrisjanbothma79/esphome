#pragma once

#include "camera.h"
#include "encoder.h"

namespace esphome {
namespace camera {

/** Camera image interface implemenation.
 */
class CameraImageAdapter : public CameraImage {
 public:
  explicit CameraImageAdapter(EncoderBuffer *buffer) : buffer_(buffer) {}
  void set_requesters(uint8_t requesters) { this->requesters_ = requesters; }
  // ---- CameraImage interface ----
  uint8_t *get_data_buffer() override { return this->buffer_->get_data(); }
  size_t get_data_length() override { return this->buffer_->get_size(); }
  bool was_requested_by(CameraRequester requester) const override {
    return (this->requesters_ & (1 << requester)) != 0;
  }
  // -------------------------------

 protected:
  EncoderBuffer *buffer_{};
  uint8_t requesters_{};
};

/** Camera image interface implemenation.
 */
class CameraImageImpl : public CameraImage {
 public:
  // Specifies the filter used in add_image_callback.
  void set_requesters(uint8_t requesters) { this->requesters_ = requesters; }
  // Sets the length of the image or jpeg buffer data. Can be used to increase the buffer.
  // returns false if allocation failed.
  virtual bool set_data_length(size_t data_length);
  // Returns the allocated size of the buffer.
  size_t get_max_data_length() { return this->capacity_; }

  // ---- CameraImage interface ----
  uint8_t *get_data_buffer() override { return this->data_; }
  size_t get_data_length() override { return this->length_; }
  bool was_requested_by(CameraRequester requester) const override {
    return (this->requesters_ & (1 << requester)) != 0;
  }
  // -------------------------------
  ~CameraImageImpl() override;

 protected:
  RAMAllocator<uint8_t> allocator_;
  uint8_t *data_{};
  size_t capacity_{};
  size_t length_{};
  uint8_t requesters_{};
};

}  // namespace camera
}  // namespace esphome
