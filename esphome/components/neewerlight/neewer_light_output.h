#pragma once

#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/output/float_output.h"
#include "esphome/core/helpers.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight {

namespace espbt = esp32_ble_tracker;

static const char *const SERVICE_UUID = "69400001-B5A3-F393-E0A9-E50E24DCCA99";
static const char *const CHARACTERISTIC_UUID = "69400002-B5A3-F393-E0A9-E50E24DCCA99";
static const int MSG_MAX_SIZE = 10;              // size of msg_ string to reserve in bytes (uint8_t*).
static const float COLD_WHITE = 1e6f / 6500.0f;  // 6500K ≈ 153.85 mireds
static const float WARM_WHITE = 1e6f / 2700.0f;  // 2700K ≈ 370.37 mireds

class NeewerBLEOutput : public Component, public output::FloatOutput, public ble_client::BLEClientNode {
 public:
  void dump_config() override;
  void loop() override {}
  float get_setup_priority() const override { return setup_priority::DATA; }
  void set_service_uuid16(uint16_t uuid) { this->service_uuid_ = espbt::ESPBTUUID::from_uint16(uuid); }
  void set_service_uuid32(uint32_t uuid) { this->service_uuid_ = espbt::ESPBTUUID::from_uint32(uuid); }
  void set_service_uuid128(uint8_t *uuid) { this->service_uuid_ = espbt::ESPBTUUID::from_raw(uuid); }
  void set_service_uuid_str(const char *uuid) { this->service_uuid_ = espbt::ESPBTUUID::from_raw(uuid); }
  void set_char_uuid16(uint16_t uuid) { this->char_uuid_ = espbt::ESPBTUUID::from_uint16(uuid); }
  void set_char_uuid32(uint32_t uuid) { this->char_uuid_ = espbt::ESPBTUUID::from_uint32(uuid); }
  void set_char_uuid128(uint8_t *uuid) { this->char_uuid_ = espbt::ESPBTUUID::from_raw(uuid); }
  void set_char_uuid_str(const char *uuid) { this->char_uuid_ = espbt::ESPBTUUID::from_raw(uuid); }
  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                           esp_ble_gattc_cb_param_t *param) override;
  void set_require_response(bool response) { this->require_response_ = response; }

  NeewerBLEOutput();

 protected:
  void write_state(float state) override;
  void build_msg_with_checksum();
  void msg_clear();
  void orig_msg_clear();
  bool require_response_;
  espbt::ESPBTUUID service_uuid_;
  espbt::ESPBTUUID char_uuid_;
  espbt::ClientState client_state_;

  const char *const TAG = "neewer_ble_output";

  uint8_t *msg_;
  uint8_t msg_len_;
  uint8_t *orig_msg_;
  uint8_t orig_msg_len_;
  bool command_block_ = false;

  const uint8_t command_prefix_ = 0x78;
  const uint8_t ct_brightness_prefix_ = 0x87;
  const uint8_t effect_prefix_ = 0x88;
};

}  // namespace neewerlight
}  // namespace esphome

#endif  // USE_ESP32