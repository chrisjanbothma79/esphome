#include "nec_protocol.h"
#include "esphome/core/log.h"

namespace esphome {
namespace remote_base {

static const char *const TAG = "remote.nec";

// NEC IR Protocol (old URL https://techdocs.altium.com/display/FPGA/NEC%2bInfrared%2bTransmission%2bProtocol)
// Protocol Reference:
// https://files.doc.altium.com/sites/default/files/wiki_attachments/299480/Legacy%20-%20FPGA%20Design.pdf
// https://www.infineon.com/dgdl/Infineon-AN2023-03_Infrared_Remote_Control_and_Saving_Last_Speed_Setting-ApplicationNotes-v01_00-EN.pdf?fileId=8ac78c8c8d1b852e018d21ff0aa71feb
// // NOLINT https://www.renesas.com/ja/document/apn/1184-remote-control-ir-receiver-decoder

// Timing constants in microseconds
static const uint16_t AGC_HIGH_US = 9000;         // AGC burst: 9ms HIGH
static const uint16_t LONG_PAUSE_LOW_US = 4500;   // After AGC burst: 4.5ms LOW
static const uint16_t SHORT_PAUSE_LOW_US = 2250;  // After AGC burst: 2.25ms LOW
static const uint16_t BIT_HIGH_US = 562;          // Bit HIGH duration: 562.5µs
static const uint16_t BIT_ONE_LOW_US = 1687;      // Logic '1': 562.5µs HIGH + 1687.5µs LOW
static const uint16_t BIT_ZERO_LOW_US = 562;      // Logic '0': 562.5µs HIGH + 562.5µs LOW
const uint16_t NEC_SPACE_INTER_FRAME_US = 40000;  // Inter-frame space: 40ms
const uint32_t NEC_SPACE_AGC_REPEAT_US = 96187;   // AGC Repeat space: ~96.1875ms

void NECProtocol::encode(RemoteTransmitData *dst, const NECData &data) {
  ESP_LOGV(TAG, "Encoding %s", this->get_protocol_type_and_fields_str(data).c_str());

  if (data.type != NECCodeType::FRAME && data.type != NECCodeType::REPEAT) {
    ESP_LOGE(TAG, "Only FRAME and REPEAT code types are supported.");
  }

  // FRAME: AGC Header (2) + Address bits (32) + Command bits (32) + Stop bit (2)
  // REPEAT: AGC Repeat header (2) + Stop bit (2)
  uint32_t dst_len = data.type == NECCodeType::FRAME ? 68 : 4;
  dst->reserve(dst_len);
  dst->set_carrier_frequency(38222);

  if (data.type == NECCodeType::REPEAT) {
    // AGC Repeat header (shorter version of the initial AGC header)
    dst->item(AGC_HIGH_US, SHORT_PAUSE_LOW_US);  // Shortened AGC header
    dst->mark(BIT_HIGH_US);                      // Stop bit to complete the repeat code
    return;
  }

  // AGC Header (start of frame)
  dst->item(AGC_HIGH_US, LONG_PAUSE_LOW_US);

  // Encode Address
  for (uint16_t mask = 1; mask; mask <<= 1) {
    if (data.address & mask) {
      dst->item(BIT_HIGH_US, BIT_ONE_LOW_US);  // Logic '1'
    } else {
      dst->item(BIT_HIGH_US, BIT_ZERO_LOW_US);  // Logic '0'
    }
  }

  // Encode Command
  for (uint16_t mask = 1; mask; mask <<= 1) {
    if (data.command & mask) {
      dst->item(BIT_HIGH_US, BIT_ONE_LOW_US);  // Logic '1'
    } else {
      dst->item(BIT_HIGH_US, BIT_ZERO_LOW_US);  // Logic '0'
    }
  }

  // Stop bit to end the message frame
  dst->mark(BIT_HIGH_US);
}

optional<NECData> NECProtocol::decode(RemoteReceiveData src) {
  NECData data{
      .address = 0,
      .command = 0,
      .repeats = 0,
      .type = NECCodeType::REPEAT,
  };

  // Validate the AGC header (start of frame or repeat code)
  if (!src.expect_mark(AGC_HIGH_US)) {
    return {};
  }

  // Validate the short pause (repeat code)
  if (src.expect_space(SHORT_PAUSE_LOW_US)) {
    // Validate the stop bit of repeat code
    if (!src.expect_mark(BIT_HIGH_US)) {
      return {};
    }

    ESP_LOGVV(TAG, "Decoded repeat code");

    // Repeat code received
    return data;
  }

  // Validate the long pause (message frame)
  if (!src.expect_space(LONG_PAUSE_LOW_US)) {
    return {};
  }

  // Validate address bits
  for (uint16_t mask = 1; mask; mask <<= 1) {
    if (src.expect_item(BIT_HIGH_US, BIT_ONE_LOW_US)) {
      data.address |= mask;  // Logic '1'
    } else if (src.expect_item(BIT_HIGH_US, BIT_ZERO_LOW_US)) {
      // Logic '0', since the address is already initialized with 0, `data.address &= ~mask;` is not needed
    } else {
      return {};
    }
  }

  // Validate command bits
  for (uint16_t mask = 1; mask; mask <<= 1) {
    if (src.expect_item(BIT_HIGH_US, BIT_ONE_LOW_US)) {
      data.command |= mask;  // Logic '1'
    } else if (src.expect_item(BIT_HIGH_US, BIT_ZERO_LOW_US)) {
      // Logic '0', since the command is already initialized with 0, `data.command &= ~mask;` is not needed
    } else {
      return {};
    }
  }

  // Validate the final stop bit (end of the message frame)
  if (!src.expect_mark(BIT_HIGH_US)) {
    return {};
  }

  // Frame received
  data.type = NECCodeType::FRAME;

  if (!NECProtocol::is_command_valid(data)) {
    ESP_LOGW(TAG, "Decoded command invalid: 0x%04X", data.command);
  }

  ESP_LOGVV(TAG, "Decoded %s, src_idx=%" PRIu32 ", src_sz=%" PRIi32,
            this->get_protocol_type_and_fields_str(data).c_str(), src.get_index(), src.size());

  return data;
}

void NECProtocol::dump(const NECData &data) {
  ESP_LOGI(TAG, "Received %s", this->get_protocol_type_and_fields_str(data).c_str());
}

std::string NECProtocol::get_protocol_type_and_fields_str(const NECData &data) {
  std::string debug_message = "NEC ";
  switch (data.type) {
    case NECCodeType::FRAME:
      debug_message += str_sprintf("Frame (%u-bit address)", NECProtocol::is_address_extended(data) ? 16 : 8);
      break;
    case NECCodeType::REPEAT:
      debug_message += "Repeat Code";
      break;
    default:
      debug_message += "Unknown";
  }

  if (data.type != NECCodeType::REPEAT) {
    debug_message += ": address=0x";
    if (NECProtocol::is_address_extended(data)) {
      debug_message += str_sprintf("%04X", data.address);
    } else {
      debug_message += str_sprintf("%02X, address#=0x%02X", data.address_bytes.lo, data.address_bytes.hi);
    }

    debug_message += str_sprintf(", command=0x%02X, command#=0x%02X, command_valid=%s,", data.command_bytes.lo,
                                 data.command_bytes.hi, YESNO(NECProtocol::is_command_valid(data)));

    if (data.type != NECCodeType::FRAME) {
      debug_message += str_sprintf(" repeats=%u, type=%u", data.repeats, static_cast<uint8_t>(data.type));
    }
  }

  return debug_message;
}

void NECBinarySensor::dump_config() {
  LOG_BINARY_SENSOR("", "Remote receiver NEC binary sensor", this);
  ESP_LOGCONFIG(TAG, "  Repeat timeout: %u ms", this->repeat_timeout_ms_);
}

bool NECBinarySensor::matches(RemoteReceiveData src) {
  auto proto = NECProtocol();
  auto res = proto.decode(src);

  if (!res.has_value()) {
    return false;
  }

  bool last_waiting_state = this->currently_on_and_waiting_for_repeat_code_;

  switch (res.value().type) {
    case NECCodeType::FRAME:
      this->currently_on_and_waiting_for_repeat_code_ = res.value() == this->data_;
      break;

    case NECCodeType::REPEAT:
      // Repeat codes are ignored, state remains unchanged
      break;

    default:
      this->currently_on_and_waiting_for_repeat_code_ = false;
      break;
  }

  if (last_waiting_state && !this->currently_on_and_waiting_for_repeat_code_) {
    ESP_LOGV(TAG, "Received unexpected signal");
    this->publish_state(false);
    this->cancel_timeout("repeat");
  }

  return this->currently_on_and_waiting_for_repeat_code_;
}

bool NECBinarySensor::on_receive(RemoteReceiveData src) {
  if (!this->matches(src)) {
    return false;
  }

  this->publish_state(true);
  this->set_timeout("repeat", this->repeat_timeout_ms_, [this]() {
    this->currently_on_and_waiting_for_repeat_code_ = false;
    this->publish_state(false);
  });

  return true;
}

}  // namespace remote_base
}  // namespace esphome
