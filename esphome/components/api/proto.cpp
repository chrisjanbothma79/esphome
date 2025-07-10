#include "proto.h"
#include <cinttypes>
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "api_pb2_size.h"

namespace esphome {
namespace api {

static const char *const TAG = "api.proto";

void ProtoMessage::decode(const uint8_t *buffer, size_t length) {
  // Use V2 type-based implementation if available
  if (get_field_metadata_v2() != nullptr || get_repeated_field_metadata_v2() != nullptr) {
    decode_v2(buffer, length);
    return;
  }

  // Fall back to old implementation
  uint32_t i = 0;
  bool error = false;
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  // Get metadata once at the start
  const FieldMeta *fields = get_field_metadata();
  size_t field_count = get_field_count();
  const RepeatedFieldMeta *repeated_fields = get_repeated_field_metadata();
  size_t repeated_count = get_repeated_field_count();

  while (i < length) {
    uint32_t consumed;
    auto res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
    if (!res.has_value()) {
      ESP_LOGV(TAG, "Invalid field start at %" PRIu32, i);
      break;
    }

    uint32_t field_type = (res->as_uint32()) & 0b111;
    uint32_t field_id = (res->as_uint32()) >> 3;
    i += consumed;

    switch (field_type) {
      case 0: {  // VarInt
        res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
        if (!res.has_value()) {
          ESP_LOGV(TAG, "Invalid VarInt at %" PRIu32, i);
          error = true;
          break;
        }
        ProtoVarInt value = *res;
        bool decoded = false;

        // Check regular fields
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && fields[j].wire_type == 0) {
            void *field_addr = base + fields[j].offset;
            decoded = fields[j].decoder.decode_varint(field_addr, value);
            break;
          }
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && repeated_fields[j].wire_type == 0) {
              void *field_addr = base + repeated_fields[j].offset;
              decoded = repeated_fields[j].decoder.decode_varint(field_addr, value);
              break;
            }
          }
        }

        if (!decoded) {
          ESP_LOGV(TAG, "Cannot decode VarInt field %" PRIu32 " with value %" PRIu32 "!", field_id, res->as_uint32());
        }
        i += consumed;
        break;
      }
      case 2: {  // Length-delimited
        res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
        if (!res.has_value()) {
          ESP_LOGV(TAG, "Invalid Length Delimited at %" PRIu32, i);
          error = true;
          break;
        }
        uint32_t field_length = res->as_uint32();
        i += consumed;
        if (field_length > length - i) {
          ESP_LOGV(TAG, "Out-of-bounds Length Delimited at %" PRIu32, i);
          error = true;
          break;
        }
        ProtoLengthDelimited value(&buffer[i], field_length);
        bool decoded = false;

        // Check regular fields
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && fields[j].wire_type == 2) {
            void *field_addr = base + fields[j].offset;
            decoded = fields[j].decoder.decode_length(field_addr, value);
            break;
          }
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && repeated_fields[j].wire_type == 2) {
              void *field_addr = base + repeated_fields[j].offset;
              decoded = repeated_fields[j].decoder.decode_length(field_addr, value);
              break;
            }
          }
        }

        if (!decoded) {
          ESP_LOGV(TAG, "Cannot decode Length Delimited field %" PRIu32 "!", field_id);
        }
        i += field_length;
        break;
      }
      case 5: {  // 32-bit
        if (length - i < 4) {
          ESP_LOGV(TAG, "Out-of-bounds Fixed32-bit at %" PRIu32, i);
          error = true;
          break;
        }
        uint32_t val = encode_uint32(buffer[i + 3], buffer[i + 2], buffer[i + 1], buffer[i]);
        Proto32Bit value(val);
        bool decoded = false;

        // Check regular fields
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && fields[j].wire_type == 5) {
            void *field_addr = base + fields[j].offset;
            decoded = fields[j].decoder.decode_32bit(field_addr, value);
            break;
          }
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && repeated_fields[j].wire_type == 5) {
              void *field_addr = base + repeated_fields[j].offset;
              decoded = repeated_fields[j].decoder.decode_32bit(field_addr, value);
              break;
            }
          }
        }

        if (!decoded) {
          ESP_LOGV(TAG, "Cannot decode 32-bit field %" PRIu32 " with value %" PRIu32 "!", field_id, val);
        }
        i += 4;
        break;
      }
      default:
        ESP_LOGV(TAG, "Invalid field type at %" PRIu32, i);
        error = true;
        break;
    }
    if (error) {
      break;
    }
  }
}

#ifdef HAS_PROTO_MESSAGE_DUMP
std::string ProtoMessage::dump() const {
  std::string out;
  this->dump_to(out);
  return out;
}
#endif

// Type-specific encoding functions
void encode_string_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *str = static_cast<const std::string *>(field_ptr);
  buffer.encode_string(field_num, *str);
}

void encode_fixed32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const uint32_t *>(field_ptr);
  buffer.encode_fixed32(field_num, *val);
}

void encode_bool_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const bool *>(field_ptr);
  buffer.encode_bool(field_num, *val);
}

void encode_float_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const float *>(field_ptr);
  buffer.encode_float(field_num, *val);
}

void encode_int32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const int32_t *>(field_ptr);
  buffer.encode_int32(field_num, *val);
}

void encode_uint32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const uint32_t *>(field_ptr);
  buffer.encode_uint32(field_num, *val);
}

void encode_int64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const int64_t *>(field_ptr);
  buffer.encode_int64(field_num, *val);
}

void encode_uint64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const uint64_t *>(field_ptr);
  buffer.encode_uint64(field_num, *val);
}

void encode_sint32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const int32_t *>(field_ptr);
  buffer.encode_sint32(field_num, *val);
}

void encode_sint64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const int64_t *>(field_ptr);
  buffer.encode_sint64(field_num, *val);
}

void encode_fixed64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const uint64_t *>(field_ptr);
  buffer.encode_fixed64(field_num, *val);
}

void encode_double_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const double *>(field_ptr);
  union {
    double value;
    uint64_t raw;
  } u{};
  u.value = *val;
  buffer.encode_fixed64(field_num, u.raw);
}

void encode_bytes_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *str = static_cast<const std::string *>(field_ptr);
  buffer.encode_bytes(field_num, reinterpret_cast<const uint8_t *>(str->data()), str->size());
}

// Type-specific size calculation functions
void size_string_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *str = static_cast<const std::string *>(field_ptr);
  ProtoSize::add_string_field(total_size, precalced_field_id_size, *str, force);
}

void size_fixed32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const uint32_t *>(field_ptr);
  ProtoSize::add_fixed_field<4>(total_size, precalced_field_id_size, *val != 0 || force, force);
}

void size_bool_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const bool *>(field_ptr);
  ProtoSize::add_bool_field(total_size, precalced_field_id_size, *val, force);
}

void size_float_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const float *>(field_ptr);
  ProtoSize::add_fixed_field<4>(total_size, precalced_field_id_size, *val != 0.0f || force, force);
}

void size_int32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const int32_t *>(field_ptr);
  ProtoSize::add_int32_field(total_size, precalced_field_id_size, *val, force);
}

void size_uint32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const uint32_t *>(field_ptr);
  ProtoSize::add_uint32_field(total_size, precalced_field_id_size, *val, force);
}

void size_int64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const int64_t *>(field_ptr);
  ProtoSize::add_int64_field(total_size, precalced_field_id_size, *val, force);
}

void size_uint64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const uint64_t *>(field_ptr);
  ProtoSize::add_uint64_field(total_size, precalced_field_id_size, *val, force);
}

void size_sint32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const int32_t *>(field_ptr);
  ProtoSize::add_sint32_field(total_size, precalced_field_id_size, *val, force);
}

void size_sint64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const int64_t *>(field_ptr);
  ProtoSize::add_sint64_field(total_size, precalced_field_id_size, *val, force);
}

void size_fixed64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const uint64_t *>(field_ptr);
  ProtoSize::add_fixed_field<8>(total_size, precalced_field_id_size, *val != 0 || force, force);
}

void size_double_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const double *>(field_ptr);
  ProtoSize::add_fixed_field<8>(total_size, precalced_field_id_size, *val != 0.0 || force, force);
}

void size_bytes_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *str = static_cast<const std::string *>(field_ptr);
  ProtoSize::add_string_field(total_size, precalced_field_id_size, *str, force);
}

// Type-specific decode functions
bool decode_string_field(void *field_ptr, ProtoLengthDelimited value) {
  auto *str = static_cast<std::string *>(field_ptr);
  *str = value.as_string();
  return true;
}

bool decode_fixed32_field(void *field_ptr, Proto32Bit value) {
  auto *val = static_cast<uint32_t *>(field_ptr);
  *val = value.as_fixed32();
  return true;
}

bool decode_bool_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<bool *>(field_ptr);
  *val = value.as_bool();
  return true;
}

bool decode_float_field(void *field_ptr, Proto32Bit value) {
  auto *val = static_cast<float *>(field_ptr);
  *val = value.as_float();
  return true;
}

bool decode_int32_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<int32_t *>(field_ptr);
  *val = value.as_int32();
  return true;
}

bool decode_uint32_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<uint32_t *>(field_ptr);
  *val = value.as_uint32();
  return true;
}

bool decode_int64_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<int64_t *>(field_ptr);
  *val = value.as_int64();
  return true;
}

bool decode_uint64_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<uint64_t *>(field_ptr);
  *val = value.as_uint64();
  return true;
}

bool decode_sint32_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<int32_t *>(field_ptr);
  *val = value.as_sint32();
  return true;
}

bool decode_sint64_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<int64_t *>(field_ptr);
  *val = value.as_sint64();
  return true;
}

bool decode_fixed64_field(void *field_ptr, Proto64Bit value) {
  auto *val = static_cast<uint64_t *>(field_ptr);
  *val = value.as_fixed64();
  return true;
}

bool decode_double_field(void *field_ptr, Proto64Bit value) {
  auto *val = static_cast<double *>(field_ptr);
  *val = value.as_double();
  return true;
}

bool decode_bytes_field(void *field_ptr, ProtoLengthDelimited value) {
  auto *str = static_cast<std::string *>(field_ptr);
  *str = value.as_string();
  return true;
}

// Template functions are now in the header file for proper instantiation

// Repeated field encoding functions
void encode_repeated_string_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<std::string> *>(field_ptr);
  for (const auto &item : *vec) {
    buffer.encode_string(field_num, item, true);
  }
}

void encode_repeated_bool_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<bool> *>(field_ptr);
  for (bool val : *vec) {
    buffer.encode_bool(field_num, val, true);
  }
}

void encode_repeated_uint32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<uint32_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_uint32(field_num, val, true);
  }
}

void encode_repeated_int32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<int32_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_int32(field_num, val, true);
  }
}

void encode_repeated_uint64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<uint64_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_uint64(field_num, val, true);
  }
}

void encode_repeated_int64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<int64_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_int64(field_num, val, true);
  }
}

void encode_repeated_sint32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<int32_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_sint32(field_num, val, true);
  }
}

void encode_repeated_sint64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<int64_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_sint64(field_num, val, true);
  }
}

void encode_repeated_fixed32_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<uint32_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_fixed32(field_num, val, true);
  }
}

void encode_repeated_fixed64_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<uint64_t> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_fixed64(field_num, val, true);
  }
}

void encode_repeated_float_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<float> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_float(field_num, val, true);
  }
}

void encode_repeated_double_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<double> *>(field_ptr);
  for (const auto &val : *vec) {
    union {
      double value;
      uint64_t raw;
    } u{};
    u.value = val;
    buffer.encode_fixed64(field_num, u.raw, true);
  }
}

// Template repeated field functions moved to header

// Repeated field size calculation functions
void size_repeated_string_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<std::string> *>(field_ptr);
  for (const auto &item : *vec) {
    ProtoSize::add_string_field(total_size, precalced_field_id_size, item, true);
  }
}

void size_repeated_bool_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<bool> *>(field_ptr);
  for (bool val : *vec) {
    ProtoSize::add_bool_field(total_size, precalced_field_id_size, val, true);
  }
}

void size_repeated_uint32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<uint32_t> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_uint32_field(total_size, precalced_field_id_size, val, true);
  }
}

void size_repeated_int32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<int32_t> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_int32_field(total_size, precalced_field_id_size, val, true);
  }
}

void size_repeated_uint64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<uint64_t> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_uint64_field(total_size, precalced_field_id_size, val, true);
  }
}

void size_repeated_int64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<int64_t> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_int64_field(total_size, precalced_field_id_size, val, true);
  }
}

void size_repeated_sint32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<int32_t> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_sint32_field(total_size, precalced_field_id_size, val, true);
  }
}

void size_repeated_sint64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<int64_t> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_sint64_field(total_size, precalced_field_id_size, val, true);
  }
}

void size_repeated_fixed32_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<uint32_t> *>(field_ptr);
  size_t count = vec->size();
  if (count > 0) {
    total_size += count * (precalced_field_id_size + 4);  // field tag + 4 bytes per item
  }
}

void size_repeated_fixed64_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<uint64_t> *>(field_ptr);
  size_t count = vec->size();
  if (count > 0) {
    total_size += count * (precalced_field_id_size + 8);  // field tag + 8 bytes per item
  }
}

void size_repeated_float_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<float> *>(field_ptr);
  size_t count = vec->size();
  if (count > 0) {
    total_size += count * (precalced_field_id_size + 4);  // field tag + 4 bytes per item
  }
}

void size_repeated_double_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<double> *>(field_ptr);
  size_t count = vec->size();
  if (count > 0) {
    total_size += count * (precalced_field_id_size + 8);  // field tag + 8 bytes per item
  }
}

// Template size functions moved to header

// Repeated field decode functions
bool decode_repeated_string_field(void *field_ptr, ProtoLengthDelimited value) {
  auto *vec = static_cast<std::vector<std::string> *>(field_ptr);
  vec->push_back(value.as_string());
  return true;
}

bool decode_repeated_bool_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<bool> *>(field_ptr);
  vec->push_back(value.as_bool());
  return true;
}

bool decode_repeated_uint32_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<uint32_t> *>(field_ptr);
  vec->push_back(value.as_uint32());
  return true;
}

bool decode_repeated_int32_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<int32_t> *>(field_ptr);
  vec->push_back(value.as_int32());
  return true;
}

bool decode_repeated_uint64_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<uint64_t> *>(field_ptr);
  vec->push_back(value.as_uint64());
  return true;
}

bool decode_repeated_int64_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<int64_t> *>(field_ptr);
  vec->push_back(value.as_int64());
  return true;
}

bool decode_repeated_sint32_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<int32_t> *>(field_ptr);
  vec->push_back(value.as_sint32());
  return true;
}

bool decode_repeated_sint64_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<int64_t> *>(field_ptr);
  vec->push_back(value.as_sint64());
  return true;
}

bool decode_repeated_fixed32_field(void *field_ptr, Proto32Bit value) {
  auto *vec = static_cast<std::vector<uint32_t> *>(field_ptr);
  vec->push_back(value.as_fixed32());
  return true;
}

bool decode_repeated_fixed64_field(void *field_ptr, Proto64Bit value) {
  auto *vec = static_cast<std::vector<uint64_t> *>(field_ptr);
  vec->push_back(value.as_fixed64());
  return true;
}

bool decode_repeated_float_field(void *field_ptr, Proto32Bit value) {
  auto *vec = static_cast<std::vector<float> *>(field_ptr);
  vec->push_back(value.as_float());
  return true;
}

bool decode_repeated_double_field(void *field_ptr, Proto64Bit value) {
  auto *vec = static_cast<std::vector<double> *>(field_ptr);
  vec->push_back(value.as_double());
  return true;
}

// Core shared functions
void encode_from_metadata(ProtoWriteBuffer buffer, const void *obj, const FieldMeta *fields, size_t field_count,
                          const RepeatedFieldMeta *repeated_fields, size_t repeated_count) {
  const uint8_t *base = static_cast<const uint8_t *>(obj);

  // Encode regular fields
  for (size_t i = 0; i < field_count; i++) {
    const void *field_addr = base + fields[i].offset;
    fields[i].encoder(buffer, field_addr, fields[i].field_num);
  }

  // Encode repeated fields
  for (size_t i = 0; i < repeated_count; i++) {
    const void *field_addr = base + repeated_fields[i].offset;
    repeated_fields[i].encoder(buffer, field_addr, repeated_fields[i].field_num);
  }
}

void calculate_size_from_metadata(uint32_t &total_size, const void *obj, const FieldMeta *fields, size_t field_count,
                                  const RepeatedFieldMeta *repeated_fields, size_t repeated_count) {
  const uint8_t *base = static_cast<const uint8_t *>(obj);

  // Calculate size for regular fields
  for (size_t i = 0; i < field_count; i++) {
    const void *field_addr = base + fields[i].offset;
    fields[i].sizer(total_size, field_addr, fields[i].precalced_field_id_size, fields[i].force_encode);
  }

  // Calculate size for repeated fields
  for (size_t i = 0; i < repeated_count; i++) {
    const void *field_addr = base + repeated_fields[i].offset;
    repeated_fields[i].sizer(total_size, field_addr, repeated_fields[i].precalced_field_id_size);
  }
}

// ProtoMessage implementations using metadata
void ProtoMessage::encode(ProtoWriteBuffer buffer) const {
  if (get_field_metadata_v2() != nullptr || get_repeated_field_metadata_v2() != nullptr) {
    encode_v2(buffer);
  } else {
    encode_from_metadata(buffer, this, get_field_metadata(), get_field_count(), get_repeated_field_metadata(),
                         get_repeated_field_count());
  }
}

void ProtoMessage::calculate_size(uint32_t &total_size) const {
  if (get_field_metadata_v2() != nullptr || get_repeated_field_metadata_v2() != nullptr) {
    calculate_size_v2(total_size);
  } else {
    calculate_size_from_metadata(total_size, this, get_field_metadata(), get_field_count(),
                                 get_repeated_field_metadata(), get_repeated_field_count());
  }
}

// Type-based decode implementation
void ProtoMessage::decode_v2(const uint8_t *buffer, size_t length) {
  uint32_t i = 0;
  bool error = false;
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  // Get V2 metadata once at the start
  const FieldMetaV2 *fields = get_field_metadata_v2();
  size_t field_count = get_field_count_v2();
  const RepeatedFieldMetaV2 *repeated_fields = get_repeated_field_metadata_v2();
  size_t repeated_count = get_repeated_field_count_v2();

  while (i < length) {
    uint32_t consumed;
    auto res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
    if (!res.has_value()) {
      ESP_LOGV(TAG, "Invalid field start at %" PRIu32, i);
      break;
    }

    uint32_t field_type = (res->as_uint32()) & 0b111;
    uint32_t field_id = (res->as_uint32()) >> 3;
    i += consumed;

    switch (field_type) {
      case 0: {  // VarInt
        res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
        if (!res.has_value()) {
          ESP_LOGV(TAG, "Invalid VarInt at %" PRIu32, i);
          error = true;
          break;
        }
        ProtoVarInt value = *res;
        bool decoded = false;

        // Check regular fields
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].type) == 0) {
            void *field_addr = base + fields[j].offset;

            switch (fields[j].type) {
              case ProtoFieldType::TYPE_BOOL:
                *static_cast<bool *>(field_addr) = value.as_bool();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_INT32:
                *static_cast<int32_t *>(field_addr) = value.as_int32();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_UINT32:
                *static_cast<uint32_t *>(field_addr) = value.as_uint32();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_INT64:
                *static_cast<int64_t *>(field_addr) = value.as_int64();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_UINT64:
                *static_cast<uint64_t *>(field_addr) = value.as_uint64();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_SINT32:
                *static_cast<int32_t *>(field_addr) = value.as_sint32();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_SINT64:
                *static_cast<int64_t *>(field_addr) = value.as_sint64();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_ENUM:
                // For enums, we need to use the old metadata for now
                // This will be fixed in Phase 5
                *static_cast<uint32_t *>(field_addr) = value.as_uint32();
                decoded = true;
                break;
              default:
                break;
            }
            break;
          }
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].type) == 0) {
              void *field_addr = base + repeated_fields[j].offset;

              switch (repeated_fields[j].type) {
                case ProtoFieldType::TYPE_BOOL: {
                  auto *vec = static_cast<std::vector<bool> *>(field_addr);
                  vec->push_back(value.as_bool());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_INT32: {
                  auto *vec = static_cast<std::vector<int32_t> *>(field_addr);
                  vec->push_back(value.as_int32());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_UINT32: {
                  auto *vec = static_cast<std::vector<uint32_t> *>(field_addr);
                  vec->push_back(value.as_uint32());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_INT64: {
                  auto *vec = static_cast<std::vector<int64_t> *>(field_addr);
                  vec->push_back(value.as_int64());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_UINT64: {
                  auto *vec = static_cast<std::vector<uint64_t> *>(field_addr);
                  vec->push_back(value.as_uint64());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_SINT32: {
                  auto *vec = static_cast<std::vector<int32_t> *>(field_addr);
                  vec->push_back(value.as_sint32());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_SINT64: {
                  auto *vec = static_cast<std::vector<int64_t> *>(field_addr);
                  vec->push_back(value.as_sint64());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_ENUM: {
                  // For repeated enums, use old metadata for now
                  auto *vec = static_cast<std::vector<uint32_t> *>(field_addr);
                  vec->push_back(value.as_uint32());
                  decoded = true;
                  break;
                }
                default:
                  break;
              }
              break;
            }
          }
        }

        if (!decoded) {
          ESP_LOGV(TAG, "Cannot decode VarInt field %" PRIu32 " with value %" PRIu32 "!", field_id, res->as_uint32());
        }
        i += consumed;
        break;
      }
      case 2: {  // Length-delimited
        res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
        if (!res.has_value()) {
          ESP_LOGV(TAG, "Invalid Length Delimited at %" PRIu32, i);
          error = true;
          break;
        }
        uint32_t field_length = res->as_uint32();
        i += consumed;
        if (field_length > length - i) {
          ESP_LOGV(TAG, "Out-of-bounds Length Delimited at %" PRIu32, i);
          error = true;
          break;
        }
        ProtoLengthDelimited value(&buffer[i], field_length);
        bool decoded = false;

        // Check regular fields
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].type) == 2) {
            void *field_addr = base + fields[j].offset;

            switch (fields[j].type) {
              case ProtoFieldType::TYPE_STRING:
                *static_cast<std::string *>(field_addr) = value.as_string();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_BYTES: {
                // ProtoLengthDelimited has protected members, use buffer directly
                static_cast<std::string *>(field_addr)
                    ->assign(reinterpret_cast<const char *>(&buffer[i]), field_length);
                decoded = true;
                break;
              }
              case ProtoFieldType::TYPE_MESSAGE: {
                // Use function pointer from metadata
                if (fields[j].handler.message.decode) {
                  decoded = fields[j].handler.message.decode(field_addr, value);
                }
                break;
              }
              default:
                break;
            }
            break;
          }
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].type) == 2) {
              void *field_addr = base + repeated_fields[j].offset;

              switch (repeated_fields[j].type) {
                case ProtoFieldType::TYPE_STRING: {
                  auto *vec = static_cast<std::vector<std::string> *>(field_addr);
                  vec->push_back(value.as_string());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_BYTES: {
                  auto *vec = static_cast<std::vector<std::string> *>(field_addr);
                  vec->emplace_back(reinterpret_cast<const char *>(&buffer[i]), field_length);
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_MESSAGE: {
                  // Use function pointer from metadata
                  if (repeated_fields[j].handler.message.decode) {
                    decoded = repeated_fields[j].handler.message.decode(field_addr, value);
                  }
                  break;
                }
                default:
                  break;
              }
              break;
            }
          }
        }

        if (!decoded) {
          ESP_LOGV(TAG, "Cannot decode Length field %" PRIu32, field_id);
        }
        i += field_length;
        break;
      }
      case 5: {  // 32-bit
        if (length - i < 4) {
          ESP_LOGV(TAG, "Invalid 32-bit at %" PRIu32, i);
          error = true;
          break;
        }
        uint32_t raw = (buffer[i]) | (buffer[i + 1] << 8) | (buffer[i + 2] << 16) | (buffer[i + 3] << 24);
        Proto32Bit value(raw);
        bool decoded = false;

        // Check regular fields
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].type) == 5) {
            void *field_addr = base + fields[j].offset;

            switch (fields[j].type) {
              case ProtoFieldType::TYPE_FLOAT: {
                float *val = static_cast<float *>(field_addr);
                *val = value.as_float();
                decoded = true;
                break;
              }
              case ProtoFieldType::TYPE_FIXED32:
                *static_cast<uint32_t *>(field_addr) = value.as_fixed32();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_SFIXED32:
                *static_cast<int32_t *>(field_addr) = value.as_sfixed32();
                decoded = true;
                break;
              default:
                break;
            }
            break;
          }
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].type) == 5) {
              void *field_addr = base + repeated_fields[j].offset;

              switch (repeated_fields[j].type) {
                case ProtoFieldType::TYPE_FLOAT: {
                  auto *vec = static_cast<std::vector<float> *>(field_addr);
                  vec->push_back(value.as_float());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_FIXED32: {
                  auto *vec = static_cast<std::vector<uint32_t> *>(field_addr);
                  vec->push_back(value.as_fixed32());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_SFIXED32: {
                  auto *vec = static_cast<std::vector<int32_t> *>(field_addr);
                  vec->push_back(value.as_sfixed32());
                  decoded = true;
                  break;
                }
                default:
                  break;
              }
              break;
            }
          }
        }

        if (!decoded) {
          ESP_LOGV(TAG, "Cannot decode 32-bit field %" PRIu32, field_id);
        }
        i += 4;
        break;
      }
      case 1: {  // 64-bit
        if (length - i < 8) {
          ESP_LOGV(TAG, "Invalid 64-bit at %" PRIu32, i);
          error = true;
          break;
        }
        uint64_t raw = uint64_t(buffer[i]) | (uint64_t(buffer[i + 1]) << 8) | (uint64_t(buffer[i + 2]) << 16) |
                       (uint64_t(buffer[i + 3]) << 24) | (uint64_t(buffer[i + 4]) << 32) |
                       (uint64_t(buffer[i + 5]) << 40) | (uint64_t(buffer[i + 6]) << 48) |
                       (uint64_t(buffer[i + 7]) << 56);
        Proto64Bit value(raw);
        bool decoded = false;

        // Check regular fields
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].type) == 1) {
            void *field_addr = base + fields[j].offset;

            switch (fields[j].type) {
              case ProtoFieldType::TYPE_DOUBLE: {
                double *val = static_cast<double *>(field_addr);
                *val = value.as_double();
                decoded = true;
                break;
              }
              case ProtoFieldType::TYPE_FIXED64:
                *static_cast<uint64_t *>(field_addr) = value.as_fixed64();
                decoded = true;
                break;
              case ProtoFieldType::TYPE_SFIXED64:
                *static_cast<int64_t *>(field_addr) = value.as_sfixed64();
                decoded = true;
                break;
              default:
                break;
            }
            break;
          }
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].type) == 1) {
              void *field_addr = base + repeated_fields[j].offset;

              switch (repeated_fields[j].type) {
                case ProtoFieldType::TYPE_DOUBLE: {
                  auto *vec = static_cast<std::vector<double> *>(field_addr);
                  vec->push_back(value.as_double());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_FIXED64: {
                  auto *vec = static_cast<std::vector<uint64_t> *>(field_addr);
                  vec->push_back(value.as_fixed64());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_SFIXED64: {
                  auto *vec = static_cast<std::vector<int64_t> *>(field_addr);
                  vec->push_back(value.as_sfixed64());
                  decoded = true;
                  break;
                }
                default:
                  break;
              }
              break;
            }
          }
        }

        if (!decoded) {
          ESP_LOGV(TAG, "Cannot decode 64-bit field %" PRIu32, field_id);
        }
        i += 8;
        break;
      }
      default: {
        ESP_LOGV(TAG, "Invalid field type %" PRIu32 " at %" PRIu32, field_type, i);
        return;
      }
    }
    if (error) {
      break;
    }
  }
}

// Type-based encode implementation
void ProtoMessage::encode_v2(ProtoWriteBuffer buffer) const {
  const uint8_t *base = reinterpret_cast<const uint8_t *>(this);

  // Get V2 metadata once at the start
  const FieldMetaV2 *fields = get_field_metadata_v2();
  size_t field_count = get_field_count_v2();

  // Encode regular fields
  for (size_t i = 0; i < field_count; i++) {
    const void *field_addr = base + fields[i].offset;

    switch (fields[i].type) {
      case ProtoFieldType::TYPE_BOOL: {
        const bool *val = static_cast<const bool *>(field_addr);
        buffer.encode_bool(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_INT32: {
        const int32_t *val = static_cast<const int32_t *>(field_addr);
        buffer.encode_int32(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_UINT32: {
        const uint32_t *val = static_cast<const uint32_t *>(field_addr);
        buffer.encode_uint32(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_INT64: {
        const int64_t *val = static_cast<const int64_t *>(field_addr);
        buffer.encode_int64(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_UINT64: {
        const uint64_t *val = static_cast<const uint64_t *>(field_addr);
        buffer.encode_uint64(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SINT32: {
        const int32_t *val = static_cast<const int32_t *>(field_addr);
        buffer.encode_sint32(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SINT64: {
        const int64_t *val = static_cast<const int64_t *>(field_addr);
        buffer.encode_sint64(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_ENUM: {
        // For enums, treat as uint32 for now
        const uint32_t *val = static_cast<const uint32_t *>(field_addr);
        buffer.encode_uint32(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_STRING: {
        const std::string *val = static_cast<const std::string *>(field_addr);
        buffer.encode_string(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_BYTES: {
        const std::string *val = static_cast<const std::string *>(field_addr);
        buffer.encode_bytes(fields[i].field_num, reinterpret_cast<const uint8_t *>(val->data()), val->size(),
                            fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_FLOAT: {
        const float *val = static_cast<const float *>(field_addr);
        buffer.encode_float(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_FIXED32: {
        const uint32_t *val = static_cast<const uint32_t *>(field_addr);
        buffer.encode_fixed32(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SFIXED32: {
        const int32_t *val = static_cast<const int32_t *>(field_addr);
        buffer.encode_sfixed32(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_DOUBLE: {
        const double *val = static_cast<const double *>(field_addr);
        buffer.encode_double(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_FIXED64: {
        const uint64_t *val = static_cast<const uint64_t *>(field_addr);
        buffer.encode_fixed64(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SFIXED64: {
        const int64_t *val = static_cast<const int64_t *>(field_addr);
        buffer.encode_sfixed64(fields[i].field_num, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_MESSAGE: {
        // Use function pointer from metadata
        if (fields[i].handler.message.encode) {
          fields[i].handler.message.encode(buffer, field_addr, fields[i].field_num);
        }
        break;
      }
    }
  }

  // Encode repeated fields
  const RepeatedFieldMetaV2 *repeated_fields = get_repeated_field_metadata_v2();
  size_t repeated_count = get_repeated_field_count_v2();

  for (size_t i = 0; i < repeated_count; i++) {
    const void *field_addr = base + repeated_fields[i].offset;

    switch (repeated_fields[i].type) {
      case ProtoFieldType::TYPE_BOOL: {
        const auto *vec = static_cast<const std::vector<bool> *>(field_addr);
        for (bool val : *vec) {
          buffer.encode_bool(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_INT32: {
        const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_int32(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_UINT32: {
        const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_uint32(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_INT64: {
        const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_int64(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_UINT64: {
        const auto *vec = static_cast<const std::vector<uint64_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_uint64(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SINT32: {
        const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_sint32(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SINT64: {
        const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_sint64(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_ENUM: {
        // For repeated enums, treat as uint32 for now
        const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_uint32(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_STRING: {
        const auto *vec = static_cast<const std::vector<std::string> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_string(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_BYTES: {
        const auto *vec = static_cast<const std::vector<std::string> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_bytes(repeated_fields[i].field_num, reinterpret_cast<const uint8_t *>(val.data()), val.size(),
                              true);
        }
        break;
      }
      case ProtoFieldType::TYPE_FLOAT: {
        const auto *vec = static_cast<const std::vector<float> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_float(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_FIXED32: {
        const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_fixed32(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SFIXED32: {
        const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_sfixed32(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_DOUBLE: {
        const auto *vec = static_cast<const std::vector<double> *>(field_addr);
        for (const auto &val : *vec) {
          union {
            double value;
            uint64_t raw;
          } u{};
          u.value = val;
          buffer.encode_fixed64(repeated_fields[i].field_num, u.raw, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_FIXED64: {
        const auto *vec = static_cast<const std::vector<uint64_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_fixed64(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SFIXED64: {
        const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
        for (const auto &val : *vec) {
          buffer.encode_sfixed64(repeated_fields[i].field_num, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_MESSAGE: {
        // Use function pointer from metadata
        if (repeated_fields[i].handler.message.encode) {
          repeated_fields[i].handler.message.encode(buffer, field_addr, repeated_fields[i].field_num);
        }
        break;
      }
    }
  }
}

// Type-based size calculation implementation
void ProtoMessage::calculate_size_v2(uint32_t &total_size) const {
  const uint8_t *base = reinterpret_cast<const uint8_t *>(this);

  // Get V2 metadata once at the start
  const FieldMetaV2 *fields = get_field_metadata_v2();
  size_t field_count = get_field_count_v2();

  // Calculate size for regular fields
  for (size_t i = 0; i < field_count; i++) {
    const void *field_addr = base + fields[i].offset;

    switch (fields[i].type) {
      case ProtoFieldType::TYPE_BOOL: {
        const bool *val = static_cast<const bool *>(field_addr);
        ProtoSize::add_bool_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_INT32: {
        const int32_t *val = static_cast<const int32_t *>(field_addr);
        ProtoSize::add_int32_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_UINT32: {
        const uint32_t *val = static_cast<const uint32_t *>(field_addr);
        ProtoSize::add_uint32_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_INT64: {
        const int64_t *val = static_cast<const int64_t *>(field_addr);
        ProtoSize::add_int64_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_UINT64: {
        const uint64_t *val = static_cast<const uint64_t *>(field_addr);
        ProtoSize::add_uint64_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SINT32: {
        const int32_t *val = static_cast<const int32_t *>(field_addr);
        ProtoSize::add_sint32_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SINT64: {
        const int64_t *val = static_cast<const int64_t *>(field_addr);
        ProtoSize::add_sint64_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_ENUM: {
        // For enums, treat as uint32 for now
        const uint32_t *val = static_cast<const uint32_t *>(field_addr);
        ProtoSize::add_enum_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_STRING: {
        const std::string *val = static_cast<const std::string *>(field_addr);
        ProtoSize::add_string_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_BYTES: {
        const std::string *val = static_cast<const std::string *>(field_addr);
        ProtoSize::add_string_field(total_size, fields[i].precalced_field_id_size, *val, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_FLOAT: {
        const float *val = static_cast<const float *>(field_addr);
        ProtoSize::add_fixed_field<4>(total_size, fields[i].precalced_field_id_size,
                                      *val != 0.0f || fields[i].force_encode, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_FIXED32: {
        const uint32_t *val = static_cast<const uint32_t *>(field_addr);
        ProtoSize::add_fixed_field<4>(total_size, fields[i].precalced_field_id_size,
                                      *val != 0 || fields[i].force_encode, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SFIXED32: {
        const int32_t *val = static_cast<const int32_t *>(field_addr);
        ProtoSize::add_fixed_field<4>(total_size, fields[i].precalced_field_id_size,
                                      *val != 0 || fields[i].force_encode, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_DOUBLE: {
        const double *val = static_cast<const double *>(field_addr);
        ProtoSize::add_fixed_field<8>(total_size, fields[i].precalced_field_id_size,
                                      *val != 0.0 || fields[i].force_encode, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_FIXED64: {
        const uint64_t *val = static_cast<const uint64_t *>(field_addr);
        ProtoSize::add_fixed_field<8>(total_size, fields[i].precalced_field_id_size,
                                      *val != 0 || fields[i].force_encode, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_SFIXED64: {
        const int64_t *val = static_cast<const int64_t *>(field_addr);
        ProtoSize::add_fixed_field<8>(total_size, fields[i].precalced_field_id_size,
                                      *val != 0 || fields[i].force_encode, fields[i].force_encode);
        break;
      }
      case ProtoFieldType::TYPE_MESSAGE: {
        // Use function pointer from metadata
        if (fields[i].handler.message.size) {
          fields[i].handler.message.size(total_size, field_addr, fields[i].precalced_field_id_size,
                                         fields[i].force_encode);
        }
        break;
      }
    }
  }

  // Calculate size for repeated fields
  const RepeatedFieldMetaV2 *repeated_fields = get_repeated_field_metadata_v2();
  size_t repeated_count = get_repeated_field_count_v2();

  for (size_t i = 0; i < repeated_count; i++) {
    const void *field_addr = base + repeated_fields[i].offset;

    switch (repeated_fields[i].type) {
      case ProtoFieldType::TYPE_BOOL: {
        const auto *vec = static_cast<const std::vector<bool> *>(field_addr);
        for (bool val : *vec) {
          ProtoSize::add_bool_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_INT32: {
        const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_int32_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_UINT32: {
        const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_uint32_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_INT64: {
        const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_int64_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_UINT64: {
        const auto *vec = static_cast<const std::vector<uint64_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_uint64_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SINT32: {
        const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_sint32_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SINT64: {
        const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_sint64_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_ENUM: {
        // For repeated enums, treat as uint32 for now
        const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_enum_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_STRING: {
        const auto *vec = static_cast<const std::vector<std::string> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_string_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_BYTES: {
        const auto *vec = static_cast<const std::vector<std::string> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_string_field(total_size, repeated_fields[i].precalced_field_id_size, val, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_FLOAT: {
        const auto *vec = static_cast<const std::vector<float> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_fixed_field<4>(total_size, repeated_fields[i].precalced_field_id_size, true, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_FIXED32: {
        const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_fixed_field<4>(total_size, repeated_fields[i].precalced_field_id_size, true, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SFIXED32: {
        const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_fixed_field<4>(total_size, repeated_fields[i].precalced_field_id_size, true, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_DOUBLE: {
        const auto *vec = static_cast<const std::vector<double> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_fixed_field<8>(total_size, repeated_fields[i].precalced_field_id_size, true, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_FIXED64: {
        const auto *vec = static_cast<const std::vector<uint64_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_fixed_field<8>(total_size, repeated_fields[i].precalced_field_id_size, true, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_SFIXED64: {
        const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
        for (const auto &val : *vec) {
          ProtoSize::add_fixed_field<8>(total_size, repeated_fields[i].precalced_field_id_size, true, true);
        }
        break;
      }
      case ProtoFieldType::TYPE_MESSAGE: {
        // Use function pointer from metadata
        if (repeated_fields[i].handler.message.size) {
          repeated_fields[i].handler.message.size(total_size, field_addr, repeated_fields[i].precalced_field_id_size);
        }
        break;
      }
    }
  }
}

// Message type handler implementations moved to api_pb2.cpp (generated by Python script)

}  // namespace api
}  // namespace esphome
