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

  const char *service_uuid() const { return this->service_uuid_.to_string().c_str(); }
  const char *characteristic_uuid() const { return this->characteristic_uuid_.to_string().c_str(); }
  bool require_response() const { return this->require_response_; }

 protected:
  esp32_ble_tracker::ESPBTUUID service_uuid_;
  esp32_ble_tracker::ESPBTUUID characteristic_uuid_;
  bool require_response_;
  esp32_ble_tracker::ClientState client_state_;

  static const std::string SERVICE_UUID;
  static const std::string CHARACTERISTIC_UUID;
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
