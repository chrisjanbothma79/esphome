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
  TRIGGER_NONE = 0,
  ON_NEW_PEER = 1,
  ON_RECEIVED = 2,
  ON_BROADCASTED = 3,
  ON_SUCCEED = 10,
  ON_FAILED = 11,
};

void show_espnow_error(esp_err_t error);

class ESPNowComponent;

using EPSNowTrigger = std::function<void(std::shared_ptr<ESPNowPacket>)>;

class ESPNowPacket extend std::vector < uint8_t {
 public:
  ESPNowPacket(uint64_t peer, const uint8_t *payload, size_t size);
  ESPNowPacket(const uint8_t *mac_address, const uint8_t *payload, int size);

  uint8_t *content() const { return (uint8_t *) this->data(); }

  void peer_address(uint64_t value) { this->peer_ = value; }
  void peer_address(const uint8_t *value) { memcpy((void *) this->mac_address(), (const void *) value, 6); };
  uint8_t *peer_address() const { return (uint8_t *) &(this->peer_); }
  uint64_t peer_address64() const { return this->peer_; }

  void timestamp(uint32_t value) { this->timestamp_ = value; }
  uint32_t timestamp() const { return this->timestamp_; }

  void errorcode(esp_err_t value) { this->errorcode_ = value; }
  esp_err_t errorcode() { return this->errorcode_; }

  void rssi(uint8_t value) { this->rssi_ = value; }
  uint8_t rssi() const { return this->rssi_; }

  void is_broadcasted(bool value) { this->is_broadcast_ = value; }
  bool is_broadcasted() { return this->is_broadcast_; }

  void write(size_t offset, size_t length, uint64_t value, bool header = false);
  uint64_t read(size_t offset, size_t length, bool header = false) const;

  void write8u(size_t offset, uint8_t value, bool header = false) {
    this->write(offset, sizeof(uint8_t), value, header);
  };
  uint8_t read8u(size_t offset, bool header = false) const {
    return static_cast<uint8_t>(this->read(offset, sizeof(uint8_t)), header);
  };

  void write16u(size_t offset, uint16_t value, bool header = false) {
    this->write(offset, sizeof(uint16_t), value, header);
  }
  uint16_t read16u(size_t offset, bool header = false) const {
    return static_cast<uint16_t>(this->read(offset, sizeof(uint16_t)), header);
  };

  void write32u(size_t offset, uint16_t value, bool header = false) {
    this->write(offset, sizeof(uint32_t), value, header);
  }
  uint32_t read32u(size_t offset, bool header = false) const {
    return static_cast<uint32_t>(this->read(offset, sizeof(uint32_t), header));
  };

  void write64u(size_t offset, uint16_t value, bool header = false) {
    this->write(offset, sizeof(uint64_t), value, header);
  }
  uint64_t read64u(size_t offset, bool header = false) const {
    return static_cast<uint64_t>(this->read(offset, sizeof(uint64_t), header));
  };

 protected:
  friend class ESPNowComponent;
  virtual size_t get_header_size() { return 0; }

  uint64_t peer_{0};
  uint32_t timestamp_{0};
  esp_err_t errorcode_{esp_OK};
  uint8_t rssi_{0};
  bool is_broadcast_{false};
};

class ESPNowInterface : public Parented<ESPNowComponent> {
 public:
  virtual void initialize() {}

  virtual bool on_add_peer(uint64_t peer) { return true; };
  virtual bool on_del_peer(uint64_t peer) { return true; };

  virtual bool on_new_peer(const std::weak_ptr<ESPNowPacket> weak_packet) { return false; }
  virtual bool on_received(const std::weak_ptr<ESPNowPacket> weak_packet) { return false; }
  virtual bool on_broadcasted(const std::weak_ptr<ESPNowPacket> weak_packet) { return false; }
  virtual bool on_sent_succeed(const std::weak_ptr<ESPNowPacket> weak_packet) { return false; }
  virtual bool on_sent_failed(const std::weak_ptr<ESPNowPacket> weak_packet) { return false; }
  bool call_trigger(ESPNowTriggers event, const std::weak_ptr<ESPNowPacket> weak_packet);
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

  void call_trigger(ESPNowTriggers event, std::weak_ptr<ESPNowPacket> weak_packet);

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
  std::string peer_string(const uint64_t peer);

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
    uint64_t peer_address =
        this->peer_address_.has_value() ? this->peer_address_.value(x...) : this->parent_->get_default_peer_address();

    show_espnow_error(this->parent_->send(peer_address, payload));
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
