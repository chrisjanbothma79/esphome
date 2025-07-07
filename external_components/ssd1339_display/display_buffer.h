#pragma once
#include <cstdint>
#include "component.h"

namespace esphome {
namespace display {

struct Color {
  uint8_t red, green, blue;
  Color() : red(0), green(0), blue(0) {}
  Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
};

class DisplayBuffer : public esphome::Component {
 public:
  DisplayBuffer();
  virtual ~DisplayBuffer();
  virtual void draw_pixel_at(int x, int y, Color color) = 0;
  virtual int get_width() = 0;
  virtual int get_height() = 0;
};

}  // namespace display
}  // namespace esphome 