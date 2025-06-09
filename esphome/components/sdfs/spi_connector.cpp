
#include "spi_connector.h"
#ifdef USE_SDSPI_MODE
// #include "SdFat.h"

namespace esphome {
namespace sdfs {

// SdFat fs;

static const char *const TAG = "spi_connector";

SpiConnector::SpiConnector() {}
bool SpiConnector::is_transaction() { return this->in_transaction; }
void SpiConnector::begin() { this->spi_setup(); }
void SpiConnector::end() { this->spi_teardown(); }
void SpiConnector::beginTransaction() {
  if (trans_level_ <= 0) {
    this->enable();
  } else {
#if defined(SPI_CALL_TRACE)
    ESP_LOGW(TAG, "Start Transaction when was in transaction.");
#endif
  }
  trans_level_++;
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "Transaction + Level=%d", trans_level_);
#endif
  // ESP_LOGV(TAG,"start transaction +");
  // if (! in_transaction )  {
  //   this->enable();
  //   in_transaction = true;
  // }
  // else {
  //   ESP_LOGW(TAG," Start Transaction when was in transaction");
  // }
}

void SpiConnector::endTransaction() {
  if (trans_level_ == 0) {
    ESP_LOGE(TAG, "close transaction w/o begin transaction");
  }
  trans_level_--;
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "Transaction - Level=%d", trans_level_);
#endif
  if (trans_level_ <= 0) {
    this->disable();
  }

  // ESP_LOGV(TAG,"end transaction -");
  // this->disable();
  // in_transaction = false;
}

uint8_t SpiConnector::transfer(uint8_t data) {
#if defined(SPI_CALL_TRACE)
// ESP_LOGV(TAG, "transfer  0x%.02X",data);
#endif
  return this->transfer_byte(data);
}

void SpiConnector::write16(uint16_t data) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "write16  0x%.04X", data);
#endif
  this->write_byte16(data);
}

void SpiConnector::write(uint8_t data) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "write 0x%.02X", data);
#endif
  this->write_byte(data);
}

void SpiConnector::write32(uint32_t data) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "write32  0x%.08X", data);
#endif
  std::array<uint8_t, 4> _value;
  _value[0] = data >> 24;
  _value[1] = data >> 16;
  _value[2] = data >> 8;
  _value[3] = data;

  this->write_array(_value);
}

uint16_t SpiConnector::transfer16(uint16_t data) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "transfer16  0x%.04X", data);
#endif
  std::array<uint8_t, 2> _value;
  _value[0] = data >> 8;
  _value[1] = data;

  this->transfer_array(_value);
  data = (_value[0] << 8) | (_value[1]);
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "transfer16 recv 0x%.04X", data);
#endif
  return data;
}

uint32_t SpiConnector::transfer32(uint32_t data) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "transfer32 0x%.08X", data);
#endif
  std::array<uint8_t, 4> _value;
  _value[0] = data >> 24;
  _value[1] = data >> 16;
  _value[2] = data >> 8;
  _value[3] = data;

  this->transfer_array(_value);

  data = (_value[0] << 24) | (_value[1] << 16) | (_value[2] << 8) | (_value[3]);
  // _value.empty();
  // delete _value;
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "transfer32  recv 0x%.08X", data);
#endif
  return data;
}

// void SpiConnector::transferBits(uint32_t data, uint32_t * out, uint8_t bits)
// {
//   ESP_LOGW(TAG,"Called uninmplemented function transferBits");
//   return;
// }

void SpiConnector::writeBytes(const uint8_t *data, uint32_t size) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "writeBytes data, len %d", size);
#endif
  this->write_array(data, size);
}

void SpiConnector::transfer(void *data, uint32_t size) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "transfer data, len %d", size);
#endif
  this->delegate_->transfer((uint8_t *) data, size);
}

// void SpiConnector::writePixels(const void * data, uint32_t size)
// {
//   ESP_LOGW(TAG,"Called uninmplemented function writePixels");
//   return;
// }

/**
 * @param data uint8_t * data buffer. can be NULL for Read Only operation
 * @param out  uint8_t * output buffer. can be NULL for Write Only operation
 * @param size uint32_t
 */
void SpiConnector::transferBytes(const uint8_t *data, uint8_t *out, uint32_t size) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "transferBytes %d bytes", size);
#endif
  uint8_t *txbuff = NULL;
  if (data == NULL) {
    txbuff = (uint8_t *) malloc(size);
    txbuff = (uint8_t *) memset(txbuff, 0xFF, size);
  } else {
    txbuff = (uint8_t *) data;
  }
  this->delegate_->transfer(txbuff, (uint8_t *) out, size);

  if (data == NULL) {
    free(txbuff);
  }
}

/**
 * @param data uint8_t *
 * @param size uint8_t  max for size is 64Byte
 * @param repeat uint32_t
 */
void SpiConnector::writePattern(const uint8_t *data, uint8_t size, uint32_t repeat) {
#if defined(SPI_CALL_TRACE)
  ESP_LOGV(TAG, "writePattern %d repeats", size);
#endif
  if (size > 64) {
    return;  // max Hardware FIFO
  }

  uint32_t byte = (size * repeat);
  uint8_t r = (64 / size);
  const uint8_t max_bytes_FIFO =
      r * size;  // Max number of whole patterns (in bytes) that can fit into the hardware FIFO

  while (byte) {
    if (byte > max_bytes_FIFO) {
      writePattern_(data, size, r);
      byte -= max_bytes_FIFO;
    } else {
      writePattern_(data, size, (byte / size));
      byte = 0;
    }
  }
}

void SpiConnector::writePattern_(const uint8_t *data, uint8_t size, uint8_t repeat) {
  uint8_t bytes = (size * repeat);
  uint8_t buffer[64];
  uint8_t *bufferPtr = &buffer[0];
  const uint8_t *dataPtr;
  uint8_t dataSize = bytes;
  for (uint8_t i = 0; i < repeat; i++) {
    dataSize = size;
    dataPtr = data;
    while (dataSize--) {
      *bufferPtr = *dataPtr;
      dataPtr++;
      bufferPtr++;
    }
  }
  this->write_array(&buffer[0], bytes);
}

#if defined(USE_SDSPI_MODE) && defined(USE_ESP8266)
/***********************************************************************
 *
 *    @brief  SdSpiImpl member function
 *
 */
SdSpiImpl::SdSpiImpl() { DEBUG_TRACE("SdSpiImpl:INIT"); }

void SdSpiImpl::set_spi(SpiConnector *c) {
  DEBUG_TRACE("SdSpiImpl:set_spi");
  connector_ = c;
}

void SdSpiImpl::begin() {
  DEBUG_TRACE("SdSpiImpl:begin");
  if (!connector_) {
    ESP_LOGE(TAG, "SPI connector unknown.  Run set_spi before.");
  } else {
    connector_->begin();
  }
}
void SdSpiImpl::end() {
  ESP_LOGD(TAG, "SdSpiImpl:end");
  this->connector_->end();
}
void SdSpiImpl::activate() {
  DEBUG_TRACE("SdSpiImpl:activate aka beginTransaction");
  this->connector_->beginTransaction();
}
void SdSpiImpl::deactivate() {
  DEBUG_TRACE("SdSpiImpl:deactivate aka endTransaction");
  this->connector_->endTransaction();
}
uint8_t SdSpiImpl::receive() {
  DEBUG_TRACE("SdSpiImpl:receive byte");
  return this->connector_->transfer(0xFF);
}
uint8_t SdSpiImpl::receive(uint8_t *buf, size_t count) {
  DEBUG_TRACE("SdSpiImpl:receive buffer");
  // this->connector_->transfer(buf,count);
  this->connector_->transferBytes(NULL, buf, count);
  // transferBytes
  return 0;
}
void SdSpiImpl::send(uint8_t data) {
  DEBUG_TRACE("SdSpiImpl:send ");
  this->connector_->write(data);
}
void SdSpiImpl::send(const uint8_t *buf, size_t count) {
  DEBUG_TRACE("SdSpiImpl:send  buffer");
  this->connector_->writeBytes(buf, count);
}
void SdSpiImpl::setSckSpeed(uint32_t maxSck) {
  DEBUG_TRACE("SdSpiImpl:setSckSpeed  %d", maxSck);
  // (void)maxSck;
}
#endif

}  // namespace sdfs
}  // namespace esphome
#endif