#pragma once
#include <cstdint>

namespace esphome {

class GPIOPin {
 public:
  GPIOPin();
  virtual ~GPIOPin();
  virtual void setup();
  virtual void digital_write(bool state);
  virtual int get_pin() const;
};

}  // namespace esphome 