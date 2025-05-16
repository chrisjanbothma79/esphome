
#include "spi_connector.h"
#ifdef USE_ARDUINO_SPI_FS
// #include "SdFat.h"

namespace esphome {
namespace sdfs {

// SdFat fs;

static const char *const TAG = "spi_connector";

void SpiConnector::begin() { this->spi_setup(); }
void SpiConnector::end() { this->spi_teardown(); }
void SpiConnector::beginTransaction(SPISettings settings) {
  this->enable();
  this->in_transaction = true;
}

void SpiConnector::endTransaction() {
  this->disable();
  this->in_transaction = false;
}

// void SpiConnector::write(uint8_t data)
// {
//     this-
//     if(_inTransaction){
//         return spiWriteByteNL(_spi, data);
//     }
//     spiWriteByte(_spi, data);
// }

uint8_t SpiConnector::transfer(uint8_t data) { return this->transfer_byte(data); }

void SpiConnector::write16(uint16_t data) { this->write_byte16(data); }

void SpiConnector::write(uint8_t data) { this->write_byte(data); }

void SpiConnector::write32(uint32_t data) {
  std::array<uint8_t, 4> _value;
  _value[0] = data >> 24;
  _value[1] = data >> 16;
  _value[2] = data >> 8;
  _value[3] = data;

  this->write_array(_value);
}

uint16_t SpiConnector::transfer16(uint16_t data) {
  std::array<uint8_t, 4> _value;
  _value[2] = data >> 8;
  _value[3] = data;

  this->transfer_array(_value);
  data = (_value[3] << 8) | (_value[3]);
  return data;
}

uint32_t SpiConnector::transfer32(uint32_t data) {
  std::array<uint8_t, 4> _value;
  _value[0] = data >> 24;
  _value[1] = data >> 16;
  _value[2] = data >> 8;
  _value[3] = data;

  this->transfer_array(_value);
  data = (_value[0] << 24) | (_value[1] << 16) | (_value[2] << 8) | (_value[3]);
  return data;
}

// void SpiConnector::transferBits(uint32_t data, uint32_t * out, uint8_t bits)
// {
//   ESP_LOGW(TAG,"Called uninmplemented function writePixels");
//   return;
// }

void SpiConnector::writeBytes(const uint8_t *data, uint32_t size) { this->write_array(data, size); }

void SpiConnector::transfer(void *data, uint32_t size) {
  transferBytes((const uint8_t *) data, (uint8_t *) data, size);
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
  if (out == NULL) {
    write_array(data, size);
  } else if (data == NULL) {
    read_array(out, size);
  } else {
    memcpy(out, data, size);
    this->transfer_array(out, size);
  }
}

/**
 * @param data uint8_t *
 * @param size uint8_t  max for size is 64Byte
 * @param repeat uint32_t
 */
void SpiConnector::writePattern(const uint8_t *data, uint8_t size, uint32_t repeat) {
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

}  // namespace sdfs
}  // namespace esphome
#endif