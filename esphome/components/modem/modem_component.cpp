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

bool ModemComponent::is_modem_connected(bool verbose) {
  float rssi, ber;
  int network_mode = 0;
  if (!this->dce || this->dce->sync() != command_result::OK) {
    ESP_LOGE(TAG, "Modem DCE not ready, cannot check connection.");
    return false;
  }
  bool network_attached = this->is_network_attached_();
  this->get_signal_quality(rssi, ber);
  this->dce->get_network_system_mode(network_mode);

  bool connected = (network_mode != 0) && (!std::isnan(rssi)) && network_attached;

  if (verbose) {
    ESP_LOGI(TAG, "Modem status: %s (attached: %s, type: %s, IP: %s, rssi: %.0fdB %s, ber: %.0f%%)",
             connected ? "Good" : "BAD", network_attached ? "Yes" : "NO",
             network_system_mode_to_string(network_mode).c_str(), this->get_modem_ip().c_str(), rssi,
             get_signal_bars(rssi).c_str(), ber);
  }
  return connected;
}

AtCommandResult ModemComponent::send_at(const std::string &cmd, uint32_t timeout) {
  AtCommandResult at_command_result;
  at_command_result.success = false;
  at_command_result.esp_modem_command_result = command_result::TIMEOUT;
  if (this->dce) {
    at_command_result.esp_modem_command_result = this->dce->at(cmd, at_command_result.output, timeout);
    ESP_LOGV(TAG, "Result for command %s: %s (status %s)", cmd.c_str(), at_command_result.c_str(),
             command_result_to_string(at_command_result.esp_modem_command_result).c_str());
  } else {
    ESP_LOGE(TAG, "Modem DCE not ready, cannot send AT command: %s", cmd.c_str());
    at_command_result.esp_modem_command_result = command_result::FAIL;
  }

  at_command_result.success = at_command_result.esp_modem_command_result == command_result::OK;
  return at_command_result;
}

AtCommandResult ModemComponent::get_modem_ip() {
  // Get the IP address assigned to the modem (not the PPP interface).
  AtCommandResult res = this->send_at("AT+CGPADDR", this->command_delay_);
  if (!res.success)
    return res;
  auto start = res.output.find(',');
  if (start != std::string::npos) {
    res.output = res.output.substr(start + 1);
    res.success = !res.output.empty();
  } else {
    res.success = false;
    res.output.clear();
  }
  return res;
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
  if (this->component_state_ == ModemComponentState::DISABLED) {
    this->component_state_ = ModemComponentState::DISCONNECTED;
  }
  this->internal_state_.enabled = true;
}

void ModemComponent::disable() {
  ESP_LOGI(TAG, "Disabling modem");
  this->internal_state_.enabled = false;
  this->internal_state_.starting = false;
  if (this->component_state_ != ModemComponentState::CONNECTED) {
    this->component_state_ = ModemComponentState::DISCONNECTED;
  }
  this->poweroff_();
}

void ModemComponent::reconnect() {
  if (!this->internal_state_.reconnect) {
    this->internal_state_.reconnect = true;
    this->internal_state_.connected = false;
    this->component_state_ = ModemComponentState::DISCONNECTED;
    // If reconnect fails, wait before retrying.
    set_timeout("retry_reconnect", this->reconnect_grace_period_,
                [this]() { this->internal_state_.reconnect = false; });
  } else {
    ESP_LOGD(TAG, "Reconnect in progress.");
  }
}

bool ModemComponent::get_signal_quality(float &rssi, float &ber) {
  rssi = NAN;
  ber = NAN;
  int modem_rssi = 99;
  int modem_ber = 99;
  if (this->dce && this->dce->sync() == command_result::OK &&
      (global_modem_component->dce->get_signal_quality(modem_rssi, modem_ber) == command_result::OK)) {
    if (modem_rssi != 99)
      rssi = -113 + (modem_rssi * 2);
    if (modem_ber != 99)
      ber = 0.1f * (modem_ber * modem_ber);
    return true;
  }
  return false;
}

network::IPAddresses ModemComponent::get_ip_addresses() {
  network::IPAddresses addresses;
  esp_netif_ip_info_t ip;
  esp_netif_get_ip_info(this->ppp_netif_, &ip);
  addresses[0] = network::IPAddress(&ip.ip);
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
  ESP_LOGCONFIG(TAG, "  Enabled   : %s", this->internal_state_.enabled ? "Yes" : "No");
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
  } else {
    ESP_LOGD(TAG, "Modem on; assuming warm reboot, using restored baud rate %d.", this->modem_restore_state_.baud_rate);
    this->internal_state_.current_baud_rate = this->modem_restore_state_.baud_rate;
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

  err = esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &ModemComponent::ip_event_handler, nullptr);
  ESPHL_ERROR_CHECK(err, "IP event handler register failed");

  ESP_LOGV(TAG, "Setup complete.");
}

void ModemComponent::loop() {
  static ModemComponentState last_state = this->component_state_;
  static uint32_t next_loop_millis = millis();
  static uint32_t last_health_check = millis();
  static bool connecting = false;
  uint32_t loop_delay;

  if ((millis() < next_loop_millis)) {
    // Some commands require a delay.
    return;
  }

  if (this->internal_state_.power_transition) {
    // A power state is used to handle long tonuart/toffuart delays.
    switch (this->internal_state_.power_state) {
      case ModemPowerState::TON:
        this->power_pin_->digital_write(false);
        delay(this->power_ton_);
        this->power_pin_->digital_write(true);
        loop_delay = this->power_tonuart_ + 2000;  // Add delay for modem readiness.
        next_loop_millis = millis() + loop_delay;  // Delay next loop.
        this->internal_state_.power_state = ModemPowerState::TONUART;
        ESP_LOGD(TAG, "Modem ON in %.1fs...", float(loop_delay) / 1000);
        break;
      case ModemPowerState::TONUART:
        this->component_state_ = ModemComponentState::DISCONNECTED;
        this->internal_state_.powered_on = true;
        this->internal_state_.power_transition = false;
        break;
      case ModemPowerState::TOFF:
        delay(10);
        this->power_pin_->digital_write(false);
        delay(this->power_toff_);
        this->power_pin_->digital_write(true);
        this->internal_state_.power_state = ModemPowerState::TOFFUART;
        ESP_LOGD(TAG, "Modem should be OFF in %.1fs...", float(this->power_toffuart_) / 1000);
        next_loop_millis = millis() + this->power_toffuart_;  // Delay the next loop.
        break;
      case ModemPowerState::TOFFUART:
        this->internal_state_.power_transition = false;
        if (!this->get_power_status()) {
          ESP_LOGI(TAG, "Modem powered off.");
          this->component_state_ = ModemComponentState::DISABLED;
          this->internal_state_.powered_on = false;
          this->internal_state_.sim_unlocked = false;
          // When modem is back online, it will be at default baud rate.
          this->modem_restore_state_.baud_rate = 0;
          this->internal_state_.current_baud_rate = 0;
          this->pref_.save(&this->modem_restore_state_);
        } else {
          ESP_LOGW(TAG, "Modem power off failed.");
        }
        break;
    }
    App.feed_wdt();
    yield();
    return;
  }

  ESP_LOGVV(TAG, "Modem loop (state: %s)", state_to_string(this->component_state_).c_str());

  switch (this->component_state_) {
    case ModemComponentState::NOT_RESPONDING:
      if (this->internal_state_.starting) {
        if (this->power_pin_ && !this->internal_state_.powered_on && !this->internal_state_.power_transition) {
          this->component_state_ = ModemComponentState::DISCONNECTED;
        } else {
          ESP_LOGW(TAG, "Modem not responding. Resetting...");
          this->internal_state_.connected = false;
          if (!this->modem_init_()) {
            ESP_LOGE(TAG, "Modem recovery failed.");
          } else {
            this->component_state_ = ModemComponentState::DISCONNECTED;
          }
        }
      }
      break;

    case ModemComponentState::DISCONNECTED:
      if (this->internal_state_.enabled) {
        // Ensure the modem is on and synced.
        if (!this->internal_state_.powered_on) {
          this->poweron_();
          break;
        } else if (!this->dce) {
          if (!this->modem_init_()) {
            this->component_state_ = ModemComponentState::NOT_RESPONDING;
          }
        }

        if (this->internal_state_.starting) {
          float time_left_s = float(this->timeout_ - (millis() - this->internal_state_.startms)) / 1000;
          // Attempt to connect.
          if ((millis() - this->internal_state_.startms) > this->timeout_) {
            this->poweroff_();  // Power off the modem to reset it.
            this->abort_("Timeout while trying to connect");
          }
          if (!connecting) {
            if (!this->internal_state_.sim_unlocked) {
              if (this->dce->read_pin(this->internal_state_.sim_unlocked) != command_result::OK) {
                ESP_LOGW(TAG, "SIM card not ready, will retry later");
                next_loop_millis = millis() + 5000;  // delay to retry
              } else {
                if (!this->internal_state_.sim_unlocked) {
                  this->abort_("Invalid SIM PIN");
                } else {
                  ESP_LOGD(TAG, "SIM card ready");
                }
              }
              if (this->prepare_sim_()) {
                this->internal_state_.sim_unlocked = true;
              } else {
                ESP_LOGE(TAG, "SIM not ready. Aborting connection.");
                this->abort_("SIM error");
              }
            }
            // Wait for the modem to attach to a network, start PPP, and set connecting=true.
            if (this->is_modem_connected()) {
              if (this->start_ppp_()) {
                connecting = true;
              } else {
                ESP_LOGE(TAG, "Modem failed to enter PPP (abort in %.0fs).", time_left_s);
                // this->dce->set_mode(modem_mode::CMUX_MANUAL_COMMAND);
                this->dce->set_mode(modem_mode::COMMAND_MODE);             // Force command mode.
                next_loop_millis = millis() + this->connect_retry_delay_;  // Delay before retrying.
              }
            } else {
              ESP_LOGW(TAG, "Waiting for modem network attach (abort in %.0fs).", time_left_s);
              next_loop_millis = millis() + this->connect_retry_delay_;  // Delay before retrying.
            }
          } else {
            // Connecting
            if (!this->internal_state_.connected) {
              // Wait until this->internal_state_.connected is set to true by IP_EVENT_PPP_GOT_IP.
              next_loop_millis = millis() + 1000;  // Delay the next loop.

              // Connecting timeout
              if (millis() - this->internal_state_.connect_begin > this->connect_timeout_) {
                ESP_LOGW(TAG, "Modem connection failed! Reconnecting...");
                this->dce->set_mode(modem_mode::CMUX_MANUAL_COMMAND);
                connecting = false;
              }
            } else {
              connecting = false;
              ESP_LOGI(TAG, "ESP connected to network via modem.");
              this->component_state_ = ModemComponentState::CONNECTED;
              this->dump_connect_params_();
              this->status_clear_warning();
            }
          }
        } else {
          this->internal_state_.starting = true;
          this->internal_state_.startms = millis();
        }
      } else {
        this->component_state_ = ModemComponentState::DISABLED;
      }
      break;

    case ModemComponentState::CONNECTED:
      this->internal_state_.starting = false;
      if (this->internal_state_.enabled) {
        if (!this->internal_state_.connected) {
          this->status_set_warning("Modem not connected");
          this->component_state_ = ModemComponentState::DISCONNECTED;
          break;
        }

        if ((millis() - last_health_check) > 35000) {
          if (this->cmux_) {
            // Health check only available in CMUX mode.
            last_health_check = millis();
            if (!this->is_modem_connected()) {
              ESP_LOGW(TAG, "Reconnecting modem...");
              this->reconnect();
            }
          }
        }
        next_loop_millis = millis() + 2000;  // Slow down the next loop.
      } else {
        if (this->internal_state_.connected) {
          // Connected but disabled, so disconnect.
          // this->dce->set_mode(modem_mode::CMUX_MANUAL_COMMAND);  // FIXME: COMMAND_MODE?
          this->dce->set_mode(modem_mode::COMMAND_MODE);
          this->component_state_ = ModemComponentState::DISCONNECTED;
        }
      }
      break;

    case ModemComponentState::DISABLED:
      if (this->internal_state_.enabled) {
        this->component_state_ = ModemComponentState::DISCONNECTED;
      }
      next_loop_millis = millis() + 2000;  // Slow down the next loop.
      break;
  }

  if (this->component_state_ != last_state) {
    ESP_LOGV(TAG, "State change: %s -> %s", state_to_string(last_state).c_str(),
             state_to_string(this->component_state_).c_str());
    this->on_state_callback_.call(last_state, this->component_state_);

    last_state = this->component_state_;
  }
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

  // if (!this->dte_->set_mode(modem_mode::COMMAND_MODE)) {
  //   ESP_LOGW(TAG, "Unable to set DTE to command mode.");
  // }
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
    ESP_LOGE(TAG, "Invalid model %s", this->model_.c_str());
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

bool ModemComponent::modem_init_() {
  // Get command mode, check SIM, and send init_at commands.
  // May reboot the modem if it is unresponsive.

  bool success = false;

  uint32_t start_ms = millis();
  uint32_t elapsed_ms;

  // Create or recreate DTE and DCE using the guessed baud rate.
  this->modem_create_dte_dce_(this->internal_state_.current_baud_rate);

  ESP_LOGD(TAG, "Autodetecting modem mode...");
  App.feed_wdt();

  // Set the modem to AUTODETECT mode, with time elapsed.
  this->dce->set_mode(modem_mode::AUTODETECT);  // WARNING: A WDT may be triggered if the modem is off.
  ESP_LOGD(TAG, "Modem check took %" PRIu32 "ms.", millis() - start_ms);

  if (this->dce->get_mode() == modem_mode::UNDEF && this->internal_state_.current_baud_rate != 0) {
    ESP_LOGW(TAG, "Autodetect failed. Retrying with default baud rate.");
    this->modem_create_dte_dce_(0);
    delay(100);  // NOLINT
    this->dce->set_mode(modem_mode::AUTODETECT);
  }

  switch (this->dce->get_mode()) {
    case modem_mode::UNDEF:
      ESP_LOGW(TAG, "Modem mode autodetect failed. Attempting command mode.");
      success = this->dce->sync() == command_result::OK || this->dce->set_mode(modem_mode::COMMAND_MODE);
      break;
    case modem_mode::COMMAND_MODE:
      ESP_LOGV(TAG, "Modem in COMMAND_MODE.");
      success = true;
      break;
    case modem_mode::DATA_MODE:
      ESP_LOGV(TAG, "Modem in DATA_MODE (previous session?). Switching to command mode.");
      success = this->dce->set_mode(modem_mode::COMMAND_MODE);
      if (!success) {
        ESP_LOGE(TAG, "Failed to switch to command mode from DATA_MODE.");
      }
      break;
    case modem_mode::CMUX_MANUAL_MODE:
      ESP_LOGV(TAG, "Modem in CMUX_MANUAL_MODE (previous session?). Switching to command mode.");
      this->dce->set_mode(modem_mode::CMUX_MANUAL_COMMAND);
      success = this->dce->set_mode(modem_mode::CMUX_MANUAL_EXIT);
      break;
    default:
      ESP_LOGW(TAG, "Modem in unhandled mode: %d (see esp_modem_types.hpp enum modem_mode).",
               static_cast<int>(this->dce->get_mode()));
  }

  if (success) {
    // Save the baud rate.
    this->modem_restore_state_.baud_rate = this->internal_state_.current_baud_rate;
    this->pref_.save(&this->modem_restore_state_);
    global_preferences->sync();
  }

  delay(100);  // NOLINT
  if (success && this->dce->sync() == command_result::OK) {
    ESP_LOGI(TAG, "Modem ready.");
  } else if (this->power_pin_) {
    ESP_LOGW(TAG, "Modem unreachable. Power cycling.");
    this->poweroff_();
    return false;
  } else {
    // Fatal error: no power pin defined. Attempting ESP reboot.
    this->abort_("Modem unreachable, no power pin, failed command mode switch.");
  }

  // Modem synced.

  // Some modems require disconnection from the network before a PPP connection.
  // This slows down the connection slightly but is more conservative.
  int network_attached = 1;
  this->dce->get_radio_state(network_attached);
  if (network_attached == 1) {
    ESP_LOGD(TAG, "Modem attached to network. Detaching...");
    this->dce->set_radio_state(4);  // disable RF (Airplane mode)
    delay(200);                     // NOLINT
    this->dce->set_radio_state(1);  // Full functionality
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
        ESP_LOGI(TAG, "Modem synced at baud rate %d.", this->baud_rate_);
        this->modem_restore_state_.baud_rate = this->internal_state_.current_baud_rate;
        this->pref_.save(&this->modem_restore_state_);
        // Save state: modem only reachable at this baud rate if not powered off.
        global_preferences->sync();

      } else {
        ESP_LOGE(TAG, "Failed to sync modem at baud rate %d.", this->baud_rate_);
        success = false;
      }
    } else {
      ESP_LOGW(TAG, "Failed to set modem baud rate to %d. Using %d.", this->baud_rate_,
               this->internal_state_.current_baud_rate);
    }
  }

  elapsed_ms = millis() - start_ms;

  if (success) {
    ESP_LOGI(TAG, "Modem initialized in %" PRIu32 "ms.", elapsed_ms);
  } else {
    ESP_LOGE(TAG, "Modem initialization failed in %" PRIu32 "ms.", elapsed_ms);
  }

  if (!success) {
    return false;
  }

  this->pref_.save(&this->modem_restore_state_);
  global_preferences->sync();

  this->send_init_at_();

  ESP_LOGI(TAG, "Modem infos:");
  std::string result;
  ESPMODEM_ERROR_CHECK(this->dce->get_module_name(result), "get_module_name");
  ESP_LOGI(TAG, "  Module name: %s", result.c_str());

  if (!this->prepare_sim_()) {
    this->abort_("Fatal: Sim error");
    return false;
  }

  success = this->dce->sync() == command_result::OK;

  if (!success) {
    ESP_LOGE(TAG, "Fatal: Modem init failed.");
  }

  return success;
}

bool ModemComponent::prepare_sim_() {
  std::string output;
  this->flush_uart_();

  // this->dce->read_pin(pin_ok) // Not used, because we can't know the cause of the error.
  App.feed_wdt();
  this->dce->command(
      "AT+CPIN?\r",
      [&](uint8_t *data, size_t len) {
        output.assign(reinterpret_cast<char *>(data), len);
        std::replace(output.begin(), output.end(), '\n', ' ');
        return command_result::OK;
      },
      this->command_delay_);

  ESP_LOGD(TAG, "SIM status: %s", output.c_str());

  if (output.find("+CPIN: READY") != std::string::npos) {
    ESP_LOGD(TAG, "SIM PIN unlocked.");
    return true;  // Pin not needed or already unlocked.
  } else if (output.find("SIM not inserted") != std::string::npos) {
    ESP_LOGE(TAG, "SIM card missing.");
    return false;
  } else if (output.find("SIM failure") != std::string::npos) {
    ESP_LOGE(TAG, "SIM card failure. Check card.");
    return false;
  } else if (output.find("SIM PUK") != std::string::npos) {
    ESP_LOGE(TAG, "SIM locked by PUK. Unlock it.");
    return false;
  }

  if (this->pin_code_.empty()) {
    ESP_LOGE(TAG, "SIM PIN empty, but SIM locked.");
    return false;
  }

  // We need to unlock the SIM.
  this->internal_state_.sim_unlocked = false;
  ESP_LOGD(TAG, "Unlocking SIM with PIN...");
  if (this->dce->set_pin(this->pin_code_) == command_result::OK) {
    ESP_LOGD(TAG, "PIN set. Will check later.");
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

    std::string output;

    ESPMODEM_ERROR_CHECK(this->dce->command(
                             cmd + "\r",
                             [&](uint8_t *data, size_t len) {
                               output.assign(reinterpret_cast<char *>(data), len);
                               std::replace(output.begin(), output.end(), '\n', ' ');
                               return command_result::OK;
                             },
                             this->command_delay_),
                         "init_at");
    delay(200);                         // NOLINT
    output += this->flush_uart_(2000);  // Probably a bug in esp_modem. Long strings are truncated.
    ESP_LOGI(TAG, "Init AT cmd %s: %s", cmd.c_str(), output.c_str());
  }
  this->flush_uart_();
}

bool ModemComponent::is_network_attached_() {
  if (this->internal_state_.connected)
    return true;
  if (this->dce->sync() == command_result::OK) {
    int attached = 99;
    this->dce->get_network_attachment_state(attached);
    if (attached != 99)
      return (bool) attached;
  }
  return false;
}

bool ModemComponent::start_ppp_() {
  this->internal_state_.connect_begin = millis();
  this->status_set_warning("Starting connection");

  uint32_t now = millis();

  ESP_LOGD(TAG, "Modem entering PPP (CMUX: %s).", this->cmux_ ? "Yes" : "No");

  bool status = false;
  if (cmux_) {
    status = this->dce->set_mode(modem_mode::CMUX_MODE);
    // Note: Do not try to check if the modem is synced with 'this->dce->sync()' now; it will fail on some modems.
  } else {
    status = this->dce->set_mode(modem_mode::DATA_MODE);
  }

  if (!status) {
    ESP_LOGE(TAG, "Failed to enter PPP mode after %" PRIu32 "ms.", millis() - now);
  } else {
    ESP_LOGD(TAG, "Entered PPP after %" PRIu32 "ms.", millis() - now);
  }
  this->pref_.save(&this->modem_restore_state_);
  return status;
}

void ModemComponent::ip_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
  ip_event_got_ip_t *event;
  const esp_netif_ip_info_t *ip_info;
  switch (event_id) {
    case IP_EVENT_PPP_GOT_IP:
      event = (ip_event_got_ip_t *) event_data;
      ip_info = &event->ip_info;
      ESP_LOGD(TAG, "IP event: Got IP " IPSTR, IP2STR(&ip_info->ip));
      global_modem_component->internal_state_.connected = true;
      break;

    case IP_EVENT_PPP_LOST_IP:
      if (global_modem_component->internal_state_.connected) {
        // Only log if previously connected.
        ESP_LOGD(TAG, "IP event: Lost IP.");
      }
      global_modem_component->internal_state_.connected = false;
      break;
  }
}

void ModemComponent::poweron_() {
  if (this->internal_state_.power_transition) {
    ESP_LOGD(TAG, "Power transition in progress. Skipping poweron.");
    return;
  }
  if (this->status_pin_) {
    // Check status pin for power state.
    if (this->get_power_status()) {
      ESP_LOGV(TAG, "Modem already ON (status pin HIGH).");
      // this->internal_state_.powered_on = true;
      this->internal_state_.power_state = ModemPowerState::TONUART;
      return;
    }
  }
  if (this->power_pin_) {
    this->internal_state_.power_state = ModemPowerState::TON;
    this->internal_state_.power_transition = true;
  } else {
    ESP_LOGW(TAG, "No power_pin defined. Cannot power on modem.");
  }
}

void ModemComponent::poweroff_() {
  if (this->power_pin_) {
    this->internal_state_.power_state = ModemPowerState::TOFF;
    this->internal_state_.power_transition = true;
    this->dce.reset();
    this->dte_.reset();
  } else {
    // This will definitely power off the modem!
    // this->send_at("AT+CPOF");
    this->dce->set_mode(modem_mode::COMMAND_MODE);
    if (this->dce->set_radio_state(0) == command_result::OK) {
      ESP_LOGI(TAG, "No power pin. Modem set to minimal functionality.");
    } else {
      ESP_LOGE(TAG, "Failed to power off modem.");
    }
  }
}

void ModemComponent::abort_(const std::string &message) {
  ESP_LOGE(TAG, "Aborting: %s.", message.c_str());
  this->pref_.save(&this->modem_restore_state_);
  App.reboot();
}

void ModemComponent::dump_connect_params_() {
  if (!this->internal_state_.connected) {
    ESP_LOGCONFIG(TAG, "Modem connection: Not connected.");
    return;
  }
  esp_netif_ip_info_t ip;
  esp_netif_get_ip_info(this->ppp_netif_, &ip);
  ESP_LOGCONFIG(TAG, "Modem connection:");
  ESP_LOGCONFIG(TAG, "  IP Address  : %s", network::IPAddress(&ip.ip).str().c_str());
  ESP_LOGCONFIG(TAG, "  Hostname    : '%s'", App.get_name().c_str());
  ESP_LOGCONFIG(TAG, "  Subnet      : %s", network::IPAddress(&ip.netmask).str().c_str());
  ESP_LOGCONFIG(TAG, "  Gateway     : %s", network::IPAddress(&ip.gw).str().c_str());

  const ip_addr_t *dns_main_ip = dns_getserver(ESP_NETIF_DNS_MAIN);
  const ip_addr_t *dns_backup_ip = dns_getserver(ESP_NETIF_DNS_BACKUP);
  const ip_addr_t *dns_fallback_ip = dns_getserver(ESP_NETIF_DNS_FALLBACK);

  ESP_LOGCONFIG(TAG, "  DNS main    : %s", network::IPAddress(dns_main_ip).str().c_str());
  ESP_LOGCONFIG(TAG, "  DNS backup  : %s", network::IPAddress(dns_backup_ip).str().c_str());
  ESP_LOGCONFIG(TAG, "  DNS fallback: %s", network::IPAddress(dns_fallback_ip).str().c_str());
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
