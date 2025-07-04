#pragma once
#include "esphome/core/gpio.h"
#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "sdfs_defines.h"
#include "fs_interface.h"

#ifdef USE_SDSPI_MODE
#include "esphome/components/spi/spi.h"
#include "spi_connector.h"
#if defined(USE_ARDUINO)
#include "SPI.h"
#endif
#endif

namespace esphome {
namespace sdfs {

enum SdDriverState : uint8_t {
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
extern const char *host_st2str[];
const char *sd_state_to_string(SdDriverState state);

/**
 * @brief   Card eject/insert interrupt data
 *
 */
struct CardDetectInterrupt {
  volatile bool present{true};
  bool init{false};
  static void card_insert(CardDetectInterrupt *card_status);
  static void card_eject(CardDetectInterrupt *card_status);
};

#ifdef USE_SDSPI_MODE
class SpiConnector;
#endif
class FsInterface;
class DriverInterface;

class SdfsHost : public PollingComponent {
  friend class SdfsDriver;

 public:
  SdfsHost();
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
  DriverInterface *get_drv() { return drv_; };
  FsInterface *get_fs();
  SdDriverState get_state() { return state_; };
  void set_state(SdDriverState state);

#if defined(USE_SDSPI_MODE)
  void set_spi_parent(spi::SPIComponent *);
  void set_cs_pin(GPIOPin *);
  void set_data_rate(uint32_t);
  void set_mode(spi::SPIMode);
#endif

  void add_on_state_callback(std::function<void(SdDriverState)> &&callback);

  void write_to_file(std::string path, char mode, uint8_t *buf, size_t size);
  int read_from_file(std::string path, uint8_t *buf, size_t size, int position);

  void set_conn_type(SdConnType type) { type_ = type; };
  void set_bus_width(BusWidth busw) { spi_bus_width_ = busw; };
  void set_bus_slot(uint8_t buss) { bus_slot_ = buss; };
  void set_path(std::string path) { path_ = path; };

  // void set_pw_ctrl_pin(int pin) { pw_ctrl_pin_ = pin; };
  // void set_cd_pin(int pin) { cd_pin_ = pin; };
  // void set_wp_pin(int pin) { wp_pin_ = pin; };

  void load_pw_ctrl_pin(InternalGPIOPin *pin) { pw_ctrl_pin_ = pin; };
  void load_cd_pin(InternalGPIOPin *pin) { cd_pin_ = pin; };
  void load_wp_pin(InternalGPIOPin *pin) { wp_pin_ = pin; };

  void set_clk_pin(int pin) { clk_pin_ = pin; };
  void set_cmd_pin(int pin) { cmd_pin_ = pin; };
  void set_data0_pin(int pin) { data0_pin_ = pin; };
  void set_data1_pin(int pin) { data1_pin_ = pin; };
  void set_data2_pin(int pin) { data2_pin_ = pin; };
  void set_data3_pin(int pin) { data3_pin_ = pin; };
  void set_data4_pin(int pin) { data4_pin_ = pin; };
  void set_data5_pin(int pin) { data5_pin_ = pin; };
  void set_data6_pin(int pin) { data6_pin_ = pin; };
  void set_data7_pin(int pin) { data7_pin_ = pin; };

  // void set_int_pin(int pin) { int_pin_ = pin; };

 protected:
  bool card_present = false;
  CardDetectInterrupt card_present_st;
#if defined(USE_SDSPI_MODE)
  SpiConnector *connector_;
#endif
  FsInterface *fs_ = NULL;
  DriverInterface *drv_ = NULL;
  SdConnType type_;
  SdDriverState state_;
  std::string path_;
  BusWidth spi_bus_width_;
  uint8_t bus_slot_{0};
  CallbackManager<void(SdDriverState)> on_state_callback_{};

  // int pw_ctrl_pin_{-1};
  // int cd_pin_{-1};
  // int wp_pin_{-1};

  InternalGPIOPin *pw_ctrl_pin_{NULL};
  InternalGPIOPin *cd_pin_{NULL};  // DOWN -> No Card ;  UP -> Card present
  InternalGPIOPin *wp_pin_{NULL};

  // int int_pin_{-1};
  int clk_pin_{-1};
  int cmd_pin_{-1};
  int data0_pin_{-1};
  int data1_pin_{-1};
  int data2_pin_{-1};
  int data3_pin_{-1};
  int data4_pin_{-1};
  int data5_pin_{-1};
  int data6_pin_{-1};
  int data7_pin_{-1};
};

/**
 * @brief Interface for interconnect with SD card.
 *  Has implementation:
 *   esp8266SpiDriver - for erp8266 and other platforms
 *   SdfsDriver  -  Other ESP Platforms
 */
class DriverInterface {
 public:
  virtual void set_parent(SdfsHost *);
  virtual bool init_host(SdConnType);
  virtual bool is_card();
  virtual bool attach_card();
  virtual bool mount(std::string, bool);
  virtual uint32_t get_last_err();
  virtual void unmount();
  virtual bool test();
  virtual fsys_t *get_fs();

  virtual card_type_t card_type();
  virtual uint64_t card_size();
  virtual size_t num_sectors();
  virtual size_t sector_size();
  virtual uint64_t total_bytes();
  virtual uint64_t used_bytes();

 protected:
  SdConnType bus_type_;
  uint32_t last_err_;
  SdfsHost *parent_;
};

// #endif
}  // namespace sdfs
}  // namespace esphome