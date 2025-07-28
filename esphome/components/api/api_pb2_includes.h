#pragma once

// This file provides includes needed by the generated protobuf code
// when using pointer optimizations for component-specific types

#ifdef USE_CLIMATE
#include "esphome/components/climate/climate_mode.h"
#include "esphome/components/climate/climate_traits.h"
#endif

#ifdef USE_LIGHT
#include "esphome/components/light/light_traits.h"
#endif

#ifdef USE_FAN
#include "esphome/components/fan/fan_traits.h"
#endif

#ifdef USE_SELECT
#include "esphome/components/select/select_traits.h"
#endif

#ifdef USE_MEDIA_PLAYER
#include "esphome/components/media_player/media_player_traits.h"
#endif

// Standard library includes that might be needed
#include <set>
#include <vector>
#include <string>
