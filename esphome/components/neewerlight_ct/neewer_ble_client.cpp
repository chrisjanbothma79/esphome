#include "neewer_ble_client.h"
#include "utils.h"

#include "esphome/core/log.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

using utils::TAG;

void NeewerBleClient::gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                                          esp_ble_gattc_cb_param_t *param) {
  switch (event) {
    case ESP_GATTC_OPEN_EVT:
      client_state_ = esp32_ble_tracker::ClientState::ESTABLISHED;
      ESP_LOGW(TAG, "[%s] Connected successfully!", characteristic_uuid_.to_string().c_str());
      break;
    case ESP_GATTC_DISCONNECT_EVT:
      ESP_LOGW(TAG, "[%s] Disconnected", characteristic_uuid_.to_string().c_str());
      client_state_ = esp32_ble_tracker::ClientState::IDLE;
      break;
    default:
      break;
  }
}

void NeewerBleClient::send_message(esphome::ble_client::BLEClient *client, std::vector<uint8_t> &&msg) {
  if (client_state_ != esp32_ble_tracker::ClientState::ESTABLISHED) {
    ESP_LOGW(TAG, "[%s] Not connected to BLE client. State update can not be written.",
             characteristic_uuid_.to_string().c_str());
    return;
  }

  auto characteristic = client->get_characteristic(service_uuid_, characteristic_uuid_);
  if (characteristic == nullptr) {
    ESP_LOGW(TAG, "[%s] Characteristic not found. State update can not be written.",
             characteristic_uuid_.to_string().c_str());
    return;
  }

  if (msg.empty()) {
    ESP_LOGW(TAG, "Empty message. No data will be written.");
    return;
  }

  ESP_LOGD(TAG, "[%s] Writing %i bytes", characteristic_uuid_.to_string().c_str(), msg.size());
  for (int i = 0; i < msg.size(); i++) {
    ESP_LOGV(TAG, "Reading byte %i/%i, value %i (0x%1x)", i, msg.size() - 1, msg[i], msg[i]);
  }
  esp_err_t status = characteristic->write_value(msg.data(), msg.size(), ESP_GATT_WRITE_TYPE_RSP);
  if (status != ESP_OK) {
    ESP_LOGW(TAG, "[%s] Write error, esp_err_t status = %d", characteristic_uuid_.to_string().c_str(), status);
  } else {
    ESP_LOGD(TAG, "[%s] Write successful", characteristic_uuid_.to_string().c_str());
  }
}

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
