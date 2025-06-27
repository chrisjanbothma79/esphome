#include "esphome/core/defines.h"
#include "sdfs.h"
#include "sdfs_defines.h"
#if defined(USE_SDSPI_MODE) && defined(USE_ESP8266)
#include "esp8266_drv.h"
#include "esp8266_cdio.h"

namespace esphome {
namespace sdfs {

const char *TAG = "esp8266_drv";

String sdcard_err2str(uint8_t code) {
  // pr->print(F("SD_CARD_ERROR_"));
  switch (code) {
    SD_ERROR_CODE_LIST
    default:
      return F("UNKNOWN");
  }
};

/***********************************************************************
 *
 *    @brief  esp8266SpiDriver member function
 *
 */
void esp8266SpiDriver::set_connector(SpiConnector *c) {
  this->connector_ = c;
  this->spi_impl_ = new SdSpiImpl();
}
void esp8266SpiDriver::set_parent(SdfsHost *p) { this->parent_ = p; }

bool esp8266SpiDriver::init_host(SdConnType ctype) {
  // SdCsPin_t fake_pin = 0;
  // SdSpiConfig *SpiConf;
  // FsVolume *fs = new FsVolume();
  // bool is_begin = false;
  this->spi_impl_->set_spi(this->connector_);
  this->spi_impl_->begin();
  // SpiConf = new SdSpiConfig((SdCsPin_t) 0, (uint8_t) SHARED_SPI, (uint32_t) SD_SCK_MHZ(50), this->spi_impl_);
  sd_card = new SdfsSpiCard();
  is_card_connected = sd_card->begin(this->spi_impl_);
  // sd_card->begin(*SpiConf);
  // is_begin = fs->begin(sd_card);

  // if (!is_begin) {
  //   ESP_LOGE(TAG, "init cd_card error = %d, %s", sd_card->errorCode(), sdcard_err2str(sd_card->errorCode()).c_str());
  //   return false;
  // }
  // this->vol = fs;
  // this->sd_card = sd_card;
  ESP_LOGD(TAG, "init_host %s ", TRUEFALSE(is_card_connected));
  return is_card_connected;
}

bool esp8266SpiDriver::is_card() {
  if (!this->sd_card) {
    return false;
  }
  cid_t cid;
  is_card_connected = this->sd_card->readCID(&cid);
  uint8_t rc = this->sd_card->errorCode();
  if (!is_card_connected) {
    ESP_LOGE(TAG, "cd_card error = %d, %s", rc, sdcard_err2str(rc).c_str());
    if (vol) {
      this->unmount();
    }
  }

  ESP_LOGD(TAG, "is_card %s ", TRUEFALSE(is_card_connected));
  return is_card_connected;
}

bool esp8266SpiDriver::attach_card() {
  if (!is_card_connected) {
    delete this->sd_card;
    this->spi_impl_->end();
    this->spi_impl_->begin();

    sd_card = new SdfsSpiCard();
    is_card_connected = sd_card->begin(this->spi_impl_);
  }
  return is_card_connected;
}

bool esp8266SpiDriver::mount(std::string, bool) {
  vol = new FsVolume();
  bool is_mount = vol->begin(this->sd_card);
  ESP_LOGD(TAG, "mount %s ", TRUEFALSE(is_mount));
  return is_mount;
}

uint32_t esp8266SpiDriver::get_last_err() { return last_err_; }
void esp8266SpiDriver::unmount() {
  if (vol) {
    vol->end();
    vol = NULL;
  }
}

bool esp8266SpiDriver::test() {
  if (!this->vol) {
    ESP_LOGD(TAG, "Test filesystem failed");
    return false;
  }
  char fn[255];
  FsFile root = this->vol->open("/", O_RDONLY);

  if (!root) {
    ESP_LOGE(TAG, "Failed to open directory");
    return false;
  }
  if (!root.isDirectory()) {
    ESP_LOGE(TAG, "Not a directory");
    return false;
  }

  FsFile newFile;
  FsFile file = root.openNextFile();
  ;
  while (file) {
    if (file.isDirectory()) {
      ESP_LOGD(TAG, "DIR : ");
      size_t flen = file.getName(fn, 13);
      ESP_LOGD(TAG, "name: %s", fn);
      // if (levels) {
      // 	listDir(audio_SD, file.name(), levels - 1);
      // }
    } else {
      ESP_LOGD(TAG, "FILE: ");
      size_t flen = file.getName(fn, 13);
      ESP_LOGD(TAG, "     %s", fn);
      ESP_LOGD(TAG, "SIZE: ");
      ESP_LOGD(TAG, "     %d", file.size());
    }
    file.close();
    file = root.openNextFile();
  }
  root.close();
  return true;
}

card_type_t esp8266SpiDriver::card_type() {
  // SdStatus_t status;
  // this->sd_card->readStatus(reinterpret_cast<uint8_t *>(&status));
  switch (this->sd_card->type()) {
    case SD_CARD_TYPE_SDHC:
      return C_SDHC;
    case SD_CARD_TYPE_SD1:
      return C_SD;
    default:
      return C_UNKNOWN;
  }
  return C_UNKNOWN;
}

uint64_t esp8266SpiDriver::card_size() {
  csd_t csd;
  this->sd_card->readCSD(&csd);
  return sdCardCapacity(&csd);
}

size_t esp8266SpiDriver::num_sectors() { return this->sd_card->sectorCount(); }

size_t esp8266SpiDriver::sector_size() {
  // csd_t csd;
  // this->sd_card->readCSD(&csd);
  // return (csd.v1.sector_size_high << 1) | csd.v1.sector_size_low;
  return 512;
}

uint64_t esp8266SpiDriver::total_bytes() { return card_size() * sector_size(); }

uint64_t esp8266SpiDriver::used_bytes() {
  if (is_mount()) {
    return total_bytes() - (this->vol->freeClusterCount() * this->vol->sectorsPerCluster() * sector_size());
  }
  return 0;
}

}  // namespace sdfs
}  // namespace esphome

#endif