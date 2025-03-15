#include "nrf24.h"
#include "esphome/core/log.h"

namespace esphome {
namespace nrf24 {

static const char *const TAG = "nrf24";

void NRF24Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up nRF24...");

  this->ce_pin_->setup();
  this->ce_pin_->digital_write(false);

  this->radio_ = new RF24(this->ce_pin_->get_pin(), this->cs_->get_pin());

  if (!this->radio_->begin()) {
    ESP_LOGE(TAG, "Radio hardware not responding!");
    this->mark_failed();
    return;
  }

  // Configure radio
  this->radio_->setChannel(this->channel_);
  this->radio_->setPALevel(static_cast<rf24_pa_dbm_e>(this->pa_level_));
  this->radio_->setDataRate(static_cast<rf24_datarate_e>(this->data_rate_));
  this->radio_->setCRCLength(static_cast<rf24_crclength_e>(this->crc_length_));
  this->radio_->setPayloadSize(this->payload_size_);
  this->radio_->setRetries(this->retry_delay_, this->retry_count_);

  // TODO: only open pipes if they are enabled; also address can be different for read and write
  this->radio_->openWritingPipe(this->address_);
  this->radio_->openReadingPipe(1, this->address_);
  // TODO: create a config for auto-ack and set it here
  if (this->crc_length_ == NRF24CRCLength::RF24_CRC_DISABLED) {
    this->radio_->disableCRC();
  }

  ESP_LOGCONFIG(TAG, "nRF24 setup complete");
}

void NRF24Component::dump_config() {
  ESP_LOGCONFIG(TAG, "nRF24:");
  LOG_PIN("  CE Pin: ", this->ce_pin_);
  LOG_PIN("  CS Pin: ", this->cs_);
  ESP_LOGCONFIG(TAG, "  Channel: %d", this->channel_);
  ESP_LOGCONFIG(TAG, "  PA Level: %d", this->pa_level_);
  ESP_LOGCONFIG(TAG, "  Data Rate: %d", this->data_rate_);
  ESP_LOGCONFIG(TAG, "  Payload Size: %d", this->payload_size_);
  ESP_LOGCONFIG(TAG, "  CRC Length: %d", this->crc_length_);
  ESP_LOGCONFIG(TAG, "  Retry Delay: %d", this->retry_delay_);
  ESP_LOGCONFIG(TAG, "  Retry Count: %d", this->retry_count_);
  ESP_LOGCONFIG(TAG, "  Address: 0x%lX", this->address_);
  // TODO: add new configs
}

bool NRF24Component::write(const void* buf, uint8_t len) {
  // TODO: check if write is enabled
  return this->radio_->write(buf, len);
}

bool NRF24Component::read(void* buf, uint8_t len) {
  // TODO: check if read is enabled
  return this->radio_->read(buf, len);
}

bool NRF24Component::available() {
  return this->radio_->available();
}

void NRF24Component::start_listening() {
  this->radio_->startListening();
}

void NRF24Component::stop_listening() {
  this->radio_->stopListening();
}

}  // namespace nrf24
}  // namespace esphome