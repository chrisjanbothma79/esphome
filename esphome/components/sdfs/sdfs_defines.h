#pragma once

#include "esphome/core/log.h"

#define FREE(ptr) \
  do { \
    free(ptr); \
    ptr = NULL; \
  } while (0)

#define IS_LAST_ERR(x, y) (((this->last_err_ >> 16) == x) && ((this->last_err_ & 0x0000ffff) == y))
#define SET_RC(x, y, str) \
  do { \
    this->last_err_ = (x << 16) | y; \
    ESP_LOGE(TAG, str " (0x%x)%s.", y, esp_err_to_name(y)); \
  } while (0)

#ifdef SPI_CALL_TRACE
#define DEBUG_TRACE(msg, ...) \
  do { \
    ESP_LOGD(TAG, msg, ##__VA_ARGS__); \
  } while (0)
#else
#define DEBUG_TRACE(msg, ...)
#endif

#define ERR_TYPE_FRAMEWORK 1  // Errors from framework
#define ERR_TYPE_FILESYS 2    // Errors from filesysytems
#define ERR_TYPE_LOCAL 3      // Local errors

typedef enum {
  RC_OK = 1,
  RC_NO_MEM = 2,
  RC_INVALID_ARG = 3,
  RC_NO_CARD = 4,
  RC_NOT_FORMATED = 5,
  RC_UNKNOWN = 6
} local_rc_t;

#if defined(USE_ESP8266)
#include "FsLib/FsVolume.h"
typedef FsVolume fsys_t;
#elif defined(USE_ARDUINO)
#include "ff.h"
typedef FATFS fsys_t;
#else
#include "ff.h"
typedef FATFS fsys_t;
#endif
