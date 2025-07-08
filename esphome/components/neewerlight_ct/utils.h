#pragma once

#include <cmath>
#include <vector>

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {
namespace utils {

static const char *const TAG = "neewerlight_ct.component";

// if input is 0, output is 0
static float mireds_to_kelvin(float mireds) {
  if (mireds == 0.0f) {
    return 0.0f;
  }
  return 1e6f / mireds;
}

static int mireds_to_kelvin_int(float mireds) { return std::round(mireds_to_kelvin(mireds)); }

// normalized_mireds is between 0.0 (coldest) and 1.0 (warmest)
static float normalized_mireds_to_kelvin(float normalized_mireds, float coldest_mireds, float warmest_mireds) {
  // normalized color temperature must apply to mireds, it's not linear in Kelvin!
  float ct_mireds = coldest_mireds - normalized_mireds * (coldest_mireds - warmest_mireds);
  return mireds_to_kelvin(ct_mireds);
}

static int normalized_mireds_to_kelvin_int(float normalized_mireds, float coldest_mireds, float warmest_mireds) {
  return std::round(normalized_mireds_to_kelvin(normalized_mireds, coldest_mireds, warmest_mireds));
}

static int brightness_to_percent(float brightness) {
  if (brightness < 0.0f) {
    return 0;
  } else if (brightness > 1.0f) {
    return 100;
  } else {
    return std::round(brightness * 100.0f);
  }
}

static uint8_t checksum(const std::vector<uint8_t> &data) {
  uint64_t checksum = 0;
  for (uint8_t byte : data) {
    checksum += byte;
  }
  uint8_t checksum_byte = checksum & 0xFF;
  return checksum_byte;
}

}  // namespace utils
}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32
