#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/components/ota_base/ota_backend.h"

#ifdef USE_OTA_STATE_CALLBACK
#include "esphome/core/automation.h"
#endif

namespace esphome {
namespace ota {

// Import types from ota_base namespace for backward compatibility
using ota_base::OTABackend;
using ota_base::OTAResponseTypes;
using ota_base::OTAState;

class OTAComponent : public Component {
#ifdef USE_OTA_STATE_CALLBACK
 public:
  void add_on_state_callback(std::function<void(ota_base::OTAState, float, uint8_t)> &&callback) {
    this->state_callback_.add(std::move(callback));
  }

 protected:
  CallbackManager<void(ota_base::OTAState, float, uint8_t)> state_callback_{};
#endif
};

#ifdef USE_OTA_STATE_CALLBACK
class OTAGlobalCallback {
 public:
  void register_ota(OTAComponent *ota_caller) {
    ota_caller->add_on_state_callback([this, ota_caller](ota_base::OTAState state, float progress, uint8_t error) {
      this->state_callback_.call(state, progress, error, ota_caller);
    });
  }
  void add_on_state_callback(std::function<void(ota_base::OTAState, float, uint8_t, OTAComponent *)> &&callback) {
    this->state_callback_.add(std::move(callback));
  }

 protected:
  CallbackManager<void(ota_base::OTAState, float, uint8_t, OTAComponent *)> state_callback_{};
};

OTAGlobalCallback *get_global_ota_callback();
void register_ota_platform(OTAComponent *ota_caller);
#endif

}  // namespace ota
}  // namespace esphome
