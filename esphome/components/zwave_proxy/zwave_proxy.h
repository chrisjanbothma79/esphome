#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace zwave_proxy {

enum ZWaveResponseTypes : uint8_t {
  ZWAVE_FRAME_TYPE_ACK = 0x06,
  ZWAVE_FRAME_TYPE_CAN = 0x18,
  ZWAVE_FRAME_TYPE_NAK = 0x15,
  ZWAVE_FRAME_TYPE_START = 0x01,
};

enum ZWaveParsingState : uint8_t {
  ZWAVE_PARSING_STATE_WAIT_START,
  ZWAVE_PARSING_STATE_WAIT_LENGTH,
  ZWAVE_PARSING_STATE_WAIT_TYPE,
  ZWAVE_PARSING_STATE_WAIT_COMMAND_ID,
  ZWAVE_PARSING_STATE_WAIT_PAYLOAD,
  ZWAVE_PARSING_STATE_WAIT_CHECKSUM,
  ZWAVE_PARSING_STATE_SEND_ACK,
  ZWAVE_PARSING_STATE_SEND_CAN,
  ZWAVE_PARSING_STATE_SEND_NAK,
};

class ZWaveProxy : public uart::UARTDevice, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void send_frame(std::vector<uint8_t> &data);

 protected:
  void parse_byte_(uint8_t byte);
  void parse_start_(uint8_t byte);
  bool response_handler_();

  uint8_t buffer_[257];         // Fixed buffer for incoming data: max length = 255 + 2 (start of frame and checksum)
  uint8_t buffer_index_{0};     // Index for populating the data buffer
  uint8_t checksum_{0};         // Checksum of the frame being parsed
  uint8_t end_frame_after_{0};  // Payload reception ends after this index
  ZWaveParsingState parsing_state_{ZWAVE_PARSING_STATE_WAIT_START};
};

}  // namespace zwave_proxy
}  // namespace esphome
