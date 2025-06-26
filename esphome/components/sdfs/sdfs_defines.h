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

// #define RET_STATUS_OK 0
// #define RET_STATUS_FAIL 1
// #define RET_STATUS_NOTCRITICAL 2

#define ERR_TYPE_FRAMEWORK 1  // Errors from framework
#define ERR_TYPE_FILESYS 2    // Errors from filesysytems
#define ERR_TYPE_LOCAL 3      // Local errors

typedef enum { C_NONE, C_MMC, C_SD, C_SDHC, C_UNKNOWN } card_type_t;

typedef enum { RET_STATUS_OK = 0, RET_STATUS_FAIL = 1, RET_STATUS_NOCARD = 2 } sdcard_status_t;

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
typedef enum {
  FR_OK = 0,              /* (0) Succeeded */
  FR_DISK_ERR,            /* (1) A hard error occurred in the low level disk I/O layer */
  FR_INT_ERR,             /* (2) Assertion failed */
  FR_NOT_READY,           /* (3) The physical drive cannot work */
  FR_NO_FILE,             /* (4) Could not find the file */
  FR_NO_PATH,             /* (5) Could not find the path */
  FR_INVALID_NAME,        /* (6) The path name format is invalid */
  FR_DENIED,              /* (7) Access denied due to prohibited access or directory full */
  FR_EXIST,               /* (8) Access denied due to prohibited access */
  FR_INVALID_OBJECT,      /* (9) The file/directory object is invalid */
  FR_WRITE_PROTECTED,     /* (10) The physical drive is write protected */
  FR_INVALID_DRIVE,       /* (11) The logical drive number is invalid */
  FR_NOT_ENABLED,         /* (12) The volume has no work area */
  FR_NO_FILESYSTEM,       /* (13) There is no valid FAT volume */
  FR_MKFS_ABORTED,        /* (14) The f_mkfs() aborted due to any problem */
  FR_TIMEOUT,             /* (15) Could not get a grant to access the volume within defined period */
  FR_LOCKED,              /* (16) The operation is rejected according to the file sharing policy */
  FR_NOT_ENOUGH_CORE,     /* (17) LFN working buffer could not be allocated */
  FR_TOO_MANY_OPEN_FILES, /* (18) Number of open files > FF_FS_LOCK */
  FR_INVALID_PARAMETER    /* (19) Given parameter is invalid */
} fs_error;

typedef uint8_t FRESULT;

#elif defined(USE_ARDUINO)
#include "ff.h"
typedef FATFS fsys_t;
#else
#include "ff.h"
typedef FATFS fsys_t;
#endif
