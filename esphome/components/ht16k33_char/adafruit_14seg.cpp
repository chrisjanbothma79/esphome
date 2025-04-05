#include <unordered_map>
#include "esphome/core/log.h"
#include "adafruit_14seg.h"

/******************************************************************************
 *Adafruit 14 segment .56" displays
 *  Product Link: https://www.adafruit.com/product/1911
 *
 *  Device specific functions for the Adafruit 14 segment displays. Both right-side-up and
 *  upside-down orientations are supported. To use these in your device, use device type
 *  'ADAFRUIT_14_SEG' or 'ADAFRUIT_14_SEG_FLIPPED'. These devices can display pretty much all
 *  of the ASCII characters. If you ask it to print an unsupported character, that digit on the
 *  display will be left blank.
 *
 *  Schematic: https://learn.adafruit.com/assets/114463
 *  Display Datasheet: https://cdn-shop.adafruit.com/datasheets/CID2379.pdf
 *
 *****************************************************************************/

namespace esphome {
namespace ht16k33_char {

static const char *const TAG = "ht16k33_char";

// Position is the index in the character buffer of the first digit to display. position 0 is the
//  begining of the buffer Returns the index of the first character to display on the next display.
//  (what we would give as `position` to the next call to this function).
uint8_t Adafruit_14seg::send_to_display(i2c::I2CDevice *display, uint8_t position) {
  uint8_t i;
  char char_to_find;
  bool special_character_found;
  const std::unordered_map<char, uint16_t> char_map = {
      {' ', 0b0000000000000000}, // Space (blank digit)
      {'!', 0b0000000000000110}, // !
      {'"', 0b0000001000100000}, // "
      {'#', 0b0001001011001110}, // #
      {'$', 0b0001001011101101}, // $
      {'%', 0b0000110000100100}, // %
      {'&', 0b0010001101011101}, // &
      {'\'', 0b0000010000000000}, // '
      {'(', 0b0010010000000000}, // (
      {')', 0b0000100100000000}, // )
      {'*', 0b0011111111000000}, // *
      {'+', 0b0001001011000000}, // +
      {',', 0b0000100000000000}, // ,
      {'-', 0b0000000011000000}, // -
      {'/', 0b0000110000000000}, // Forward slash character '/'
      {'0', 0b0000110000111111}, // 0
      {'1', 0b0000000000000110}, // 1
      {'2', 0b0000000011011011}, // 2
      {'3', 0b0000000010001111}, // 3
      {'4', 0b0000000011100110}, // 4
      {'5', 0b0010000001101001}, // 5
      {'6', 0b0000000011111101}, // 6
      {'7', 0b0001010000000001}, // 7 (Fixed)
      {'8', 0b0000000011111111}, // 8
      {'9', 0b0000000011101111}, // 9
      {':', 0b0001001000000000}, // :
      {';', 0b0000101000000000}, // ;
      {'<', 0b0010010000000000}, // <
      {'=', 0b0000000011001000}, // =
      {'>', 0b0000100100000000}, // >
      {'?', 0b0001000010000011}, // ?
      {'@', 0b0000001010111011}, // @
      {'A', 0b0000000011110111}, // A
      {'B', 0b0001001010001111}, // B
      {'C', 0b0000000000111001}, // C
      {'D', 0b0001001000001111}, // D
      {'E', 0b0000000011111001}, // E
      {'F', 0b0000000001110001}, // F
      {'G', 0b0000000010111101}, // G
      {'H', 0b0000000011110110}, // H
      {'I', 0b0001001000000000}, // I
      {'J', 0b0000000000011110}, // J
      {'K', 0b0010010001110000}, // K
      {'L', 0b0000000000111000}, // L
      {'M', 0b0000010100110110}, // M
      {'N', 0b0010000100110110}, // N
      {'O', 0b0000000000111111}, // O
      {'P', 0b0000000011110011}, // P
      {'Q', 0b0010000000111111}, // Q
      {'R', 0b0010000011110011}, // R
      {'S', 0b0000000011101101}, // S
      {'T', 0b0001001000000001}, // T
      {'U', 0b0000000000111110}, // U
      {'V', 0b0000110000110000}, // V
      {'W', 0b0010100000110110}, // W
      {'X', 0b0010110100000000}, // X
      {'Y', 0b0001010100000000}, // Y
      {'Z', 0b0000110000001001}, // Z
      {'[', 0b0000000000111001}, // [
      {'\\', 0b0010000100000000}, // Backslash character '\'
      {']', 0b0000000000001111}, // ]
      {'^', 0b0000000000100011}, // ^ (Fixed)
      {'_', 0b0000000000001000}, // _
      {'`', 0b0000000100000000}, // `
      {'a', 0b0001000001011000}, // a
      {'b', 0b0010000001111000}, // b
      {'c', 0b0000000011011000}, // c
      {'d', 0b0000100010001110}, // d
      {'e', 0b0000100001011000}, // e
      {'f', 0b0000000001110001}, // f
      {'g', 0b0000000110001111}, // g (Fixed)
      {'h', 0b0001000001110000}, // h
      {'i', 0b0001000000000000}, // i
      {'j', 0b0000000000001110}, // j
      {'k', 0b0011011000000000}, // k
      {'l', 0b0000000000110000}, // l
      {'m', 0b0001000011010100}, // m
      {'n', 0b0001000001010000}, // n
      {'o', 0b0000000011011100}, // o
      {'p', 0b0000010001110001}, // p (fixed)
      {'q', 0b0010000011100011}, // q (fixed)
      {'r', 0b0000000001010000}, // r
      {'s', 0b0010000010001000}, // s TODO: change to the same as upper case?
      {'t', 0b0000000001111000}, // t
      {'u', 0b0000000000011100}, // u
      {'v', 0b0010000000000100}, // v
      {'w', 0b0010100000010100}, // w
      {'x', 0b0010100011000000}, // x TODO: change to the same as upper case?
      {'y', 0b0000001010001110}, // y (fixed)
      {'z', 0b0000100001001000}, // z TODO: change to the same as upper case?
      {'{', 0b0000100101001001}, // {
      {'|', 0b0001001000000000}, // |
      {'}', 0b0010010010001001}, // }
      {'~', 0b0000000011000000}, // ~ (fixed)
  };

  const uint8_t digit_map[4] = {1, 3, 5, 7};
  uint8_t char_buffer_location;

  this->buffer_[0] = HT16K33_DISPLAY_DATA_ADDRESS;

  // Clear any old data from the buffer
  for(int i = 1; i < 16; i++) {
    this->buffer_[i] = 0x00;
  }

  char_buffer_location = position;
  i = 0;
  special_character_found = false;

  // In this while loop, `i` represents the digit that will display the character. We count through
  // the four digits in the display and set them to the next four characters in the character buffer.
  while (i < 4) {
    if (char_buffer_location >= this->char_buffer_.length()) {
      // char_buffer_location is past the end of the character buffer.
      if (this->continuous_) {
        // We want a continuous display where the message starts over immediately.
        char_buffer_location = 0;
      } else {
        // Blank the digits past the end of the display.
        this->buffer_[digit_map[i]] = 0x00;
        i++;
      }
    }

    else {
      // The character to find is within the bounds of the buffer array.
      char_to_find = this->char_buffer_.at(char_buffer_location);
      auto it = char_map.find(char_to_find);
      if (it != char_map.end()) {
        this->buffer_[digit_map[i]]   = (uint8_t) ((it->second) & 0xFF);
        this->buffer_[digit_map[i] + 1] = (uint8_t) ((it->second >> 8) & 0xFF);
        special_character_found = false;
        i++;
      } else {
        // Look for special characters. For this display, the only special character is a period.
        //  Because of how scrolling works, if there is a period in the first location in the char
        //  buffer, the display will skip over it. So '.123' will be displayed as '123'. This is
        //  only true if the period is in exactly the first digit. If you want to display .123 on
        //  the display, you can make the char buffer '0.123' and it will display as expected.
        if (!special_character_found) {
          if (char_to_find == '.') {
            special_character_found = true;
            char_buffer_location++;
            if (i > 0) {
              // We can't put a period before the first digit.
              this->buffer_[digit_map[i - 1] + 1] |= 0x40;
            } else {
              // If there is a decimal point in the first location in the char buffer, skip over it.
              this->fist_char_location_++;
            }
            continue;
          }
        }

        // Digit is not in the map. Blank the digit.
        this->buffer_[digit_map[i]] = 0x00;
        special_character_found = false;
        i++;
      }

      char_buffer_location++;
    }
  }

  // We can have a period after the last digit. Handle that here
  if (!(char_buffer_location >= this->char_buffer_.length())) {
    char_to_find = this->char_buffer_.at(char_buffer_location);
    if (char_to_find == '.') {
      this->buffer_[digit_map[3] + 1] |= 0x40;
      char_buffer_location++;
    }
  }

  display->write(this->buffer_, 16, true);
  return char_buffer_location;
}

// Position is the position in the character buffer. position 0 is the begining of the buffer
// Returns the index of the first character to display in the buffer (what we would give as `position` to the next call
// to this function).
uint8_t Adafruit_14seg_flip::send_to_display(i2c::I2CDevice *display, uint8_t position) {
  uint8_t i;
  char char_to_find;
  const std::unordered_map<char, uint16_t> char_map = {
        { ' ', 0b0000000000000000 }, // Space (blank digit)
        { '!', 0b0000000000110000 }, //  !
        { '"', 0b0001000000000100 }, //  "
        { '#', 0b0001001011110001 }, //  #
        { '$', 0b0001001011101101 }, //  $
        { '%', 0b0000110000100100 }, //  %
        { '&', 0b0011000110101011 }, //  &
        { '\'', 0b0000100000000000 }, //  '
        { '(', 0b0000100100000000 }, //  (
        { ')', 0b0010010000000000 }, //  )
        { '*', 0b0011111111000000 }, //  *
        { '+', 0b0001001011000000 }, //  +
        { ',', 0b0000010000000000 }, //  ,
        { '-', 0b0000000011000000 }, //  -
        { '/', 0b0000110000000000 }, //  /
        { '0', 0b0000110000111111 }, //  0
        { '1', 0b0000000000110000 }, //  1
        { '2', 0b0000000011011011 }, //  2
        { '3', 0b0000000001111001 }, //  3
        { '4', 0b0000000011110100 }, //  4
        { '5', 0b0000000110001101 }, //  5
        { '6', 0b0000000011101111 }, //  6
        { '7', 0b0000101000001000 }, //  7
        { '8', 0b0000000011111111 }, //  8
        { '9', 0b0000000011111101 }, //  9
        { ':', 0b0001001000000000 }, //  :
        { ';', 0b0001010000000000 }, //  ;
        { '<', 0b0000100100000000 }, //  <
        { '=', 0b0000000011000001 }, //  =
        { '>', 0b0010010000000000 }, //  >
        { '?', 0b0000001001011000 }, //  ?
        { '@', 0b0001000001011111 }, //  @
        { 'A', 0b0000000011111110 }, //  A
        { 'B', 0b0001001001111001 }, //  B
        { 'C', 0b0000000000001111 }, //  C
        { 'D', 0b0001001000111001 }, //  D
        { 'E', 0b0000000011001111 }, //  E
        { 'F', 0b0000000010001110 }, //  F
        { 'G', 0b0000000001101111 }, //  G
        { 'H', 0b0000000011110110 }, //  H
        { 'I', 0b0001001000000000 }, //  I
        { 'J', 0b0000000000110011 }, //  J
        { 'K', 0b0000100110000110 }, //  K
        { 'L', 0b0000000000000111 }, //  L
        { 'M', 0b0010100000110110 }, //  M
        { 'N', 0b0010000100110110 }, //  N
        { 'O', 0b0000000000111111 }, //  O
        { 'P', 0b0000000011011110 }, //  P
        { 'Q', 0b0000000100111111 }, //  Q
        { 'R', 0b0000000111011110 }, //  R
        { 'S', 0b0000000011101101 }, //  S
        { 'T', 0b0001001000001000 }, //  T
        { 'U', 0b0000000000110111 }, //  U
        { 'V', 0b0000110000000110 }, //  V
        { 'W', 0b0000010100110110 }, //  W
        { 'X', 0b0010110100000000 }, //  X
        { 'Y', 0b0010101000000000 }, //  Y
        { 'Z', 0b0000110000001001 }, //  Z
        { '[', 0b0000000000001111 }, //  [
        { '\\', 0b0010000100000000 }, //  '\'
        { ']', 0b0000000000111001 }, //  ]
        { '^', 0b0000000000011100 }, //  ^
        { '_', 0b0000000000000001 }, //  _
        { '`', 0b0010000000000000 }, //  `
        { 'a', 0b0000001010000011 }, //  a
        { 'b', 0b0000000110000111 }, //  b
        { 'c', 0b0000000011000011 }, //  c
        { 'd', 0b0000010001110001 }, //  d
        { 'e', 0b0000010010000011 }, //  e
        { 'f', 0b0000000010001110 }, //  f
        { 'g', 0b0010000001111001 }, //  g
        { 'h', 0b0000001010000110 }, //  h
        { 'i', 0b0000001000000000 }, //  i
        { 'j', 0b0000000000110001 }, //  j
        { 'k', 0b0001101100000000 }, //  k
        { 'l', 0b0000000000000110 }, //  l
        { 'm', 0b0000001011100010 }, //  m
        { 'n', 0b0000001010000010 }, //  n
        { 'o', 0b0000000011100011 }, //  o
        { 'p', 0b0000100010001110 }, //  p
        { 'q', 0b0000000111011100 }, //  q
        { 'r', 0b0000000010000010 }, //  r
        { 's', 0b0000000101000001 }, //  s
        { 't', 0b0000000010000111 }, //  t
        { 'u', 0b0000000000100011 }, //  u
        { 'v', 0b0000000100100000 }, //  v
        { 'w', 0b0000010100100010 }, //  w
        { 'x', 0b0000010111000000 }, //  x
        { 'y', 0b0001000001110001 }, //  y
        { 'z', 0b0000010010000001 }, //  z
        { '{', 0b0010010010001001 }, //  {
        { '|', 0b0001001000000000 }, //  |
        { '}', 0b0000100101001001 }, //  }
        { '~', 0b0000000011000000 }, //  ~
  };

  const uint8_t digit_map[4] = {7, 5, 3, 1};
  uint8_t char_buffer_location;

  this->buffer_[0] = HT16K33_DISPLAY_DATA_ADDRESS;

  // Clear any old data from the buffer
  for(int i = 1; i < 16; i++) {
    this->buffer_[i] = 0x00;
  }

  char_buffer_location = position;
  i = 0;

  while (i < 4) {
    if (char_buffer_location >= this->char_buffer_.length()) {
      // char_buffer_location is past the end of the character buffer.
      if (this->continuous_) {
        // We want a continuous display where the message starts over immediately.
        char_buffer_location = 0;
      } else {
        // Blank the digits past the end of the display.
        this->buffer_[digit_map[i]] = 0x00;
        i++;
      }
    }

    else {
      // The character to find is within the bounds of the buffer array.
      char_to_find = this->char_buffer_.at(char_buffer_location);
      auto it = char_map.find(char_to_find);
      if (it != char_map.end()) {
        this->buffer_[digit_map[i]] = (uint8_t)((it->second) & 0xFF);
        this->buffer_[digit_map[i]+1] = (uint8_t)((it->second >> 8) & 0xFF);
        i++;
      } else {
        // Regarding special characters: With the display flipped, the decimal points are now on the
        //  top. I suppose I could count those as ' or `. For now I don't do that and just ignore
        //  the decimal points on the display. ' and ` can be displayed using the actual 14-segment
        //  digits, so I will leave them there.
        
        // Digit is not in the map. Blank the digit.
        this->buffer_[digit_map[i]] = 0x00;
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
