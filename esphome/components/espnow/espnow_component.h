#pragma once

#include "esphome/core/automation.h"
#include "esphome/core/component.h"

#ifdef USE_ESP32

#include "esphome/core/event_pool.h"
#include "esphome/core/lock_free_queue.h"
#include "espnow_packet.h"

#include <esp_idf_version.h>

#include <esp_mac.h>
#include <esp_now.h>

#include <array>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace esphome {
namespace espnow {

// Maximum size of the ESPNow event queue - must be power of 2 for lock-free queue
static constexpr size_t MAX_ESP_NOW_QUEUE_SIZE = 16;

enum class ESPNowTriggers : uint8_t {
  TRIGGER_NONE = 0,
  ON_NEW_PEER = 1,
  ON_RECEIVED = 2,
  ON_BROADCASTED = 3,
  ON_SUCCEED = 10,
  ON_FAILED = 11,
};

enum ESPNowState : uint8_t {
  /** Nothing has been initialized yet. */
  ESPNOW_STATE_OFF = 0,
  /** ESPNOW is disabled. */
  ESPNOW_STATE_DISABLED,
  /** ESPNOW is enabled. */
  ESPNOW_STATE_ENABLED,
};

struct ESPNowPeer {
  uint8_t address[ESP_NOW_ETH_ALEN];  // MAC address of the peer

  bool operator==(const ESPNowPeer &other) const { return memcmp(this->address, other.address, ESP_NOW_ETH_ALEN) == 0; }
  bool operator==(const uint8_t *other) const { return memcmp(this->address, other, ESP_NOW_ETH_ALEN) == 0; }
};

/// Handler interface for receiving ESPNow packets
/// Components should inherit from this class to handle incoming ESPNow data
class ESPNowReceivedPacketHandler {
 public:
  /// Called when an ESPNow packet is received
  /// @param info Information about the received packet (sender MAC, etc.)
  /// @param data Pointer to the received data payload
  /// @param size Size of the received data in bytes
  /// @return true if the packet was handled, false otherwise
  virtual bool espnow_received_handler(const ESPNowRecvInfo &info, const uint8_t *data, uint8_t size) = 0;
};

/// Handler interface for ESPNow packet transmission status
/// Components should inherit from this class to handle send confirmations
class ESPNowSentPacketHandler {
 public:
  /// Called when an ESPNow packet transmission is completed
  /// @param mac_addr MAC address of the recipient
  /// @param status ESP_NOW_SEND_SUCCESS or ESP_NOW_SEND_FAIL
  /// @return true if the status was handled, false otherwise
  virtual bool espnow_sent_handler(const uint8_t *mac_addr, esp_now_send_status_t status) = 0;
};

class ESPNowComponent : public Component {
 public:
  ESPNowComponent();
  void setup() override;
  void loop() override;
  void dump_config() override;

  float get_setup_priority() const override { return setup_priority::LATE; }

  // Add a peer to the internal list of peers
  void add_peer(std::array<uint8_t, ESP_NOW_ETH_ALEN> address) {
    ESPNowPeer peer;
    memcpy(peer.address, address.data(), ESP_NOW_ETH_ALEN);
    this->peers_.push_back(peer);
  }
  // Add a peer with the esp_now api and add to the internal list if doesnt exist already
  esp_err_t add_peer(const uint8_t *peer);
  // Remove a peer with the esp_now api and remove from the internal list if exists
  esp_err_t del_peer(const uint8_t *peer);

  void set_wifi_channel(uint8_t channel) { this->wifi_channel_ = channel; }
  void apply_wifi_channel();

  void set_auto_add_peer(bool value) { this->auto_add_peer_ = value; }

  void enable();
  void disable();
  bool is_disabled() const { return this->state_ == ESPNOW_STATE_DISABLED; };
  void set_enable_on_boot(bool enable_on_boot) { this->enable_on_boot_ = enable_on_boot; }
  bool is_wifi_enabled();

  esp_err_t send(const uint8_t *peer_address, std::vector<uint8_t> payload);

  void register_received_handler(ESPNowReceivedPacketHandler *handler) { this->received_handlers_.push_back(handler); }
  void register_sent_handler(ESPNowSentPacketHandler *handler) { this->sent_handlers_.push_back(handler); }

 protected:
  friend void on_data_received(const esp_now_recv_info_t *info, const uint8_t *data, int size);
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
  friend void on_send_report(const esp_now_send_info_t *info, esp_now_send_status_t status);
#else
  friend void on_send_report(const uint8_t *mac_addr, esp_now_send_status_t status);
#endif

  void enable_();

 private:
  std::vector<ESPNowReceivedPacketHandler *> received_handlers_;
  std::vector<ESPNowSentPacketHandler *> sent_handlers_;

  std::vector<ESPNowPeer> peers_{};

  uint8_t own_address_[ESP_NOW_ETH_ALEN]{0};
  LockFreeQueue<ESPNowPacket, MAX_ESP_NOW_QUEUE_SIZE> packet_queue_{};
  EventPool<ESPNowPacket, MAX_ESP_NOW_QUEUE_SIZE> packet_pool_{};

  uint8_t wifi_channel_{0};
  esp_err_t last_send_state_{false};
  ESPNowState state_{ESPNOW_STATE_OFF};

  bool auto_add_peer_{false};
  bool enable_on_boot_{true};
};

extern ESPNowComponent *global_esp_now;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

}  // namespace espnow
}  // namespace esphome

#endif  // USE_ESP32
