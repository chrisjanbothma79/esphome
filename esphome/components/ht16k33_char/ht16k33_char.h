#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace ht16k33_char {

class HT16k33CharComponent;

//We can have up to 7 chips. Chip addresses are 0b1110xxx. Default is 0b1110000 (0x70).
//For 7 segment displays the 28 pin package could address up to 8 digits. So an absolute maximum number of chars is 8*7=56.

//What does this do?
using ht16k33_char_writer_t = std::function<void(HT16k33CharComponent &)>;

class HT16k33CharComponent : public PollingComponent, public i2c::I2CDevice {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  

  void set_writer(ht16k33_char_writer_t &&writer) { this->writer_ = writer; };
  float get_setup_priority() const override;
  void display();
  
  uint8_t send_to_display(i2c::I2CDevice *display, uint8_t position);
  
  void set_brightness(uint8_t brightness) { this->brightness_ = brightness; };
  void set_buffer_size(uint8_t size_to_set) { this->char_buffer_size_ = size_to_set; };  //TODO: Should I use a compiler define for this?
  //void set_device_type(uint8_t device_type) { this->device_type_ = device_type; };
  
  //Called automatically during setup to generate a list of I2CDevices that represent the displays.
  //We iterate through the displays_ to address individual displays during runtime.
  void add_secondary_display(i2c::I2CDevice *display) { this->displays_.push_back(display); }
  
  void set_scroll(bool scroll) { this->scroll_ = scroll; }
  void set_continuous(bool continuous) { this->continuous_ = continuous; }
  void set_scroll_speed(unsigned long scroll_speed) { this->scroll_speed_ = scroll_speed; }
  void set_scroll_dwell(unsigned long scroll_dwell) { this->scroll_dwell_ = scroll_dwell; }
  void set_scroll_delay(unsigned long scroll_delay) { this->scroll_delay_ = scroll_delay; }


  /// Evaluate the printf-format and print the result at the given position.
  uint8_t printf(uint8_t pos, bool clear_buffer, const char *format, ...) __attribute__((format(printf, 4, 5)));
  /// Evaluate the printf-format and print the result at position 0.
  //uint8_t printf(bool clear_buffer, const char *format, ...) __attribute__((format(printf, 3, 4)));

  /// Print `str` at the given position.
  uint8_t print(uint8_t pos, const char *str, bool clear_buffer);
  /// Print `str` at position 0.
  uint8_t print(const char *str, bool clear_buffer);

  /// Evaluate the strftime-format and print the result at the given position.
  uint8_t strftime(uint8_t pos, bool clear_buffer, const char *format, ESPTime time) __attribute__((format(strftime, 4, 0)));
  
  uint8_t clock_display(ESPTime time, uint8_t position, bool clear_buffer, bool show_leading_zero, bool UseAMPM);

  void blank();

  /// Evaluate the strftime-format and print the result at position 0.
  uint8_t strftime(const char *format, ESPTime time) __attribute__((format(strftime, 2, 0)));

 protected:
  std::vector<i2c::I2CDevice *> displays_ {this};

  //uint8_t device_type_;   //TODO: Is this used anywhere?
  uint8_t fist_char_location_;
  
  bool scroll_ {false};
  bool continuous_ {false};
  unsigned long scroll_speed_ {250};  //TODO: should these be initialized to zero??
  unsigned long scroll_dwell_ {2000};
  unsigned long scroll_delay_ {750};
  unsigned long last_scroll_ {0};

  uint8_t brightness_{15};     // Intensity of the display from 0 to 15 (most) TODO: Change to brightness?
  
  std::string char_buffer_;     //This buffer holds the entire character message to display.
  uint8_t buffer_[20];          //This buffer is used to send the raw bytes to the HT16k33 device. TODO: Make this 17?
  uint8_t char_buffer_size_;         //This is the length of the character buffer. I need to track this separately instead of just calling buffer.lenght(), since when I clear the buffer, it resets the size to 0. TODO: Maybe a different data type would be better here?
  
  optional<ht16k33_char_writer_t> writer_{};

};

}  // namespace ht16k33_char
}  // namespace esphome
