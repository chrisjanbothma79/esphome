#include "camera_impl.h"
#include "camera_image_reader_impl.h"

#include "esphome.h"

static const char *const TAG = "camera_impl";

namespace esphome {
namespace camera {

void CameraImpl::set_camera_image_spec(int width, int height, ImageFormat format) {
  this->camera_image_spec_.width = width;
  this->camera_image_spec_.height = height;
  this->camera_image_spec_.format = format;
}
void CameraImpl::set_idle_update_interval(uint32_t idle_update_interval) {
  this->idle_update_interval_ = idle_update_interval;
}
void CameraImpl::set_max_update_interval(uint32_t max_update_interval) {
  this->max_update_interval_ = max_update_interval;
}
void CameraImpl::set_encoder(Encoder *encoder) { this->encoder_ = encoder; }
void CameraImpl::set_encoder_buffer_size(size_t encoder_buffer_size) {
  this->encoder_buffer_size_ = encoder_buffer_size;
}
void CameraImpl::set_encoder_buffer_grow(size_t encoder_buffer_grow) {
  this->encoder_buffer_grow_ = encoder_buffer_grow;
}

CameraImageReader *CameraImpl::create_image_reader() {
  ESP_LOGV(TAG, "CameraImpl::create_image_reader.");
  return new CameraImageReaderImpl;
}

void CameraImpl::request_image(CameraRequester requester) {
  ESP_LOGV(TAG, "CameraImpl::request_image requester: %d", requester);
  this->image_requesters_ |= (1U << requester);
}

void CameraImpl::start_stream(CameraRequester requester) {
  ESP_LOGV(TAG, "CameraImpl::start_stream requester: %d", requester);
  if (this->stream_requesters_ & (1U << requester))
    return;

  this->stream_start_callback_.call();
  this->stream_requesters_ |= (1U << requester);
}

void CameraImpl::stop_stream(CameraRequester requester) {
  ESP_LOGV(TAG, "CameraImpl::stop_stream requester: %d", requester);
  this->stream_stop_callback_.call();
  this->stream_requesters_ &= ~(1U << requester);
}

void CameraImpl::setup() {
  this->pixels_ = std::make_shared<CameraImageImpl>(this->camera_image_spec_.bytes_per_image());
  this->pixels_->set_data_length(this->camera_image_spec_.bytes_per_image());
  this->jpeg_ = std::make_shared<CameraImageImpl>(this->encoder_buffer_size_);
}

void CameraImpl::loop() {
  if (!this->pixels_ || !this->jpeg_) {
    ESP_LOGE(TAG, "Missing setup() call detected. Are you overriding setup() without calling CameraImpl::setup() ?");
    mark_failed();
    return;
  }

  // Is image still in use ?
  if (this->jpeg_.use_count() > 1)
    return;

  const uint32_t now = millis();
  // Framerate limiter
  if (now - this->last_update_ <= this->max_update_interval_)
    return;

  // Request idle image every idle_update_interval
  if (this->idle_update_interval_ != 0 && now - this->last_idle_request_ > this->idle_update_interval_) {
    this->last_idle_request_ = now;
    this->request_image(camera::IDLE);
  }

  // No new image requested
  if (!image_requesters_ && !stream_requesters_)
    return;

  // Capture a new image
  this->image_capture_callback_.call(this->pixels_, this->camera_image_spec_);

  // Check that we have a valid image for the encoder
  if (this->camera_image_spec_.bytes_per_image() != this->pixels_->get_data_length()) {
    ESP_LOGE(TAG, "Spec bytes %d != %d image bytes!", this->camera_image_spec_.bytes_per_image(),
             this->pixels_->get_data_length());
    return;
  }

  size_t length = 0;
  if (this->encoder_) {
    // Set available data to max for encoder.
    this->jpeg_->set_data_length(this->jpeg_->get_max_data_length());

    // Encodes the pixels and returns the number of bytes written.
    length = this->encoder_->encode_pixels(&camera_image_spec_, this->pixels_.get(), this->jpeg_.get());
    switch (this->encoder_->get_last_error()) {
      case ENCODER_ERROR_SUCCESS:
        break;
      case ENCODER_ERROR_OUT_OF_MEMORY: {
        ESP_LOGE(TAG, "The encoder buffer is too small. The encoding failed. Buffer size: %u",
                 this->jpeg_->get_max_data_length());
        if (this->encoder_buffer_grow_ > 0) {
          size_t new_size = this->jpeg_->get_max_data_length() + this->encoder_buffer_grow_;
          ESP_LOGI(TAG, "Increasing encoder buffer size with %u bytes. Retry...", this->encoder_buffer_grow_);
          this->jpeg_->set_data_length(new_size);
          return;
        }
      } break;
      default:
        ESP_LOGE(TAG, "Encoder failed with error code: %u", this->encoder_->get_last_error());
    }
  }

  if (length > 0) {
    this->jpeg_->set_data_length(length);
    this->jpeg_->set_requesters(this->image_requesters_ | this->stream_requesters_);
    this->new_image_callback_.call(this->jpeg_);
  }

  this->image_requesters_ = 0;
  this->last_update_ = now;
}

void CameraImpl::dump_config() {
  ESP_LOGCONFIG(TAG, "Camera:");
  ESP_LOGCONFIG(TAG, "  Name: %s", this->name_.c_str());
  ESP_LOGCONFIG(TAG, "  Internal: %s", YESNO(this->internal_));
  ESP_LOGCONFIG(TAG, "  Resolution: %dx%d", camera_image_spec_.width, camera_image_spec_.height);
  ESP_LOGCONFIG(TAG, "  Format: %d", camera_image_spec_.format);
  ESP_LOGCONFIG(TAG, "  Encoder enabled: %s", YESNO(this->encoder_));
  ESP_LOGCONFIG(TAG, "  Encoder size: %d", encoder_buffer_size_);
  ESP_LOGCONFIG(TAG, "  Encoder grow: %d", encoder_buffer_grow_);
  ESP_LOGCONFIG(TAG, "  Idle update: %d ms", idle_update_interval_);
  ESP_LOGCONFIG(TAG, "  Max update: %d ms", max_update_interval_);
}

}  // namespace camera
}  // namespace esphome
