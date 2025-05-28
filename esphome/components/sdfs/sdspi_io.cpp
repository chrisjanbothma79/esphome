#include "sdspi_io.h"
#if defined(USE_SDSPI_MODE) && !defined(USE_ESP8266)
#include "dirent.h"
#include "esp_system.h"
#include "esp_log.h"

#if defined(USE_ESP_IDF)
#include "vfs_fat_internal.h"
#endif

extern "C" {
#include "ff.h"
#include "diskio.h"
#if ESP_IDF_VERSION_MAJOR > 3
#include "diskio_impl.h"
#endif
#include "esp_vfs_fat.h"
}

namespace esphome {
namespace sdfs {

// #if ARDUHAL_LOG_LEVEL >= ARDUHAL_LOG_LEVEL_ERROR
// const char *fs_err2str[] = {"(0) Succeeded",
//                             "(1) A hard error occurred in the low level disk I/O layer",
//                             "(2) Assertion failed",
//                             "(3) The physical drive cannot work",
//                             "(4) Could not find the file",
//                             "(5) Could not find the path",
//                             "(6) The path name format is invalid",
//                             "(7) Access denied due to prohibited access or directory full",
//                             "(8) Access denied due to prohibited access",
//                             "(9) The file/directory object is invalid",
//                             "(10) The physical drive is write protected",
//                             "(11) The logical drive number is invalid",
//                             "(12) The volume has no work area",
//                             "(13) There is no valid FAT volume",
//                             "(14) The f_mkfs() aborted due to any problem",
//                             "(15) Could not get a grant to access the volume within defined period",
//                             "(16) The operation is rejected according to the file sharing policy",
//                             "(17) LFN working buffer could not be allocated",
//                             "(18) Number of open files > FF_FS_LOCK",
//                             "(19) Given parameter is invalid"};
// #endif

#define LOCK_SPI s_cards[pdrv]->conn->beginTransaction()
#define UNLOCK_SPI s_cards[pdrv]->conn->endTransaction()

static esp_ardu_sdcard_t *s_cards[FF_VOLUMES] = {NULL};
// static uint32_t def_sector_size = 512;
static const char *TAG = "sdspi_io";
static size_t allocation_unit_size = 16 * 1024;
FATFS *fs_handler;

// uint32_t millis() { return (uint32_t) (esp_timer_get_time() / 1000ULL); }

sdcard_type_t ff_sd_type(uint8_t pdrv) { return s_cards[pdrv]->type; }
size_t ff_sd_sectors(uint8_t pdrv) { return s_cards[pdrv]->sectors; }

uint8_t sdspi_init(SpiConnector *connector_) {
  uint8_t pdrv = FF_DRV_NOT_USED;
  // ESP_LOGD(TAG, "ArduinoSdFatDriver/init_host");
  // this->connector_->begin();
  // TODO: check for SPI initilized ?

  if (ff_diskio_get_drive(&pdrv) != ESP_OK || pdrv == FF_DRV_NOT_USED) {
    return pdrv;
  }

  esp_ardu_sdcard_t *card = (esp_ardu_sdcard_t *) malloc(sizeof(esp_ardu_sdcard_t));
  if (!card) {
    return FF_DRV_NOT_USED;
  }

  card->base_path = NULL;
  // card->frequency = this->frequency_;
  card->conn = connector_;
  card->supports_crc = true;
  card->type = CARD_NONE;
  card->status = STA_NOINIT;
  s_cards[pdrv] = card;

  static const ff_diskio_impl_t *sd_impl = sdimpl_init();
  ff_diskio_register(pdrv, sd_impl);

  // DSTATUS res = ff_sd_initialize(pdrv);
  // if ((res & STA_NOINIT) == STA_NOINIT) {
  //   status_ = ST_MOUNT;
  //   ESP_LOGD(TAG, "Slot initilized pdrv=%d. Status NOT INIT", pdrv_);
  // } else {
  //   status_ = ST_INIT;
  //   ESP_LOGD(TAG, "Slot initilized pdrv=%d. Status INIT", pdrv_);
  // }
  return pdrv;
}

void sdspi_uninit(uint8_t pdrv) {
  if (pdrv != FF_DRV_NOT_USED) {
    esp_err_t err;
    // _impl->mountpoint(NULL);
    sdcard_unmount(pdrv);
    esp_ardu_sdcard_t *card = s_cards[pdrv];

    LOCK_SPI;
    sdTransaction(pdrv, GO_IDLE_STATE, 0, NULL);
    ff_diskio_register(pdrv, NULL);
    UNLOCK_SPI;
    s_cards[pdrv] = NULL;

    if (card->base_path) {
      err = esp_vfs_fat_unregister_path(card->base_path);
      free(card->base_path);
    }
    free(card);
  }
}

/* ********************************************************************
 *
 *       SPI cmd's
 *
 * */
bool sdWait(uint8_t pdrv, int timeout) {
  char resp;
  uint32_t start = millis();

  do {
    resp = s_cards[pdrv]->conn->transfer(0xFF);
  } while (resp == 0x00 && (millis() - start) < (unsigned int) timeout);

  if (!resp) {
    ESP_LOGW(TAG, "Wait Failed");
  }
  return (resp > 0x00);
}

void sdStop(uint8_t pdrv) { s_cards[pdrv]->conn->write(0xFD); }

// void sdDeselectCard(uint8_t pdrv) {
//   esp_ardu_sdcard_t *card = s_cards[pdrv];
// }

bool sdSelectCard(uint8_t pdrv) {
  esp_ardu_sdcard_t *card = s_cards[pdrv];
  bool s = sdWait(pdrv, 500);
  if (!s) {
    ESP_LOGE(TAG, "Select Failed");
    return false;
  }
  return true;
}

char sdCommand(uint8_t pdrv, char cmd, unsigned int arg, unsigned int *resp) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGVV(TAG, "sdCommand, cmd=%d, arg=0x%x", cmd, arg);
#endif

  char token;
  esp_ardu_sdcard_t *card = s_cards[pdrv];

  for (int f = 0; f < 3; f++) {
    if (cmd == SEND_NUM_WR_BLOCKS || cmd == SET_WR_BLK_ERASE_COUNT || cmd == APP_OP_COND ||
        cmd == APP_CLR_CARD_DETECT) {
      token = sdCommand(pdrv, APP_CMD, 0, NULL);
      if (token > 1) {
        break;
      }
      if (!sdSelectCard(pdrv)) {
        token = 0xFF;
        break;
      }
    }

    char cmdPacket[7];
    cmdPacket[0] = cmd | 0x40;
    cmdPacket[1] = arg >> 24;
    cmdPacket[2] = arg >> 16;
    cmdPacket[3] = arg >> 8;
    cmdPacket[4] = arg;
    if (card->supports_crc || cmd == GO_IDLE_STATE || cmd == SEND_IF_COND) {
      cmdPacket[5] = (CRC7(cmdPacket, 5) << 1) | 0x01;
    } else {
      cmdPacket[5] = 0x01;
    }
    cmdPacket[6] = 0xFF;
    card->conn->writeBytes((uint8_t *) cmdPacket, (cmd == STOP_TRANSMISSION) ? 7 : 6);

    for (int i = 0; i < 9; i++) {
      token = card->conn->transfer(0xFF);
      if (!(token & 0x80)) {
        break;
      }
    }

    if (token == 0xFF) {
      ESP_LOGW(TAG, "no token received");
      delay(100);
      sdSelectCard(pdrv);
      continue;
    } else if (token & 0x08) {
      ESP_LOGW(TAG, "crc error");
      delay(100);
      sdSelectCard(pdrv);
      continue;
    } else if (token > 1) {
      ESP_LOGW(TAG, "token error [%u] 0x%x", cmd, token);
      break;
    }

    if (cmd == SEND_STATUS && resp) {
      *resp = card->conn->transfer(0xFF);
    } else if ((cmd == SEND_IF_COND || cmd == READ_OCR) && resp) {
      *resp = card->conn->transfer32(0xFFFFFFFF);
    }
    break;
  }
  if (token == 0xFF) {
    ESP_LOGE(TAG, "Card Failed! cmd: %d", cmd);
    card->status = STA_NOINIT;
  }
#if defined(SPI_CALL_TRACE)
  ESP_LOGVV(TAG, "sdCommand return, token=%u", token);
#endif
  return token;
}

bool sdReadBytes(uint8_t pdrv, char *buffer, int length) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdReadBytes, len %d", length);
#endif
  char token;
  unsigned short crc;
  esp_ardu_sdcard_t *card = s_cards[pdrv];

  uint32_t start = millis();
  do {
    token = card->conn->transfer(0xFF);
  } while (token == 0xFF && (millis() - start) < 500);

  if (token != 0xFE) {
    return false;
  }

  card->conn->transferBytes(NULL, (uint8_t *) buffer, length);
  crc = card->conn->transfer16(0xFFFF);
  return (!card->supports_crc || crc == CRC16(buffer, length));
}

char sdWriteBytes(uint8_t pdrv, const char *buffer, char token) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdWriteBytes, token=%u", token);
#endif
  esp_ardu_sdcard_t *card = s_cards[pdrv];
  unsigned short crc = (card->supports_crc) ? CRC16(buffer, 512) : 0xFFFF;
  if (!sdWait(pdrv, 500)) {
    return false;
  }

  card->conn->write(token);
  card->conn->writeBytes((uint8_t *) buffer, 512);
  card->conn->write16(crc);
  return (card->conn->transfer(0xFF) & 0x1F);
}

/************************************************************************
 *
 *   SPI  interaction
 *
 * */

char sdTransaction(uint8_t pdrv, char cmd, unsigned int arg, unsigned int *resp) {
  if (!sdSelectCard(pdrv)) {
    return 0xFF;
  }
  char token = sdCommand(pdrv, cmd, arg, resp);
  return token;
}

bool sdReadSector(uint8_t pdrv, char *buffer, unsigned long long sector) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdReadSector, sector=%d", sector);
#endif
  for (int f = 0; f < 3; f++) {
    if (!sdSelectCard(pdrv)) {
      return false;
    }
    if (!sdCommand(pdrv, READ_BLOCK_SINGLE, (s_cards[pdrv]->type == CARD_SDHC) ? sector : sector << 9, NULL)) {
      bool success = sdReadBytes(pdrv, buffer, 512);
      if (success) {
        return true;
      }
    } else {
      break;
    }
  }
  return false;
}

bool sdReadSectors(uint8_t pdrv, char *buffer, unsigned long long sector, int count) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdReadSectors, sector=%d, count=%d", sector, count);
#endif
  for (int f = 0; f < 3;) {
    if (!sdSelectCard(pdrv)) {
      return false;
    }

    if (!sdCommand(pdrv, READ_BLOCK_MULTIPLE, (s_cards[pdrv]->type == CARD_SDHC) ? sector : sector << 9, NULL)) {
      do {
        if (!sdReadBytes(pdrv, buffer, 512)) {
          f++;
          break;
        }

        sector++;
        buffer += 512;
        f = 0;
      } while (--count);

      if (sdCommand(pdrv, STOP_TRANSMISSION, 0, NULL)) {
        ESP_LOGE(TAG, "command failed");
        break;
      }

      if (count == 0) {
        return true;
      }
    } else {
      break;
    }
  }
  return false;
}

bool sdWriteSector(uint8_t pdrv, const char *buffer, unsigned long long sector) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdWriteSector, sector=%d", sector);
#endif
  for (int f = 0; f < 3; f++) {
    if (!sdSelectCard(pdrv)) {
      return false;
    }
    if (!sdCommand(pdrv, WRITE_BLOCK_SINGLE, (s_cards[pdrv]->type == CARD_SDHC) ? sector : sector << 9, NULL)) {
      char token = sdWriteBytes(pdrv, buffer, 0xFE);

      if (token == 0x0A) {
        continue;
      } else if (token == 0x0C) {
        return false;
      }

      unsigned int resp;
      if (sdTransaction(pdrv, SEND_STATUS, 0, &resp) || resp) {
        return false;
      }
      return true;
    } else {
      break;
    }
  }
  return false;
}

bool sdWriteSectors(uint8_t pdrv, const char *buffer, unsigned long long sector, int count) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdWriteSectors, sector=%d, count=%d", sector, count);
#endif
  char token;
  const char *currentBuffer = buffer;
  unsigned long long currentSector = sector;
  int currentCount = count;
  esp_ardu_sdcard_t *card = s_cards[pdrv];

  for (int f = 0; f < 3;) {
    if (card->type != CARD_MMC) {
      if (sdTransaction(pdrv, SET_WR_BLK_ERASE_COUNT, currentCount, NULL)) {
        return false;
      }
    }

    if (!sdSelectCard(pdrv)) {
      return false;
    }

    if (!sdCommand(pdrv, WRITE_BLOCK_MULTIPLE, (card->type == CARD_SDHC) ? currentSector : currentSector << 9, NULL)) {
      do {
        token = sdWriteBytes(pdrv, currentBuffer, 0xFC);
        if (token != 0x05) {
          f++;
          break;
        }
        currentBuffer += 512;
        f = 0;
      } while (--currentCount);

      if (!sdWait(pdrv, 500)) {
        break;
      }

      if (currentCount == 0) {
        sdStop(pdrv);

        unsigned int resp;
        if (sdTransaction(pdrv, SEND_STATUS, 0, &resp) || resp) {
          return false;
        }
        return true;
      } else {
        if (sdCommand(pdrv, STOP_TRANSMISSION, 0, NULL)) {
          break;
        }

        if (token == 0x0A) {
          unsigned int writtenBlocks = 0;
          if (card->type != CARD_MMC && sdSelectCard(pdrv)) {
            if (!sdCommand(pdrv, SEND_NUM_WR_BLOCKS, 0, NULL)) {
              char acmdData[4];
              if (sdReadBytes(pdrv, acmdData, 4)) {
                writtenBlocks = acmdData[0] << 24;
                writtenBlocks |= acmdData[1] << 16;
                writtenBlocks |= acmdData[2] << 8;
                writtenBlocks |= acmdData[3];
              }
            }
          }
          currentBuffer = buffer + (writtenBlocks << 9);
          currentSector = sector + writtenBlocks;
          currentCount = count - writtenBlocks;
          continue;
        } else {
          break;
        }
      }
    } else {
      break;
    }
  }
  return false;
}

unsigned long sdGetSectorsCount(uint8_t pdrv) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdGetSectorsCount");
#endif
  bool res;

  for (int f = 0; f < 3; f++) {
    res = sdSelectCard(pdrv);
    if (!res) {
      ESP_LOGE(TAG, "sdSelectCard ERROR %d", res);
      return 0;
    }

    res = sdCommand(pdrv, SEND_CSD, 0, NULL);
    if (!res) {
      char csd[16];
      bool success = sdReadBytes(pdrv, csd, 16);
      if (success) {
        if ((csd[0] >> 6) == 0x01) {
          unsigned long size = (((unsigned long) (csd[7] & 0x3F) << 16) | ((unsigned long) csd[8] << 8) | csd[9]) + 1;
          return size << 10;
        }
        unsigned long size =
            (((unsigned long) (csd[6] & 0x03) << 10) | ((unsigned long) csd[7] << 2) | ((csd[8] & 0xC0) >> 6)) + 1;
        size <<= ((((csd[9] & 0x03) << 1) | ((csd[10] & 0x80) >> 7)) + 2);
        size <<= (csd[5] & 0x0F);
        return size >> 9;
      }
    } else {
      break;
    }
  }

  ESP_LOGV(TAG, "sdGetSectorsCount return  0");
  return 0;
}

// namespace {

// struct AcquireSPI {
//   esp_ardu_sdcard_t *card;
//   explicit AcquireSPI(esp_ardu_sdcard_t *card) : card(card) {
//     ESP_LOGD(TAG, "LOCK. AcquireSPI");
//     // card->spi->beginTransaction(SPISettings(card->frequency, MSBFIRST, SPI_MODE0));
//     card->conn->beginTransaction();
//   }
//   AcquireSPI(esp_ardu_sdcard_t *card, int frequency) : card(card) {
//     ESP_LOGD(TAG, "LOCK. cquireSPI, freq=%d",frequency);
//     // card->spi->beginTransaction(SPISettings(frequency, MSBFIRST, SPI_MODE0));
//     card->conn->beginTransaction();
//   }
//   ~AcquireSPI() {
//     // card->spi->endTransaction();
//     ESP_LOGD(TAG, "UNLOCK. AcquireSPI");
//     card->conn->endTransaction();
// }

//  private:
//   AcquireSPI(AcquireSPI const &);
//   AcquireSPI &operator=(AcquireSPI const &);
// };

// }  // namespace

/*
 * FATFS API
 * */

/**
 *    Initialize CARD with SPI interface
 */
DSTATUS ff_sd_initialize(uint8_t pdrv) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "ff_sd_initialize pdrv=%d", pdrv);
#endif
  char token;
  unsigned int resp;
  unsigned int start;
  esp_ardu_sdcard_t *card = s_cards[pdrv];

  // if (!(card->status & STA_NOINIT)) {
  //   return card->status;
  // }
  LOCK_SPI;
  for (uint8_t i = 0; i < 20; i++) {
    card->conn->transfer(0XFF);
  }

  if (!sdWait(pdrv, 500)) {
    ESP_LOGW(TAG, "sdWait fail ignored, card initialize continues");
  }

  if (sdCommand(pdrv, GO_IDLE_STATE, 0, NULL) != 1) {
    ESP_LOGW(TAG, "GO_IDLE_STATE failed");
    goto unknown_card;
  }

  token = sdTransaction(pdrv, CRC_ON_OFF, 1, NULL);
  if (token == 0x5) {
    // old card maybe
    card->supports_crc = false;
  } else if (token != 1) {
    ESP_LOGW(TAG, "CRC_ON_OFF failed: %u", token);
    goto unknown_card;
  }

  if (sdTransaction(pdrv, SEND_IF_COND, 0x1AA, &resp) == 1) {
    if ((resp & 0xFFF) != 0x1AA) {
      ESP_LOGW(TAG, "SEND_IF_COND failed: %03X", resp & 0xFFF);
      goto unknown_card;
    }

    if (sdTransaction(pdrv, READ_OCR, 0, &resp) != 1 || !(resp & (1 << 20))) {
      ESP_LOGW(TAG, "READ_OCR failed: %X", resp);
      goto unknown_card;
    }

    start = millis();
    do {
      token = sdTransaction(pdrv, APP_OP_COND, 0x40100000, NULL);
    } while (token == 1 && (millis() - start) < 1000);

    if (token) {
      ESP_LOGW(TAG, "APP_OP_COND failed: %u", token);
      goto unknown_card;
    }

    if (!sdTransaction(pdrv, READ_OCR, 0, &resp)) {
      if (resp & (1 << 30)) {
        card->type = CARD_SDHC;
      } else {
        card->type = CARD_SD;
      }
    } else {
      ESP_LOGW(TAG, "READ_OCR failed: %X", resp);
      goto unknown_card;
    }
  } else {
    if (sdTransaction(pdrv, READ_OCR, 0, &resp) != 1 || !(resp & (1 << 20))) {
      ESP_LOGW(TAG, "READ_OCR failed: %X", resp);
      goto unknown_card;
    }

    start = millis();
    do {
      token = sdTransaction(pdrv, APP_OP_COND, 0x100000, NULL);
    } while (token == 0x01 && (millis() - start) < 1000);

    if (!token) {
      card->type = CARD_SD;
    } else {
      start = millis();
      do {
        token = sdTransaction(pdrv, SEND_OP_COND, 0x100000, NULL);
      } while (token != 0x00 && (millis() - start) < 1000);

      if (token == 0x00) {
        card->type = CARD_MMC;
      } else {
        ESP_LOGW(TAG, "SEND_OP_COND failed: %u", token);
        goto unknown_card;
      }
    }
  }

  if (card->type != CARD_MMC) {
    if (sdTransaction(pdrv, APP_CLR_CARD_DETECT, 0, NULL)) {
      ESP_LOGW(TAG, "APP_CLR_CARD_DETECT failed");
      goto unknown_card;
    }
  }

  if (card->type != CARD_SDHC) {
    if (sdTransaction(pdrv, SET_BLOCKLEN, 512, NULL) != 0x00) {
      ESP_LOGW(TAG, "SET_BLOCKLEN failed");
      goto unknown_card;
    }
  }

  card->sectors = sdGetSectorsCount(pdrv);

  // if (card->frequency > 25000000) {
  //   card->frequency = 25000000;
  // }

  card->status &= ~STA_NOINIT;
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "ff_sd_initialize initialized. INIT, status=0x%.02X", card->status);
#endif
  UNLOCK_SPI;
  return card->status;

unknown_card:
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "ff_sd_initialize initialized. CARD UNKNOWN ");
#endif
  card->type = CARD_UNKNOWN;
  UNLOCK_SPI;
  return card->status;
}

DSTATUS ff_sd_status(uint8_t pdrv) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "ff_sd_status");
#endif
  LOCK_SPI;
  if (sdTransaction(pdrv, SEND_STATUS, 0, NULL)) {
    ESP_LOGE(TAG, "Check status failed");
    UNLOCK_SPI;
    return STA_NOINIT;
  }
  UNLOCK_SPI;
  return s_cards[pdrv]->status;
}

DRESULT ff_sd_read(uint8_t pdrv, uint8_t *buffer, DWORD sector, UINT count) {
  esp_ardu_sdcard_t *card = s_cards[pdrv];

  if (card->status & STA_NOINIT) {
    ESP_LOGV(TAG, "ff_sd_read. STA_NOINIT");
    return RES_NOTRDY;
  }
  DRESULT res = RES_OK;

  LOCK_SPI;
  if (count > 1) {
    res = sdReadSectors(pdrv, (char *) buffer, sector, count) ? RES_OK : RES_ERROR;
  } else {
    res = sdReadSector(pdrv, (char *) buffer, sector) ? RES_OK : RES_ERROR;
  }
  UNLOCK_SPI;
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "ff_sd_read, sector=%d, count=%d, rc=%d", sector, count, res);
#endif
  return res;
}

DRESULT ff_sd_write(uint8_t pdrv, const uint8_t *buffer, DWORD sector, UINT count) {
  esp_ardu_sdcard_t *card = s_cards[pdrv];
  if (card->status & STA_NOINIT) {
    ESP_LOGV(TAG, "ff_sd_write, STA_NOINIT");
    return RES_NOTRDY;
  }

  if (card->status & STA_PROTECT) {
    ESP_LOGV(TAG, "ff_sd_write, STA_PROTECT");
    return RES_WRPRT;
  }
  DRESULT res = RES_OK;

  LOCK_SPI;
  if (count > 1) {
    res = sdWriteSectors(pdrv, (const char *) buffer, sector, count) ? RES_OK : RES_ERROR;
  } else {
    res = sdWriteSector(pdrv, (const char *) buffer, sector) ? RES_OK : RES_ERROR;
  }
  UNLOCK_SPI;
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "ff_sd_write, sector=%d, count=%d, rc=%d", sector, count, res);
#endif
  return res;
}

DRESULT ff_sd_ioctl(uint8_t pdrv, uint8_t cmd, void *buff) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "ff_sd_ioctl, cmd=%d", cmd);
#endif
  switch (cmd) {
    case CTRL_SYNC: {
      LOCK_SPI;
      if (sdSelectCard(pdrv)) {
        UNLOCK_SPI;
        return RES_OK;
      }
      UNLOCK_SPI;
    }
      return RES_ERROR;
    case GET_SECTOR_COUNT:
      *((unsigned long *) buff) = s_cards[pdrv]->sectors;
      return RES_OK;
    case GET_SECTOR_SIZE:
      *((WORD *) buff) = 512;
      return RES_OK;
    case GET_BLOCK_SIZE:
      *((uint32_t *) buff) = 1;
      return RES_OK;
  }
  return RES_PARERR;
}

bool sd_read_raw(uint8_t pdrv, uint8_t *buffer, DWORD sector) { return ff_sd_read(pdrv, buffer, sector, 1) == ESP_OK; }

bool sd_write_raw(uint8_t pdrv, uint8_t *buffer, DWORD sector) {
  return ff_sd_write(pdrv, buffer, sector, 1) == ESP_OK;
}

/***********************************************************
 *
 *         Public methods
 *
 * */

// uint8_t sdcard_uninit(uint8_t pdrv) {
//   esp_ardu_sdcard_t *card = s_cards[pdrv];
//   if (pdrv >= FF_VOLUMES || card == NULL) {
//     return 1;
//   }
//   sdTransaction(pdrv, GO_IDLE_STATE, 0, NULL);
//   ff_diskio_register(pdrv, NULL);
//   s_cards[pdrv] = NULL;
//   esp_err_t err = ESP_OK;
//   if (card->base_path) {
//     err = esp_vfs_fat_unregister_path(card->base_path);
//     free(card->base_path);
//   }
//   free(card);
//   return err;
// }

// uint8_t sdcard_init(uint8_t cs, SPIClass *spi, int hz) {
//   uint8_t pdrv = 0xFF;
//   if (ff_diskio_get_drive(&pdrv) != ESP_OK || pdrv == 0xFF) {
//     return pdrv;
//   }

//   ardu_sdcard_t *card = (ardu_sdcard_t *) malloc(sizeof(ardu_sdcard_t));
//   if (!card) {
//     return 0xFF;
//   }

//   card->base_path = NULL;
//   card->frequency = hz;
//   card->spi = spi;
//   card->ssPin = cs;

//   card->supports_crc = true;
//   card->type = CARD_NONE;
//   card->status = STA_NOINIT;

//   pinMode(card->ssPin, OUTPUT);
//   digitalWrite(card->ssPin, HIGH);

//   s_cards[pdrv] = card;

//   static const ff_diskio_impl_t sd_impl = {.init = &ff_sd_initialize,
//                                            .status = &ff_sd_status,
//                                            .read = &ff_sd_read,
//                                            .write = &ff_sd_write,
//                                            .ioctl = &ff_sd_ioctl};
//   ff_diskio_register(pdrv, &sd_impl);

//   return pdrv;
// }

void sdcard_unmount(uint8_t pdrv) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "sdcard_unmount");
#endif
  esp_ardu_sdcard_t *card = s_cards[pdrv];
  if (pdrv >= FF_VOLUMES || card == NULL) {
    ESP_LOGE(TAG, "Cannot unmount FS. pdrv=%d", pdrv);
    return;
  }
  card->status |= STA_NOINIT;
  card->type = CARD_NONE;

  char drv[3] = {(char) ('0' + pdrv), ':', 0};
  f_mount(NULL, drv, 0);
  // ESP_LOGV(TAG, "FS Unregister path %s",drv);
  esp_vfs_fat_unregister_path(card->base_path);

  if (card->base_path != NULL) {
    free(card->base_path);
    card->base_path = NULL;
  }

  // if (fs_handler != NULL) {
  //   free(fs_handler);
  //   fs_handler = NULL;
  // }
  ESP_LOGV(TAG, "FS Unregister path");
}

FATFS *sdcard_mount(uint8_t pdrv, const char *path, uint8_t max_files, bool format_if_empty) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGD(TAG, "sdcard_mount");
#endif
  esp_ardu_sdcard_t *card = s_cards[pdrv];
  FATFS *local_fs;

  if (pdrv >= FF_VOLUMES || card == NULL) {
    return NULL;
  }

  if (card->base_path != NULL) {
    free(card->base_path);
  }
  card->base_path = strdup(path);

  char drv[3] = {(char) ('0' + pdrv), ':', 0};
  esp_err_t err = esp_vfs_fat_register(card->base_path, drv, max_files, &local_fs);
  if (err == ESP_ERR_INVALID_STATE) {
    ESP_LOGE(TAG, "esp_vfs_fat_register failed 0x(%x): SD is registered.", err);
    return NULL;
  } else if (err != ESP_OK) {
    ESP_LOGE(TAG, "esp_vfs_fat_register failed 0x(%x)", err);
    return NULL;
  }

#if defined(SPI_CALL_TRACE)
  ESP_LOGD(TAG, "Register path %s", card->base_path);
#endif

  FRESULT res = f_mount(local_fs, drv, 1);
  if (res != FR_OK) {
    ESP_LOGE(TAG, "f_mount failed: %s", sdfs::fs_err2str[res]);
    if (res == 13 && format_if_empty) {
      size_t workbuf_size = sizeof(BYTE) * FF_MAX_SS;
      BYTE *work = (BYTE *) malloc(workbuf_size);
      if (!work) {
        ESP_LOGE(TAG, "alloc for f_mkfs failed");
        return NULL;
      }

#if defined(USE_ESP_IDF)
      size_t alloc_unit_size = esp_vfs_fat_get_allocation_unit_size(FF_SS_SDCARD, allocation_unit_size);
      // ESP_LOGW(TAG, "formatting card, allocation unit size=%d", alloc_unit_size);
      const MKFS_PARM opt = {(BYTE) FM_ANY, 0, 0, 0, alloc_unit_size};
      res = f_mkfs(drv, &opt, work, workbuf_size);
#else
      res = f_mkfs(drv, FM_ANY, 0, (void *) work, workbuf_size);  // workbuf_size  (UINT)sizeof(work)
#endif
      free(work);
      if (res != FR_OK) {
        ESP_LOGE(TAG, "f_mkfs failed: %s", sdfs::fs_err2str[res]);
        esp_vfs_fat_unregister_path(path);
        return NULL;
      }
      res = f_mount(local_fs, drv, 1);
      if (res != FR_OK) {
        ESP_LOGE(TAG, "f_mount failed: %s", sdfs::fs_err2str[res]);
        esp_vfs_fat_unregister_path(path);
        return NULL;
      }
    } else {
      esp_vfs_fat_unregister_path(path);
      return NULL;
    }
  }
  ESP_LOGV(TAG, "sdcard_mount, pdrv=%d, path=%s, max_files=%d, format if empty %s", pdrv, path, max_files,
           format_if_empty ? "TRUE" : "FALSE");

  LOCK_SPI;
  card->sectors = sdGetSectorsCount(pdrv);
  UNLOCK_SPI;

  // fs_handler = local_fs;
  return local_fs;
}

// uint32_t sdcard_num_sectors(uint8_t pdrv)
// {
//     ardu_sdcard_t * card = s_cards[pdrv];
//     if(pdrv >= FF_VOLUMES || card == NULL){
//         return 0;
//     }
//     return card->sectors;
// }

// uint32_t sdcard_sector_size(uint8_t pdrv)
// {
//     if(pdrv >= FF_VOLUMES || s_cards[pdrv] == NULL){
//         return 0;
//     }
//     return 512;
// }

// sdcard_type_t sdcard_type(uint8_t pdrv)
// {
//     ardu_sdcard_t * card = s_cards[pdrv];
//     if(pdrv >= FF_VOLUMES || card == NULL){
//         return CARD_NONE;
//     }
//     return card->type;
// }
static const ff_diskio_impl_t *sdimpl_init() {
  static const ff_diskio_impl_t sd_impl = {.init = &ff_sd_initialize,
                                           .status = &ff_sd_status,
                                           .read = &ff_sd_read,
                                           .write = &ff_sd_write,
                                           .ioctl = &ff_sd_ioctl};
  return &sd_impl;
}

/*****************************************************************
 */

const char m_CRC7Table[] = {
    0x00, 0x09, 0x12, 0x1B, 0x24, 0x2D, 0x36, 0x3F, 0x48, 0x41, 0x5A, 0x53, 0x6C, 0x65, 0x7E, 0x77, 0x19, 0x10, 0x0B,
    0x02, 0x3D, 0x34, 0x2F, 0x26, 0x51, 0x58, 0x43, 0x4A, 0x75, 0x7C, 0x67, 0x6E, 0x32, 0x3B, 0x20, 0x29, 0x16, 0x1F,
    0x04, 0x0D, 0x7A, 0x73, 0x68, 0x61, 0x5E, 0x57, 0x4C, 0x45, 0x2B, 0x22, 0x39, 0x30, 0x0F, 0x06, 0x1D, 0x14, 0x63,
    0x6A, 0x71, 0x78, 0x47, 0x4E, 0x55, 0x5C, 0x64, 0x6D, 0x76, 0x7F, 0x40, 0x49, 0x52, 0x5B, 0x2C, 0x25, 0x3E, 0x37,
    0x08, 0x01, 0x1A, 0x13, 0x7D, 0x74, 0x6F, 0x66, 0x59, 0x50, 0x4B, 0x42, 0x35, 0x3C, 0x27, 0x2E, 0x11, 0x18, 0x03,
    0x0A, 0x56, 0x5F, 0x44, 0x4D, 0x72, 0x7B, 0x60, 0x69, 0x1E, 0x17, 0x0C, 0x05, 0x3A, 0x33, 0x28, 0x21, 0x4F, 0x46,
    0x5D, 0x54, 0x6B, 0x62, 0x79, 0x70, 0x07, 0x0E, 0x15, 0x1C, 0x23, 0x2A, 0x31, 0x38, 0x41, 0x48, 0x53, 0x5A, 0x65,
    0x6C, 0x77, 0x7E, 0x09, 0x00, 0x1B, 0x12, 0x2D, 0x24, 0x3F, 0x36, 0x58, 0x51, 0x4A, 0x43, 0x7C, 0x75, 0x6E, 0x67,
    0x10, 0x19, 0x02, 0x0B, 0x34, 0x3D, 0x26, 0x2F, 0x73, 0x7A, 0x61, 0x68, 0x57, 0x5E, 0x45, 0x4C, 0x3B, 0x32, 0x29,
    0x20, 0x1F, 0x16, 0x0D, 0x04, 0x6A, 0x63, 0x78, 0x71, 0x4E, 0x47, 0x5C, 0x55, 0x22, 0x2B, 0x30, 0x39, 0x06, 0x0F,
    0x14, 0x1D, 0x25, 0x2C, 0x37, 0x3E, 0x01, 0x08, 0x13, 0x1A, 0x6D, 0x64, 0x7F, 0x76, 0x49, 0x40, 0x5B, 0x52, 0x3C,
    0x35, 0x2E, 0x27, 0x18, 0x11, 0x0A, 0x03, 0x74, 0x7D, 0x66, 0x6F, 0x50, 0x59, 0x42, 0x4B, 0x17, 0x1E, 0x05, 0x0C,
    0x33, 0x3A, 0x21, 0x28, 0x5F, 0x56, 0x4D, 0x44, 0x7B, 0x72, 0x69, 0x60, 0x0E, 0x07, 0x1C, 0x15, 0x2A, 0x23, 0x38,
    0x31, 0x46, 0x4F, 0x54, 0x5D, 0x62, 0x6B, 0x70, 0x79};

char CRC7(const char *data, int length) {
  char crc = 0;
  for (int i = 0; i < length; i++) {
    crc = m_CRC7Table[(crc << 1) ^ data[i]];
  }
  return crc;
}

const unsigned short m_CRC16Table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD,
    0xE1CE, 0xF1EF, 0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B, 0xA35A,
    0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, 0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B,
    0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D, 0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC, 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861,
    0x2802, 0x3823, 0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, 0x5AF5, 0x4AD4, 0x7AB7, 0x6A96,
    0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, 0x6CA6, 0x7C87,
    0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A,
    0x9F59, 0x8F78, 0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3,
    0x5004, 0x4025, 0x7046, 0x6067, 0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 0x02B1, 0x1290,
    0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, 0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E,
    0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634, 0xD94C, 0xC96D, 0xF90E, 0xE92F,
    0x99C8, 0x89E9, 0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3, 0xCB7D, 0xDB5C,
    0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A, 0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83,
    0x1CE0, 0x0CC1, 0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74,
    0x2E93, 0x3EB2, 0x0ED1, 0x1EF0};

unsigned short CRC16(const char *data, int length) {
  unsigned short crc = 0;
  for (int i = 0; i < length; i++) {
    crc = (crc << 8) ^ m_CRC16Table[((crc >> 8) ^ data[i]) & 0x00FF];
  }
  return crc;
}

}  // namespace sdfs
}  // namespace esphome
#endif