#include "esphome/core/defines.h"
#include "sdfs.h"
#include "sdfs_defines.h"
#if defined(USE_SDSPI_MODE) && defined(USE_ESP8266)
#include "esp8266_drv.h"
#include "esp8266_cdio.h"

namespace esphome {
namespace sdfs {

const char *TAG = "esp8266_drv";

/***********************************************************************
 *
 *    @brief  esp8266SpiDriver member function
 *
 */
void esp8266SpiDriver::set_connector(SpiConnector *c) {
  this->connector_ = c;
  this->spi_impl_ = new SdSpiImpl();
}
void esp8266SpiDriver::set_parent(SdmmcHost *p) { this->parent_ = p; }
bool esp8266SpiDriver::is_card() {
  // if (! this->sd_card) {
  // 	return false;
  // }
  // uint8_t st;
  // bool st_bool = this->sd_card->readStatus(&st);
  // uint8_t rc = this->sd_card->errorCode();
  // if ((!st_bool)  && (rc != SD_CARD_ERROR_READ_TIMEOUT)){
  // 	ESP_LOGE(TAG,"cd_card error = (%d)%s", rc, sd_err2str(rc).c_str());
  // }
  // return st_bool;
  return true;
}
bool esp8266SpiDriver::attach_card() { return true; }
bool esp8266SpiDriver::mount(std::string, bool) { return true; }
uint32_t esp8266SpiDriver::get_last_err() { return last_err_; }
void esp8266SpiDriver::unmount() {}

bool esp8266SpiDriver::init_host(SdConnType ctype) {
  // SdCsPin_t fake_pin = 0;
  SdSpiConfig *SpiConf;
  FsVolume *fs = new FsVolume();
  bool is_begin = false;
  this->spi_impl_->set_spi(this->connector_);
  SpiConf = new SdSpiConfig((SdCsPin_t) 0, (uint8_t) SHARED_SPI, (uint32_t) SD_SCK_MHZ(50), this->spi_impl_);

  SdfsSpiCard *sd_card = new SdfsSpiCard();
  sd_card->begin(*SpiConf);
  is_begin = fs->begin(sd_card);

  if (!is_begin) {
    ESP_LOGD(TAG, "init_host failed");
    return false;
  }
  this->vol = fs;
  ESP_LOGD(TAG, "init_host OK");
  return true;
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

  // // FsFile file = root.openNextFile();
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

/***********************************************************************
 *
 *    @brief  SdSpiImpl member function
 *
 */
SdSpiImpl::SdSpiImpl() { DEBUG_TRACE("SdSpiImpl:INIT"); }

void SdSpiImpl::set_spi(SpiConnector *c) {
  DEBUG_TRACE("SdSpiImpl:set_spi");
  connector_ = c;
}

void SdSpiImpl::begin(SdSpiConfig config) {
  DEBUG_TRACE("SdSpiImpl:begin");
  if (!connector_) {
    ESP_LOGE(TAG, "SPI connector unknown.  Run set_spi before.");
  } else {
    connector_->begin();
  }
}
// void SdSpiImpl::end()  {
// 	ESP_LOGD(TAG,"SdSpiImpl:end");
// 	this->connector_->end();
// }
void SdSpiImpl::activate() {
  DEBUG_TRACE("SdSpiImpl:activate aka beginTransaction");
  this->connector_->beginTransaction();
}
void SdSpiImpl::deactivate() {
  DEBUG_TRACE("SdSpiImpl:deactivate aka endTransaction");
  this->connector_->endTransaction();
}
uint8_t SdSpiImpl::receive() {
  DEBUG_TRACE("SdSpiImpl:receive byte");
  return this->connector_->transfer(0xFF);
}
uint8_t SdSpiImpl::receive(uint8_t *buf, size_t count) {
  DEBUG_TRACE("SdSpiImpl:receive buffer");
  // this->connector_->transfer(buf,count);
  this->connector_->transferBytes(NULL, buf, count);
  // transferBytes
  return count;
}
void SdSpiImpl::send(uint8_t data) {
  DEBUG_TRACE("SdSpiImpl:send ");
  this->connector_->write(data);
}
void SdSpiImpl::send(const uint8_t *buf, size_t count) {
  DEBUG_TRACE("SdSpiImpl:send  buffer");
  this->connector_->writeBytes(buf, count);
}
void SdSpiImpl::setSckSpeed(uint32_t maxSck) {
  DEBUG_TRACE("SdSpiImpl:setSckSpeed  %d", maxSck);
  // (void)maxSck;
}

}  // namespace sdfs
}  // namespace esphome

#endif