#include "sdfs.h"
#include "esphome/core/log.h"

/**
 * @brief  CDFS is module for connecting and mount FAT filesysyem on SD card.
 *  Drives support SPI os MMC conncetion. In case SPI connection it use esphome's SPI module.
 *  For MMC connection it ues ESP IDF internal libs, therefore  MMC communication
 *  available oonly on pure ESP32 or ESP32S3 board variats.
 *
 *  CDFS  ( SdfsHost  class)  is a central class for controlling, checking  and mounting card.
 *  esp8266_drv (esp8266SpiDriver driver) reailzation of DriverInterface  for esp8266 based boards
 *  spi_connector -  SPi interface  for connect card io operation and esphome spi module
 *  fs_int  -  FS and File  access, read and write interface
 *
 * esp8266 boards SPI inteface
 * ---------------------------
 * SdfsHost (sdfs.cpp) -> esp8266SpiDriver (esp8266_drv.cpp) -> SdfsSpiCard (esp8266_cdio.cpp)
 *
 * Other boards
 * -----------------------------------
 * SdfsHost (sdfs.cpp) -> SdfsDriver (sdsfs_drv.cpp) --> sdspi_io (sdspi_io.cpp) --> for SPI connections
 *                                                   +-> SdmmcIO (sdmmc_io.cpp) --> for MMC connections
 *
 */

#ifndef USE_ESP8266
#include "sdfs_drv.h"
#else
#include "esp8266_drv.h"
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

void CardDetectInterrupt::card_insert(CardDetectInterrupt *data) { data->present = true; }
void CardDetectInterrupt::card_eject(CardDetectInterrupt *data) { data->present = false; }

class SdfsDriver;

/*******************************************************************************
 *
 * @brief  EspHome component for univeral interface for card attach and mount controll
 *
 */
SdfsHost::SdfsHost() {
  this->set_state(SD_SLOT_ST_NOTINIT);

#if defined(USE_SDSPI_MODE)
  this->connector_ = new SpiConnector();
#endif
  ESP_LOGD(TAG, "Host class init");
}
/*******************************************************************************
 *
 * @brief Return filesystem object
 *
 * @return FsInterface*
 */
FsInterface *SdfsHost::get_fs() {
  if ((fs_ == NULL) && (drv_ != NULL)) {
    fs_ = new FsInterface(this);
  }
  return fs_;
}

/*******************************************************************************
 *
 * @brief Dump current params in debug console
 *
 */
void SdfsHost::dump_config() {
  LOG_UPDATE_INTERVAL(this);
  ESP_LOGCONFIG(TAG, "   SD Connection type: %s", this->type_ == SD_MMC ? "sdmmc" : "sdspi");
  ESP_LOGCONFIG(TAG, "   FS mountpoint:     %s", this->path_.c_str());

  if (this->type_ == SD_MMC) {
    // if (this->int_pin_ != -1)
    //   ESP_LOGCONFIG(TAG, "   SDIO int pin:      %d", this->int_pin_);

    if (this->cd_pin_ != NULL)
      ESP_LOGCONFIG(TAG, "   SDIO cd pin:       %d", this->cd_pin_);
    if (this->wp_pin_ != NULL)
      ESP_LOGCONFIG(TAG, "   SDIO wp pin:       %d", this->wp_pin_);
    if (this->pw_ctrl_pin_ != NULL)
      ESP_LOGCONFIG(TAG, "   SDIO pwr ctrl pin: %d", this->pw_ctrl_pin_);

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

    if (this->spi_bus_width_ == 4) {
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
#if defined(USE_SDSPI_MODE)
    if (this->connector_ != NULL) {
      this->connector_->dump_config();
    }
#endif
    ESP_LOGCONFIG(TAG, "   SPI bus slot:      %d", this->bus_slot_);
  }
}

/*******************************************************
 *
 * @brief  Save new card state on change
 *
 * @param state
 */
void SdfsHost::set_state(SdDriverStatus state) {
  ESP_LOGD(TAG, "Change state to: %s", host_st2str[state]);
  this->on_state_callback_.call(static_cast<SdDriverStatus>(state));
  this->state_ = state;
}

/*******************************************************
 *
 * @brief  Init SPI connector and SD disk driver
 *
 */
void SdfsHost::setup() {
  // TODO: Init common pins   CD WP PWR_CTRL
  if (this->cd_pin_ != NULL) {
    this->cd_pin_->setup();
    this->cd_pin_->pin_mode(gpio::FLAG_PULLUP);
    this->cd_pin_->attach_interrupt(CardDetectInterrupt::card_insert, &this->card_present_st,
                                    gpio::INTERRUPT_LOW_LEVEL);
    this->cd_pin_->attach_interrupt(CardDetectInterrupt::card_eject, &this->card_present_st,
                                    gpio::INTERRUPT_HIGH_LEVEL);
    ESP_LOGD(TAG, "Arm CardDetect interrupt");
  }
  if (this->wp_pin_ != NULL) {
    this->wp_pin_->setup();
    this->wp_pin_->pin_mode(gpio::FLAG_PULLUP);
  }
  if (this->pw_ctrl_pin_ != NULL) {
    this->pw_ctrl_pin_->setup();
  }

#ifndef USE_ESP8266
  SdfsDriver *drv = new SdfsDriver();
#if defined(USE_SDSPI_MODE)
  drv->set_connector(this->connector_);
#endif
  drv->set_parent(this);
  this->drv_ = drv;
#else
  esp8266SpiDriver *drv = new esp8266SpiDriver();
  drv->set_connector(this->connector_);
  drv->set_parent(this);
  this->drv_ = drv;
#endif

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

  ESP_LOGD(TAG, "Chack card.");
  if (this->drv_->is_card()) {
    this->set_state(SD_SLOT_ST_EMPTY);
    if (this->drv_->attach_card()) {
      this->set_state(SD_SLOT_ST_CARD);
      card_present = true;
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

/*******************************************************
 *
 * @brief  Initialize SPI connector
 *
 */
#if defined(USE_SDSPI_MODE)
void SdfsHost::set_spi_parent(spi::SPIComponent *parent) { connector_->set_spi_parent(parent); }
void SdfsHost::set_cs_pin(GPIOPin *cs) { connector_->set_cs_pin(cs); }
void SdfsHost::set_data_rate(uint32_t data_rate) { connector_->set_data_rate(data_rate); }
void SdfsHost::set_mode(spi::SPIMode mode) { connector_->set_mode(mode); }
#endif

/********************************************************

 * @brief   Check card detect interrupt.
 *
 */
void SdfsHost::loop() {
  if (this->card_present_st.init) {
    if ((this->card_present_st.card_insert && (!card_present)) ||
        ((!this->card_present_st.card_insert) && card_present)) {
      this->update();
    }
  }
}
/*******************************************************
 *
 * @brief Check and update card status
 *
 */
void SdfsHost::update() {
  ESP_LOGD(TAG, "Check SD card status.");

  if ((!this->drv_->is_card()) || (this->get_state() != SD_SLOT_ST_MOUNT)) {
    this->set_state(SD_SLOT_ST_EMPTY);
    fs_ = NULL;
    if (this->drv_->attach_card()) {
      this->set_state(SD_SLOT_ST_CARD);
      card_present = true;
      if (this->drv_->mount(path_, false)) {
        this->set_state(SD_SLOT_ST_MOUNT);
      } else {
        ESP_LOGW(TAG, "Seems card present but cannot mount. %d", this->drv_->get_last_err());
      }
    } else {  // attach_card
      card_present = false;
    }
  }
}

/*******************************************************
 *
 * @brief  Arm callback on state changed
 *
 * @param callback
 */
void SdfsHost::add_on_state_callback(std::function<void(SdDriverStatus)> &&callback) {
  this->on_state_callback_.add(std::move(callback));
}

/*******************************************************
 * @brief  Write to file action
 *
 * @param path
 * @param mode
 * @param buf
 * @param size
 */
void SdfsHost::write_to_file(std::string path, std::string mode, uint8_t *buf, size_t size) {
  FsInterface *fs = get_fs();

  if ((fs == NULL) || (!fs->is_ready())) {
    ESP_LOGE(TAG, "Write_to_file action. FileSystem not mounted yet", path.c_str(), size);
    return;
  }

  FileInterface *file = NULL;
  ESP_LOGD(TAG, "Write file %s, buff size=%d", path.c_str(), size);

  if (mode == "read") {
    ESP_LOGE(TAG, "Can be opened only for for write or append");
    return;
  }

  file = fs->open_file(path, mode);

  ESP_LOGD(TAG, "Open file OK, mode=%s, rc=%d", mode.c_str(), file->get_error());
  if (file->get_error() == FR_OK) {
    if (file->write(buf, size) <= 0) {
      ESP_LOGE(TAG, "Write file error %d", file->get_error());
    }
    ESP_LOGD(TAG, "Write file OK, rc=%d", file->get_error());
    file->close();
  }
}

/*******************************************************
 * @brief   Read from file as specifiyed position
 *
 * @param path
 * @param buf
 * @param size
 * @param position
 * @return int
 */
int SdfsHost::read_from_file(std::string path, uint8_t *buf, size_t size, int position = 0) {
  FsInterface *fs = get_fs();
  FileInterface *file = NULL;
  int rd = -1;
  std::string mode("read");

  ESP_LOGD(TAG, "Read file %s, buff size=%d, pos=%d", path.c_str(), size, position);
  file = fs->open_file(path, mode);
  if (position > 0) {
    file->seek(position);
  }
  ESP_LOGD(TAG, "Open file OK, rc=%d", file->get_error());
  if (file->get_error() == FR_OK) {
    rd = file->read(buf, size);
    if (rd <= 0) {
      ESP_LOGE(TAG, "Read file error %d", file->get_error());
    }
    ESP_LOGD(TAG, "Read file OK, rc=%d", file->get_error());
    file->close();
  }
  return rd;
}

// TODO:  add is_exist condition
// TODO:  add is_dir condition

}  // namespace sdfs
}  // namespace esphome