// This file was automatically generated with a tool.
// See script/api_protobuf/api_protobuf.py
#include "api_pb2.h"
#include "api_pb2_size.h"
#include "proto_templates.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace api {

#ifdef USE_BINARY_SENSOR
#endif
#ifdef USE_COVER
#endif
#ifdef USE_FAN
#endif
#ifdef USE_LIGHT
#endif
#ifdef USE_SENSOR
#endif
#ifdef USE_SWITCH
#endif
#ifdef USE_TEXT_SENSOR
#endif
#ifdef USE_API_NOISE
#endif
#ifdef USE_CAMERA
#endif
#ifdef USE_CLIMATE
#endif
#ifdef USE_NUMBER
#endif
#ifdef USE_SELECT
#endif
#ifdef USE_SIREN
#endif
#ifdef USE_LOCK
#endif
#ifdef USE_BUTTON
#endif
#ifdef USE_MEDIA_PLAYER
#endif
#ifdef USE_BLUETOOTH_PROXY
#endif
#ifdef USE_VOICE_ASSISTANT
#endif
#ifdef USE_ALARM_CONTROL_PANEL
#endif
#ifdef USE_TEXT
#endif
#ifdef USE_DATETIME_DATE
#endif
#ifdef USE_DATETIME_TIME
#endif
#ifdef USE_EVENT
#endif
#ifdef USE_VALVE
#endif
#ifdef USE_DATETIME_DATETIME
#endif
#ifdef USE_UPDATE
#endif

// Metadata definitions for classes using metadata approach
const FieldMetaV2 HelloRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(HelloRequest, client_info), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(HelloRequest, api_version_major), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(HelloRequest, api_version_minor), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 HelloResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(HelloResponse, api_version_major), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(HelloResponse, api_version_minor), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(HelloResponse, server_info), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(HelloResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const FieldMetaV2 ConnectRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ConnectRequest, password), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const FieldMetaV2 ConnectResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ConnectResponse, invalid_password), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 AreaInfo::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(AreaInfo, area_id), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(AreaInfo, name), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const FieldMetaV2 DeviceInfo::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(DeviceInfo, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(DeviceInfo, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(DeviceInfo, area_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 DeviceInfoResponse::FIELDS_V2[20] = {
    {1, PROTO_FIELD_OFFSET(DeviceInfoResponse, uses_password), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(DeviceInfoResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(DeviceInfoResponse, mac_address), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(DeviceInfoResponse, esphome_version), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(DeviceInfoResponse, compilation_time), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(DeviceInfoResponse, model), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(DeviceInfoResponse, has_deep_sleep), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(DeviceInfoResponse, project_name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(DeviceInfoResponse, project_version), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(DeviceInfoResponse, webserver_port), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {11,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_bluetooth_proxy_version),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}},
    {15,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_proxy_feature_flags),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}},
    {12, PROTO_FIELD_OFFSET(DeviceInfoResponse, manufacturer), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(DeviceInfoResponse, friendly_name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {14,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_voice_assistant_version),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}},
    {17,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, voice_assistant_feature_flags),
     ProtoFieldType::TYPE_UINT32,
     false,
     2,
     {}},
    {16, PROTO_FIELD_OFFSET(DeviceInfoResponse, suggested_area), ProtoFieldType::TYPE_STRING, false, 2, {}},
    {18, PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_mac_address), ProtoFieldType::TYPE_STRING, false, 2, {}},
    {19, PROTO_FIELD_OFFSET(DeviceInfoResponse, api_encryption_supported), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {22,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, area),
     ProtoFieldType::TYPE_MESSAGE,
     false,
     2,
     {.message = {&encode_message_field<AreaInfo>, &size_message_field<AreaInfo>, &decode_message_field<AreaInfo>}}}};
const RepeatedFieldMetaV2 DeviceInfoResponse::REPEATED_FIELDS_V2[2] = {
    {20,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, devices),
     ProtoFieldType::TYPE_MESSAGE,
     2,
     {.message = {&encode_repeated_message_field<DeviceInfo>, &size_repeated_message_field<DeviceInfo>,
                  &decode_repeated_message_field<DeviceInfo>}}},
    {21,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, areas),
     ProtoFieldType::TYPE_MESSAGE,
     2,
     {.message = {&encode_repeated_message_field<AreaInfo>, &size_repeated_message_field<AreaInfo>,
                  &decode_repeated_message_field<AreaInfo>}}}};
#ifdef USE_BINARY_SENSOR
const FieldMetaV2 ListEntitiesBinarySensorResponse::FIELDS_V2[10] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, is_status_binary_sensor),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, disabled_by_default),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 BinarySensorStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BinarySensorStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BinarySensorStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BinarySensorStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(BinarySensorStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
#endif
#ifdef USE_COVER
const FieldMetaV2 ListEntitiesCoverResponse::FIELDS_V2[13] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_position), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_tilt), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_stop), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 CoverStateResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(CoverStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(CoverStateResponse, legacy_state), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(CoverStateResponse, position), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(CoverStateResponse, tilt), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(CoverStateResponse, current_operation), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(CoverStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 CoverCommandRequest::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(CoverCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(CoverCommandRequest, has_legacy_command), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(CoverCommandRequest, legacy_command), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(CoverCommandRequest, has_position), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(CoverCommandRequest, position), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(CoverCommandRequest, has_tilt), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(CoverCommandRequest, tilt), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(CoverCommandRequest, stop), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
#endif
#ifdef USE_FAN
const FieldMetaV2 ListEntitiesFanResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_oscillation), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_speed), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_direction), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_speed_count), ProtoFieldType::TYPE_INT32, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 ListEntitiesFanResponse::REPEATED_FIELDS_V2[1] = {
    {12, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_preset_modes), ProtoFieldType::TYPE_STRING, 1, {}}};
const FieldMetaV2 FanStateResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(FanStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(FanStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(FanStateResponse, oscillating), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(FanStateResponse, speed), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(FanStateResponse, direction), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(FanStateResponse, speed_level), ProtoFieldType::TYPE_INT32, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(FanStateResponse, preset_mode), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(FanStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 FanCommandRequest::FIELDS_V2[13] = {
    {1, PROTO_FIELD_OFFSET(FanCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(FanCommandRequest, has_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(FanCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(FanCommandRequest, has_speed), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(FanCommandRequest, speed), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(FanCommandRequest, has_oscillating), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(FanCommandRequest, oscillating), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(FanCommandRequest, has_direction), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(FanCommandRequest, direction), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(FanCommandRequest, has_speed_level), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(FanCommandRequest, speed_level), ProtoFieldType::TYPE_INT32, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(FanCommandRequest, has_preset_mode), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(FanCommandRequest, preset_mode), ProtoFieldType::TYPE_STRING, false, 1, {}}};
#endif
#ifdef USE_LIGHT
const FieldMetaV2 ListEntitiesLightResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_brightness),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_rgb), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_white_value),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_color_temperature),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, min_mireds), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, max_mireds), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {14, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {15, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {16, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 2, {}}};
const RepeatedFieldMetaV2 ListEntitiesLightResponse::REPEATED_FIELDS_V2[2] = {
    {12, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, supported_color_modes), ProtoFieldType::TYPE_ENUM, 1, {}},
    {11, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, effects), ProtoFieldType::TYPE_STRING, 1, {}}};
const FieldMetaV2 LightStateResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(LightStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(LightStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(LightStateResponse, brightness), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(LightStateResponse, color_mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(LightStateResponse, color_brightness), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(LightStateResponse, red), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(LightStateResponse, green), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(LightStateResponse, blue), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(LightStateResponse, white), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(LightStateResponse, color_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(LightStateResponse, cold_white), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(LightStateResponse, warm_white), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(LightStateResponse, effect), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {14, PROTO_FIELD_OFFSET(LightStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 LightCommandRequest::FIELDS_V2[27] = {
    {1, PROTO_FIELD_OFFSET(LightCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(LightCommandRequest, has_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(LightCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(LightCommandRequest, has_brightness), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(LightCommandRequest, brightness), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {22, PROTO_FIELD_OFFSET(LightCommandRequest, has_color_mode), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {23, PROTO_FIELD_OFFSET(LightCommandRequest, color_mode), ProtoFieldType::TYPE_ENUM, false, 2, {}},
    {20, PROTO_FIELD_OFFSET(LightCommandRequest, has_color_brightness), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {21, PROTO_FIELD_OFFSET(LightCommandRequest, color_brightness), ProtoFieldType::TYPE_FLOAT, false, 2, {}},
    {6, PROTO_FIELD_OFFSET(LightCommandRequest, has_rgb), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(LightCommandRequest, red), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(LightCommandRequest, green), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(LightCommandRequest, blue), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(LightCommandRequest, has_white), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(LightCommandRequest, white), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(LightCommandRequest, has_color_temperature), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(LightCommandRequest, color_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {24, PROTO_FIELD_OFFSET(LightCommandRequest, has_cold_white), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {25, PROTO_FIELD_OFFSET(LightCommandRequest, cold_white), ProtoFieldType::TYPE_FLOAT, false, 2, {}},
    {26, PROTO_FIELD_OFFSET(LightCommandRequest, has_warm_white), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {27, PROTO_FIELD_OFFSET(LightCommandRequest, warm_white), ProtoFieldType::TYPE_FLOAT, false, 2, {}},
    {14, PROTO_FIELD_OFFSET(LightCommandRequest, has_transition_length), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {15, PROTO_FIELD_OFFSET(LightCommandRequest, transition_length), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {16, PROTO_FIELD_OFFSET(LightCommandRequest, has_flash_length), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {17, PROTO_FIELD_OFFSET(LightCommandRequest, flash_length), ProtoFieldType::TYPE_UINT32, false, 2, {}},
    {18, PROTO_FIELD_OFFSET(LightCommandRequest, has_effect), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {19, PROTO_FIELD_OFFSET(LightCommandRequest, effect), ProtoFieldType::TYPE_STRING, false, 2, {}}};
#endif
#ifdef USE_SENSOR
const FieldMetaV2 ListEntitiesSensorResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unit_of_measurement), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, accuracy_decimals), ProtoFieldType::TYPE_INT32, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, force_update), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, state_class), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, legacy_last_reset_type),
     ProtoFieldType::TYPE_ENUM,
     false,
     1,
     {}},
    {12, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {14, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 SensorStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(SensorStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SensorStateResponse, state), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(SensorStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(SensorStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
#endif
#ifdef USE_SWITCH
const FieldMetaV2 ListEntitiesSwitchResponse::FIELDS_V2[10] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 SwitchStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SwitchStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SwitchStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(SwitchStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 SwitchCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SwitchCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SwitchCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
#endif
#ifdef USE_TEXT_SENSOR
const FieldMetaV2 ListEntitiesTextSensorResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, disabled_by_default),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 TextSensorStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(TextSensorStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(TextSensorStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(TextSensorStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(TextSensorStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
#endif
const FieldMetaV2 SubscribeLogsRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SubscribeLogsRequest, level), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SubscribeLogsRequest, dump_config), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 SubscribeLogsResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SubscribeLogsResponse, level), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(SubscribeLogsResponse, message), ProtoFieldType::TYPE_BYTES, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(SubscribeLogsResponse, send_failed), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
#ifdef USE_API_NOISE
const FieldMetaV2 NoiseEncryptionSetKeyRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyRequest, key), ProtoFieldType::TYPE_BYTES, false, 1, {}}};
const FieldMetaV2 NoiseEncryptionSetKeyResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyResponse, success), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
#endif
const FieldMetaV2 HomeassistantServiceMap::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(HomeassistantServiceMap, key), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(HomeassistantServiceMap, value), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const FieldMetaV2 HomeassistantServiceResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, service), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, is_event), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const RepeatedFieldMetaV2 HomeassistantServiceResponse::REPEATED_FIELDS_V2[3] = {
    {2,
     PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<HomeassistantServiceMap>,
                  &size_repeated_message_field<HomeassistantServiceMap>,
                  &decode_repeated_message_field<HomeassistantServiceMap>}}},
    {3,
     PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data_template),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<HomeassistantServiceMap>,
                  &size_repeated_message_field<HomeassistantServiceMap>,
                  &decode_repeated_message_field<HomeassistantServiceMap>}}},
    {4,
     PROTO_FIELD_OFFSET(HomeassistantServiceResponse, variables),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<HomeassistantServiceMap>,
                  &size_repeated_message_field<HomeassistantServiceMap>,
                  &decode_repeated_message_field<HomeassistantServiceMap>}}}};
const FieldMetaV2 SubscribeHomeAssistantStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, entity_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, attribute), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, once), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 HomeAssistantStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(HomeAssistantStateResponse, entity_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(HomeAssistantStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(HomeAssistantStateResponse, attribute), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const FieldMetaV2 GetTimeResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(GetTimeResponse, epoch_seconds), ProtoFieldType::TYPE_FIXED32, false, 1, {}}};
const FieldMetaV2 ListEntitiesServicesArgument::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, type), ProtoFieldType::TYPE_ENUM, false, 1, {}}};
const FieldMetaV2 ListEntitiesServicesResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}}};
const RepeatedFieldMetaV2 ListEntitiesServicesResponse::REPEATED_FIELDS_V2[1] = {
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, args),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<ListEntitiesServicesArgument>,
                  &size_repeated_message_field<ListEntitiesServicesArgument>,
                  &decode_repeated_message_field<ListEntitiesServicesArgument>}}}};
const FieldMetaV2 ExecuteServiceArgument::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ExecuteServiceArgument, legacy_int), ProtoFieldType::TYPE_INT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_), ProtoFieldType::TYPE_SINT32, false, 1, {}}};
const RepeatedFieldMetaV2 ExecuteServiceArgument::REPEATED_FIELDS_V2[4] = {
    {6, PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_array), ProtoFieldType::TYPE_BOOL, 1, {}},
    {7, PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_array), ProtoFieldType::TYPE_SINT32, 1, {}},
    {8, PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_array), ProtoFieldType::TYPE_FLOAT, 1, {}},
    {9, PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_array), ProtoFieldType::TYPE_STRING, 1, {}}};
const FieldMetaV2 ExecuteServiceRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ExecuteServiceRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}}};
const RepeatedFieldMetaV2 ExecuteServiceRequest::REPEATED_FIELDS_V2[1] = {
    {2,
     PROTO_FIELD_OFFSET(ExecuteServiceRequest, args),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<ExecuteServiceArgument>,
                  &size_repeated_message_field<ExecuteServiceArgument>,
                  &decode_repeated_message_field<ExecuteServiceArgument>}}}};
#ifdef USE_CAMERA
const FieldMetaV2 ListEntitiesCameraResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 CameraImageResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(CameraImageResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(CameraImageResponse, data), ProtoFieldType::TYPE_BYTES, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(CameraImageResponse, done), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 CameraImageRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(CameraImageRequest, single), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(CameraImageRequest, stream), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
#endif
#ifdef USE_CLIMATE
const FieldMetaV2 ListEntitiesClimateResponse::FIELDS_V2[20] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_temperature),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_two_point_target_temperature),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_temperature),
     ProtoFieldType::TYPE_FLOAT,
     false,
     1,
     {}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_temperature),
     ProtoFieldType::TYPE_FLOAT,
     false,
     1,
     {}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_target_temperature_step),
     ProtoFieldType::TYPE_FLOAT,
     false,
     1,
     {}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, legacy_supports_away),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {12, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_action), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {18, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {19, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, icon), ProtoFieldType::TYPE_STRING, false, 2, {}},
    {20, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 2, {}},
    {21,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_current_temperature_step),
     ProtoFieldType::TYPE_FLOAT,
     false,
     2,
     {}},
    {22,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_humidity),
     ProtoFieldType::TYPE_BOOL,
     false,
     2,
     {}},
    {23,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_target_humidity),
     ProtoFieldType::TYPE_BOOL,
     false,
     2,
     {}},
    {24,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_humidity),
     ProtoFieldType::TYPE_FLOAT,
     false,
     2,
     {}},
    {25,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_humidity),
     ProtoFieldType::TYPE_FLOAT,
     false,
     2,
     {}},
    {26, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 2, {}}};
const RepeatedFieldMetaV2 ListEntitiesClimateResponse::REPEATED_FIELDS_V2[6] = {
    {7, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_modes), ProtoFieldType::TYPE_ENUM, 1, {}},
    {13, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_fan_modes), ProtoFieldType::TYPE_ENUM, 1, {}},
    {14, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_swing_modes), ProtoFieldType::TYPE_ENUM, 1, {}},
    {15,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_fan_modes),
     ProtoFieldType::TYPE_STRING,
     1,
     {}},
    {16, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_presets), ProtoFieldType::TYPE_ENUM, 2, {}},
    {17,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_presets),
     ProtoFieldType::TYPE_STRING,
     2,
     {}}};
const FieldMetaV2 ClimateStateResponse::FIELDS_V2[16] = {
    {1, PROTO_FIELD_OFFSET(ClimateStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ClimateStateResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ClimateStateResponse, current_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_low), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_high), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ClimateStateResponse, unused_legacy_away), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ClimateStateResponse, action), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ClimateStateResponse, fan_mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ClimateStateResponse, swing_mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ClimateStateResponse, custom_fan_mode), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(ClimateStateResponse, preset), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(ClimateStateResponse, custom_preset), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {14, PROTO_FIELD_OFFSET(ClimateStateResponse, current_humidity), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {15, PROTO_FIELD_OFFSET(ClimateStateResponse, target_humidity), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {16, PROTO_FIELD_OFFSET(ClimateStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 2, {}}};
const FieldMetaV2 ClimateCommandRequest::FIELDS_V2[23] = {
    {1, PROTO_FIELD_OFFSET(ClimateCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_mode), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ClimateCommandRequest, mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_low), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_low), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {8,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_high),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {9, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_high), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_has_legacy_away), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_legacy_away), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_fan_mode), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(ClimateCommandRequest, fan_mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {14, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_swing_mode), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {15, PROTO_FIELD_OFFSET(ClimateCommandRequest, swing_mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {16, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_fan_mode), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {17, PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_fan_mode), ProtoFieldType::TYPE_STRING, false, 2, {}},
    {18, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_preset), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {19, PROTO_FIELD_OFFSET(ClimateCommandRequest, preset), ProtoFieldType::TYPE_ENUM, false, 2, {}},
    {20, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_preset), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {21, PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_preset), ProtoFieldType::TYPE_STRING, false, 2, {}},
    {22, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_humidity), ProtoFieldType::TYPE_BOOL, false, 2, {}},
    {23, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_humidity), ProtoFieldType::TYPE_FLOAT, false, 2, {}}};
#endif
#ifdef USE_NUMBER
const FieldMetaV2 ListEntitiesNumberResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, min_value), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, max_value), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, step), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unit_of_measurement),
     ProtoFieldType::TYPE_STRING,
     false,
     1,
     {}},
    {12, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {13, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {14, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 NumberStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(NumberStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(NumberStateResponse, state), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(NumberStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(NumberStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 NumberCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(NumberCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(NumberCommandRequest, state), ProtoFieldType::TYPE_FLOAT, false, 1, {}}};
#endif
#ifdef USE_SELECT
const FieldMetaV2 ListEntitiesSelectResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 ListEntitiesSelectResponse::REPEATED_FIELDS_V2[1] = {
    {6, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, options), ProtoFieldType::TYPE_STRING, 1, {}}};
const FieldMetaV2 SelectStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(SelectStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SelectStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(SelectStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(SelectStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 SelectCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SelectCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SelectCommandRequest, state), ProtoFieldType::TYPE_STRING, false, 1, {}}};
#endif
#ifdef USE_SIREN
const FieldMetaV2 ListEntitiesSirenResponse::FIELDS_V2[10] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_duration), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_volume), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 ListEntitiesSirenResponse::REPEATED_FIELDS_V2[1] = {
    {7, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, tones), ProtoFieldType::TYPE_STRING, 1, {}}};
const FieldMetaV2 SirenStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SirenStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SirenStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(SirenStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 SirenCommandRequest::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(SirenCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SirenCommandRequest, has_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(SirenCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(SirenCommandRequest, has_tone), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(SirenCommandRequest, tone), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(SirenCommandRequest, has_duration), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(SirenCommandRequest, duration), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(SirenCommandRequest, has_volume), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(SirenCommandRequest, volume), ProtoFieldType::TYPE_FLOAT, false, 1, {}}};
#endif
#ifdef USE_LOCK
const FieldMetaV2 ListEntitiesLockResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, supports_open), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, requires_code), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, code_format), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 LockStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(LockStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(LockStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(LockStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 LockCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(LockCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(LockCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(LockCommandRequest, has_code), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(LockCommandRequest, code), ProtoFieldType::TYPE_STRING, false, 1, {}}};
#endif
#ifdef USE_BUTTON
const FieldMetaV2 ListEntitiesButtonResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 ButtonCommandRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ButtonCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}}};
#endif
#ifdef USE_MEDIA_PLAYER
const FieldMetaV2 MediaPlayerSupportedFormat::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, format), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_rate), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, num_channels), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, purpose), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_bytes), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 ListEntitiesMediaPlayerResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, disabled_by_default),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supports_pause), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 ListEntitiesMediaPlayerResponse::REPEATED_FIELDS_V2[1] = {
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supported_formats),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<MediaPlayerSupportedFormat>,
                  &size_repeated_message_field<MediaPlayerSupportedFormat>,
                  &decode_repeated_message_field<MediaPlayerSupportedFormat>}}}};
const FieldMetaV2 MediaPlayerStateResponse::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, volume), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, muted), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 MediaPlayerCommandRequest::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_command), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_volume), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, volume), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_media_url), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, media_url), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_announcement), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, announcement), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
#endif
#ifdef USE_BLUETOOTH_PROXY
const FieldMetaV2 SubscribeBluetoothLEAdvertisementsRequest::FIELDS_V2[1] = {
    {1,
     PROTO_FIELD_OFFSET(SubscribeBluetoothLEAdvertisementsRequest, flags),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}}};
const FieldMetaV2 BluetoothServiceData::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothServiceData, uuid), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothServiceData, data), ProtoFieldType::TYPE_BYTES, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothServiceData::REPEATED_FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothServiceData, legacy_data), ProtoFieldType::TYPE_UINT32, 1, {}}};
const FieldMetaV2 BluetoothLEAdvertisementResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, name), ProtoFieldType::TYPE_BYTES, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, rssi), ProtoFieldType::TYPE_SINT32, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address_type), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothLEAdvertisementResponse::REPEATED_FIELDS_V2[3] = {
    {4, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_uuids), ProtoFieldType::TYPE_STRING, 1, {}},
    {5,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_data),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<BluetoothServiceData>,
                  &size_repeated_message_field<BluetoothServiceData>,
                  &decode_repeated_message_field<BluetoothServiceData>}}},
    {6,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, manufacturer_data),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<BluetoothServiceData>,
                  &size_repeated_message_field<BluetoothServiceData>,
                  &decode_repeated_message_field<BluetoothServiceData>}}}};
const FieldMetaV2 BluetoothLERawAdvertisement::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, rssi), ProtoFieldType::TYPE_SINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address_type), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, data), ProtoFieldType::TYPE_BYTES, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothLERawAdvertisementsResponse::REPEATED_FIELDS_V2[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisementsResponse, advertisements),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<BluetoothLERawAdvertisement>,
                  &size_repeated_message_field<BluetoothLERawAdvertisement>,
                  &decode_repeated_message_field<BluetoothLERawAdvertisement>}}}};
const FieldMetaV2 BluetoothDeviceRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, request_type), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, has_address_type), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address_type), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 BluetoothDeviceConnectionResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, connected), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, mtu), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, error), ProtoFieldType::TYPE_INT32, false, 1, {}}};
const FieldMetaV2 BluetoothGATTGetServicesRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, {}}};
const FieldMetaV2 BluetoothGATTDescriptor::FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothGATTDescriptor::REPEATED_FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, uuid), ProtoFieldType::TYPE_UINT64, 1, {}}};
const FieldMetaV2 BluetoothGATTCharacteristic::FIELDS_V2[2] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, properties), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothGATTCharacteristic::REPEATED_FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, uuid), ProtoFieldType::TYPE_UINT64, 1, {}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, descriptors),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<BluetoothGATTDescriptor>,
                  &size_repeated_message_field<BluetoothGATTDescriptor>,
                  &decode_repeated_message_field<BluetoothGATTDescriptor>}}}};
const FieldMetaV2 BluetoothGATTService::FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTService, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothGATTService::REPEATED_FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTService, uuid), ProtoFieldType::TYPE_UINT64, 1, {}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothGATTService, characteristics),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<BluetoothGATTCharacteristic>,
                  &size_repeated_message_field<BluetoothGATTCharacteristic>,
                  &decode_repeated_message_field<BluetoothGATTCharacteristic>}}}};
const FieldMetaV2 BluetoothGATTGetServicesResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothGATTGetServicesResponse::REPEATED_FIELDS_V2[1] = {
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, services),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<BluetoothGATTService>,
                  &size_repeated_message_field<BluetoothGATTService>,
                  &decode_repeated_message_field<BluetoothGATTService>}}}};
const FieldMetaV2 BluetoothGATTGetServicesDoneResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesDoneResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}}};
const FieldMetaV2 BluetoothGATTReadRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 BluetoothGATTReadResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, data), ProtoFieldType::TYPE_BYTES, false, 1, {}}};
const FieldMetaV2 BluetoothGATTWriteRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, response), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, data), ProtoFieldType::TYPE_BYTES, false, 1, {}}};
const FieldMetaV2 BluetoothGATTReadDescriptorRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 BluetoothGATTWriteDescriptorRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, data), ProtoFieldType::TYPE_BYTES, false, 1, {}}};
const FieldMetaV2 BluetoothGATTNotifyRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, enable), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 BluetoothGATTNotifyDataResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, data), ProtoFieldType::TYPE_BYTES, false, 1, {}}};
const FieldMetaV2 BluetoothConnectionsFreeResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, free), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, limit), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 BluetoothConnectionsFreeResponse::REPEATED_FIELDS_V2[1] = {
    {3, PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, allocated), ProtoFieldType::TYPE_UINT64, 1, {}}};
const FieldMetaV2 BluetoothGATTErrorResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, error), ProtoFieldType::TYPE_INT32, false, 1, {}}};
const FieldMetaV2 BluetoothGATTWriteResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 BluetoothGATTNotifyResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 BluetoothDevicePairingResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, paired), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, error), ProtoFieldType::TYPE_INT32, false, 1, {}}};
const FieldMetaV2 BluetoothDeviceUnpairingResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, success), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, error), ProtoFieldType::TYPE_INT32, false, 1, {}}};
const FieldMetaV2 BluetoothDeviceClearCacheResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, success), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, error), ProtoFieldType::TYPE_INT32, false, 1, {}}};
const FieldMetaV2 BluetoothScannerStateResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, {}}};
const FieldMetaV2 BluetoothScannerSetModeRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothScannerSetModeRequest, mode), ProtoFieldType::TYPE_ENUM, false, 1, {}}};
#endif
#ifdef USE_VOICE_ASSISTANT
const FieldMetaV2 SubscribeVoiceAssistantRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, subscribe), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, flags), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 VoiceAssistantAudioSettings::FIELDS_V2[3] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, noise_suppression_level),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, auto_gain), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, volume_multiplier), ProtoFieldType::TYPE_FLOAT, false, 1, {}}};
const FieldMetaV2 VoiceAssistantRequest::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantRequest, start), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantRequest, conversation_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(VoiceAssistantRequest, flags), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4,
     PROTO_FIELD_OFFSET(VoiceAssistantRequest, audio_settings),
     ProtoFieldType::TYPE_MESSAGE,
     false,
     1,
     {.message = {&encode_message_field<VoiceAssistantAudioSettings>, &size_message_field<VoiceAssistantAudioSettings>,
                  &decode_message_field<VoiceAssistantAudioSettings>}}},
    {5, PROTO_FIELD_OFFSET(VoiceAssistantRequest, wake_word_phrase), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const FieldMetaV2 VoiceAssistantResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantResponse, port), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantResponse, error), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 VoiceAssistantEventData::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantEventData, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantEventData, value), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const FieldMetaV2 VoiceAssistantEventResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, event_type), ProtoFieldType::TYPE_ENUM, false, 1, {}}};
const RepeatedFieldMetaV2 VoiceAssistantEventResponse::REPEATED_FIELDS_V2[1] = {
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, data),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<VoiceAssistantEventData>,
                  &size_repeated_message_field<VoiceAssistantEventData>,
                  &decode_repeated_message_field<VoiceAssistantEventData>}}}};
const FieldMetaV2 VoiceAssistantAudio::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantAudio, data), ProtoFieldType::TYPE_BYTES, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantAudio, end), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 VoiceAssistantTimerEventResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, event_type), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, timer_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, total_seconds), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, seconds_left), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, is_active), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 VoiceAssistantAnnounceRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, media_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, text), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, preannounce_media_id),
     ProtoFieldType::TYPE_STRING,
     false,
     1,
     {}},
    {4,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, start_conversation),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}}};
const FieldMetaV2 VoiceAssistantAnnounceFinished::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceFinished, success), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
const FieldMetaV2 VoiceAssistantWakeWord::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, wake_word), ProtoFieldType::TYPE_STRING, false, 1, {}}};
const RepeatedFieldMetaV2 VoiceAssistantWakeWord::REPEATED_FIELDS_V2[1] = {
    {3, PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, trained_languages), ProtoFieldType::TYPE_STRING, 1, {}}};
const FieldMetaV2 VoiceAssistantConfigurationResponse::FIELDS_V2[1] = {
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, max_active_wake_words),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}}};
const RepeatedFieldMetaV2 VoiceAssistantConfigurationResponse::REPEATED_FIELDS_V2[2] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, available_wake_words),
     ProtoFieldType::TYPE_MESSAGE,
     1,
     {.message = {&encode_repeated_message_field<VoiceAssistantWakeWord>,
                  &size_repeated_message_field<VoiceAssistantWakeWord>,
                  &decode_repeated_message_field<VoiceAssistantWakeWord>}}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, active_wake_words),
     ProtoFieldType::TYPE_STRING,
     1,
     {}}};
const RepeatedFieldMetaV2 VoiceAssistantSetConfiguration::REPEATED_FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantSetConfiguration, active_wake_words), ProtoFieldType::TYPE_STRING, 1, {}}};
#endif
#ifdef USE_ALARM_CONTROL_PANEL
const FieldMetaV2 ListEntitiesAlarmControlPanelResponse::FIELDS_V2[11] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, object_id),
     ProtoFieldType::TYPE_STRING,
     false,
     1,
     {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, unique_id),
     ProtoFieldType::TYPE_STRING,
     false,
     1,
     {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, disabled_by_default),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, entity_category),
     ProtoFieldType::TYPE_ENUM,
     false,
     1,
     {}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, supported_features),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code_to_arm),
     ProtoFieldType::TYPE_BOOL,
     false,
     1,
     {}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, device_id),
     ProtoFieldType::TYPE_UINT32,
     false,
     1,
     {}}};
const FieldMetaV2 AlarmControlPanelStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 AlarmControlPanelCommandRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, code), ProtoFieldType::TYPE_STRING, false, 1, {}}};
#endif
#ifdef USE_TEXT
const FieldMetaV2 ListEntitiesTextResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, min_length), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, max_length), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, pattern), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 TextStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(TextStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(TextStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(TextStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(TextStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 TextCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(TextCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(TextCommandRequest, state), ProtoFieldType::TYPE_STRING, false, 1, {}}};
#endif
#ifdef USE_DATETIME_DATE
const FieldMetaV2 ListEntitiesDateResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 DateStateResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(DateStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(DateStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(DateStateResponse, year), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(DateStateResponse, month), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(DateStateResponse, day), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(DateStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 DateCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(DateCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(DateCommandRequest, year), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(DateCommandRequest, month), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(DateCommandRequest, day), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
#endif
#ifdef USE_DATETIME_TIME
const FieldMetaV2 ListEntitiesTimeResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 TimeStateResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(TimeStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(TimeStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(TimeStateResponse, hour), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(TimeStateResponse, minute), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(TimeStateResponse, second), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(TimeStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 TimeCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(TimeCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(TimeCommandRequest, hour), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(TimeCommandRequest, minute), ProtoFieldType::TYPE_UINT32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(TimeCommandRequest, second), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
#endif
#ifdef USE_EVENT
const FieldMetaV2 ListEntitiesEventResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const RepeatedFieldMetaV2 ListEntitiesEventResponse::REPEATED_FIELDS_V2[1] = {
    {9, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, event_types), ProtoFieldType::TYPE_STRING, 1, {}}};
const FieldMetaV2 EventResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(EventResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(EventResponse, event_type), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(EventResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
#endif
#ifdef USE_VALVE
const FieldMetaV2 ListEntitiesValveResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_position), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_stop), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {12, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 ValveStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(ValveStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ValveStateResponse, position), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ValveStateResponse, current_operation), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ValveStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 ValveCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(ValveCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ValveCommandRequest, has_position), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ValveCommandRequest, position), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ValveCommandRequest, stop), ProtoFieldType::TYPE_BOOL, false, 1, {}}};
#endif
#ifdef USE_DATETIME_DATETIME
const FieldMetaV2 ListEntitiesDateTimeResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 DateTimeStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(DateTimeStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(DateTimeStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(DateTimeStateResponse, epoch_seconds), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(DateTimeStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 DateTimeCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(DateTimeCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(DateTimeCommandRequest, epoch_seconds), ProtoFieldType::TYPE_FIXED32, false, 1, {}}};
#endif
#ifdef USE_UPDATE
const FieldMetaV2 ListEntitiesUpdateResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, name), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 UpdateStateResponse::FIELDS_V2[11] = {
    {1, PROTO_FIELD_OFFSET(UpdateStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(UpdateStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {3, PROTO_FIELD_OFFSET(UpdateStateResponse, in_progress), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {4, PROTO_FIELD_OFFSET(UpdateStateResponse, has_progress), ProtoFieldType::TYPE_BOOL, false, 1, {}},
    {5, PROTO_FIELD_OFFSET(UpdateStateResponse, progress), ProtoFieldType::TYPE_FLOAT, false, 1, {}},
    {6, PROTO_FIELD_OFFSET(UpdateStateResponse, current_version), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {7, PROTO_FIELD_OFFSET(UpdateStateResponse, latest_version), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {8, PROTO_FIELD_OFFSET(UpdateStateResponse, title), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {9, PROTO_FIELD_OFFSET(UpdateStateResponse, release_summary), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {10, PROTO_FIELD_OFFSET(UpdateStateResponse, release_url), ProtoFieldType::TYPE_STRING, false, 1, {}},
    {11, PROTO_FIELD_OFFSET(UpdateStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, {}}};
const FieldMetaV2 UpdateCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(UpdateCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, {}},
    {2, PROTO_FIELD_OFFSET(UpdateCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, {}}};
#endif

}  // namespace api
}  // namespace esphome
