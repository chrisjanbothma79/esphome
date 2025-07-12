#pragma once

#ifdef USE_CAMERA_SW_JPEG_ENCODER

#include "esphome/components/camera/encoder.h"
#include <JPEGENC.h>

namespace esphome {
namespace camera_encoder {

/** Enumeration of different qualities of the encoded image.
 *  Better quality results in more memory consumption and higher CPU usage.
 */
enum DefaultQuality : uint8_t { QUALITY_BEST = 0, QUALITY_HIGH, QUALITY_MED, QUALITY_LOW };

/** Enumeration of different modes to reduce the color information in the image.
 * SUBSAMPLING_444 is without reduction.
 * SUBSAMPLING_420 is with reduced color information and lower memory consumption at the cost of reduced image
 * quality.
 */
enum DefaultSubsampling : uint8_t { SUBSAMPLING_444 = 0, SUBSAMPLING_420 };

class DefaultJPEGEncoder : public camera::Encoder {
 public:
  /**
   * @param quality Set the quality of the encoded image.
   * @param subsampling Specify whether the color information should be reduced to reduce memory consumption at the
   * expense of quality.
   * @param mcu_count MCU_count number of MCUs to encode in every encoding call. Encoding will continue sequentially
   * from the current MCU position. A zero value disables incremental encoding and causes the full image to be encoded
   * in a single call.
   */
  DefaultJPEGEncoder(DefaultQuality quality, DefaultSubsampling subsampling, size_t mcu_count);
  // -------- Encoder --------
  size_t encode_pixels(camera::CameraImageSpec *spec, camera::CameraImage *pixels, camera::CameraImage *jpeg) override;
  camera::EncoderError get_last_error() override;
  // -------------------------
 protected:
  int to_internal_(DefaultQuality quality);
  int to_internal_(camera::ImageFormat format);
  int to_internal_(DefaultSubsampling subsampling);

  int quality_{};
  int subsampling_{};
  JPEGENC encoder_{};
  JPEGENCODE encoder_state_{};
  bool incremental_{};
  ssize_t mcu_count_{};
};

}  // namespace camera_encoder
}  // namespace esphome

#endif
