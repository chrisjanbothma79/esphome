#pragma once

#ifdef USE_ESP32

#include "espnow_component.h"

#include "esphome/core/automation.h"
#include "esphome/core/log.h"

namespace esphome {
namespace espnow {

template<typename... Ts> class SendAction : public Action<Ts...>, public Parented<ESPNowComponent> {
 public:
  void set_data_template(std::function<std::vector<uint8_t>(Ts...)> func) {
    this->data_func_ = func;
    this->data_is_static_ = false;
  }
  void set_data_static(const std::vector<uint8_t> &data) {
    this->data_static_ = data;
    this->data_is_static_ = true;
  }
  void set_address_template(std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> func) {
    this->address_func_ = func;
    this->address_is_static_ = false;
  }
  void set_address_static(const std::array<uint8_t, ESP_NOW_ETH_ALEN> &address) {
    this->address_static_ = address;
    this->address_is_static_ = true;
  }
  void play(Ts... x) override {
    if (this->address_is_static_ && this->data_is_static_) {
      this->parent_->send(this->address_static_.data(), this->data_static_);
    } else if (this->address_is_static_) {
      auto data = this->data_func_(x...);
      this->parent_->send(this->address_static_.data(), data);
    } else if (this->data_is_static_) {
      auto address = this->address_func_(x...);
      this->parent_->send(address.data(), this->data_static_);
    } else {
      auto address = this->address_func_(x...);
      auto data = this->data_func_(x...);
      this->parent_->send(address.data(), data);
    }
  }

 protected:
  std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> address_func_;
  std::function<std::vector<uint8_t>(Ts...)> data_func_;
  std::array<uint8_t, ESP_NOW_ETH_ALEN> address_static_{0};
  std::vector<uint8_t> data_static_;
  bool address_is_static_{false};
  bool data_is_static_{false};
};

template<typename... Ts> class AddPeerAction : public Action<Ts...>, public Parented<ESPNowComponent> {
 public:
  void set_address_template(std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> func) {
    this->address_func_ = func;
    this->address_is_static_ = false;
  }
  void set_address_static(const std::array<uint8_t, ESP_NOW_ETH_ALEN> &address) {
    this->address_static_ = address;
    this->address_is_static_ = true;
  }
  void play(Ts... x) override {
    if (this->address_is_static_) {
      this->parent_->add_peer(this->address_static_.data());
    } else {
      auto address = this->address_func_(x...);
      this->parent_->add_peer(address.data());
    }
  }

 protected:
  std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> address_func_;
  std::array<uint8_t, ESP_NOW_ETH_ALEN> address_static_{0};
  bool address_is_static_{false};
};

template<typename... Ts> class DeletePeerAction : public Action<Ts...>, public Parented<ESPNowComponent> {
 public:
  void set_address_template(std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> func) {
    this->address_func_ = func;
    this->address_is_static_ = false;
  }
  void set_address_static(const std::array<uint8_t, ESP_NOW_ETH_ALEN> &address) {
    this->address_static_ = address;
    this->address_is_static_ = true;
  }
  void play(Ts... x) override {
    if (this->address_is_static_) {
      this->parent_->del_peer(this->address_static_.data());
    } else {
      auto address = this->address_func_(x...);
      this->parent_->del_peer(address.data());
    }
  }

 protected:
  std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> address_func_;
  std::array<uint8_t, ESP_NOW_ETH_ALEN> address_static_{0};
  bool address_is_static_{false};
};

template<typename... Ts> class SetChannelAction : public Action<Ts...>, public Parented<ESPNowComponent> {
 public:
  TEMPLATABLE_VALUE(uint8_t, channel)
  void play(Ts... x) override {
    if (this->parent_->is_wifi_enabled()) {
      return;
    }
    this->parent_->set_wifi_channel(this->channel_.value(x...));
    this->parent_->apply_wifi_channel();
  }
};

class OnReceiveTrigger : public Trigger<const ESPNowRecvInfo &, const uint8_t *, uint8_t>,
                         public ESPNowReceivedPacketHandler {
 public:
  explicit OnReceiveTrigger(ESPNowComponent *parent, std::array<uint8_t, ESP_NOW_ETH_ALEN> address)
      : parent_(parent), has_address_(true) {
    memcpy(this->address_, address.data(), ESP_NOW_ETH_ALEN);
  }

  explicit OnReceiveTrigger(ESPNowComponent *parent) : parent_(parent), has_address_(false) {}

  void espnow_received_handler(const ESPNowRecvInfo &info, const uint8_t *data, uint8_t size) override {
    bool match = !this->has_address_ || (memcmp(this->address_, info.src_addr, ESP_NOW_ETH_ALEN) == 0);
    if (!match)
      return;

    this->trigger(info, data, size);
  }

 protected:
  ESPNowComponent *parent_;
  bool has_address_{false};
  const uint8_t *address_[ESP_NOW_ETH_ALEN];
};

}  // namespace espnow
}  // namespace esphome

#endif  // USE_ESP32
