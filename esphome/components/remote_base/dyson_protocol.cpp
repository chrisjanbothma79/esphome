#include "dyson_protocol.h"
#include "esphome/core/log.h"

#include <cinttypes>

namespace esphome {
namespace remote_base {

static const char *const TAG = "remote.dyson";

// timings [µs]
constexpr uint32_t PW_SHORT_US = 700;
constexpr uint32_t PW_LONG_US = 1400;
constexpr uint32_t PW_START_US = 2300;

// number of data bits
constexpr int32_t N_DYSON_BITS = 15;

// numbar of required symbols
constexpr uint32_t N_SYMBOLS_REQ = 2u * (N_DYSON_BITS + 1);

void DysonProtocol::encode(RemoteTransmitData *dst, const DysonData &data) {
  uint32_t code = (data.code << 2) + (data.index & 3);
  dst->reserve(N_SYMBOLS_REQ + 1);
  dst->item(PW_START_US, PW_SHORT_US);
  for (uint16_t mask = (1 << (N_DYSON_BITS - 1)); mask != 0; mask >>= 1) {
    if (1 == (mask & code)) {
      dst->item(PW_SHORT_US, PW_LONG_US);
    } else {
      dst->item(PW_SHORT_US, PW_SHORT_US);
    }
  }
  dst->mark(PW_SHORT_US);  // final carrier pulse
}

optional<DysonData> DysonProtocol::decode(RemoteReceiveData src) {
  int32_t n_received = src.size();
  uint16_t raw_code = 0;
  DysonData data{
      .code = 0,
      .index = 0,
  };
  if (n_received < N_SYMBOLS_REQ)
    return {};
  if (!src.expect_item(PW_START_US, PW_SHORT_US))
    return {};
  for (uint16_t mask = (1 << (N_DYSON_BITS - 1)); mask != 0; mask >>= 1) {
    if (src.expect_item(PW_SHORT_US, PW_SHORT_US)) {  // zero detected
      raw_code &= ~mask;
    } else if (src.expect_item(PW_SHORT_US, PW_LONG_US)) {  // one detected
      raw_code |= mask;
    } else {  // invalid data
      return {};
    }
  }
  data.code = raw_code >> 2;  // extract the button code
  data.index = raw_code & 3;  // extract the rolling index counter
  if (src.expect_mark(PW_SHORT_US)) {
    return data;
  }
  return {};
}

void DysonProtocol::dump(const DysonData &data) {
  ESP_LOGI(TAG, "Dyson: code=0x%x rolling index=%d", data.code, data.index);
}

}  // namespace remote_base
}  // namespace esphome
