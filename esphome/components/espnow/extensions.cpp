#include "esphome/core/automation.h"
#include "extensions.h"

#if defined(USE_ESP32)
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 1)

namespace esphome {
namespace espnow {

/* ESPNowExtension ********************************************************************** */

esp_err_t ESPNowExtension::send(uint64_t peer, std::vector<uint8_t> payload) {
  return this->parent_->send(peer, std::move(payload));
}

bool ESPNowExtension::call_trigger(ESPNowTriggers event, const std::weak_ptr<ESPNowPacket> &weak_packet) {
  switch (event) {
    case ESPNowTriggers::ON_NEW_PEER:
      return this->on_new_peer(weak_packet);
    case ESPNowTriggers::ON_RECEIVED:
      return this->on_received(weak_packet);
    case ESPNowTriggers::ON_BROADCASTED:
      return this->on_broadcasted(weak_packet);
    case ESPNowTriggers::ON_SUCCEED:
      return this->on_sent_succeed(weak_packet);
    case ESPNowTriggers::ON_FAILED:
      return this->on_sent_failed(weak_packet);
    default:
      return false;
  }
}

uint64_t ESPNowExtension::get_default_peer_address_() { return this->parent_->get_default_peer_address(); }
void ESPNowExtension::set_default_peer_address_(uint64_t value) { this->parent_->set_default_peer_address(value); }

/* ESPNowExtension ********************************************************************** */

void ESPNowExtComponent::report_add_peer(uint64_t peer) {
  this->defer("Add_peer_trigger", [this, peer]() {
    for (const auto &kv : this->extensions_) {
      kv->on_add_peer(peer);
    }
  });
};

void ESPNowExtComponent::report_del_peer(uint64_t peer) {
  this->defer("Add_peer_trigger", [this, peer]() {
    for (const auto &kv : this->extensions_) {
      kv->on_del_peer(peer);
    }
  });
};

void ESPNowExtComponent::call_trigger(ESPNowTriggers event, const std::weak_ptr<ESPNowPacket> &weak_packet) {
  bool result = false;
  for (const auto &kv : this->extensions_) {
    result = kv->call_trigger(event, weak_packet);
    if (result) {
      break;
    }
  }
  if (!result) {
    ESPNowComponent::call_trigger(event, weak_packet);
  }
};

}  // namespace espnow
}  // namespace esphome

#endif
#endif
