#pragma once
#include "esphome/core/defines.h"
#include "sdfs.h"
#include "sdfs_defines.h"
#if defined(USE_SDMMC_MODE) && defined(SOC_SDMMC_HOST_SUPPORTED)
// #include "ffconf.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_types.h"
#include "ff.h"
#include "esp_vfs_fat.h"

namespace esphome {
namespace sdfs {

// typedef enum { SDMMC_RET_STATUS_OK = 0, SDMMC_RET_STATUS_FAIL = 1, SDMMC_RET_STATUS_NOCARD = 2 } init_status_t;

// typedef struct {
//   // sdfs::SpiConnector *conn;
//   int frequency;
//   char *base_path;
//   // card_type_t type;
//   unsigned long sectors;
//   bool supports_crc;
//   int status;
// } ardu_sdmmc_card_t;

class SdmmcIO {
 public:
  SdmmcIO();

  void set_bus_width(uint8_t);
  void set_wp_pin(uint8_t);
  void set_cd_pin(uint8_t);
  void set_clk_pin(uint8_t);
  void set_cmd_pin(uint8_t);
  void set_bus_slot(uint8_t);
  void set_data0_pin(uint8_t);
  void set_data1_pin(uint8_t);
  void set_data2_pin(uint8_t);
  void set_data3_pin(uint8_t);
  void set_data4_pin(uint8_t);
  void set_data5_pin(uint8_t);
  void set_data6_pin(uint8_t);
  void set_data7_pin(uint8_t);

  bool init();
  bool init_slot();
  sdcard_status_t init_card();
  sdcard_status_t get_disk_status();
  FATFS *mount(std::string);
  local_rc_t format();
  void unmount();
  uint8_t get_pdrv();
  bool is_card_mem();
  bool is_card_sdio();
  bool is_card_mmc();

  size_t sectors();      // card_info_->csd->capacity
  size_t sector_size();  // card_info_->csd->sector_size

 protected:
  sdmmc_host_t *host_config_{NULL};
  sdmmc_slot_config_t *slot_config_{NULL};
  sdmmc_card_t *card_info_{NULL};
  esp_vfs_fat_mount_config_t *mount_config_{NULL};
  std::string mountpoint_;
  uint8_t pdrv_;
  uint32_t last_err_;
  FATFS *fs_ = NULL;
  uint8_t spi_bus_width_ = 1;
  uint8_t wp_pin_ = 255;
  uint8_t cd_pin_ = 255;
  uint8_t clk_pin_ = 255;
  uint8_t cmd_pin_ = 255;
  uint8_t bus_slot_ = 1;
  uint8_t data0_pin_ = 255;
  uint8_t data1_pin_ = 255;
  uint8_t data2_pin_ = 255;
  uint8_t data3_pin_ = 255;
  uint8_t data4_pin_ = 255;
  uint8_t data5_pin_ = 255;
  uint8_t data6_pin_ = 255;
  uint8_t data7_pin_ = 255;
};

}  // namespace sdfs
}  // namespace esphome
#endif