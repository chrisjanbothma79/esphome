#include "simple_mqtt.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"
#include "esphome/core/hal.h"  // For millis() and delay()
#include "esphome/components/network/util.h"

#ifdef USE_OPENTHREAD_ZEPHYR
#include "esphome/components/openthread_zephyr/openthread.h"
#endif

namespace esphome {
namespace simple_mqtt {

static const char *const TAG = "simple_mqtt";

// MQTT packet types
enum class MQTTPacketType : uint8_t {
  CONNECT = 1,
  CONNACK = 2,
  PUBLISH = 3,
  PUBACK = 4,
  PUBREC = 5,
  PUBREL = 6,
  PUBCOMP = 7,
  SUBSCRIBE = 8,
  SUBACK = 9,
  UNSUBSCRIBE = 10,
  UNSUBACK = 11,
  PINGREQ = 12,
  PINGRESP = 13,
  DISCONNECT = 14
};

// MQTT connect flags
enum class MQTTConnectFlag : uint8_t {
  USERNAME = 0x80,
  PASSWORD = 0x40,
  WILL_RETAIN = 0x20,
  WILL_QOS_1 = 0x08,
  WILL_QOS_2 = 0x10,
  WILL = 0x04,
  CLEAN_SESSION = 0x02
};

// MQTT connect return codes
enum class MQTTConnectReturnCode : uint8_t {
  ACCEPTED = 0,
  UNACCEPTABLE_PROTOCOL = 1,
  IDENTIFIER_REJECTED = 2,
  SERVER_UNAVAILABLE = 3,
  BAD_CREDENTIALS = 4,
  NOT_AUTHORIZED = 5
};

void SimpleMQTTClient::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Simple MQTT...");
  this->buffer_.reserve(1024);

  // Try to connect if auto-reconnect is enabled
  if (this->auto_reconnect_) {
    this->connect();
  }
}

void SimpleMQTTClient::loop() {
  const uint32_t now = millis();

  // Handle connection state
  switch (this->state_) {
    case MQTTClientState::DISCONNECTED:
      // Try to reconnect if needed
      if (this->auto_reconnect_ && (now - this->last_reconnect_attempt_ > 5000)) {
        ESP_LOGD(TAG, "Attempting to reconnect to MQTT broker...");
        this->connect();
        this->last_reconnect_attempt_ = now;
      }
      break;

    case MQTTClientState::CONNECTING:
      // Check for connection timeout
      break;

    case MQTTClientState::CONNECTED: {
      // Send keep-alive ping if needed
      if (now - this->last_ping_time_ > this->keep_alive_ * 1000 / 2) {
        if (!this->send_ping_request_()) {
          ESP_LOGW(TAG, "Failed to send ping request, disconnecting");
          this->disconnect();
          return;
        }
        this->last_ping_time_ = now;
      }

      // Process incoming packets
      if (this->socket_ != nullptr) {
        this->process_packet_();
      }
      break;
    }
  }
}

void SimpleMQTTClient::dump_config() {
  ESP_LOGCONFIG(TAG, "Simple MQTT:");
  ESP_LOGCONFIG(TAG, "  Broker Address: %s", this->broker_address_.c_str());
  ESP_LOGCONFIG(TAG, "  Broker Port: %u", this->broker_port_);
  ESP_LOGCONFIG(TAG, "  Client ID: %s", this->client_id_.c_str());
  if (!this->username_.empty()) {
    ESP_LOGCONFIG(TAG, "  Username: %s", this->username_.c_str());
  }
  if (!this->password_.empty()) {
    ESP_LOGCONFIG(TAG, "  Password: " LOG_SECRET("%s"), this->password_.c_str());
  }
  ESP_LOGCONFIG(TAG, "  Keep Alive: %us", this->keep_alive_);
  ESP_LOGCONFIG(TAG, "  Auto Reconnect: %s", YESNO(this->auto_reconnect_));
}

void SimpleMQTTClient::on_shutdown() {
  if (this->is_connected()) {
    this->disconnect();
  }
}

bool SimpleMQTTClient::connect() {
  if (this->state_ != MQTTClientState::DISCONNECTED) {
    return false;
  }

  ESP_LOGI(TAG, "Connecting to MQTT broker %s:%u...", this->broker_address_.c_str(), this->broker_port_);

  // Check if we should use IPv6 from OpenThread
  std::string broker_address = this->broker_address_;
  bool is_ipv6 = broker_address.find(':') != std::string::npos;
  
#ifdef USE_OPENTHREAD_ZEPHYR
  if (openthread_zephyr::global_openthread_component != nullptr && 
      openthread_zephyr::global_openthread_component->is_connected() &&
      openthread_zephyr::global_openthread_component->has_ipv6_address()) {
    if (is_ipv6) {
      ESP_LOGD(TAG, "Using IPv6 broker address: %s", broker_address.c_str());
    } else {
      ESP_LOGD(TAG, "Using IPv4 address with NAT64 translation: %s", broker_address.c_str());
    }
  } else {
    ESP_LOGD(TAG, "OpenThread not connected or no IPv6 address available");
  }
#endif

  // Create socket - always use IPv6 for OpenThread
  ESP_LOGD(TAG, "Creating IPv6 socket for MQTT connection...");
  this->socket_ = socket::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
  
  if (this->socket_ == nullptr) {
    ESP_LOGE(TAG, "Failed to create socket, errno: %d (%s)", errno, strerror(errno));
    return false;
  }

  // Set non-blocking mode
  ESP_LOGD(TAG, "Setting socket to non-blocking mode");
  int ret = this->socket_->setblocking(false);
  if (ret < 0) {
    ESP_LOGE(TAG, "Failed to set socket to non-blocking mode, errno: %d (%s)", errno, strerror(errno));
    this->socket_ = nullptr;
    return false;
  }

  // Resolve broker address
  ESP_LOGD(TAG, "Resolving broker address: %s", broker_address.c_str());
  struct sockaddr_storage storage;
  socklen_t addrlen = sizeof(storage);
  
  // Set up the sockaddr structure - the socket component will handle NAT64 translation
  // for IPv4 addresses when using an IPv6 socket
  memset(&storage, 0, addrlen);
  struct sockaddr *addr = (struct sockaddr *)&storage;
  addr->sa_family = AF_INET6;  // Set family to IPv6 to trigger NAT64 translation if needed
  
  addrlen = socket::set_sockaddr(addr, addrlen, broker_address, this->broker_port_);
  if (addrlen == 0) {
    ESP_LOGE(TAG, "Failed to resolve broker address");
    this->socket_ = nullptr;
    return false;
  }
  
  // Connect to broker
  ESP_LOGD(TAG, "Connecting to broker...");
  int err = this->socket_->connect((struct sockaddr *) &storage, addrlen);
  if (err < 0) {
    if (errno == EINPROGRESS) {
      ESP_LOGD(TAG, "Connection in progress, waiting for completion...");
      // Connection in progress, wait for completion
      this->state_ = MQTTClientState::CONNECTING;
      this->connect_start_time_ = millis();
      return true;
    } else {
      ESP_LOGE(TAG, "Failed to connect to MQTT broker, errno: %d (%s)", errno, strerror(errno));
      
      // Get more information about the socket
      std::string peer_name = this->socket_->getpeername();
      std::string sock_name = this->socket_->getsockname();
      ESP_LOGD(TAG, "Socket peer name: %s", peer_name.empty() ? "unknown" : peer_name.c_str());
      ESP_LOGD(TAG, "Socket local name: %s", sock_name.empty() ? "unknown" : sock_name.c_str());
      
      // Try to get socket error
      int socket_error = 0;
      socklen_t len = sizeof(socket_error);
      if (this->socket_->getsockopt(SOL_SOCKET, SO_ERROR, &socket_error, &len) == 0) {
        ESP_LOGD(TAG, "Socket error: %d (%s)", socket_error, strerror(socket_error));
      }
      
      this->socket_ = nullptr;
      return false;
    }
  }

  // Connection successful, send MQTT CONNECT packet
  ESP_LOGD(TAG, "Socket connected, sending MQTT CONNECT packet");
  this->state_ = MQTTClientState::CONNECTING;
  this->connect_start_time_ = millis();
  this->last_activity_time_ = millis();

  // Send CONNECT packet
  if (!this->send_connect_packet_()) {
    ESP_LOGE(TAG, "Failed to send CONNECT packet");
    this->socket_ = nullptr;
    this->state_ = MQTTClientState::DISCONNECTED;
    return false;
  }

  // Wait for CONNACK packet
  // In a real implementation, we would handle this asynchronously
  // For simplicity, we'll wait for the response here
  delay(100);
  if (!this->process_packet_()) {
    ESP_LOGE(TAG, "Failed to receive CONNACK packet");
    this->socket_ = nullptr;
    this->state_ = MQTTClientState::DISCONNECTED;
    return false;
  }

  ESP_LOGI(TAG, "Connected to MQTT broker");
  this->state_ = MQTTClientState::CONNECTED;
  this->last_ping_time_ = millis();

  // Resubscribe to topics
  for (const auto &topic : this->subscribed_topics_) {
    this->subscribe(topic);
  }

  return true;
}

bool SimpleMQTTClient::disconnect() {
  if (this->state_ == MQTTClientState::DISCONNECTED) {
    return true;
  }

  ESP_LOGI(TAG, "Disconnecting from MQTT broker");

  if (this->state_ == MQTTClientState::CONNECTED) {
    this->send_disconnect_packet_();
  }

  if (this->socket_ != nullptr) {
    this->socket_->close();
    this->socket_ = nullptr;
  }

  this->state_ = MQTTClientState::DISCONNECTED;
  return true;
}

bool SimpleMQTTClient::publish(const std::string &topic, const std::string &payload, uint8_t qos, bool retain) {
  if (this->state_ != MQTTClientState::CONNECTED) {
    ESP_LOGW(TAG, "Not connected to MQTT broker");
    return false;
  }

  return this->send_publish_packet_(topic, payload, qos, retain);
}

bool SimpleMQTTClient::subscribe(const std::string &topic, uint8_t qos) {
  if (this->state_ != MQTTClientState::CONNECTED) {
    ESP_LOGW(TAG, "Not connected to MQTT broker");

    // Add to subscribed topics list for auto-resubscribe
    if (std::find(this->subscribed_topics_.begin(), this->subscribed_topics_.end(), topic) ==
        this->subscribed_topics_.end()) {
      this->subscribed_topics_.push_back(topic);
    }

    return false;
  }

  // Add to subscribed topics list for auto-resubscribe
  if (std::find(this->subscribed_topics_.begin(), this->subscribed_topics_.end(), topic) ==
      this->subscribed_topics_.end()) {
    this->subscribed_topics_.push_back(topic);
  }

  return this->send_subscribe_packet_(topic, qos);
}

bool SimpleMQTTClient::unsubscribe(const std::string &topic) {
  // Remove from subscribed topics list
  auto it = std::find(this->subscribed_topics_.begin(), this->subscribed_topics_.end(), topic);
  if (it != this->subscribed_topics_.end()) {
    this->subscribed_topics_.erase(it);
  }

  if (this->state_ != MQTTClientState::CONNECTED) {
    ESP_LOGW(TAG, "Not connected to MQTT broker");
    return false;
  }

  return this->send_unsubscribe_packet_(topic);
}

/* Commented out to avoid redefinition - already defined in header
MQTTMessageTrigger *SimpleMQTTClient::make_message_trigger(const std::string &topic) {
  auto trigger = new MQTTMessageTrigger(this);
  this->message_triggers_.push_back(trigger);

  // Subscribe to the topic
  this->subscribe(topic);
}
*/

void SimpleMQTTClient::handle_message_(const std::string &topic, const std::string &payload) {
  // Call the message callback if set
  if (this->message_callback_) {
    this->message_callback_(topic, payload);
  }

  // Trigger all message triggers that match the topic
  for (auto *trigger : this->message_triggers_) {
    trigger->trigger(topic, payload);
  }
}

bool SimpleMQTTClient::send_connect_packet_() {
  // Calculate packet size
  uint16_t client_id_length = this->client_id_.length();
  uint16_t username_length = this->username_.length();
  uint16_t password_length = this->password_.length();

  uint16_t variable_header_length = 10;  // Protocol name + version + flags + keep alive
  uint16_t payload_length = 2 + client_id_length;

  if (!this->username_.empty()) {
    payload_length += 2 + username_length;
  }

  if (!this->password_.empty()) {
    payload_length += 2 + password_length;
  }

  uint16_t remaining_length = variable_header_length + payload_length;

  // Prepare packet
  std::vector<uint8_t> packet;
  packet.reserve(1 + 2 + remaining_length);  // Fixed header + remaining length + variable header + payload

  // Fixed header
  packet.push_back(static_cast<uint8_t>(MQTTPacketType::CONNECT) << 4);

  // Remaining length
  if (remaining_length < 128) {
    packet.push_back(remaining_length);
  } else {
    packet.push_back((remaining_length & 0x7F) | 0x80);
    packet.push_back(remaining_length >> 7);
  }

  // Variable header - Protocol name
  packet.push_back(0);  // Length MSB
  packet.push_back(4);  // Length LSB
  packet.push_back('M');
  packet.push_back('Q');
  packet.push_back('T');
  packet.push_back('T');

  // Variable header - Protocol version
  packet.push_back(4);  // MQTT 3.1.1

  // Variable header - Connect flags
  uint8_t connect_flags = 0;
  if (!this->username_.empty()) {
    connect_flags |= static_cast<uint8_t>(MQTTConnectFlag::USERNAME);
  }
  if (!this->password_.empty()) {
    connect_flags |= static_cast<uint8_t>(MQTTConnectFlag::PASSWORD);
  }
  connect_flags |= static_cast<uint8_t>(MQTTConnectFlag::CLEAN_SESSION);
  packet.push_back(connect_flags);

  // Variable header - Keep alive
  packet.push_back(this->keep_alive_ >> 8);    // MSB
  packet.push_back(this->keep_alive_ & 0xFF);  // LSB

  // Payload - Client ID
  packet.push_back(client_id_length >> 8);    // MSB
  packet.push_back(client_id_length & 0xFF);  // LSB
  packet.insert(packet.end(), this->client_id_.begin(), this->client_id_.end());

  // Payload - Username (if set)
  if (!this->username_.empty()) {
    packet.push_back(username_length >> 8);    // MSB
    packet.push_back(username_length & 0xFF);  // LSB
    packet.insert(packet.end(), this->username_.begin(), this->username_.end());
  }

  // Payload - Password (if set)
  if (!this->password_.empty()) {
    packet.push_back(password_length >> 8);    // MSB
    packet.push_back(password_length & 0xFF);  // LSB
    packet.insert(packet.end(), this->password_.begin(), this->password_.end());
  }

  // Send packet
  ssize_t sent = this->socket_->write(packet.data(), packet.size());
  return sent == static_cast<ssize_t>(packet.size());
}

bool SimpleMQTTClient::send_disconnect_packet_() {
  // Prepare packet
  std::vector<uint8_t> packet;
  packet.reserve(2);

  // Fixed header
  packet.push_back(static_cast<uint8_t>(MQTTPacketType::DISCONNECT) << 4);

  // Remaining length
  packet.push_back(0);

  // Send packet
  ssize_t sent = this->socket_->write(packet.data(), packet.size());
  return sent == static_cast<ssize_t>(packet.size());
}

bool SimpleMQTTClient::send_ping_request_() {
  // Prepare packet
  std::vector<uint8_t> packet;
  packet.reserve(2);

  // Fixed header
  packet.push_back(static_cast<uint8_t>(MQTTPacketType::PINGREQ) << 4);

  // Remaining length
  packet.push_back(0);

  // Send packet
  ssize_t sent = this->socket_->write(packet.data(), packet.size());
  return sent == static_cast<ssize_t>(packet.size());
}

bool SimpleMQTTClient::send_publish_packet_(const std::string &topic, const std::string &payload, uint8_t qos,
                                            bool retain) {
  // Calculate packet size
  uint16_t topic_length = topic.length();
  uint16_t payload_length = payload.length();

  uint16_t variable_header_length = 2 + topic_length;
  if (qos > 0) {
    variable_header_length += 2;  // Packet ID
  }

  uint16_t remaining_length = variable_header_length + payload_length;

  // Prepare packet
  std::vector<uint8_t> packet;
  packet.reserve(1 + 2 + remaining_length);  // Fixed header + remaining length + variable header + payload

  // Fixed header
  uint8_t fixed_header = static_cast<uint8_t>(MQTTPacketType::PUBLISH) << 4;
  if (retain) {
    fixed_header |= 0x01;
  }
  if (qos > 0) {
    fixed_header |= (qos & 0x03) << 1;
  }
  packet.push_back(fixed_header);

  // Remaining length
  if (remaining_length < 128) {
    packet.push_back(remaining_length);
  } else {
    packet.push_back((remaining_length & 0x7F) | 0x80);
    packet.push_back(remaining_length >> 7);
  }

  // Variable header - Topic
  packet.push_back(topic_length >> 8);    // MSB
  packet.push_back(topic_length & 0xFF);  // LSB
  packet.insert(packet.end(), topic.begin(), topic.end());

  // Variable header - Packet ID (if QoS > 0)
  if (qos > 0) {
    uint16_t packet_id = this->get_next_packet_id_();
    packet.push_back(packet_id >> 8);    // MSB
    packet.push_back(packet_id & 0xFF);  // LSB
  }

  // Payload
  packet.insert(packet.end(), payload.begin(), payload.end());

  // Send packet
  ssize_t sent = this->socket_->write(packet.data(), packet.size());
  return sent == static_cast<ssize_t>(packet.size());
}

bool SimpleMQTTClient::send_subscribe_packet_(const std::string &topic, uint8_t qos) {
  // Calculate packet size
  uint16_t topic_length = topic.length();

  uint16_t variable_header_length = 2;             // Packet ID
  uint16_t payload_length = 2 + topic_length + 1;  // Topic length + topic + QoS

  uint16_t remaining_length = variable_header_length + payload_length;

  // Prepare packet
  std::vector<uint8_t> packet;
  packet.reserve(1 + 2 + remaining_length);  // Fixed header + remaining length + variable header + payload

  // Fixed header
  packet.push_back(static_cast<uint8_t>(MQTTPacketType::SUBSCRIBE) << 4 | 0x02);  // SUBSCRIBE packet with QoS 1

  // Remaining length
  if (remaining_length < 128) {
    packet.push_back(remaining_length);
  } else {
    packet.push_back((remaining_length & 0x7F) | 0x80);
    packet.push_back(remaining_length >> 7);
  }

  // Variable header - Packet ID
  uint16_t packet_id = this->get_next_packet_id_();
  packet.push_back(packet_id >> 8);    // MSB
  packet.push_back(packet_id & 0xFF);  // LSB

  // Payload - Topic filter
  packet.push_back(topic_length >> 8);    // MSB
  packet.push_back(topic_length & 0xFF);  // LSB
  packet.insert(packet.end(), topic.begin(), topic.end());

  // Payload - QoS
  packet.push_back(qos & 0x03);

  // Send packet
  ssize_t sent = this->socket_->write(packet.data(), packet.size());
  return sent == static_cast<ssize_t>(packet.size());
}

bool SimpleMQTTClient::send_unsubscribe_packet_(const std::string &topic) {
  // Calculate packet size
  uint16_t topic_length = topic.length();

  uint16_t variable_header_length = 2;         // Packet ID
  uint16_t payload_length = 2 + topic_length;  // Topic length + topic

  uint16_t remaining_length = variable_header_length + payload_length;

  // Prepare packet
  std::vector<uint8_t> packet;
  packet.reserve(1 + 2 + remaining_length);  // Fixed header + remaining length + variable header + payload

  // Fixed header
  packet.push_back(static_cast<uint8_t>(MQTTPacketType::UNSUBSCRIBE) << 4 | 0x02);  // UNSUBSCRIBE packet with QoS 1

  // Remaining length
  if (remaining_length < 128) {
    packet.push_back(remaining_length);
  } else {
    packet.push_back((remaining_length & 0x7F) | 0x80);
    packet.push_back(remaining_length >> 7);
  }

  // Variable header - Packet ID
  uint16_t packet_id = this->get_next_packet_id_();
  packet.push_back(packet_id >> 8);    // MSB
  packet.push_back(packet_id & 0xFF);  // LSB

  // Payload - Topic filter
  packet.push_back(topic_length >> 8);    // MSB
  packet.push_back(topic_length & 0xFF);  // LSB
  packet.insert(packet.end(), topic.begin(), topic.end());

  // Send packet
  ssize_t sent = this->socket_->write(packet.data(), packet.size());
  return sent == static_cast<ssize_t>(packet.size());
}

bool SimpleMQTTClient::process_packet_() {
  if (!this->read_packet_()) {
    return false;
  }

  if (this->buffer_.empty()) {
    return false;
  }

  // Get packet type
  uint8_t packet_type = this->buffer_[0] >> 4;

  switch (static_cast<MQTTPacketType>(packet_type)) {
    case MQTTPacketType::CONNACK: {
      if (this->buffer_.size() < 4) {
        ESP_LOGW(TAG, "Received invalid CONNACK packet");
        return false;
      }

      uint8_t return_code = this->buffer_[3];
      if (return_code != static_cast<uint8_t>(MQTTConnectReturnCode::ACCEPTED)) {
        ESP_LOGW(TAG, "Connection rejected with code %u", return_code);
        return false;
      }

      ESP_LOGI(TAG, "Connection accepted");
      this->state_ = MQTTClientState::CONNECTED;
      return true;
    }

    case MQTTPacketType::PUBLISH: {
      if (this->buffer_.size() < 4) {
        ESP_LOGW(TAG, "Received invalid PUBLISH packet");
        return false;
      }

      // Extract QoS
      uint8_t qos = (this->buffer_[0] >> 1) & 0x03;

      // Extract topic length
      uint16_t topic_length = (this->buffer_[1] << 8) | this->buffer_[2];

      // Check if we have enough data
      if (this->buffer_.size() < 3 + topic_length) {
        ESP_LOGW(TAG, "Received incomplete PUBLISH packet");
        return false;
      }

      // Extract topic
      std::string topic(reinterpret_cast<char *>(&this->buffer_[3]), topic_length);

      // Extract payload
      size_t payload_offset = 3 + topic_length;
      if (qos > 0) {
        payload_offset += 2;  // Skip packet ID
      }

      std::string payload;
      if (payload_offset < this->buffer_.size()) {
        payload = std::string(reinterpret_cast<char *>(&this->buffer_[payload_offset]),
                              this->buffer_.size() - payload_offset);
      }

      ESP_LOGD(TAG, "Received message on topic '%s': %s", topic.c_str(), payload.c_str());

      // Handle the message
      this->handle_message_(topic, payload);

      return true;
    }

    case MQTTPacketType::PUBACK:
    case MQTTPacketType::PUBREC:
    case MQTTPacketType::PUBREL:
    case MQTTPacketType::PUBCOMP: {
      // Handle QoS acknowledgments
      return true;
    }

    case MQTTPacketType::SUBACK: {
      ESP_LOGI(TAG, "Subscription acknowledged");
      return true;
    }

    case MQTTPacketType::UNSUBACK: {
      ESP_LOGI(TAG, "Unsubscription acknowledged");
      return true;
    }

    case MQTTPacketType::PINGRESP: {
      ESP_LOGD(TAG, "Received ping response");
      return true;
    }

    default: {
      ESP_LOGW(TAG, "Received unknown packet type: %u", packet_type);
      return false;
    }
  }
}

bool SimpleMQTTClient::read_packet_() {
  if (this->socket_ == nullptr) {
    return false;
  }

  this->buffer_.clear();

  // Read fixed header
  uint8_t byte;
  ssize_t ret = this->socket_->read(&byte, 1);
  if (ret <= 0) {
    if (ret < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
      ESP_LOGW(TAG, "Error reading from socket: %d", errno);
      this->disconnect();
    }
    return false;
  }

  this->buffer_.push_back(byte);

  // Read remaining length
  uint32_t remaining_length = 0;
  uint32_t multiplier = 1;
  do {
    ret = this->socket_->read(&byte, 1);
    if (ret <= 0) {
      if (ret < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
        ESP_LOGW(TAG, "Error reading from socket: %d", errno);
        this->disconnect();
      }
      return false;
    }

    this->buffer_.push_back(byte);

    remaining_length += (byte & 0x7F) * multiplier;
    multiplier *= 128;

    if (multiplier > 128 * 128 * 128) {
      ESP_LOGW(TAG, "Malformed remaining length");
      return false;
    }
  } while ((byte & 0x80) != 0);

  // Read the rest of the packet
  if (remaining_length > 0) {
    size_t original_size = this->buffer_.size();
    this->buffer_.resize(original_size + remaining_length);

    size_t bytes_read = 0;
    while (bytes_read < remaining_length) {
      ret = this->socket_->read(&this->buffer_[original_size + bytes_read], remaining_length - bytes_read);
      if (ret <= 0) {
        if (ret < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
          ESP_LOGW(TAG, "Error reading from socket: %d", errno);
          this->disconnect();
        }
        return false;
      }

      bytes_read += ret;
    }
  }

  return true;
}

}  // namespace simple_mqtt
}  // namespace esphome
