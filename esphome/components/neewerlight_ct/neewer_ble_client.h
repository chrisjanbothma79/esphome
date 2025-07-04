#pragma once

#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

#include <cstdint>
#include <vector>

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

// TODO split to cpp file
class NeewerBleClient {
 public:
  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);
  // NOTE: msg is non-const because BLECharacteristic::write_value failed to declare it as const, just std::move it in
  void send_message(esphome::ble_client::BLEClient *client, std::vector<uint8_t> &&msg);
  void set_characteristic_uuid_str(const char *uuid) {
    characteristic_uuid_ = esp32_ble_tracker::ESPBTUUID::from_raw(uuid);
  }
  void set_require_response(bool response) { require_response_ = response; }
  void set_service_uuid_str(const char *uuid) { service_uuid_ = esp32_ble_tracker::ESPBTUUID::from_raw(uuid); }

  bool require_response_;
  esp32_ble_tracker::ESPBTUUID service_uuid_;
  esp32_ble_tracker::ESPBTUUID characteristic_uuid_;
  esp32_ble_tracker::ClientState client_state_;
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
