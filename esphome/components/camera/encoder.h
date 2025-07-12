#pragma once

#include "camera.h"

namespace esphome {
namespace camera {

/** Enumeration of various errors during encoding.
 */
enum EncoderError : uint8_t {
  ENCODER_ERROR_SUCCESS = 0,
  ENCODER_ERROR_INVALID_PARAMETER,
  ENCODER_ERROR_ENCODE_ERROR,
  ENCODER_ERROR_MEMORY_ERROR,
  ENCODER_ERROR_OUT_OF_MEMORY,
  ENCODER_ERROR_UNSUPPORTED_FEATURE,
  ENCODER_ERROR_GENERIC
};

/** Abstract base class for image encoder interfaces.
 */
class Encoder {
 public:
  // Encodes the pixels and returns the number of bytes written.
  // Spec contains information about the format of the pixel image.
  virtual size_t encode_pixels(CameraImageSpec *spec, CameraImage *pixels, CameraImage *jpeg) = 0;
  // Return the result of the last encoding.
  virtual EncoderError get_last_error() = 0;
  virtual ~Encoder() {}
};

}  // namespace camera
}  // namespace esphome
