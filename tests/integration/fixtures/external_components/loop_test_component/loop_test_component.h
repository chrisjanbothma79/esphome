#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace loop_test_component {

static const char *const TAG = "loop_test_component";

class LoopTestComponent : public Component {
 public:
  void setup() override {
    ESP_LOGI(TAG, "LoopTestComponent setup()");
    this->loop_count_ = 0;
    this->setup_disable_count_ = 0;
    this->setup_enable_count_ = 0;

    // Test 1: Try to disable/enable in setup (before calculate_looping_components_)
    ESP_LOGI(TAG, "Test 1: Disable in setup");
    this->disable_loop();
    this->setup_disable_count_++;

    ESP_LOGI(TAG, "Test 1: Enable in setup");
    this->enable_loop();
    this->setup_enable_count_++;
  }

  void loop() override {
    this->loop_count_++;

    if (this->loop_count_ <= 10 || this->loop_count_ % 10 == 0) {
      ESP_LOGI(TAG, "Loop count: %d", this->loop_count_);
    }

    // Test 2: Disable after 50 loops
    if (this->loop_count_ == 50) {
      ESP_LOGI(TAG, "Test 2: Disabling loop after 50 iterations");
      this->disable_loop();
      this->loop_disable_count_++;
    }

    // This should not happen
    if (this->loop_count_ > 50 && this->loop_count_ < 100) {
      ESP_LOGE(TAG, "ERROR: Loop called after disable! Count: %d", this->loop_count_);
    }

    // Test 3: Re-enable after being disabled (shouldn't get here)
    if (this->loop_count_ == 75) {
      ESP_LOGE(TAG, "ERROR: This code should never execute!");
      this->enable_loop();
    }
  }

  // For testing from outside
  void test_enable_from_outside() {
    ESP_LOGI(TAG, "Test 3: Enabling from outside call");
    this->enable_loop();
    this->external_enable_count_++;
  }

  void test_disable_from_outside() {
    ESP_LOGI(TAG, "Test 4: Disabling from outside call");
    this->disable_loop();
    this->external_disable_count_++;
  }

  // Getters for test validation
  int get_loop_count() const { return this->loop_count_; }
  int get_setup_disable_count() const { return this->setup_disable_count_; }
  int get_setup_enable_count() const { return this->setup_enable_count_; }
  int get_loop_disable_count() const { return this->loop_disable_count_; }
  int get_external_enable_count() const { return this->external_enable_count_; }
  int get_external_disable_count() const { return this->external_disable_count_; }

  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  int loop_count_{0};
  int setup_disable_count_{0};
  int setup_enable_count_{0};
  int loop_disable_count_{0};
  int external_enable_count_{0};
  int external_disable_count_{0};
};

}  // namespace loop_test_component
}  // namespace esphome