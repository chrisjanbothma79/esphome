#pragma once

#include "esphome/core/defines.h"
#include "esphome/components/ota_base/ota_backend.h"

namespace esphome {
namespace ota {

// Import types from ota_base namespace for backward compatibility
using ota_base::OTABackend;
using ota_base::OTAComponent;
using ota_base::OTAResponseTypes;
using ota_base::OTAState;

// Re-export specific enum values for backward compatibility
// OTAState values
static constexpr auto OTA_COMPLETED = ota_base::OTA_COMPLETED;
static constexpr auto OTA_STARTED = ota_base::OTA_STARTED;
static constexpr auto OTA_IN_PROGRESS = ota_base::OTA_IN_PROGRESS;
static constexpr auto OTA_ABORT = ota_base::OTA_ABORT;
static constexpr auto OTA_ERROR = ota_base::OTA_ERROR;

// OTAResponseTypes values
static constexpr auto OTA_RESPONSE_OK = ota_base::OTA_RESPONSE_OK;
static constexpr auto OTA_RESPONSE_REQUEST_AUTH = ota_base::OTA_RESPONSE_REQUEST_AUTH;
static constexpr auto OTA_RESPONSE_HEADER_OK = ota_base::OTA_RESPONSE_HEADER_OK;
static constexpr auto OTA_RESPONSE_AUTH_OK = ota_base::OTA_RESPONSE_AUTH_OK;
static constexpr auto OTA_RESPONSE_UPDATE_PREPARE_OK = ota_base::OTA_RESPONSE_UPDATE_PREPARE_OK;
static constexpr auto OTA_RESPONSE_BIN_MD5_OK = ota_base::OTA_RESPONSE_BIN_MD5_OK;
static constexpr auto OTA_RESPONSE_RECEIVE_OK = ota_base::OTA_RESPONSE_RECEIVE_OK;
static constexpr auto OTA_RESPONSE_UPDATE_END_OK = ota_base::OTA_RESPONSE_UPDATE_END_OK;
static constexpr auto OTA_RESPONSE_SUPPORTS_COMPRESSION = ota_base::OTA_RESPONSE_SUPPORTS_COMPRESSION;
static constexpr auto OTA_RESPONSE_CHUNK_OK = ota_base::OTA_RESPONSE_CHUNK_OK;
static constexpr auto OTA_RESPONSE_ERROR_MAGIC = ota_base::OTA_RESPONSE_ERROR_MAGIC;
static constexpr auto OTA_RESPONSE_ERROR_UPDATE_PREPARE = ota_base::OTA_RESPONSE_ERROR_UPDATE_PREPARE;
static constexpr auto OTA_RESPONSE_ERROR_AUTH_INVALID = ota_base::OTA_RESPONSE_ERROR_AUTH_INVALID;
static constexpr auto OTA_RESPONSE_ERROR_WRITING_FLASH = ota_base::OTA_RESPONSE_ERROR_WRITING_FLASH;
static constexpr auto OTA_RESPONSE_ERROR_UPDATE_END = ota_base::OTA_RESPONSE_ERROR_UPDATE_END;
static constexpr auto OTA_RESPONSE_ERROR_INVALID_BOOTSTRAPPING = ota_base::OTA_RESPONSE_ERROR_INVALID_BOOTSTRAPPING;
static constexpr auto OTA_RESPONSE_ERROR_WRONG_CURRENT_FLASH_CONFIG =
    ota_base::OTA_RESPONSE_ERROR_WRONG_CURRENT_FLASH_CONFIG;
static constexpr auto OTA_RESPONSE_ERROR_WRONG_NEW_FLASH_CONFIG = ota_base::OTA_RESPONSE_ERROR_WRONG_NEW_FLASH_CONFIG;
static constexpr auto OTA_RESPONSE_ERROR_ESP8266_NOT_ENOUGH_SPACE =
    ota_base::OTA_RESPONSE_ERROR_ESP8266_NOT_ENOUGH_SPACE;
static constexpr auto OTA_RESPONSE_ERROR_ESP32_NOT_ENOUGH_SPACE = ota_base::OTA_RESPONSE_ERROR_ESP32_NOT_ENOUGH_SPACE;
static constexpr auto OTA_RESPONSE_ERROR_NO_UPDATE_PARTITION = ota_base::OTA_RESPONSE_ERROR_NO_UPDATE_PARTITION;
static constexpr auto OTA_RESPONSE_ERROR_MD5_MISMATCH = ota_base::OTA_RESPONSE_ERROR_MD5_MISMATCH;
static constexpr auto OTA_RESPONSE_ERROR_RP2040_NOT_ENOUGH_SPACE = ota_base::OTA_RESPONSE_ERROR_RP2040_NOT_ENOUGH_SPACE;
static constexpr auto OTA_RESPONSE_ERROR_UNKNOWN = ota_base::OTA_RESPONSE_ERROR_UNKNOWN;

#ifdef USE_OTA_STATE_CALLBACK
using ota_base::OTAGlobalCallback;

// Deprecated: Use ota_base::get_global_ota_callback() instead
// Will be removed after 2025-12-30 (6 months from 2025-06-30)
[[deprecated("Use ota_base::get_global_ota_callback() instead")]] inline OTAGlobalCallback *get_global_ota_callback() {
  return ota_base::get_global_ota_callback();
}

// Deprecated: Use ota_base::register_ota_platform() instead
// Will be removed after 2025-12-30 (6 months from 2025-06-30)
[[deprecated("Use ota_base::register_ota_platform() instead")]] inline void register_ota_platform(
    OTAComponent *ota_caller) {
  ota_base::register_ota_platform(ota_caller);
}
#endif

}  // namespace ota
}  // namespace esphome
