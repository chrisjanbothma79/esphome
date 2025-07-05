#include "deep_sleep_component.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"

namespace esphome {
namespace deep_sleep {

static const char *const TAG = "deep_sleep";
// 5 seconds for deep sleep to ensure clean disconnect from Home Assistant
static const uint32_t TEARDOWN_TIMEOUT_DEEP_SLEEP_MS = 5000;

bool global_has_deep_sleep = false;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

void DeepSleepComponent::setup() {
  ESP_LOGCONFIG(TAG, "Running setup");
  global_has_deep_sleep = true;

  const optional<uint32_t> run_duration = get_run_duration_();
  if (run_duration.has_value()) {
    ESP_LOGI(TAG, "Scheduling in %" PRIu32 " ms", *run_duration);
    this->set_timeout(*run_duration, [this]() { this->begin_sleep(); });
  } else {
    ESP_LOGD(TAG, "Not scheduling; no run duration configured");
  }
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

void DeepSleepComponent::set_sleep_duration(uint32_t time_ms) { this->sleep_duration_ = uint64_t(time_ms) * 1000; }

void DeepSleepComponent::set_run_duration(uint32_t time_ms) { this->run_duration_ = time_ms; }

void DeepSleepComponent::begin_sleep(bool manual) {
  if (this->sleep_state_ == SLEEP_STATE_ENTERING_SLEEP) {
    // Already entering sleep, avoid re-entrance
    return;
  }

  if (this->prevent_ && !manual) {
    // Sleep was prevented
    this->sleep_state_ = SLEEP_STATE_BLOCKED_BY_PREVENT;
    ESP_LOGD(TAG, "Deep sleep blocked by prevent flag");
    return;
  }

  this->sleep_state_ = SLEEP_STATE_ENTERING_SLEEP;

  if (!this->prepare_to_sleep_()) {
    // prepare_to_sleep_ will set appropriate blocked state
    return;
  }

  ESP_LOGI(TAG, "Beginning sleep");
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

float DeepSleepComponent::get_setup_priority() const { return setup_priority::LATE; }

void DeepSleepComponent::prevent_deep_sleep() { this->prevent_ = true; }

void DeepSleepComponent::allow_deep_sleep() {
  this->prevent_ = false;
  // If sleep was blocked by prevent flag, try to sleep now
  if (this->sleep_state_ == SLEEP_STATE_BLOCKED_BY_PREVENT) {
    ESP_LOGD(TAG, "Deep sleep allowed, executing deferred sleep");
    this->sleep_state_ = SLEEP_STATE_IDLE;
    // Schedule sleep for next loop iteration to avoid potential issues
    // with calling begin_sleep during another component's execution
    this->defer([this]() { this->begin_sleep(false); });  // false = automatic sleep (respects prevent flag)
  }
}

}  // namespace deep_sleep
}  // namespace esphome
