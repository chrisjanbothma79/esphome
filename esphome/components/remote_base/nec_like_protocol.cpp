#include "nec_like_protocol.h"
#include "esphome/core/log.h"

namespace esphome {
namespace remote_base {

static const char *const TAG = "remote.nec_like";

// NEC timing constants (µs)
static const uint32_t HEADER_HIGH_US = 9000;
static const uint32_t HEADER_LOW_US = 4500;
static const uint32_t BIT_HIGH_US = 560;
static const uint32_t BIT_ONE_LOW_US = 1680;
static const uint32_t BIT_ZERO_LOW_US = 600;

void NECLikeProtocol::encode(RemoteTransmitData *dst, const NECLikeData &data) {
  ESP_LOGD(TAG, "Sending NEC_Like raw bits, length=%u", data.bits_.size());
  dst->reserve(2 + data.bits_.size() * 2 + 1);
  dst->set_carrier_frequency(38000);

  // Header
  dst->item(HEADER_HIGH_US, HEADER_LOW_US);
  // Bits
  for (size_t i = 0; i < data.bits_.size(); ++i) {
    dst->mark(BIT_HIGH_US);
    if (data.bits_[i]) {
      dst->space(BIT_ONE_LOW_US);
    } else {
      dst->space(BIT_ZERO_LOW_US);
    }
  }
  // Final mark
  dst->mark(BIT_HIGH_US);
}

optional<NECLikeData> NECLikeProtocol::decode(RemoteReceiveData src) {
  NECLikeData data;
  data.bits_.clear();

  // Expect header
  if (!src.expect_item(HEADER_HIGH_US, HEADER_LOW_US))
    return {};

  // Decode bits
  while (true) {
    if (src.expect_item(BIT_HIGH_US, BIT_ONE_LOW_US)) {
      data.bits_.push_back(true);
    } else if (src.expect_item(BIT_HIGH_US, BIT_ZERO_LOW_US)) {
      data.bits_.push_back(false);
    } else {
      break;
    }
  }
  // Optional trailing mark
  src.expect_mark(BIT_HIGH_US);

  return data;
}

void NECLikeProtocol::dump(const NECLikeData &data) {
  // Convert bits to hex for logging
  std::string hex_str;
  for (size_t i = 0; i + 8 <= data.bits_.size(); i += 8) {
    uint8_t byte = 0;
    for (size_t j = 0; j < 8; ++j)
      byte = (byte << 1) | (data.bits_[i + j]);
    char buf[4];
    snprintf(buf, sizeof(buf), "%02X", byte);
    if (!hex_str.empty())
      hex_str += ' ';
    hex_str += buf;
  }
  ESP_LOGI(TAG, "Received NEC_Like (%u bits): %s", data.bits_.size(), hex_str.c_str());
}

void NECLikeProtocol::swap_nibbles(NECLikeData &data) {
  size_t n = data.bits_.size();
  size_t full_bytes = n / 8;
  // copy original bitstream
  std::vector<bool> orig = data.bits_;
  // For each full byte, swap high and low nibble in-place
  for (size_t i = 0; i < full_bytes; ++i) {
    for (size_t bit = 0; bit < 8; ++bit) {
      size_t src_bit = i * 8 + ((bit + 4) % 8);
      data.bits_[i * 8 + bit] = orig[src_bit];
    }
  }
}

}  // namespace remote_base
}  // namespace esphome
