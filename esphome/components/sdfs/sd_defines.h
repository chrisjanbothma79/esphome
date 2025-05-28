#pragma once

#define FREE(ptr) \
  do { \
    free(ptr); \
    ptr = NULL; \
  } while (0)

#define IS_LAST_ERR(x, y) (((this->last_err_ >> 16) == x) && ((this->last_err_ & 0x0000ffff) == y))
#define SET_RC(x, y, str) \
  do { \
    this->last_err_ = (x << 16) | y; \
    ESP_LOGE(TAG, str " (0x%x).", y); \
  } while (0)

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
