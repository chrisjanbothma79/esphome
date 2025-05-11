#pragma once
#include "esphome/core/gpio.h"
#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"

#ifdef USE_ARDUINO_SPI_FS
#define SPI_DRIVER_SELECT 3
#define SD_CHIP_SELECT_MODE 0
// #include "sdio_drv_ard.h"
#include "esphome/components/spi/spi.h"

#include "SdFat.h"
#include "SpiDriver/SdSpiBaseClass.h"
#endif

namespace esphome {
namespace sdfs {
// #ifdef USE_ESP_IDF
// #else

// #endif

enum SdDriverStatus : int {
  SD_SLOT_ST_NOTINIT = 0,
  SD_SLOT_ST_INIT = 1,
  SD_SLOT_ST_EMPTY = 2,
  SD_SLOT_ST_CARD = 3,
  SD_SLOT_ST_MOUNT = 4,
};

enum BusWidth : int {
  BUS_WIDTH_1BIT = 1,
  BUS_WIDTH_4BIT = 4,
  BUS_WIDTH_8BIT = 8,
};

enum SdConnType {
  SD_MMC = 0,
  SD_SPI = 1,
};

class SdmmcDriver;
#ifdef USE_ARDUINO_SPI_FS
class EspHomeConnector;
#endif

class SdmmcHost : public Component {
  friend class SdmmcDriver;
  friend class SdmmcIdfDriver;

 public:
  SdmmcHost();
  void setup() override;
  void loop() override;
  void dump_config() override;

#ifdef USE_ARDUINO_SPI_FS
  void set_spi_parent(spi::SPIComponent *);
  void set_cs_pin(GPIOPin *);
  void set_data_rate(uint32_t);
  void set_mode(spi::SPIMode);
#endif

  SdDriverStatus get_state();
  void set_state(SdDriverStatus);

  void set_conn_type(SdConnType);
  void set_bus_width(BusWidth);

  void set_bus_slot(uint8_t);  // spi_mode
  void set_cs_pin(uint8_t);
  void set_miso_pin(uint8_t);
  void set_mosi_pin(uint8_t);
  void set_clk_pin(uint8_t);

  void set_cmd_pin(uint8_t);  //--- ????
  void set_data0_pin(uint8_t);
  void set_data1_pin(uint8_t);
  void set_data2_pin(uint8_t);
  void set_data3_pin(uint8_t);
  void set_data4_pin(uint8_t);
  void set_data5_pin(uint8_t);
  void set_data6_pin(uint8_t);
  void set_data7_pin(uint8_t);
  void set_pw_ctrl_pin(uint8_t);
  void set_cd_pin(uint8_t);
  void set_wp_pin(uint8_t);
  void set_int_pin(uint8_t);
  void set_path(std::string);

 protected:
#ifdef USE_ARDUINO_SPI_FS
  EspHomeConnector *connector_;
#endif
  bool last_card_staus = false;
  time_t last_time_check_;
  SdmmcDriver *drv_;
  SdConnType type_;
  SdDriverStatus state_;
  std::string path_;
  BusWidth spi_bus_width_;
  uint8_t bus_slot_{255};
  uint8_t clk_pin_{255};
  uint8_t cmd_pin_{255};
  uint8_t data0_pin_{255};
  uint8_t data1_pin_{255};
  uint8_t data2_pin_{255};
  uint8_t data3_pin_{255};
  uint8_t data4_pin_{255};
  uint8_t data5_pin_{255};
  uint8_t data6_pin_{255};
  uint8_t data7_pin_{255};
  uint8_t cs_pin_{255};
  uint8_t cd_pin_{255};
  uint8_t wp_pin_{255};
  uint8_t int_pin_{255};
  uint8_t pw_ctrl_pin_{255};
  uint8_t miso_pin_{255};
  uint8_t mosi_pin_{255};
};

/**
 * @brief   Interface clss  to serve slot initializing,  card check, mout and unmount fs
 *          with warious frameworks
 *          SdmmcHost used for access to cpu pin assignements for initialize SPI or SDIO driver on cpu
 */
class SdmmcDriver {
 public:
  SdmmcDriver(SdmmcHost *);
  virtual bool init_host(SdConnType);
  virtual bool is_card();
  virtual bool attach_card();
  virtual bool mount(bool);
  virtual void unmount();

  void set_last_err(uint32_t);
  uint32_t get_last_err();
  bool is_last_err(uint16_t dom, uint16_t rc);

 protected:
  uint32_t last_err_;
  SdmmcHost *parent_;
};
// #endif
}  // namespace sdfs
}  // namespace esphome