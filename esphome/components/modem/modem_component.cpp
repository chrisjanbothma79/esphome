// This file is just a stub for the ModemComponent class.
// It will be overridden by future merge of #9807

#ifdef USE_ESP_IDF

#include "modem_component.h"
#include "modem_handler.h"
#include "esphome/core/log.h"

namespace esphome {
namespace modem {

static const char *const TAG = "modem";

ModemComponent *global_modem_component = nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

ModemComponent::ModemComponent() {
  ESP_LOGE(TAG, "Not impelmented");
  global_modem_component = this;
  this->modem_handler = std::make_unique<ModemHandler>();
}

AtCommandResult ModemComponent::send_at(const std::string &cmd, uint32_t timeout, bool verbose) {
  return AtCommandResult{};
}

void ModemComponent::enable() {}

void ModemComponent::disable() {}

void ModemComponent::reset() {}

network::IPAddresses ModemComponent::get_ip_addresses() { return network::IPAddresses{}; }

std::string ModemComponent::get_use_address() const { return {}; }

void ModemComponent::setup() {}

void ModemComponent::loop() {}

void ModemComponent::handle_state_powering_on_() {}

void ModemComponent::handle_state_syncing_() {}

void ModemComponent::handle_state_init_network_() {}

void ModemComponent::handle_state_start_ppp_() {}

void ModemComponent::handle_state_wait_ip_() {}

void ModemComponent::handle_state_connected_() {}

void ModemComponent::handle_state_disconnected_() {}

void ModemComponent::handle_state_not_responding_() {}

void ModemComponent::handle_state_disabling_() {}

void ModemComponent::handle_state_disabled_() {}

void ModemComponent::handle_state_powering_off_() {}

void ModemComponent::abort_(const std::string &message) {}

void ModemComponent::loop_delay_(uint32_t delay_ms) {}

void ModemComponent::dump_connect_params_() {}

}  // namespace modem
}  // namespace esphome

#endif
