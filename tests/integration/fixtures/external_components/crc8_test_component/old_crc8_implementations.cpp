#include "old_crc8_implementations.h"

namespace esphome {
namespace crc8_test_component {

// Original AGS10 CRC8 implementation
uint8_t OldCRC8Implementations::ags10_calc_crc8_(const uint8_t *data, uint8_t num) {
  uint8_t i, byte1, crc = 0xFF;
  for (byte1 = 0; byte1 < num; byte1++) {
    crc ^= (data[byte1]);
    for (i = 0; i < 8; i++) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x31;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}

// Original AM2315C CRC8 implementation
uint8_t OldCRC8Implementations::am2315c_crc8_(const uint8_t *data, uint8_t len) {
  uint8_t crc = 0xFF;
  while (len--) {
    crc ^= *data++;
    for (uint8_t i = 0; i < 8; i++) {
      if (crc & 0x80) {
        crc <<= 1;
        crc ^= 0x31;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}

// Original HTE501 CRC8 implementation
uint8_t OldCRC8Implementations::hte501_calc_crc8_(const uint8_t buf[], uint8_t from, uint8_t to) {
  uint8_t crc_val = 0xFF;
  uint8_t i = 0;
  uint8_t j = 0;
  for (i = from; i <= to; i++) {
    int cur_val = buf[i];
    for (j = 0; j < 8; j++) {
      if (((crc_val ^ cur_val) & 0x80) != 0)  // If MSBs are not equal
      {
        crc_val = ((crc_val << 1) ^ 0x31);
      } else {
        crc_val = (crc_val << 1);
      }
      cur_val = cur_val << 1;
    }
  }
  return crc_val;
}

// Original LC709203F CRC8 implementation
uint8_t OldCRC8Implementations::lc709203f_crc8_(const uint8_t *byte_buffer, uint8_t length_of_crc) {
  uint8_t crc = 0x00;
  const uint8_t polynomial(0x07);

  for (uint8_t j = length_of_crc; j; --j) {
    crc ^= *byte_buffer++;

    for (uint8_t i = 8; i; --i) {
      crc = (crc & 0x80) ? (crc << 1) ^ polynomial : (crc << 1);
    }
  }
  return crc;
}

// Original MLX90614 CRC8 PEC implementation
uint8_t OldCRC8Implementations::mlx90614_crc8_pec_(const uint8_t *data, uint8_t len) {
  uint8_t crc = 0;
  for (uint8_t i = 0; i < len; i++) {
    uint8_t in = data[i];
    for (uint8_t j = 0; j < 8; j++) {
      bool carry = (crc ^ in) & 0x80;
      crc <<= 1;
      if (carry)
        crc ^= 0x07;
      in <<= 1;
    }
  }
  return crc;
}

// Original TEE501 CRC8 implementation
uint8_t OldCRC8Implementations::tee501_calc_crc8_(const uint8_t buf[], uint8_t from, uint8_t to) {
  uint8_t crc_val = 0xFF;
  uint8_t i = 0;
  uint8_t j = 0;
  for (i = from; i <= to; i++) {
    int cur_val = buf[i];
    for (j = 0; j < 8; j++) {
      if (((crc_val ^ cur_val) & 0x80) != 0)  // If MSBs are not equal
      {
        crc_val = ((crc_val << 1) ^ 0x31);
      } else {
        crc_val = (crc_val << 1);
      }
      cur_val = cur_val << 1;
    }
  }
  return crc_val;
}

}  // namespace crc8_test_component
}  // namespace esphome
