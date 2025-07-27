#pragma once

#ifdef USE_ESP32

#include "espnow_component.h"

#include "esphome/core/automation.h"
#include "esphome/core/base_automation.h"

namespace esphome {
namespace espnow {

template<typename... Ts> class SendAction : public Action<Ts...>, public Parented<ESPNowComponent> {
 public:
  void add_on_sent(const std::vector<Action<Ts...> *> &actions) {
    this->sent_.add_actions(actions);
    if (this->flags_.wait_for_sent) {
      this->sent_.add_action(new LambdaAction<Ts...>([this](Ts... x) { this->play_next_(x...); }));
    }
  }
  void add_on_error(const std::vector<Action<Ts...> *> &actions) {
    this->error_.add_actions(actions);
    if (this->flags_.wait_for_sent) {
      this->error_.add_action(new LambdaAction<Ts...>([this](Ts... x) {
        if (this->flags_.continue_on_error) {
          this->play_next_(x...);
        } else {
          this->stop_complex();
        }
      }));
    }
  }

  void set_wait_for_sent(bool wait_for_sent) { this->flags_.wait_for_sent = wait_for_sent; }
  void set_continue_on_error(bool continue_on_error) { this->flags_.continue_on_error = continue_on_error; }
  void set_data_template(std::function<std::vector<uint8_t>(Ts...)> func) {
    this->data_func_ = func;
    this->flags_.data_is_static = false;
  }
  void set_data_static(const std::vector<uint8_t> &data) {
    this->data_static_ = data;
    this->flags_.data_is_static = true;
  }
  void set_address_template(std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> func) {
    this->address_func_ = func;
    this->flags_.address_is_static = false;
  }
  void set_address_static(const std::array<uint8_t, ESP_NOW_ETH_ALEN> &address) {
    this->address_static_ = address;
    this->flags_.address_is_static = true;
  }
  void play_complex(Ts... x) override {
    this->num_running_++;
    send_callback_t send_callback = [this, x...](esp_err_t status) {
      if (status == ESP_OK) {
        if (this->sent_.empty() && this->flags_.wait_for_sent) {
          this->play_next_(x...);
        } else if (!this->sent_.empty()) {
          this->sent_.play(x...);
        }
      } else {
        if (this->error_.empty() && this->flags_.wait_for_sent) {
          if (this->flags_.continue_on_error) {
            this->play_next_(x...);
          } else {
            this->stop_complex();
          }
        } else if (!this->error_.empty()) {
          this->error_.play(x...);
        }
      }
    };
    if (this->flags_.address_is_static && this->flags_.data_is_static) {
      this->parent_->send(this->address_static_.data(), this->data_static_, send_callback);
    } else if (this->flags_.address_is_static) {
      auto data = this->data_func_(x...);
      this->parent_->send(this->address_static_.data(), data, send_callback);
    } else if (this->flags_.data_is_static) {
      auto address = this->address_func_(x...);
      this->parent_->send(address.data(), this->data_static_, send_callback);
    } else {
      auto address = this->address_func_(x...);
      auto data = this->data_func_(x...);
      this->parent_->send(address.data(), data, send_callback);
    }
    if (!this->flags_.wait_for_sent) {
      this->play_next_(x...);
    }
  }

  void play(Ts... x) override { /* ignore - see play_complex */
  }

  void stop() override {
    this->sent_.stop();
    this->error_.stop();
  }

 protected:
  ActionList<Ts...> sent_;
  ActionList<Ts...> error_;

  std::function<std::array<uint8_t, ESP_NOW_ETH_ALEN>(Ts...)> address_func_;
  std::function<std::vector<uint8_t>(Ts...)> data_func_;
  std::array<uint8_t, ESP_NOW_ETH_ALEN> address_static_{0};
  std::vector<uint8_t> data_static_;
  struct {
    uint8_t address_is_static : 1;  // Is the address static or dynamic
    uint8_t data_is_static : 1;     // Is the data static or dynamic
    uint8_t wait_for_sent : 1;      // Wait for the send operation to complete before continuing automation
    uint8_t continue_on_error : 1;  // Continue automation even if the send operation fails
    uint8_t reserved : 4;           // Reserved for future use
  } flags_{0};
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

class ESPNowHandlerTrigger : public Trigger<const ESPNowRecvInfo &, const uint8_t *, uint8_t>,
                             public ESPNowReceivedPacketHandler {
 public:
  explicit ESPNowHandlerTrigger(ESPNowComponent *parent, std::array<uint8_t, ESP_NOW_ETH_ALEN> address)
      : parent_(parent), has_address_(true) {
    memcpy(this->address_, address.data(), ESP_NOW_ETH_ALEN);
  }

  explicit ESPNowHandlerTrigger(ESPNowComponent *parent) : parent_(parent), has_address_(false) {}

  bool handle_trigger(const ESPNowRecvInfo &info, const uint8_t *data, uint8_t size) override {
    bool match = !this->has_address_ || (memcmp(this->address_, info.src_addr, ESP_NOW_ETH_ALEN) == 0);
    if (!match)
      return false;

    this->trigger(info, data, size);
    return false;  // Return false to continue processing other internal handlers
  }

 protected:
  ESPNowComponent *parent_;
  bool has_address_{false};
  const uint8_t *address_[ESP_NOW_ETH_ALEN];
};

class OnReceiveTrigger : public ESPNowHandlerTrigger, public ESPNowReceivedPacketHandler {
  bool on_received(const ESPNowRecvInfo &info, const uint8_t *data, uint8_t size) override {
    return this->handle_trigger(info, data, size);
  }
};
class OnUnknownPeerTrigger : public ESPNowHandlerTrigger, public ESPNowUnknownPeerHandler {
  bool on_unknown_peer(const ESPNowRecvInfo &info, const uint8_t *data, uint8_t size) override {
    return this->handle_trigger(info, data, size);
  }
};
class OnBroadcastedTrigger : public ESPNowHandlerTrigger, public ESPNowBroadcastedHandler {
  bool on_broadcasted(const ESPNowRecvInfo &info, const uint8_t *data, uint8_t size) override {
    return this->handle_trigger(info, data, size);
  }
};

}  // namespace espnow
}  // namespace esphome

#endif  // USE_ESP32
