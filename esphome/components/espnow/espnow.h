#pragma once
#include "esphome/core/automation.h"
#include "esphome/core/base_automation.h"
#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

#if defined(USE_ESP32)
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 1)

#include "esp_mac.h"
#include <esp_now.h>

#include <algorithm>  // std::max
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace esphome {
namespace espnow {

static const uint64_t ESPNOW_BROADCAST_ADDR = 0xFFFFFFFFFFFF;
static const uint64_t ESPNOW_MULTICAST_ADDR = 0xFFFFFFFFFFFE;

class ESPNowTAG {
 public:
  // could be made inline with C++17
  static const char *const TAG;
};

enum class ESPNowTriggers : uint8_t {
  ON_NEW_PEER = 1,
  ON_RECEIVED = 2,
  ON_BROADCASTED = 3,
  ON_SUCCEED = 10,
  ON_FAILED = 20,

};

void show_espnow_error(esp_err_t error);

class ESPNowComponent;

using ESPNowTrigger = Trigger<uint64_t, std::vector<uint8_t>, esp_err_t>;

class ESPNowInterface : public Parented<ESPNowComponent> {
 public:
  virtual void initialize() {}

  virtual bool on_add_peer(uint64_t peer) { return true; };
  virtual bool on_del_peer(uint64_t peer) { return true; };

  virtual bool on_new_peer(const uint64_t peer_address, std::vector<uint8_t> payload, esp_err_t errorcode) {
    return false;
  }
  virtual bool on_received(const uint64_t peer_address, std::vector<uint8_t> payload, esp_err_t errorcode) {
    return false;
  }
  virtual bool on_broadcasted(const uint64_t peer_address, std::vector<uint8_t> payload, esp_err_t errorcode) {
    return false;
  }
  virtual bool on_sent_succeed(const uint64_t peer_address, std::vector<uint8_t> payload, esp_err_t errorcode) {
    return false;
  }
  virtual bool on_sent_failed(const uint64_t peer_address, std::vector<uint8_t> payload, esp_err_t errorcode) {
    return false;
  }
  bool call_trigger(ESPNowTriggers event, const uint64_t peer_address, std::vector<uint8_t> payload,
                    esp_err_t errorcode = 0);
  esp_err_t send(uint64_t peer, std::vector<uint8_t> payload);

 private:
  uint64_t get_default_peer_address_();
  void set_default_peer_address_(uint64_t value);
};

class ESPNowComponent : public Component {
 public:
  ESPNowComponent();

  void dump_config() override;

  float get_setup_priority() const override { return -100; }

  esp_err_t add_peer(uint64_t peer);
  esp_err_t del_peer(uint64_t peer);

  uint8_t get_wifi_channel() { return this->wifi_channel_; }
  void set_wifi_channel(uint8_t channel);

  void set_auto_add_peer(bool value) { this->auto_add_peer_ = value; }
  void set_response_timeout(uint32_t timeout) { this->response_timeout_ = timeout; }
  void set_long_range(bool value) { this->long_range_ = value; }

  uint64_t get_default_peer_address() { return this->default_peer_address_; }
  void set_default_peer_address(uint64_t value) {
    this->default_peer_address_ = value;
    this->update_prefs_();
  }

  ESPNowTrigger *get_trigger(ESPNowTriggers event) {
    if (this->triggers_[event] == nullptr) {
      this->triggers_[event] = new ESPNowTrigger();
    }
    return this->triggers_[event];
  }

  void call_trigger(ESPNowTriggers event, const uint64_t peer_address, std::vector<uint8_t> payload,
                    esp_err_t errorcode = 0);

  uint64_t get_own_peer_address() const { return this->own_peer_address_; }

  void set_enable_state(bool value);
  void enable();
  void disable();
  bool is_enabled() { return this->enabled_; };

  void setup() override;
#ifdef USE_WIFI
  void loop() override;
#endif

  bool can_proceed() override;

  void register_interface(ESPNowInterface *app) {
    app->set_parent(this);
    this->interfaces_.push_back(app);
    app->initialize();
  }

  esp_err_t send(const uint64_t peer_address, std::vector<uint8_t> payload);
  bool get_last_send_state() { return this->last_send_state_; }

  static void on_data_received(const esp_now_recv_info_t *info, const uint8_t *data, int size);
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
  static void on_send_report(const esp_now_send_info_t *info, esp_now_send_status_t status);
#else
  static void on_send_report(const uint8_t *mac_addr, esp_now_send_status_t status);
#endif

 protected:
  void on_data_received_(const esp_now_recv_info_t *info, const uint8_t *data, int size);
  void on_send_report_(const uint64_t peer_address, std::vector<uint8_t> payload, esp_now_send_status_t status);

  bool is_wifi_enabled_();

  bool validate_channel_(uint8_t channel);
  void update_prefs_(){};

  // Needed to splits the enable becase ::is_raedy() is set to early,

  void enable_();

  uint64_t own_peer_address_{0};
  uint64_t default_peer_address_{0};

  uint32_t response_timeout_{5000};

  uint8_t wifi_channel_{0};
  esp_err_t last_send_state_{false};

  bool is_suspended_{false};
  bool enabled_{true};
  bool long_range_{false};
  bool auto_add_peer_{false};

  std::map<ESPNowTriggers, ESPNowTrigger *> triggers_{};

  std::vector<uint64_t> peers_{};
  std::vector<ESPNowInterface *> interfaces_{};

  static ESPNowComponent *static_;  // NOLINT
};

/*********************************  Actions **************************************/
template<typename... Ts> class SendAction : public Action<Ts...>, public Parented<ESPNowComponent> {
  TEMPLATABLE_VALUE(uint64_t, peer_address);
  TEMPLATABLE_VALUE(std::vector<uint8_t>, payload);

 public:
  void play(Ts... x) override {
    std::vector<uint8_t> payload = this->payload_.value(x...);
    uint64_t mac =
        this->peer_address_.has_value() ? this->peer_address_.value(x...) : this->parent_->get_default_peer_address();

    show_espnow_error(this->parent_->send(mac, payload));
  }
};

template<typename... Ts> class SetChannelAction : public Action<Ts...>, public Parented<ESPNowComponent> {
 public:
  TEMPLATABLE_VALUE(int8_t, channel);
  void play(Ts... x) override {
    int8_t value = this->channel_.value(x...);
    this->parent_->set_wifi_channel(value);
  }
};

/********************************* triggers **************************************/

template<typename... Ts> class IsLastStatusCondition : public Condition<Ts...> {
 public:
  explicit IsLastStatusCondition(ESPNowComponent *espnow) : espnow_(espnow) {}
  bool check(Ts... x) override { return this->espnow_->get_last_send_state() == ESP_OK; }

 protected:
  ESPNowComponent *espnow_;
};

}  // namespace espnow
}  // namespace esphome

#endif
#endif
