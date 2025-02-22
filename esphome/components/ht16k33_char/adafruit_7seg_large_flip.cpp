#include <unordered_map>
#include "esphome/core/log.h"

#include "adafruit_7seg_large_flip.h"

/***********
 *Notes for the 7 segment 1.2" display.
 *  Digit 1 is COM0
 *  Digit 2 is COM1
 *  DPs are COM2
 *  Digit 3 is COM3
 *  Digit 4 is COM4
 *  tempBuffer[5] = 0b00010000; this is the dp between the right two digits
 *  tempBuffer[5] = 0b00000010; this is the colon between the two sets of digits
 *  tempBuffer[5] = 0b00000100; this is the dp on the edge of the display. Roughly in line with the first decimal point above
 *  tempBuffer[5] = 0b00001000; This is the DP on the edge of the display. it is on the lower part of the display, further from being a decimal point.
 *
 *
 *For the flipped display:
 *A = D
 *B = E
 *C = F
 *D = A
 *E = B
 *F = C
 *G = G
 *To convert codes do this:
 *code&0x07<<3 | code&0x38 >> 3 | code& 0x40
 *
 *
 *
 */ 



//TODO: Are these namespace things needed for this?
namespace esphome {
namespace ht16k33_char {

static const char *const TAG = "ht16k33_char";  //TODO: Debug only, remove someday...


//Position is the position in the character buffer. position 0 is the begining of the buffer
//Returns the index of the next character to display in the buffer (what we would give as `position` to the next call to this function).
uint8_t Adafruit_7seg_large_flip::send_to_display(i2c::I2CDevice *display, uint8_t position){
  //ESP_LOGD(TAG, "Display type 1");
  
  uint8_t i;
  char char_to_find;
  bool special_character_found;
  const std::unordered_map<char, uint8_t> char_map = {
    {'0', 0x3F}, //The number zero
    {'1', 0x30},
    {'2', 0x5B},
    {'3', 0x79},
    {'4', 0x74},
    {'5', 0x6D},
    {'6', 0x6F},
    {'7', 0x38},
    {'8', 0x7F},
    {'9', 0x7D},
    {' ', 0x00}, //Blank space
    {'A', 0x7E},
    {'b', 0x67},
    {'C', 0x0F},
    {'c', 0x43},
    {'d', 0x73},
    {'E', 0x4F},
    {'F', 0x4E},
    {'G', 0x2F},
    {'H', 0x76},
    {'h', 0x66},
    {'I', 0x06},
    {'J', 0x31},
    {'L', 0x07},
    {'N', 0x3E},
    {'O', 0x3F}, //The capitol letter 'o'
    {'o', 0x63}, //The lower case letter 'o'
    {'P', 0x5E},
    {'r', 0x42},
    {'S', 0x6D},
    {'t', 0x47},
    {'U', 0x37},
    {'u', 0x23},
    {'Y', 0x75},
  };

  //TODO: colon at the end.

  const uint8_t digit_map[4] = {9, 7, 3, 1};
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
      break;
      //this->buffer_[digit_map[i]] = 0x00;
      //i++;
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
            /*if (i == 0) {
              //We want a colon before the first digit
              //ESP_LOGD(TAG, "colon before digit 0");
              this->buffer_[5] = this->buffer_[5] | 0b00001100;
              special_character_found = true;
              char_buffer_location++;
              continue;
            }*/
            if (i == 2) {
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
}

}  // namespace ht16k33_char
}  // namespace esphome
