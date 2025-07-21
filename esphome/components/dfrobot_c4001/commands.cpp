#include "dfrobot_c4001.h"
#include "commands.h"

#include <sstream>

namespace esphome {
namespace dfrobot_c4001 {
static const char *const TAG = "dfrobot_c4001.commands";

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
      std::string message = "";
      this->on_message();
      ESP_LOGV(TAG, "Send Cmd: Shortcutting Reset System Command");
      this->state_ = STATE_WAIT_PROMPT;
    }
    return false;
  }
  // surround state machine with a successful read message
  if (this->parent_->read_message_()) {
    this->read_buffer_ = this->parent_->read_buffer_;
    std::string message(this->read_buffer_);
    switch (this->state_) {
      case STATE_WAIT_ECHO:
        if (str_startswith(message, this->cmd_)) {
          this->state_ = STATE_PROCESS;
        }
        break;
      case STATE_PROCESS:
        if (str_startswith(message, "Error")) {
          this->error_ = true;
          this->state_ = STATE_WAIT_PROMPT;
          break;
        }
        if (str_startswith(message, "sensor is not stopped")) {
          // Let queue know we need to stop the sensor and then retry this command
          this->retry_power_stop = true;
          break;
        }
        // process message
        this->on_message();
        if (this->done_) {
          this->state_ = STATE_WAIT_PROMPT;
        }
        break;
      case STATE_WAIT_PROMPT:
        if (message.find("DFRobot:/>") != std::string::npos) {
          if (this->error_ || this->retry_power_stop) {
            if (this->retries_left_ > 0) {
              this->retries_left_ -= 1;
              this->error_count_ -= 1;
              if (this->retry_power_stop) {
                ESP_LOGD(TAG, "Command Retry: Sensor not stopped");
                // allow command to be used again
                this->state_ = STATE_CMD_SEND;
                // this command is done, but the queue needs to send a commandStop first
                return this->error_count_ < 0 ? this->error_count_ : true;
              } else {
                ESP_LOGD(TAG, "Command Retry");
                // reset state to send command again
                this->state_ = STATE_CMD_SEND;
                return false;  // command not done
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
          return this->error_count_ < 0 ? this->error_count_ : true;
        }
        break;
      default:  // STATE_DONE
        // Command done
        return this->error_count_ < 0 ? this->error_count_ : true;
    }
  }
  // check for timeout
  if (millis() - this->parent_->ts_last_cmd_sent_ > this->timeout_ms_) {
    if (this->retries_left_ > 0) {
      this->retries_left_ -= 1;
      ESP_LOGD(TAG, "Command timeout: Retrying");
      this->state_ = STATE_CMD_SEND;
      this->error_count_ -= 1;
      return false;  // command not done
    } else {
      ESP_LOGE(TAG, "Command Failure: %s", this->cmd_.c_str());
      this->state_ = STATE_DONE;
      this->error_count_ -= 1;
      // Command done
      return this->error_count_ < 0 ? this->error_count_ : true;
    }
  }
  return false;
}

void Command::on_message() {
  if (strcmp(this->read_buffer_, "Done") == 0)
    this->done_ = true;  // command is done
}

uint8_t ReadStateCommand::execute(DFRobotC4001Hub *parent) {
  this->parent_ = parent;

  char *token;

  if (this->parent_->read_message_()) {
    std::string message(this->parent_->read_buffer_);
    if (str_startswith(message, "$DFHPD,0, , , *")) {
      this->parent_->set_occupancy(false);
      ESP_LOGV(TAG, "Recv Rpt: Occupancy Clear");
      return true;  // Command done
    } else if (str_startswith(message, "$DFHPD,1, , , *")) {
      this->parent_->set_occupancy(true);
      ESP_LOGV(TAG, "Recv Rpt: Occupancy Detected");
      return true;  // Command done
    } else if (str_startswith(message, "$DFDMD")) {
      strtok(this->parent_->read_buffer_, ",");
      token = strtok(NULL, ",");
      auto target = parse_number<uint8_t>(token);
      strtok(NULL, ",");
      token = strtok(NULL, ",");
      auto target_distance = parse_number<float>(token);
      token = strtok(NULL, ",");
      auto target_speed = parse_number<float>(token);
      token = strtok(NULL, ",");
      auto target_energy = parse_number<float>(token);
      if (target.has_value() && target.value() == 1) {
        // one target is detected
        if (target_distance.has_value() && target_speed.has_value() && target_energy.has_value()) {
          // 1 target is detected, that is all this sensor can do
          this->parent_->set_target_distance(target_distance.value());
          this->parent_->set_target_speed(target_speed.value());
          this->parent_->set_target_energy(target_energy.value());
          this->parent_->set_occupancy(true);
          ESP_LOGV(TAG, "Recv Rpt: Target Detected, Dist=%.3f, Speed=%.3f, Energy=%d", target_distance.value(),
                   target_speed.value(), (uint) target_energy.value());
          return true;  // command completed successfully
        } else {
          ESP_LOGD(TAG, "Error parsing Distance and Speed Detection Output");
          return true;  // command done with error
        }
      } else if (target.has_value() && target == 0) {
        // no target is detected
        this->parent_->set_target_distance(0.0);
        this->parent_->set_target_speed(0.0);
        this->parent_->set_target_energy(0.0);
        this->parent_->set_occupancy(false);
        ESP_LOGV(TAG, "Recv Rpt: No Target");
        return true;  // command completed successfully
      }
    }
  }
  if (millis() - this->parent_->ts_last_cmd_sent_ > this->timeout_ms_) {
    return 1;  // Command done, timeout
  }
  return 0;  // Command not done yet.
}

void ReadStateCommand::on_message() {}

PowerCommand::PowerCommand(bool power_on) {
  if (power_on) {
    this->cmd_ = "sensorStart";
  } else {
    this->cmd_ = "sensorStop";
  }
};

GetRangeCommand::GetRangeCommand() { this->cmd_ = "getRange"; }

void GetRangeCommand::on_message() {
  char *token;

  token = strtok(this->read_buffer_, " ");
  if (strcmp(token, "Done") == 0) {
    if (!this->min_range_.has_value() || !this->max_range_.has_value()) {
      ESP_LOGD(TAG, "Failed to parse response");
      this->error_ = true;  // command is done
    } else {
      this->parent_->set_min_range(this->min_range_.value(), false);
      this->parent_->set_max_range(this->max_range_.value(), false);
      this->done_ = true;  // command is done
    }
  } else if (strcmp(token, "Response") == 0) {
    token = strtok(NULL, " ");
    this->min_range_ = parse_number<float>(token);
    token = strtok(NULL, " ");
    this->max_range_ = parse_number<float>(token);
  }
}

SetRangeCommand::SetRangeCommand(float min_range, float max_range) {
  this->cmd_ = str_sprintf("setRange %.3f %.3f", min_range, max_range);
};

GetTrigRangeCommand::GetTrigRangeCommand() { this->cmd_ = "getTrigRange"; }

void GetTrigRangeCommand::on_message() {
  char *token;

  token = strtok(this->read_buffer_, " ");
  if (strcmp(token, "Done") == 0) {
    if (!this->trigger_range_.has_value()) {
      ESP_LOGD(TAG, "Failed to parse response");
      this->error_ = true;  // command is done
    } else {
      this->parent_->set_trigger_range(this->trigger_range_.value(), false);
      this->done_ = true;  // command is done
    }
  } else if (strcmp(token, "Response") == 0) {
    token = strtok(NULL, " ");
    this->trigger_range_ = parse_number<float>(token);
  }
}

SetTrigRangeCommand::SetTrigRangeCommand(float trigger_range) {
  this->cmd_ = str_sprintf("setTrigRange %.3f", trigger_range);
};

GetSensitivityCommand::GetSensitivityCommand() { this->cmd_ = "getSensitivity"; }

void GetSensitivityCommand::on_message() {
  char *token;

  token = strtok(this->read_buffer_, " ");
  if (strcmp(token, "Done") == 0) {
    if (!this->hold_sensitivity_.has_value() || !this->trigger_sensitivity_.has_value()) {
      ESP_LOGD(TAG, "Failed to parse response");
      this->error_ = true;  // command is done
    } else {
      this->parent_->set_hold_sensitivity(this->hold_sensitivity_.value(), false);
      this->parent_->set_trigger_sensitivity(this->trigger_sensitivity_.value(), false);
      this->done_ = true;  // command is done
    }
  } else if (strcmp(token, "Response") == 0) {
    token = strtok(NULL, " ");
    this->hold_sensitivity_ = parse_number<float>(token);
    token = strtok(NULL, " ");
    this->trigger_sensitivity_ = parse_number<float>(token);
  }
}

SetSensitivityCommand::SetSensitivityCommand(float hold_sensitivity, float trigger_sensitivity) {
  this->cmd_ = str_sprintf("setSensitivity %.0f %.0f", round(hold_sensitivity), round(trigger_sensitivity));
};

GetLatencyCommand::GetLatencyCommand() { this->cmd_ = "getLatency"; }

void GetLatencyCommand::on_message() {
  char *token;

  token = strtok(this->read_buffer_, " ");
  if (strcmp(token, "Done") == 0) {
    if (!this->on_latency_.has_value() || !this->off_latency_.has_value()) {
      ESP_LOGD(TAG, "Failed to parse response");
      this->error_ = true;  // command is done
    } else {
      this->parent_->set_on_latency(this->on_latency_.value(), false);
      this->parent_->set_off_latency(this->off_latency_.value(), false);
      this->done_ = true;  // command is done
    }
  } else if (strcmp(token, "Response") == 0) {
    token = strtok(NULL, " ");
    this->on_latency_ = parse_number<float>(token);
    token = strtok(NULL, " ");
    this->off_latency_ = parse_number<float>(token);
  }
}

SetLatencyCommand::SetLatencyCommand(float on_latency, float off_latency) {
  this->cmd_ = str_sprintf("setLatency %.3f %.3f", on_latency, off_latency);
};

GetInhibitTimeCommand::GetInhibitTimeCommand() { this->cmd_ = "getInhibit"; }

void GetInhibitTimeCommand::on_message() {
  char *token;

  token = strtok(this->read_buffer_, " ");
  if (strcmp(token, "Done") == 0) {
    if (!this->inhibit_time_.has_value()) {
      ESP_LOGD(TAG, "Failed to parse response");
      this->error_ = true;  // command is done
    } else {
      this->parent_->set_inhibit_time(this->inhibit_time_.value(), false);
      this->done_ = true;  // command is done
    }
  } else if (strcmp(token, "Response") == 0) {
    token = strtok(NULL, " ");
    this->inhibit_time_ = parse_number<float>(token);
  }
}

SetInhibitTimeCommand::SetInhibitTimeCommand(float inhibit) { this->cmd_ = str_sprintf("setInhibit %.3f", inhibit); };

SetUartOutputCommand::SetUartOutputCommand() { this->cmd_ = "setUartOutput 1 1 1 1.0"; };

FactoryResetCommand::FactoryResetCommand() { this->cmd_ = "resetCfg"; }

void FactoryResetCommand::on_message() {
  if (strcmp(this->read_buffer_, "Done") == 0) {
    this->parent_->setup_module();  // reload settings
    this->parent_->config_load();
    this->done_ = true;  // command is done
  }
}

ResetSystemCommand::ResetSystemCommand(bool read_config) {
  this->read_config_ = read_config;
  this->cmd_ = "resetSystem";
}

void ResetSystemCommand::on_message() {
  // this command responds with nothing, not even a command echo
  if (this->read_config_)
    this->parent_->config_load();
  this->done_ = true;  // command is done
}

SaveCfgCommand::SaveCfgCommand() { this->cmd_ = "saveConfig"; }

void SaveCfgCommand::on_message() {
  if (strcmp(this->read_buffer_, "Done") == 0) {
    this->parent_->config_load();
    this->done_ = true;  // command is done
  }
}

SetRunAppCommand::SetRunAppCommand() { this->cmd_ = "setRunApp 0"; }

}  // namespace dfrobot_c4001
}  // namespace esphome
