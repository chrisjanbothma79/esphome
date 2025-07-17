#ifdef USE_ESP_IDF
#include "modem_component.h"
#include "helpers.h"

#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/defines.h"
#include "esphome/components/network/util.h"

#include <esp_netif.h>
#include <esp_netif_ppp.h>
#include <esp_event.h>
#include <driver/gpio.h>
#include <lwip/dns.h>

#include <cxx_include/esp_modem_dte.hpp>
#include <esp_modem_config.h>
#include <cxx_include/esp_modem_api.hpp>

#include <cstring>
#include <iostream>
#include <cmath>

#define ESPHL_ERROR_CHECK(err, message) \
  if ((err) != ESP_OK) { \
    ESP_LOGE(TAG, message ": (%d) %s", err, esp_err_to_name(err)); \
    this->mark_failed(); \
    return; \
  }

#define ESPMODEM_ERROR_CHECK(err, message) \
  if ((err) != command_result::OK) { \
    ESP_LOGE(TAG, message ": %s", command_result_to_string(err).c_str()); \
  }

namespace esphome {
namespace modem {

using namespace esp_modem;

static const char *const TAG = "modem";

ModemComponent *global_modem_component = nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

ModemComponent::ModemComponent() {
  assert(global_modem_component == nullptr);
  global_modem_component = this;
}

void ModemComponent::enable_debug() { esp_log_level_set("command_lib", ESP_LOG_VERBOSE); }

std::string ModemComponent::modem_network_status_string() {
  std::string cfun_str;
  if (this->internal_state_.cfun == 1) {
    cfun_str = "OK";
  } else {
    cfun_str = "NOK (" + std::to_string(this->internal_state_.cfun) + ")";
  }

  char buf[256];
  snprintf(buf, sizeof(buf),
           "Modem status: %s, attached: %s, radio function: %s, SIM: %s, type: %s, ber: %.0f%%, rssi: %.0fdB %s",
           this->internal_state_.modem_connected ? "Good" : "BAD",
           this->internal_state_.network_attached ? "Yes" : "NO", cfun_str.c_str(),
           this->internal_state_.sim_status.c_str(),
           network_system_mode_to_string(this->internal_state_.network_mode).c_str(), this->internal_state_.ber,
           this->internal_state_.rssi, get_signal_bars(this->internal_state_.rssi).c_str());

  std::string status_string(buf);
  return status_string;
}

AtCommandResult ModemComponent::send_at(const std::string &cmd, uint32_t timeout) {
  AtCommandResult at_command_result;
  at_command_result.success = false;
  at_command_result.esp_modem_command_result = command_result::TIMEOUT;
  if (this->dce) {
    at_command_result.esp_modem_command_result = this->dce->at(cmd, at_command_result.output, timeout);
    ESP_LOGVV(TAG, "Result for command %s: %s (status %s)", cmd.c_str(), at_command_result.c_str(),
              command_result_to_string(at_command_result.esp_modem_command_result).c_str());
  } else {
    ESP_LOGE(TAG, "Modem DCE not ready, cannot send AT command: %s", cmd.c_str());
    at_command_result.esp_modem_command_result = command_result::FAIL;
  }

  at_command_result.success = at_command_result.esp_modem_command_result == command_result::OK;
  return at_command_result;
}

bool ModemComponent::get_power_status() {
  if (this->status_pin_) {
    return this->status_pin_->digital_read();
  } else if (this->dce->sync() == command_result::OK) {
    return true;
  } else {
    ESP_LOGW(TAG, "No status pin, modem sync failed. Assuming powered on.");
    return true;
  }
}

void ModemComponent::enable() {
  ESP_LOGI(TAG, "Enabling modem");
  set_timeout("modem timeout", this->timeout_, [this]() { this->abort_("Modem was not able to connect (timeout)"); });
  this->enable_loop();
  if (this->status_pin_) {
    // Check status pin for power state.
    if (this->get_power_status()) {
      ESP_LOGV(TAG, "Modem already ON (status pin HIGH).");
      this->component_state_ = ModemComponentState::INIT_NETWORK;
      return;
    }
  }
  if (this->power_pin_) {
    this->component_state_ = ModemComponentState::POWERING_ON;
  } else {
    this->component_state_ = ModemComponentState::INIT_NETWORK;
  }
}

void ModemComponent::disable() {
  this->internal_state_.disable_wanted = true;
  this->component_state_ = ModemComponentState::DISABLING;
}

void ModemComponent::reset() {
  this->component_state_ = ModemComponentState::DISABLING;
  this->internal_state_.disable_wanted = false;
}

bool ModemComponent::get_signal_quality(float &rssi, float &ber) {
  rssi = NAN;
  ber = NAN;
  int modem_rssi = 99;
  int modem_ber = 99;
  if (this->dce && this->dce->sync() == command_result::OK &&
      (global_modem_component->dce->get_signal_quality(modem_rssi, modem_ber) == command_result::OK)) {
    if (modem_rssi != 99)
      rssi = -113.0f + (modem_rssi * 2);
    if (modem_ber != 99)
      ber = 0.1f * (modem_ber * modem_ber);
    return true;
  }
  return false;
}

network::IPAddresses ModemComponent::get_ip_addresses() {
  network::IPAddresses addresses;
  if (this->component_state_ == ModemComponentState::CONNECTED) {
    addresses[0] = network::IPAddress(&this->internal_state_.ip_info.ip);
  }
  return addresses;
}

std::string ModemComponent::get_use_address() const {
  // Not useful for a modem?
  if (this->use_address_.empty()) {
    return App.get_name() + ".local";
  }
  return this->use_address_;
}

void ModemComponent::setup() {
  ESP_LOGI(TAG, "Modem setup...");
  this->pref_ = global_preferences->make_preference<ModemRestoreState>(76007670UL);
  this->pref_.load(&this->modem_restore_state_);

  if (this->power_pin_) {
    this->power_pin_->setup();
    // If a power pin is configured, assume the modem is initially off.
    this->internal_state_.powered_on = false;
  } else {
    // If no power pin is configured, assume the modem is initially on.
    this->internal_state_.powered_on = true;
  }

  if (this->status_pin_) {
    this->status_pin_->setup();
    this->status_pin_->pin_mode(gpio::Flags::FLAG_INPUT | gpio::Flags::FLAG_PULLUP);
    // Check the status pin to determine the initial power state.
    this->internal_state_.powered_on = this->get_power_status();
  }

  ESP_LOGCONFIG(TAG, "Config Modem:");
  ESP_LOGCONFIG(TAG, "  Model     : %s", this->model_.c_str());
  ESP_LOGCONFIG(TAG, "  APN       : %s", this->apn_.c_str());
  ESP_LOGCONFIG(TAG, "  PIN code  : %s", (this->pin_code_.empty()) ? "No" : "Yes (not shown)");
  ESP_LOGCONFIG(TAG, "  Tx Pin    : GPIO%u", this->tx_pin_->get_pin());
  ESP_LOGCONFIG(TAG, "  Rx Pin    : GPIO%u", this->rx_pin_->get_pin());
  ESP_LOGCONFIG(TAG, "  Power pin : %s", (this->power_pin_) ? this->power_pin_->dump_summary().c_str() : "Not defined");
  if (this->status_pin_) {
    std::string current_status = this->get_power_status() ? "ON" : "OFF";
    ESP_LOGCONFIG(TAG, "  Status pin: %s (state: %s)", this->status_pin_->dump_summary().c_str(),
                  current_status.c_str());
  } else {
    ESP_LOGCONFIG(TAG, "  Status pin: None");
  }
  ESP_LOGCONFIG(TAG, "  Enabled   : %s", (this->component_state_ != ModemComponentState::DISABLED) ? "Yes" : "No");
  ESP_LOGCONFIG(TAG, "  Use CMUX  : %s", this->cmux_ ? "Yes" : "No");
  ESP_LOGCONFIG(TAG, "  Baud rate : %d", this->baud_rate_);

  if (CONFIG_ESP_TASK_WDT_TIMEOUT_S <= 10) {
    ESP_LOGW(TAG, "WDT timeout (%d s) may be too low for modem. Increase if WDT triggers.",
             CONFIG_ESP_TASK_WDT_TIMEOUT_S);
  }

  if (!this->internal_state_.powered_on) {
    // If modem is off, it starts at default baud (e.g., 115200) after boot.
    ESP_LOGD(TAG, "Modem off; using default baud rate.");
    this->internal_state_.current_baud_rate = 0;
    this->component_state_ = ModemComponentState::POWERING_ON;
  } else {
    ESP_LOGD(TAG, "Modem on; assuming warm reboot, using restored baud rate %d.", this->modem_restore_state_.baud_rate);
    this->internal_state_.current_baud_rate = this->modem_restore_state_.baud_rate;
    this->component_state_ = ModemComponentState::SYNCING;
  }

  ESP_LOGV(TAG, "PPP netif init.");
  esp_err_t err;
  err = esp_netif_init();
  ESPHL_ERROR_CHECK(err, "PPP netif init failed");
  err = esp_event_loop_create_default();
  ESPHL_ERROR_CHECK(err, "PPP event loop init failed");

  esp_netif_config_t netif_ppp_config = ESP_NETIF_DEFAULT_PPP();
  this->ppp_netif_ = esp_netif_new(&netif_ppp_config);
  assert(this->ppp_netif_);

  err = esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &ModemComponent::ip_event_handler, this);
  ESPHL_ERROR_CHECK(err, "IP event handler register failed");

  ESP_LOGV(TAG, "Setup complete.");
}

void ModemComponent::loop() {
  static ModemComponentState last_state = this->component_state_;

  if ((millis() < this->internal_state_.next_loop_millis)) {
    // Some commands require a delay.
    return;
  }

  switch (this->component_state_) {
    case ModemComponentState::DISABLED:
      this->handle_state_disabled_();
      break;
    case ModemComponentState::POWERING_ON:
      this->handle_state_powering_on_();
      break;
    case ModemComponentState::SYNCING:
      this->handle_state_syncing_();
      break;
    case ModemComponentState::INIT_NETWORK:
      this->handle_state_init_network_();
      break;
    case ModemComponentState::START_PPP:
      this->handle_state_start_ppp_();
      break;
    case ModemComponentState::WAIT_IP:
      this->handle_state_wait_ip_();
      break;
    case ModemComponentState::CONNECTED:
      this->handle_state_connected_();
      break;
    case ModemComponentState::DISCONNECTED:
      this->handle_state_disconnected_();
      break;
    case ModemComponentState::NOT_RESPONDING:
      this->handle_state_not_responding_();
      break;
    case ModemComponentState::DISABLING:
      this->handle_state_disabling_();
      break;
    case ModemComponentState::POWERING_OFF:
      this->handle_state_powering_off_();
      break;
  }

  if (this->component_state_ != last_state) {
    ESP_LOGV(TAG, "State change: %s -> %s", state_to_string(last_state).c_str(),
             state_to_string(this->component_state_).c_str());
    this->on_state_callback_.call(last_state, this->component_state_);

    last_state = this->component_state_;
  }
}

void ModemComponent::handle_state_disabled_() {
  // Just wait 'enable()'
  if (this->internal_state_.disable_wanted) {
    cancel_timeout("modem timeout");
    this->disable_loop();
  } else {
    // Disable state was temporary (reset wanted)
    this->enable();
  }
}

void ModemComponent::handle_state_powering_on_() {
  this->power_pin_->digital_write(false);
  delay(this->power_ton_);
  this->power_pin_->digital_write(true);
  uint32_t loop_delay = this->power_tonuart_ + 2000;  // Add delay for modem readiness.
  this->loop_delay_(loop_delay);                      // Delay next loop.
  ESP_LOGD(TAG, "Modem ON in %.1fs...", float(loop_delay) / 1000);

  this->component_state_ = ModemComponentState::SYNCING;
  this->internal_state_.powered_on = true;
}

void ModemComponent::handle_state_powering_off_() {
  delay(10);
  this->power_pin_->digital_write(false);
  delay(this->power_toff_);
  this->power_pin_->digital_write(true);
  this->loop_delay_(this->power_toffuart_);
  ESP_LOGD(TAG, "Modem should be OFF in %.1fs...", float(this->power_toffuart_) / 1000);

  this->component_state_ = ModemComponentState::DISABLED;
  this->internal_state_.powered_on = false;
  // When modem is back online, it will be at default baud rate.
  this->modem_restore_state_.baud_rate = 0;
  this->internal_state_.current_baud_rate = 0;
  this->pref_.save(&this->modem_restore_state_);
  this->dce.reset();
  this->dte_.reset();
}

void ModemComponent::handle_state_syncing_() {
  // Goal is to have modem synced at wanted baud rate

  // Create or recreate DTE and DCE using the guessed baud rate (0, ie default on cold boot, or last used on warm boot)
  this->modem_create_dte_dce_(this->internal_state_.current_baud_rate);

  ESP_LOGD(TAG, "Autodetecting modem mode...");
  App.feed_wdt();

  // Set the modem to AUTODETECT mode
  this->dce->set_mode(modem_mode::AUTODETECT);  // WARNING: A WDT may be triggered if the modem is off.

  if (this->dce->get_mode() == modem_mode::UNDEF && this->internal_state_.current_baud_rate != 0) {
    ESP_LOGW(TAG, "Autodetect failed. Retrying with default baud rate.");
    this->modem_create_dte_dce_(0);
    delay(100);  // NOLINT
    this->dce->set_mode(modem_mode::AUTODETECT);
  }

  switch (this->dce->get_mode()) {
    case modem_mode::UNDEF:
      ESP_LOGW(TAG, "Modem mode autodetect failed. ");
      if (this->dce->sync() != command_result::OK) {
        ESP_LOGW(TAG, "Trying to force command mode");
        this->dce->set_mode(modem_mode::COMMAND_MODE);
      }
      break;
    case modem_mode::COMMAND_MODE:
      ESP_LOGV(TAG, "Modem in COMMAND_MODE.");
      break;
    case modem_mode::DATA_MODE:
      ESP_LOGV(TAG, "Modem in DATA_MODE (previous session?). Switching to command mode.");
      this->dce->set_mode(modem_mode::COMMAND_MODE);
      break;
    case modem_mode::CMUX_MANUAL_MODE:
      ESP_LOGV(TAG, "Modem in CMUX_MANUAL_MODE (previous session?). Switching to command mode.");
      this->dce->set_mode(modem_mode::CMUX_MANUAL_EXIT);
      this->dce->set_mode(modem_mode::CMUX_MANUAL_COMMAND);

      break;
    default:
      ESP_LOGW(TAG, "Modem in unhandled mode: %d (see esp_modem_types.hpp enum modem_mode).",
               static_cast<int>(this->dce->get_mode()));
  }

  delay(100);  // NOLINT
  if (this->dce->sync() != command_result::OK) {
    ESP_LOGE(TAG, "Unable to sync modem");
    this->component_state_ = ModemComponentState::NOT_RESPONDING;
    return;
  }

  // Change baud rate if needed.
  if (this->baud_rate_ != this->internal_state_.current_baud_rate) {
    ESP_LOGD(TAG, "Setting baud rate: %d -> %d", this->internal_state_.current_baud_rate, this->baud_rate_);
    this->flush_uart_();
    if (this->dce->set_baud(this->baud_rate_) == command_result::OK) {
      ESP_LOGD(TAG, "Modem baud rate set to %d.", this->baud_rate_);
      delay(200);  // NOLINT
      // Recreate DTE/DCE with new baud rate.
      this->modem_create_dte_dce_(this->baud_rate_);
      App.feed_wdt();
      delay(200);  // NOLINT
      this->flush_uart_();
      if (this->dce->sync() == command_result::OK) {
        ESP_LOGI(TAG, "Modem synced at baud rate %d.", this->internal_state_.current_baud_rate);
        this->modem_restore_state_.baud_rate = this->internal_state_.current_baud_rate;
        this->pref_.save(&this->modem_restore_state_);
        // Save state: modem only reachable at this baud rate if not powered off.
        global_preferences->sync();

      } else {
        ESP_LOGE(TAG, "Failed to sync modem at baud rate %d.", this->baud_rate_);
        this->component_state_ = ModemComponentState::NOT_RESPONDING;
      }
    } else {
      ESP_LOGW(TAG, "Failed to set modem baud rate to %d. Using %d.", this->baud_rate_,
               this->internal_state_.current_baud_rate);
      this->loop_delay_(1000);
      return;  // still syncing state
    }
  }

  if (this->dce->sync() == command_result::OK) {
    ESP_LOGD(TAG, "Modem synced");
    this->send_init_at_();
    this->component_state_ = ModemComponentState::INIT_NETWORK;
  }
}

void ModemComponent::handle_state_init_network_() {
  // When leaving this state, the modem will be internally attached to netword, and ready to connect

  if (!this->dce || (this->dce->sync() != command_result::OK)) {
    ESP_LOGW(TAG, "Modem not synced during network init");
    this->component_state_ = ModemComponentState::SYNCING;
    return;
  }

  if (this->cmux_) {
    // Be sure no stale cmux term
    this->dce->set_mode(modem_mode::CMUX_MANUAL_EXIT);
  }

  this->update_network_state_();
  ESP_LOGI(TAG, "%s", this->modem_network_status_string().c_str());

  if (this->internal_state_.cfun != 1) {
    ESP_LOGD(TAG, "Enabling modem full functionality");
    this->dce->set_radio_state(1);
    this->loop_delay_(200);
    return;
  }

  if (this->internal_state_.sim_status.find("READY") == std::string::npos) {
    this->prepare_sim_();
    this->loop_delay_(1000);  // Need some delay before able to respond
    return;
  }

  if (!this->internal_state_.network_attached) {
    this->dce->set_network_attachment_state(1);
    this->loop_delay_(200);
    return;
  }

  this->update_network_state_();
  if (this->internal_state_.modem_connected) {
    this->component_state_ = ModemComponentState::START_PPP;
    ESP_LOGI(TAG, "Modem initialized and ready");
  } else {
    ESP_LOGE(TAG, "Modem not ready to connect");
    this->loop_delay_(1000);
  }
}

void ModemComponent::handle_state_start_ppp_() {
  // In START_PPP state, we attempt to connect.
  this->update_network_state_();
  ESP_LOGI(TAG, "%s", this->modem_network_status_string().c_str());
  if (!this->internal_state_.modem_connected) {
    // need to go back to initialize, to get modem connected
    this->component_state_ = ModemComponentState::INIT_NETWORK;
    this->loop_delay_(1000);
    return;
  }

  this->status_set_warning("Starting connection");

  ESP_LOGI(TAG, "%s", this->modem_network_status_string().c_str());

  bool status = false;
  if (cmux_) {
    status = this->dce->set_mode(modem_mode::CMUX_MODE);
    // Note: Do not try to check if the modem is synced with 'this->dce->sync()' now; it will fail on some modems.
  } else {
    status = this->dce->set_mode(modem_mode::DATA_MODE);
  }

  if (!status) {
    ESP_LOGE(TAG, "Failed to enter PPP");
    this->component_state_ = ModemComponentState::SYNCING;
    this->loop_delay_(1000);
  } else {
    this->component_state_ = ModemComponentState::WAIT_IP;
  }
}

void ModemComponent::handle_state_wait_ip_() {
  static uint8_t retry = 10;
  // In WAIT_IP state, we wait for IP_EVENT_PPP_GOT_IP.
  if (this->internal_state_.got_ip) {
    this->component_state_ = ModemComponentState::CONNECTED;
    this->status_clear_warning();
    retry = 10;
    return;
  } else {
    if (retry-- > 0) {
      ESP_LOGD(TAG, "Wait IP left retry: %d", retry);
      this->loop_delay_(this->connect_retry_delay_);
    } else {
      ESP_LOGE(TAG, "Unable to get IP address");
      retry = 10;
      this->component_state_ = ModemComponentState::SYNCING;
    }
  }
  // if (millis() - this->internal_state_.connect_begin > this->connect_timeout_) {
  //   // Connecting timeout
  //   ESP_LOGW(TAG, "Modem connection failed! Reconnecting...");
  //   this->component_state_ = ModemComponentState::START_PPP;
  //   this->loop_delay_(this->connect_retry_delay_);
  // } else {
  //   // Wait until IP_EVENT_PPP_GOT_IP.
  //   this->loop_delay_(1000);
  // }
}

void ModemComponent::handle_state_connected_() {
  cancel_timeout("modem timeout");
  if (!this->internal_state_.got_ip) {
    ESP_LOGW(TAG, "Lost IP");
    this->component_state_ = ModemComponentState::DISCONNECTED;
    this->loop_delay_(this->connect_retry_delay_);
    return;
  }
  // If CMUX, we can log status
  if (this->cmux_) {
    if ((millis() - this->internal_state_.last_health_check) > 30000) {
      this->internal_state_.last_health_check = millis();
      this->update_network_state_();
      ESP_LOGI(TAG, "%s", this->modem_network_status_string().c_str());
      if (!this->internal_state_.modem_connected) {
        this->component_state_ = ModemComponentState::DISCONNECTED;
      }
    }
    this->loop_delay_(2000);
  }
}

void ModemComponent::handle_state_disconnected_() {
  if (!this->dce || (this->dce->sync() != command_result::OK)) {
    ESP_LOGD(TAG, "Disconnected and not responding");
    this->component_state_ = ModemComponentState::NOT_RESPONDING;
  } else {
    ESP_LOGW(TAG, "Disconnected. Attempting to reconnect");
    this->component_state_ = ModemComponentState::START_PPP;
  }
}

void ModemComponent::handle_state_not_responding_() {
  // In NOT_RESPONDING state, we attempt recovery.
  if (this->status_pin_ && !this->get_power_status()) {
    ESP_LOGD(TAG, "Modem off, powering on");
    this->component_state_ = ModemComponentState::POWERING_ON;
  } else {
    ESP_LOGW(TAG, "Modem not responding, attempting a reset");
    this->reset();
  }
}

void ModemComponent::handle_state_disabling_() {
  ESP_LOGI(TAG, "Disabling modem");
  if (this->power_pin_) {
    this->component_state_ = ModemComponentState::POWERING_OFF;
  } else {
    // This will definitely power off the modem!
    // this->send_at("AT+CPOF");
    if (this->dce->get_mode() != modem_mode::COMMAND_MODE) {
      this->dce->set_mode(modem_mode::COMMAND_MODE);
    }
    if (this->dce->set_radio_state(0) == command_result::OK) {
      ESP_LOGI(TAG, "No power pin. Modem set to minimal functionality.");
    } else {
      ESP_LOGE(TAG, "Failed to set modem to minimal functionality.");
    }
    if (this->internal_state_.disable_wanted) {
      this->component_state_ = ModemComponentState::DISABLED;
    } else {
      // Reset wanted, so reenable
      this->enable();
      this->internal_state_.disable_wanted = true;
    }
  }
  this->dce.reset();
  this->dte_.reset();
  this->loop_delay_(this->command_delay_);
}

void ModemComponent::modem_create_dte_dce_(int baud_rate) {
  // Create or recreate DTE and DCE.
  // No communication is done with the modem.

  this->internal_state_.current_baud_rate = baud_rate;

  esp_modem_dte_config_t dte_config = ESP_MODEM_DTE_DEFAULT_CONFIG();

  dte_config.uart_config.tx_io_num = this->tx_pin_->get_pin();
  dte_config.uart_config.rx_io_num = this->rx_pin_->get_pin();
  dte_config.uart_config.rx_buffer_size = this->uart_rx_buffer_size_;
  dte_config.uart_config.tx_buffer_size = this->uart_tx_buffer_size_;
  dte_config.uart_config.event_queue_size = this->uart_event_queue_size_;
  if (baud_rate != 0) {
    ESP_LOGD(TAG, "DTE baud rate: %d", baud_rate);
    dte_config.uart_config.baud_rate = baud_rate;
  }

  dte_config.task_stack_size = this->uart_event_task_stack_size_;
  dte_config.task_priority = this->uart_event_task_priority_;
  dte_config.dte_buffer_size = this->uart_rx_buffer_size_ / 2;

  this->dce.reset();
  this->dte_.reset();
  this->dte_ = create_uart_dte(&dte_config);

  esp_modem_dce_config_t dce_config = ESP_MODEM_DCE_DEFAULT_CONFIG(this->apn_.c_str());

  if (this->model_ == "GENERIC") {
    this->dce = create_generic_dce(&dce_config, this->dte_, this->ppp_netif_);
  } else if (this->model_ == "BG96") {
    this->dce = create_BG96_dce(&dce_config, this->dte_, this->ppp_netif_);
  } else if (this->model_ == "SIM800") {
    this->dce = create_SIM800_dce(&dce_config, this->dte_, this->ppp_netif_);
  } else if (this->model_ == "SIM7000") {
    this->dce = create_SIM7000_dce(&dce_config, this->dte_, this->ppp_netif_);
  } else if (this->model_ == "SIM7600" || this->model_ == "SIM7670") {
    this->dce = create_SIM7600_dce(&dce_config, this->dte_, this->ppp_netif_);
  } else {
    ESP_LOGE(TAG, "Invalid model %s. DCE not created.", this->model_.c_str());
    return;
  }

  // Flow control is not fully implemented but is kept here for future work.
  // if (dte_config.uart_config.flow_control == ESP_MODEM_FLOW_CONTROL_HW) {
  //   if (command_result::OK != this->dce->set_flow_control(2, 2)) {
  //     ESP_LOGE(TAG, "Failed to set the set_flow_control mode");
  //     return;
  //   }
  //   ESP_LOGD(TAG, "set_flow_control OK");
  // }

  ESP_LOGV(TAG, "DTE/DCE created.");
}

bool ModemComponent::prepare_sim_() {
  // Radio state (ie CFUN=1) must be enabled before trying to unlock the sim

  // this->dce->read_pin(pin_ok) // Not used, because we can't know the cause of the error.
  App.feed_wdt();
  AtCommandResult result = this->send_at("AT+CPIN?");
  if (!result.success) {
    ESP_LOGW(TAG, "Failed to check pin");
    return false;
  }

  std::string sim_status = result.output.starts_with("+CPIN: ") ? result.output.substr(7) : result.output;
  ESP_LOGD(TAG, "SIM: %s", sim_status.c_str());

  if (sim_status.find("READY") != std::string::npos) {
    return true;  // Pin not needed or already unlocked.
  }

  if (this->pin_code_.empty()) {
    ESP_LOGE(TAG, "SIM PIN empty, but SIM locked.");
    return false;
  }

  // We need to unlock the SIM.
  ESP_LOGD(TAG, "Unlocking SIM with PIN...");
  if (this->dce->set_pin(this->pin_code_) == command_result::OK) {
    ESP_LOGD(TAG, "PIN set. (But not yet checked).");
    return true;
  } else {
    ESP_LOGE(TAG, "Failed to set PIN.");
    return false;  // Failed to set pin code.
  }

  return false;
}

void ModemComponent::send_init_at_() {
  // Send initial AT commands from YAML.
  for (const auto &cmd : this->init_at_commands_) {
    App.feed_wdt();
    this->flush_uart_();
    AtCommandResult result = this->send_at(cmd);
    if (result.success) {
      ESP_LOGI(TAG, "init_at %s: %s", cmd.c_str(), result.output.c_str());
    } else {
      ESP_LOGW(TAG, "init_at %s: %s", cmd.c_str(), command_result_to_string(result.esp_modem_command_result).c_str());
    }
    delay(200);  // NOLINT
  }
  this->flush_uart_();
}

void ModemComponent::update_network_state_() {
  // On command error, state will be unchanged

  if (this->dce && (this->dce->sync() == command_result::OK)) {
    AtCommandResult sim_status = this->send_at("AT+CPIN?");
    if (sim_status) {
      this->internal_state_.sim_status =
          sim_status.output.starts_with("+CPIN: ") ? sim_status.output.substr(7) : sim_status.output;
    } else {
      ESP_LOGE(TAG, "Unable to check pin: %s", command_result_to_string(sim_status.esp_modem_command_result).c_str());
    }
    delay(200);  // NOLINT

    ESPMODEM_ERROR_CHECK(this->dce->get_radio_state(this->internal_state_.cfun), "get_radio_state");
    ESPMODEM_ERROR_CHECK(this->dce->get_network_attachment_state(this->internal_state_.network_attached),
                         "get_network_attachment_state");
    this->get_signal_quality(this->internal_state_.rssi, this->internal_state_.ber);

    ESPMODEM_ERROR_CHECK(this->dce->get_network_system_mode(this->internal_state_.network_mode),
                         "get_network_system_mode");
  } else {
    ESP_LOGW(TAG, "Modem not synced, some network states might be incorrect");
    return;
  }

  this->internal_state_.modem_connected =
      (this->internal_state_.network_mode != 0) && (!std::isnan(this->internal_state_.rssi)) &&
      this->internal_state_.network_attached && this->internal_state_.sim_status.find("READY") != std::string::npos;
}

void ModemComponent::ip_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
  auto *self = static_cast<ModemComponent *>(arg);

  switch (event_id) {
    case IP_EVENT_PPP_GOT_IP: {
      ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
      ESP_LOGD(TAG, "IP event: Got IP " IPSTR, IP2STR(&event->ip_info.ip));
      self->internal_state_.ip_info = event->ip_info;
      esp_netif_get_dns_info(event->esp_netif, ESP_NETIF_DNS_MAIN, &self->internal_state_.dns_main);
      esp_netif_get_dns_info(event->esp_netif, ESP_NETIF_DNS_BACKUP, &self->internal_state_.dns_backup);
      self->internal_state_.got_ip = true;
      break;
    }
    case IP_EVENT_PPP_LOST_IP:
      if (self->component_state_ == ModemComponentState::CONNECTED) {
        // Only log if previously connected.
        ESP_LOGD(TAG, "IP event: Lost IP.");
      }
      self->internal_state_.got_ip = false;
      break;
  }
}

void ModemComponent::abort_(const std::string &message) {
  ESP_LOGE(TAG, "Aborting: %s.", message.c_str());
  this->pref_.save(&this->modem_restore_state_);
  App.reboot();
}

void ModemComponent::loop_delay_(uint32_t delay_ms) { this->internal_state_.next_loop_millis = millis() + delay_ms; }

void ModemComponent::dump_connect_params_() {
  if (this->component_state_ != ModemComponentState::CONNECTED) {
    ESP_LOGCONFIG(TAG, "Modem connection: Not connected.");
    return;
  }
  esp_netif_ip_info_t ip = this->internal_state_.ip_info;
  esp_netif_dns_info_t dns_main = this->internal_state_.dns_main;
  esp_netif_dns_info_t dns_backup = this->internal_state_.dns_backup;

  ESP_LOGCONFIG(TAG, "Modem connection:");
  ESP_LOGCONFIG(TAG, "  IP Address  : %s", network::IPAddress(&ip.ip).str().c_str());
  ESP_LOGCONFIG(TAG, "  Hostname    : '%s'", App.get_name().c_str());
  ESP_LOGCONFIG(TAG, "  Subnet      : %s", network::IPAddress(&ip.netmask).str().c_str());
  ESP_LOGCONFIG(TAG, "  Gateway     : %s", network::IPAddress(&ip.gw).str().c_str());
  ESP_LOGCONFIG(TAG, "  DNS main    : %s", network::IPAddress(&dns_main.ip.u_addr.ip4).str().c_str());
  ESP_LOGCONFIG(TAG, "  DNS backup  : %s", network::IPAddress(&dns_backup.ip.u_addr.ip4).str().c_str());
}

std::string ModemComponent::flush_uart_(uint32_t timeout) {
  // Empty command that just reads the result to flush the UART.
  size_t cleaned = 0;
  std::string output;
  this->dce->command(
      "",
      [&](uint8_t *data, size_t len) {
        cleaned = len;
        output.assign(reinterpret_cast<char *>(data), len);
        return command_result::OK;
      },
      timeout);

  if (cleaned != 0) {
    ESP_LOGV(TAG, "Flushed %d bytes from modem buffer: %s", cleaned, output.c_str());
  }
  return output;
}

}  // namespace modem
}  // namespace esphome

#endif
