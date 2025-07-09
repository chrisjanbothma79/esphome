#include "brennenstuhl_protocol.h"
#include "esphome/core/log.h"

#include <cinttypes>

namespace esphome {
namespace remote_base {

static const char *const TAG = "remote.brennenstuhl";

// receiver timings [µs]
constexpr uint32_t START_PULSE_MIN = 200;
constexpr uint32_t START_PULSE_MAX = 500;
constexpr uint32_t START_SYMBOL_MIN = 2600;
constexpr uint32_t START_SYMBOL_MAX = 2700;
constexpr uint32_t DATA_SYMBOL_MIN = 1500;
constexpr uint32_t DATA_SYMBOL_MAX = 1600;

// transmitter timings [µs]
constexpr uint32_t PW_SHORT_US = 390;
constexpr uint32_t PW_LONG_US = 1160;
constexpr uint32_t PW_START_US = 2300;

// number of data bits
constexpr uint32_t N_BITS = 24;

// numbar of required symbols = 2 x (start + N_BITS) = 50
constexpr uint32_t N_SYMBOLS_REQ = 2u * (N_BITS + 1);

// number of bs codes within received frame
constexpr int32_t N_FRAME_CODES = 4;

// decoder finite-state-machine
enum class RxSt { START_PULSE, START_SYMBOL, PULSE, DATA_SYMBOL };

// validates if a pulse or symbol is within expected range
static bool validate_timing(int32_t val, int32_t val_min, int32_t val_max) {
  return ((val_min <= val && val <= val_max) ? true : false);
}

void BrennenstuhlProtocol::encode(RemoteTransmitData *dst, const BrennenstuhlData &data) {
  uint32_t code = data.code;
  dst->reserve(N_SYMBOLS_REQ * N_FRAME_CODES + 1);
  for (uint32_t kc = 0; kc < N_FRAME_CODES; kc++) {
    dst->item(PW_SHORT_US, PW_START_US);
    for (uint32_t ic = 0; ic < N_BITS; ic++) {
      uint32_t bit = ((code) >> (N_BITS - 1 - ic)) & 1;
      if (1 == bit) {
        dst->item(PW_LONG_US, PW_SHORT_US);
      } else {
        dst->item(PW_SHORT_US, PW_LONG_US);
      }
    }
  }
}

optional<BrennenstuhlData> BrennenstuhlProtocol::decode(RemoteReceiveData src) {
  int32_t n_received = src.size();
  BrennenstuhlData data{
      .code = 0,
  };
  // suppress noisy frames, at least a complete bs_code should be available
  if (n_received > N_SYMBOLS_REQ) {
    int32_t bs_codes[4] = {0, 0, 0, 0};
    int32_t bs_cnt = 0;
    int32_t bs_idx = -1;
    int32_t bit_cnt = 0;
    int32_t abs_pre = 0;
    RxSt fsm = RxSt::START_PULSE;
    for (int32_t ic = 0; ic < n_received && bs_cnt < N_FRAME_CODES; ic++) {
      int32_t act = src[ic];
      int32_t abs_act = std::abs(act);
      switch (fsm) {
        case RxSt::START_PULSE: {
          if ((act > 0) && validate_timing(abs_act, START_PULSE_MIN, START_PULSE_MAX)) {
            bs_codes[bs_cnt] = 0;
            bit_cnt = 0;
            abs_pre = abs_act;
            fsm = RxSt::START_SYMBOL;
          }
          break;
        }
        case RxSt::START_SYMBOL: {
          if ((act < 0) && validate_timing(abs_pre + abs_act, START_SYMBOL_MIN, START_SYMBOL_MAX)) {
            fsm = RxSt::PULSE;
          } else {
            fsm = RxSt::START_PULSE;
          }
          break;
        }
        case RxSt::PULSE: {
          if (act > 0) {
            abs_pre = abs_act;
            fsm = RxSt::DATA_SYMBOL;
          } else {
            fsm = RxSt::START_PULSE;
          }
          break;
        }
        case RxSt::DATA_SYMBOL: {
          if ((act < 0) && validate_timing(abs_pre + abs_act, DATA_SYMBOL_MIN, DATA_SYMBOL_MAX)) {
            bs_codes[bs_cnt] <<= 1;
            bs_codes[bs_cnt] += (abs_act < abs_pre) ? 1 : 0;
            if (++bit_cnt < N_BITS) {
              fsm = RxSt::PULSE;
            } else {
              bs_cnt++;
              fsm = RxSt::START_PULSE;
            }
          } else {
            fsm = RxSt::START_PULSE;
          }
          break;
        }
      }
    }
    if (bs_cnt > 0) {
      uint8_t identical_max = 0;
      for (int32_t ic = 0; ic < bs_cnt; ic++) {
        uint8_t identical_cnt = 0;
        for (int32_t jc = 0; jc < bs_cnt; jc++) {
          identical_cnt += (bs_codes[ic] == bs_codes[jc]) ? 1 : 0;
        }
        if (identical_cnt > identical_max) {
          identical_max = identical_cnt;
          bs_idx = ic;
        }
      }
      if (bs_idx > -1) {
        data.code = bs_codes[bs_idx];
        return data;
      }
    }
  }
  return {};
}

void BrennenstuhlProtocol::dump(const BrennenstuhlData &data) {
  ESP_LOGI(TAG, "Brennenstuhl: code=0x%x", data.code);
}

}  // namespace remote_base
}  // namespace esphome
