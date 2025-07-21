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

static constexpr const char *TAG = ESPNowTAG::TAG;

static const esp_err_t ESP_ERR_ESPNOW_CMP_BASE = (ESP_ERR_ESPNOW_BASE + 20);
static const esp_err_t ESP_ERR_ESPNOW_FAILED = (ESP_ERR_ESPNOW_CMP_BASE + 1);
static const esp_err_t ESP_ERR_ESPNOW_OWN_PEER_ADDRESS = (ESP_ERR_ESPNOW_CMP_BASE + 2);
static const esp_err_t ESP_ERR_ESPNOW_PAYLOAD_SIZE = (ESP_ERR_ESPNOW_CMP_BASE + 3);
static const esp_err_t ESP_ERR_ESPNOW_PEER_NOT_SET = (ESP_ERR_ESPNOW_CMP_BASE + 4);

static const esp_err_t ESP_MSG_ESPNOW_BROADCAST = (ESP_ERR_ESPNOW_BASE + 10);

static const esp_err_t CONFIG_ESPNOW_WAKE_WINDOW = 50;
static const esp_err_t CONFIG_ESPNOW_WAKE_INTERVAL = 100;

ESPNowComponent *ESPNowComponent::static_{nullptr};  // NOLINT

const LogString *espnow_error_to_str(esp_err_t error) {
  switch (error) {
    case ESP_ERR_ESPNOW_FAILED:
      return LOG_STR("Cannot send espnow packet, espnow is in fail mode.");
    case ESP_ERR_ESPNOW_OWN_PEER_ADDRESS:
      return LOG_STR("Trying to send a message to your self.");
    case ESP_ERR_ESPNOW_PAYLOAD_SIZE:
      return LOG_STR("Trying to send a payload size to large.");
    case ESP_ERR_ESPNOW_PEER_NOT_SET:
      return LOG_STR("Peer address not set.");
    case ESP_ERR_ESPNOW_NOT_INIT:
      return LOG_STR("ESPNOW not init.");
    case ESP_ERR_ESPNOW_ARG:
      return LOG_STR("Invalid argument");
    case ESP_ERR_ESPNOW_INTERNAL:
      return LOG_STR("Internal Error");
    case ESP_ERR_ESPNOW_NO_MEM:
      return LOG_STR("Our of memory");
    case ESP_ERR_ESPNOW_NOT_FOUND:
      return LOG_STR("Peer not found.");
    case ESP_ERR_ESPNOW_IF:
      return LOG_STR("Interface does not match.");
    default:
      return LOG_STR("Unknown Error.");
  }
}

std::string peer_str(uint64_t peer) {
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

/* ESPNowPacket ********************************************************************** */

ESPNowPacket::ESPNowPacket(uint64_t peer, const uint8_t *payload, size_t size) {
  if (size > ESP_NOW_MAX_DATA_LEN) {
    ESP_LOGE(TAG, "Payload size %zu is larger than max (%d bytes)", size, ESP_NOW_MAX_DATA_LEN);
    return;
  }
  this->peer_id(peer);

  if (size > 0) {
    this->content_.insert(this->content_.begin(), payload, payload + size);
  }
}

ESPNowPacket::ESPNowPacket(const uint8_t *peer, const uint8_t *payload, int size) {
  this->peer_address(peer);
  if (size > 0) {
    this->content_.insert(this->content_.begin(), payload, payload + size);
  }
}

void ESPNowPacket::write(size_t pos, size_t length, uint64_t value, bool header) {
  pos += length;
  if (header) {
    pos += this->header_size();
  }
  while (length-- != 0) {
    this->content_[--pos] = static_cast<uint8_t>(value);
    value >>= 8;
  }
}

uint64_t ESPNowPacket::read(size_t pos, size_t length, bool header) const {
  uint64_t result = 0;

  pos += length;
  if (header) {
    pos += this->header_size();
  }
  if (pos > this->content_.size()) {
    esph_log_e(ESPNowTAG::TAG, "Trying to read outside content size (%d of %d).", pos, this->content_.size());
    return 0;
  }

  while (length-- != 0) {
    result <<= 8;
    result |= this->content_[--pos];
  }
  return result;
}

std::string ESPNowPacket::info() const {
  char info[100];
  char mode[2] = {this->is_received_ ? 'R' : 'S', this->is_broadcast_ ? 'U' : 'B'};

  snprintf(info, sizeof(info), "%c%c > %s, Broadcast: %s, Size: %d ", mode[0], mode[1],
           peer_str(this->peer_id()).c_str(), this->size());
  return info;
}

/* ESPNowComponent ********************************************************************** */

ESPNowComponent::ESPNowComponent() { ESPNowComponent::static_ = this; }  // NOLINT

void ESPNowComponent::dump_config() {
  uint32_t version = 0;
  esp_now_get_version(&version);

  ESP_LOGCONFIG(TAG,
                "esp_now: V%d %s\n"
                "  Wifi channel: %d\n"
                "  WIFI enabled: %s\n"
                "  Own Mac address: %s\n"
                "  Default Mac Address: %s\n"
                "  Long range mode: %s",
                version, this->enabled_ ? "" : "[Disabled]", this->wifi_channel_, YESNO(this->is_wifi_enabled_()),
                peer_str(this->own_peer_address_).c_str(), peer_str(this->default_peer_address_).c_str(),
                YESNO(this->long_range_));
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

void ESPNowComponent::set_default_peer_address(uint64_t value) {
  this->default_peer_address_ = value;
  this->update_prefs_();
}

Trigger<std::shared_ptr<ESPNowPacket>> *ESPNowComponent::get_trigger(ESPNowTriggers event) {
  if (this->triggers_[event] == nullptr) {
    this->triggers_[event] = new Trigger<std::shared_ptr<ESPNowPacket>>();
  }
  return this->triggers_[event];
}

void ESPNowComponent::enable() {
  if (this->enabled_ && this->is_ready()) {
    ESP_LOGE(TAG, "Already enabled.");
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
    if (this->long_range_) {
      //     esp_wifi_set_protocol(ESPNOW_WIFI_IF,
      //                            WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N | WIFI_PROTOCOL_LR);
    }

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

#ifdef USE_DEEP_SLEEP
  esp_now_set_wake_window(CONFIG_ESPNOW_WAKE_WINDOW);
  esp_wifi_connectionless_module_set_wake_interval(CONFIG_ESPNOW_WAKE_INTERVAL);
#endif

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
  ESPNowTriggers event = ESPNowTriggers::TRIGGER_NONE;

  ESP_LOGVV(TAG, "> Sent status.");
  if (that != nullptr) {
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
    auto packet = std::make_shared<ESPNowPacket>(info->src_addr, info->data, info->data_len);  // NOLINT
#else
    auto packet = std::make_shared<ESPNowPacket>(mac_addr, nullptr, 0);  // NOLINT
#endif
    if (status == ESP_NOW_SEND_SUCCESS) {
      ESP_LOGV(TAG, "Sent status: SUCCEED");
      event = ESPNowTriggers::ON_SUCCEED;
    } else {
      ESP_LOGV(TAG, "Sent status: FAILED");
      event = ESPNowTriggers::ON_FAILED;
    }
    that->set_timeout(10, [that, event, packet]() { that->call_trigger(event, packet); });
  }
}

void ESPNowComponent::on_data_received(const esp_now_recv_info_t *info, const uint8_t *data, int size) {
  ESPNowComponent *that = ESPNowComponent::static_;
  ESP_LOGI(TAG, "< Received package.");
  ESPNowTriggers event = ESPNowTriggers::TRIGGER_NONE;
  if (that != nullptr) {
    auto packet = std::make_shared<ESPNowPacket>(info->src_addr, data, size);  // NOLINT
    bool broadcast = memcmp(info->des_addr, (void *) &ESPNOW_BROADCAST_ADDR, ESP_NOW_ETH_ALEN) == 0;
    packet->rssi(info->rx_ctrl->rssi);
    packet->timestamp(info->rx_ctrl->timestamp);
    packet->is_broadcasted(broadcast);
    packet->is_received_ = true;

    if (!esp_now_is_peer_exist(info->src_addr)) {
      ESP_LOGV(TAG, "Received packet from unknown device.");
      event = ESPNowTriggers::ON_NEW_PEER;
      if (that->auto_add_peer_) {
        that->add_peer(packet->peer_id());
      }
    } else if (broadcast) {
      ESP_LOGV(TAG, "Received broadcast package.");
      event = ESPNowTriggers::ON_BROADCASTED;
    } else {
      ESP_LOGV(TAG, "Received unicast package.");
      event = ESPNowTriggers::ON_RECEIVED;
    }
    that->set_timeout(10, [that, event, packet]() { that->call_trigger(event, packet); });
  }
}

void ESPNowComponent::call_trigger(ESPNowTriggers event, const std::weak_ptr<ESPNowPacket> &weak_packet) {
  if (this->triggers_[event]) {
    ESP_LOGI(TAG, "call triggger {%d}", (int) event);
    auto packet = weak_packet.lock();
    this->triggers_[event]->trigger(packet);
  }
}

esp_err_t ESPNowComponent::send(uint64_t peer_address, std::vector<uint8_t> payload) {
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
        this->report_add_peer(peer);
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
        this->report_del_peer(peer);
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

}  // namespace espnow
}  // namespace esphome

#endif
#endif
