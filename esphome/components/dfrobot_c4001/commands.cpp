#include "dfrobot_c4001.h"
#include "commands.h"

namespace esphome {
namespace dfrobot_c4001 {
static const char *const TAG = "dfrobot_c4001.commands";

// returns
//  negative number: failed, abs(return value) is the number of errors that occured
//  1: success
//  0: not done yet
// if this->retry_power_stop = true then command reported "sensor not stopped", need to send sensorStop command
uint8_t Command::execute(DFRobotC4001Hub *parent) {
  this->parent_ = parent;
  // send command is separate from the rest of the state machine
  if (this->state_ == STATE_CMD_SEND) {
    this->done_ = false;
    this->error_ = false;
    this->retry_power_stop = false;
    if (this->parent_->send_cmd_(this->cmd_.c_str(), this->cmd_duration_ms_)) {
      this->state_ = STATE_WAIT_ECHO;
    }
    if (this->cmd_ == "resetSystem") {
      // resetSystem command only returns prompt, bypass central part of state machine
      on_message();
      ESP_LOGV(TAG, "Send Cmd: Shortcutting Reset System Command");
      this->state_ = STATE_WAIT_PROMPT;
    }
    return 0;
  }
  // surround state machine with a successful read message
  if (this->parent_->read_message_()) {
    this->read_buffer_ = this->parent_->read_buffer_;
    switch (this->state_) {
      case STATE_WAIT_ECHO:
        if (strstr(this->read_buffer_, this->cmd_.c_str())) {
          this->state_ = STATE_PROCESS;
        }
        break;
      case STATE_PROCESS:
        if (strstr(this->read_buffer_, "Error")) {
          this->error_ = true;
          this->state_ = STATE_WAIT_PROMPT;
          break;
        }
        if (strstr(this->read_buffer_, "sensor is not stopped")) {
          // Let queue know we need to stop the sensor and then retry this command
          this->retry_power_stop = true;
          break;
        }
        // process message
        on_message();
        if (this->done_) {
          this->state_ = STATE_WAIT_PROMPT;
        }
        break;
      case STATE_WAIT_PROMPT:
        if (strstr(this->read_buffer_, "DFRobot:/>")) {
          if (this->error_ || this->retry_power_stop) {
            if (this->retries_left_ > 0) {
              this->retries_left_ -= 1;
              this->error_count_ -= 1;
              if (this->retry_power_stop) {
                ESP_LOGD(TAG, "Command Retry: Sensor not stopped");
                // allow command to be used again
                this->state_ = STATE_CMD_SEND;
                // this command is done, but the queue needs to send a commandStop first
                return this->error_count_ < 0 ? this->error_count_ : 1;
              } else {
                ESP_LOGD(TAG, "Command Retry");
                // reset state to send command again
                this->state_ = STATE_CMD_SEND;
                return 0;  // command not done
              }
            } else {
              ESP_LOGE(TAG, "Command Failure");
              this->error_count_ -= 1;
            }
          } else {
            ESP_LOGV(TAG, "Send Cmd: Complete: %s", this->cmd_.c_str());
          }
          // Command done
          this->state_ = STATE_DONE;
          return this->error_count_ < 0 ? this->error_count_ : 1;
        }
        break;
      default:  // STATE_DONE
        // Command done
        return this->error_count_ < 0 ? this->error_count_ : 1;
    }
  }
  // check for timeout
  if (millis() - this->parent_->ts_last_cmd_sent_ > this->timeout_ms_) {
    if (this->retries_left_ > 0) {
      this->retries_left_ -= 1;
      ESP_LOGD(TAG, "Command timeout: Retrying");
      this->state_ = STATE_CMD_SEND;
      this->error_count_ -= 1;
      return 0;  // command not done
    } else {
      ESP_LOGE(TAG, "Command Failure: %s", this->cmd_.c_str());
      this->state_ = STATE_DONE;
      this->error_count_ -= 1;
      // Command done
      return this->error_count_ < 0 ? this->error_count_ : 1;
    }
  }
  return 0;
}

void Command::on_message() {
  if (strstr(this->parent_->read_buffer_, "Done"))
    this->done_ = true;
}

uint8_t ReadStateCommand::execute(DFRobotC4001Hub *parent) {
  this->parent_ = parent;
  if (this->parent_->read_message_()) {
    if (strstr(this->parent_->read_buffer_, "$DFHPD,0, , , *")) {
      this->parent_->set_occupancy(false);
      ESP_LOGV(TAG, "Recv Rpt: Occupancy Clear");
      return true;  // Command done
    } else if (strstr(this->parent_->read_buffer_, "$DFHPD,1, , , *")) {
      this->parent_->set_occupancy(true);
      ESP_LOGV(TAG, "Recv Rpt: Occupancy Detected");
      return true;  // Command done
    }
  }
  if (millis() - this->parent_->ts_last_cmd_sent_ > this->timeout_ms_) {
    return true;  // Command done, timeout
  }
  return false;  // Command not done yet.
}

ResetSystemCommand::ResetSystemCommand() { this->cmd_ = "resetSystem"; }

void ResetSystemCommand::on_message() {
  // this command responds with nothing, not even a command echo
  this->done_ = true;  // command is done
}

PowerCommand::PowerCommand(bool power_on) { this->cmd_ = power_on ? "sensorStart" : "sensorStop"; };

SetUartOutputCommand::SetUartOutputCommand() { this->cmd_ = "setUartOutput 1 1 1 1.0"; };

SetRunAppCommand::SetRunAppCommand() { this->cmd_ = "setRunApp 0"; }

}  // namespace dfrobot_c4001
}  // namespace esphome
