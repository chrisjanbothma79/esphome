#pragma once

#include "ht16k33_char.h"
//TODO: Do I need these .h files at all?

namespace esphome {
namespace ht16k33_char {

class Adafruit_7seg_large_flip;

class Adafruit_7seg_large_flip : public HT16k33CharComponent {
  public:
    uint8_t send_to_display(i2c::I2CDevice *display, uint8_t position);
};

}  // namespace ht16k33_char
}  // namespace esphome
