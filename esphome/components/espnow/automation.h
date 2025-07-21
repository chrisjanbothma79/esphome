#pragma once

#include "esphome/core/automation.h"
#include "espnow.h"

#if defined(USE_ESP32)
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 1)

namespace esphome {
namespace espnow {

/*********************************  Actions **************************************/
template<typename... Ts> class SendAction : public Action<Ts...>, public Parented<ESPNowComponent> {
  TEMPLATABLE_VALUE(uint64_t, peer_address);
  TEMPLATABLE_VALUE(std::vector<uint8_t>, payload);

 public:
  void play(Ts... x) override {
    std::vector<uint8_t> payload = this->payload_.value(x...);
    uint64_t peer_address =
        this->peer_address_.has_value() ? this->peer_address_.value(x...) : this->parent_->get_default_peer_address();
    esp_err_t result = this->parent_->send(peer_address, payload);
    if (result != ESP_OK) {
      esph_log_w(ESPNowTAG::TAG, LOG_STR_ARG(espnow_error_to_str(result)));
    }
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

/********************************* Condition **************************************/

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
