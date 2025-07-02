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

// normalized_mireds is between 0.0 (coldest) and 1.0 (warmest)
static float normalized_mireds_to_kelvin(float normalized_mireds, float coldest_mireds, float warmest_mireds) {
  // normalized color temperature must apply to mireds, it's not linear in Kelvin!
  float ct_mireds = coldest_mireds - normalized_mireds * (coldest_mireds - warmest_mireds);
  return utils::mireds_to_kelvin(ct_mireds);
}

}  // namespace utils
}  // namespace neewerlight_ct
}  // namespace esphome
