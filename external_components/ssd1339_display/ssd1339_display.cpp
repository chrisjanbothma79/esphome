#include "ssd1339_display.h"
#include "log.h"

namespace esphome {
namespace ssd1339_display {

SSD1339Display::SSD1339Display() {}

void SSD1339Display::setup() {
  // 初始化所有引脚为输出
  if (hven_pin_) hven_pin_->setup();
  if (rst_pin_) rst_pin_->setup();
  if (cs_pin_) cs_pin_->setup();
  if (dc_pin_) dc_pin_->setup();
  if (din_pin_) din_pin_->setup();
  if (clk_pin_) clk_pin_->setup();
  if (hven_pin_) hven_pin_->digital_write(true);
  delay(10);
  oled_ = new SSD1339(
    rst_pin_ ? rst_pin_->get_pin() : 4,
    cs_pin_ ? cs_pin_->get_pin() : 5,
    dc_pin_ ? dc_pin_->get_pin() : 2,
    din_pin_ ? din_pin_->get_pin() : 7,
    clk_pin_ ? clk_pin_->get_pin() : 6,
    255 // HVEN 由esphome控制
  );
  oled_->begin();
  oled_->clear(0x0000);
}

void SSD1339Display::draw_pixel_at(int x, int y, esphome::display::Color color) {
  if (x < 0 || x >= 128 || y < 0 || y >= 128) return;
  uint16_t c = SSD1339::MAKECOLOR64k(color.red, color.green, color.blue);
  buffer_[y * 128 + x] = c;
}

void SSD1339Display::flush_() {
  uint8_t data[128 * 128 * 2];
  for (int i = 0; i < 128 * 128; i++) {
    data[i * 2] = buffer_[i] >> 8;
    data[i * 2 + 1] = buffer_[i] & 0xFF;
  }
  oled_->Show_64k_Pattern(data, 0, 0, 127, 127);
}

void SSD1339Display::update() {
  for (int i = 0; i < 128 * 128; i++) buffer_[i] = 0x0000;
  // 这里可以用 this->print(...) 绘制内容到 buffer_
  flush_();
}

}  // namespace ssd1339_display
}  // namespace esphome 