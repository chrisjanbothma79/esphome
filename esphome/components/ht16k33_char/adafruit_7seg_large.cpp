#include <unordered_map>
#include "esphome/core/log.h"

#include "adafruit_7seg_large.h"

/*
#include "esphome/core/defines.h"   //TODO: needed to get access to the compiler define for device type
#include "ht16k33_char.h"

#if HT16K33_CHAR_DISPLAY_TYPE == HT16K33_CHAR_TYPE_ADAFRUIT_7SEGMENT_1_2IN*/

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
 *************/


//TODO: Are these namespace things needed for this?
namespace esphome {
namespace ht16k33_char {

static const char *const TAG = "ht16k33_char";

//Position is the position in the character buffer. position 0 is the begining of the buffer
//Returns the index of the next character to display in the buffer (what we would give as `position` to the next call to this function).
uint8_t Adafruit_7seg_large::send_to_display(i2c::I2CDevice *display, uint8_t position){
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
    {'A', 0b01110111},
    {'b', 0b01111100},
    {'C', 0b00111001},
    {'c', 0b01011000},
    {'d', 0b01011110},
    {'E', 0b01111001},
    {'F', 0b01110001},
    {'G', 0b00111101},
    {'H', 0b01110110},
    {'h', 0b01110100},
    {'I', 0b00110000},
    {'J', 0b00001110},
    {'L', 0b00111000},
    {'N', 0b00110111},
    {'O', 0b00111111},  //The capitol letter 'o'
    {'o', 0b01011100},  //The lower case letter 'o'
    {'P', 0b01110011},
    {'r', 0b01010000},
    {'S', 0b01101101},
    {'t', 0b01111000},
    {'U', 0b00111110},
    {'u', 0b00011100},
    {'Y', 0b01101110},
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
}

}  // namespace ht16k33_char
}  // namespace esphome
