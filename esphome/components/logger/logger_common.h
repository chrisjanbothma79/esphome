#pragma once

#include "esphome/core/defines.h"

namespace esphome {
namespace logger {

// Maximum log message text size (power of 2 for efficiency)
constexpr size_t LOG_MSG_SIZE = 128;

// Size for temporary text storage with null terminator
constexpr size_t LOG_MSG_SIZE_WITH_NULL = LOG_MSG_SIZE + 1;

}  // namespace logger
}  // namespace esphome