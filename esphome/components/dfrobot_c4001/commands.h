#pragma once

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dfrobot_c4001 {
class DFRobotC4001Hub;
// Enumeration for Command States
enum CommandState {
  STATE_CMD_SEND = 0,  // command needs to be sent
  STATE_WAIT_ECHO,     // command was sent, now waiting for command echo
  STATE_PROCESS,       // command in process
  STATE_WAIT_PROMPT,   // waiting for prompt, teminates this transaction
  STATE_DONE,
};

// Use command queue and time stamps to avoid blocking.
// When component has run time, check if minimum time (1s) between
// commands has passed. After that run a command from the queue.
class Command {
 public:
  virtual ~Command() = default;
  virtual uint8_t execute(DFRobotC4001Hub *parent);
  virtual void on_message();
  uint8_t retry_power_stop{false};

 protected:
  DFRobotC4001Hub *parent_{nullptr};
  uint8_t state_{STATE_CMD_SEND};
  uint8_t done_{false};
  uint8_t error_{false};
  std::string cmd_;
  char *read_buffer_{nullptr};
  int8_t error_count_{0};
  int8_t retries_left_{2};
  uint32_t cmd_duration_ms_{10};
  uint32_t timeout_ms_{1500};
};

class ReadStateCommand : public Command {
 public:
  uint8_t execute(DFRobotC4001Hub *parent) override;
};

class PowerCommand : public Command {
 public:
  PowerCommand(bool power_on);
};

class SetUartOutputCommand : public Command {
 public:
  SetUartOutputCommand();
};

class ResetSystemCommand : public Command {
 public:
  ResetSystemCommand();
  void on_message() override;
};

class SetRunAppCommand : public Command {
 public:
  SetRunAppCommand();
};

}  // namespace dfrobot_c4001
}  // namespace esphome
