#pragma once

namespace esphome {
namespace dallas_pio {

static const char *const TAG = "dallas_pio";

static const uint8_t DALLAS_MODEL_DS2413 = 0xBA;
static const uint8_t DALLAS_MODEL_DS2406 = 0x12;
static const uint8_t DALLAS_MODEL_DS2408 = 0x29;
static const uint8_t DALLAS_COMMAND_PIO_ACCESS_READ = 0xF5;
static const uint8_t DALLAS_COMMAND_PIO_ACCESS_WRITE = 0x5A;
static const uint8_t DALLAS_COMMAND_PIO_ACK_SUCCESS = 0xAA;
static const uint8_t DALLAS_COMMAND_PIO_ACK_ERROR = 0xFF;

}  // namespace dallas_pio
}  // namespace esphome
