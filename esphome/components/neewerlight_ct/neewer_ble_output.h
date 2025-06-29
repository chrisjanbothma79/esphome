#pragma once

#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/output/float_output.h"
#include "esphome/core/helpers.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

static const char *const SERVICE_UUID = "69400001-B5A3-F393-E0A9-E50E24DCCA99";
static const char *const CHARACTERISTIC_UUID = "69400002-B5A3-F393-E0A9-E50E24DCCA99";

namespace espbt = esp32_ble_tracker;

class NeewerBLEOutput : public Component, public output::FloatOutput, public ble_client::BLEClientNode {
 public:
  explicit NeewerBLEOutput();

  void dump_config() override;
  void loop() override {}
  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                           esp_ble_gattc_cb_param_t *param) override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_char_uuid_str(const char *uuid) { this->char_uuid_ = espbt::ESPBTUUID::from_raw(uuid); }
  void set_require_response(bool response) { this->require_response_ = response; }
  void set_service_uuid_str(const char *uuid) { this->service_uuid_ = espbt::ESPBTUUID::from_raw(uuid); }

 protected:
  void write_state(float state) override;

  void build_msg_with_checksum();
  void msg_clear();
  void orig_msg_clear();

  bool require_response_;
  espbt::ESPBTUUID service_uuid_;
  espbt::ESPBTUUID char_uuid_;
  espbt::ClientState client_state_;

  uint8_t *msg_;
  uint8_t msg_len_;
  uint8_t *orig_msg_;
  uint8_t orig_msg_len_;
  bool command_block_ = false;

  static const int MSG_MAX_SIZE = 10;  // size of msg_ string to reserve in bytes (uint8_t*).
  static const uint8_t COMMAND_PREFIX = 0x78;
  static const uint8_t CT_BRIGHTNESS_PREFIX = 0x87;
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32