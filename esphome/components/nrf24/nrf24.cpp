#include "nrf24.h"
#include "esphome/core/log.h"

namespace esphome {
namespace nrf24 {

static const char *const TAG = "nrf24";

void NRF24Device::setup_nrf24() {
  ESP_LOGD(TAG, "Setting up SPIDevice...");
  this->spi_setup();
  ESP_LOGCONFIG(TAG, "SPIDevice set up!");

  ESP_LOGCONFIG(TAG, "Setting up nRF24...");
  this->radio_ = new RF24(spi::Utility::get_pin_no(ce_pin_), spi::Utility::get_pin_no(cs_), this->data_rate_);

  if (!this->radio_->begin()) {
    ESP_LOGE(TAG, "Radio hardware not responding!");
    // this->mark_failed();
    return;
  }

  // Configure radio
  this->radio_->setChannel(this->channel_);
  this->radio_->setPALevel(static_cast<rf24_pa_dbm_e>(this->pa_level_));
  this->radio_->setDataRate(static_cast<rf24_datarate_e>(this->rf_data_rate_));
  this->radio_->setCRCLength(static_cast<rf24_crclength_e>(this->crc_length_));
  this->radio_->setPayloadSize(this->payload_size_);
  this->radio_->setRetries(this->retry_delay_, this->retry_count_);
  this->radio_->setAutoAck(this->auto_ack_);

  // Configure CRC
  if (this->crc_length_ == RF24_CRC_DISABLED) {
    this->radio_->disableCRC();
  }
  // Configure pipes
  if (this->write_address_ != 0) {
    this->radio_->openWritingPipe(this->write_address_);
  }

  for (const auto &pipe : this->pipes_) {
    this->radio_->openReadingPipe(pipe.pipe_num, pipe.address);
  }

  ESP_LOGCONFIG(TAG, "nRF24 setup complete");
}

void NRF24Device::dump_config() {
  ESP_LOGCONFIG(TAG, "nRF24:");
  LOG_PIN("  CE Pin: ", this->ce_pin_);
  LOG_PIN("  CS Pin: ", this->cs_);
  ESP_LOGCONFIG(TAG, "  Channel: %d", this->channel_);
  ESP_LOGCONFIG(TAG, "  PA Level: %d", this->pa_level_);
  ESP_LOGCONFIG(TAG, "  SPI Data Rate: %d", this->data_rate_);
  ESP_LOGCONFIG(TAG, "  RF Data Rate: %d", this->rf_data_rate_);
  ESP_LOGCONFIG(TAG, "  Payload Size: %d", this->payload_size_);
  ESP_LOGCONFIG(TAG, "  CRC Length: %d", this->crc_length_);
  ESP_LOGCONFIG(TAG, "  Auto ACK: %s", YESNO(this->auto_ack_));
  ESP_LOGCONFIG(TAG, "  Retry Delay: %d", this->retry_delay_);
  ESP_LOGCONFIG(TAG, "  Retry Count: %d", this->retry_count_);
  ESP_LOGCONFIG(TAG, "  Write Address: 0x%llX", this->write_address_);

  for (const auto &pipe : this->pipes_) {
    ESP_LOGCONFIG(TAG, "  Read pipe %d Address: 0x%llX", pipe.pipe_num, pipe.address);
  }
}

bool NRF24Device::write(const void* buf, uint8_t len) {
  return this->radio_->write(buf, len);
}

void NRF24Device::read(void* buf, uint8_t len) {
  this->radio_->read(buf, len);
}

bool NRF24Device::available() {
  return this->radio_->available();
}

void NRF24Device::start_listening() {
  this->radio_->startListening();
}

void NRF24Device::stop_listening() {
  this->radio_->stopListening();
}

}  // namespace nrf24
}  // namespace esphome