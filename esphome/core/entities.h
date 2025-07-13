#pragma once

// This file is not used by the runtime, instead, a version is generated during
// compilation with only the relevant feature flags for the current build.
//
// This file is only used by static analyzers and IDEs.

namespace esphome {
namespace switch_ {
class Switch;
}
namespace binary_sensor {
class BinarySensor;
}
using entities_t = std::tuple<switch_::Switch *, binary_sensor::BinarySensor *>;
}  // namespace esphome
