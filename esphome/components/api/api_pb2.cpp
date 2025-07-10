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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool HelloRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void HelloRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void HelloRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ConnectRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ConnectRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool AreaInfo::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void AreaInfo::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void AreaInfo::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool DeviceInfo::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool DeviceInfo::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void DeviceInfo::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void DeviceInfo::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool CoverCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void CoverCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void CoverCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool FanCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool FanCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void FanCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void FanCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool LightCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool LightCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void LightCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void LightCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SwitchCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SwitchCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SwitchCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SubscribeLogsRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SubscribeLogsRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void NoiseEncryptionSetKeyRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void NoiseEncryptionSetKeyRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void HomeassistantServiceMap::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void HomeassistantServiceMap::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ListEntitiesServicesArgument::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ListEntitiesServicesArgument::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ListEntitiesServicesArgument::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ExecuteServiceArgument::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ExecuteServiceArgument::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ExecuteServiceArgument::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ExecuteServiceArgument::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool ExecuteServiceRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ExecuteServiceRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ExecuteServiceRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void ExecuteServiceRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void CameraImageRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void CameraImageRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ClimateCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ClimateCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ClimateCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ClimateCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void NumberCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void NumberCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SelectCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SelectCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SelectCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SirenCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool SirenCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SirenCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SirenCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool LockCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool LockCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void LockCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void LockCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ButtonCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ButtonCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
#ifdef USE_MEDIA_PLAYER
bool MediaPlayerSupportedFormat::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool MediaPlayerSupportedFormat::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void MediaPlayerSupportedFormat::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void MediaPlayerSupportedFormat::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool MediaPlayerCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool MediaPlayerCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void MediaPlayerCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void MediaPlayerCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
#ifdef USE_BLUETOOTH_PROXY
bool SubscribeBluetoothLEAdvertisementsRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SubscribeBluetoothLEAdvertisementsRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SubscribeBluetoothLEAdvertisementsRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothServiceData::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothServiceData::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothServiceData::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothServiceData::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothLERawAdvertisement::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothLERawAdvertisement::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothLERawAdvertisement::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothLERawAdvertisementsResponse::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return false;  // No length-delimited fields
}
void BluetoothLERawAdvertisementsResponse::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, nullptr, 0, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothLERawAdvertisementsResponse::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, nullptr, 0, REPEATED_FIELDS, REPEATED_COUNT);
}
bool BluetoothDeviceRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothDeviceRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothDeviceRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTGetServicesRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTGetServicesRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTDescriptor::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTDescriptor::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothGATTDescriptor::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool BluetoothGATTCharacteristic::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothGATTCharacteristic::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTCharacteristic::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothGATTCharacteristic::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
bool BluetoothGATTService::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothGATTService::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTService::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void BluetoothGATTService::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTReadRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTReadRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothGATTWriteRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTWriteRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTWriteRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTReadDescriptorRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTReadDescriptorRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTReadDescriptorRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTWriteDescriptorRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool BluetoothGATTWriteDescriptorRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTWriteDescriptorRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTWriteDescriptorRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool BluetoothGATTNotifyRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothGATTNotifyRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothGATTNotifyRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void BluetoothScannerSetModeRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void BluetoothScannerSetModeRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif
#ifdef USE_VOICE_ASSISTANT
bool SubscribeVoiceAssistantRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void SubscribeVoiceAssistantRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void SubscribeVoiceAssistantRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool VoiceAssistantAudioSettings::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool VoiceAssistantAudioSettings::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantAudioSettings::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantAudioSettings::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool VoiceAssistantRequest::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool VoiceAssistantRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantEventData::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantEventData::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool VoiceAssistantAudio::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantAudio::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantAudio::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool VoiceAssistantAnnounceRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantAnnounceRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantAnnounceRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool VoiceAssistantAnnounceFinished::decode_varint(uint32_t field_id, ProtoVarInt value) {
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantAnnounceFinished::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void VoiceAssistantAnnounceFinished::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
bool VoiceAssistantWakeWord::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void VoiceAssistantWakeWord::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
}
void VoiceAssistantWakeWord::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, REPEATED_FIELDS, REPEATED_COUNT);
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
  return false;  // No length-delimited fields
}
void VoiceAssistantSetConfiguration::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, nullptr, 0, REPEATED_FIELDS, REPEATED_COUNT);
}
void VoiceAssistantSetConfiguration::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, nullptr, 0, REPEATED_FIELDS, REPEATED_COUNT);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool AlarmControlPanelCommandRequest::decode_length(uint32_t field_id, ProtoLengthDelimited value) {
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool AlarmControlPanelCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void AlarmControlPanelCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void AlarmControlPanelCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_length_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool TextCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void TextCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void TextCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool DateCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void DateCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void DateCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool TimeCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void TimeCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void TimeCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool ValveCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void ValveCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void ValveCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void DateTimeCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void DateTimeCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
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
  return decode_varint_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
bool UpdateCommandRequest::decode_32bit(uint32_t field_id, Proto32Bit value) {
  return decode_32bit_metadata(field_id, value, FIELDS, FIELD_COUNT);
}
void UpdateCommandRequest::encode(ProtoWriteBuffer buffer) const {
  encode_from_metadata(buffer, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
void UpdateCommandRequest::calculate_size(uint32_t &total_size) const {
  calculate_size_from_metadata(total_size, this, FIELDS, FIELD_COUNT, nullptr, 0);
}
#endif

// Metadata definitions for classes using metadata approach
const FieldMeta HelloRequest::FIELDS[3] = {{1,
                                            PROTO_FIELD_OFFSET(HelloRequest, client_info),
                                            &encode_string_field,
                                            &size_string_field,
                                            false,
                                            2,
                                            {.decode_length = &decode_string_field}},
                                           {2,
                                            PROTO_FIELD_OFFSET(HelloRequest, api_version_major),
                                            &encode_uint32_field,
                                            &size_uint32_field,
                                            false,
                                            0,
                                            {.decode_varint = &decode_uint32_field}},
                                           {3,
                                            PROTO_FIELD_OFFSET(HelloRequest, api_version_minor),
                                            &encode_uint32_field,
                                            &size_uint32_field,
                                            false,
                                            0,
                                            {.decode_varint = &decode_uint32_field}}};
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
const FieldMeta ConnectRequest::FIELDS[1] = {{1,
                                              PROTO_FIELD_OFFSET(ConnectRequest, password),
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
const FieldMeta AreaInfo::FIELDS[2] = {{1,
                                        PROTO_FIELD_OFFSET(AreaInfo, area_id),
                                        &encode_uint32_field,
                                        &size_uint32_field,
                                        false,
                                        0,
                                        {.decode_varint = &decode_uint32_field}},
                                       {2,
                                        PROTO_FIELD_OFFSET(AreaInfo, name),
                                        &encode_string_field,
                                        &size_string_field,
                                        false,
                                        2,
                                        {.decode_length = &decode_string_field}}};
const FieldMeta DeviceInfo::FIELDS[3] = {{1,
                                          PROTO_FIELD_OFFSET(DeviceInfo, device_id),
                                          &encode_uint32_field,
                                          &size_uint32_field,
                                          false,
                                          0,
                                          {.decode_varint = &decode_uint32_field}},
                                         {2,
                                          PROTO_FIELD_OFFSET(DeviceInfo, name),
                                          &encode_string_field,
                                          &size_string_field,
                                          false,
                                          2,
                                          {.decode_length = &decode_string_field}},
                                         {3,
                                          PROTO_FIELD_OFFSET(DeviceInfo, area_id),
                                          &encode_uint32_field,
                                          &size_uint32_field,
                                          false,
                                          0,
                                          {.decode_varint = &decode_uint32_field}}};
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
const FieldMeta CoverCommandRequest::FIELDS[8] = {{1,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, has_legacy_command),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, legacy_command),
                                                   &encode_enum_field<enums::LegacyCoverCommand>,
                                                   &size_enum_field<enums::LegacyCoverCommand>,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_enum_field<enums::LegacyCoverCommand>}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, has_position),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {5,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, position),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {6,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, has_tilt),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {7,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, tilt),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {8,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, stop),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}}};
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
const FieldMeta FanCommandRequest::FIELDS[13] = {{1,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_state),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, state),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_speed),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {5,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, speed),
                                                  &encode_enum_field<enums::FanSpeed>,
                                                  &size_enum_field<enums::FanSpeed>,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_enum_field<enums::FanSpeed>}},
                                                 {6,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_oscillating),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {7,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, oscillating),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {8,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_direction),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {9,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, direction),
                                                  &encode_enum_field<enums::FanDirection>,
                                                  &size_enum_field<enums::FanDirection>,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_enum_field<enums::FanDirection>}},
                                                 {10,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_speed_level),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {11,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, speed_level),
                                                  &encode_int32_field,
                                                  &size_int32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_int32_field}},
                                                 {12,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_preset_mode),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {13,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, preset_mode),
                                                  &encode_string_field,
                                                  &size_string_field,
                                                  false,
                                                  2,
                                                  {.decode_length = &decode_string_field}}};
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
const FieldMeta LightCommandRequest::FIELDS[27] = {{1,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {3,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {4,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_brightness),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {5,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, brightness),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {22,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_color_mode),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {23,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, color_mode),
                                                    &encode_enum_field<enums::ColorMode>,
                                                    &size_enum_field<enums::ColorMode>,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_enum_field<enums::ColorMode>}},
                                                   {20,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_color_brightness),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {21,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, color_brightness),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {6,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_rgb),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {7,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, red),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {8,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, green),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {9,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, blue),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {10,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_white),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {11,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, white),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {12,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_color_temperature),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {13,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, color_temperature),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {24,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_cold_white),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {25,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, cold_white),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {26,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_warm_white),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {27,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, warm_white),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {14,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_transition_length),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {15,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, transition_length),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_uint32_field}},
                                                   {16,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_flash_length),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {17,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, flash_length),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_uint32_field}},
                                                   {18,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_effect),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {19,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, effect),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}}};
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
const FieldMeta SwitchCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(SwitchCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(SwitchCommandRequest, state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}}};
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
const FieldMeta SubscribeLogsRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(SubscribeLogsRequest, level),
                                                    &encode_enum_field<enums::LogLevel>,
                                                    &size_enum_field<enums::LogLevel>,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_enum_field<enums::LogLevel>}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(SubscribeLogsRequest, dump_config),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_bool_field}}};
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
const FieldMeta NoiseEncryptionSetKeyRequest::FIELDS[1] = {{1,
                                                            PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyRequest, key),
                                                            &encode_bytes_field,
                                                            &size_bytes_field,
                                                            false,
                                                            2,
                                                            {.decode_length = &decode_bytes_field}}};
const FieldMeta NoiseEncryptionSetKeyResponse::FIELDS[1] = {{1,
                                                             PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyResponse, success),
                                                             &encode_bool_field,
                                                             &size_bool_field,
                                                             false,
                                                             0,
                                                             {.decode_varint = &decode_bool_field}}};
#endif
const FieldMeta HomeassistantServiceMap::FIELDS[2] = {{1,
                                                       PROTO_FIELD_OFFSET(HomeassistantServiceMap, key),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       {.decode_length = &decode_string_field}},
                                                      {2,
                                                       PROTO_FIELD_OFFSET(HomeassistantServiceMap, value),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       {.decode_length = &decode_string_field}}};
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
const FieldMeta ListEntitiesServicesArgument::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, type),
     &encode_enum_field<enums::ServiceArgType>,
     &size_enum_field<enums::ServiceArgType>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::ServiceArgType>}}};
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
const FieldMeta ExecuteServiceArgument::FIELDS[5] = {{1,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_),
                                                      &encode_bool_field,
                                                      &size_bool_field,
                                                      false,
                                                      0,
                                                      {.decode_varint = &decode_bool_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, legacy_int),
                                                      &encode_int32_field,
                                                      &size_int32_field,
                                                      false,
                                                      0,
                                                      {.decode_varint = &decode_int32_field}},
                                                     {3,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_),
                                                      &encode_float_field,
                                                      &size_float_field,
                                                      false,
                                                      5,
                                                      {.decode_32bit = &decode_float_field}},
                                                     {4,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_),
                                                      &encode_string_field,
                                                      &size_string_field,
                                                      false,
                                                      2,
                                                      {.decode_length = &decode_string_field}},
                                                     {5,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_),
                                                      &encode_sint32_field,
                                                      &size_sint32_field,
                                                      false,
                                                      0,
                                                      {.decode_varint = &decode_sint32_field}}};
const RepeatedFieldMeta ExecuteServiceArgument::REPEATED_FIELDS[4] = {
    {6, PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_array), &encode_repeated_bool_field, &size_repeated_bool_field},
    {7, PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_array), &encode_repeated_sint32_field,
     &size_repeated_sint32_field},
    {8, PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_array), &encode_repeated_float_field,
     &size_repeated_float_field},
    {9, PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_array), &encode_repeated_string_field,
     &size_repeated_string_field}};
const FieldMeta ExecuteServiceRequest::FIELDS[1] = {{1,
                                                     PROTO_FIELD_OFFSET(ExecuteServiceRequest, key),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     {.decode_32bit = &decode_fixed32_field}}};
const RepeatedFieldMeta ExecuteServiceRequest::REPEATED_FIELDS[1] = {
    {2, PROTO_FIELD_OFFSET(ExecuteServiceRequest, args), &encode_repeated_message_field<ExecuteServiceArgument>,
     &size_repeated_message_field<ExecuteServiceArgument>}};
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
const FieldMeta CameraImageRequest::FIELDS[2] = {{1,
                                                  PROTO_FIELD_OFFSET(CameraImageRequest, single),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(CameraImageRequest, stream),
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
const FieldMeta ClimateCommandRequest::FIELDS[23] = {
    {1,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, mode),
     &encode_enum_field<enums::ClimateMode>,
     &size_enum_field<enums::ClimateMode>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::ClimateMode>}},
    {4,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {5,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {6,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_low),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_low),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {8,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_high),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_high),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {10,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_has_legacy_away),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_legacy_away),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {12,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_fan_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {13,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, fan_mode),
     &encode_enum_field<enums::ClimateFanMode>,
     &size_enum_field<enums::ClimateFanMode>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::ClimateFanMode>}},
    {14,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_swing_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {15,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, swing_mode),
     &encode_enum_field<enums::ClimateSwingMode>,
     &size_enum_field<enums::ClimateSwingMode>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::ClimateSwingMode>}},
    {16,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_fan_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {17,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_fan_mode),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {18,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_preset),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {19,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, preset),
     &encode_enum_field<enums::ClimatePreset>,
     &size_enum_field<enums::ClimatePreset>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::ClimatePreset>}},
    {20,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_preset),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {21,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_preset),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {22,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_humidity),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {23,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_humidity),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}}};
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
const FieldMeta NumberCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(NumberCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(NumberCommandRequest, state),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_float_field}}};
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
const FieldMeta SelectCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(SelectCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(SelectCommandRequest, state),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}}};
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
const FieldMeta SirenCommandRequest::FIELDS[9] = {{1,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_tone),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {5,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, tone),
                                                   &encode_string_field,
                                                   &size_string_field,
                                                   false,
                                                   2,
                                                   {.decode_length = &decode_string_field}},
                                                  {6,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_duration),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {7,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, duration),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_uint32_field}},
                                                  {8,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_volume),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {9,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, volume),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}}};
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
const FieldMeta LockCommandRequest::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, command),
                                                  &encode_enum_field<enums::LockCommand>,
                                                  &size_enum_field<enums::LockCommand>,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_enum_field<enums::LockCommand>}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, has_code),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, code),
                                                  &encode_string_field,
                                                  &size_string_field,
                                                  false,
                                                  2,
                                                  {.decode_length = &decode_string_field}}};
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
const FieldMeta ButtonCommandRequest::FIELDS[1] = {{1,
                                                    PROTO_FIELD_OFFSET(ButtonCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_fixed32_field}}};
#endif
#ifdef USE_MEDIA_PLAYER
const FieldMeta MediaPlayerSupportedFormat::FIELDS[5] = {
    {1,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, format),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_rate),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, num_channels),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {4,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, purpose),
     &encode_enum_field<enums::MediaPlayerFormatPurpose>,
     &size_enum_field<enums::MediaPlayerFormatPurpose>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::MediaPlayerFormatPurpose>}},
    {5,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_bytes),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
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
const FieldMeta MediaPlayerCommandRequest::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_command),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, command),
     &encode_enum_field<enums::MediaPlayerCommand>,
     &size_enum_field<enums::MediaPlayerCommand>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::MediaPlayerCommand>}},
    {4,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_volume),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {5,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, volume),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}},
    {6,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_media_url),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, media_url),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {8,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_announcement),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, announcement),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}}};
#endif
#ifdef USE_BLUETOOTH_PROXY
const FieldMeta SubscribeBluetoothLEAdvertisementsRequest::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(SubscribeBluetoothLEAdvertisementsRequest, flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta BluetoothServiceData::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(BluetoothServiceData, uuid),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_string_field}},
                                                   {3,
                                                    PROTO_FIELD_OFFSET(BluetoothServiceData, data),
                                                    &encode_bytes_field,
                                                    &size_bytes_field,
                                                    false,
                                                    2,
                                                    {.decode_length = &decode_bytes_field}}};
const RepeatedFieldMeta BluetoothServiceData::REPEATED_FIELDS[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothServiceData, legacy_data), &encode_repeated_uint32_field,
     &size_repeated_uint32_field}};
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
const FieldMeta BluetoothLERawAdvertisement::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, rssi),
     &encode_sint32_field,
     &size_sint32_field,
     false,
     0,
     {.decode_varint = &decode_sint32_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address_type),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, data),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     {.decode_length = &decode_bytes_field}}};
const RepeatedFieldMeta BluetoothLERawAdvertisementsResponse::REPEATED_FIELDS[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisementsResponse, advertisements),
     &encode_repeated_message_field<BluetoothLERawAdvertisement>,
     &size_repeated_message_field<BluetoothLERawAdvertisement>}};
const FieldMeta BluetoothDeviceRequest::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, request_type),
     &encode_enum_field<enums::BluetoothDeviceRequestType>,
     &size_enum_field<enums::BluetoothDeviceRequestType>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::BluetoothDeviceRequestType>}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, has_address_type),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address_type),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
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
const FieldMeta BluetoothGATTGetServicesRequest::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}}};
const FieldMeta BluetoothGATTDescriptor::FIELDS[1] = {{2,
                                                       PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, handle),
                                                       &encode_uint32_field,
                                                       &size_uint32_field,
                                                       false,
                                                       0,
                                                       {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothGATTDescriptor::REPEATED_FIELDS[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, uuid), &encode_repeated_uint64_field, &size_repeated_uint64_field}};
const FieldMeta BluetoothGATTCharacteristic::FIELDS[2] = {{2,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, handle),
                                                           &encode_uint32_field,
                                                           &size_uint32_field,
                                                           false,
                                                           0,
                                                           {.decode_varint = &decode_uint32_field}},
                                                          {3,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, properties),
                                                           &encode_uint32_field,
                                                           &size_uint32_field,
                                                           false,
                                                           0,
                                                           {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothGATTCharacteristic::REPEATED_FIELDS[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, uuid), &encode_repeated_uint64_field,
     &size_repeated_uint64_field},
    {4, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, descriptors),
     &encode_repeated_message_field<BluetoothGATTDescriptor>, &size_repeated_message_field<BluetoothGATTDescriptor>}};
const FieldMeta BluetoothGATTService::FIELDS[1] = {{2,
                                                    PROTO_FIELD_OFFSET(BluetoothGATTService, handle),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothGATTService::REPEATED_FIELDS[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTService, uuid), &encode_repeated_uint64_field, &size_repeated_uint64_field},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTService, characteristics),
     &encode_repeated_message_field<BluetoothGATTCharacteristic>,
     &size_repeated_message_field<BluetoothGATTCharacteristic>}};
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
const FieldMeta BluetoothGATTReadRequest::FIELDS[2] = {{1,
                                                        PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, address),
                                                        &encode_uint64_field,
                                                        &size_uint64_field,
                                                        false,
                                                        0,
                                                        {.decode_varint = &decode_uint64_field}},
                                                       {2,
                                                        PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, handle),
                                                        &encode_uint32_field,
                                                        &size_uint32_field,
                                                        false,
                                                        0,
                                                        {.decode_varint = &decode_uint32_field}}};
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
const FieldMeta BluetoothGATTWriteRequest::FIELDS[4] = {{1,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, address),
                                                         &encode_uint64_field,
                                                         &size_uint64_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_uint64_field}},
                                                        {2,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, handle),
                                                         &encode_uint32_field,
                                                         &size_uint32_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_uint32_field}},
                                                        {3,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, response),
                                                         &encode_bool_field,
                                                         &size_bool_field,
                                                         false,
                                                         0,
                                                         {.decode_varint = &decode_bool_field}},
                                                        {4,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, data),
                                                         &encode_bytes_field,
                                                         &size_bytes_field,
                                                         false,
                                                         2,
                                                         {.decode_length = &decode_bytes_field}}};
const FieldMeta BluetoothGATTReadDescriptorRequest::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, handle),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta BluetoothGATTWriteDescriptorRequest::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, handle),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, data),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     {.decode_length = &decode_bytes_field}}};
const FieldMeta BluetoothGATTNotifyRequest::FIELDS[3] = {{1,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, address),
                                                          &encode_uint64_field,
                                                          &size_uint64_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_uint64_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, handle),
                                                          &encode_uint32_field,
                                                          &size_uint32_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_uint32_field}},
                                                         {3,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, enable),
                                                          &encode_bool_field,
                                                          &size_bool_field,
                                                          false,
                                                          0,
                                                          {.decode_varint = &decode_bool_field}}};
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
const FieldMeta BluetoothScannerSetModeRequest::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothScannerSetModeRequest, mode),
     &encode_enum_field<enums::BluetoothScannerMode>,
     &size_enum_field<enums::BluetoothScannerMode>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::BluetoothScannerMode>}}};
#endif
#ifdef USE_VOICE_ASSISTANT
const FieldMeta SubscribeVoiceAssistantRequest::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, subscribe),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}},
    {2,
     PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}}};
const FieldMeta VoiceAssistantAudioSettings::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, noise_suppression_level),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, auto_gain),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, volume_multiplier),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     {.decode_32bit = &decode_float_field}}};
const FieldMeta VoiceAssistantRequest::FIELDS[4] = {{1,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, start),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_bool_field}},
                                                    {2,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, conversation_id),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     {.decode_length = &decode_string_field}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, flags),
                                                     &encode_uint32_field,
                                                     &size_uint32_field,
                                                     false,
                                                     0,
                                                     {.decode_varint = &decode_uint32_field}},
                                                    {5,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, wake_word_phrase),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     {.decode_length = &decode_string_field}}};
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
const FieldMeta VoiceAssistantEventData::FIELDS[2] = {{1,
                                                       PROTO_FIELD_OFFSET(VoiceAssistantEventData, name),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       {.decode_length = &decode_string_field}},
                                                      {2,
                                                       PROTO_FIELD_OFFSET(VoiceAssistantEventData, value),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       {.decode_length = &decode_string_field}}};
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
const FieldMeta VoiceAssistantAudio::FIELDS[2] = {{1,
                                                   PROTO_FIELD_OFFSET(VoiceAssistantAudio, data),
                                                   &encode_bytes_field,
                                                   &size_bytes_field,
                                                   false,
                                                   2,
                                                   {.decode_length = &decode_bytes_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(VoiceAssistantAudio, end),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}}};
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
const FieldMeta VoiceAssistantAnnounceRequest::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, media_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, text),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, preannounce_media_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, start_conversation),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}}};
const FieldMeta VoiceAssistantAnnounceFinished::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceFinished, success),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     {.decode_varint = &decode_bool_field}}};
const FieldMeta VoiceAssistantWakeWord::FIELDS[2] = {{1,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, id),
                                                      &encode_string_field,
                                                      &size_string_field,
                                                      false,
                                                      2,
                                                      {.decode_length = &decode_string_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, wake_word),
                                                      &encode_string_field,
                                                      &size_string_field,
                                                      false,
                                                      2,
                                                      {.decode_length = &decode_string_field}}};
const RepeatedFieldMeta VoiceAssistantWakeWord::REPEATED_FIELDS[1] = {
    {3, PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, trained_languages), &encode_repeated_string_field,
     &size_repeated_string_field}};
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
const RepeatedFieldMeta VoiceAssistantSetConfiguration::REPEATED_FIELDS[1] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantSetConfiguration, active_wake_words), &encode_repeated_string_field,
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
const FieldMeta AlarmControlPanelCommandRequest::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, command),
     &encode_enum_field<enums::AlarmControlPanelStateCommand>,
     &size_enum_field<enums::AlarmControlPanelStateCommand>,
     false,
     0,
     {.decode_varint = &decode_enum_field<enums::AlarmControlPanelStateCommand>}},
    {3,
     PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, code),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     {.decode_length = &decode_string_field}}};
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
const FieldMeta TextCommandRequest::FIELDS[2] = {{1,
                                                  PROTO_FIELD_OFFSET(TextCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(TextCommandRequest, state),
                                                  &encode_string_field,
                                                  &size_string_field,
                                                  false,
                                                  2,
                                                  {.decode_length = &decode_string_field}}};
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
const FieldMeta DateCommandRequest::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, year),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, month),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, day),
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
const FieldMeta TimeCommandRequest::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, hour),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, minute),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, second),
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
const FieldMeta ValveCommandRequest::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, has_position),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, position),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, stop),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   {.decode_varint = &decode_bool_field}}};
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
const FieldMeta DateTimeCommandRequest::FIELDS[2] = {{1,
                                                      PROTO_FIELD_OFFSET(DateTimeCommandRequest, key),
                                                      &encode_fixed32_field,
                                                      &size_fixed32_field,
                                                      false,
                                                      5,
                                                      {.decode_32bit = &decode_fixed32_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(DateTimeCommandRequest, epoch_seconds),
                                                      &encode_fixed32_field,
                                                      &size_fixed32_field,
                                                      false,
                                                      5,
                                                      {.decode_32bit = &decode_fixed32_field}}};
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
const FieldMeta UpdateCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(UpdateCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(UpdateCommandRequest, command),
                                                    &encode_enum_field<enums::UpdateCommand>,
                                                    &size_enum_field<enums::UpdateCommand>,
                                                    false,
                                                    0,
                                                    {.decode_varint = &decode_enum_field<enums::UpdateCommand>}}};
#endif

}  // namespace api
}  // namespace esphome
