#include "proto.h"
#include <cinttypes>
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "api_pb2_size.h"

namespace esphome {
namespace api {

static const char *const TAG = "api.proto";

// Message handler registries are defined in api_pb2.cpp

#ifdef HAS_PROTO_MESSAGE_DUMP
std::string ProtoMessage::dump() const {
  std::string out;
  this->dump_to(out);
  return out;
}
#endif

// ============================================================================
// Unified Field Operations - Single Implementation for Both Regular and Repeated
// ============================================================================

// Helper to get vector size for any repeated field type
static size_t get_vector_size(ProtoFieldType type, const void *field_addr) {
  switch (type) {
    case ProtoFieldType::TYPE_BOOL:
      return static_cast<const std::vector<bool> *>(field_addr)->size();
    case ProtoFieldType::TYPE_INT32:
    case ProtoFieldType::TYPE_SINT32:
    case ProtoFieldType::TYPE_SFIXED32:
      return static_cast<const std::vector<int32_t> *>(field_addr)->size();
    case ProtoFieldType::TYPE_UINT32:
    case ProtoFieldType::TYPE_ENUM:
    case ProtoFieldType::TYPE_FIXED32:
      return static_cast<const std::vector<uint32_t> *>(field_addr)->size();
    case ProtoFieldType::TYPE_INT64:
    case ProtoFieldType::TYPE_SINT64:
    case ProtoFieldType::TYPE_SFIXED64:
      return static_cast<const std::vector<int64_t> *>(field_addr)->size();
    case ProtoFieldType::TYPE_UINT64:
    case ProtoFieldType::TYPE_FIXED64:
      return static_cast<const std::vector<uint64_t> *>(field_addr)->size();
    case ProtoFieldType::TYPE_FLOAT:
      return static_cast<const std::vector<float> *>(field_addr)->size();
    case ProtoFieldType::TYPE_DOUBLE:
      return static_cast<const std::vector<double> *>(field_addr)->size();
    case ProtoFieldType::TYPE_STRING:
    case ProtoFieldType::TYPE_BYTES:
      return static_cast<const std::vector<std::string> *>(field_addr)->size();
    default:
      return 0;
  }
}

// Helper to get a pointer to the nth element in a vector (const version)
static const void *get_vector_element(ProtoFieldType type, const void *field_addr, size_t index) {
  switch (type) {
    case ProtoFieldType::TYPE_BOOL: {
      // std::vector<bool> is special - we need to handle it differently
      static bool temp_bool;
      temp_bool = (*static_cast<const std::vector<bool> *>(field_addr))[index];
      return &temp_bool;
    }
    case ProtoFieldType::TYPE_INT32:
    case ProtoFieldType::TYPE_SINT32:
    case ProtoFieldType::TYPE_SFIXED32:
      return &(*static_cast<const std::vector<int32_t> *>(field_addr))[index];
    case ProtoFieldType::TYPE_UINT32:
    case ProtoFieldType::TYPE_ENUM:
    case ProtoFieldType::TYPE_FIXED32:
      return &(*static_cast<const std::vector<uint32_t> *>(field_addr))[index];
    case ProtoFieldType::TYPE_INT64:
    case ProtoFieldType::TYPE_SINT64:
    case ProtoFieldType::TYPE_SFIXED64:
      return &(*static_cast<const std::vector<int64_t> *>(field_addr))[index];
    case ProtoFieldType::TYPE_UINT64:
    case ProtoFieldType::TYPE_FIXED64:
      return &(*static_cast<const std::vector<uint64_t> *>(field_addr))[index];
    case ProtoFieldType::TYPE_FLOAT:
      return &(*static_cast<const std::vector<float> *>(field_addr))[index];
    case ProtoFieldType::TYPE_DOUBLE:
      return &(*static_cast<const std::vector<double> *>(field_addr))[index];
    case ProtoFieldType::TYPE_STRING:
    case ProtoFieldType::TYPE_BYTES:
      return &(*static_cast<const std::vector<std::string> *>(field_addr))[index];
    default:
      return nullptr;
  }
}

// Unified encode function that works for both single fields and repeated fields
static void encode_field(ProtoWriteBuffer &buffer, ProtoFieldType type, uint8_t field_num, const void *field_addr,
                         bool force) {
  switch (type) {
    case ProtoFieldType::TYPE_BOOL:
      buffer.encode_bool(field_num, *static_cast<const bool *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_INT32:
      buffer.encode_int32(field_num, *static_cast<const int32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_UINT32:
    case ProtoFieldType::TYPE_ENUM:
      buffer.encode_uint32(field_num, *static_cast<const uint32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_INT64:
      buffer.encode_int64(field_num, *static_cast<const int64_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_UINT64:
      buffer.encode_uint64(field_num, *static_cast<const uint64_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_SINT32:
      buffer.encode_sint32(field_num, *static_cast<const int32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_SINT64:
      buffer.encode_sint64(field_num, *static_cast<const int64_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_STRING:
      buffer.encode_string(field_num, *static_cast<const std::string *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_BYTES: {
      const auto *str = static_cast<const std::string *>(field_addr);
      buffer.encode_bytes(field_num, reinterpret_cast<const uint8_t *>(str->data()), str->size(), force);
      break;
    }
    case ProtoFieldType::TYPE_FLOAT:
      buffer.encode_float(field_num, *static_cast<const float *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_FIXED32:
      buffer.encode_fixed32(field_num, *static_cast<const uint32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_SFIXED32:
      buffer.encode_sfixed32(field_num, *static_cast<const int32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_DOUBLE:
      buffer.encode_double(field_num, *static_cast<const double *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_FIXED64:
      buffer.encode_fixed64(field_num, *static_cast<const uint64_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_SFIXED64:
      buffer.encode_sfixed64(field_num, *static_cast<const int64_t *>(field_addr), force);
      break;
    default:
      break;
  }
}

// Unified size calculation
static void calculate_field_size(uint32_t &total_size, ProtoFieldType type, uint8_t precalc_size,
                                 const void *field_addr, bool force) {
  switch (type) {
    case ProtoFieldType::TYPE_BOOL:
      ProtoSize::add_bool_field(total_size, precalc_size, *static_cast<const bool *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_INT32:
      ProtoSize::add_int32_field(total_size, precalc_size, *static_cast<const int32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_UINT32:
      ProtoSize::add_uint32_field(total_size, precalc_size, *static_cast<const uint32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_INT64:
      ProtoSize::add_int64_field(total_size, precalc_size, *static_cast<const int64_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_UINT64:
      ProtoSize::add_uint64_field(total_size, precalc_size, *static_cast<const uint64_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_SINT32:
      ProtoSize::add_sint32_field(total_size, precalc_size, *static_cast<const int32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_SINT64:
      ProtoSize::add_sint64_field(total_size, precalc_size, *static_cast<const int64_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_ENUM:
      ProtoSize::add_enum_field(total_size, precalc_size, *static_cast<const uint32_t *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_STRING:
    case ProtoFieldType::TYPE_BYTES:
      ProtoSize::add_string_field(total_size, precalc_size, *static_cast<const std::string *>(field_addr), force);
      break;
    case ProtoFieldType::TYPE_FLOAT: {
      float val = *static_cast<const float *>(field_addr);
      ProtoSize::add_fixed_field<4>(total_size, precalc_size, val != 0.0f, force);
      break;
    }
    case ProtoFieldType::TYPE_FIXED32: {
      uint32_t val = *static_cast<const uint32_t *>(field_addr);
      ProtoSize::add_fixed_field<4>(total_size, precalc_size, val != 0, force);
      break;
    }
    case ProtoFieldType::TYPE_SFIXED32: {
      int32_t val = *static_cast<const int32_t *>(field_addr);
      ProtoSize::add_fixed_field<4>(total_size, precalc_size, val != 0, force);
      break;
    }
    case ProtoFieldType::TYPE_DOUBLE: {
      double val = *static_cast<const double *>(field_addr);
      ProtoSize::add_fixed_field<8>(total_size, precalc_size, val != 0.0, force);
      break;
    }
    case ProtoFieldType::TYPE_FIXED64: {
      uint64_t val = *static_cast<const uint64_t *>(field_addr);
      ProtoSize::add_fixed_field<8>(total_size, precalc_size, val != 0, force);
      break;
    }
    case ProtoFieldType::TYPE_SFIXED64: {
      int64_t val = *static_cast<const int64_t *>(field_addr);
      ProtoSize::add_fixed_field<8>(total_size, precalc_size, val != 0, force);
      break;
    }
    default:
      break;
  }
}

// Decode varint for single fields
static bool decode_varint_field(ProtoFieldType type, void *field_addr, const ProtoVarInt &value) {
  switch (type) {
    case ProtoFieldType::TYPE_BOOL:
      *static_cast<bool *>(field_addr) = value.as_bool();
      return true;
    case ProtoFieldType::TYPE_INT32:
      *static_cast<int32_t *>(field_addr) = value.as_int32();
      return true;
    case ProtoFieldType::TYPE_UINT32:
    case ProtoFieldType::TYPE_ENUM:
      *static_cast<uint32_t *>(field_addr) = value.as_uint32();
      return true;
    case ProtoFieldType::TYPE_INT64:
      *static_cast<int64_t *>(field_addr) = value.as_int64();
      return true;
    case ProtoFieldType::TYPE_UINT64:
      *static_cast<uint64_t *>(field_addr) = value.as_uint64();
      return true;
    case ProtoFieldType::TYPE_SINT32:
      *static_cast<int32_t *>(field_addr) = value.as_sint32();
      return true;
    case ProtoFieldType::TYPE_SINT64:
      *static_cast<int64_t *>(field_addr) = value.as_sint64();
      return true;
    default:
      return false;
  }
}

// Decode varint for repeated fields
static bool decode_repeated_varint_field(ProtoFieldType type, void *field_addr, const ProtoVarInt &value) {
  switch (type) {
    case ProtoFieldType::TYPE_BOOL:
      static_cast<std::vector<bool> *>(field_addr)->push_back(value.as_bool());
      return true;
    case ProtoFieldType::TYPE_INT32:
      static_cast<std::vector<int32_t> *>(field_addr)->push_back(value.as_int32());
      return true;
    case ProtoFieldType::TYPE_UINT32:
    case ProtoFieldType::TYPE_ENUM:
      static_cast<std::vector<uint32_t> *>(field_addr)->push_back(value.as_uint32());
      return true;
    case ProtoFieldType::TYPE_INT64:
      static_cast<std::vector<int64_t> *>(field_addr)->push_back(value.as_int64());
      return true;
    case ProtoFieldType::TYPE_UINT64:
      static_cast<std::vector<uint64_t> *>(field_addr)->push_back(value.as_uint64());
      return true;
    case ProtoFieldType::TYPE_SINT32:
      static_cast<std::vector<int32_t> *>(field_addr)->push_back(value.as_sint32());
      return true;
    case ProtoFieldType::TYPE_SINT64:
      static_cast<std::vector<int64_t> *>(field_addr)->push_back(value.as_sint64());
      return true;
    default:
      return false;
  }
}

// Decode 32-bit for single fields
static bool decode_32bit_field(ProtoFieldType type, void *field_addr, const Proto32Bit &value) {
  switch (type) {
    case ProtoFieldType::TYPE_FLOAT:
      *static_cast<float *>(field_addr) = value.as_float();
      return true;
    case ProtoFieldType::TYPE_FIXED32:
      *static_cast<uint32_t *>(field_addr) = value.as_fixed32();
      return true;
    case ProtoFieldType::TYPE_SFIXED32:
      *static_cast<int32_t *>(field_addr) = value.as_sfixed32();
      return true;
    default:
      return false;
  }
}

// Decode 32-bit for repeated fields
static bool decode_repeated_32bit_field(ProtoFieldType type, void *field_addr, const Proto32Bit &value) {
  switch (type) {
    case ProtoFieldType::TYPE_FLOAT:
      static_cast<std::vector<float> *>(field_addr)->push_back(value.as_float());
      return true;
    case ProtoFieldType::TYPE_FIXED32:
      static_cast<std::vector<uint32_t> *>(field_addr)->push_back(value.as_fixed32());
      return true;
    case ProtoFieldType::TYPE_SFIXED32:
      static_cast<std::vector<int32_t> *>(field_addr)->push_back(value.as_sfixed32());
      return true;
    default:
      return false;
  }
}

// Decode 64-bit for single fields
static bool decode_64bit_field(ProtoFieldType type, void *field_addr, const Proto64Bit &value) {
  switch (type) {
    case ProtoFieldType::TYPE_DOUBLE:
      *static_cast<double *>(field_addr) = value.as_double();
      return true;
    case ProtoFieldType::TYPE_FIXED64:
      *static_cast<uint64_t *>(field_addr) = value.as_fixed64();
      return true;
    case ProtoFieldType::TYPE_SFIXED64:
      *static_cast<int64_t *>(field_addr) = value.as_sfixed64();
      return true;
    default:
      return false;
  }
}

// Decode 64-bit for repeated fields
static bool decode_repeated_64bit_field(ProtoFieldType type, void *field_addr, const Proto64Bit &value) {
  switch (type) {
    case ProtoFieldType::TYPE_DOUBLE:
      static_cast<std::vector<double> *>(field_addr)->push_back(value.as_double());
      return true;
    case ProtoFieldType::TYPE_FIXED64:
      static_cast<std::vector<uint64_t> *>(field_addr)->push_back(value.as_fixed64());
      return true;
    case ProtoFieldType::TYPE_SFIXED64:
      static_cast<std::vector<int64_t> *>(field_addr)->push_back(value.as_sfixed64());
      return true;
    default:
      return false;
  }
}

// Decode length-delimited for single fields
static bool decode_length_field(ProtoFieldType type, void *field_addr, const ProtoLengthDelimited &value,
                                uint8_t message_type_id) {
  switch (type) {
    case ProtoFieldType::TYPE_STRING:
    case ProtoFieldType::TYPE_BYTES:
      *static_cast<std::string *>(field_addr) = value.as_string();
      return true;
    case ProtoFieldType::TYPE_MESSAGE:
      if (message_type_id < MESSAGE_HANDLER_COUNT && MESSAGE_HANDLERS[message_type_id].decode != nullptr) {
        return MESSAGE_HANDLERS[message_type_id].decode(field_addr, value);
      }
      return false;
    default:
      return false;
  }
}

// Decode length-delimited for repeated fields
static bool decode_repeated_length_field(ProtoFieldType type, void *field_addr, const ProtoLengthDelimited &value,
                                         uint8_t message_type_id) {
  switch (type) {
    case ProtoFieldType::TYPE_STRING:
    case ProtoFieldType::TYPE_BYTES:
      static_cast<std::vector<std::string> *>(field_addr)->push_back(value.as_string());
      return true;
    case ProtoFieldType::TYPE_MESSAGE:
      if (message_type_id < REPEATED_MESSAGE_HANDLER_COUNT &&
          REPEATED_MESSAGE_HANDLERS[message_type_id].decode != nullptr) {
        return REPEATED_MESSAGE_HANDLERS[message_type_id].decode(field_addr, value);
      }
      return false;
    default:
      return false;
  }
}

void ProtoMessage::decode(const uint8_t *buffer, size_t length) {
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  // Get metadata
  const FieldMeta *fields = get_field_metadata();
  size_t field_count = get_field_count();
  const RepeatedFieldMeta *repeated_fields = get_repeated_field_metadata();
  size_t repeated_count = get_repeated_field_count();

  // Handle empty message
  if (field_count == 0 && repeated_count == 0) {
    if (length > 0) {
      ESP_LOGW(TAG, "Received data for message with no fields");
    }
    return;
  }

  uint32_t i = 0;
  while (i < length) {
    // Parse field tag
    uint32_t consumed;
    auto tag_res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
    if (!tag_res.has_value()) {
      ESP_LOGV(TAG, "Invalid field tag at position %u", i);
      break;
    }

    uint32_t tag = tag_res->as_uint32();
    uint32_t field_id = tag >> 3;
    uint32_t wire_type = tag & 0x07;
    i += consumed;

    bool decoded = false;

    switch (wire_type) {
      case 0: {  // Varint
        auto value_res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
        if (!value_res.has_value()) {
          ESP_LOGV(TAG, "Invalid varint at position %u", i);
          return;
        }
        ProtoVarInt value = *value_res;

        // Try regular fields first
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 0) {
            void *field_addr = base + fields[j].get_offset();
            decoded = decode_varint_field(fields[j].get_type(), field_addr, value);
            break;
          }
        }

        // If not found, try repeated fields
        if (!decoded) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 0) {
              void *field_addr = base + repeated_fields[j].get_offset();
              decoded = decode_repeated_varint_field(repeated_fields[j].get_type(), field_addr, value);
              break;
            }
          }
        }

        i += consumed;
        break;
      }

      case 2: {  // Length-delimited
        auto len_res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
        if (!len_res.has_value()) {
          ESP_LOGV(TAG, "Invalid length at position %u", i);
          return;
        }
        uint32_t field_length = len_res->as_uint32();
        i += consumed;

        if (i + field_length > length) {
          ESP_LOGV(TAG, "Length-delimited field exceeds buffer at position %u", i);
          return;
        }

        ProtoLengthDelimited value(&buffer[i], field_length);

        // Try regular fields first
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 2) {
            void *field_addr = base + fields[j].get_offset();
            decoded = decode_length_field(fields[j].get_type(), field_addr, value, fields[j].get_message_type_id());
            break;
          }
        }

        // If not found, try repeated fields
        if (!decoded) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 2) {
              void *field_addr = base + repeated_fields[j].get_offset();
              decoded = decode_repeated_length_field(repeated_fields[j].get_type(), field_addr, value,
                                                     repeated_fields[j].get_message_type_id());
              break;
            }
          }
        }

        i += field_length;
        break;
      }

      case 5: {  // 32-bit
        if (i + 4 > length) {
          ESP_LOGV(TAG, "32-bit field exceeds buffer at position %u", i);
          return;
        }

        uint32_t raw = 0;
        raw |= uint32_t(buffer[i]) << 0;
        raw |= uint32_t(buffer[i + 1]) << 8;
        raw |= uint32_t(buffer[i + 2]) << 16;
        raw |= uint32_t(buffer[i + 3]) << 24;
        Proto32Bit value(raw);

        // Try regular fields first
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 5) {
            void *field_addr = base + fields[j].get_offset();
            decoded = decode_32bit_field(fields[j].get_type(), field_addr, value);
            break;
          }
        }

        // If not found, try repeated fields
        if (!decoded) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 5) {
              void *field_addr = base + repeated_fields[j].get_offset();
              decoded = decode_repeated_32bit_field(repeated_fields[j].get_type(), field_addr, value);
              break;
            }
          }
        }

        i += 4;
        break;
      }

      case 1: {  // 64-bit
        if (i + 8 > length) {
          ESP_LOGV(TAG, "64-bit field exceeds buffer at position %u", i);
          return;
        }

        uint64_t raw = 0;
        raw |= uint64_t(buffer[i]) << 0;
        raw |= uint64_t(buffer[i + 1]) << 8;
        raw |= uint64_t(buffer[i + 2]) << 16;
        raw |= uint64_t(buffer[i + 3]) << 24;
        raw |= uint64_t(buffer[i + 4]) << 32;
        raw |= uint64_t(buffer[i + 5]) << 40;
        raw |= uint64_t(buffer[i + 6]) << 48;
        raw |= uint64_t(buffer[i + 7]) << 56;
        Proto64Bit value(raw);

        // Try regular fields first
        for (size_t j = 0; j < field_count; j++) {
          if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 1) {
            void *field_addr = base + fields[j].get_offset();
            decoded = decode_64bit_field(fields[j].get_type(), field_addr, value);
            break;
          }
        }

        // If not found, try repeated fields
        if (!decoded) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 1) {
              void *field_addr = base + repeated_fields[j].get_offset();
              decoded = decode_repeated_64bit_field(repeated_fields[j].get_type(), field_addr, value);
              break;
            }
          }
        }

        i += 8;
        break;
      }

      default:
        ESP_LOGV(TAG, "Unknown wire type %u at position %u", wire_type, i);
        return;
    }

    if (!decoded) {
      ESP_LOGV(TAG, "Skipping unknown field %u with wire type %u", field_id, wire_type);
    }
  }
}

void ProtoMessage::encode(ProtoWriteBuffer buffer) const {
  const uint8_t *base = reinterpret_cast<const uint8_t *>(this);

  // Encode regular fields
  const FieldMeta *fields = get_field_metadata();
  size_t field_count = get_field_count();

  for (size_t i = 0; i < field_count; i++) {
    const void *field_addr = base + fields[i].get_offset();

    if (fields[i].get_type() == ProtoFieldType::TYPE_MESSAGE) {
      uint8_t handler_id = fields[i].get_message_type_id();
      if (handler_id < MESSAGE_HANDLER_COUNT && MESSAGE_HANDLERS[handler_id].encode != nullptr) {
        MESSAGE_HANDLERS[handler_id].encode(buffer, field_addr, fields[i].field_num);
      }
    } else {
      encode_field(buffer, fields[i].get_type(), fields[i].field_num, field_addr, false);
    }
  }

  // Encode repeated fields - reuse the same encode_field function!
  const RepeatedFieldMeta *repeated_fields = get_repeated_field_metadata();
  size_t repeated_count = get_repeated_field_count();

  for (size_t i = 0; i < repeated_count; i++) {
    const void *field_addr = base + repeated_fields[i].get_offset();

    if (repeated_fields[i].get_type() == ProtoFieldType::TYPE_MESSAGE) {
      uint8_t handler_id = repeated_fields[i].get_message_type_id();
      if (handler_id < REPEATED_MESSAGE_HANDLER_COUNT && REPEATED_MESSAGE_HANDLERS[handler_id].encode != nullptr) {
        REPEATED_MESSAGE_HANDLERS[handler_id].encode(buffer, field_addr, repeated_fields[i].field_num);
      }
    } else {
      // Iterate through the vector and encode each element using the same function!
      size_t count = get_vector_size(repeated_fields[i].get_type(), field_addr);
      for (size_t j = 0; j < count; j++) {
        const void *element = get_vector_element(repeated_fields[i].get_type(), field_addr, j);
        if (element != nullptr) {
          encode_field(buffer, repeated_fields[i].get_type(), repeated_fields[i].field_num, element, true);
        }
      }
    }
  }
}

void ProtoMessage::calculate_size(uint32_t &total_size) const {
  const uint8_t *base = reinterpret_cast<const uint8_t *>(this);

  // Calculate size for regular fields
  const FieldMeta *fields = get_field_metadata();
  size_t field_count = get_field_count();

  for (size_t i = 0; i < field_count; i++) {
    const void *field_addr = base + fields[i].get_offset();

    if (fields[i].get_type() == ProtoFieldType::TYPE_MESSAGE) {
      uint8_t handler_id = fields[i].get_message_type_id();
      if (handler_id < MESSAGE_HANDLER_COUNT && MESSAGE_HANDLERS[handler_id].size != nullptr) {
        MESSAGE_HANDLERS[handler_id].size(total_size, field_addr, fields[i].get_precalced_size(), false);
      }
    } else {
      calculate_field_size(total_size, fields[i].get_type(), fields[i].get_precalced_size(), field_addr, false);
    }
  }

  // Calculate size for repeated fields - reuse the same calculate_field_size function!
  const RepeatedFieldMeta *repeated_fields = get_repeated_field_metadata();
  size_t repeated_count = get_repeated_field_count();

  for (size_t i = 0; i < repeated_count; i++) {
    const void *field_addr = base + repeated_fields[i].get_offset();

    if (repeated_fields[i].get_type() == ProtoFieldType::TYPE_MESSAGE) {
      uint8_t handler_id = repeated_fields[i].get_message_type_id();
      if (handler_id < REPEATED_MESSAGE_HANDLER_COUNT && REPEATED_MESSAGE_HANDLERS[handler_id].size != nullptr) {
        REPEATED_MESSAGE_HANDLERS[handler_id].size(total_size, field_addr, repeated_fields[i].get_precalced_size());
      }
    } else {
      // Special optimization for fixed-size types
      ProtoFieldType type = repeated_fields[i].get_type();
      size_t count = get_vector_size(type, field_addr);

      // For fixed-size types, we can calculate size more efficiently
      if (type == ProtoFieldType::TYPE_FIXED32 || type == ProtoFieldType::TYPE_SFIXED32 ||
          type == ProtoFieldType::TYPE_FLOAT) {
        if (count > 0) {
          total_size += count * (repeated_fields[i].get_precalced_size() + 4);
        }
      } else if (type == ProtoFieldType::TYPE_FIXED64 || type == ProtoFieldType::TYPE_SFIXED64 ||
                 type == ProtoFieldType::TYPE_DOUBLE) {
        if (count > 0) {
          total_size += count * (repeated_fields[i].get_precalced_size() + 8);
        }
      } else {
        // For variable-size types, calculate each element
        for (size_t j = 0; j < count; j++) {
          const void *element = get_vector_element(type, field_addr, j);
          if (element != nullptr) {
            calculate_field_size(total_size, type, repeated_fields[i].get_precalced_size(), element, true);
          }
        }
      }
    }
  }
}

}  // namespace api
}  // namespace esphome
