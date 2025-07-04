#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/api/api_server.h"
#include "esphome/components/api/api_connection.h"
#include "esphome/components/api/api_pb2.h"

namespace esphome {
namespace api_buffer_test_component {

static const char *const TAG = "api_buffer_test";

class APIBufferTestComponent : public Component {
 public:
  void setup() override;
  void loop() override;

  float get_setup_priority() const override { return setup_priority::AFTER_CONNECTION; }

  // Subscribe to API connection (like bluetooth_proxy)
  void subscribe_api_connection(api::APIConnection *api_connection);
  void unsubscribe_api_connection(api::APIConnection *api_connection);

  // Test methods
  void fill_buffer();
  void keep_buffer_full();
  void generate_heavy_traffic();
  void generate_traffic_burst();

  // Configuration
  void set_fill_size(size_t size) { this->fill_size_ = size; }
  void set_fill_count(size_t count) { this->fill_count_ = count; }
  void set_auto_fill_delay(uint32_t delay) { this->auto_fill_delay_ = delay; }

 protected:
  api::APIConnection *api_connection_{nullptr};
  size_t fill_size_{2048};
  size_t fill_count_{200};
  uint32_t auto_fill_delay_{2000};
  uint32_t last_fill_time_{0};
  bool buffer_filled_{false};
  bool should_keep_full_{false};
  uint32_t keep_full_until_{0};
  bool tried_subscribe_{false};
};

extern APIBufferTestComponent
    *global_api_buffer_test_component;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

}  // namespace api_buffer_test_component
}  // namespace esphome