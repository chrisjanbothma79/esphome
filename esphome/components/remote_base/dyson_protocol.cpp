#include "dyson_protocol.h"
#include "esphome/core/log.h"

#include <cinttypes>

namespace esphome {
namespace remote_base {

static const char *const TAG = "remote.dyson";

// receiver timings [µs]
// range start pulse
constexpr uint32_t START_PULSE_min = 2250;
constexpr uint32_t START_PULSE_max = 2350;

// range start symbol
constexpr uint32_t START_ITEM_min = 650;
constexpr uint32_t START_ITEM_max = 750;

// range pulse
constexpr uint32_t PULSE_min = 750;
constexpr uint32_t PULSE_max = 850;

// range data symbol for "one"
constexpr uint32_t ITEM_ONE_min = 1350;
constexpr uint32_t ITEM_ONE_max = 1450;

// range data symbol for "zero"
constexpr uint32_t ITEM_ZERO_min = 650;
constexpr uint32_t ITEM_ZERO_max = 750;

// transmitter timings [µs]
constexpr uint32_t PW_SHORT_US = 700;
constexpr uint32_t PW_LONG_US = 1400;
constexpr uint32_t PW_START_US = 2300;

// number of data bits
constexpr int32_t N_DYSON_BITS = 15;

// numbar of required symbols = 2 x (start + N_BITS) = 50
constexpr uint32_t N_SYMBOLS_REQ = 2u * (N_DYSON_BITS + 1);

// number of dyson codes within received frame
constexpr int32_t N_FRAME_CODES = 2;

// decoder statemachine
enum class RxSt { START_PULSE, START_ITEM, PULSE, ITEM };

// validates if a pulse or symbol is within expected range
inline bool validate_timing(int32_t val, int32_t val_min, int32_t val_max) {
  return ((val_min <= val && val <= val_max) ? true : false);
}

// The encode() member function reserves and fills a complete frame, to be send. The Dyson
// RC receivers demand a frame with a start-symbol followed by 2 repeated codes.
void DysonProtocol::encode(RemoteTransmitData *dst, const DysonData &data) {
  uint32_t code = (data.code << 2) + (data.roll & 3);
  dst->reserve(N_SYMBOLS_REQ * N_FRAME_CODES + 1);
  dst->item(PW_START_US, PW_SHORT_US);  // start symbol
  for (uint32_t ic = 0; ic < N_DYSON_BITS; ic++) {
    uint32_t bit = ((code) >> (N_DYSON_BITS - 1 - ic)) & 1;
    if (1 == bit) {
      dst->item(PW_SHORT_US, PW_LONG_US);
    } else {
      dst->item(PW_SHORT_US, PW_SHORT_US);
    }
  }
  dst->mark(PW_SHORT_US);
}

// The decode() member function extracts Dyson codes from the received frame.
// returns the best code (the one with the most identical codes)
optional<DysonData> DysonProtocol::decode(RemoteReceiveData src) {
  int32_t n_received = src.size();
  DysonData data{
      .code = 0,
      .roll = 0,
  };

  if (n_received > N_SYMBOLS_REQ) {
    int32_t dyson_codes[N_FRAME_CODES] = {0, 0};  // internal dyson codes
    int32_t dyson_code = 0;
    int32_t dyson_cnt = 0;   // number of dyson codes found within frame
    int32_t dyson_idx = -1;  // index to best code
    int32_t n_bit = 0;
    RxSt fsm = RxSt::START_PULSE;
    for (int32_t ic = 0; ic < n_received && dyson_cnt < N_FRAME_CODES; ic++) {
      int32_t act = src[ic];
      int32_t abs_act = std::abs(act);
      switch (fsm) {
        case RxSt::START_PULSE: {  // find start-pulse
          if ((act > 0) && validate_timing(abs_act, START_PULSE_min, START_PULSE_max)) {
            dyson_code = 0;
            n_bit = 0;
            fsm = RxSt::START_ITEM;
          }
          break;
        }
        case RxSt::START_ITEM: {  // find start-item
          if ((act < 0) && validate_timing(abs_act, START_ITEM_min, START_ITEM_max)) {
            fsm = RxSt::PULSE;
          } else {  // invalid start, abort frame
            fsm = RxSt::START_PULSE;
          }
          break;
        }
        case RxSt::PULSE: {  // extract pulse (positive value)
          if ((act > 0) && validate_timing(abs_act, PULSE_min, PULSE_max)) {
            fsm = RxSt::ITEM;
          } else {  // invalid pulse, abort frame
            fsm = RxSt::START_PULSE;
          }
          break;
        }
        case RxSt::ITEM: {  // extract data item
          fsm = RxSt::START_PULSE;
          if ((act < 0) && validate_timing(abs_act, ITEM_ONE_min, ITEM_ONE_max)) {
            dyson_code = ((dyson_code) << 1) + 1;
            if (++n_bit < N_DYSON_BITS) {
              fsm = RxSt::PULSE;
            } else {  // code complete
              dyson_codes[dyson_cnt] = dyson_code;
              dyson_cnt++;
            }
          } else if ((act < 0) && validate_timing(abs_act, ITEM_ZERO_min, ITEM_ZERO_max)) {
            dyson_code = ((dyson_code) << 1);
            if (++n_bit < N_DYSON_BITS) {
              fsm = RxSt::PULSE;
            } else {  // code complete
              dyson_codes[dyson_cnt] = dyson_code;
              dyson_cnt++;
            }
          }
          break;
        }
      }
    }
    if (dyson_cnt > 0) {  // raw codes found, locate best
      uint8_t identical_max = 0;
      for (int32_t ic = 0; ic < dyson_cnt; ic++) {
        uint8_t identical_cnt = 0;
        for (int32_t jc = 0; jc < dyson_cnt; jc++) {
          identical_cnt += (dyson_codes[ic] == dyson_codes[jc]) ? 1 : 0;
        }
        if (identical_cnt > identical_max) {
          identical_max = identical_cnt;
          dyson_idx = ic;  // save index to best code
        }
      }
      if (dyson_idx > -1) {  // extract code and rolling index from raw code
        data.code = dyson_codes[dyson_idx] >> 2;
        data.roll = dyson_codes[dyson_idx] & 3;
        return data;
      }
    }
  }
  return {};  // decoding failed
}

void DysonProtocol::dump(const DysonData &data) { ESP_LOGI(TAG, "Dyson: code=0x%x roll=%d", data.code, data.roll); }

}  // namespace remote_base
}  // namespace esphome
