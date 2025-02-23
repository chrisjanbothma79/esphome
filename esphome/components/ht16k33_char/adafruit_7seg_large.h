#pragma once

#include "ht16k33_char.h"

namespace esphome {
namespace ht16k33_char {

class Adafruit_7seg_large;

//using ht16k33_char_writer_t = std::function<void(Adafruit_7seg_large &)>;

class Adafruit_7seg_large : public HT16k33CharComponent {
  public:
    //void update();
    //void set_writer(ht16k33_char_writer_t &&writer) { this->writer_ = writer; };
    uint8_t send_to_display(i2c::I2CDevice *display, uint8_t position);
    
  //protected:
    //uint8_t digits_per_display_ {4};
    //optional<ht16k33_char_writer_t> writer_{};
    
};

}  // namespace ht16k33_char
}  // namespace esphome
