#pragma once

#include "proto.h"
#include "api_pb2_size.h"

namespace esphome {
namespace api {

// Template enum field functions (must be in header for instantiation)
template<typename EnumType>
inline void encode_enum_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *val = static_cast<const EnumType *>(field_ptr);
  buffer.encode_enum<EnumType>(field_num, *val);
}

template<typename EnumType>
inline void size_enum_field(uint32_t &total_size, const void *field_ptr, uint8_t field_num, bool force) {
  const auto *val = static_cast<const EnumType *>(field_ptr);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(*val), force);
}

// Template repeated field functions (must be in header for instantiation)
template<typename EnumType>
inline void encode_repeated_enum_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<EnumType> *>(field_ptr);
  for (const auto &val : *vec) {
    buffer.encode_enum<EnumType>(field_num, val, true);
  }
}

template<typename MessageType>
inline void encode_repeated_message_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<MessageType> *>(field_ptr);
  for (const auto &msg : *vec) {
    buffer.encode_message<MessageType>(field_num, msg, true);
  }
}

// Template size functions for repeated fields (must be in header for instantiation)
template<typename EnumType>
inline void size_repeated_enum_field(uint32_t &total_size, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<EnumType> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(val), true);
  }
}

template<typename MessageType>
inline void size_repeated_message_field(uint32_t &total_size, const void *field_ptr, uint8_t field_num) {
  const auto *vec = static_cast<const std::vector<MessageType> *>(field_ptr);
  ProtoSize::add_repeated_message<MessageType>(total_size, 1, *vec);
}

}  // namespace api
}  // namespace esphome