#pragma once

#include <cstdint>
#include <vector>

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

struct NeewerBleMessage {
  explicit NeewerBleMessage() {
    cmd = 0;
    type = 0;
    payload.clear();
  }

  uint8_t cmd;
  uint8_t type;
  std::vector<uint8_t> payload;
};

static const uint8_t COMMAND = 0x78;
static const uint8_t CT_BRIGHTNESS = 0x87;
static const uint8_t TURN_ON_OFF = 0x81;

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
