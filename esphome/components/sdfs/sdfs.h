#pragma once
#include "esphome/core/gpio.h"
#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "sdfs_defines.h"

#ifdef USE_SDSPI_MODE
#include "esphome/components/spi/spi.h"
#include "spi_connector.h"
#if defined(USE_ARDUINO)
#include "SPI.h"
#endif
#endif

namespace esphome {
namespace sdfs {

typedef enum { CARD_NONE, CARD_MMC, CARD_SD, CARD_SDHC, CARD_UNKNOWN } sdcard_type_t;

#define RET_STATUS_OK 0
#define RET_STATUS_FAIL 1
#define RET_STATUS_NOTCRITICAL 2

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

extern const char *fat_type2str[];
extern const char *fs_err2str[];

// #ifdef USE_SDSPI_MODE
// extern const char *fs_err2str[];
// #endif

extern const char *host_st2str[];

#ifdef USE_SDSPI_MODE
class SpiConnector;
#endif

class DriverInterface;

class SdmmcHost : public Component {
  friend class SdmmcDriver;
  friend class SdfsIdfDriver;
  friend class SdfsArduinoDriver;

  // #ifdef USE_ESP_IDF
  // #endif
  // #ifdef USE_ARDUINO
  // #endif

 public:
  SdmmcHost();
  void setup() override;
  void loop() override;
  void dump_config() override;

#if defined(USE_SDSPI_MODE)
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
#if defined(USE_SDSPI_MODE)
  SpiConnector *connector_;
#endif
  bool last_card_staus = false;
  time_t last_time_check_;
  DriverInterface *drv_;
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

class DriverInterface {
 public:
  virtual void set_parent(SdmmcHost *);
  virtual bool init_host(SdConnType);
  virtual bool is_card();
  virtual bool attach_card();
  virtual bool mount(std::string, bool);
  virtual uint32_t get_last_err();
  virtual void unmount();
  virtual bool test();

 protected:
  SdConnType bus_type_;
  uint32_t last_err_;
  SdmmcHost *parent_;
};
// #endif
}  // namespace sdfs
}  // namespace esphome