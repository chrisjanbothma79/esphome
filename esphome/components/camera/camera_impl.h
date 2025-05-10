#pragma once

#include "camera.h"
#include "camera_image_impl.h"
#include "encoder.h"

namespace esphome {
namespace camera {

/** Camera interface implemenation.
 */
class CameraImpl : public Camera {
 public:
  // Sets the camera's image specifications
  void set_camera_image_spec(int width, int height, ImageFormat format);
  // Sets the update interval in milliseconds for images without requests
  void set_idle_update_interval(uint32_t idle_update_interval);
  // Sets the number of milliseconds between two consecutive images
  void set_max_update_interval(uint32_t max_update_interval);
  // Sets encoder implementation
  void set_encoder(Encoder *encoder);
  // Sets the initial number of bytes in the encoder buffer
  void set_encoder_buffer_size(size_t encoder_buffer_size);
  // Specifies how many bytes the buffer should grow after an underflow error
  void set_encoder_buffer_grow(size_t encoder_buffer_grow);
  // ---- Camera interface ----
  CameraImageReader *create_image_reader() override;
  void request_image(CameraRequester requester) override;
  void start_stream(CameraRequester requester) override;
  void stop_stream(CameraRequester requester) override;
  // -------- Component -------
  void setup() override;
  void loop() override;
  void dump_config() override;
  // --------------------------
 protected:
  CameraImageSpec camera_image_spec_{0};
  std::shared_ptr<CameraImageImpl> pixels_;
  std::shared_ptr<CameraImageImpl> jpeg_;
  Encoder *encoder_{nullptr};
  size_t encoder_buffer_size_{0};
  size_t encoder_buffer_grow_{0};
  uint8_t image_requesters_{0};
  uint8_t stream_requesters_{0};
  uint32_t last_idle_request_{0};
  uint32_t idle_update_interval_{0};
  uint32_t last_update_{0};
  uint32_t max_update_interval_{0};
};

}  // namespace camera
}  // namespace esphome
