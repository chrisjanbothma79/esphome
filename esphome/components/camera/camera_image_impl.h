#pragma once

#include "camera.h"

namespace esphome {
namespace camera {

/** Camera image interface implemenation.
 */
class CameraImageImpl : public CameraImage {
 public:
  // Allocates buffer with max_data_length uint8 data to store JPEG data.
  CameraImageImpl(size_t max_data_length);
  // Specifies the filter used in add_image_callback.
  void set_requesters(uint8_t requesters);
  // Sets the length of encoded JPEG data. Can be used to increase the buffer.
  void set_data_length(size_t data_length);
  // Returns the allocated size of the buffer.
  size_t get_max_data_length();

  // ---- CameraImage interface ----
  uint8_t *get_data_buffer() override;
  size_t get_data_length() override;
  bool was_requested_by(CameraRequester requester) const override;
  // -------------------------------
 protected:
  std::vector<uint8_t, RAMAllocator<uint8_t>> data_;
  uint8_t requesters_{0};
};

}  // namespace camera
}  // namespace esphome
