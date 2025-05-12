
#include "spi_connector.h"
#ifdef USE_ARDUINO_SPI_FS
#include "SdFat.h"

namespace esphome {
namespace sdfs {

SdFat fs;

static const char *const TAG = "spi_connector";

void SpiConnector::begin() {
  this->set_data_rate(this->maxSck_);
#if ENABLE_DEDICATED_SPI
  SdSpiConfig cfg = SdSpiConfig(0, DEDICATED_SPI, this->maxSck_, this);
#else
  SdSpiConfig cfg = SdSpiConfig(0, SHARED_SPI, this->maxSck_, this);
#endif
  this->begin(cfg);
}

// Initialize the SPI bus.
void SpiConnector::begin(SdSpiConfig config) {
  ESP_LOGD(TAG, "Starting SPI. Speed=%d", config.maxSck);
  this->config_ = &config;
  this->spi_setup();
  fs.begin(config);
  this->card_ = fs.card();
  set_last_err(this->card_->errorCode());
}
SdSpiConfig *SpiConnector::get_config() { return this->config_; }

void SpiConnector::activate() { this->enable(); }
void SpiConnector::deactivate() { this->disable(); }  // Deactivate SPI hardware.
void SpiConnector::end() { this->spi_teardown(); }
uint8_t SpiConnector::get_errCode() { return this->last_err_; }
uint32_t SpiConnector::get_status() { return this->card_->errorData(); }

void SpiConnector::set_last_err(uint8_t rc) {
  if (rc > 0) {
    this->last_err_ = rc;
    ESP_LOGE(TAG, " SPI Last operation err %d", rc);
  }
}
// Save SPISettings for new max SCK frequency
void SpiConnector::setSckSpeed(uint32_t maxSck) {
  this->maxSck_ = maxSck;
  ESP_LOGD(TAG, "SPI setSckSpeed called. Speed %d", maxSck);
}
// Receive a byte.
uint8_t SpiConnector::receive() {
  uint8_t bt = this->receive();
  set_last_err(this->card_->errorCode());
  return bt;
}
// Receive multiple bytes.
uint8_t SpiConnector::receive(uint8_t *buf, size_t count) {
  size_t num = this->receive(buf, count);
  set_last_err(this->card_->errorCode());
  return num;
}
// Send a byte.
void SpiConnector::send(uint8_t data) {
  this->send(data);
  set_last_err(this->card_->errorCode());
}
// Send multiple bytes.
void SpiConnector::send(const uint8_t *buf, size_t count) {
  this->send(buf, count);
  set_last_err(this->card_->errorCode());
}

}  // namespace sdfs
}  // namespace esphome
#endif