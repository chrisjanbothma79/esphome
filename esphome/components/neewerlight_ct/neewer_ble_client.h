#pragma once

#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

#include <cstdint>
#include <vector>

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

class NeewerBleClient {
 public:
  explicit NeewerBleClient();
  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);

  // NOTE: msg is non-const because BLECharacteristic::write_value failed to declare it as const, just std::move it in
  void send_message(esphome::ble_client::BLEClient *client, std::vector<uint8_t> &&msg);

  const char *service_uuid() const { return service_uuid_.to_string().c_str(); }
  const char *characteristic_uuid() const { return characteristic_uuid_.to_string().c_str(); }
  bool require_response() const { return require_response_; }

 protected:
  esp32_ble_tracker::ESPBTUUID service_uuid_;
  esp32_ble_tracker::ESPBTUUID characteristic_uuid_;
  bool require_response_;
  esp32_ble_tracker::ClientState client_state_;

  const std::string SERVICE_UUID = "69400001-B5A3-F393-E0A9-E50E24DCCA99";
  const std::string CHARACTERISTIC_UUID = "69400002-B5A3-F393-E0A9-E50E24DCCA99";
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
