#include "esphome/core/defines.h"   //TODO: needed to get access to the compiler define for device type
#include "esphome/core/log.h"
#include "ht16k33_char.h"

#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

#include <unordered_map>

namespace esphome {
namespace ht16k33_char {

static const char *const TAG = "ht16k33_char";

//Commands
static const uint8_t HT16K33_DISPLAY_DATA_ADDRESS = 0x00;
static const uint8_t HT16K33_SYSTEM_SETUP = 0x20;
static const uint8_t HT16K33_KEY_DATA_ADDRESS = 0x40;
static const uint8_t HT16K33_INT_FLAG_ADDRESS = 0x60;
static const uint8_t HT16K33_DISPLAY_SETUP = 0x80;
static const uint8_t HT16K33_ROW_INT_SET = 0xA0;
static const uint8_t HT16K33_DIMMING_SET = 0xE0;

static const uint8_t HT16K33_DISPLAY_OFF = 0x00;
static const uint8_t HT16K33_DISPLAY_ON = 0x01;
static const uint8_t HT16K33_MODE_STANDBY = 0x00;
static const uint8_t HT16K33_MODE_NORMAL = 0x01;

//Return a setup priority. More info here: https://esphome.io/api/namespaceesphome_1_1setup__priority
float HT16k33CharComponent::get_setup_priority() const { return setup_priority::PROCESSOR; }

void HT16k33CharComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up HT16K33...");
  uint8_t SetupBuffer;
  
  for (auto *display : this->displays_) {
    SetupBuffer = HT16K33_SYSTEM_SETUP|HT16K33_MODE_NORMAL;
    display->write(&SetupBuffer, 1, true);
  
    SetupBuffer = HT16K33_DISPLAY_SETUP|HT16K33_DISPLAY_ON;
    display->write(&SetupBuffer, 1, true);
  }
  
  this->blank();
  this->char_buffer_.resize(this->char_buffer_size_, ' ');
  this->fist_char_location_ = 0;
}

void HT16k33CharComponent::update() {
  //TODO: I will probably want to implement the scrolling stuff here
  //ESP_LOGD(TAG, "Update function");
  
  if (this->writer_.has_value()) {
    //This line is responsible for calling the lambda code.
    (*this->writer_)(*this);    
  }
  
  //The lambda code does not actually update the display directly. It manipulates the char buffer.
  //We call the display function to actually update the display after the lambda function is complete.
  this->display();
  
  ESP_LOGD(TAG, "Buffer: %s. Length is %d", this->char_buffer_.c_str(), this->char_buffer_.length());
}

void HT16k33CharComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "HT16K33:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    // Nothing in this code actually sets the device to failed, so this should never trigger.
    //  I am leaving this in incase I want to implement a check during init to verify the
    //  correct device is on the bus.
    ESP_LOGCONFIG(TAG, "  I2C Device at 0x0B does not appear to be a HT16K33");
  }
  LOG_UPDATE_INTERVAL(this);
}

/* To add more device types:
 *    -Add to the enum in the display.py file
 *    -Add a section to send_to_display() that implements the code to convert the char buffer into 
 *     the proper memory settings for the chip
 */


//Zeros out all of the display memory on the device. This is not the same a turning it off, but it will have the same effect.
void HT16k33CharComponent::blank() {
  for (auto *display : this->displays_) {
    
    this->buffer_[0] = HT16K33_DISPLAY_DATA_ADDRESS;

    //Clear any old data from the buffer
    for(int i=1; i<16; i++) {
      this->buffer_[i] = 0x00;
    }
    
    display->write(this->buffer_, 16, true);
  }
}


void HT16k33CharComponent::display() {
  uint8_t buffer_location = this->fist_char_location_;
  
  for (auto *display : this->displays_) {
    buffer_location = this->send_to_display(display, buffer_location);
  }
}

//TODO: This function should take a character array and put it in the character buffer
//NOTE: start_pos is zero reference
uint8_t HT16k33CharComponent::print(uint8_t start_pos, const char *str, bool clear_buffer) {
  uint8_t top;
  uint8_t j;
  //ESP_LOGD(TAG, "print function:");
  //ESP_LOGD(TAG, "Old Buffer: %s. Length is %d", this->char_buffer_.c_str(), this->char_buffer_.length());
  //ESP_LOGD(TAG, "Adding %s of length %d at location %d", str, strlen(str), start_pos);
  
  if (start_pos >= this->char_buffer_.length()) {
    //Start position is after the end of the buffer
    //ESP_LOGD(TAG, "Start position is beyond the end of the buffer");
    return 0;
  }
  
  if ((start_pos + strlen(str)) <= this->char_buffer_.length()) {
    //The entire string will fit in the buffer
    //ESP_LOGD(TAG, "New string fits in the buffer");
    top = (start_pos + strlen(str))-1;
  }
  else {
    //ESP_LOGD(TAG, "New string is too long for buffer");
    top = this->char_buffer_.length()-1;
  }
  
  if(clear_buffer) {
    //TODO: Does this reallocate memory? Should I step through the buffer and clear manually?
    //ESP_LOGD(TAG, "Clear buffer");
    this->char_buffer_.clear();
    this->char_buffer_.resize(this->char_buffer_size_, ' ');
  }
  
  j = 0;
  for(uint8_t i = start_pos; i<=top; i++) {
    //ESP_LOGD(TAG, "i = %d, buffer = %c, str = %c", i, this->char_buffer_.at(i), str[j]);
    this->char_buffer_.at(i) = str[j];
    j++;
  }
  
  //ESP_LOGD(TAG, "New Buffer: %s. Length is %d", this->char_buffer_.c_str(), this->char_buffer_.length());
  return 0;
}

uint8_t HT16k33CharComponent::print(const char *str, bool clear_buffer) { return this->print(0, str, clear_buffer); }

uint8_t HT16k33CharComponent::printf(uint8_t pos, bool clear_buffer, const char *format, ...) {
  va_list arg;
  va_start(arg, format);
  char buffer[this->char_buffer_size_+1];  //Add one for the string terminating character.
  int ret = vsnprintf(buffer, sizeof(buffer), format, arg);
  //ESP_LOGD(TAG, "printf: %s, size %d", buffer, sizeof(buffer));
  va_end(arg);
  
  //TODO: Why am I returning something here? change to void?
  return this->print(pos, buffer, clear_buffer);
}

uint8_t HT16k33CharComponent::strftime(uint8_t pos, bool clear_buffer, const char *format, ESPTime time) {
  char buffer[64];    //TODO: This buffer is really big, I should make it smaller.
  size_t ret = time.strftime(buffer, sizeof(buffer), format);
  if (ret > 0)
    return this->print(pos, buffer, clear_buffer);
  return 0;
}

uint8_t HT16k33CharComponent::clock_display(ESPTime time, uint8_t position, bool clear_buffer, bool show_leading_zero, bool UseAMPM){
  char buffer[6];
  //TODO: strftime is very memory intensive if all I need is hours and minutes. I could rewrite this to not use strftime and save a bunch of flash
  
  if (UseAMPM) {
    size_t ret = time.strftime(buffer, sizeof(buffer), "%I:%M");
  }
  else {
    size_t ret = time.strftime(buffer, sizeof(buffer), "%H:%M");
  }
  
  if((!show_leading_zero) && (buffer[0] == '0')) {
    //ESP_LOGD(TAG, "clear leading zero");
    buffer[0] = ' ';
  }

  ESP_LOGD(TAG, "time: %s, %d:%d", buffer, time.hour, time.minute);
  
  return this->print(position, buffer, clear_buffer);
}


//Notes for the 7 segment 1.2" display.
  //Digit 1 is COM0
  //Digit 2 is COM1
  //DPs are COM2
  //Digit 3 is COM3
  //Digit 4 is COM4
  //tempBuffer[5] = 0b00010000; this is the dp between the right two digits
  //tempBuffer[5] = 0b00000010; this is the colon between the two sets of digits
  //tempBuffer[5] = 0b00000100; this is the dp on the edge of the display. Roughly in line with the first decimal point above
  //tempBuffer[5] = 0b00001000; This is the DP on the edge of the display. it is on the lower part of the display, further from being a decimal point.


//Position is the position in the character buffer. position 0 is the begining of the buffer
//Returns the index of the next character to display in the buffer (what we would give as `position` to the next call to this function).
//TODO: There is probably a cleaner way to do this. I want to use compiler defines to only include code for the device type we are actually using. I could instead use different includes or something to move all this to a separate file.
uint8_t HT16k33CharComponent::send_to_display(i2c::I2CDevice *display, uint8_t position){
  #if HT16K33_CHAR_DISPLAY_TYPE == HT16K33_CHAR_TYPE_ADAFRUIT_7SEGMENT_1_2IN
    //ESP_LOGD(TAG, "Display type 1");
    
    uint8_t i;
    char char_to_find;
    bool special_character_found;
    const std::unordered_map<char, uint8_t> char_map = {
      {'0', 0b00111111},  //The number zero
      {'1', 0b00000110}, 
      {'2', 0b01011011},
      {'3', 0b01001111},
      {'4', 0b01100110},
      {'5', 0b01101101},
      {'6', 0b01111101},
      {'7', 0b00000111},
      {'8', 0b01111111},
      {'9', 0b01101111},
      {' ', 0b00000000},  //Blank space
      {'O', 0b00111111},  //The capitol letter 'o'
      {'A', 0b01110111},
      {'b', 0b01111100},
      {'C', 0b00111001},
      {'d', 0b01011110},
      {'E', 0b01111001},
      {'F', 0b01110001},
      {'r', 0b01010000},
      {'o', 0b01011100},  //The lower case letter 'o'
      {'N', 0b00110111},
      {'P', 0b01110011},
      {'L', 0b00111000},
      {'Y', 0b01101110},
      {'t', 0b01111000},
      {'U', 0b00111110},
      {'S', 0b01101101},
    };
  
    const uint8_t digit_map[4] = {1, 3, 7, 9};
    uint8_t char_buffer_location;

    this->buffer_[0] = HT16K33_DISPLAY_DATA_ADDRESS;

    //Clear any old data from the buffer
    for(int i=1; i<16; i++) {
      this->buffer_[i] = 0x00;
    }
  
    char_buffer_location = position;
    i = 0;
    special_character_found = false;
  
    while (i < 4) {
      if (char_buffer_location >= this->char_buffer_.length()) {
        //char_buffer_location is past the end of the character buffer. 
        //Blank the digits past the end of the display.
        //TODO: Is there a situation where we would not want to blank the digits? Maybe allow wrapping the digits?
        this->buffer_[digit_map[i]] = 0x00;
        i++;
      }
      
      else {
        //The character to find is within the bounds of the buffer array.
        char_to_find = this->char_buffer_.at(char_buffer_location);

        auto it = char_map.find(char_to_find);  //TODO: can I get rid of auto here?
        if (it != char_map.end()) {
          this->buffer_[digit_map[i]] = it->second;
          //ESP_LOGD(TAG, "char%d %c:%d", i, char_to_find, this->buffer_[digit_map[i]]);
          special_character_found = false;
          i++;
        }
        else {
          //Look for special characters. These characters are only valid at certain locations in the display. A special character in an invalid location will be treated the same way as an invalid character. In the case of an invalid character, that location in the display will be left blank. only one special character will be evaulated per location on the display.
          if(!special_character_found) {
            if(char_to_find == ':') {
              if (i == 0) {
                //We want a colon before the first digit
                //ESP_LOGD(TAG, "colon before digit 0");
                this->buffer_[5] = this->buffer_[5] | 0b00001100;
                special_character_found = true;
                char_buffer_location++;
                continue;
              }
              else if (i == 2) {
                //We want a colon between digit 2 and 3
                //ESP_LOGD(TAG, "colon before digit 2");
                this->buffer_[5] = this->buffer_[5] | 0b00000010;
                special_character_found = true;
                char_buffer_location++;
                continue;
              }
              //ESP_LOGD(TAG, "colon at invalid location");
            }
            else if(char_to_find == '\'' || char_to_find == '`') {
              if (i == 0) {
                //We want an apostrophe before the first digit
                //ESP_LOGD(TAG, "apostrophe before digit 0");
                this->buffer_[5] = this->buffer_[5] | 0b00000100;
                special_character_found = true;
                char_buffer_location++;
                continue;

              }
              else if (i == 3) {
                //We want an apostrophe before the fourth digit
                //ESP_LOGD(TAG, "apostrophe before digit 3");
                this->buffer_[5] = this->buffer_[5] | 0b00010000;
                special_character_found = true;
                char_buffer_location++;
                continue;
              }
              //ESP_LOGD(TAG, "apostrophe at invalid location");
            }
            else if(char_to_find == '.') {
              if (i == 0) {
                //We want an period before the first digit
                //ESP_LOGD(TAG, "period before digit 0");
                this->buffer_[5] = this->buffer_[5] | 0b00001000;
                special_character_found = true;
                char_buffer_location++;
                continue;
              }
              //ESP_LOGD(TAG, "period at invalid location");
            }
          }

          this->buffer_[digit_map[i]] = 0x00;
          //ESP_LOGD(TAG, "char%d %c is not in map", i, char_to_find);
          special_character_found = false;
          i++;
        }
      
        char_buffer_location++;
      }
    }

    display->write(this->buffer_, 16, true);
    return char_buffer_location;
    
  #elif HT16K33_CHAR_DISPLAY_TYPE == HT16K33_CHAR_TYPE_ADAFRUIT_14_SEG
    ESP_LOGD(TAG, "Display type 2");
    return 0;
  #else
    ESP_LOGD(TAG, "unknown disp type");
    return 0;
  #endif
}


}  // namespace ht16k33_char
}  // namespace esphome
