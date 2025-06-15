#pragma once
#include "esphome/core/defines.h"
#include "sdfs.h"
#include "sdfs_defines.h"
#if defined(USE_SDSPI_MODE) && !defined(USE_ESP8266)
// #include "esphome/components/spi/spi.h"

#if defined(USE_ARDUINO)
#include <SPI.h>
#else
#include "driver/spi_master.h"
#endif

// #include "ffconf.h"
#include "diskio_impl.h"
#include "spi_connector.h"
// #include <FS.h>
// #include <SD.h>
// #include "FSImpl.h"

extern "C" {
#include "ff.h"
}

namespace esphome {
namespace sdfs {

// typedef enum { CARD_NONE, CARD_MMC, CARD_SD, CARD_SDHC, CARD_UNKNOWN } sdcard_type_t;
typedef enum { ST_NOTINIT, ST_INIT, ST_MOUNT } slot_status_t;

typedef enum {
  GO_IDLE_STATE = 0,
  SEND_OP_COND = 1,
  SEND_CID = 2,
  SEND_RELATIVE_ADDR = 3,
  SEND_SWITCH_FUNC = 6,
  SEND_IF_COND = 8,
  SEND_CSD = 9,
  STOP_TRANSMISSION = 12,
  SEND_STATUS = 13,
  SET_BLOCKLEN = 16,
  READ_BLOCK_SINGLE = 17,
  READ_BLOCK_MULTIPLE = 18,
  SEND_NUM_WR_BLOCKS = 22,
  SET_WR_BLK_ERASE_COUNT = 23,
  WRITE_BLOCK_SINGLE = 24,
  WRITE_BLOCK_MULTIPLE = 25,
  APP_OP_COND = 41,
  APP_CLR_CARD_DETECT = 42,
  APP_CMD = 55,
  READ_OCR = 58,
  CRC_ON_OFF = 59
} ardu_sdcard_command_t;

typedef struct {
  sdfs::SpiConnector *conn;
  int frequency;
  char *base_path;
  sdcard_type_t type;
  unsigned long sectors;
  bool supports_crc;
  int status;
} esp_ardu_sdcard_t;

// static esp_ardu_sdcard_t *s_cards[FF_VOLUMES] = {NULL};

uint8_t sdspi_init(SpiConnector *);
void sdspi_uninit(uint8_t);
FATFS *sdspi_mount(uint8_t, const char *, uint8_t, bool);
void sdspi_unmount(uint8_t);

static const ff_diskio_impl_t *sdimpl_init();
unsigned long sdGetSectorsCount(uint8_t);
DSTATUS ff_sd_initialize(uint8_t);
sdcard_type_t ff_sd_type(uint8_t);
size_t ff_sd_sectors(uint8_t);
// uint8_t sdcard_uninit(uint8_t);
// bool sd_read_raw(uint8_t, uint8_t *, uint32_t);
// bool sd_write_raw(uint8_t, uint8_t *, uint32_t);
char sdTransaction(uint8_t, char, unsigned int, unsigned int *);

char CRC7(const char *data, int length);
unsigned short CRC16(const char *data, int length);

}  // namespace sdfs
}  // namespace esphome
#endif