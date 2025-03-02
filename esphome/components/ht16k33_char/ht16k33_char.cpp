#include <unordered_map>

//#include "esphome/core/defines.h"   //TODO: needed to get access to the compiler define for device type
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"

#include "ht16k33_char.h"

/* To add more device types:
 *    -Add to the enum in the display.py file
 *    -Add a new .h and .c file that defines a class derived from the `HT16k33CharComponent` class.
 *    -Implement a `uint8_t send_to_display(i2c::I2CDevice *display, uint8_t position)` function in that class.
 */

//States for the scrolling state machine.
#define HT16K33_SCROLL_STATE_STATIC         0   //No scrolling. If this state is set, it will never change.
#define HT16K33_SCROLL_STATE_START          1
#define HT16K33_SCROLL_STATE_SCROLLING      2
#define HT16K33_SCROLL_STATE_END            3
#define HT16K33_SCROLL_STATE_FIRST_START    4

namespace esphome {
namespace ht16k33_char {

static const char *const TAG = "ht16k33_char";

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
  
  this->brightness(this->brightness_);  
  
  this->blank();
  this->char_buffer_.resize(this->char_buffer_size_, ' ');
  this->fist_char_location_ = 0;
  
  //Check to see if we need to scroll the display.
  if ( !(this->scroll_) ) {
    //Scrolling is off.
    this->scroll_state_ = HT16K33_SCROLL_STATE_STATIC;
  }
  else if (this->continuous_) {
    //If the state is continuous, there is not start and end delay. Go directly into the scrolling.
    this->scroll_state_ = HT16K33_SCROLL_STATE_SCROLLING;
    this->last_scroll_ = millis();
  }
  else {
    this->scroll_state_ = HT16K33_SCROLL_STATE_FIRST_START;
    this->last_scroll_ = millis();
  }
}

void HT16k33CharComponent::update() {
  //This checks if the lambda function is defined. If it is not defined, we don't do anything.
  if (this->writer_.has_value()) {
    //This line is responsible for calling the lambda code.
    (*this->writer_)(*this);
    
    //The lambda code does not actually update the display directly. It manipulates the char buffer.
    //  - If the display is static (no scrolling), we directly call display() to update the display now.
    //  - If scrolling is happening, we do not update the display in this function. The display will 
    //    be updated in the loop() function.
    if ( (this->scroll_state_ == HT16K33_SCROLL_STATE_STATIC) || 
         (this->scroll_state_ == HT16K33_SCROLL_STATE_FIRST_START) ) {
      this->update_display();
    }
  }
  //ESP_LOGD(TAG, "digits per display: %d", this->digits_per_display2_);
}

//Note: Scroll that is not continuous will go to the end of the buffer size, not the end of the message in the buffer.
void HT16k33CharComponent::loop() {
  uint32_t now;
  uint8_t current_buffer_location;
  
  if (this->scroll_state_ == HT16K33_SCROLL_STATE_STATIC) {
    //Check this first. If the display is static, we don't need to do anything in this function.
    return;
  }
  
  now = millis();
  
  if(this->last_scroll_ > now) {
    //This will happen when the millis() function overflows. (approx every 50 days)
    this->last_scroll_ = now;
    return;
  }
  
  switch (this->scroll_state_) {
    case HT16K33_SCROLL_STATE_START:
    case HT16K33_SCROLL_STATE_FIRST_START:
      if ( (now - this->last_scroll_) >= this->scroll_delay_) {
        //Start scrolling
        this->last_scroll_ = now;
        this->fist_char_location_++;
        current_buffer_location = this->update_display();    //Update the display
        if( current_buffer_location >= this->char_buffer_.length() ) {
          //We reached the end of the char buffer before we reached the end of the display. 
          // Scrolling is not required.
          this->scroll_state_ = HT16K33_SCROLL_STATE_STATIC;
        }
        else {
          this->scroll_state_ = HT16K33_SCROLL_STATE_SCROLLING;
        }
      }
      break;
    
    case HT16K33_SCROLL_STATE_SCROLLING:
      if ( (now - this->last_scroll_) >= this->scroll_speed_) {
        //Scroll to the next character.
        this->last_scroll_ = now;
        this->fist_char_location_++;
        if (this->fist_char_location_ >= this->char_buffer_.length()) {
          //This only happens in continuous mode.
          this->fist_char_location_ = 0;
        }
        current_buffer_location = this->update_display();    //Update the display
        
        if ( !(this->continuous_) && ((current_buffer_location+1) >= this->char_buffer_.length()) ) {
          //We have reached the end of the stuff to display. Go to the end delay.
          //The display does not need to be updated here.
          this->scroll_state_ = HT16K33_SCROLL_STATE_END;
        }
      }
      break;
    
    case HT16K33_SCROLL_STATE_END:
      if ( (now - this->last_scroll_) >= this->scroll_dwell_) {
        //Go back to the begining
        this->last_scroll_ = now;
        this->scroll_state_ = HT16K33_SCROLL_STATE_START;
        this->fist_char_location_ = 0;
        this->update_display();    //Update the display
      }
      break;
  }
}

void HT16k33CharComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "HT16K33 Char:");
  
  //ESP_LOGCONFIG(TAG, "  Device Type: ");  //TODO: Do I add a string to be able to show the device type?
  ESP_LOGCONFIG(TAG, "  Buffer Length: %d", this->char_buffer_size_);
  ESP_LOGCONFIG(TAG, "  Brightness: %d", this->brightness_);
  
  //Scrolling stuff
  if(this->scroll_){
    ESP_LOGCONFIG(TAG, "  Scrolling: Enabled");
    if(this->continuous_) {
      ESP_LOGCONFIG(TAG, "    Continuous: Yes");
    }
    else {
      ESP_LOGCONFIG(TAG, "    Continuous: No");
    }
    ESP_LOGCONFIG(TAG, "    Scroll Speed:       %0.2f sec", this->scroll_speed_/1000.);
    ESP_LOGCONFIG(TAG, "    Scroll Start Delay: %0.2f sec", this->scroll_delay_/1000.);
    ESP_LOGCONFIG(TAG, "    Scroll End Delay    %0.2f sec", this->scroll_dwell_/1000.);
  }
  else {
    ESP_LOGCONFIG(TAG, "  Scrolling: Disabled");
  }
  
  //Display device addresses.
  ESP_LOGCONFIG(TAG, "  Number of displays: %d", this->displays_.size());
  if (this->displays_.size() == 1) {
    //Only one display
    LOG_I2C_DEVICE(this);
  }
  else {
    //TODO: I2C address is protected, how do I display the address of the devices?
    //ESP_LOGCONFIG(TAG, "Device List:");
    //for (auto *display : this->displays_) {
    //  LOG_I2C_DEVICE(display);
    //}
  }
  
  if (this->is_failed()) {
    // Nothing in this code actually sets the device to failed, so this should never trigger.
    //  I am leaving this in incase I want to implement a check during init to verify the
    //  correct device is on the bus.
    ESP_LOGCONFIG(TAG, "  I2C Device at 0x0B does not appear to be a HT16K33");
  }
  LOG_UPDATE_INTERVAL(this);
}

//Zeros out all of the display memory on the device. This is not the same a turning it off, but it will have the same effect.
void HT16k33CharComponent::blank() {
  //ESP_LOGD(TAG, "Blank display");
  for (auto *display : this->displays_) {
    
    this->buffer_[0] = HT16K33_DISPLAY_DATA_ADDRESS;

    //Clear any old data from the buffer
    for(int i=1; i<16; i++) {
      this->buffer_[i] = 0x00;
    }
    
    display->write(this->buffer_, 16, true);
  }
}

uint8_t HT16k33CharComponent::update_display() {
  uint8_t buffer_location = this->fist_char_location_;
  
  for (auto *display : this->displays_) {
    buffer_location = this->send_to_display(display, buffer_location);
  }
  
  return buffer_location;
}

void HT16k33CharComponent::brightness(uint8_t brightness_to_set) {
  uint8_t buffer;
  
  if (brightness_to_set > 0x0F) {
    buffer = HT16K33_DIMMING_SET|0x0F;
  }
  else {
    buffer = HT16K33_DIMMING_SET|brightness_to_set;
  }

  for (auto *display : this->displays_) {
    display->write(&buffer, 1, true);
  }
  
}


//TODO: This function should take a character array and put it in the character buffer
//NOTE: start_pos is zero reference
uint8_t HT16k33CharComponent::print(uint8_t start_pos, const char *str, bool clear_buffer) {
  uint8_t top;
  uint8_t j;
  //ESP_LOGD(TAG, "print function:");
  //ESP_LOGD(TAG, "this in the print function %d", this);
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
  //ESP_LOGD(TAG, "end print function:");
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

  //ESP_LOGD(TAG, "time: %s, %d:%d", buffer, time.hour, time.minute);
  
  return this->print(position, buffer, clear_buffer);
}

}  // namespace ht16k33_char
}  // namespace esphome
