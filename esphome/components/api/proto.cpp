#include "proto.h"
#include <cinttypes>
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "api_pb2_size.h"

namespace esphome {
namespace api {

static const char *const TAG = "api.proto";

void ProtoMessage::decode(const uint8_t *buffer, size_t length) {
  uint32_t i = 0;
  bool error = false;
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
        if (!this->decode_varint(field_id, *res)) {
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
        if (!this->decode_length(field_id, ProtoLengthDelimited(&buffer[i], field_length))) {
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
        if (!this->decode_32bit(field_id, Proto32Bit(val))) {
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

// Base class implementations using virtual metadata getters
void ProtoMetadataMessage::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, get_field_metadata(), get_field_count(), get_repeated_field_metadata(),
                       get_repeated_field_count());
}

void ProtoMetadataMessage::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, get_field_metadata(), get_field_count(), get_repeated_field_metadata(),
                               get_repeated_field_count());
}

bool ProtoMetadataMessage::decode_varint(uint32_t field_id, ProtoVarInt value) {
  const FieldMeta *fields = get_field_metadata();
  if (!fields)
    return false;
  return decode_varint_metadata(field_id, value, fields, get_field_count());
}

bool ProtoMetadataMessage::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  const FieldMeta *fields = get_field_metadata();
  if (!fields)
    return false;
  return decode_length_metadata(field_id, value, fields, get_field_count());
}

bool ProtoMetadataMessage::decode_32bit(uint32_t field_id, Proto32Bit value) {
  const FieldMeta *fields = get_field_metadata();
  if (!fields)
    return false;
  return decode_32bit_metadata(field_id, value, fields, get_field_count());
}

bool ProtoMetadataMessage::decode_64bit(uint32_t field_id, Proto64Bit value) {
  const FieldMeta *fields = get_field_metadata();
  if (!fields)
    return false;
  return decode_64bit_metadata(field_id, value, fields, get_field_count());
}

// Metadata-driven decode implementations
bool ProtoMetadataMessage::decode_varint_metadata(uint32_t field_id, ProtoVarInt value, const FieldMeta *fields,
                                                  size_t field_count) {
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  for (size_t i = 0; i < field_count; i++) {
    if (fields[i].field_num == field_id && fields[i].wire_type == 0) {  // varint
      void *field_addr = base + fields[i].offset;
      return fields[i].decoder.decode_varint(field_addr, value);
    }
  }
  return false;
}

bool ProtoMetadataMessage::decode_length_metadata(uint32_t field_id, ProtoLengthDelimited value,
                                                  const FieldMeta *fields, size_t field_count) {
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  for (size_t i = 0; i < field_count; i++) {
    if (fields[i].field_num == field_id && fields[i].wire_type == 2) {  // length-delimited
      void *field_addr = base + fields[i].offset;
      return fields[i].decoder.decode_length(field_addr, value);
    }
  }
  return false;
}

bool ProtoMetadataMessage::decode_32bit_metadata(uint32_t field_id, Proto32Bit value, const FieldMeta *fields,
                                                 size_t field_count) {
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  for (size_t i = 0; i < field_count; i++) {
    if (fields[i].field_num == field_id && fields[i].wire_type == 5) {  // 32-bit
      void *field_addr = base + fields[i].offset;
      return fields[i].decoder.decode_32bit(field_addr, value);
    }
  }
  return false;
}

bool ProtoMetadataMessage::decode_64bit_metadata(uint32_t field_id, Proto64Bit value, const FieldMeta *fields,
                                                 size_t field_count) {
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  for (size_t i = 0; i < field_count; i++) {
    if (fields[i].field_num == field_id && fields[i].wire_type == 1) {  // 64-bit
      void *field_addr = base + fields[i].offset;
      return fields[i].decoder.decode_64bit(field_addr, value);
    }
  }
  return false;
}

}  // namespace api
}  // namespace esphome
