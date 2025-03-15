#include "nrf24.h"
#include "esphome/core/log.h"

namespace esphome {
namespace nrf24 {

static const char *const TAG = "nrf24";

void nrf24::setup() {
  ESP_LOGCONFIG(TAG, "Setting up nrf24...");

  ce_pin_->setup();

  radio.begin();
  radio.setChannel(channel_);

  // Map generic PA levels to RF24 levels
  RF24_PA_e rf24_pa_level;
  switch (pa_level_) {
    case nrf24PALevel::LOW:
      rf24_pa_level = RF24_PA_LOW;
      break;
    case nrf24PALevel::MEDIUM:
      rf24_pa_level = RF24_PA_HIGH;  // Assuming HIGH is a reasonable "medium"
      break;
    case nrf24PALevel::HIGH:
      rf24_pa_level = RF24_PA_HIGH;
      break;
    case nrf24PALevel::MAX:
      rf24_pa_level = RF24_PA_MAX;
      break;
    default:
      rf24_pa_level = RF24_PA_HIGH;
      ESP_LOGW(TAG, "Invalid PA level, defaulting to HIGH");
      break;
  }
  radio.setPALevel(rf24_pa_level);

  radio.setDataRate(data_rate_);
  radio.setPayloadSize(payload_size_);
  radio.setRetries(retry_delay_, retry_count_);

  radio.openReadingPipe(1, address_);  // pipe 0 is not recommended
  ESP_LOGCONFIG(TAG, "Address is 0x%llX", address_);
  this->before_start_listening();
  radio.startListening();

  ESP_LOGCONFIG(TAG, "nrf24 setup complete");
}

void nrf24::loop() {
  if (radio.available()) {
    uint8_t len = radio.getPayloadSize();
    uint8_t data[len];
    radio.read(data, len);
    process_received_data(data, len);
  }
}

void nrf24::process_received_data(const uint8_t *data, uint8_t length) {
  // This is where derived components would process the received data
  ESP_LOGD(TAG, "Received data (length=%u):", length);
  ESP_LOGD(TAG, "Implement process_received_data in derived class to handle this data");
}

}  // namespace nrf24
}  // namespace esphome