#pragma once
#include "esphome/core/log.h"

// #define SPI_CALL_TRACE
#ifndef USE_ESP8266
#include "ff.h"
#endif

#define FREE(ptr) \
  do { \
    free(ptr); \
    (ptr) = NULL; \
  } while (0)

#define ERR_TYPE_FRAMEWORK 1  // Errors from framework   // NOLINT
#define ERR_TYPE_FILESYS 2    // Errors from filesysytems // NOLINT
#define ERR_TYPE_LOCAL 3      // Local errors // NOLINT

#define IS_LAST_ERR(x, y) (((this->last_err_ >> 16) == (x)) && ((this->last_err_ & 0x0000ffff) == (y)))

namespace esphome {
namespace sdfs {

// enum class card_type_t { C_NONE, C_MMC, C_SD, C_SDHC, C_UNKNOWN };
// using enum card_type_t;
enum class SdCardType { C_NONE, C_MMC, C_SD, C_SDHC, C_UNKNOWN };

#ifndef USE_ESP8266
using enum SdCardType;
#endif

enum class SdCardStatus : uint8_t { RET_STATUS_OK = 0, RET_STATUS_FAIL = 1, RET_STATUS_NOCARD = 2 };

#ifndef USE_ESP8266
using enum SdCardStatus;
#endif

}  // namespace sdfs
}  // namespace esphome

#if !defined(USE_ESP8266)
using fsys_t = FATFS;

#elif defined(USE_ESP8266)
#include "FsLib/FsVolume.h"
using fsys_t = FsVolume;
using FRESULT = uint8_t;

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

#endif
