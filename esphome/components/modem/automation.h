#pragma once

#ifdef USE_ESP_IDF

#include "modem_component.h"

#include "esphome/core/automation.h"

namespace esphome {
namespace modem {

class ModemOnNotRespondingTrigger : public Trigger<> {
 public:
  explicit ModemOnNotRespondingTrigger(ModemComponent *parent) {
    parent->add_on_state_callback([this, parent](ModemComponentState old_state, ModemComponentState state) {
      if (!parent->is_failed() && state == ModemComponentState::NOT_RESPONDING) {
        this->trigger();
      }
    });
  }
};

class ModemOnConnectTrigger : public Trigger<> {
 public:
  explicit ModemOnConnectTrigger(ModemComponent *parent) {
    parent->add_on_state_callback([this, parent](ModemComponentState old_state, ModemComponentState state) {
      if (!parent->is_failed() && state == ModemComponentState::CONNECTED) {
        this->trigger();
      }
    });
  }
};

class ModemOnDisconnectTrigger : public Trigger<> {
 public:
  explicit ModemOnDisconnectTrigger(ModemComponent *parent) {
    parent->add_on_state_callback([this, parent](ModemComponentState old_state, ModemComponentState state) {
      if (!parent->is_failed() && state == ModemComponentState::DISCONNECTED) {
        // only trigger if old_state is CONNECTED
        if (old_state == ModemComponentState::CONNECTED) {
          this->trigger();
        }
      }
    });
  }
};

class ModemOnStartPPPTrigger : public Trigger<> {
 public:
  explicit ModemOnStartPPPTrigger(ModemComponent *parent) {
    parent->add_on_state_callback([this, parent](ModemComponentState old_state, ModemComponentState state) {
      if (!parent->is_failed() && state == ModemComponentState::START_PPP) {
        this->trigger();
      }
    });
  }
};

}  // namespace modem
}  // namespace esphome
#endif  // USE_ESP_IDF
