#pragma once
#include "display_buffer.h"
#include "component.h"
#include "gpio.h"
#include "SSD1339.h"

namespace esphome {
namespace ssd1339_display {

class SSD1339Display : public esphome::display::DisplayBuffer {
 public:
  SSD1339Display();
  void setup() override;
  void update() override;
  void draw_pixel_at(int x, int y, esphome::display::Color color) override;
  int get_width() override { return 128; }
  int get_height() override { return 128; }

  void set_rst_pin(esphome::GPIOPin *pin) { rst_pin_ = pin; }
  void set_cs_pin(esphome::GPIOPin *pin) { cs_pin_ = pin; }
  void set_dc_pin(esphome::GPIOPin *pin) { dc_pin_ = pin; }
  void set_din_pin(esphome::GPIOPin *pin) { din_pin_ = pin; }
  void set_clk_pin(esphome::GPIOPin *pin) { clk_pin_ = pin; }
  void set_hven_pin(esphome::GPIOPin *pin) { hven_pin_ = pin; }

 private:
  SSD1339 *oled_ = nullptr;
  esphome::GPIOPin *rst_pin_{nullptr};
  esphome::GPIOPin *cs_pin_{nullptr};
  esphome::GPIOPin *dc_pin_{nullptr};
  esphome::GPIOPin *din_pin_{nullptr};
  esphome::GPIOPin *clk_pin_{nullptr};
  esphome::GPIOPin *hven_pin_{nullptr};
  uint16_t buffer_[128 * 128];
  void flush_();
};

}  // namespace ssd1339_display
}  // namespace esphome 