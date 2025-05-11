#if defined(USE_ARDUINO_SPI_FS)
#include "sdio_drv_ard.h"
#include "esphome/components/spi/spi.h"
namespace esphome {
namespace sdfs {
static const char *const TAG = "sd_ard_driver";

SdFat sd;
// ------------------------------------------------------------
//
//         EspHomeConnector
//

// EspHomeConnector(spi::SPIComponent *parent, GPIOPin *cs_pin) parent_(parent){};

EspHomeConnector::EspHomeConnector() { ESP_LOGD(TAG, " Load connector"); }

// Activate SPI hardware with correct speed and mode.
void EspHomeConnector::activate() {
  ESP_LOGD(TAG, "SPI Activate called");
  this->set_data_rate(this->maxSck_);
  this->spi_setup();
}
// Initialize the SPI bus.
void EspHomeConnector::begin(SdSpiConfig config) {
  ESP_LOGD(TAG, "Begin called. Optons=0x%x, max speed %d", config.options, config.maxSck);
  // m_spiSettings = config;
  // SPI.begin();
}
// Deactivate SPI hardware.
void EspHomeConnector::deactivate() {
  ESP_LOGD(TAG, "SPI deactivate called");
  this->spi_teardown();
  // SPI.endTransaction();
}
// Receive a byte.
uint8_t EspHomeConnector::receive() {
  this->enable();
  uint8_t bt = this->receive();
  this->disable();
  // return SPI.transfer(0XFF);
  return bt;
}
// Receive multiple bytes.
// Replace this function if your board has multiple byte receive.
uint8_t EspHomeConnector::receive(uint8_t *buf, size_t count) {
  this->enable();
  size_t num = this->receive(buf, count);
  this->disable();
  return num;
  // for (size_t i = 0; i < count; i++) {
  //   buf[i] = SPI.transfer(0XFF);
  // }
  // return 0;
}
// Send a byte.
void EspHomeConnector::send(uint8_t data) {
  this->enable();
  this->send(data);
  this->disable();
  // SPI.transfer(data);
}
// Send multiple bytes.
// Replace this function if your board has multiple byte send.
void EspHomeConnector::send(const uint8_t *buf, size_t count) {
  this->enable();
  this->send(buf, count);
  this->disable();
  // for (size_t i = 0; i < count; i++) {
  //   SPI.transfer(buf[i]);
  // }
}
// Save SPISettings for new max SCK frequency
void setSckSpeed(uint32_t maxSck) {
  ESP_LOGD(TAG, "SPI setSckSpeed called. Speed %d", maxSck);
  // m_spiSettings = SPISettings(maxSck, MSBFIRST, SPI_MODE0);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
//
//         SdArduinoDriver
//
SdArduinoDriver::SdArduinoDriver(SdmmcHost *parent) : SdmmcDriver(parent) {
  this->parent_ = parent;
  this->connector_ = NULL;
}
// EspHomeConnector* connector
//     this->connector_ = connector;

void SdArduinoDriver::set_connector(EspHomeConnector *connector) { this->connector_ = connector; }

bool SdArduinoDriver::init_host(SdConnType bus_type) {
  uint8_t ret_status = 0;
  this->bus_type_ = bus_type;

  if (this->bus_type_ == SD_MMC) {
    ESP_LOGE(TAG, "SDIO connection under Arduino framework is not sopported.");
    return false;
  } else {
    ret_status = init_sdspi();
  }

  // if (ret_status == RET_STATUS_FAIL) {
  //   return false;
  // }
  return true;
}

/***********************************************************************************
 * @brief   Init SDFS controller
 *
 * @return true
 * @return false
 */
bool SdArduinoDriver::init_sdspi() {
  ESP_LOGD(TAG, "INIT sdspi");
#define SD_CS_PIN 0
  SdCsPin_t P0 = 0;
  this->connector_->activate();

#if ENABLE_DEDICATED_SPI
  //  #define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(50), &EspHomeConnector)
  this->arduino_spi_config = new SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(50), this->connector_);
#else   // ENABLE_DEDICATED_SPI
  //  #define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SD_SCK_MHZ(50), &EspHomeConnector)
  this->arduino_spi_config = new SdSpiConfig(SD_CS_PIN, SHARED_SPI, SD_SCK_MHZ(50), &this->connector_);
#endif  // ENABLE_DEDICATED_SPI
}

bool SdArduinoDriver::mount(bool formatting) {
  ESP_LOGD(TAG, "FS Mount");
  sd.begin(*(this->arduino_spi_config));
  this->card_ = sd.card();
  ESP_LOGD(TAG, "Card status %s", this->card_ == NULL ? "NOT READY" : "READY");
}

bool SdArduinoDriver::is_card() {
  ESP_LOGD(TAG, "Card status");

  this->card_ = sd.card();
  // bool ret = true;
  // uint8_t status;
  // ret = this->card_->readStatus(&status);
  return this->card_->isSpi();
  // ESP_LOGD(TAG,"Card status 0x%x",status);

  // return true;
}

bool SdArduinoDriver::attach_card() { return true; }
void SdArduinoDriver::unmount() {}

void sdCsInit(SdCsPin_t pin) {}
void sdCsWrite(SdCsPin_t pin, bool level) {}
}  // namespace sdfs
}  // namespace esphome
#endif