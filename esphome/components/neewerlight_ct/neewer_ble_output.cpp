#include "neewer_ble_output.h"
#include "utils.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

using utils::TAG;

void NeewerBLEOutput::dump_config() {
  ESP_LOGCONFIG(TAG, "Neewer BLE Output:");
  ESP_LOGCONFIG(TAG, "  MAC address        : %s", this->parent_->address_str().c_str());
  ESP_LOGCONFIG(TAG, "  Service UUID       : %s", this->service_uuid_.to_string().c_str());
  ESP_LOGCONFIG(TAG, "  Characteristic UUID: %s", this->char_uuid_.to_string().c_str());
  LOG_BINARY_OUTPUT(this);
};

void NeewerBLEOutput::gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                                          esp_ble_gattc_cb_param_t *param) {
  switch (event) {
    case ESP_GATTC_OPEN_EVT:
      this->client_state_ = espbt::ClientState::ESTABLISHED;
      ESP_LOGW(TAG, "[%s] Connected successfully!", this->char_uuid_.to_string().c_str());
      break;
    case ESP_GATTC_DISCONNECT_EVT:
      ESP_LOGW(TAG, "[%s] Disconnected", this->char_uuid_.to_string().c_str());
      this->client_state_ = espbt::ClientState::IDLE;
      break;
    case ESP_GATTC_WRITE_CHAR_EVT: {
      if (param->write.status == 0) {
        break;
      }

      auto *chr = this->parent()->get_characteristic(this->service_uuid_, this->char_uuid_);
      if (chr == nullptr) {
        ESP_LOGW(TAG, "[%s] Characteristic not found.", this->char_uuid_.to_string().c_str());
        break;
      }
      if (param->write.handle == chr->handle) {
        ESP_LOGW(TAG, "[%s] Write error, status=%d", this->char_uuid_.to_string().c_str(), param->write.status);
      }
      break;
    }
    default:
      break;
  }
};

void NeewerBLEOutput::write_state(float state) {
  if (this->client_state_ != espbt::ClientState::ESTABLISHED) {
    ESP_LOGW(TAG, "[%s] Not connected to BLE client.  State update can not be written.",
             this->char_uuid_.to_string().c_str());
    return;
  }

  auto *chr = this->parent()->get_characteristic(this->service_uuid_, this->char_uuid_);
  if (chr == nullptr) {
    ESP_LOGW(TAG, "[%s] Characteristic not found.  State update can not be written.",
             this->char_uuid_.to_string().c_str());
    return;
  }

  // this->msg_ must be prepared prior to running this function

  ESP_LOGD(TAG, "Message length before write to light: %i", this->msg_len_);
  if (!this->msg_ && !this->msg_len_) {
    ESP_LOGI(TAG, "Could not send message to light - 0 length message.");
  } else if (chr != nullptr) {
    ESP_LOGI(TAG, "Attempting to write colour command %i bytes, state value: %f", this->msg_len_, state);
    for (int i = 0; i < this->msg_len_; i++) {
      ESP_LOGV(TAG, "Reading byte %i/%i, value %i (0x%1x)", i, this->msg_len_ - 1, this->msg_[i], this->msg_[i]);
    }
    chr->write_value(this->msg_, this->msg_len_, ESP_GATT_WRITE_TYPE_RSP);
  } else {
    ESP_LOGD(TAG, "Writing colour command failed: could not get characteristic from parent.");
  }
};

// Prepare the msg_ byte array and append checksum
// Algorithm borrowed from https://github.com/keefo/NeewerLite (MIT Licensed)
void NeewerBLEOutput::build_msg_with_checksum() {
  this->msg_clear();

  int checksum = 0;
  for (int i = 0; i < this->orig_msg_len_; i++) {
    this->msg_[i] = this->orig_msg_[i] < 0 ? (uint8_t) (this->orig_msg_[i] + 0x100) : (uint8_t) this->orig_msg_[i];
    checksum = checksum + this->msg_[i];
  }
  this->msg_[this->orig_msg_len_] = (uint8_t) (checksum & 0xFF);
  this->msg_len_ = this->orig_msg_len_ + 1;
  ESP_LOGD(TAG, "Message length at end of build_msg_with_checksum: %i", this->msg_len_);
};

void NeewerBLEOutput::msg_clear() {
  for (int i = 0; i < MSG_MAX_SIZE; i++) {
    this->msg_[i] = 0;
  }
  this->msg_len_ = 0;
};

void NeewerBLEOutput::orig_msg_clear() {
  for (int i = 0; i < MSG_MAX_SIZE; i++) {
    this->orig_msg_[i] = 0;
  }
  this->orig_msg_len_ = 0;
};

NeewerBLEOutput::NeewerBLEOutput() {
  msg_ = (uint8_t *) malloc(MSG_MAX_SIZE);
  this->msg_clear();
  orig_msg_ = (uint8_t *) malloc(MSG_MAX_SIZE);
  this->orig_msg_clear();
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
