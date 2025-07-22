#pragma once

#ifdef USE_ESP32

#include "espnow_err.h"

#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

#include <esp_err.h>
#include <esp_idf_version.h>
#include <esp_now.h>

namespace esphome {
namespace espnow {

static const uint8_t ESPNOW_BROADCAST_ADDR[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t ESPNOW_MULTICAST_ADDR[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE};

struct WifiPacketRxControl {
  int8_t rssi;         // Received Signal Strength Indicator (RSSI) of packet, unit: dBm
  uint32_t timestamp;  // Timestamp in microseconds when the packet was received, precise only if modem sleep or
                       // light sleep is not enabled
};

struct ESPNowRecvInfo {
  uint8_t src_addr[ESP_NOW_ETH_ALEN]; /**< Source address of ESPNOW packet */
  uint8_t des_addr[ESP_NOW_ETH_ALEN]; /**< Destination address of ESPNOW packet */
  wifi_pkt_rx_ctrl_t *rx_ctrl;        /**< Rx control info of ESPNOW packet */
};

class ESPNowPacket {
 public:
  // NOLINTNEXTLINE(readability-identifier-naming)
  enum esp_now_packet_type_t : uint8_t {
    RECEIVED,
    SENT,
  };

  // Constructor for received data
  ESPNowPacket(const esp_now_recv_info_t *info, const uint8_t *data, int size) {
    this->init_received_data_(info, data, size);
  };

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 5, 0)
  // Constructor for sent data
  ESPNowPacket(const esp_now_send_info_t *info, esp_now_send_status_t status) {
    this->init_sent_data(info->src_addr, status);
  }
#else
  // Constructor for sent data
  ESPNowPacket(const uint8_t *mac_addr, esp_now_send_status_t status) { this->init_sent_data(mac_addr, status); }
#endif

  // Destructor to clean up heap allocations
  ~ESPNowPacket() {}

  // Default constructor for pre-allocation in pool
  ESPNowPacket() {}

  void release() {}

  void load_received_data(const esp_now_recv_info_t *info, const uint8_t *data, int size) {
    this->type_ = RECEIVED;
    this->init_received_data_(info, data, size);
  }

  void load_sent_data(const uint8_t *mac_addr, esp_now_send_status_t status) {
    this->type_ = SENT;
    this->init_sent_data(mac_addr, status);
  }

  // Disable copy to prevent double-delete
  ESPNowPacket(const ESPNowPacket &) = delete;
  ESPNowPacket &operator=(const ESPNowPacket &) = delete;

  union {
    // NOLINTNEXTLINE(readability-identifier-naming)
    struct received_data {
      ESPNowRecvInfo info;                 // Information about the received packet
      uint8_t data[ESP_NOW_MAX_DATA_LEN];  // Data received in the packet
      uint8_t size;                        // Size of the received data
      WifiPacketRxControl rx_ctrl;         // Status of the received packet
    } receive;

    // NOLINTNEXTLINE(readability-identifier-naming)
    struct sent_data {
      uint8_t address[ESP_NOW_ETH_ALEN];
      esp_now_send_status_t status;
    } sent;
  } packet_;

  esp_now_packet_type_t type_;

  esp_now_packet_type_t type() const { return this->type_; }
  const ESPNowRecvInfo &get_receive_info() const { return this->packet_.receive.info; }

 private:
  void init_received_data_(const esp_now_recv_info_t *info, const uint8_t *data, int size) {
    memcpy(this->packet_.receive.info.src_addr, info->src_addr, ESP_NOW_ETH_ALEN);
    memcpy(this->packet_.receive.info.des_addr, info->des_addr, ESP_NOW_ETH_ALEN);
    memcpy(this->packet_.receive.data, data, size);
    this->packet_.receive.size = size;

    this->packet_.receive.rx_ctrl.rssi = info->rx_ctrl->rssi;
    this->packet_.receive.rx_ctrl.timestamp = info->rx_ctrl->timestamp;

    this->packet_.receive.info.rx_ctrl = reinterpret_cast<wifi_pkt_rx_ctrl_t *>(&this->packet_.receive.rx_ctrl);
  }

  void init_sent_data(const uint8_t *mac_addr, esp_now_send_status_t status) {
    memcpy(this->packet_.sent.address, mac_addr, ESP_NOW_ETH_ALEN);
    this->packet_.sent.status = status;
  }
};

}  // namespace espnow
}  // namespace esphome

#endif  // USE_ESP32
