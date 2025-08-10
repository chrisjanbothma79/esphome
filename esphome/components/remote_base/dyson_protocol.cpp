#include "dyson_protocol.h"
#include "esphome/core/log.h"

#include <cinttypes>

namespace esphome {
namespace remote_base {

static const char *const TAG = "remote.dyson";

// pulsewidth [µs]
constexpr uint32_t PW_MARK_US = 780;
constexpr uint32_t PW_SHORT_US = 720;
constexpr uint32_t PW_LONG_US = 1500;
constexpr uint32_t PW_START_US = 2280;

// number of data bits of dyson code
constexpr int32_t N_DYSON_BITS = 15;

// required symbols in transmit buffer
constexpr uint32_t N_SYMBOLS_REQ = 2u * (N_DYSON_BITS + 1);

void DysonProtocol::encode(RemoteTransmitData *dst, const DysonData &data) {
  uint32_t raw_code = (data.code << 2) + (data.index & 3);
  ESP_LOGI("dyson", "data.code=%04x data.index=%d --> raw_code %04x", data.code, data.index, raw_code);
  dst->set_carrier_frequency(36000);
  dst->reserve(N_SYMBOLS_REQ + 1);
  dst->item(PW_START_US, PW_SHORT_US);
  for (uint16_t mask = (1 << (N_DYSON_BITS - 1)); mask != 0; mask >>= 1) {
    if (mask == (mask & raw_code)) {
      dst->item(PW_MARK_US, PW_LONG_US);
    } else {
      dst->item(PW_MARK_US, PW_SHORT_US);
    }
  }
  dst->mark(PW_MARK_US);  // final carrier pulse
}

optional<DysonData> DysonProtocol::decode(RemoteReceiveData src) {
  int32_t n_received = src.size();
  uint16_t raw_code = 0;
  DysonData data{
      .code = 0,
      .index = 0,
  };
  if (n_received < N_SYMBOLS_REQ)
    return {};  // invalid frame length
  if (!src.expect_item(PW_START_US, PW_SHORT_US))
    return {};  // start not found
  for (uint16_t mask = (1 << (N_DYSON_BITS - 1)); mask != 0; mask >>= 1) {
    if (src.expect_item(PW_MARK_US, PW_SHORT_US)) {
      raw_code &= ~mask;  // zero detected
    } else if (src.expect_item(PW_MARK_US, PW_LONG_US)) {
      raw_code |= mask;  // one detected
    } else {
      return {};  // invalid data item
    }
  }
  data.code = raw_code >> 2;          // extract the button code
  data.index = raw_code & 3;          // extract the rolling index counter
  if (src.expect_mark(PW_MARK_US)) {  // the closing mark
    return data;
  }
  return {};  // frame not complete
}

void DysonProtocol::dump(const DysonData &data) {
  ESP_LOGI(TAG, "Dyson: code=0x%x rolling index=%d", data.code, data.index);
}

}  // namespace remote_base
}  // namespace esphome
