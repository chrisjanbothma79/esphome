// This file was automatically generated with a tool.
// See script/api_protobuf/api_protobuf.py
#include "api_pb2.h"
#include "api_pb2_size.h"
#include "proto_templates.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace api {

bool HelloRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->api_version_major = value.as_uint32();
      return true;
    }
    case 3: {
      this->api_version_minor = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool HelloRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->client_info = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void HelloRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->client_info);
  buffer.encode_uint32(2, this->api_version_major);
  buffer.encode_uint32(3, this->api_version_minor);
}
void HelloRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->client_info, false);
  ProtoSize::add_uint32_field(total_size, 1, this->api_version_major, false);
  ProtoSize::add_uint32_field(total_size, 1, this->api_version_minor, false);
}
bool HelloResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool HelloResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void HelloResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void HelloResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool ConnectRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->password = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void ConnectRequest::encode(ProtoWriteBuffer buffer) const { buffer.encode_string(1, this->password); }
void ConnectRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->password, false);
}
bool ConnectResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ConnectResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ConnectResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool AreaInfo::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->area_id = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool AreaInfo::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 2: {
      this->name = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void AreaInfo::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint32(1, this->area_id);
  buffer.encode_string(2, this->name);
}
void AreaInfo::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint32_field(total_size, 1, this->area_id, false);
  ProtoSize::add_string_field(total_size, 1, this->name, false);
}
bool DeviceInfo::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->device_id = value.as_uint32();
      return true;
    }
    case 3: {
      this->area_id = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool DeviceInfo::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 2: {
      this->name = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void DeviceInfo::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint32(1, this->device_id);
  buffer.encode_string(2, this->name);
  buffer.encode_uint32(3, this->area_id);
}
void DeviceInfo::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint32_field(total_size, 1, this->device_id, false);
  ProtoSize::add_string_field(total_size, 1, this->name, false);
  ProtoSize::add_uint32_field(total_size, 1, this->area_id, false);
}
bool DeviceInfoResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool DeviceInfoResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void DeviceInfoResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void DeviceInfoResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
#ifdef USE_BINARY_SENSOR
bool ListEntitiesBinarySensorResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesBinarySensorResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesBinarySensorResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesBinarySensorResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesBinarySensorResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BinarySensorStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BinarySensorStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BinarySensorStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BinarySensorStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
#ifdef USE_COVER
bool ListEntitiesCoverResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesCoverResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesCoverResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesCoverResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesCoverResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool CoverStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool CoverStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void CoverStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void CoverStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool CoverCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->has_legacy_command = value.as_bool();
      return true;
    }
    case 3: {
      this->legacy_command = value.as_enum<enums::LegacyCoverCommand>();
      return true;
    }
    case 4: {
      this->has_position = value.as_bool();
      return true;
    }
    case 6: {
      this->has_tilt = value.as_bool();
      return true;
    }
    case 8: {
      this->stop = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool CoverCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 5: {
      this->position = value.as_float();
      return true;
    }
    case 7: {
      this->tilt = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void CoverCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->has_legacy_command);
  buffer.encode_enum<enums::LegacyCoverCommand>(3, this->legacy_command);
  buffer.encode_bool(4, this->has_position);
  buffer.encode_float(5, this->position);
  buffer.encode_bool(6, this->has_tilt);
  buffer.encode_float(7, this->tilt);
  buffer.encode_bool(8, this->stop);
}
void CoverCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_legacy_command, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->legacy_command), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_position, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->position != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_tilt, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->tilt != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->stop, false);
}
#endif
#ifdef USE_FAN
bool ListEntitiesFanResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesFanResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesFanResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesFanResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesFanResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool FanStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool FanStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool FanStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void FanStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void FanStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool FanCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->has_state = value.as_bool();
      return true;
    }
    case 3: {
      this->state = value.as_bool();
      return true;
    }
    case 4: {
      this->has_speed = value.as_bool();
      return true;
    }
    case 5: {
      this->speed = value.as_enum<enums::FanSpeed>();
      return true;
    }
    case 6: {
      this->has_oscillating = value.as_bool();
      return true;
    }
    case 7: {
      this->oscillating = value.as_bool();
      return true;
    }
    case 8: {
      this->has_direction = value.as_bool();
      return true;
    }
    case 9: {
      this->direction = value.as_enum<enums::FanDirection>();
      return true;
    }
    case 10: {
      this->has_speed_level = value.as_bool();
      return true;
    }
    case 11: {
      this->speed_level = value.as_int32();
      return true;
    }
    case 12: {
      this->has_preset_mode = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool FanCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 13: {
      this->preset_mode = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool FanCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void FanCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->has_state);
  buffer.encode_bool(3, this->state);
  buffer.encode_bool(4, this->has_speed);
  buffer.encode_enum<enums::FanSpeed>(5, this->speed);
  buffer.encode_bool(6, this->has_oscillating);
  buffer.encode_bool(7, this->oscillating);
  buffer.encode_bool(8, this->has_direction);
  buffer.encode_enum<enums::FanDirection>(9, this->direction);
  buffer.encode_bool(10, this->has_speed_level);
  buffer.encode_int32(11, this->speed_level);
  buffer.encode_bool(12, this->has_preset_mode);
  buffer.encode_string(13, this->preset_mode);
}
void FanCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_state, false);
  ProtoSize::add_bool_field(total_size, 1, this->state, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_speed, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->speed), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_oscillating, false);
  ProtoSize::add_bool_field(total_size, 1, this->oscillating, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_direction, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->direction), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_speed_level, false);
  ProtoSize::add_int32_field(total_size, 1, this->speed_level, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_preset_mode, false);
  ProtoSize::add_string_field(total_size, 1, this->preset_mode, false);
}
#endif
#ifdef USE_LIGHT
bool ListEntitiesLightResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesLightResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesLightResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesLightResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesLightResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool LightStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool LightStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool LightStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void LightStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void LightStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool LightCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->has_state = value.as_bool();
      return true;
    }
    case 3: {
      this->state = value.as_bool();
      return true;
    }
    case 4: {
      this->has_brightness = value.as_bool();
      return true;
    }
    case 22: {
      this->has_color_mode = value.as_bool();
      return true;
    }
    case 23: {
      this->color_mode = value.as_enum<enums::ColorMode>();
      return true;
    }
    case 20: {
      this->has_color_brightness = value.as_bool();
      return true;
    }
    case 6: {
      this->has_rgb = value.as_bool();
      return true;
    }
    case 10: {
      this->has_white = value.as_bool();
      return true;
    }
    case 12: {
      this->has_color_temperature = value.as_bool();
      return true;
    }
    case 24: {
      this->has_cold_white = value.as_bool();
      return true;
    }
    case 26: {
      this->has_warm_white = value.as_bool();
      return true;
    }
    case 14: {
      this->has_transition_length = value.as_bool();
      return true;
    }
    case 15: {
      this->transition_length = value.as_uint32();
      return true;
    }
    case 16: {
      this->has_flash_length = value.as_bool();
      return true;
    }
    case 17: {
      this->flash_length = value.as_uint32();
      return true;
    }
    case 18: {
      this->has_effect = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool LightCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 19: {
      this->effect = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool LightCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 5: {
      this->brightness = value.as_float();
      return true;
    }
    case 21: {
      this->color_brightness = value.as_float();
      return true;
    }
    case 7: {
      this->red = value.as_float();
      return true;
    }
    case 8: {
      this->green = value.as_float();
      return true;
    }
    case 9: {
      this->blue = value.as_float();
      return true;
    }
    case 11: {
      this->white = value.as_float();
      return true;
    }
    case 13: {
      this->color_temperature = value.as_float();
      return true;
    }
    case 25: {
      this->cold_white = value.as_float();
      return true;
    }
    case 27: {
      this->warm_white = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void LightCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->has_state);
  buffer.encode_bool(3, this->state);
  buffer.encode_bool(4, this->has_brightness);
  buffer.encode_float(5, this->brightness);
  buffer.encode_bool(22, this->has_color_mode);
  buffer.encode_enum<enums::ColorMode>(23, this->color_mode);
  buffer.encode_bool(20, this->has_color_brightness);
  buffer.encode_float(21, this->color_brightness);
  buffer.encode_bool(6, this->has_rgb);
  buffer.encode_float(7, this->red);
  buffer.encode_float(8, this->green);
  buffer.encode_float(9, this->blue);
  buffer.encode_bool(10, this->has_white);
  buffer.encode_float(11, this->white);
  buffer.encode_bool(12, this->has_color_temperature);
  buffer.encode_float(13, this->color_temperature);
  buffer.encode_bool(24, this->has_cold_white);
  buffer.encode_float(25, this->cold_white);
  buffer.encode_bool(26, this->has_warm_white);
  buffer.encode_float(27, this->warm_white);
  buffer.encode_bool(14, this->has_transition_length);
  buffer.encode_uint32(15, this->transition_length);
  buffer.encode_bool(16, this->has_flash_length);
  buffer.encode_uint32(17, this->flash_length);
  buffer.encode_bool(18, this->has_effect);
  buffer.encode_string(19, this->effect);
}
void LightCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_state, false);
  ProtoSize::add_bool_field(total_size, 1, this->state, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_brightness, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->brightness != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 2, this->has_color_mode, false);
  ProtoSize::add_enum_field(total_size, 2, static_cast<uint32_t>(this->color_mode), false);
  ProtoSize::add_bool_field(total_size, 2, this->has_color_brightness, false);
  ProtoSize::add_fixed_field<4>(total_size, 2, this->color_brightness != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_rgb, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->red != 0.0f, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->green != 0.0f, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->blue != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_white, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->white != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_color_temperature, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->color_temperature != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 2, this->has_cold_white, false);
  ProtoSize::add_fixed_field<4>(total_size, 2, this->cold_white != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 2, this->has_warm_white, false);
  ProtoSize::add_fixed_field<4>(total_size, 2, this->warm_white != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_transition_length, false);
  ProtoSize::add_uint32_field(total_size, 1, this->transition_length, false);
  ProtoSize::add_bool_field(total_size, 2, this->has_flash_length, false);
  ProtoSize::add_uint32_field(total_size, 2, this->flash_length, false);
  ProtoSize::add_bool_field(total_size, 2, this->has_effect, false);
  ProtoSize::add_string_field(total_size, 2, this->effect, false);
}
#endif
#ifdef USE_SENSOR
bool ListEntitiesSensorResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSensorResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSensorResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesSensorResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesSensorResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool SensorStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SensorStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SensorStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SensorStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
#ifdef USE_SWITCH
bool ListEntitiesSwitchResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSwitchResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSwitchResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesSwitchResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesSwitchResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool SwitchStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SwitchStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SwitchStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SwitchStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool SwitchCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->state = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool SwitchCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void SwitchCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->state);
}
void SwitchCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->state, false);
}
#endif
#ifdef USE_TEXT_SENSOR
bool ListEntitiesTextSensorResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesTextSensorResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesTextSensorResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesTextSensorResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesTextSensorResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool TextSensorStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool TextSensorStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool TextSensorStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void TextSensorStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void TextSensorStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
bool SubscribeLogsRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->level = value.as_enum<enums::LogLevel>();
      return true;
    }
    case 2: {
      this->dump_config = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
void SubscribeLogsRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_enum<enums::LogLevel>(1, this->level);
  buffer.encode_bool(2, this->dump_config);
}
void SubscribeLogsRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->level), false);
  ProtoSize::add_bool_field(total_size, 1, this->dump_config, false);
}
bool SubscribeLogsResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SubscribeLogsResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SubscribeLogsResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SubscribeLogsResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#ifdef USE_API_NOISE
bool NoiseEncryptionSetKeyRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void NoiseEncryptionSetKeyRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_bytes(1, reinterpret_cast<const uint8_t *>(this->key.data()), this->key.size());
}
void NoiseEncryptionSetKeyRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->key, false);
}
bool NoiseEncryptionSetKeyResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void NoiseEncryptionSetKeyResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void NoiseEncryptionSetKeyResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
bool HomeassistantServiceMap::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_string();
      return true;
    }
    case 2: {
      this->value = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void HomeassistantServiceMap::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->key);
  buffer.encode_string(2, this->value);
}
void HomeassistantServiceMap::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->key, false);
  ProtoSize::add_string_field(total_size, 1, this->value, false);
}
bool HomeassistantServiceResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool HomeassistantServiceResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void HomeassistantServiceResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void HomeassistantServiceResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool SubscribeHomeAssistantStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SubscribeHomeAssistantStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SubscribeHomeAssistantStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SubscribeHomeAssistantStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool HomeAssistantStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void HomeAssistantStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void HomeAssistantStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool GetTimeResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void GetTimeResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void GetTimeResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool ListEntitiesServicesArgument::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->type = value.as_enum<enums::ServiceArgType>();
      return true;
    }
    default:
      return false;
  }
}
bool ListEntitiesServicesArgument::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->name = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void ListEntitiesServicesArgument::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->name);
  buffer.encode_enum<enums::ServiceArgType>(2, this->type);
}
void ListEntitiesServicesArgument::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->name, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->type), false);
}
bool ListEntitiesServicesResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesServicesResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesServicesResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesServicesResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool ExecuteServiceArgument::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->bool_ = value.as_bool();
      return true;
    }
    case 2: {
      this->legacy_int = value.as_int32();
      return true;
    }
    case 5: {
      this->int_ = value.as_sint32();
      return true;
    }
    case 6: {
      this->bool_array.push_back(value.as_bool());
      return true;
    }
    case 7: {
      this->int_array.push_back(value.as_sint32());
      return true;
    }
    default:
      return false;
  }
}
bool ExecuteServiceArgument::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 4: {
      this->string_ = value.as_string();
      return true;
    }
    case 9: {
      this->string_array.push_back(value.as_string());
      return true;
    }
    default:
      return false;
  }
}
bool ExecuteServiceArgument::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 3: {
      this->float_ = value.as_float();
      return true;
    }
    case 8: {
      this->float_array.push_back(value.as_float());
      return true;
    }
    default:
      return false;
  }
}
void ExecuteServiceArgument::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_bool(1, this->bool_);
  buffer.encode_int32(2, this->legacy_int);
  buffer.encode_float(3, this->float_);
  buffer.encode_string(4, this->string_);
  buffer.encode_sint32(5, this->int_);
  for (auto it : this->bool_array) {
    buffer.encode_bool(6, it, true);
  }
  for (auto &it : this->int_array) {
    buffer.encode_sint32(7, it, true);
  }
  for (auto &it : this->float_array) {
    buffer.encode_float(8, it, true);
  }
  for (auto &it : this->string_array) {
    buffer.encode_string(9, it, true);
  }
}
void ExecuteServiceArgument::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_bool_field(total_size, 1, this->bool_, false);
  ProtoSize::add_int32_field(total_size, 1, this->legacy_int, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->float_ != 0.0f, false);
  ProtoSize::add_string_field(total_size, 1, this->string_, false);
  ProtoSize::add_sint32_field(total_size, 1, this->int_, false);
  if (!this->bool_array.empty()) {
    for (const auto it : this->bool_array) {
      ProtoSize::add_bool_field(total_size, 1, it, true);
    }
  }
  if (!this->int_array.empty()) {
    for (const auto &it : this->int_array) {
      ProtoSize::add_sint32_field(total_size, 1, it, true);
    }
  }
  if (!this->float_array.empty()) {
    for (const auto &it : this->float_array) {
      ProtoSize::add_fixed_field<4>(total_size, 1, it != 0.0f, true);
    }
  }
  if (!this->string_array.empty()) {
    for (const auto &it : this->string_array) {
      ProtoSize::add_string_field(total_size, 1, it, true);
    }
  }
}
bool ExecuteServiceRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 2: {
      this->args.push_back(value.as_message<ExecuteServiceArgument>());
      return true;
    }
    default:
      return false;
  }
}
bool ExecuteServiceRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void ExecuteServiceRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  for (auto &it : this->args) {
    buffer.encode_message<ExecuteServiceArgument>(2, it, true);
  }
}
void ExecuteServiceRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_repeated_message(total_size, 1, this->args);
}
#ifdef USE_CAMERA
bool ListEntitiesCameraResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesCameraResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesCameraResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesCameraResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesCameraResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool CameraImageResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool CameraImageResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool CameraImageResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void CameraImageResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void CameraImageResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool CameraImageRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->single = value.as_bool();
      return true;
    }
    case 2: {
      this->stream = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
void CameraImageRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_bool(1, this->single);
  buffer.encode_bool(2, this->stream);
}
void CameraImageRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_bool_field(total_size, 1, this->single, false);
  ProtoSize::add_bool_field(total_size, 1, this->stream, false);
}
#endif
#ifdef USE_CLIMATE
bool ListEntitiesClimateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesClimateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesClimateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesClimateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesClimateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool ClimateStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ClimateStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ClimateStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ClimateStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ClimateStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool ClimateCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->has_mode = value.as_bool();
      return true;
    }
    case 3: {
      this->mode = value.as_enum<enums::ClimateMode>();
      return true;
    }
    case 4: {
      this->has_target_temperature = value.as_bool();
      return true;
    }
    case 6: {
      this->has_target_temperature_low = value.as_bool();
      return true;
    }
    case 8: {
      this->has_target_temperature_high = value.as_bool();
      return true;
    }
    case 10: {
      this->unused_has_legacy_away = value.as_bool();
      return true;
    }
    case 11: {
      this->unused_legacy_away = value.as_bool();
      return true;
    }
    case 12: {
      this->has_fan_mode = value.as_bool();
      return true;
    }
    case 13: {
      this->fan_mode = value.as_enum<enums::ClimateFanMode>();
      return true;
    }
    case 14: {
      this->has_swing_mode = value.as_bool();
      return true;
    }
    case 15: {
      this->swing_mode = value.as_enum<enums::ClimateSwingMode>();
      return true;
    }
    case 16: {
      this->has_custom_fan_mode = value.as_bool();
      return true;
    }
    case 18: {
      this->has_preset = value.as_bool();
      return true;
    }
    case 19: {
      this->preset = value.as_enum<enums::ClimatePreset>();
      return true;
    }
    case 20: {
      this->has_custom_preset = value.as_bool();
      return true;
    }
    case 22: {
      this->has_target_humidity = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool ClimateCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 17: {
      this->custom_fan_mode = value.as_string();
      return true;
    }
    case 21: {
      this->custom_preset = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool ClimateCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 5: {
      this->target_temperature = value.as_float();
      return true;
    }
    case 7: {
      this->target_temperature_low = value.as_float();
      return true;
    }
    case 9: {
      this->target_temperature_high = value.as_float();
      return true;
    }
    case 23: {
      this->target_humidity = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void ClimateCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->has_mode);
  buffer.encode_enum<enums::ClimateMode>(3, this->mode);
  buffer.encode_bool(4, this->has_target_temperature);
  buffer.encode_float(5, this->target_temperature);
  buffer.encode_bool(6, this->has_target_temperature_low);
  buffer.encode_float(7, this->target_temperature_low);
  buffer.encode_bool(8, this->has_target_temperature_high);
  buffer.encode_float(9, this->target_temperature_high);
  buffer.encode_bool(10, this->unused_has_legacy_away);
  buffer.encode_bool(11, this->unused_legacy_away);
  buffer.encode_bool(12, this->has_fan_mode);
  buffer.encode_enum<enums::ClimateFanMode>(13, this->fan_mode);
  buffer.encode_bool(14, this->has_swing_mode);
  buffer.encode_enum<enums::ClimateSwingMode>(15, this->swing_mode);
  buffer.encode_bool(16, this->has_custom_fan_mode);
  buffer.encode_string(17, this->custom_fan_mode);
  buffer.encode_bool(18, this->has_preset);
  buffer.encode_enum<enums::ClimatePreset>(19, this->preset);
  buffer.encode_bool(20, this->has_custom_preset);
  buffer.encode_string(21, this->custom_preset);
  buffer.encode_bool(22, this->has_target_humidity);
  buffer.encode_float(23, this->target_humidity);
}
void ClimateCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_mode, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->mode), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_target_temperature, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->target_temperature != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_target_temperature_low, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->target_temperature_low != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_target_temperature_high, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->target_temperature_high != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->unused_has_legacy_away, false);
  ProtoSize::add_bool_field(total_size, 1, this->unused_legacy_away, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_fan_mode, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->fan_mode), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_swing_mode, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->swing_mode), false);
  ProtoSize::add_bool_field(total_size, 2, this->has_custom_fan_mode, false);
  ProtoSize::add_string_field(total_size, 2, this->custom_fan_mode, false);
  ProtoSize::add_bool_field(total_size, 2, this->has_preset, false);
  ProtoSize::add_enum_field(total_size, 2, static_cast<uint32_t>(this->preset), false);
  ProtoSize::add_bool_field(total_size, 2, this->has_custom_preset, false);
  ProtoSize::add_string_field(total_size, 2, this->custom_preset, false);
  ProtoSize::add_bool_field(total_size, 2, this->has_target_humidity, false);
  ProtoSize::add_fixed_field<4>(total_size, 2, this->target_humidity != 0.0f, false);
}
#endif
#ifdef USE_NUMBER
bool ListEntitiesNumberResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesNumberResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesNumberResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesNumberResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesNumberResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool NumberStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool NumberStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void NumberStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void NumberStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool NumberCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 2: {
      this->state = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void NumberCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_float(2, this->state);
}
void NumberCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->state != 0.0f, false);
}
#endif
#ifdef USE_SELECT
bool ListEntitiesSelectResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSelectResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSelectResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesSelectResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesSelectResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool SelectStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SelectStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SelectStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SelectStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SelectStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool SelectCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 2: {
      this->state = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool SelectCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void SelectCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_string(2, this->state);
}
void SelectCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_string_field(total_size, 1, this->state, false);
}
#endif
#ifdef USE_SIREN
bool ListEntitiesSirenResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSirenResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesSirenResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesSirenResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesSirenResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool SirenStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SirenStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SirenStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SirenStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool SirenCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->has_state = value.as_bool();
      return true;
    }
    case 3: {
      this->state = value.as_bool();
      return true;
    }
    case 4: {
      this->has_tone = value.as_bool();
      return true;
    }
    case 6: {
      this->has_duration = value.as_bool();
      return true;
    }
    case 7: {
      this->duration = value.as_uint32();
      return true;
    }
    case 8: {
      this->has_volume = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool SirenCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 5: {
      this->tone = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool SirenCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 9: {
      this->volume = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void SirenCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->has_state);
  buffer.encode_bool(3, this->state);
  buffer.encode_bool(4, this->has_tone);
  buffer.encode_string(5, this->tone);
  buffer.encode_bool(6, this->has_duration);
  buffer.encode_uint32(7, this->duration);
  buffer.encode_bool(8, this->has_volume);
  buffer.encode_float(9, this->volume);
}
void SirenCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_state, false);
  ProtoSize::add_bool_field(total_size, 1, this->state, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_tone, false);
  ProtoSize::add_string_field(total_size, 1, this->tone, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_duration, false);
  ProtoSize::add_uint32_field(total_size, 1, this->duration, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_volume, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->volume != 0.0f, false);
}
#endif
#ifdef USE_LOCK
bool ListEntitiesLockResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesLockResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesLockResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesLockResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesLockResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool LockStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool LockStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void LockStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void LockStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool LockCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->command = value.as_enum<enums::LockCommand>();
      return true;
    }
    case 3: {
      this->has_code = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool LockCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 4: {
      this->code = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool LockCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void LockCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_enum<enums::LockCommand>(2, this->command);
  buffer.encode_bool(3, this->has_code);
  buffer.encode_string(4, this->code);
}
void LockCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->command), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_code, false);
  ProtoSize::add_string_field(total_size, 1, this->code, false);
}
#endif
#ifdef USE_BUTTON
bool ListEntitiesButtonResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesButtonResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesButtonResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesButtonResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesButtonResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool ButtonCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void ButtonCommandRequest::encode(ProtoWriteBuffer buffer) const { buffer.encode_fixed32(1, this->key); }
void ButtonCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
}
#endif
#ifdef USE_MEDIA_PLAYER
bool MediaPlayerSupportedFormat::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->sample_rate = value.as_uint32();
      return true;
    }
    case 3: {
      this->num_channels = value.as_uint32();
      return true;
    }
    case 4: {
      this->purpose = value.as_enum<enums::MediaPlayerFormatPurpose>();
      return true;
    }
    case 5: {
      this->sample_bytes = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool MediaPlayerSupportedFormat::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->format = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void MediaPlayerSupportedFormat::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->format);
  buffer.encode_uint32(2, this->sample_rate);
  buffer.encode_uint32(3, this->num_channels);
  buffer.encode_enum<enums::MediaPlayerFormatPurpose>(4, this->purpose);
  buffer.encode_uint32(5, this->sample_bytes);
}
void MediaPlayerSupportedFormat::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->format, false);
  ProtoSize::add_uint32_field(total_size, 1, this->sample_rate, false);
  ProtoSize::add_uint32_field(total_size, 1, this->num_channels, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->purpose), false);
  ProtoSize::add_uint32_field(total_size, 1, this->sample_bytes, false);
}
bool ListEntitiesMediaPlayerResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesMediaPlayerResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesMediaPlayerResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesMediaPlayerResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesMediaPlayerResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool MediaPlayerStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool MediaPlayerStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void MediaPlayerStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void MediaPlayerStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool MediaPlayerCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->has_command = value.as_bool();
      return true;
    }
    case 3: {
      this->command = value.as_enum<enums::MediaPlayerCommand>();
      return true;
    }
    case 4: {
      this->has_volume = value.as_bool();
      return true;
    }
    case 6: {
      this->has_media_url = value.as_bool();
      return true;
    }
    case 8: {
      this->has_announcement = value.as_bool();
      return true;
    }
    case 9: {
      this->announcement = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool MediaPlayerCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 7: {
      this->media_url = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool MediaPlayerCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 5: {
      this->volume = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void MediaPlayerCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->has_command);
  buffer.encode_enum<enums::MediaPlayerCommand>(3, this->command);
  buffer.encode_bool(4, this->has_volume);
  buffer.encode_float(5, this->volume);
  buffer.encode_bool(6, this->has_media_url);
  buffer.encode_string(7, this->media_url);
  buffer.encode_bool(8, this->has_announcement);
  buffer.encode_bool(9, this->announcement);
}
void MediaPlayerCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_command, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->command), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_volume, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->volume != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_media_url, false);
  ProtoSize::add_string_field(total_size, 1, this->media_url, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_announcement, false);
  ProtoSize::add_bool_field(total_size, 1, this->announcement, false);
}
#endif
#ifdef USE_BLUETOOTH_PROXY
bool SubscribeBluetoothLEAdvertisementsRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->flags = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
void SubscribeBluetoothLEAdvertisementsRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint32(1, this->flags);
}
void SubscribeBluetoothLEAdvertisementsRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint32_field(total_size, 1, this->flags, false);
}
bool BluetoothServiceData::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->legacy_data.push_back(value.as_uint32());
      return true;
    }
    default:
      return false;
  }
}
bool BluetoothServiceData::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->uuid = value.as_string();
      return true;
    }
    case 3: {
      this->data = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothServiceData::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->uuid);
  for (auto &it : this->legacy_data) {
    buffer.encode_uint32(2, it, true);
  }
  buffer.encode_bytes(3, reinterpret_cast<const uint8_t *>(this->data.data()), this->data.size());
}
void BluetoothServiceData::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->uuid, false);
  if (!this->legacy_data.empty()) {
    for (const auto &it : this->legacy_data) {
      ProtoSize::add_uint32_field(total_size, 1, it, true);
    }
  }
  ProtoSize::add_string_field(total_size, 1, this->data, false);
}
bool BluetoothLEAdvertisementResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothLEAdvertisementResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothLEAdvertisementResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothLEAdvertisementResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool BluetoothLERawAdvertisement::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    case 2: {
      this->rssi = value.as_sint32();
      return true;
    }
    case 3: {
      this->address_type = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool BluetoothLERawAdvertisement::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 4: {
      this->data = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothLERawAdvertisement::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint64(1, this->address);
  buffer.encode_sint32(2, this->rssi);
  buffer.encode_uint32(3, this->address_type);
  buffer.encode_bytes(4, reinterpret_cast<const uint8_t *>(this->data.data()), this->data.size());
}
void BluetoothLERawAdvertisement::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
  ProtoSize::add_sint32_field(total_size, 1, this->rssi, false);
  ProtoSize::add_uint32_field(total_size, 1, this->address_type, false);
  ProtoSize::add_string_field(total_size, 1, this->data, false);
}
bool BluetoothLERawAdvertisementsResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothLERawAdvertisementsResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, nullptr, 0, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothLERawAdvertisementsResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, nullptr, 0, REPEATED_FIELDS, REPEATED_COUNT);
}
bool BluetoothDeviceRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    case 2: {
      this->request_type = value.as_enum<enums::BluetoothDeviceRequestType>();
      return true;
    }
    case 3: {
      this->has_address_type = value.as_bool();
      return true;
    }
    case 4: {
      this->address_type = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothDeviceRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint64(1, this->address);
  buffer.encode_enum<enums::BluetoothDeviceRequestType>(2, this->request_type);
  buffer.encode_bool(3, this->has_address_type);
  buffer.encode_uint32(4, this->address_type);
}
void BluetoothDeviceRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->request_type), false);
  ProtoSize::add_bool_field(total_size, 1, this->has_address_type, false);
  ProtoSize::add_uint32_field(total_size, 1, this->address_type, false);
}
bool BluetoothDeviceConnectionResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothDeviceConnectionResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothDeviceConnectionResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTGetServicesRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTGetServicesRequest::encode(ProtoWriteBuffer buffer) const { buffer.encode_uint64(1, this->address); }
void BluetoothGATTGetServicesRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
}
bool BluetoothGATTDescriptor::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->uuid.push_back(value.as_uint64());
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTDescriptor::encode(ProtoWriteBuffer buffer) const {
  for (auto &it : this->uuid) {
    buffer.encode_uint64(1, it, true);
  }
  buffer.encode_uint32(2, this->handle);
}
void BluetoothGATTDescriptor::calculate_size(uint32_t &total_size) const {
  if (!this->uuid.empty()) {
    for (const auto &it : this->uuid) {
      ProtoSize::add_uint64_field(total_size, 1, it, true);
    }
  }
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
}
bool BluetoothGATTCharacteristic::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->uuid.push_back(value.as_uint64());
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    case 3: {
      this->properties = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool BluetoothGATTCharacteristic::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 4: {
      this->descriptors.push_back(value.as_message<BluetoothGATTDescriptor>());
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTCharacteristic::encode(ProtoWriteBuffer buffer) const {
  for (auto &it : this->uuid) {
    buffer.encode_uint64(1, it, true);
  }
  buffer.encode_uint32(2, this->handle);
  buffer.encode_uint32(3, this->properties);
  for (auto &it : this->descriptors) {
    buffer.encode_message<BluetoothGATTDescriptor>(4, it, true);
  }
}
void BluetoothGATTCharacteristic::calculate_size(uint32_t &total_size) const {
  if (!this->uuid.empty()) {
    for (const auto &it : this->uuid) {
      ProtoSize::add_uint64_field(total_size, 1, it, true);
    }
  }
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
  ProtoSize::add_uint32_field(total_size, 1, this->properties, false);
  ProtoSize::add_repeated_message(total_size, 1, this->descriptors);
}
bool BluetoothGATTService::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->uuid.push_back(value.as_uint64());
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool BluetoothGATTService::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 3: {
      this->characteristics.push_back(value.as_message<BluetoothGATTCharacteristic>());
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTService::encode(ProtoWriteBuffer buffer) const {
  for (auto &it : this->uuid) {
    buffer.encode_uint64(1, it, true);
  }
  buffer.encode_uint32(2, this->handle);
  for (auto &it : this->characteristics) {
    buffer.encode_message<BluetoothGATTCharacteristic>(3, it, true);
  }
}
void BluetoothGATTService::calculate_size(uint32_t &total_size) const {
  if (!this->uuid.empty()) {
    for (const auto &it : this->uuid) {
      ProtoSize::add_uint64_field(total_size, 1, it, true);
    }
  }
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
  ProtoSize::add_repeated_message(total_size, 1, this->characteristics);
}
bool BluetoothGATTGetServicesResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothGATTGetServicesResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTGetServicesResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothGATTGetServicesResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool BluetoothGATTGetServicesDoneResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTGetServicesDoneResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTGetServicesDoneResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTReadRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTReadRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint64(1, this->address);
  buffer.encode_uint32(2, this->handle);
}
void BluetoothGATTReadRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
}
bool BluetoothGATTReadResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothGATTReadResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTReadResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTReadResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTWriteRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    case 3: {
      this->response = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool BluetoothGATTWriteRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 4: {
      this->data = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTWriteRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint64(1, this->address);
  buffer.encode_uint32(2, this->handle);
  buffer.encode_bool(3, this->response);
  buffer.encode_bytes(4, reinterpret_cast<const uint8_t *>(this->data.data()), this->data.size());
}
void BluetoothGATTWriteRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
  ProtoSize::add_bool_field(total_size, 1, this->response, false);
  ProtoSize::add_string_field(total_size, 1, this->data, false);
}
bool BluetoothGATTReadDescriptorRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTReadDescriptorRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint64(1, this->address);
  buffer.encode_uint32(2, this->handle);
}
void BluetoothGATTReadDescriptorRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
}
bool BluetoothGATTWriteDescriptorRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool BluetoothGATTWriteDescriptorRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 3: {
      this->data = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTWriteDescriptorRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint64(1, this->address);
  buffer.encode_uint32(2, this->handle);
  buffer.encode_bytes(3, reinterpret_cast<const uint8_t *>(this->data.data()), this->data.size());
}
void BluetoothGATTWriteDescriptorRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
  ProtoSize::add_string_field(total_size, 1, this->data, false);
}
bool BluetoothGATTNotifyRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->address = value.as_uint64();
      return true;
    }
    case 2: {
      this->handle = value.as_uint32();
      return true;
    }
    case 3: {
      this->enable = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothGATTNotifyRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint64(1, this->address);
  buffer.encode_uint32(2, this->handle);
  buffer.encode_bool(3, this->enable);
}
void BluetoothGATTNotifyRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint64_field(total_size, 1, this->address, false);
  ProtoSize::add_uint32_field(total_size, 1, this->handle, false);
  ProtoSize::add_bool_field(total_size, 1, this->enable, false);
}
bool BluetoothGATTNotifyDataResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothGATTNotifyDataResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTNotifyDataResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTNotifyDataResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothConnectionsFreeResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothConnectionsFreeResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothConnectionsFreeResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool BluetoothGATTErrorResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTErrorResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTErrorResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTWriteResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTWriteResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTWriteResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTNotifyResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTNotifyResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTNotifyResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothDevicePairingResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothDevicePairingResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothDevicePairingResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothDeviceUnpairingResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothDeviceUnpairingResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothDeviceUnpairingResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothDeviceClearCacheResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothDeviceClearCacheResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothDeviceClearCacheResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothScannerStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothScannerStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothScannerStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothScannerSetModeRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->mode = value.as_enum<enums::BluetoothScannerMode>();
      return true;
    }
    default:
      return false;
  }
}
void BluetoothScannerSetModeRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_enum<enums::BluetoothScannerMode>(1, this->mode);
}
void BluetoothScannerSetModeRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->mode), false);
}
#endif
#ifdef USE_VOICE_ASSISTANT
bool SubscribeVoiceAssistantRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->subscribe = value.as_bool();
      return true;
    }
    case 2: {
      this->flags = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
void SubscribeVoiceAssistantRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_bool(1, this->subscribe);
  buffer.encode_uint32(2, this->flags);
}
void SubscribeVoiceAssistantRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_bool_field(total_size, 1, this->subscribe, false);
  ProtoSize::add_uint32_field(total_size, 1, this->flags, false);
}
bool VoiceAssistantAudioSettings::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->noise_suppression_level = value.as_uint32();
      return true;
    }
    case 2: {
      this->auto_gain = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool VoiceAssistantAudioSettings::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 3: {
      this->volume_multiplier = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantAudioSettings::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_uint32(1, this->noise_suppression_level);
  buffer.encode_uint32(2, this->auto_gain);
  buffer.encode_float(3, this->volume_multiplier);
}
void VoiceAssistantAudioSettings::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_uint32_field(total_size, 1, this->noise_suppression_level, false);
  ProtoSize::add_uint32_field(total_size, 1, this->auto_gain, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->volume_multiplier != 0.0f, false);
}
bool VoiceAssistantRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->start = value.as_bool();
      return true;
    }
    case 3: {
      this->flags = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool VoiceAssistantRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 2: {
      this->conversation_id = value.as_string();
      return true;
    }
    case 4: {
      this->audio_settings = value.as_message<VoiceAssistantAudioSettings>();
      return true;
    }
    case 5: {
      this->wake_word_phrase = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_bool(1, this->start);
  buffer.encode_string(2, this->conversation_id);
  buffer.encode_uint32(3, this->flags);
  buffer.encode_message<VoiceAssistantAudioSettings>(4, this->audio_settings);
  buffer.encode_string(5, this->wake_word_phrase);
}
void VoiceAssistantRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_bool_field(total_size, 1, this->start, false);
  ProtoSize::add_string_field(total_size, 1, this->conversation_id, false);
  ProtoSize::add_uint32_field(total_size, 1, this->flags, false);
  ProtoSize::add_message_object(total_size, 1, this->audio_settings, false);
  ProtoSize::add_string_field(total_size, 1, this->wake_word_phrase, false);
}
bool VoiceAssistantResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool VoiceAssistantEventData::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->name = value.as_string();
      return true;
    }
    case 2: {
      this->value = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantEventData::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->name);
  buffer.encode_string(2, this->value);
}
void VoiceAssistantEventData::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->name, false);
  ProtoSize::add_string_field(total_size, 1, this->value, false);
}
bool VoiceAssistantEventResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool VoiceAssistantEventResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantEventResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void VoiceAssistantEventResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool VoiceAssistantAudio::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->end = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool VoiceAssistantAudio::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->data = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantAudio::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_bytes(1, reinterpret_cast<const uint8_t *>(this->data.data()), this->data.size());
  buffer.encode_bool(2, this->end);
}
void VoiceAssistantAudio::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->data, false);
  ProtoSize::add_bool_field(total_size, 1, this->end, false);
}
bool VoiceAssistantTimerEventResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool VoiceAssistantTimerEventResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantTimerEventResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantTimerEventResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool VoiceAssistantAnnounceRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 4: {
      this->start_conversation = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool VoiceAssistantAnnounceRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->media_id = value.as_string();
      return true;
    }
    case 2: {
      this->text = value.as_string();
      return true;
    }
    case 3: {
      this->preannounce_media_id = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantAnnounceRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->media_id);
  buffer.encode_string(2, this->text);
  buffer.encode_string(3, this->preannounce_media_id);
  buffer.encode_bool(4, this->start_conversation);
}
void VoiceAssistantAnnounceRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->media_id, false);
  ProtoSize::add_string_field(total_size, 1, this->text, false);
  ProtoSize::add_string_field(total_size, 1, this->preannounce_media_id, false);
  ProtoSize::add_bool_field(total_size, 1, this->start_conversation, false);
}
bool VoiceAssistantAnnounceFinished::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 1: {
      this->success = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantAnnounceFinished::encode(ProtoWriteBuffer buffer) const { buffer.encode_bool(1, this->success); }
void VoiceAssistantAnnounceFinished::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_bool_field(total_size, 1, this->success, false);
}
bool VoiceAssistantWakeWord::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->id = value.as_string();
      return true;
    }
    case 2: {
      this->wake_word = value.as_string();
      return true;
    }
    case 3: {
      this->trained_languages.push_back(value.as_string());
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantWakeWord::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_string(1, this->id);
  buffer.encode_string(2, this->wake_word);
  for (auto &it : this->trained_languages) {
    buffer.encode_string(3, it, true);
  }
}
void VoiceAssistantWakeWord::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_string_field(total_size, 1, this->id, false);
  ProtoSize::add_string_field(total_size, 1, this->wake_word, false);
  if (!this->trained_languages.empty()) {
    for (const auto &it : this->trained_languages) {
      ProtoSize::add_string_field(total_size, 1, it, true);
    }
  }
}
bool VoiceAssistantConfigurationResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool VoiceAssistantConfigurationResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantConfigurationResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void VoiceAssistantConfigurationResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool VoiceAssistantSetConfiguration::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 1: {
      this->active_wake_words.push_back(value.as_string());
      return true;
    }
    default:
      return false;
  }
}
void VoiceAssistantSetConfiguration::encode(ProtoWriteBuffer buffer) const {
  for (auto &it : this->active_wake_words) {
    buffer.encode_string(1, it, true);
  }
}
void VoiceAssistantSetConfiguration::calculate_size(uint32_t &total_size) const {
  if (!this->active_wake_words.empty()) {
    for (const auto &it : this->active_wake_words) {
      ProtoSize::add_string_field(total_size, 1, it, true);
    }
  }
}
#endif
#ifdef USE_ALARM_CONTROL_PANEL
bool ListEntitiesAlarmControlPanelResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesAlarmControlPanelResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesAlarmControlPanelResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesAlarmControlPanelResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesAlarmControlPanelResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool AlarmControlPanelStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool AlarmControlPanelStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void AlarmControlPanelStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void AlarmControlPanelStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool AlarmControlPanelCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->command = value.as_enum<enums::AlarmControlPanelStateCommand>();
      return true;
    }
    default:
      return false;
  }
}
bool AlarmControlPanelCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 3: {
      this->code = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool AlarmControlPanelCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void AlarmControlPanelCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_enum<enums::AlarmControlPanelStateCommand>(2, this->command);
  buffer.encode_string(3, this->code);
}
void AlarmControlPanelCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->command), false);
  ProtoSize::add_string_field(total_size, 1, this->code, false);
}
#endif
#ifdef USE_TEXT
bool ListEntitiesTextResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesTextResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesTextResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesTextResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesTextResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool TextStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool TextStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool TextStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void TextStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void TextStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool TextCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  switch (field_id) {
    case 2: {
      this->state = value.as_string();
      return true;
    }
    default:
      return false;
  }
}
bool TextCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void TextCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_string(2, this->state);
}
void TextCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_string_field(total_size, 1, this->state, false);
}
#endif
#ifdef USE_DATETIME_DATE
bool ListEntitiesDateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesDateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesDateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesDateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesDateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool DateStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool DateStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void DateStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void DateStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool DateCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->year = value.as_uint32();
      return true;
    }
    case 3: {
      this->month = value.as_uint32();
      return true;
    }
    case 4: {
      this->day = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool DateCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void DateCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_uint32(2, this->year);
  buffer.encode_uint32(3, this->month);
  buffer.encode_uint32(4, this->day);
}
void DateCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_uint32_field(total_size, 1, this->year, false);
  ProtoSize::add_uint32_field(total_size, 1, this->month, false);
  ProtoSize::add_uint32_field(total_size, 1, this->day, false);
}
#endif
#ifdef USE_DATETIME_TIME
bool ListEntitiesTimeResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesTimeResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesTimeResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesTimeResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesTimeResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool TimeStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool TimeStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void TimeStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void TimeStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool TimeCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->hour = value.as_uint32();
      return true;
    }
    case 3: {
      this->minute = value.as_uint32();
      return true;
    }
    case 4: {
      this->second = value.as_uint32();
      return true;
    }
    default:
      return false;
  }
}
bool TimeCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void TimeCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_uint32(2, this->hour);
  buffer.encode_uint32(3, this->minute);
  buffer.encode_uint32(4, this->second);
}
void TimeCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_uint32_field(total_size, 1, this->hour, false);
  ProtoSize::add_uint32_field(total_size, 1, this->minute, false);
  ProtoSize::add_uint32_field(total_size, 1, this->second, false);
}
#endif
#ifdef USE_EVENT
bool ListEntitiesEventResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesEventResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesEventResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesEventResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ListEntitiesEventResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool EventResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool EventResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool EventResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void EventResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void EventResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
#ifdef USE_VALVE
bool ListEntitiesValveResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesValveResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesValveResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesValveResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesValveResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool ValveStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ValveStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ValveStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ValveStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool ValveCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->has_position = value.as_bool();
      return true;
    }
    case 4: {
      this->stop = value.as_bool();
      return true;
    }
    default:
      return false;
  }
}
bool ValveCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 3: {
      this->position = value.as_float();
      return true;
    }
    default:
      return false;
  }
}
void ValveCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_bool(2, this->has_position);
  buffer.encode_float(3, this->position);
  buffer.encode_bool(4, this->stop);
}
void ValveCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_bool_field(total_size, 1, this->has_position, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->position != 0.0f, false);
  ProtoSize::add_bool_field(total_size, 1, this->stop, false);
}
#endif
#ifdef USE_DATETIME_DATETIME
bool ListEntitiesDateTimeResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesDateTimeResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesDateTimeResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesDateTimeResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesDateTimeResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool DateTimeStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool DateTimeStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void DateTimeStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void DateTimeStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool DateTimeCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    case 2: {
      this->epoch_seconds = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void DateTimeCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_fixed32(2, this->epoch_seconds);
}
void DateTimeCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_fixed_field<4>(total_size, 1, this->epoch_seconds != 0, false);
}
#endif
#ifdef USE_UPDATE
bool ListEntitiesUpdateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesUpdateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesUpdateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesUpdateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesUpdateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool UpdateStateResponse::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool UpdateStateResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool UpdateStateResponse::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void UpdateStateResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void UpdateStateResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool UpdateCommandRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  switch (field_id) {
    case 2: {
      this->command = value.as_enum<enums::UpdateCommand>();
      return true;
    }
    default:
      return false;
  }
}
bool UpdateCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  switch (field_id) {
    case 1: {
      this->key = value.as_fixed32();
      return true;
    }
    default:
      return false;
  }
}
void UpdateCommandRequest::encode(ProtoWriteBuffer buffer) const {
  buffer.encode_fixed32(1, this->key);
  buffer.encode_enum<enums::UpdateCommand>(2, this->command);
}
void UpdateCommandRequest::calculate_size(uint32_t &total_size) const {
  ProtoSize::add_fixed_field<4>(total_size, 1, this->key != 0, false);
  ProtoSize::add_enum_field(total_size, 1, static_cast<uint32_t>(this->command), false);
}
#endif

// Metadata definitions for Response classes
const FieldMeta HelloResponse::FIELDS[4] = {{1,
                                             PROTO_FIELD_OFFSET(HelloResponse, api_version_major),
                                             &encode_uint32_field,
                                             &size_uint32_field,
                                             false,
                                             0,
                                             {.decode_varint = &decode_uint32_field}},
                                            {2,
                                             PROTO_FIELD_OFFSET(HelloResponse, api_version_minor),
                                             &encode_uint32_field,
                                             &size_uint32_field,
                                             false,
                                             0,
                                             {.decode_varint = &decode_uint32_field}},
                                            {3,
                                             PROTO_FIELD_OFFSET(HelloResponse, server_info),
                                             &encode_string_field,
                                             &size_string_field,
                                             false,
                                             2,
                                             {.decode_length = &decode_string_field}},
                                            {4,
                                             PROTO_FIELD_OFFSET(HelloResponse, name),
                                             &encode_string_field,
                                             &size_string_field,
                                             false,
                                             2,
                                             {.decode_length = &decode_string_field}}};
const FieldMeta ConnectResponse::FIELDS[1] = {{1,
                                               PROTO_FIELD_OFFSET(ConnectResponse, invalid_password),
                                               &encode_bool_field,
                                               &size_bool_field,
                                               false,
                                               0,
                                               {.decode_varint = &decode_bool_field}}};
const FieldMeta DeviceInfoResponse::FIELDS[19] = {
    {1,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, uses_password),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {2,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, mac_address),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, esphome_version),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, compilation_time),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, model),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, has_deep_sleep),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, project_name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, project_version),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, webserver_port),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {11,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_bluetooth_proxy_version),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {15,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_proxy_feature_flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {12,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, manufacturer),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {13,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, friendly_name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {14,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_voice_assistant_version),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {17,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, voice_assistant_feature_flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {16,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, suggested_area),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {18,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_mac_address),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {19,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, api_encryption_supported),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}}};
const RepeatedFieldMeta DeviceInfoResponse::REPEATED_FIELDS[2] = {
    {20, PROTO_FIELD_OFFSET(DeviceInfoResponse, devices), &encode_repeated_message_field<DeviceInfo>,
     &size_repeated_message_field<DeviceInfo>},
    {21, PROTO_FIELD_OFFSET(DeviceInfoResponse, areas), &encode_repeated_message_field<AreaInfo>,
     &size_repeated_message_field<AreaInfo>}};
#ifdef USE_BINARY_SENSOR
const FieldMeta ListEntitiesBinarySensorResponse::FIELDS[10] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, is_status_binary_sensor),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta BinarySensorStateResponse::FIELDS[4] = {{1,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, key),
                                                         &encode_fixed32_field,
                                                         &size_fixed32_field,
                                                         false,
                                                         5,
                                                         {.decode_32bit = &decode_fixed32_field}},
                                                        {2,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, state),
                                                         &encode_bool_field,
                                                         &size_bool_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_bool_field}},
                                                        {3,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, missing_state),
                                                         &encode_bool_field,
                                                         &size_bool_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_bool_field}},
                                                        {4,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, device_id),
                                                         &encode_uint32_field,
                                                         &size_uint32_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_COVER
const FieldMeta ListEntitiesCoverResponse::FIELDS[13] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_position),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_tilt),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_stop),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta CoverStateResponse::FIELDS[6] = {{1,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, legacy_state),
                                                  &encode_enum_field<enums::LegacyCoverState>,
                                                  &size_enum_field<enums::LegacyCoverState>,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_enum_field<enums::LegacyCoverState>}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, position),
                                                  &encode_float_field,
                                                  &size_float_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_float_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, tilt),
                                                  &encode_float_field,
                                                  &size_float_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_float_field}},
                                                 {5,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, current_operation),
                                                  &encode_enum_field<enums::CoverOperation>,
                                                  &size_enum_field<enums::CoverOperation>,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_enum_field<enums::CoverOperation>}},
                                                 {6,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, device_id),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_FAN
const FieldMeta ListEntitiesFanResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_oscillation),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_speed),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_direction),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_speed_count),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     {.decode_varint = &decode_int32_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesFanResponse::REPEATED_FIELDS[1] = {
    {12, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_preset_modes), &encode_repeated_string_field,
     &size_repeated_string_field}};
const FieldMeta FanStateResponse::FIELDS[8] = {{1,
                                                PROTO_FIELD_OFFSET(FanStateResponse, key),
                                                &encode_fixed32_field,
                                                &size_fixed32_field,
                                                false,
                                                5,
                                                {.decode_32bit = &decode_fixed32_field}},
                                               {2,
                                                PROTO_FIELD_OFFSET(FanStateResponse, state),
                                                &encode_bool_field,
                                                &size_bool_field,
                                                false,
                                                0,
                                                {.decode_varint = &decode_bool_field}},
                                               {3,
                                                PROTO_FIELD_OFFSET(FanStateResponse, oscillating),
                                                &encode_bool_field,
                                                &size_bool_field,
                                                false,
                                                0,
                                                {.decode_varint = &decode_bool_field}},
                                               {4,
                                                PROTO_FIELD_OFFSET(FanStateResponse, speed),
                                                &encode_enum_field<enums::FanSpeed>,
                                                &size_enum_field<enums::FanSpeed>,
                                                false,
                                                0,
                                                {.decode_varint = &decode_enum_field<enums::FanSpeed>}},
                                               {5,
                                                PROTO_FIELD_OFFSET(FanStateResponse, direction),
                                                &encode_enum_field<enums::FanDirection>,
                                                &size_enum_field<enums::FanDirection>,
                                                false,
                                                0,
                                                {.decode_varint = &decode_enum_field<enums::FanDirection>}},
                                               {6,
                                                PROTO_FIELD_OFFSET(FanStateResponse, speed_level),
                                                &encode_int32_field,
                                                &size_int32_field,
                                                false,
                                                0,
                                                {.decode_varint = &decode_int32_field}},
                                               {7,
                                                PROTO_FIELD_OFFSET(FanStateResponse, preset_mode),
                                                &encode_string_field,
                                                &size_string_field,
                                                false,
                                                2,
                                                {.decode_length = &decode_string_field}},
                                               {8,
                                                PROTO_FIELD_OFFSET(FanStateResponse, device_id),
                                                &encode_uint32_field,
                                                &size_uint32_field,
                                                false,
                                                0,
                                                {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_LIGHT
const FieldMeta ListEntitiesLightResponse::FIELDS[14] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_brightness),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_rgb),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_white_value),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_color_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, min_mireds),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, max_mireds),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {14,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {15,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {16,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesLightResponse::REPEATED_FIELDS[2] = {
    {12, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, supported_color_modes),
     &encode_repeated_enum_field<enums::ColorMode>, &size_repeated_enum_field<enums::ColorMode>},
    {11, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, effects), &encode_repeated_string_field,
     &size_repeated_string_field}};
const FieldMeta LightStateResponse::FIELDS[14] = {{1,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, brightness),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {11,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, color_mode),
                                                   &encode_enum_field<enums::ColorMode>,
                                                   &size_enum_field<enums::ColorMode>,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_enum_field<enums::ColorMode>}},
                                                  {10,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, color_brightness),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, red),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {5,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, green),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {6,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, blue),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {7,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, white),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {8,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, color_temperature),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {12,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, cold_white),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {13,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, warm_white),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {9,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, effect),
                                                   &encode_string_field,
                                                   &size_string_field,
                                                   false,
                                                   2,
                                                   {.decode_length = &decode_string_field}},
                                                  {14,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_SENSOR
const FieldMeta ListEntitiesSensorResponse::FIELDS[14] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unit_of_measurement),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, accuracy_decimals),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     {.decode_varint = &decode_int32_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, force_update),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, state_class),
     &encode_enum_field<enums::SensorStateClass>,
     &size_enum_field<enums::SensorStateClass>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::SensorStateClass>}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, legacy_last_reset_type),
     &encode_enum_field<enums::SensorLastResetType>,
     &size_enum_field<enums::SensorLastResetType>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::SensorLastResetType>}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {14,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta SensorStateResponse::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, state),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, missing_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_SWITCH
const FieldMeta ListEntitiesSwitchResponse::FIELDS[10] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta SwitchStateResponse::FIELDS[3] = {{1,
                                                   PROTO_FIELD_OFFSET(SwitchStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SwitchStateResponse, state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SwitchStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_TEXT_SENSOR
const FieldMeta ListEntitiesTextSensorResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta TextSensorStateResponse::FIELDS[4] = {{1,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, key),
                                                       &encode_fixed32_field,
                                                       &size_fixed32_field,
                                                       false,
                                                       5,
                                                       {.decode_32bit = &decode_fixed32_field}},
                                                      {2,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, state),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       {.decode_length = &decode_string_field}},
                                                      {3,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, missing_state),
                                                       &encode_bool_field,
                                                       &size_bool_field,
                                                       false,
                                                       0,
                                                       {.decode_varint = &decode_bool_field}},
                                                      {4,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, device_id),
                                                       &encode_uint32_field,
                                                       &size_uint32_field,
                                                       false,
                                                       0,
                                                       {.decode_varint = &decode_uint32_field}}};
#endif
const FieldMeta SubscribeLogsResponse::FIELDS[3] = {{1,
                                                     PROTO_FIELD_OFFSET(SubscribeLogsResponse, level),
                                                     &encode_enum_field<enums::LogLevel>,
                                                     &size_enum_field<enums::LogLevel>,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_enum_field<enums::LogLevel>}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(SubscribeLogsResponse, message),
                                                     &encode_bytes_field,
                                                     &size_bytes_field,
                                                     false,
                                                     2,
                                                     {.decode_length = &decode_bytes_field}},
                                                    {4,
                                                     PROTO_FIELD_OFFSET(SubscribeLogsResponse, send_failed),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_bool_field}}};
#ifdef USE_API_NOISE
const FieldMeta NoiseEncryptionSetKeyResponse::FIELDS[1] = {{1,
                                                             PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyResponse, success),
                                                             &encode_bool_field,
                                                             &size_bool_field,
                                                             false,
                                                             0,
                                                             {.decode_varint = &decode_bool_field}}};
#endif
const FieldMeta HomeassistantServiceResponse::FIELDS[2] = {{1,
                                                            PROTO_FIELD_OFFSET(HomeassistantServiceResponse, service),
                                                            &encode_string_field,
                                                            &size_string_field,
                                                            false,
                                                            2,
                                                            {.decode_length = &decode_string_field}},
                                                           {5,
                                                            PROTO_FIELD_OFFSET(HomeassistantServiceResponse, is_event),
                                                            &encode_bool_field,
                                                            &size_bool_field,
                                                            false,
                                                            0,
                                                            {.decode_varint = &decode_bool_field}}};
const RepeatedFieldMeta HomeassistantServiceResponse::REPEATED_FIELDS[3] = {
    {2, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data), &encode_repeated_message_field<HomeassistantServiceMap>,
     &size_repeated_message_field<HomeassistantServiceMap>},
    {3, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data_template),
     &encode_repeated_message_field<HomeassistantServiceMap>, &size_repeated_message_field<HomeassistantServiceMap>},
    {4, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, variables),
     &encode_repeated_message_field<HomeassistantServiceMap>, &size_repeated_message_field<HomeassistantServiceMap>}};
const FieldMeta SubscribeHomeAssistantStateResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, entity_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, attribute),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, once),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}}};
const FieldMeta HomeAssistantStateResponse::FIELDS[3] = {{1,
                                                          PROTO_FIELD_OFFSET(HomeAssistantStateResponse, entity_id),
                                                          &encode_string_field,
                                                          &size_string_field,
                                                          false,
                                                          2,
                                                          {.decode_length = &decode_string_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(HomeAssistantStateResponse, state),
                                                          &encode_string_field,
                                                          &size_string_field,
                                                          false,
                                                          2,
                                                          {.decode_length = &decode_string_field}},
                                                         {3,
                                                          PROTO_FIELD_OFFSET(HomeAssistantStateResponse, attribute),
                                                          &encode_string_field,
                                                          &size_string_field,
                                                          false,
                                                          2,
                                                          {.decode_length = &decode_string_field}}};
const FieldMeta GetTimeResponse::FIELDS[1] = {{1,
                                               PROTO_FIELD_OFFSET(GetTimeResponse, epoch_seconds),
                                               &encode_fixed32_field,
                                               &size_fixed32_field,
                                               false,
                                               5,
                                               {.decode_32bit = &decode_fixed32_field}}};
const FieldMeta ListEntitiesServicesResponse::FIELDS[2] = {{1,
                                                            PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, name),
                                                            &encode_string_field,
                                                            &size_string_field,
                                                            false,
                                                            2,
                                                            {.decode_length = &decode_string_field}},
                                                           {2,
                                                            PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, key),
                                                            &encode_fixed32_field,
                                                            &size_fixed32_field,
                                                            false,
                                                            5,
                                                            {.decode_32bit = &decode_fixed32_field}}};
const RepeatedFieldMeta ListEntitiesServicesResponse::REPEATED_FIELDS[1] = {
    {3, PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, args),
     &encode_repeated_message_field<ListEntitiesServicesArgument>,
     &size_repeated_message_field<ListEntitiesServicesArgument>}};
#ifdef USE_CAMERA
const FieldMeta ListEntitiesCameraResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta CameraImageResponse::FIELDS[3] = {{1,
                                                   PROTO_FIELD_OFFSET(CameraImageResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(CameraImageResponse, data),
                                                   &encode_bytes_field,
                                                   &size_bytes_field,
                                                   false,
                                                   2,
                                                   {.decode_length = &decode_bytes_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(CameraImageResponse, done),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}}};
#endif
#ifdef USE_CLIMATE
const FieldMeta ListEntitiesClimateResponse::FIELDS[20] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_two_point_target_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_temperature),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_temperature),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_target_temperature_step),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, legacy_supports_away),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_action),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {18,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {19,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {20,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {21,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_current_temperature_step),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {22,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_humidity),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {23,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_target_humidity),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {24,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_humidity),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {25,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_humidity),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {26,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesClimateResponse::REPEATED_FIELDS[6] = {
    {7, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_modes),
     &encode_repeated_enum_field<enums::ClimateMode>, &size_repeated_enum_field<enums::ClimateMode>},
    {13, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_fan_modes),
     &encode_repeated_enum_field<enums::ClimateFanMode>, &size_repeated_enum_field<enums::ClimateFanMode>},
    {14, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_swing_modes),
     &encode_repeated_enum_field<enums::ClimateSwingMode>, &size_repeated_enum_field<enums::ClimateSwingMode>},
    {15, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_fan_modes), &encode_repeated_string_field,
     &size_repeated_string_field},
    {16, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_presets),
     &encode_repeated_enum_field<enums::ClimatePreset>, &size_repeated_enum_field<enums::ClimatePreset>},
    {17, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_presets), &encode_repeated_string_field,
     &size_repeated_string_field}};
const FieldMeta ClimateStateResponse::FIELDS[16] = {{1,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, key),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_fixed32_field}},
                                                    {2,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, mode),
                                                     &encode_enum_field<enums::ClimateMode>,
                                                     &size_enum_field<enums::ClimateMode>,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateMode>}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, current_temperature),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {4,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {5,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_low),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {6,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_high),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {7,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, unused_legacy_away),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_bool_field}},
                                                    {8,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, action),
                                                     &encode_enum_field<enums::ClimateAction>,
                                                     &size_enum_field<enums::ClimateAction>,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateAction>}},
                                                    {9,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, fan_mode),
                                                     &encode_enum_field<enums::ClimateFanMode>,
                                                     &size_enum_field<enums::ClimateFanMode>,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateFanMode>}},
                                                    {10,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, swing_mode),
                                                     &encode_enum_field<enums::ClimateSwingMode>,
                                                     &size_enum_field<enums::ClimateSwingMode>,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateSwingMode>}},
                                                    {11,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, custom_fan_mode),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     {.decode_length = &decode_string_field}},
                                                    {12,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, preset),
                                                     &encode_enum_field<enums::ClimatePreset>,
                                                     &size_enum_field<enums::ClimatePreset>,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_enum_field<enums::ClimatePreset>}},
                                                    {13,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, custom_preset),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     {.decode_length = &decode_string_field}},
                                                    {14,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, current_humidity),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {15,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_humidity),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {16,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, device_id),
                                                     &encode_uint32_field,
                                                     &size_uint32_field,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_NUMBER
const FieldMeta ListEntitiesNumberResponse::FIELDS[14] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, min_value),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, max_value),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, step),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unit_of_measurement),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, mode),
     &encode_enum_field<enums::NumberMode>,
     &size_enum_field<enums::NumberMode>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::NumberMode>}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {14,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta NumberStateResponse::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, state),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, missing_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_SELECT
const FieldMeta ListEntitiesSelectResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesSelectResponse::REPEATED_FIELDS[1] = {
    {6, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, options), &encode_repeated_string_field,
     &size_repeated_string_field}};
const FieldMeta SelectStateResponse::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, state),
                                                   &encode_string_field,
                                                   &size_string_field,
                                                   false,
                                                   2,
                                                   {.decode_length = &decode_string_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, missing_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_SIREN
const FieldMeta ListEntitiesSirenResponse::FIELDS[10] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_duration),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_volume),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesSirenResponse::REPEATED_FIELDS[1] = {
    {7, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, tones), &encode_repeated_string_field,
     &size_repeated_string_field}};
const FieldMeta SirenStateResponse::FIELDS[3] = {{1,
                                                  PROTO_FIELD_OFFSET(SirenStateResponse, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(SirenStateResponse, state),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(SirenStateResponse, device_id),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_LOCK
const FieldMeta ListEntitiesLockResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, supports_open),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, requires_code),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, code_format),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta LockStateResponse::FIELDS[3] = {{1,
                                                 PROTO_FIELD_OFFSET(LockStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(LockStateResponse, state),
                                                 &encode_enum_field<enums::LockState>,
                                                 &size_enum_field<enums::LockState>,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_enum_field<enums::LockState>}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(LockStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_BUTTON
const FieldMeta ListEntitiesButtonResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_MEDIA_PLAYER
const FieldMeta ListEntitiesMediaPlayerResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supports_pause),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesMediaPlayerResponse::REPEATED_FIELDS[1] = {
    {9, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supported_formats),
     &encode_repeated_message_field<MediaPlayerSupportedFormat>,
     &size_repeated_message_field<MediaPlayerSupportedFormat>}};
const FieldMeta MediaPlayerStateResponse::FIELDS[5] = {{1,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, key),
                                                        &encode_fixed32_field,
                                                        &size_fixed32_field,
                                                        false,
                                                        5,
                                                        {.decode_32bit = &decode_fixed32_field}},
                                                       {2,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, state),
                                                        &encode_enum_field<enums::MediaPlayerState>,
                                                        &size_enum_field<enums::MediaPlayerState>,
                                                        false,
                                                        0,
                                                        {.decode_varint = &decode_enum_field<enums::MediaPlayerState>}},
                                                       {3,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, volume),
                                                        &encode_float_field,
                                                        &size_float_field,
                                                        false,
                                                        5,
                                                        {.decode_32bit = &decode_float_field}},
                                                       {4,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, muted),
                                                        &encode_bool_field,
                                                        &size_bool_field,
                                                        false,
                                                        0,
                                                        {.decode_varint = &decode_bool_field}},
                                                       {5,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, device_id),
                                                        &encode_uint32_field,
                                                        &size_uint32_field,
                                                        false,
                                                        0,
                                                        {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_BLUETOOTH_PROXY
const FieldMeta BluetoothLEAdvertisementResponse::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, name),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     {.decode_length = &decode_bytes_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, rssi),
     &encode_sint32_field,
     &size_sint32_field,
     false,
     0,
     {.decode_varint = &decode_sint32_field}},
    {7,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address_type),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothLEAdvertisementResponse::REPEATED_FIELDS[3] = {
    {4, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_uuids), &encode_repeated_string_field,
     &size_repeated_string_field},
    {5, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_data),
     &encode_repeated_message_field<BluetoothServiceData>, &size_repeated_message_field<BluetoothServiceData>},
    {6, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, manufacturer_data),
     &encode_repeated_message_field<BluetoothServiceData>, &size_repeated_message_field<BluetoothServiceData>}};
const RepeatedFieldMeta BluetoothLERawAdvertisementsResponse::REPEATED_FIELDS[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisementsResponse, advertisements),
     &encode_repeated_message_field<BluetoothLERawAdvertisement>,
     &size_repeated_message_field<BluetoothLERawAdvertisement>}};
const FieldMeta BluetoothDeviceConnectionResponse::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, connected),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, mtu),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     {.decode_varint = &decode_int32_field}}};
const FieldMeta BluetoothGATTGetServicesResponse::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}}};
const RepeatedFieldMeta BluetoothGATTGetServicesResponse::REPEATED_FIELDS[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, services),
     &encode_repeated_message_field<BluetoothGATTService>, &size_repeated_message_field<BluetoothGATTService>}};
const FieldMeta BluetoothGATTGetServicesDoneResponse::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesDoneResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}}};
const FieldMeta BluetoothGATTReadResponse::FIELDS[3] = {{1,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, address),
                                                         &encode_uint64_field,
                                                         &size_uint64_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_uint64_field}},
                                                        {2,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, handle),
                                                         &encode_uint32_field,
                                                         &size_uint32_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_uint32_field}},
                                                        {3,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, data),
                                                         &encode_bytes_field,
                                                         &size_bytes_field,
                                                         false,
                                                         2,
                                                         {.decode_length = &decode_bytes_field}}};
const FieldMeta BluetoothGATTNotifyDataResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, handle),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, data),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     {.decode_length = &decode_bytes_field}}};
const FieldMeta BluetoothConnectionsFreeResponse::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, free),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, limit),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothConnectionsFreeResponse::REPEATED_FIELDS[1] = {
    {3, PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, allocated), &encode_repeated_uint64_field,
     &size_repeated_uint64_field}};
const FieldMeta BluetoothGATTErrorResponse::FIELDS[3] = {{1,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, address),
                                                          &encode_uint64_field,
                                                          &size_uint64_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_uint64_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, handle),
                                                          &encode_uint32_field,
                                                          &size_uint32_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_uint32_field}},
                                                         {3,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, error),
                                                          &encode_int32_field,
                                                          &size_int32_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_int32_field}}};
const FieldMeta BluetoothGATTWriteResponse::FIELDS[2] = {{1,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, address),
                                                          &encode_uint64_field,
                                                          &size_uint64_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_uint64_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, handle),
                                                          &encode_uint32_field,
                                                          &size_uint32_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_uint32_field}}};
const FieldMeta BluetoothGATTNotifyResponse::FIELDS[2] = {{1,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, address),
                                                           &encode_uint64_field,
                                                           &size_uint64_field,
                                                           false,
                                                           0,
                                                           {.decode_varint = &decode_uint64_field}},
                                                          {2,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, handle),
                                                           &encode_uint32_field,
                                                           &size_uint32_field,
                                                           false,
                                                           0,
                                                           {.decode_varint = &decode_uint32_field}}};
const FieldMeta BluetoothDevicePairingResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, paired),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     {.decode_varint = &decode_int32_field}}};
const FieldMeta BluetoothDeviceUnpairingResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, success),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     {.decode_varint = &decode_int32_field}}};
const FieldMeta BluetoothDeviceClearCacheResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, success),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     {.decode_varint = &decode_int32_field}}};
const FieldMeta BluetoothScannerStateResponse::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, state),
     &encode_enum_field<enums::BluetoothScannerState>,
     &size_enum_field<enums::BluetoothScannerState>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::BluetoothScannerState>}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, mode),
     &encode_enum_field<enums::BluetoothScannerMode>,
     &size_enum_field<enums::BluetoothScannerMode>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::BluetoothScannerMode>}}};
#endif
#ifdef USE_VOICE_ASSISTANT
const FieldMeta VoiceAssistantResponse::FIELDS[2] = {{1,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantResponse, port),
                                                      &encode_uint32_field,
                                                      &size_uint32_field,
                                                      false,
                                                      0,
                                                      {.decode_varint = &decode_uint32_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantResponse, error),
                                                      &encode_bool_field,
                                                      &size_bool_field,
                                                      false,
                                                      0,
                                                      {.decode_varint = &decode_bool_field}}};
const FieldMeta VoiceAssistantEventResponse::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, event_type),
     &encode_enum_field<enums::VoiceAssistantEvent>,
     &size_enum_field<enums::VoiceAssistantEvent>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::VoiceAssistantEvent>}}};
const RepeatedFieldMeta VoiceAssistantEventResponse::REPEATED_FIELDS[1] = {
    {2, PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, data), &encode_repeated_message_field<VoiceAssistantEventData>,
     &size_repeated_message_field<VoiceAssistantEventData>}};
const FieldMeta VoiceAssistantTimerEventResponse::FIELDS[6] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, event_type),
     &encode_enum_field<enums::VoiceAssistantTimerEvent>,
     &size_enum_field<enums::VoiceAssistantTimerEvent>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::VoiceAssistantTimerEvent>}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, timer_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, total_seconds),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {5,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, seconds_left),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {6,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, is_active),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}}};
const FieldMeta VoiceAssistantConfigurationResponse::FIELDS[1] = {
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, max_active_wake_words),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta VoiceAssistantConfigurationResponse::REPEATED_FIELDS[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, available_wake_words),
     &encode_repeated_message_field<VoiceAssistantWakeWord>, &size_repeated_message_field<VoiceAssistantWakeWord>},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, active_wake_words), &encode_repeated_string_field,
     &size_repeated_string_field}};
#endif
#ifdef USE_ALARM_CONTROL_PANEL
const FieldMeta ListEntitiesAlarmControlPanelResponse::FIELDS[11] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, supported_features),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code_to_arm),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta AlarmControlPanelStateResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, state),
     &encode_enum_field<enums::AlarmControlPanelState>,
     &size_enum_field<enums::AlarmControlPanelState>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::AlarmControlPanelState>}},
    {3,
     PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_TEXT
const FieldMeta ListEntitiesTextResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, min_length),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, max_length),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, pattern),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, mode),
     &encode_enum_field<enums::TextMode>,
     &size_enum_field<enums::TextMode>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::TextMode>}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta TextStateResponse::FIELDS[4] = {{1,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, state),
                                                 &encode_string_field,
                                                 &size_string_field,
                                                 false,
                                                 2,
                                                 {.decode_length = &decode_string_field}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, missing_state),
                                                 &encode_bool_field,
                                                 &size_bool_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_bool_field}},
                                                {4,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_DATETIME_DATE
const FieldMeta ListEntitiesDateResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta DateStateResponse::FIELDS[6] = {{1,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, missing_state),
                                                 &encode_bool_field,
                                                 &size_bool_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_bool_field}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, year),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {4,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, month),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {5,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, day),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {6,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_DATETIME_TIME
const FieldMeta ListEntitiesTimeResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta TimeStateResponse::FIELDS[6] = {{1,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, missing_state),
                                                 &encode_bool_field,
                                                 &size_bool_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_bool_field}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, hour),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {4,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, minute),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {5,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, second),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {6,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_EVENT
const FieldMeta ListEntitiesEventResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesEventResponse::REPEATED_FIELDS[1] = {
    {9, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, event_types), &encode_repeated_string_field,
     &size_repeated_string_field}};
const FieldMeta EventResponse::FIELDS[3] = {{1,
                                             PROTO_FIELD_OFFSET(EventResponse, key),
                                             &encode_fixed32_field,
                                             &size_fixed32_field,
                                             false,
                                             5,
                                             {.decode_32bit = &decode_fixed32_field}},
                                            {2,
                                             PROTO_FIELD_OFFSET(EventResponse, event_type),
                                             &encode_string_field,
                                             &size_string_field,
                                             false,
                                             2,
                                             {.decode_length = &decode_string_field}},
                                            {3,
                                             PROTO_FIELD_OFFSET(EventResponse, device_id),
                                             &encode_uint32_field,
                                             &size_uint32_field,
                                             false,
                                             0,
                                             {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_VALVE
const FieldMeta ListEntitiesValveResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_position),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_stop),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta ValveStateResponse::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, position),
                                                  &encode_float_field,
                                                  &size_float_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_float_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, current_operation),
                                                  &encode_enum_field<enums::ValveOperation>,
                                                  &size_enum_field<enums::ValveOperation>,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_enum_field<enums::ValveOperation>}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, device_id),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_DATETIME_DATETIME
const FieldMeta ListEntitiesDateTimeResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta DateTimeStateResponse::FIELDS[4] = {{1,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, key),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_fixed32_field}},
                                                    {2,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, missing_state),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_bool_field}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, epoch_seconds),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_fixed32_field}},
                                                    {4,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, device_id),
                                                     &encode_uint32_field,
                                                     &size_uint32_field,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_uint32_field}}};
#endif
#ifdef USE_UPDATE
const FieldMeta ListEntitiesUpdateResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta UpdateStateResponse::FIELDS[11] = {{1,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, missing_state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {3,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, in_progress),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {4,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, has_progress),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {5,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, progress),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {6,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, current_version),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}},
                                                   {7,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, latest_version),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}},
                                                   {8,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, title),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}},
                                                   {9,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, release_summary),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}},
                                                   {10,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, release_url),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}},
                                                   {11,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, device_id),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_uint32_field}}};
#endif

}  // namespace api
}  // namespace esphome
