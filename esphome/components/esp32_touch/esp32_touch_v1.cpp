#ifdef USE_ESP32_VARIANT_ESP32

#include "esp32_touch.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

#include <algorithm>
#include <cinttypes>

// Include HAL for ISR-safe touch reading
#include "hal/touch_sensor_ll.h"
// Include for RTC clock frequency
#include "soc/rtc.h"
// Include FreeRTOS ring buffer
#include "freertos/ringbuf.h"

namespace esphome {
namespace esp32_touch {

static const char *const TAG = "esp32_touch";

// Structure for a single pad's state in the ring buffer
struct TouchPadState {
  uint8_t pad;      // touch_pad_t
  uint32_t value;   // Current reading
  bool is_touched;  // Touch state
};

void ESP32TouchComponent::setup() {
  ESP_LOGCONFIG(TAG, "Running setup for ESP32");

  touch_pad_init();
  touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);

  // Create ring buffer for touch events
  // Size calculation: We need space for multiple snapshots
  // Each snapshot contains: array of TouchPadState structures
  size_t pad_state_size = sizeof(TouchPadState);
  size_t snapshot_size = this->children_.size() * pad_state_size;

  // Allow for 4 snapshots in the buffer to handle normal operation and bursts
  size_t buffer_size = snapshot_size * 4;

  // Create a byte buffer ring buffer (allows variable sized items)
  this->ring_buffer_handle_ = xRingbufferCreate(buffer_size, RINGBUF_TYPE_BYTEBUF);
  if (this->ring_buffer_handle_ == nullptr) {
    ESP_LOGE(TAG, "Failed to create ring buffer of size %d", buffer_size);
    this->mark_failed();
    return;
  }

  // Set up IIR filter if enabled
  if (this->iir_filter_enabled_()) {
    touch_pad_filter_start(this->iir_filter_);
  }

  // Configure measurement parameters
#if ESP_IDF_VERSION_MAJOR >= 5
  touch_pad_set_measurement_clock_cycles(this->meas_cycle_);
  touch_pad_set_measurement_interval(this->sleep_cycle_);
#else
  touch_pad_set_meas_time(this->sleep_cycle_, this->meas_cycle_);
#endif
  touch_pad_set_voltage(this->high_voltage_reference_, this->low_voltage_reference_, this->voltage_attenuation_);

  // Configure each touch pad
  for (auto *child : this->children_) {
    touch_pad_config(child->get_touch_pad(), child->get_threshold());
  }

  // Register ISR handler
  esp_err_t err = touch_pad_isr_register(touch_isr_handler, this);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Failed to register touch ISR: %s", esp_err_to_name(err));
    vRingbufferDelete(this->ring_buffer_handle_);
    this->ring_buffer_handle_ = nullptr;
    this->mark_failed();
    return;
  }

  // Calculate release timeout based on sleep cycle
  // Design note: ESP32 v1 hardware limitation - interrupts only fire on touch (not release)
  // We must use timeout-based detection for release events
  // Formula: 3 sleep cycles converted to ms, with MINIMUM_RELEASE_TIME_MS minimum
  uint32_t rtc_freq = rtc_clk_slow_freq_get_hz();
  this->release_timeout_ms_ = (this->sleep_cycle_ * 1000 * 3) / (rtc_freq * 2);
  if (this->release_timeout_ms_ < MINIMUM_RELEASE_TIME_MS) {
    this->release_timeout_ms_ = MINIMUM_RELEASE_TIME_MS;
  }
  this->release_check_interval_ms_ = std::min(this->release_timeout_ms_ / 4, (uint32_t) 50);

  // Enable touch pad interrupt
  touch_pad_intr_enable();
}

void ESP32TouchComponent::dump_config() {
  this->dump_config_base_();

  if (this->iir_filter_enabled_()) {
    ESP_LOGCONFIG(TAG, "    IIR Filter: %" PRIu32 "ms", this->iir_filter_);
  } else {
    ESP_LOGCONFIG(TAG, "  IIR Filter DISABLED");
  }

  if (this->setup_mode_) {
    ESP_LOGCONFIG(TAG, "  Setup Mode ENABLED");
  }

  this->dump_config_sensors_();
}

void ESP32TouchComponent::loop() {
  const uint32_t now = App.get_loop_component_start_time();

  // Print debug info for all pads in setup mode
  if (this->setup_mode_ && now - this->setup_mode_last_log_print_ > SETUP_MODE_LOG_INTERVAL_MS) {
    for (auto *child : this->children_) {
      ESP_LOGD(TAG, "Touch Pad '%s' (T%" PRIu32 "): %" PRIu32, child->get_name().c_str(),
               (uint32_t) child->get_touch_pad(), child->value_);
    }
    this->setup_mode_last_log_print_ = now;
  }

  // Process ring buffer entries
  size_t item_size;
  TouchPadState *pad_states;

  // Receive all available items from ring buffer (non-blocking)
  while ((pad_states = (TouchPadState *) xRingbufferReceive(this->ring_buffer_handle_, &item_size, 0)) != nullptr) {
    // Calculate number of pads in this snapshot
    size_t num_pads = item_size / sizeof(TouchPadState);

    // Process each pad in the snapshot
    for (size_t i = 0; i < num_pads; i++) {
      const TouchPadState &pad_state = pad_states[i];

      // Find the corresponding sensor
      for (auto *child : this->children_) {
        if (child->get_touch_pad() == static_cast<touch_pad_t>(pad_state.pad)) {
          child->value_ = pad_state.value;

          // Track when we last saw this pad as touched
          if (pad_state.is_touched) {
            this->last_touch_time_[pad_state.pad] = now;
          }

          // Only publish if state changed
          if (pad_state.is_touched != child->last_state_) {
            child->last_state_ = pad_state.is_touched;
            child->publish_state(pad_state.is_touched);
            ESP_LOGV(TAG, "Touch Pad '%s' state: %s (value: %" PRIu32 ", threshold: %" PRIu32 ")",
                     child->get_name().c_str(), pad_state.is_touched ? "ON" : "OFF", pad_state.value,
                     child->get_threshold());
          }
          break;
        }
      }
    }

    // Return item to ring buffer
    vRingbufferReturnItem(this->ring_buffer_handle_, (void *) pad_states);
  }

  // Check for released pads periodically
  static uint32_t last_release_check = 0;
  if (now - last_release_check < this->release_check_interval_ms_) {
    return;
  }
  last_release_check = now;

  for (auto *child : this->children_) {
    touch_pad_t pad = child->get_touch_pad();
    uint32_t last_time = this->last_touch_time_[pad];

    // Design note: Sentinel value pattern explanation
    // - 0: Never touched since boot (waiting for initial timeout)
    // - 1: Initial OFF state has been published (prevents repeated publishes)
    // - >1: Actual timestamp of last touch event
    // This avoids needing a separate boolean flag for initial state tracking

    // If we've never seen this pad touched (last_time == 0) and enough time has passed
    // since startup, publish OFF state and mark as published with value 1
    if (last_time == 0 && now > this->release_timeout_ms_) {
      child->publish_state(false);
      this->last_touch_time_[pad] = 1;  // Mark as "initial state published"
      ESP_LOGV(TAG, "Touch Pad '%s' state: OFF (initial)", child->get_name().c_str());
    } else if (child->last_state_ && last_time > 1) {  // last_time > 1 means it's a real timestamp
      uint32_t time_diff = now - last_time;

      // Check if we haven't seen this pad recently
      if (time_diff > this->release_timeout_ms_) {
        // Haven't seen this pad recently, assume it's released
        child->last_state_ = false;
        child->publish_state(false);
        this->last_touch_time_[pad] = 1;  // Reset to "initial published" state
        ESP_LOGV(TAG, "Touch Pad '%s' state: OFF (timeout)", child->get_name().c_str());
      }
    }
  }
}

void ESP32TouchComponent::on_shutdown() {
  touch_pad_intr_disable();
  touch_pad_isr_deregister(touch_isr_handler, this);

  if (this->ring_buffer_handle_) {
    vRingbufferDelete(this->ring_buffer_handle_);
    this->ring_buffer_handle_ = nullptr;
  }

  bool is_wakeup_source = false;

  if (this->iir_filter_enabled_()) {
    touch_pad_filter_stop();
    touch_pad_filter_delete();
  }

  for (auto *child : this->children_) {
    if (child->get_wakeup_threshold() != 0) {
      if (!is_wakeup_source) {
        is_wakeup_source = true;
        // Touch sensor FSM mode must be 'TOUCH_FSM_MODE_TIMER' to use it to wake-up.
        touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
      }

      // No filter available when using as wake-up source.
      touch_pad_config(child->get_touch_pad(), child->get_wakeup_threshold());
    }
  }

  if (!is_wakeup_source) {
    touch_pad_deinit();
  }
}

void IRAM_ATTR ESP32TouchComponent::touch_isr_handler(void *arg) {
  ESP32TouchComponent *component = static_cast<ESP32TouchComponent *>(arg);

  touch_pad_clear_status();

  // Calculate size needed for this snapshot
  size_t num_pads = component->children_.size();
  size_t snapshot_size = num_pads * sizeof(TouchPadState);

  // Allocate space in ring buffer (ISR-safe version)
  void *buffer = xRingbufferSendAcquireFromISR(component->ring_buffer_handle_, snapshot_size);
  if (buffer == nullptr) {
    // Buffer full - track overflow
    component->ring_buffer_overflow_count_++;
    return;
  }

  // Fill the buffer with pad states
  TouchPadState *pad_states = (TouchPadState *) buffer;

  // Process all configured pads
  size_t pad_index = 0;
  for (auto *child : component->children_) {
    touch_pad_t pad = child->get_touch_pad();

    // Read current value using ISR-safe API
    uint32_t value;
    if (component->iir_filter_enabled_()) {
      uint16_t temp_value = 0;
      touch_pad_read_filtered(pad, &temp_value);
      value = temp_value;
    } else {
      // Use low-level HAL function when filter is not enabled
      value = touch_ll_read_raw_data(pad);
    }

    // Skip pads with 0 value - they haven't been measured in this cycle
    if (value == 0) {
      continue;
    }

    // Store pad state
    pad_states[pad_index].pad = static_cast<uint8_t>(pad);
    pad_states[pad_index].value = value;
    // For original ESP32, lower value means touched
    pad_states[pad_index].is_touched = value < child->get_threshold();

    pad_index++;
  }

  // Adjust size if we skipped any pads
  size_t actual_size = pad_index * sizeof(TouchPadState);

  // Send the item
  BaseType_t higher_priority_task_woken = pdFALSE;
  xRingbufferSendCompleteFromISR(component->ring_buffer_handle_, buffer, actual_size, &higher_priority_task_woken);

  if (higher_priority_task_woken) {
    portYIELD_FROM_ISR();
  }
}

}  // namespace esp32_touch
}  // namespace esphome

#endif  // USE_ESP32_VARIANT_ESP32
