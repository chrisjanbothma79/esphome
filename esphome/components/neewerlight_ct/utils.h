#pragma once

#include <cmath>

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

}  // namespace utils
}  // namespace neewerlight_ct
}  // namespace esphome
