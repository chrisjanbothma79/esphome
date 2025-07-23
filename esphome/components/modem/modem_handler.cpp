// This file is just a stub for the ModemHandler class.
// It will be overridden by future merge of #9807
#ifdef USE_ESP_IDF

#include "modem_handler.h"
#include <cmath>

namespace esphome {
namespace modem {

static const char *const TAG = "modem_handler";

void ModemHandler::modem_create_dte_dce(int baud_rate) {}

void ModemHandler::enable_debug() {}

AtCommandResult ModemHandler::send_at(const std::string &cmd, uint32_t timeout, bool verbose) {
  return AtCommandResult{};
}

bool ModemHandler::get_power_status() { return false; }

bool ModemHandler::get_signal_quality(float &out_rssi, float &out_ber) {
  out_rssi = NAN;
  out_ber = NAN;
  return false;
}

void ModemHandler::ip_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {}

std::string ModemHandler::modem_network_status_string() { return {}; }

void ModemHandler::send_init_at() {}

void ModemHandler::update_network_state() {}

bool ModemHandler::prepare_sim() { return false; }

std::string ModemHandler::flush_uart(uint32_t timeout) { return {}; }

}  // namespace modem
}  // namespace esphome

#endif
