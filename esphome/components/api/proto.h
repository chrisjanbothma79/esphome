#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

#include <vector>

#ifdef ESPHOME_LOG_HAS_VERY_VERBOSE
#define HAS_PROTO_MESSAGE_DUMP
#endif

namespace esphome {
namespace api {

// Forward declarations
class ProtoWriteBuffer;

// Enum for all supported field types
enum class ProtoFieldType : uint8_t {
  // Varint types (wire type 0)
  TYPE_BOOL = 0,
  TYPE_INT32 = 1,
  TYPE_UINT32 = 2,
  TYPE_INT64 = 3,
  TYPE_UINT64 = 4,
  TYPE_SINT32 = 5,
  TYPE_SINT64 = 6,
  TYPE_ENUM = 7,

  // Length-delimited types (wire type 2)
  TYPE_STRING = 8,
  TYPE_BYTES = 9,
  TYPE_MESSAGE = 10,

  // 32-bit types (wire type 5)
  TYPE_FLOAT = 11,
  TYPE_FIXED32 = 12,
  TYPE_SFIXED32 = 13,
};

// Helper to get wire type from field type
inline constexpr uint8_t get_wire_type(ProtoFieldType type) {
  switch (type) {
    case ProtoFieldType::TYPE_BOOL:
    case ProtoFieldType::TYPE_INT32:
    case ProtoFieldType::TYPE_UINT32:
    case ProtoFieldType::TYPE_INT64:
    case ProtoFieldType::TYPE_UINT64:
    case ProtoFieldType::TYPE_SINT32:
    case ProtoFieldType::TYPE_SINT64:
    case ProtoFieldType::TYPE_ENUM:
      return 0;  // varint

    case ProtoFieldType::TYPE_STRING:
    case ProtoFieldType::TYPE_BYTES:
    case ProtoFieldType::TYPE_MESSAGE:
      return 2;  // length-delimited

    case ProtoFieldType::TYPE_FLOAT:
    case ProtoFieldType::TYPE_FIXED32:
    case ProtoFieldType::TYPE_SFIXED32:
      return 5;  // 32-bit
  }
  return 0;
}

// Macro to calculate field offset without triggering -Winvalid-offsetof
// This uses the same approach as offsetof but with explicit reinterpret_cast
#define PROTO_FIELD_OFFSET(Type, Member) \
  static_cast<uint16_t>(reinterpret_cast<size_t>(&reinterpret_cast<Type *>(16)->Member) - \
                        16) /* NOLINT(bugprone-macro-parentheses) */

/// Representation of a VarInt - in ProtoBuf should be 64bit but we only use 32bit
class ProtoVarInt {
 public:
  ProtoVarInt() : value_(0) {}
  explicit ProtoVarInt(uint64_t value) : value_(value) {}

  static optional<ProtoVarInt> parse(const uint8_t *buffer, uint32_t len, uint32_t *consumed) {
    if (len == 0) {
      if (consumed != nullptr)
        *consumed = 0;
      return {};
    }

    // Most common case: single-byte varint (values 0-127)
    if ((buffer[0] & 0x80) == 0) {
      if (consumed != nullptr)
        *consumed = 1;
      return ProtoVarInt(buffer[0]);
    }

    // General case for multi-byte varints
    // Since we know buffer[0]'s high bit is set, initialize with its value
    uint64_t result = buffer[0] & 0x7F;
    uint8_t bitpos = 7;

    // Start from the second byte since we've already processed the first
    for (uint32_t i = 1; i < len; i++) {
      uint8_t val = buffer[i];
      result |= uint64_t(val & 0x7F) << uint64_t(bitpos);
      bitpos += 7;
      if ((val & 0x80) == 0) {
        if (consumed != nullptr)
          *consumed = i + 1;
        return ProtoVarInt(result);
      }
    }

    if (consumed != nullptr)
      *consumed = 0;
    return {};  // Incomplete or invalid varint
  }

  inline uint16_t as_uint16() const { return this->value_; }
  inline uint32_t as_uint32() const { return this->value_; }
  inline uint64_t as_uint64() const { return this->value_; }
  inline bool as_bool() const { return this->value_; }
  template<typename T> inline T as_enum() const { return static_cast<T>(this->as_uint32()); }
  inline int32_t as_int32() const {
    // Not ZigZag encoded
    return static_cast<int32_t>(this->as_int64());
  }
  inline int64_t as_int64() const {
    // Not ZigZag encoded
    return static_cast<int64_t>(this->value_);
  }
  inline int32_t as_sint32() const {
    // with ZigZag encoding
    if (this->value_ & 1) {
      return static_cast<int32_t>(~(this->value_ >> 1));
    } else {
      return static_cast<int32_t>(this->value_ >> 1);
    }
  }
  inline int64_t as_sint64() const {
    // with ZigZag encoding
    if (this->value_ & 1) {
      return static_cast<int64_t>(~(this->value_ >> 1));
    } else {
      return static_cast<int64_t>(this->value_ >> 1);
    }
  }
  /**
   * Encode the varint value to a pre-allocated buffer without bounds checking.
   *
   * @param buffer The pre-allocated buffer to write the encoded varint to
   * @param len The size of the buffer in bytes
   *
   * @note The caller is responsible for ensuring the buffer is large enough
   *       to hold the encoded value. Use ProtoSize::varint() to calculate
   *       the exact size needed before calling this method.
   * @note No bounds checking is performed for performance reasons.
   */
  void encode_to_buffer_unchecked(uint8_t *buffer, size_t len) {
    uint64_t val = this->value_;
    if (val <= 0x7F) {
      buffer[0] = val;
      return;
    }
    size_t i = 0;
    while (val && i < len) {
      uint8_t temp = val & 0x7F;
      val >>= 7;
      if (val) {
        buffer[i++] = temp | 0x80;
      } else {
        buffer[i++] = temp;
      }
    }
  }
  void encode(std::vector<uint8_t> &out) {
    uint64_t val = this->value_;
    if (val <= 0x7F) {
      out.push_back(val);
      return;
    }
    while (val) {
      uint8_t temp = val & 0x7F;
      val >>= 7;
      if (val) {
        out.push_back(temp | 0x80);
      } else {
        out.push_back(temp);
      }
    }
  }

 protected:
  uint64_t value_;
};

class ProtoLengthDelimited {
 public:
  explicit ProtoLengthDelimited(const uint8_t *value, size_t length) : value_(value), length_(length) {}
  inline std::string as_string() const {
    return std::string(reinterpret_cast<const char *>(this->value_), this->length_);
  }
  template<class C> inline C as_message() const {
    auto msg = C();
    msg.decode(this->value_, this->length_);
    return msg;
  }

 protected:
  const uint8_t *const value_;
  const size_t length_;
};

class Proto32Bit {
 public:
  explicit Proto32Bit(uint32_t value) : value_(value) {}
  inline uint32_t as_fixed32() const { return this->value_; }
  inline int32_t as_sfixed32() const { return static_cast<int32_t>(this->value_); }
  inline float as_float() const {
    union {
      uint32_t raw;
      float value;
    } s{};
    s.raw = this->value_;
    return s.value;
  }

 protected:
  const uint32_t value_;
};

// Function pointer types used by V2 structures
using EncodeFunc = void (*)(ProtoWriteBuffer &, const void *field_ptr, uint8_t field_num);
using SizeFunc = void (*)(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force);
using DecodeLengthFunc = bool (*)(void *field_ptr, ProtoLengthDelimited value);

// Function pointer types for repeated fields used by V2 structures
using RepeatedEncodeFunc = void (*)(ProtoWriteBuffer &, const void *field_ptr, uint8_t field_num);
using RepeatedSizeFunc = void (*)(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size);
using RepeatedDecodeLengthFunc = bool (*)(void *field_ptr, ProtoLengthDelimited value);

// Message handler registry entry
struct MessageHandler {
  EncodeFunc encode;
  SizeFunc size;
  DecodeLengthFunc decode;
};

// Repeated message handler registry entry
struct RepeatedMessageHandler {
  RepeatedEncodeFunc encode;
  RepeatedSizeFunc size;
  RepeatedDecodeLengthFunc decode;
};

// Global message handler registries (defined in api_pb2.cpp)
extern const MessageHandler MESSAGE_HANDLERS[];
extern const uint8_t MESSAGE_HANDLER_COUNT;
extern const RepeatedMessageHandler REPEATED_MESSAGE_HANDLERS[];
extern const uint8_t REPEATED_MESSAGE_HANDLER_COUNT;

// Optimized metadata structure (4 bytes - no padding on 32-bit architectures)
struct FieldMeta {
  uint8_t field_num;      // Protobuf field number (1-255)
  uint8_t type_and_size;  // bits 0-4: ProtoFieldType, bits 5-6: precalced_field_id_size-1, bit 7: wire_type_high_bit
  union {
    uint16_t offset;  // For non-message types: offset in class (0-65535)
    struct {
      uint8_t offset_low;       // For TYPE_MESSAGE: low byte of offset (bits 0-7)
      uint8_t message_type_id;  // For TYPE_MESSAGE: bits 0-1: offset high (bits 8-9), bits 2-7: handler index (0-63)
    };
  };

  // Helper methods
  inline ProtoFieldType get_type() const { return static_cast<ProtoFieldType>(type_and_size & 0x1F); }
  inline uint8_t get_precalced_size() const { return ((type_and_size >> 5) & 0x03) + 1; }
  inline uint8_t get_wire_type() const {
    // Wire type is encoded as: 0=varint, 2=length-delimited, 5=32-bit
    // We only need 1 bit to distinguish between 0/2 and 5 (32-bit)
    // If bit 7 is set, it's wire type 5, otherwise check the field type
    if (type_and_size & 0x80) {
      return 5;  // 32-bit types
    }
    ProtoFieldType t = get_type();
    return (t >= ProtoFieldType::TYPE_STRING) ? 2 : 0;  // length-delimited : varint
  }
  inline uint16_t get_offset() const {
    if (get_type() == ProtoFieldType::TYPE_MESSAGE) {
      // Reconstruct full offset from packed fields (10-bit offset)
      // Bits 0-7 from offset_low, bits 8-9 from lower 2 bits of message_type_id
      return static_cast<uint16_t>(offset_low) | (static_cast<uint16_t>(message_type_id & 0x03) << 8);
    }
    return offset;
  }
  inline uint8_t get_message_type_id() const { return message_type_id >> 2; }  // Upper 6 bits for type ID (0-63)
};

// Optimized repeated field metadata (4 bytes - no padding on 32-bit architectures)
struct RepeatedFieldMeta {
  uint8_t field_num;      // Protobuf field number (1-255)
  uint8_t type_and_size;  // bits 0-4: ProtoFieldType, bits 5-6: precalced_field_id_size-1, bit 7: wire_type_high_bit
  union {
    uint16_t offset;  // For non-message types: offset in class (0-65535)
    struct {
      uint8_t offset_low;       // For TYPE_MESSAGE: low byte of offset (bits 0-7)
      uint8_t message_type_id;  // For TYPE_MESSAGE: bits 0-1: offset high (bits 8-9), bits 2-7: handler index (0-63)
    };
  };

  // Helper methods
  inline ProtoFieldType get_type() const { return static_cast<ProtoFieldType>(type_and_size & 0x1F); }
  inline uint8_t get_precalced_size() const { return ((type_and_size >> 5) & 0x03) + 1; }
  inline uint8_t get_wire_type() const {
    // Wire type is encoded as: 0=varint, 2=length-delimited, 5=32-bit
    // We only need 1 bit to distinguish between 0/2 and 5 (32-bit)
    // If bit 7 is set, it's wire type 5, otherwise check the field type
    if (type_and_size & 0x80) {
      return 5;  // 32-bit types
    }
    ProtoFieldType t = get_type();
    return (t >= ProtoFieldType::TYPE_STRING) ? 2 : 0;  // length-delimited : varint
  }
  inline uint16_t get_offset() const {
    if (get_type() == ProtoFieldType::TYPE_MESSAGE) {
      // Reconstruct full offset from packed fields (10-bit offset)
      // Bits 0-7 from offset_low, bits 8-9 from lower 2 bits of message_type_id
      return static_cast<uint16_t>(offset_low) | (static_cast<uint16_t>(message_type_id & 0x03) << 8);
    }
    return offset;
  }
  inline uint8_t get_message_type_id() const { return message_type_id >> 2; }  // Upper 6 bits for type ID (0-63)
};

// Binary search for field lookup - optimized for performance
inline const FieldMeta *find_field_binary(const FieldMeta *fields, uint8_t count, uint8_t field_id, uint8_t wire_type) {
  uint8_t left = 0;
  uint8_t right = count;

  while (left < right) {
    uint8_t mid = (left + right) / 2;
    uint8_t mid_field = fields[mid].field_num;

    if (mid_field < field_id) {
      left = mid + 1;
    } else if (mid_field > field_id) {
      right = mid;
    } else {
      // Found field_id, check wire type
      if (fields[mid].get_wire_type() == wire_type) {
        return &fields[mid];
      }
      // Field number matches but wire type doesn't - search nearby entries
      // (in case there are multiple fields with same number but different types)

      // Search backwards
      for (uint8_t k = mid; k > 0 && fields[k - 1].field_num == field_id; k--) {
        if (fields[k - 1].get_wire_type() == wire_type) {
          return &fields[k - 1];
        }
      }

      // Search forwards
      for (uint8_t k = mid + 1; k < count && fields[k].field_num == field_id; k++) {
        if (fields[k].get_wire_type() == wire_type) {
          return &fields[k];
        }
      }

      return nullptr;  // Field number found but no matching wire type
    }
  }

  return nullptr;  // Field not found
}

class ProtoWriteBuffer {
 public:
  ProtoWriteBuffer(std::vector<uint8_t> *buffer) : buffer_(buffer) {}
  inline void write(uint8_t value) { this->buffer_->push_back(value); }
  inline void encode_varint_raw(ProtoVarInt value) { value.encode(*this->buffer_); }
  inline void encode_varint_raw(uint32_t value) { this->encode_varint_raw(ProtoVarInt(value)); }
  /**
   * Encode a field key (tag/wire type combination).
   *
   * @param field_id Field number (tag) in the protobuf message
   * @param type Wire type value:
   *   - 0: Varint (int32, int64, uint32, uint64, sint32, sint64, bool, enum)
   *   - 1: 64-bit (fixed64, sfixed64, double)
   *   - 2: Length-delimited (string, bytes, embedded messages, packed repeated fields)
   *   - 5: 32-bit (fixed32, sfixed32, float)
   *
   * Following https://protobuf.dev/programming-guides/encoding/#structure
   */
  inline void encode_field_raw(uint32_t field_id, uint32_t type) {
    uint32_t val = (field_id << 3) | (type & 0b111);
    this->encode_varint_raw(val);
  }
  inline void encode_string(uint32_t field_id, const char *string, size_t len, bool force = false) {
    if (len == 0 && !force)
      return;

    this->encode_field_raw(field_id, 2);  // type 2: Length-delimited string
    this->encode_varint_raw(len);
    auto *data = reinterpret_cast<const uint8_t *>(string);
    this->buffer_->insert(this->buffer_->end(), data, data + len);
  }
  inline void encode_string(uint32_t field_id, const std::string &value, bool force = false) {
    this->encode_string(field_id, value.data(), value.size(), force);
  }
  inline void encode_bytes(uint32_t field_id, const uint8_t *data, size_t len, bool force = false) {
    this->encode_string(field_id, reinterpret_cast<const char *>(data), len, force);
  }
  inline void encode_uint32(uint32_t field_id, uint32_t value, bool force = false) {
    if (value == 0 && !force)
      return;
    this->encode_field_raw(field_id, 0);  // type 0: Varint - uint32
    this->encode_varint_raw(value);
  }
  inline void encode_uint64(uint32_t field_id, uint64_t value, bool force = false) {
    if (value == 0 && !force)
      return;
    this->encode_field_raw(field_id, 0);  // type 0: Varint - uint64
    this->encode_varint_raw(ProtoVarInt(value));
  }
  inline void encode_bool(uint32_t field_id, bool value, bool force = false) {
    if (!value && !force)
      return;
    this->encode_field_raw(field_id, 0);  // type 0: Varint - bool
    this->write(0x01);
  }
  void encode_fixed32(uint32_t field_id, uint32_t value, bool force = false) {
    if (value == 0 && !force)
      return;

    this->encode_field_raw(field_id, 5);  // type 5: 32-bit fixed32
    // Reserve space and write all 4 bytes at once for better performance
    size_t pos = this->buffer_->size();
    this->buffer_->resize(pos + 4);
    (*this->buffer_)[pos] = (value >> 0) & 0xFF;
    (*this->buffer_)[pos + 1] = (value >> 8) & 0xFF;
    (*this->buffer_)[pos + 2] = (value >> 16) & 0xFF;
    (*this->buffer_)[pos + 3] = (value >> 24) & 0xFF;
  }
  inline void encode_float(uint32_t field_id, float value, bool force = false) {
    if (value == 0.0f && !force)
      return;

    union {
      float value;
      uint32_t raw;
    } val{};
    val.value = value;
    this->encode_fixed32(field_id, val.raw);
  }
  inline void encode_int32(uint32_t field_id, int32_t value, bool force = false) {
    if (value < 0) {
      // negative int32 is always 10 byte long
      this->encode_int64(field_id, value, force);
      return;
    }
    this->encode_uint32(field_id, static_cast<uint32_t>(value), force);
  }
  inline void encode_int64(uint32_t field_id, int64_t value, bool force = false) {
    this->encode_uint64(field_id, static_cast<uint64_t>(value), force);
  }
  inline void encode_sint32(uint32_t field_id, int32_t value, bool force = false) {
    uint32_t uvalue;
    if (value < 0) {
      uvalue = ~(value << 1);
    } else {
      uvalue = value << 1;
    }
    this->encode_uint32(field_id, uvalue, force);
  }
  inline void encode_sint64(uint32_t field_id, int64_t value, bool force = false) {
    uint64_t uvalue;
    if (value < 0) {
      uvalue = ~(value << 1);
    } else {
      uvalue = value << 1;
    }
    this->encode_uint64(field_id, uvalue, force);
  }
  inline void encode_sfixed32(uint32_t field_id, int32_t value, bool force = false) {
    if (!force && value == 0)
      return;
    this->encode_fixed32(field_id, static_cast<uint32_t>(value), force);
  }
  template<class C> void encode_message(uint32_t field_id, const C &value, bool force = false) {
    this->encode_field_raw(field_id, 2);  // type 2: Length-delimited message
    size_t begin = this->buffer_->size();

    value.encode(*this);

    const uint32_t nested_length = this->buffer_->size() - begin;
    // add size varint
    std::vector<uint8_t> var;
    ProtoVarInt(nested_length).encode(var);
    this->buffer_->insert(this->buffer_->begin() + begin, var.begin(), var.end());
  }
  std::vector<uint8_t> *get_buffer() const { return buffer_; }

 protected:
  std::vector<uint8_t> *buffer_;
};

class ProtoMessage {
 public:
  virtual ~ProtoMessage() = default;

  // Metadata getters - must be implemented by derived classes
  virtual const FieldMeta *get_field_metadata() const { return nullptr; }
  virtual uint8_t get_field_count() const { return 0; }
  virtual const RepeatedFieldMeta *get_repeated_field_metadata() const { return nullptr; }
  virtual uint8_t get_repeated_field_count() const { return 0; }

  // Encode/decode/calculate_size using V2 metadata (will check for V3 first)
  void encode(ProtoWriteBuffer buffer) const;
  void decode(const uint8_t *buffer, size_t length);
  void calculate_size(uint32_t &total_size) const;

#ifdef HAS_PROTO_MESSAGE_DUMP
  std::string dump() const;
  virtual void dump_to(std::string &out) const = 0;
  virtual const char *message_name() const { return "unknown"; }
#endif

 protected:
};

template<typename T> const char *proto_enum_to_string(T value);

class ProtoService {
 public:
 protected:
  virtual bool is_authenticated() = 0;
  virtual bool is_connection_setup() = 0;
  virtual void on_fatal_error() = 0;
  virtual void on_unauthenticated_access() = 0;
  virtual void on_no_setup_connection() = 0;
  /**
   * Create a buffer with a reserved size.
   * @param reserve_size The number of bytes to pre-allocate in the buffer. This is a hint
   *                     to optimize memory usage and avoid reallocations during encoding.
   *                     Implementations should aim to allocate at least this size.
   * @return A ProtoWriteBuffer object with the reserved size.
   */
  virtual ProtoWriteBuffer create_buffer(uint32_t reserve_size) = 0;
  virtual bool send_buffer(ProtoWriteBuffer buffer, uint8_t message_type) = 0;
  virtual void read_message(uint32_t msg_size, uint32_t msg_type, uint8_t *msg_data) = 0;

  // Optimized method that pre-allocates buffer based on message size
  bool send_message_(const ProtoMessage &msg, uint8_t message_type) {
    uint32_t msg_size = 0;
    msg.calculate_size(msg_size);

    // Create a pre-sized buffer
    auto buffer = this->create_buffer(msg_size);

    // Encode message into the buffer
    msg.encode(buffer);

    // Send the buffer
    return this->send_buffer(buffer, message_type);
  }

  // Authentication helper methods
  bool check_connection_setup_() {
    if (!this->is_connection_setup()) {
      this->on_no_setup_connection();
      return false;
    }
    return true;
  }

  bool check_authenticated_() {
    if (!this->check_connection_setup_()) {
      return false;
    }
    if (!this->is_authenticated()) {
      this->on_unauthenticated_access();
      return false;
    }
    return true;
  }
};
template<typename MessageType>
void encode_repeated_message_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num);

template<typename MessageType>
void size_repeated_message_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size);

template<typename MessageType>
void encode_message_field(ProtoWriteBuffer &buffer, const void *field_ptr, uint8_t field_num);

template<typename MessageType>
void size_message_field(uint32_t &total_size, const void *field_ptr, uint8_t precalced_field_id_size, bool force);

}  // namespace api
}  // namespace esphome
