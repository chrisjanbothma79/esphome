#include "esphome/core/hal.h"
#include "esphome/core/log.h"

#include "lmic_component.h"

#include "arduino_lmic.h"

// extern "C" {
// // #include <lbm_lib/lora_basics_modem_version.h>
// #include "lora_basics_modem_version.h"
// #include "smtc_modem_core/lmic_manager/lmic_join_management.h"
// }
// #include "swl2001.h"
// #include "swl2001_radio_callbacks.h"

namespace esphome {
namespace lmic {

static const char *const TAG = "lmic";

void LMICComponent::setup() {
  Component::setup();

  u1_t devStatusAns_battery;
  LMIC.dataLen = 0;

  // Register listener to the LoRa component
  this->parent_->register_listener(this);

  // Set-up the SWL2001 stack
  // keys_t keys;
  // std::copy(this->app_key_.begin(), this->app_key_.end(), keys.app_key);
  // std::copy(this->dev_eui_.begin(), this->dev_eui_.end(), keys.dev_eui);
  // std::copy(this->join_eui_.begin(), this->join_eui_.end(), keys.join_eui);
  // std::copy(this->gen_app_key_.begin(), this->gen_app_key_.end(), keys.gen_app_key);
  // timings_t timings = {
  //     .join_delay = this->after_join_delay_,
  //     .periodicity = this->periodical_uplink_delay_,
  // };
  // swl2001_init(this, this->parent_, keys, timings);
}

void LMICComponent::loop() {
  // swl2001_loop();
}

void LMICComponent::on_packet(const std::vector<uint8_t> &packet, float rssi, float snr) {
  // Handle data from radio
  RadioPacket rp = {packet, rssi, snr};
  // this->rx_buffer.push_back(rp);
}

void LMICComponent::send_packet(std::vector<uint8_t> &data, uint8_t port, bool confirmed) {
  uint8_t len = data.size();
  uint8_t buf[len];
  std::copy(data.begin(), data.end(), buf);
  // swl2001_send_to_stack(buf, len, port, confirmed);
}

void LMICComponent::received_packet(uint8_t *buf, uint8_t len, uint8_t port, float rssi, float snr) {
  const std::vector<uint8_t> packet(buf, buf + len);
  this->call_listeners_(packet, port, rssi, snr);
}

// uint8_t LMICComponent::get_battery_level() {
//   if (this->battery_sensor_ != nullptr) {
//     float battery_level = this->battery_sensor_->state;
//     if (battery_level < this->battery_min_) {
//       battery_level = this->battery_min_;
//     } else if (battery_level > this->battery_max_) {
//       battery_level = this->battery_max_;
//     }
//     return static_cast<uint8_t>(
//         roundf((battery_level - this->battery_min_) / (this->battery_max_ - this->battery_min_) * 254.0f));
//   }
//   return 255u;  // No battery sensor configured
// }

void LMICComponent::forward_packet(const uint8_t *buf, const uint8_t len) {
  const std::vector<uint8_t> packet(buf, buf + len);
  this->parent_->send_packet(packet);
}

uint8_t LMICComponent::read_packet(uint8_t *buf) {
  // if (this->rx_buffer.size() > 0) {
  //   RadioPacket rp = this->rx_buffer.front();
  //   this->rx_buffer.pop_front();
  //   std::copy(rp.packet.begin(), rp.packet.end(), buf);
  //   return rp.packet.size();
  // } else {
  return 0u;
  // }
}

void LMICComponent::call_listeners_(const std::vector<uint8_t> &packet, uint8_t port, float rssi, float snr) {
  for (auto &listener : this->listeners_) {
    listener->on_packet(packet, port, rssi, snr);
  }
  this->packet_trigger_->trigger(packet, port, rssi, snr);
}

}  // namespace lmic
}  // namespace esphome