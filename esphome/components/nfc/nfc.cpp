#include "nfc.h"
#include <cstdio>
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace nfc {

static const char *const TAG = "nfc";

std::string format_uid(const std::vector<uint8_t> &uid) { return format_hex_pretty(uid, '-', false); }

std::string format_bytes(const std::vector<uint8_t> &bytes) { return format_hex_pretty(bytes, ' ', false); }

uint8_t guess_tag_type(uint8_t uid_length) {
  switch (uid_length) {
    case 0:
      return TAG_TYPE_UNKNOWN;
    case 4:
      return TAG_TYPE_MIFARE_CLASSIC;
    case 7:
    case 10:
      return TAG_TYPE_2;
    default:
      return TAG_TYPE_UNKNOWN;
  }
}

int8_t get_mifare_classic_ndef_start_index(const std::vector<uint8_t> &data) {
  for (int8_t i = 0; i < static_cast<int8_t>(MIFARE_CLASSIC_BLOCK_SIZE) && static_cast<size_t>(i) < data.size(); i++) {
    if (data[i] == 0x00) {
      // Do nothing, skip
    } else if (data[i] == 0x03) {
      return i;
    } else {
      return -2;
    }
  }
  return -1;
}

bool decode_mifare_classic_tlv(const std::vector<uint8_t> &data, uint32_t &message_length,
                               uint16_t &message_start_index) {
  int8_t i = get_mifare_classic_ndef_start_index(data);
  if (i < 0 || static_cast<size_t>(i) >= data.size()) {
    ESP_LOGE(TAG, "Invalid TLV start index: %d", i);
    return false;
  }
  if (data[i] != 0x03) {
    ESP_LOGE(TAG, "Can't decode message length.");
    return false;
  }
  if (static_cast<size_t>(i) + MIFARE_CLASSIC_LONG_TLV_SIZE > data.size()) {
    ESP_LOGE(TAG, "TLV too short: need %zu, have %zu", static_cast<size_t>(i) + MIFARE_CLASSIC_LONG_TLV_SIZE,
             data.size());
    return false;
  }
  if (data[i + 1] == 0xFF) {
    message_length = ((0xFF & data[i + 2]) << 8) | (0xFF & data[i + 3]);
    message_start_index = static_cast<uint16_t>(i) + MIFARE_CLASSIC_LONG_TLV_SIZE;
  } else {
    if (static_cast<size_t>(i) + MIFARE_CLASSIC_SHORT_TLV_SIZE > data.size()) {
      ESP_LOGE(TAG, "TLV too short: need %zu, have %zu", static_cast<size_t>(i) + MIFARE_CLASSIC_SHORT_TLV_SIZE,
               data.size());
      return false;
    }
    message_length = data[i + 1];
    message_start_index = static_cast<uint16_t>(i) + MIFARE_CLASSIC_SHORT_TLV_SIZE;
  }
  return true;
}

uint32_t get_mifare_ultralight_buffer_size(uint32_t message_length) {
  uint32_t buffer_size = message_length + 2 + 1;
  if (buffer_size % MIFARE_ULTRALIGHT_READ_SIZE != 0)
    buffer_size = ((buffer_size / MIFARE_ULTRALIGHT_READ_SIZE) + 1) * MIFARE_ULTRALIGHT_READ_SIZE;
  return buffer_size;
}

uint32_t get_mifare_classic_buffer_size(uint32_t message_length) {
  uint32_t buffer_size = message_length;
  if (message_length < 255) {
    buffer_size += MIFARE_CLASSIC_SHORT_TLV_SIZE + 1;
  } else {
    buffer_size += MIFARE_CLASSIC_LONG_TLV_SIZE + 1;
  }
  if (buffer_size % MIFARE_CLASSIC_BLOCK_SIZE != 0) {
    buffer_size = ((buffer_size / MIFARE_CLASSIC_BLOCK_SIZE) + 1) * MIFARE_CLASSIC_BLOCK_SIZE;
  }
  return buffer_size;
}

bool mifare_classic_is_first_block(uint8_t block_num) {
  if (block_num < MIFARE_CLASSIC_BLOCKS_PER_SECT_LOW * MIFARE_CLASSIC_16BLOCK_SECT_START) {
    return (block_num % MIFARE_CLASSIC_BLOCKS_PER_SECT_LOW == 0);
  } else {
    return (block_num % MIFARE_CLASSIC_BLOCKS_PER_SECT_HIGH == 0);
  }
}

bool mifare_classic_is_trailer_block(uint8_t block_num) {
  if (block_num < MIFARE_CLASSIC_BLOCKS_PER_SECT_LOW * MIFARE_CLASSIC_16BLOCK_SECT_START) {
    return ((block_num + 1) % MIFARE_CLASSIC_BLOCKS_PER_SECT_LOW == 0);
  } else {
    return ((block_num + 1) % MIFARE_CLASSIC_BLOCKS_PER_SECT_HIGH == 0);
  }
}

}  // namespace nfc
}  // namespace esphome
