#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/core/automation.h"
#include "esphome/components/socket/socket.h"
#include <string>
#include <vector>
#include <functional>

namespace esphome {
namespace simple_mqtt {

enum class MQTTClientState {
  DISCONNECTED = 0,
  CONNECTING,
  CONNECTED
};

class SimpleMQTTClient;

// MQTT Message callback class
class MQTTMessageTrigger : public Trigger<std::string, std::string> {
 public:
  explicit MQTTMessageTrigger(SimpleMQTTClient *parent) : Trigger<std::string, std::string>(), parent_(parent) {}

 private:
  SimpleMQTTClient *parent_;
};

class SimpleMQTTClient : public Component {
 public:
  SimpleMQTTClient() = default;
  
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::AFTER_CONNECTION; }
  void on_shutdown() override;
  
  // Configuration setters
  void set_broker_address(const std::string &broker_address) { broker_address_ = broker_address; }
  void set_broker_port(uint16_t broker_port) { broker_port_ = broker_port; }
  void set_client_id(const std::string &client_id) { client_id_ = client_id; }
  void set_username(const std::string &username) { username_ = username; }
  void set_password(const std::string &password) { password_ = password; }
  void set_keep_alive(uint16_t keep_alive) { keep_alive_ = keep_alive; }
  void set_auto_reconnect(bool auto_reconnect) { auto_reconnect_ = auto_reconnect; }
  
  // MQTT methods
  bool connect();
  bool disconnect();
  bool is_connected() const { return state_ == MQTTClientState::CONNECTED; }
  bool publish(const std::string &topic, const std::string &payload, uint8_t qos = 0, bool retain = false);
  bool subscribe(const std::string &topic, uint8_t qos = 0);
  bool unsubscribe(const std::string &topic);
  
  // Helper methods for ESPHome-style triggers
  MQTTMessageTrigger *make_message_trigger(const std::string &topic) {
    auto trigger = new MQTTMessageTrigger(this);
    this->subscribe(topic);
    this->message_triggers_.push_back(trigger);
    return trigger;
  }
  
  // Callback for received messages
  using MessageCallback = std::function<void(const std::string &topic, const std::string &payload)>;
  void set_message_callback(MessageCallback callback) { message_callback_ = callback; }
  
 protected:
  // Connection parameters
  std::string broker_address_{"localhost"};
  uint16_t broker_port_{1883};
  std::string client_id_{"esphome"};
  std::string username_{};
  std::string password_{};
  uint16_t keep_alive_{60};
  bool auto_reconnect_{true};
  uint32_t last_reconnect_attempt_{0};
  
  // Connection state
  MQTTClientState state_{MQTTClientState::DISCONNECTED};
  uint32_t connect_start_time_{0};  // Timestamp when connection started
  uint32_t last_ping_time_{0};
  uint32_t last_activity_time_{0};
  std::unique_ptr<socket::Socket> socket_{nullptr};
  uint16_t packet_id_{0};
  
  // Message handling
  MessageCallback message_callback_{};
  std::vector<MQTTMessageTrigger *> message_triggers_{};
  std::vector<std::string> subscribed_topics_{};
  
  // MQTT packet handling
  bool send_connect_packet_();
  bool send_disconnect_packet_();
  bool send_ping_request_();
  bool send_publish_packet_(const std::string &topic, const std::string &payload, uint8_t qos, bool retain);
  bool send_subscribe_packet_(const std::string &topic, uint8_t qos);
  bool send_unsubscribe_packet_(const std::string &topic);
  
  // Helper methods
  uint16_t get_next_packet_id_() { return ++packet_id_ == 0 ? ++packet_id_ : packet_id_; }
  bool process_packet_();
  bool read_packet_();
  void handle_message_(const std::string &topic, const std::string &payload);
  
  // Buffer for receiving data
  std::vector<uint8_t> buffer_;
};

// MQTT Publish Action - using TEMPLATABLE_VALUE like the official MQTT component
template<typename... Ts>
class MQTTPublishAction : public Action<Ts...> {
 public:
  MQTTPublishAction(SimpleMQTTClient *parent) : parent_(parent) {}
  
  TEMPLATABLE_VALUE(std::string, topic)
  TEMPLATABLE_VALUE(std::string, payload)
  TEMPLATABLE_VALUE(uint8_t, qos)
  TEMPLATABLE_VALUE(bool, retain)

  void play(Ts... x) override {
    if (this->parent_ != nullptr && this->parent_->is_connected()) {
      this->parent_->publish(this->topic_.value(x...), this->payload_.value(x...), 
                            this->qos_.value(x...), this->retain_.value(x...));
    } else {
      ESP_LOGW("simple_mqtt", "Not connected to MQTT broker, cannot publish");
    }
  }
  
 protected:
  SimpleMQTTClient *parent_;
};

}  // namespace simple_mqtt
}  // namespace esphome 