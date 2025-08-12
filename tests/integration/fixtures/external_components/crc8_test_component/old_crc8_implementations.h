#pragma once

#include <cstdint>

namespace esphome {
namespace crc8_test_component {

class OldCRC8Implementations {
 public:
  // Original AGS10 CRC8 implementation
  static uint8_t ags10_calc_crc8_(const uint8_t *data, uint8_t num);

  // Original AM2315C CRC8 implementation
  static uint8_t am2315c_crc8_(const uint8_t *data, uint8_t len);

  // Original HTE501 CRC8 implementation
  static uint8_t hte501_calc_crc8_(const uint8_t buf[], uint8_t from, uint8_t to);

  // Original LC709203F CRC8 implementation
  static uint8_t lc709203f_crc8_(const uint8_t *byte_buffer, uint8_t length_of_crc);

  // Original MLX90614 CRC8 PEC implementation
  static uint8_t mlx90614_crc8_pec_(const uint8_t *data, uint8_t len);

  // Original TEE501 CRC8 implementation
  static uint8_t tee501_calc_crc8_(const uint8_t buf[], uint8_t from, uint8_t to);
};

}  // namespace crc8_test_component
}  // namespace esphome
