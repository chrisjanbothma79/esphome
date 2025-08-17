#include "dfrobot_c4001.h"

#include <cmath>

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace dfrobot_c4001 {
static const char *const TAG = "dfrobot_c4001";
const char ASCII_CR = 0x0D;
const char ASCII_LF = 0x0A;

void DFRobotC4001Hub::set_occupancy(bool occupancy) {
  this->occupancy_ = occupancy;
#ifdef USE_BINARY_SENSOR
  if (this->occupancy_binary_sensor_ != nullptr) {
    this->occupancy_binary_sensor_->publish_state(occupancy);
  }
#endif
}

// initial setup of module
void DFRobotC4001Hub::setup_module() {
  // stop the module so that configuration can be set
  this->enqueue(make_unique<PowerCommand>(false));
  // put the module is the requested mode
  this->enqueue(make_unique<SetRunAppCommand>());
  this->enqueue(make_unique<SetUartOutputCommand>());
  // start the module
  this->enqueue(make_unique<PowerCommand>(true));
}

void DFRobotC4001Hub::dump_config() {
  ESP_LOGCONFIG(TAG, "DFRobot C4001 mmWave Radar:\n");
#ifdef USE_BINARY_SENSOR
  ESP_LOGCONFIG(TAG, "Binary Sensors:");
  LOG_BINARY_SENSOR("  ", "Occupancy", this->occupancy_binary_sensor_);
#endif
}

void DFRobotC4001Hub::setup() {
  ESP_LOGCONFIG(TAG, "Running setup");
  // setup the module
  this->enqueue(make_unique<ResetSystemCommand>());
  this->setup_module();
}

void DFRobotC4001Hub::loop() {
  if (this->is_failed()) {
    return;
  }

  if (this->cmd_queue_.is_empty()) {
    // Command queue empty, first time this happens setup is complete
    if (!this->is_setup_) {
      this->is_setup_ = true;
      ESP_LOGCONFIG(TAG, "Setup complete");
      if (this->ts_cmd_error_cnt_ > 3) {
        this->mark_failed("Too many errors");
      }
    }
    // Read sensor state
    this->enqueue(make_unique<ReadStateCommand>());
  }
  // Commands are non-blocking and need to be called repeatedly.
  int8_t result = this->cmd_queue_.process(this);
  if (result) {
    if (this->cmd_queue_.is_retry_power_stop()) {
      // add PowerCommand to the beginning of the queue to stop the sensor
      this->enqueue(make_unique<PowerCommand>(false), true);
      ESP_LOGV(TAG, "Queue: Retrying command after stopping sensor");
    } else {
      // negative result means errors occurred magnitude is number of errors
      if (result < 0) {
        this->ts_cmd_error_cnt_ -= result;
        ESP_LOGV(TAG, "Queue: Error Count: %d", this->ts_cmd_error_cnt_);
      }
      // dequeue the command
      this->cmd_queue_.dequeue();
    }
  }
}

int8_t DFRobotC4001Hub::enqueue(std::unique_ptr<Command> cmd, bool first) {
  return this->cmd_queue_.enqueue(std::move(cmd), first);  // Transfer ownership using std::move
}

uint8_t DFRobotC4001Hub::read_message_() {
  while (this->available()) {
    uint8_t byte;
    this->read_byte(&byte);

    if (this->read_pos_ == MMWAVE_READ_BUFFER_LENGTH)
      this->read_pos_ = 0;

    ESP_LOGVV(TAG, "Buffer pos: %u %d", this->read_pos_, byte);

    if (byte == ASCII_CR)
      continue;
    if (byte >= 0x7F)
      byte = '?';  // needs to be valid utf8 string for log functions.
    this->read_buffer_[this->read_pos_] = byte;

    if (byte == '>') {
      this->read_buffer_[++this->read_pos_] = ASCII_LF;
    }

    if (this->read_buffer_[this->read_pos_] == ASCII_LF) {
      this->read_buffer_[this->read_pos_] = 0;
      this->read_pos_ = 0;
#ifdef ESPHOME_LOG_HAS_VERBOSE
      std::string message(this->read_buffer_);
      if (!(str_startswith(message, "$DFHPD")) && !(str_startswith(message, "$DFDMD")))
        ESP_LOGV(TAG, "Recv Msg: %s", this->read_buffer_);
#endif
      // ESP_LOGV(TAG, "Recv Msg: %s", this->read_buffer_);
      return true;  // Full message in buffer
    } else {
      this->read_pos_++;
    }
  }
  return false;  // No full message yet
}

uint8_t DFRobotC4001Hub::send_cmd_(const char *cmd, uint32_t duration) {
  // The interval between two commands must be larger than the specified duration (in ms).
  if (millis() - this->ts_last_cmd_sent_ > duration) {
    this->write_str(cmd);
    this->write_byte(ASCII_CR);
    this->write_byte(ASCII_LF);
    this->ts_last_cmd_sent_ = millis();
    ESP_LOGV(TAG, "Send Cmd: %s", cmd);
    return true;  // Command sent
  }
  // Could not send command yet as command duration did not fully pass yet.
  return false;
}

int8_t CircularCommandQueue::enqueue(std::unique_ptr<Command> cmd, bool first) {
  if (this->is_full()) {
    ESP_LOGE(TAG, "Command queue is full");
    return -1;
  }
  if (first) {
    if (this->is_empty())
      this->rear_ = 0;
    this->front_ = (this->front_ - 1) % COMMAND_QUEUE_SIZE;
    this->commands_[this->front_] = std::move(cmd);  // Transfer ownership using std::move
    return 1;
  } else {
    if (this->is_empty())
      this->front_ = 0;
    this->rear_ = (this->rear_ + 1) % COMMAND_QUEUE_SIZE;
    this->commands_[this->rear_] = std::move(cmd);  // Transfer ownership using std::move
    return 1;
  }
}

bool CircularCommandQueue::is_retry_power_stop() {
  if (this->is_empty()) {
    return false;
  } else {
    return this->commands_[this->front_]->retry_power_stop;
  }
}

std::unique_ptr<Command> CircularCommandQueue::dequeue() {
  if (this->is_empty())
    return nullptr;
  std::unique_ptr<Command> dequeued_cmd = std::move(this->commands_[this->front_]);
  if (this->front_ == this->rear_) {
    this->front_ = -1;
    this->rear_ = -1;
  } else {
    this->front_ = (this->front_ + 1) % COMMAND_QUEUE_SIZE;
  }

  return dequeued_cmd;
}

bool CircularCommandQueue::is_empty() { return this->front_ == -1; }

// queue is full when there is 1 space left
bool CircularCommandQueue::is_full() { return (this->rear_ + 2) % COMMAND_QUEUE_SIZE == this->front_; }

// Run execute method of first in line command.
// Execute is non-blocking and has to be called until it returns 1.
int8_t CircularCommandQueue::process(DFRobotC4001Hub *parent) {
  if (!is_empty()) {
    return this->commands_[this->front_]->execute(parent);
  } else {
    return true;
  }
}

}  // namespace dfrobot_c4001
}  // namespace esphome
