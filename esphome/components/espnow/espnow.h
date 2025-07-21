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
  inline static constexpr const char *TAG = "espnow";
};

enum class ESPNowTriggers : uint8_t {
  TRIGGER_NONE = 0,
  ON_NEW_PEER = 1,
  ON_RECEIVED = 2,
  ON_BROADCASTED = 3,
  ON_SUCCEED = 10,
  ON_FAILED = 11,
};

const LogString *espnow_error_to_str(esp_err_t error);

class ESPNowComponent;
class ESPNowPacket;

using ESPNowTriggerCB = std::function<void(std::shared_ptr<ESPNowPacket>)>;

class ESPNowPacket {
 public:
  ESPNowPacket(uint64_t peer, const uint8_t *payload, size_t size);
  ESPNowPacket(const uint8_t *peer, const uint8_t *payload, int size);

  uint8_t *content() const { return (uint8_t *) this->content_.data(); }
  uint8_t *payload() const { return (uint8_t *) this->content_.data() + this->header_size(); }

  size_t size() const { return this->content_.size() - this->header_size(); }

  void peer_address(const uint8_t *value) { memcpy((void *) this->peer_address(), (const void *) value, 6); };
  uint8_t *peer_address() const { return (uint8_t *) &(this->peer_id_); }

  void peer_id(uint64_t value) { this->peer_id_ = value; }
  uint64_t peer_id() const { return this->peer_id_; }

  std::string peer_str() const;

  virtual std::string info() const;

  void timestamp(uint32_t value) { this->timestamp_ = value; }
  uint32_t timestamp() const { return this->timestamp_; }

  void errorcode(esp_err_t value) { this->errorcode_ = value; }
  esp_err_t errorcode() { return this->errorcode_; }

  void rssi(uint8_t value) { this->rssi_ = value; }
  uint8_t rssi() const { return this->rssi_; }

  void is_broadcasted(bool value) { this->is_broadcast_ = value; }
  bool is_broadcasted() { return this->is_broadcast_; }

  void write(size_t pos, size_t length, uint64_t value, bool header = false);
  uint64_t read(size_t pos, size_t length, bool header = false) const;

  void write8u(size_t pos, uint8_t value, bool header = false) { this->write(pos, sizeof(uint8_t), value, header); };
  uint8_t read8u(size_t pos, bool header = false) const {
    return static_cast<uint8_t>(this->read(pos, sizeof(uint8_t)), header);
  };

  void write16u(size_t pos, uint16_t value, bool header = false) { this->write(pos, sizeof(uint16_t), value, header); }
  uint16_t read16u(size_t pos, bool header = false) const {
    return static_cast<uint16_t>(this->read(pos, sizeof(uint16_t)), header);
  };

  void write32u(size_t pos, uint32_t value, bool header = false) { this->write(pos, sizeof(uint32_t), value, header); }
  uint32_t read32u(size_t pos, bool header = false) const {
    return static_cast<uint32_t>(this->read(pos, sizeof(uint32_t), header));
  };

  void write64u(size_t pos, uint64_t value, bool header = false) { this->write(pos, sizeof(uint64_t), value, header); }
  uint64_t read64u(size_t pos, bool header = false) const {
    return static_cast<uint64_t>(this->read(pos, sizeof(uint64_t), header));
  };

 protected:
  friend class ESPNowComponent;
  virtual size_t header_size() const { return 0; }

  std::vector<uint8_t> content_{};
  uint64_t peer_id_{0};
  uint32_t timestamp_{0};
  esp_err_t errorcode_{ESP_OK};
  uint8_t rssi_{0};
  bool is_broadcast_{false};
  bool is_received_{false};
};

class ESPNowExtension : public Parented<ESPNowComponent> {
 public:
  virtual void initialize() {}

  virtual bool on_add_peer(uint64_t peer) { return true; };
  virtual bool on_del_peer(uint64_t peer) { return true; };

  virtual bool on_new_peer(const std::weak_ptr<ESPNowPacket> &weak_packet) { return false; }
  virtual bool on_received(const std::weak_ptr<ESPNowPacket> &weak_packet) { return false; }
  virtual bool on_broadcasted(const std::weak_ptr<ESPNowPacket> &weak_packet) { return false; }
  virtual bool on_sent_succeed(const std::weak_ptr<ESPNowPacket> &weak_packet) { return false; }
  virtual bool on_sent_failed(const std::weak_ptr<ESPNowPacket> &weak_packet) { return false; }

  virtual bool call_trigger(ESPNowTriggers event, const std::weak_ptr<ESPNowPacket> &weak_packet);

  esp_err_t send(uint64_t peer, std::vector<uint8_t> payload);

 protected:
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
  void set_long_range(bool value) { this->long_range_ = value; }

  uint64_t get_default_peer_address() { return this->default_peer_address_; }
  void set_default_peer_address(uint64_t value);

  Trigger<std::shared_ptr<ESPNowPacket>> *get_trigger(ESPNowTriggers event);

  void call_trigger(ESPNowTriggers event, const std::weak_ptr<ESPNowPacket> &weak_packet);

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

  void register_extension(ESPNowExtension *app) {
    app->set_parent(this);
    this->extensions_.push_back(app);
    app->initialize();
  }

  esp_err_t send(uint64_t peer_address, std::vector<uint8_t> payload);
  bool get_last_send_state() { return this->last_send_state_; }

  static void on_data_received(const esp_now_recv_info_t *info, const uint8_t *data, int size);
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
  static void on_send_report(const esp_now_send_info_t *info, esp_now_send_status_t status);
#else
  static void on_send_report(const uint8_t *mac_addr, esp_now_send_status_t status);
#endif
  std::string peer_str(uint64_t peer);

 protected:
  bool is_wifi_enabled_();

  bool validate_channel_(uint8_t channel);
  void update_prefs_(){};

  // Needed to splits the enable becase ::is_raedy() is set to early,

  void enable_();

  uint64_t own_peer_address_{0};
  uint64_t default_peer_address_{0};

  uint8_t wifi_channel_{0};
  esp_err_t last_send_state_{false};

  bool is_suspended_{false};
  bool enabled_{true};
  bool long_range_{false};
  bool auto_add_peer_{false};

  std::map<ESPNowTriggers, Trigger<std::shared_ptr<ESPNowPacket>> *> triggers_{};

  std::vector<uint64_t> peers_{};
  std::vector<ESPNowExtension *> extensions_{};

  static ESPNowComponent *static_;  // NOLINT
};

}  // namespace espnow
}  // namespace esphome

#endif
#endif
