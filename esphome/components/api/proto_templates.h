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
inline void size_enum_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force) {
  const auto *val = static_cast<const EnumType *>(field_ptr);
  ProtoSize::add_enum_field(total_size, precalced_field_id_size, static_cast<uint32_t>(*val), force);
}

template<typename EnumType> inline bool decode_enum_field(void *field_ptr, ProtoVarInt value) {
  auto *val = static_cast<EnumType *>(field_ptr);
  *val = value.as_enum<EnumType>();
  return true;
}

// Template functions for message field handling (regular fields)
template<typename MessageType>
inline void encode_message_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num) {
  const MessageType *msg = static_cast<const MessageType *>(field_ptr);
  buffer.encode_message<MessageType>(field_num, *msg);
}

template<typename MessageType>
inline void size_message_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size,
                               bool force) {
  const MessageType *msg = static_cast<const MessageType *>(field_ptr);
  ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
}

template<typename MessageType> inline bool decode_message_field(void *field_ptr, ProtoLengthDelimited value) {
  MessageType *msg = static_cast<MessageType *>(field_ptr);
  *msg = value.as_message<MessageType>();
  return true;
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
inline void size_repeated_enum_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<EnumType> *>(field_ptr);
  for (const auto &val : *vec) {
    ProtoSize::add_enum_field(total_size, precalced_field_id_size, static_cast<uint32_t>(val), true);
  }
}

template<typename MessageType>
inline void size_repeated_message_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size) {
  const auto *vec = static_cast<const std::vector<MessageType> *>(field_ptr);
  ProtoSize::add_repeated_message<MessageType>(total_size, precalced_field_id_size, *vec);
}

// Template decode functions for repeated fields
template<typename EnumType> inline bool decode_repeated_enum_field(void *field_ptr, ProtoVarInt value) {
  auto *vec = static_cast<std::vector<EnumType> *>(field_ptr);
  vec->push_back(value.as_enum<EnumType>());
  return true;
}

template<typename MessageType> inline bool decode_repeated_message_field(void *field_ptr, ProtoLengthDelimited value) {
  auto *vec = static_cast<std::vector<MessageType> *>(field_ptr);
  vec->push_back(value.as_message<MessageType>());
  return true;
}

}  // namespace api
}  // namespace esphome