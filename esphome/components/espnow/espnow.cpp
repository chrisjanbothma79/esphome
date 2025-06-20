#include "esphome/core/application.h"
#include "esphome/core/version.h"
#include "esphome/core/log.h"

#if defined(USE_ESP32)
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 1)

#include "espnow.h"

#include <cstring>

#include "esp_mac.h"
#include "esp_random.h"

#include "esp_wifi.h"
#include "esp_now.h"
#include "esp_event.h"

#ifdef USE_WIFI
#include "esphome/components/wifi/wifi_component.h"
#endif

#include <memory>

namespace esphome {
namespace espnow {

static const char *const TAG = "espnow";
const char *const ESPNowTAG::TAG = "espnow";

static const esp_err_t ESP_ERR_ESPNOW_CMP_BASE = (ESP_ERR_ESPNOW_BASE + 20);
static const esp_err_t ESP_ERR_ESPNOW_FAILED = (ESP_ERR_ESPNOW_CMP_BASE + 1);
static const esp_err_t ESP_ERR_ESPNOW_OWN_PEER_ADDRESS = (ESP_ERR_ESPNOW_CMP_BASE + 2);
static const esp_err_t ESP_ERR_ESPNOW_PAYLOAD_SIZE = (ESP_ERR_ESPNOW_CMP_BASE + 3);
static const esp_err_t ESP_ERR_ESPNOW_PEER_NOT_SET = (ESP_ERR_ESPNOW_CMP_BASE + 4);

static const esp_err_t ESP_MSG_ESPNOW_BROADCAST = (ESP_ERR_ESPNOW_BASE + 10);

ESPNowComponent *ESPNowComponent::static_{nullptr};  // NOLINT

std::string peer_string(const uint64_t peer) {
  char mac[24];
  if (peer == 0) {
    snprintf(mac, sizeof(mac), "%s", "[Not Set]");
  } else if (peer == ESPNOW_BROADCAST_ADDR) {
    snprintf(mac, sizeof(mac), "%s", "[Broadcast]");
  } else if (peer == ESPNOW_MULTICAST_ADDR) {
    snprintf(mac, sizeof(mac), "%s", "[Multicast]");
  } else {
    uint8_t *ppeer = (uint8_t *) &peer;
    snprintf(mac, sizeof(mac), "%02X:%02X:%02X:%02X:%02X:%02X", ppeer[0], ppeer[1], ppeer[2], ppeer[3], ppeer[4],
             ppeer[5]);
  }
  return mac;
}

void show_espnow_error(esp_err_t error) {
  if (error == ESP_ERR_ESPNOW_FAILED) {
    ESP_LOGE(TAG, "Cannot send espnow packet, espnow is in fail mode.");
  } else if (error == ESP_ERR_ESPNOW_OWN_PEER_ADDRESS) {
    ESP_LOGE(TAG, "Trying to send a message to your self.");
  } else if (error == ESP_ERR_ESPNOW_PAYLOAD_SIZE) {
    ESP_LOGE(TAG, "Trying to send a payload size to large.");
  } else if (error == ESP_ERR_ESPNOW_PEER_NOT_SET) {
    ESP_LOGE(TAG, "Peer address not set.");
  } else if (error == ESP_ERR_ESPNOW_NOT_INIT) {
    ESP_LOGE(TAG, "ESPNOW not init.");
  } else if (error == ESP_ERR_ESPNOW_ARG) {
    ESP_LOGE(TAG, "Invalid argument");
  } else if (error == ESP_ERR_ESPNOW_INTERNAL) {
    ESP_LOGE(TAG, "Internal Error");
  } else if (error == ESP_ERR_ESPNOW_NO_MEM) {
    ESP_LOGE(TAG, "Our of memory");
  } else if (error == ESP_ERR_ESPNOW_NOT_FOUND) {
    ESP_LOGE(TAG, "Peer not found.");
  } else if (error == ESP_ERR_ESPNOW_IF) {
    ESP_LOGE(TAG, "Interface does not match.");
  }
}

/* ESPNowComponent ********************************************************************** */

ESPNowComponent::ESPNowComponent() { ESPNowComponent::static_ = this; }  // NOLINT

void ESPNowComponent::dump_config() {
  uint32_t version = 0;
  esp_now_get_version(&version);

  ESP_LOGCONFIG(TAG, "esp_now:  V%d", version);
#ifdef USE_WIFI
  ESP_LOGE(TAG, "  WIFI enabled        : Yes. (Make sure provided device know how to channel swap)");
#endif
  ESP_LOGCONFIG(TAG, "  Wifi channel        : %d.", this->wifi_channel_);

  ESP_LOGCONFIG(TAG, "  Own Mac address    : %s.", peer_string(this->own_peer_address_).c_str());
  ESP_LOGCONFIG(TAG, "  Default Mac Address: %s.", peer_string(this->default_peer_address_).c_str());

  ESP_LOGCONFIG(TAG, "  Response timeout: %" PRId32 "ms.", this->response_timeout_);
}

bool ESPNowComponent::is_wifi_enabled_() {
#ifdef USE_WIFI
  if (wifi::global_wifi_component != nullptr) {
    if (!wifi::global_wifi_component->is_disabled())
      return wifi::global_wifi_component->is_connected();
  }
  return false;
#else
  return false;
#endif
}

bool ESPNowComponent::can_proceed() {
#ifdef USE_WIFI
  if (wifi::global_wifi_component != nullptr) {
    if (wifi::global_wifi_component->is_disabled())
      return true;
    return wifi::global_wifi_component->is_connected();
  }
  return false;
#else
  return true;
#endif
}

void ESPNowComponent::setup() {
  if (this->enabled_) {
    this->enable_();
  }
}

void ESPNowComponent::set_enable_state(bool value) {
  if (!this->is_ready()) {
    this->enabled_ = value;
  } else if (value) {
    this->enable();
  } else {
    this->disable();
  }
}

void ESPNowComponent::enable() {
  if (this->enabled_ && this->is_ready()) {
    ESP_LOGE(TAG, "Allready enabled.");
    return;
  }

  this->enable_();
}

void ESPNowComponent::enable_() {
  if (!this->is_wifi_enabled_()) {
    esp_event_loop_create_default();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_disconnect());

    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(this->wifi_channel_, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);
#ifdef USE_WIFI
  } else {
    this->wifi_channel_ = wifi::global_wifi_component->get_wifi_channel();
#endif
  }

  esp_err_t err = esp_now_init();
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "esp_now_init failed: %s", esp_err_to_name(err));
    this->mark_failed();
    return;
  }

  err = esp_now_register_recv_cb(ESPNowComponent::on_data_received);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "esp_now_register_recv_cb failed: %s", esp_err_to_name(err));
    this->mark_failed();
    return;
  }

  err = esp_now_register_send_cb(ESPNowComponent::on_send_report);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "esp_now_register_recv_cb failed: %s", esp_err_to_name(err));
    this->mark_failed();
    return;
  }

  esp_wifi_get_mac(WIFI_IF_STA, (uint8_t *) &this->own_peer_address_);

  for (auto peer : this->peers_) {
    this->add_peer(peer);
  }
  this->enabled_ = true;
}

void ESPNowComponent::disable() {
  if (!this->enabled_) {
    return;
  }
  esp_now_unregister_recv_cb();
  esp_now_unregister_send_cb();

  for (auto peer : this->peers_) {
    this->del_peer(peer);
  }

  esp_err_t err = esp_now_deinit();
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "esp_now_deinit failed! 0x%x", err);
    return;
  }
  this->enabled_ = false;
}

void ESPNowComponent::set_wifi_channel(uint8_t channel) {
  if (this->is_wifi_enabled_()) {
    ESP_LOGE(TAG, "Manually changing the channel is not possible with WIFI enabled.");
    this->mark_failed();
    return;
  }

  if (this->is_ready() && (this->wifi_channel_ != channel)) {
    ESP_LOGI(TAG, "Channel is changed set to %d.", channel);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);
  }
  this->wifi_channel_ = channel;
}

bool ESPNowComponent::validate_channel_(uint8_t channel) {
  wifi_country_t g_self_country;
  esp_wifi_get_country(&g_self_country);
  if (channel >= g_self_country.schan + g_self_country.nchan) {
    ESP_LOGE(TAG, "Can't set channel %d, not allowed in country %c%c%c.", channel, g_self_country.cc[0],
             g_self_country.cc[1], g_self_country.cc[2]);
    return false;
  }
  return true;
}

#ifdef USE_WIFI
void ESPNowComponent::loop() {
  if (wifi::global_wifi_component != nullptr && wifi::global_wifi_component->is_connected()) {
    int32_t new_channel = wifi::global_wifi_component->get_wifi_channel();
    if (new_channel != this->wifi_channel_) {
      ESP_LOGI(TAG, "Wifi Channel is changed from %d to %d.", this->wifi_channel_, new_channel);
      this->wifi_channel_ = new_channel;
    }
  }
}
#endif

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
void ESPNowComponent::on_send_report(const esp_now_send_info_t *info, esp_now_send_status_t status)
#else
void ESPNowComponent::on_send_report(const uint8_t *mac_addr, esp_now_send_status_t status)
#endif
{
  ESPNowComponent *that = ESPNowComponent::static_;
  ESP_LOGI(TAG, "> Sent status.");
  uint64_t peer_address = 0ULL;
  if (that != nullptr) {
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
    memcpy((void *) peer_address, (void *) info->src_addr, 6);
    std::vector<uint8_t> payload(info->data, info->data + info->data_len);
#else
    // memcpy((void *) peer_address, (void *) mac_addr, 6);
    std::vector<uint8_t> payload;
#endif
    that->on_send_report_(peer_address, payload, status);
  }
}

void ESPNowComponent::on_send_report_(const uint64_t peer, std::vector<uint8_t> payload, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    ESP_LOGI(TAG, "Sent status: SUCCEED");
    this->call_trigger(ESPNowTriggers::ON_SUCCEED, peer, payload, 0);
  } else {
    ESP_LOGI(TAG, "Sent status: FAILED");
    this->call_trigger(ESPNowTriggers::ON_FAILED, peer, payload, 0);
  }
}

void ESPNowComponent::on_data_received(const esp_now_recv_info_t *info, const uint8_t *data, int size) {
  ESPNowComponent *that = ESPNowComponent::static_;
  ESP_LOGI(TAG, "< Received package.");

  if (that != nullptr) {
    that->on_data_received_(info, data, size);
  }
}

void ESPNowComponent::on_data_received_(const esp_now_recv_info_t *info, const uint8_t *data, int size) {
  bool broadcast = memcmp(info->des_addr, (void *) ESPNOW_BROADCAST_ADDR, ESP_NOW_ETH_ALEN) == 0;
  // packet->rssi(recv_info->rx_ctrl->rssi);
  // packet->timestamp(recv_info->rx_ctrl->timestamp);

  std::vector<uint8_t> payload(data, data + size);
  uint64_t peer = 0ULL;
  memcpy((void *) peer, (const void *) info->src_addr, 6);

  if (!esp_now_is_peer_exist(info->src_addr)) {
    ESP_LOGI(TAG, "Received packet from unknown device.");
    this->call_trigger(ESPNowTriggers::ON_NEW_PEER, peer, payload, broadcast ? ESP_MSG_ESPNOW_BROADCAST : 0);
  } else if (broadcast) {
    ESP_LOGI(TAG, "Received broadcast package.");
    this->call_trigger(ESPNowTriggers::ON_BROADCASTED, peer, payload, ESP_MSG_ESPNOW_BROADCAST);
  } else {
    ESP_LOGI(TAG, "Received unidirect package.");
    this->call_trigger(ESPNowTriggers::ON_RECEIVED, peer, payload, 0);
  }
}

esp_err_t ESPNowComponent::send(const uint64_t peer_address, std::vector<uint8_t> payload) {
  if (!this->can_proceed() || !this->is_ready()) {
    return ESP_ERR_ESPNOW_NOT_INIT;
  } else if (this->is_failed()) {
    return ESP_ERR_ESPNOW_FAILED;
  } else if (peer_address == 0ULL) {
    return ESP_ERR_ESPNOW_PEER_NOT_SET;
  } else if (peer_address == this->own_peer_address_) {
    return ESP_ERR_ESPNOW_OWN_PEER_ADDRESS;
  } else {
    if (payload.size() > ESP_NOW_MAX_DATA_LEN) {
      return ESP_ERR_ESPNOW_PAYLOAD_SIZE;
    }
    if ((!esp_now_is_peer_exist((uint8_t *) &peer_address) &&
         (peer_address == ESPNOW_BROADCAST_ADDR || this->auto_add_peer_))) {
      this->add_peer(peer_address);
    }
    this->last_send_state_ = esp_now_send((const uint8_t *) &peer_address, payload.data(), payload.size());
    return this->last_send_state_;
  }
}

esp_err_t ESPNowComponent::add_peer(uint64_t peer) {
  esp_err_t result = ESP_OK;
  esp_now_peer_info_t peer_info = {};

  if (peer == this->own_peer_address_) {
    this->mark_failed();
    return ESP_ERR_INVALID_MAC;
  }

  if (this->is_ready() && this->enabled_) {
    if (!esp_now_is_peer_exist((uint8_t *) &peer)) {
      memset(&peer_info, 0, sizeof(esp_now_peer_info_t));
      peer_info.ifidx = WIFI_IF_STA;
      memcpy((void *) peer_info.peer_addr, (void *) &peer, 6);
      result = esp_now_add_peer(&peer_info);
      if (result == ESP_OK) {
        this->defer("Add_peer_trigger", [this, peer]() {
          for (const auto &kv : this->interfaces_) {
            kv->on_add_peer(peer);
          }
        });
      }
    }
    if (result == ESP_OK) {
      int results = std::find(this->peers_.begin(), this->peers_.end(), peer) - this->peers_.begin();
      if (results == this->peers_.size()) {
        this->peers_.push_back(peer);
        if (this->is_ready()) {
          this->update_prefs_();
        }
      }
    }
  }
  return result;
}

esp_err_t ESPNowComponent::del_peer(uint64_t peer) {
  esp_err_t result = ESP_OK;
  if (this->is_ready() && this->enabled_) {
    if (esp_now_is_peer_exist((uint8_t *) &peer)) {
      esp_err_t result = esp_now_del_peer((uint8_t *) &peer);
      if (result == ESP_OK) {
        this->defer("del_peer_trigger", [this, peer]() {
          for (const auto &kv : this->interfaces_) {
            kv->on_del_peer(peer);
          }
        });
      }
    }
  }
  if (result == ESP_OK) {
    auto pos = std::find(this->peers_.begin(), this->peers_.end(), peer);
    if (pos != this->peers_.end()) {
      this->peers_.erase(pos);
      if (peer == this->default_peer_address_) {
        this->default_peer_address_ = 0;
      }
      if (this->is_ready()) {
        this->update_prefs_();
      }
    }
  }
  return result;
}

void ESPNowComponent::call_trigger(ESPNowTriggers event, const uint64_t peer_address, std::vector<uint8_t> payload,
                                   esp_err_t errorcode) {
  ESP_LOGI(TAG, "call triggger {%d}", (int) event);

  this->set_timeout(10, [this, event, peer_address, payload, errorcode]() {
    bool result = false;
    for (const auto &kv : this->interfaces_) {
      result = kv->call_trigger(event, peer_address, payload, errorcode);
      if (result) {
        break;
      }
    }
    if (!result && this->triggers_[event]) {
      this->triggers_[event]->trigger(peer_address, payload, errorcode);
    }
  });
}

/* ESPNowInterface ********************************************************************** */

esp_err_t ESPNowInterface::send(uint64_t peer, std::vector<uint8_t> payload) {
  return this->parent_->send(peer, payload);
}

bool ESPNowInterface::call_trigger(ESPNowTriggers event, const uint64_t peer_address, std::vector<uint8_t> payload,
                                   esp_err_t errorcode) {
  switch (event) {
  ON_NEW_PEER:
    return this->on_new_peer(peer_address, std::move(payload), errorcode);
  ON_RECEIVED:
    return this->on_received(peer_address, std::move(payload), errorcode);
  ON_BROADCASTED:
    return this->on_broadcasted(peer_address, std::move(payload), errorcode);
  ON_SUCCEED:
    return this->on_sent_succeed(peer_address, std::move(payload), errorcode);
  ON_FAILED:
    return this->on_sent_failed(peer_address, std::move(payload), errorcode);
    default:
      return false;
  }
}

uint64_t ESPNowInterface::get_default_peer_address_() { return this->parent_->get_default_peer_address(); }
void ESPNowInterface::set_default_peer_address_(uint64_t value) { this->parent_->set_default_peer_address(value); }

}  // namespace espnow
}  // namespace esphome

#endif
#endif
