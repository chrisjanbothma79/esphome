#include "proto.h"
#include <cinttypes>
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "api_pb2_size.h"
#include "proto_templates.h"

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

// Type-specific encoding functions removed - V3 inlines encoding directly

// Type-specific size calculation functions removed - V3 inlines size calculation directly

// Type-specific decode functions removed - V3 inlines decoding directly

// Template functions are now in the header file for proper instantiation

// Repeated field encoding functions removed - V3 inlines encoding directly

// Template repeated field functions moved to header

// Repeated field size calculation functions removed - V3 inlines size calculation directly

// Template size functions moved to header

// Repeated field decode functions removed - V3 inlines decoding directly

// ProtoMessage implementations using metadata
void ProtoMessage::decode(const uint8_t *buffer, size_t length) {
  ESP_LOGD(TAG, "ProtoMessage::decode entered, buffer=%p, length=%zu", buffer, length);

  // Handle null buffer
  if (buffer == nullptr && length > 0) {
    ESP_LOGW(TAG, "decode called with nullptr buffer but length=%zu", length);
    return;
  }

  uint32_t i = 0;
  bool error = false;
  uint8_t *base = reinterpret_cast<uint8_t *>(this);

  // Get V3 metadata
  ESP_LOGD(TAG, "Getting V3 metadata...");
  const FieldMetaV3 *fields = get_field_metadata_v3();
  size_t field_count = get_field_count_v3();
  const RepeatedFieldMetaV3 *repeated_fields = get_repeated_field_metadata_v3();
  size_t repeated_count = get_repeated_field_count_v3();

  ESP_LOGD(TAG, "decode: field_count=%zu, repeated_count=%zu, length=%zu, fields=%p, repeated_fields=%p", field_count,
           repeated_count, length, fields, repeated_fields);

  // If message has no fields at all, just return (valid empty message)
  if (field_count == 0 && repeated_count == 0) {
    if (length > 0) {
      ESP_LOGW(TAG, "Received data for message with no fields");
    }
    ESP_LOGD(TAG, "Empty message handled, returning");
    return;
  }

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
        if (fields != nullptr) {
          for (size_t j = 0; j < field_count; j++) {
            if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 0) {
              void *field_addr = base + fields[j].get_offset();

              switch (fields[j].get_type()) {
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
                  *static_cast<uint32_t *>(field_addr) = value.as_uint32();
                  decoded = true;
                  break;
                default:
                  break;
              }
              break;
            }
          }
        }
        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 0) {
              void *field_addr = base + repeated_fields[j].get_offset();

              switch (repeated_fields[j].get_type()) {
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
          ESP_LOGV(TAG, "Skipping VarInt field %" PRIu32 " at %" PRIu32, field_id, i);
        }
        i += consumed;
        break;
      }

      case 2: {  // Length-delimited
        res = ProtoVarInt::parse(&buffer[i], length - i, &consumed);
        if (!res.has_value()) {
          ESP_LOGV(TAG, "Invalid length delimited size at %" PRIu32, i);
          error = true;
          break;
        }
        uint32_t field_length = res->as_uint32();
        i += consumed;

        if (i + field_length > length) {
          ESP_LOGV(TAG, "Length delimited field %" PRIu32 " exceeds buffer", field_id);
          error = true;
          break;
        }

        ProtoLengthDelimited value(&buffer[i], field_length);
        bool decoded = false;

        // Check regular fields
        if (fields != nullptr) {
          for (size_t j = 0; j < field_count; j++) {
            if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 2) {
              void *field_addr = base + fields[j].get_offset();

              switch (fields[j].get_type()) {
                case ProtoFieldType::TYPE_STRING: {
                  auto *str = static_cast<std::string *>(field_addr);
                  *str = value.as_string();
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_BYTES: {
                  auto *str = static_cast<std::string *>(field_addr);
                  *str = value.as_string();
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_MESSAGE: {
                  // Use message handler registry
                  uint8_t handler_id = fields[j].get_message_type_id();
                  ESP_LOGD(TAG, "TYPE_MESSAGE field %d, handler_id=%d, MESSAGE_HANDLER_COUNT=%zu", field_id, handler_id,
                           MESSAGE_HANDLER_COUNT);
                  if (handler_id < MESSAGE_HANDLER_COUNT && MESSAGE_HANDLERS[handler_id].decode != nullptr) {
                    decoded = MESSAGE_HANDLERS[handler_id].decode(field_addr, value);
                  } else {
                    ESP_LOGW(TAG, "No handler for message type %d", handler_id);
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

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 2) {
              void *field_addr = base + repeated_fields[j].get_offset();

              switch (repeated_fields[j].get_type()) {
                case ProtoFieldType::TYPE_STRING: {
                  auto *vec = static_cast<std::vector<std::string> *>(field_addr);
                  vec->push_back(value.as_string());
                  decoded = true;
                  break;
                }
                case ProtoFieldType::TYPE_MESSAGE: {
                  // Use repeated message handler registry
                  uint8_t handler_id = repeated_fields[j].get_message_type_id();
                  ESP_LOGD(TAG, "Repeated TYPE_MESSAGE field %d, handler_id=%d, REPEATED_MESSAGE_HANDLER_COUNT=%zu", 
                           field_id, handler_id, REPEATED_MESSAGE_HANDLER_COUNT);
                  if (handler_id < REPEATED_MESSAGE_HANDLER_COUNT && REPEATED_MESSAGE_HANDLERS[handler_id].decode != nullptr) {
                    decoded = REPEATED_MESSAGE_HANDLERS[handler_id].decode(field_addr, value);
                    ESP_LOGD(TAG, "Decoded repeated message field %d: %s", field_id, decoded ? "success" : "failed");
                  } else {
                    ESP_LOGW(TAG, "No handler for repeated message type %d", handler_id);
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
          ESP_LOGV(TAG, "Skipping length delimited field %" PRIu32 " at %" PRIu32, field_id, i);
        }
        i += field_length;
        break;
      }

      case 5: {  // 32-bit
        if (i + 4 > length) {
          ESP_LOGV(TAG, "32-bit field %" PRIu32 " exceeds buffer", field_id);
          error = true;
          break;
        }

        uint32_t raw = 0;
        raw |= uint32_t(buffer[i]) << 0;
        raw |= uint32_t(buffer[i + 1]) << 8;
        raw |= uint32_t(buffer[i + 2]) << 16;
        raw |= uint32_t(buffer[i + 3]) << 24;
        Proto32Bit value(raw);
        bool decoded = false;

        // Check regular fields
        if (fields != nullptr) {
          for (size_t j = 0; j < field_count; j++) {
            if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 5) {
              void *field_addr = base + fields[j].get_offset();

              switch (fields[j].get_type()) {
                case ProtoFieldType::TYPE_FLOAT:
                  *static_cast<float *>(field_addr) = value.as_float();
                  decoded = true;
                  break;
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
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 5) {
              void *field_addr = base + repeated_fields[j].get_offset();

              switch (repeated_fields[j].get_type()) {
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
          ESP_LOGV(TAG, "Skipping 32-bit field %" PRIu32 " at %" PRIu32, field_id, i);
        }
        i += 4;
        break;
      }

      case 1: {  // 64-bit
        if (i + 8 > length) {
          ESP_LOGV(TAG, "64-bit field %" PRIu32 " exceeds buffer", field_id);
          error = true;
          break;
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
        bool decoded = false;

        // Check regular fields
        if (fields != nullptr) {
          for (size_t j = 0; j < field_count; j++) {
            if (fields[j].field_num == field_id && get_wire_type(fields[j].get_type()) == 1) {
              void *field_addr = base + fields[j].get_offset();

              switch (fields[j].get_type()) {
                case ProtoFieldType::TYPE_DOUBLE:
                  *static_cast<double *>(field_addr) = value.as_double();
                  decoded = true;
                  break;
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
        }

        // Check repeated fields if not found
        if (!decoded && repeated_fields) {
          for (size_t j = 0; j < repeated_count; j++) {
            if (repeated_fields[j].field_num == field_id && get_wire_type(repeated_fields[j].get_type()) == 1) {
              void *field_addr = base + repeated_fields[j].get_offset();

              switch (repeated_fields[j].get_type()) {
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
          ESP_LOGV(TAG, "Skipping 64-bit field %" PRIu32 " at %" PRIu32, field_id, i);
        }
        i += 8;
        break;
      }

      default:
        ESP_LOGV(TAG, "Unknown field type %" PRIu32 " at %" PRIu32, field_type, i);
        return;
    }

    if (error) {
      break;
    }
  }
}

void ProtoMessage::encode(ProtoWriteBuffer buffer) const {
  const uint8_t *base = reinterpret_cast<const uint8_t *>(this);

  // Get V3 metadata
  const FieldMetaV3 *fields = get_field_metadata_v3();
  size_t field_count = get_field_count_v3();

  // Regular fields
  if (fields != nullptr) {
    for (size_t i = 0; i < field_count; i++) {
      const void *field_addr = base + fields[i].get_offset();

      switch (fields[i].get_type()) {
        case ProtoFieldType::TYPE_BOOL: {
          const auto *val = static_cast<const bool *>(field_addr);
          buffer.encode_bool(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_INT32: {
          const auto *val = static_cast<const int32_t *>(field_addr);
          buffer.encode_int32(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_UINT32: {
          const auto *val = static_cast<const uint32_t *>(field_addr);
          buffer.encode_uint32(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_INT64: {
          const auto *val = static_cast<const int64_t *>(field_addr);
          buffer.encode_int64(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_UINT64: {
          const auto *val = static_cast<const uint64_t *>(field_addr);
          buffer.encode_uint64(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_SINT32: {
          const auto *val = static_cast<const int32_t *>(field_addr);
          buffer.encode_sint32(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_SINT64: {
          const auto *val = static_cast<const int64_t *>(field_addr);
          buffer.encode_sint64(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_ENUM: {
          const auto *val = static_cast<const uint32_t *>(field_addr);
          buffer.encode_uint32(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_STRING: {
          const auto *val = static_cast<const std::string *>(field_addr);
          buffer.encode_string(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_BYTES: {
          const auto *str = static_cast<const std::string *>(field_addr);
          buffer.encode_bytes(fields[i].field_num, reinterpret_cast<const uint8_t *>(str->data()), str->size(), false);
          break;
        }
        case ProtoFieldType::TYPE_FLOAT: {
          const auto *val = static_cast<const float *>(field_addr);
          buffer.encode_float(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_FIXED32: {
          const auto *val = static_cast<const uint32_t *>(field_addr);
          buffer.encode_fixed32(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_SFIXED32: {
          const auto *val = static_cast<const int32_t *>(field_addr);
          buffer.encode_sfixed32(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_DOUBLE: {
          const auto *val = static_cast<const double *>(field_addr);
          buffer.encode_double(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_FIXED64: {
          const auto *val = static_cast<const uint64_t *>(field_addr);
          buffer.encode_fixed64(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_SFIXED64: {
          const auto *val = static_cast<const int64_t *>(field_addr);
          buffer.encode_sfixed64(fields[i].field_num, *val, false);
          break;
        }
        case ProtoFieldType::TYPE_MESSAGE: {
          // Use message handler registry
          if (fields[i].get_message_type_id() < MESSAGE_HANDLER_COUNT) {
            MESSAGE_HANDLERS[fields[i].get_message_type_id()].encode(buffer, field_addr, fields[i].field_num);
          }
          break;
        }
      }
    }
  }
  // Repeated fields
  const RepeatedFieldMetaV3 *repeated_fields = get_repeated_field_metadata_v3();
  size_t repeated_count = get_repeated_field_count_v3();

  if (repeated_fields != nullptr) {
    for (size_t i = 0; i < repeated_count; i++) {
      const void *field_addr = base + repeated_fields[i].get_offset();

      switch (repeated_fields[i].get_type()) {
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
            buffer.encode_double(repeated_fields[i].field_num, val, true);
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
          // Use repeated message handler registry
          if (repeated_fields[i].get_message_type_id() < REPEATED_MESSAGE_HANDLER_COUNT) {
            REPEATED_MESSAGE_HANDLERS[repeated_fields[i].get_message_type_id()].encode(buffer, field_addr,
                                                                                       repeated_fields[i].field_num);
          }
          break;
        }
      }
    }
  }
}

void ProtoMessage::calculate_size(uint32_t &total_size) const {
  const uint8_t *base = reinterpret_cast<const uint8_t *>(this);

  // Get V3 metadata
  const FieldMetaV3 *fields = get_field_metadata_v3();
  size_t field_count = get_field_count_v3();

  // Regular fields
  if (fields != nullptr) {
    for (size_t i = 0; i < field_count; i++) {
      const void *field_addr = base + fields[i].get_offset();

      switch (fields[i].get_type()) {
        case ProtoFieldType::TYPE_BOOL: {
          const auto *val = static_cast<const bool *>(field_addr);
          ProtoSize::add_bool_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_INT32: {
          const auto *val = static_cast<const int32_t *>(field_addr);
          ProtoSize::add_int32_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_UINT32: {
          const auto *val = static_cast<const uint32_t *>(field_addr);
          ProtoSize::add_uint32_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_INT64: {
          const auto *val = static_cast<const int64_t *>(field_addr);
          ProtoSize::add_int64_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_UINT64: {
          const auto *val = static_cast<const uint64_t *>(field_addr);
          ProtoSize::add_uint64_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_SINT32: {
          const auto *val = static_cast<const int32_t *>(field_addr);
          ProtoSize::add_sint32_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_SINT64: {
          const auto *val = static_cast<const int64_t *>(field_addr);
          ProtoSize::add_sint64_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_ENUM: {
          const auto *val = static_cast<const uint32_t *>(field_addr);
          ProtoSize::add_enum_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_STRING: {
          const auto *val = static_cast<const std::string *>(field_addr);
          ProtoSize::add_string_field(total_size, fields[i].get_precalced_size(), *val, false);
          break;
        }
        case ProtoFieldType::TYPE_BYTES: {
          const auto *str = static_cast<const std::string *>(field_addr);
          ProtoSize::add_string_field(total_size, fields[i].get_precalced_size(), *str, false);
          break;
        }
        case ProtoFieldType::TYPE_FLOAT: {
          const auto *val = static_cast<const float *>(field_addr);
          ProtoSize::add_fixed_field<4>(total_size, fields[i].get_precalced_size(), *val != 0.0f, false);
          break;
        }
        case ProtoFieldType::TYPE_FIXED32: {
          const auto *val = static_cast<const uint32_t *>(field_addr);
          ProtoSize::add_fixed_field<4>(total_size, fields[i].get_precalced_size(), *val != 0, false);
          break;
        }
        case ProtoFieldType::TYPE_SFIXED32: {
          const auto *val = static_cast<const int32_t *>(field_addr);
          ProtoSize::add_fixed_field<4>(total_size, fields[i].get_precalced_size(), *val != 0, false);
          break;
        }
        case ProtoFieldType::TYPE_DOUBLE: {
          const auto *val = static_cast<const double *>(field_addr);
          ProtoSize::add_fixed_field<8>(total_size, fields[i].get_precalced_size(), *val != 0.0, false);
          break;
        }
        case ProtoFieldType::TYPE_FIXED64: {
          const auto *val = static_cast<const uint64_t *>(field_addr);
          ProtoSize::add_fixed_field<8>(total_size, fields[i].get_precalced_size(), *val != 0, false);
          break;
        }
        case ProtoFieldType::TYPE_SFIXED64: {
          const auto *val = static_cast<const int64_t *>(field_addr);
          ProtoSize::add_fixed_field<8>(total_size, fields[i].get_precalced_size(), *val != 0, false);
          break;
        }
        case ProtoFieldType::TYPE_MESSAGE: {
          // Use message handler registry
          if (fields[i].get_message_type_id() < MESSAGE_HANDLER_COUNT) {
            MESSAGE_HANDLERS[fields[i].get_message_type_id()].size(total_size, field_addr,
                                                                   fields[i].get_precalced_size(), false);
          }
          break;
        }
      }
    }
  }
  // Repeated fields
  const RepeatedFieldMetaV3 *repeated_fields = get_repeated_field_metadata_v3();
  size_t repeated_count = get_repeated_field_count_v3();

  for (size_t i = 0; i < repeated_count; i++) {
    if (repeated_fields != nullptr) {
      const void *field_addr = base + repeated_fields[i].get_offset();

      switch (repeated_fields[i].get_type()) {
        case ProtoFieldType::TYPE_BOOL: {
          const auto *vec = static_cast<const std::vector<bool> *>(field_addr);
          for (bool val : *vec) {
            ProtoSize::add_bool_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_INT32: {
          const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_int32_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_UINT32: {
          const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_uint32_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_INT64: {
          const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_int64_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_UINT64: {
          const auto *vec = static_cast<const std::vector<uint64_t> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_uint64_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_SINT32: {
          const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_sint32_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_SINT64: {
          const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_sint64_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_ENUM: {
          const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_enum_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_STRING: {
          const auto *vec = static_cast<const std::vector<std::string> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_string_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_BYTES: {
          const auto *vec = static_cast<const std::vector<std::string> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_string_field(total_size, repeated_fields[i].get_precalced_size(), val, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_FLOAT: {
          const auto *vec = static_cast<const std::vector<float> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_fixed_field<4>(total_size, repeated_fields[i].get_precalced_size(), val != 0.0f, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_FIXED32: {
          const auto *vec = static_cast<const std::vector<uint32_t> *>(field_addr);
          size_t count = vec->size();
          if (count > 0) {
            total_size += count * (repeated_fields[i].get_precalced_size() + 4);
          }
          break;
        }
        case ProtoFieldType::TYPE_SFIXED32: {
          const auto *vec = static_cast<const std::vector<int32_t> *>(field_addr);
          size_t count = vec->size();
          if (count > 0) {
            total_size += count * (repeated_fields[i].get_precalced_size() + 4);
          }
          break;
        }
        case ProtoFieldType::TYPE_DOUBLE: {
          const auto *vec = static_cast<const std::vector<double> *>(field_addr);
          for (const auto &val : *vec) {
            ProtoSize::add_fixed_field<8>(total_size, repeated_fields[i].get_precalced_size(), val != 0.0, true);
          }
          break;
        }
        case ProtoFieldType::TYPE_FIXED64: {
          const auto *vec = static_cast<const std::vector<uint64_t> *>(field_addr);
          size_t count = vec->size();
          if (count > 0) {
            total_size += count * (repeated_fields[i].get_precalced_size() + 8);
          }
          break;
        }
        case ProtoFieldType::TYPE_SFIXED64: {
          const auto *vec = static_cast<const std::vector<int64_t> *>(field_addr);
          size_t count = vec->size();
          if (count > 0) {
            total_size += count * (repeated_fields[i].get_precalced_size() + 8);
          }
          break;
        }
        case ProtoFieldType::TYPE_MESSAGE: {
          // Use repeated message handler registry
          if (repeated_fields[i].get_message_type_id() < REPEATED_MESSAGE_HANDLER_COUNT) {
            REPEATED_MESSAGE_HANDLERS[repeated_fields[i].get_message_type_id()].size(
                total_size, field_addr, repeated_fields[i].get_precalced_size());
          }
          break;
        }
      }
    }
  }
}

// Message type handler implementations moved to api_pb2.cpp (generated by Python script)

}  // namespace api
}  // namespace esphome
