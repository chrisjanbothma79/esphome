#include "deep_sleep_component.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace deep_sleep {

static const char *const TAG = "deep_sleep";
static const char *const RUN_TIMEOUT = "run_timeout";

// 5 seconds for deep sleep to ensure clean disconnect from Home Assistant
static const uint32_t TEARDOWN_TIMEOUT_DEEP_SLEEP_MS = 5000;

bool global_has_deep_sleep = false;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

void DeepSleepComponent::setup() {
  global_has_deep_sleep = true;

  const optional<uint32_t> run_duration = this->get_run_duration_();
  if (run_duration.has_value()) {
    ESP_LOGI(TAG, "Scheduling in %" PRIu32 " ms", *run_duration);
    this->set_timeout(RUN_TIMEOUT, *run_duration, [this]() { this->begin_sleep(); });
  } else {
    ESP_LOGD(TAG, "Not scheduling; no run duration configured");
  }
  this->setup_platform_();
}

void DeepSleepComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Deep sleep:");
  if (this->sleep_duration_.has_value()) {
    uint32_t duration = *this->sleep_duration_ / 1000;
    ESP_LOGCONFIG(TAG, "  Sleep Duration: %" PRIu32 " ms", duration);
  }
  if (this->run_duration_.has_value()) {
    ESP_LOGCONFIG(TAG, "  Run Duration: %" PRIu32 " ms", *this->run_duration_);
  }
  this->dump_config_platform_();
}

float DeepSleepComponent::get_setup_priority() const { return setup_priority::LATE; }

float DeepSleepComponent::get_loop_priority() const {
  return -100.0f;  // run after everything else is ready
}

void DeepSleepComponent::set_sleep_duration(uint32_t time_ms) { this->sleep_duration_ = uint64_t(time_ms) * 1000; }

void DeepSleepComponent::set_run_duration(uint32_t time_ms) { this->run_duration_ = time_ms; }

void DeepSleepComponent::begin_sleep(bool manual) {
  this->cancel_timeout(RUN_TIMEOUT);

  if (!manual && (this->waiting_for_sleep_ || this->prevent_ != 0)) {
    this->waiting_for_sleep_ = true;
    ESP_LOGI(TAG, "Waiting to allow for deep sleep");
    return;
  }

  ESP_LOGI(TAG, "Going to sleep now");
  if (this->sleep_duration_.has_value()) {
    ESP_LOGI(TAG, "Sleeping for %" PRId64 "us", *this->sleep_duration_);
  }
  App.run_safe_shutdown_hooks();
  // It's critical to teardown components cleanly for deep sleep to ensure
  // Home Assistant sees a clean disconnect instead of marking the device unavailable
  App.teardown_components(TEARDOWN_TIMEOUT_DEEP_SLEEP_MS);
  App.run_powerdown_hooks();

  this->deep_sleep_();
}

void DeepSleepComponent::prevent_deep_sleep() { this->set_deep_sleep_prevention(true, false); }
void DeepSleepComponent::allow_deep_sleep() { this->set_deep_sleep_prevention(false, false); }

void DeepSleepComponent::set_deep_sleep_prevention(bool prevent, bool external) {
  uint8_t value = external ? this->prevent_ >> 4 : this->prevent_ & 0xf;
  if (prevent && (value < 15)) {
    this->prevent_ += (external ? 16 : 1);
  }
  if (!prevent && (value > 0)) {
    this->prevent_ -= (external ? 16 : 1);
  }

  ESP_LOGV(TAG, "Prevent count is %02x, %d, %s", this->prevent_, value, prevent ? "PRESS" : "released");
  if (this->prevent_ == 0 && this->waiting_for_sleep_) {
    this->begin_sleep(true);
  }
}

}  // namespace deep_sleep
}  // namespace esphome
