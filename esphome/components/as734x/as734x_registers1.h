// #pragma once
// #include <cstdint>

// namespace esphome {
// namespace as734x {

// static constexpr uint8_t AS7341_NUM_CHANNELS = 10;
// static constexpr uint8_t AS7343_NUM_CHANNELS = 13;

// static constexpr uint8_t AS7343_CHIP_ID = 0b10000001;
// static constexpr uint8_t AS7343_ENABLE_PON_BIT = 0;
// static constexpr uint8_t AS7343_ENABLE_SP_EN_BIT = 1;
// static constexpr uint8_t AS7343_CFG0_REG_BANK_BIT = 4;
// static constexpr uint8_t AS7343_LED_ENABLE_BIT = 7;

// enum AS734xGain : uint8_t {
//   AS734x_GAIN_0_5X,
//   AS734x_GAIN_1X,
//   AS734x_GAIN_2X,
//   AS734x_GAIN_4X,
//   AS734x_GAIN_8X,
//   AS734x_GAIN_16X,
//   AS734x_GAIN_32X,
//   AS734x_GAIN_64X,
//   AS734x_GAIN_128X,
//   AS734x_GAIN_256X,
//   AS734x_GAIN_512X,
//   AS734x_GAIN_1024X,
//   AS734x_GAIN_2048X,
//   AS734x_MAX_GAIN
// };

// union AS7343RegStatus {
//   uint8_t raw;
//   struct {
//     uint8_t sint : 1;
//     uint8_t reserved_1 : 1;
//     uint8_t fint : 1;
//     uint8_t aint : 1;
//     uint8_t reserved_4_6 : 3;
//     uint8_t asat : 1;
//   } __attribute__((packed));
// };

// union AS7343RegStatus2 {
//   uint8_t raw;
//   struct {
//     uint8_t fdsat_digital : 1;
//     uint8_t fdsat_analog : 1;
//     uint8_t reserved_2 : 1;
//     uint8_t asat_analog : 1;
//     uint8_t asat_digital : 1;
//     uint8_t reserved_5 : 1;
//     uint8_t avalid : 1;
//     uint8_t reserved_7 : 1;
//   } __attribute__((packed));
// };

// union AS7343RegAStatus {
//   uint8_t raw;
//   struct {
//     AS734xGain again_status : 4;
//     uint8_t reserved_4_6 : 3;
//     uint8_t asat_status : 1;

//   } __attribute__((packed));
// };

// union AS7343RegLed {
//   uint8_t raw;
//   struct {
//     uint8_t drive_current : 7;  // current in mA = 4 + 2 * value;
//     bool led_enable : 1;
//   } __attribute__((packed));
// };

// }  // namespace as734x
// }  // namespace esphome
