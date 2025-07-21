#pragma once

#include "esphome/core/automation.h"
#include "espnow.h"

#if defined(USE_ESP32)
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 1)

namespace esphome {
namespace espnow {

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

class ESPNowExtComponent : public ESPNowComponent {
 public:
  void register_extension(ESPNowExtension *app) {
    app->set_parent(this);
    this->extensions_.push_back(app);
    app->initialize();
  }

  void call_trigger(ESPNowTriggers event, const std::weak_ptr<ESPNowPacket> &weak_packet) override;

 protected:
  void report_add_peer(uint64_t peer) override;
  void report_del_peer(uint64_t peer) override;

  std::vector<ESPNowExtension *> extensions_{};
};

}  // namespace espnow
}  // namespace esphome

#endif
#endif
