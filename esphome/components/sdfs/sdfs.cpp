#include "sdfs.h"
#include "esphome/core/log.h"

// #if defined(USE_SDSPI_MODE)
// #include "esphome/components/spi/spi.h"
// #include "spi_connector.h"
// #endif

/**
 * @brief  CDFS is module for connecting and mount FAT filesysyem on SD card.
 *  Drives support SPI os MMC conncetion. In case SPI connection it use esphome's SPI module.
 *  For MMC connection it ues ESP IDF internal libs, therefore  MMC communication
 *  available oonly on pure ESP32 or ESP32S3 board variats.
 *
 *  CDFS  ( SdmmcHost  class)  is a central class for controlling, checking  and mounting card.
 *  esp8266_drv (esp8266SpiDriver driver) reailzation of DriverInterface  for esp8266 based boards
 *  spi_connector -  SPi interface  for connect card io operation and esphome spi module
 *  fs_interface  -  FS and File  access, read and write interface
 *
 * esp8266 boards SPI inteface
 * ---------------------------
 * SdmmcHost (sdfs.cpp) -> esp8266SpiDriver (esp8266_drv.cpp) -> SdfsSpiCard (esp8266_cdio.cpp)
 *
 * Other boards with arduino framework
 * -----------------------------------
 * SdmmcHost (sdfs.cpp) -> SdfsArduinoDriver (sdspi_drv_ard.cpp) --> sdspi_io    - for SPI connections
 *                                                               +-> SdmmcIO (sdmmc_io.cpp)  - for MMC connections
 *
 * Other boards with IDF framework
 * -----------------------------------
 * SdmmcHost (sdfs.cpp) -> SdfsIdfDriver (sdspi_drv_idf.cpp) --> - for MMC connections
 *                                                 +-> sdspi_io  - for SPI connections
 *
 */

#if defined(USE_ARDUINO) && !defined(USE_ESP8266)
#include "sdfs_drv_ard.h"
#elif defined(USE_ARDUINO) && defined(USE_ESP8266)
#include "esp8266_drv.h"
#elif defined(USE_ESP_IDF)
#include "sdfs_drv_idf.h"
#endif

namespace esphome {
namespace sdfs {

static const char *TAG = "sdfs";

const char *fs_err2str[] = {"(0) Succeeded",
                            "(1) A hard error occurred in the low level disk I/O layer",
                            "(2) Assertion failed",
                            "(3) The physical drive cannot work",
                            "(4) Could not find the file",
                            "(5) Could not find the path",
                            "(6) The path name format is invalid",
                            "(7) Access denied due to prohibited access or directory full",
                            "(8) Access denied due to prohibited access",
                            "(9) The file/directory object is invalid",
                            "(10) The physical drive is write protected",
                            "(11) The logical drive number is invalid",
                            "(12) The volume has no work area",
                            "(13) There is no valid FAT volume",
                            "(14) The f_mkfs() aborted due to any problem",
                            "(15) Could not get a grant to access the volume within defined period",
                            "(16) The operation is rejected according to the file sharing policy",
                            "(17) LFN working buffer could not be allocated",
                            "(18) Number of open files > FF_FS_LOCK",
                            "(19) Given parameter is invalid"};

const char *host_st2str[] = {
    "(0) ST: Slot not init", "(1) ST: Slot initiallized", "(2) ST: Slot empty",
    "(3) ST: Card present",  "(4) ST: Card mount",
};

const char *fat_type2str[] = {"NO_FS", "FS_FAT12", "FS_FAT16", "FS_FAT32", "FS_EXFAT"};
class SdfsArduinoDriver;

/**
 * @brief  EspHome component for univeral interface for card attach and mount controll
 *
 */
SdmmcHost::SdmmcHost() {
  this->set_state(SD_SLOT_ST_NOTINIT);

#if defined(USE_SDSPI_MODE)
  this->connector_ = new SpiConnector();
#endif
  ESP_LOGD(TAG, "Host class init");
}

void SdmmcHost::dump_config() {
  ESP_LOGCONFIG(TAG, "   SD Connection type: %s", this->type_ == SD_MMC ? "sdmmc" : "sdspi");
  ESP_LOGCONFIG(TAG, "   FS Root path:     %s", this->path_.c_str());

  if (this->type_ == SD_MMC) {
    ESP_LOGCONFIG(TAG, "   SDIO bus slot:      %d", this->bus_slot_);
    if (this->spi_bus_width_ == BUS_WIDTH_1BIT)
      ESP_LOGCONFIG(TAG, "   SDIO bus_width: 1bit");
    else if (this->spi_bus_width_ == BUS_WIDTH_4BIT)
      ESP_LOGCONFIG(TAG, "   SDIO bus_width: 4bit");
    else if (this->spi_bus_width_ == BUS_WIDTH_8BIT)
      ESP_LOGCONFIG(TAG, "   SDIO bus_width: 8bit");

    ESP_LOGCONFIG(TAG, "   SDIO clk_pin:      %d", this->clk_pin_);
    ESP_LOGCONFIG(TAG, "   SDIO cmd_pin:      %d", this->cmd_pin_);
    ESP_LOGCONFIG(TAG, "   SDIO data0 pin:    %d", this->data0_pin_);

    if (this->spi_bus_width_ != 1) {
      ESP_LOGCONFIG(TAG, "   SDIO data1 pin:    %d", this->data1_pin_);
      ESP_LOGCONFIG(TAG, "   SDIO data2_pin:    %d", this->data2_pin_);
      ESP_LOGCONFIG(TAG, "   SDIO data3 pin:    %d", this->data3_pin_);
    }
    if (this->spi_bus_width_ == 8) {
      ESP_LOGCONFIG(TAG, "   SDIO data4 pin:    %d", this->data4_pin_);
      ESP_LOGCONFIG(TAG, "   SDIO data5 pin:    %d", this->data5_pin_);
      ESP_LOGCONFIG(TAG, "   SDIO data6 pin:    %d", this->data6_pin_);
      ESP_LOGCONFIG(TAG, "   SDIO data7 pin:    %d", this->data7_pin_);
    }
  } else {
    ESP_LOGCONFIG(TAG, "   SPI bus slot:      %d", this->bus_slot_);
    ESP_LOGCONFIG(TAG, "   SPI miso pin:     %d", this->miso_pin_);
    ESP_LOGCONFIG(TAG, "   SPI mosi pin:     %d", this->mosi_pin_);
    ESP_LOGCONFIG(TAG, "   SPI sc pin:       %d", this->cs_pin_);
    if (this->int_pin_ < 255)
      ESP_LOGCONFIG(TAG, "   SPI int pin:      %d", this->int_pin_);
  }

  if (this->cd_pin_ < 255)
    ESP_LOGCONFIG(TAG, "   SPI/SDIO cd pin:       %d", this->cd_pin_);
  if (this->wp_pin_ < 255)
    ESP_LOGCONFIG(TAG, "   SPI/SDIO wp pin:       %d", this->wp_pin_);
  if (this->pw_ctrl_pin_ < 255)
    ESP_LOGCONFIG(TAG, "   SPI/SDIO pwr ctrl pin: %d", this->pw_ctrl_pin_);
}

SdDriverStatus SdmmcHost::get_state() { return this->state_; }
void SdmmcHost::set_conn_type(SdConnType type) { this->type_ = type; }
void SdmmcHost::set_bus_slot(uint8_t gpio_num) { this->bus_slot_ = gpio_num; }
void SdmmcHost::set_clk_pin(uint8_t gpio_num) { this->clk_pin_ = gpio_num; }
void SdmmcHost::set_cmd_pin(uint8_t gpio_num) { this->cmd_pin_ = gpio_num; }
void SdmmcHost::set_data0_pin(uint8_t gpio_num) { this->data0_pin_ = gpio_num; }
void SdmmcHost::set_data1_pin(uint8_t gpio_num) { this->data1_pin_ = gpio_num; }
void SdmmcHost::set_data2_pin(uint8_t gpio_num) { this->data2_pin_ = gpio_num; }
void SdmmcHost::set_data3_pin(uint8_t gpio_num) { this->data3_pin_ = gpio_num; }
void SdmmcHost::set_data4_pin(uint8_t gpio_num) { this->data4_pin_ = gpio_num; }
void SdmmcHost::set_data5_pin(uint8_t gpio_num) { this->data5_pin_ = gpio_num; }
void SdmmcHost::set_data6_pin(uint8_t gpio_num) { this->data6_pin_ = gpio_num; }
void SdmmcHost::set_data7_pin(uint8_t gpio_num) { this->data7_pin_ = gpio_num; }
void SdmmcHost::set_pw_ctrl_pin(uint8_t gpio_num) { this->pw_ctrl_pin_ = gpio_num; }
void SdmmcHost::set_cs_pin(uint8_t gpio_num) { this->cs_pin_ = gpio_num; }
void SdmmcHost::set_cd_pin(uint8_t gpio_num) { this->cd_pin_ = gpio_num; }
void SdmmcHost::set_wp_pin(uint8_t gpio_num) { this->wp_pin_ = gpio_num; }
void SdmmcHost::set_int_pin(uint8_t gpio_num) { this->int_pin_ = gpio_num; }
void SdmmcHost::set_miso_pin(uint8_t gpio_num) { this->miso_pin_ = gpio_num; }
void SdmmcHost::set_mosi_pin(uint8_t gpio_num) { this->mosi_pin_ = gpio_num; }
void SdmmcHost::set_path(std::string path) { this->path_ = path; }
void SdmmcHost::set_bus_width(BusWidth bus_width) { this->spi_bus_width_ = bus_width; }

#if defined(USE_SDSPI_MODE)
void SdmmcHost::set_spi_parent(spi::SPIComponent *parent) { this->connector_->set_spi_parent(parent); }
void SdmmcHost::set_cs_pin(GPIOPin *cs) { this->connector_->set_cs_pin(cs); }
void SdmmcHost::set_data_rate(uint32_t data_rate) { this->connector_->set_data_rate(data_rate); }
void SdmmcHost::set_mode(spi::SPIMode mode) { this->connector_->set_mode(mode); }
#endif

void SdmmcHost::set_state(SdDriverStatus state) {
  ESP_LOGD(TAG, "Change state to: %s", host_st2str[state]);
  this->state_ = state;
}

/**
 * @brief  init SPI connector and SD disk driver
 *
 */
void SdmmcHost::setup() {
  ESP_LOGD(TAG, "Setup called");

#if defined(USE_ARDUINO) && !defined(USE_ESP8266)
  SdfsArduinoDriver *drv = new SdfsArduinoDriver();
#if defined(USE_SDSPI_MODE)
  drv->set_connector(this->connector_);
#endif
  drv->set_parent(this);
  this->drv_ = drv;
#elif defined(USE_ARDUINO) && defined(USE_ESP8266)  // USE_ARDUINO  with USE_ESP8266
  esp8266SpiDriver *drv = new esp8266SpiDriver();
  drv->set_connector(this->connector_);
  drv->set_parent(this);
  this->drv_ = drv;

#elif defined(USE_ESP_IDF)  // USE_ESP_IDF
  SdfsIdfDriver *drv = new SdfsIdfDriver();
  drv = new SdfsIdfDriver();
#if defined(USE_SDSPI_MODE)
  drv->set_connector(this->connector_);
#endif
  drv->set_parent(this);
  this->drv_ = drv;
#endif

  ESP_LOGD(TAG, "Setup");
  this->last_time_check_ = ::time(nullptr);
  this->dump_config();
  if (this->drv_ == NULL) {
    ESP_LOGE(TAG, " Intialize SDMMC/SDSPI driver only for ESP-IDF or ARDUINO frameworks supported.");
    this->mark_failed();
    return;
  }

  ESP_LOGD(TAG, "Init host");
  if (!this->drv_->init_host(this->type_)) {
    this->mark_failed();
    this->set_state(SD_SLOT_ST_NOTINIT);
    return;
  }
  this->set_state(SD_SLOT_ST_INIT);
  this->last_card_staus = true;

  ESP_LOGD(TAG, "Chack card.");
  if (this->drv_->is_card()) {
    this->set_state(SD_SLOT_ST_EMPTY);
    if (this->drv_->attach_card()) {
      this->set_state(SD_SLOT_ST_CARD);
      if (this->drv_->mount(path_, false)) {
        this->set_state(SD_SLOT_ST_MOUNT);

        if (this->drv_->test()) {
          ESP_LOGD(TAG, "FS test OK");
        } else {
          ESP_LOGD(TAG, "FS test FAIL");
        }

      } else {
        this->set_state(SD_SLOT_ST_CARD);
      }
    }
  }
  ESP_LOGD(TAG, "Setup complete");
}

void SdmmcHost::loop() {
  time_t cur_time = ::time(nullptr);

  if ((cur_time - this->last_time_check_) > 10) {
    ESP_LOGD(TAG, "Check card status. %d", cur_time - this->last_time_check_);
    this->last_time_check_ = cur_time;

    bool card_present = this->drv_->is_card();
    if ((!card_present) || (this->get_state() != SD_SLOT_ST_MOUNT)) {
      this->set_state(SD_SLOT_ST_EMPTY);

      if (this->drv_->attach_card()) {
        this->set_state(SD_SLOT_ST_CARD);

        if (this->drv_->mount(path_, false)) {
          this->set_state(SD_SLOT_ST_MOUNT);
        } else {
          ESP_LOGW(TAG, "Seems card present but cannot mount. %d", this->drv_->get_last_err());
        }
      }
    }
  }
}

}  // namespace sdfs
}  // namespace esphome