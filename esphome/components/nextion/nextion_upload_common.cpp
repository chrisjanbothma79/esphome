#include "nextion.h"

#ifdef USE_NEXTION_TFT_UPLOAD

#include "esphome/core/application.h"

namespace esphome {
namespace nextion {
static const char *const TAG = "nextion.upload.common";

bool Nextion::upload_end_(bool successful) {
  ESP_LOGD(TAG, "TFT upload done: %s", YESNO(successful));

  if (successful) {
    ESP_LOGD(TAG, "Restart");
    delay(1500);  // NOLINT
    App.safe_reboot();
    delay(1500);  // NOLINT
  } else {
    ESP_LOGE(TAG, "TFT upload failed");

    this->is_updating_ = false;
    this->ignore_is_setup_ = false;

    uint32_t baud_rate = this->parent_->get_baud_rate();
    if (baud_rate != this->original_baud_rate_) {
      ESP_LOGD(TAG, "Baud back: %" PRIu32 "->%" PRIu32, baud_rate, this->original_baud_rate_);
      this->parent_->set_baud_rate(this->original_baud_rate_);
      this->parent_->load_settings();
    }
  }

  return successful;
}

}  // namespace nextion
}  // namespace esphome

#endif  // USE_NEXTION_TFT_UPLOAD
