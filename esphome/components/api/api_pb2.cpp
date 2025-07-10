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
const FieldMetaV3 HelloRequest::FIELDS_V3[3] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(HelloRequest, client_info)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(HelloRequest, api_version_major)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(HelloRequest, api_version_minor)}}};
const FieldMetaV3 HelloResponse::FIELDS_V3[4] = {
    {1, 2, {.offset = PROTO_FIELD_OFFSET(HelloResponse, api_version_major)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(HelloResponse, api_version_minor)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(HelloResponse, server_info)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(HelloResponse, name)}}};
const FieldMetaV3 ConnectRequest::FIELDS_V3[1] = {{1, 8, {.offset = PROTO_FIELD_OFFSET(ConnectRequest, password)}}};
const FieldMetaV3 ConnectResponse::FIELDS_V3[1] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(ConnectResponse, invalid_password)}}};
const FieldMetaV3 AreaInfo::FIELDS_V3[2] = {{1, 2, {.offset = PROTO_FIELD_OFFSET(AreaInfo, area_id)}},
                                            {2, 8, {.offset = PROTO_FIELD_OFFSET(AreaInfo, name)}}};
const FieldMetaV3 DeviceInfo::FIELDS_V3[3] = {{1, 2, {.offset = PROTO_FIELD_OFFSET(DeviceInfo, device_id)}},
                                              {2, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfo, name)}},
                                              {3, 2, {.offset = PROTO_FIELD_OFFSET(DeviceInfo, area_id)}}};
const FieldMetaV3 DeviceInfoResponse::FIELDS_V3[20] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, uses_password)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, name)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, mac_address)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, esphome_version)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, compilation_time)}},
    {6, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, model)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, has_deep_sleep)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, project_name)}},
    {9, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, project_version)}},
    {10, 2, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, webserver_port)}},
    {11, 2, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_bluetooth_proxy_version)}},
    {15, 2, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_proxy_feature_flags)}},
    {12, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, manufacturer)}},
    {13, 8, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, friendly_name)}},
    {14, 2, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_voice_assistant_version)}},
    {17, 34, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, voice_assistant_feature_flags)}},
    {16, 40, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, suggested_area)}},
    {18, 40, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_mac_address)}},
    {19, 32, {.offset = PROTO_FIELD_OFFSET(DeviceInfoResponse, api_encryption_supported)}},
    {22,
     42,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(DeviceInfoResponse, area) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(9 | (((PROTO_FIELD_OFFSET(DeviceInfoResponse, area) >> 8) & 0x0F) << 4))}}};
const RepeatedFieldMetaV3 DeviceInfoResponse::REPEATED_FIELDS_V3[2] = {
    {20,
     42,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(DeviceInfoResponse, devices) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(0 | (((PROTO_FIELD_OFFSET(DeviceInfoResponse, devices) >> 8) & 0x0F) << 4))}},
    {21,
     42,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(DeviceInfoResponse, areas) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(1 | (((PROTO_FIELD_OFFSET(DeviceInfoResponse, areas) >> 8) & 0x0F) << 4))}}};
#ifdef USE_BINARY_SENSOR
const FieldMetaV3 ListEntitiesBinarySensorResponse::FIELDS_V3[10] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_class)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, is_status_binary_sensor)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, disabled_by_default)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, icon)}},
    {9, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, entity_category)}},
    {10, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_id)}}};
const FieldMetaV3 BinarySensorStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(BinarySensorStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(BinarySensorStateResponse, state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(BinarySensorStateResponse, missing_state)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(BinarySensorStateResponse, device_id)}}};
#endif
#ifdef USE_COVER
const FieldMetaV3 ListEntitiesCoverResponse::FIELDS_V3[13] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, unique_id)}},
    {5, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, assumed_state)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_position)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_tilt)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_class)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, disabled_by_default)}},
    {10, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, icon)}},
    {11, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, entity_category)}},
    {12, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_stop)}},
    {13, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_id)}}};
const FieldMetaV3 CoverStateResponse::FIELDS_V3[6] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(CoverStateResponse, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(CoverStateResponse, legacy_state)}},
    {3, 11, {.offset = PROTO_FIELD_OFFSET(CoverStateResponse, position)}},
    {4, 11, {.offset = PROTO_FIELD_OFFSET(CoverStateResponse, tilt)}},
    {5, 7, {.offset = PROTO_FIELD_OFFSET(CoverStateResponse, current_operation)}},
    {6, 2, {.offset = PROTO_FIELD_OFFSET(CoverStateResponse, device_id)}}};
const FieldMetaV3 CoverCommandRequest::FIELDS_V3[8] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, has_legacy_command)}},
    {3, 7, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, legacy_command)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, has_position)}},
    {5, 11, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, position)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, has_tilt)}},
    {7, 11, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, tilt)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(CoverCommandRequest, stop)}}};
#endif
#ifdef USE_FAN
const FieldMetaV3 ListEntitiesFanResponse::FIELDS_V3[12] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, unique_id)}},
    {5, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_oscillation)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_speed)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_direction)}},
    {8, 1, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_speed_count)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, disabled_by_default)}},
    {10, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, icon)}},
    {11, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, entity_category)}},
    {13, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, device_id)}}};
const RepeatedFieldMetaV3 ListEntitiesFanResponse::REPEATED_FIELDS_V3[1] = {
    {12, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_preset_modes)}}};
const FieldMetaV3 FanStateResponse::FIELDS_V3[8] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, oscillating)}},
    {4, 7, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, speed)}},
    {5, 7, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, direction)}},
    {6, 1, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, speed_level)}},
    {7, 8, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, preset_mode)}},
    {8, 2, {.offset = PROTO_FIELD_OFFSET(FanStateResponse, device_id)}}};
const FieldMetaV3 FanCommandRequest::FIELDS_V3[13] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, has_state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, state)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, has_speed)}},
    {5, 7, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, speed)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, has_oscillating)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, oscillating)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, has_direction)}},
    {9, 7, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, direction)}},
    {10, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, has_speed_level)}},
    {11, 1, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, speed_level)}},
    {12, 0, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, has_preset_mode)}},
    {13, 8, {.offset = PROTO_FIELD_OFFSET(FanCommandRequest, preset_mode)}}};
#endif
#ifdef USE_LIGHT
const FieldMetaV3 ListEntitiesLightResponse::FIELDS_V3[14] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, unique_id)}},
    {5, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_brightness)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_rgb)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_white_value)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_color_temperature)}},
    {9, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, min_mireds)}},
    {10, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, max_mireds)}},
    {13, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, disabled_by_default)}},
    {14, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, icon)}},
    {15, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, entity_category)}},
    {16, 34, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, device_id)}}};
const RepeatedFieldMetaV3 ListEntitiesLightResponse::REPEATED_FIELDS_V3[2] = {
    {12, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, supported_color_modes)}},
    {11, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLightResponse, effects)}}};
const FieldMetaV3 LightStateResponse::FIELDS_V3[14] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, state)}},
    {3, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, brightness)}},
    {11, 7, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, color_mode)}},
    {10, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, color_brightness)}},
    {4, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, red)}},
    {5, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, green)}},
    {6, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, blue)}},
    {7, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, white)}},
    {8, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, color_temperature)}},
    {12, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, cold_white)}},
    {13, 11, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, warm_white)}},
    {9, 8, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, effect)}},
    {14, 2, {.offset = PROTO_FIELD_OFFSET(LightStateResponse, device_id)}}};
const FieldMetaV3 LightCommandRequest::FIELDS_V3[27] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, state)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_brightness)}},
    {5, 11, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, brightness)}},
    {22, 32, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_color_mode)}},
    {23, 39, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, color_mode)}},
    {20, 32, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_color_brightness)}},
    {21, 43, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, color_brightness)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_rgb)}},
    {7, 11, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, red)}},
    {8, 11, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, green)}},
    {9, 11, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, blue)}},
    {10, 0, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_white)}},
    {11, 11, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, white)}},
    {12, 0, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_color_temperature)}},
    {13, 11, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, color_temperature)}},
    {24, 32, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_cold_white)}},
    {25, 43, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, cold_white)}},
    {26, 32, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_warm_white)}},
    {27, 43, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, warm_white)}},
    {14, 0, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_transition_length)}},
    {15, 2, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, transition_length)}},
    {16, 32, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_flash_length)}},
    {17, 34, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, flash_length)}},
    {18, 32, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, has_effect)}},
    {19, 40, {.offset = PROTO_FIELD_OFFSET(LightCommandRequest, effect)}}};
#endif
#ifdef USE_SENSOR
const FieldMetaV3 ListEntitiesSensorResponse::FIELDS_V3[14] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, icon)}},
    {6, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unit_of_measurement)}},
    {7, 1, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, accuracy_decimals)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, force_update)}},
    {9, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_class)}},
    {10, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, state_class)}},
    {11, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, legacy_last_reset_type)}},
    {12, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, disabled_by_default)}},
    {13, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, entity_category)}},
    {14, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_id)}}};
const FieldMetaV3 SensorStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(SensorStateResponse, key)}},
    {2, 11, {.offset = PROTO_FIELD_OFFSET(SensorStateResponse, state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(SensorStateResponse, missing_state)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(SensorStateResponse, device_id)}}};
#endif
#ifdef USE_SWITCH
const FieldMetaV3 ListEntitiesSwitchResponse::FIELDS_V3[10] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, assumed_state)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, disabled_by_default)}},
    {8, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, entity_category)}},
    {9, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_class)}},
    {10, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_id)}}};
const FieldMetaV3 SwitchStateResponse::FIELDS_V3[3] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(SwitchStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(SwitchStateResponse, state)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(SwitchStateResponse, device_id)}}};
const FieldMetaV3 SwitchCommandRequest::FIELDS_V3[2] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(SwitchCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(SwitchCommandRequest, state)}}};
#endif
#ifdef USE_TEXT_SENSOR
const FieldMetaV3 ListEntitiesTextSensorResponse::FIELDS_V3[9] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, entity_category)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_class)}},
    {9, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_id)}}};
const FieldMetaV3 TextSensorStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(TextSensorStateResponse, key)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(TextSensorStateResponse, state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(TextSensorStateResponse, missing_state)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(TextSensorStateResponse, device_id)}}};
#endif
const FieldMetaV3 SubscribeLogsRequest::FIELDS_V3[2] = {
    {1, 7, {.offset = PROTO_FIELD_OFFSET(SubscribeLogsRequest, level)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(SubscribeLogsRequest, dump_config)}}};
const FieldMetaV3 SubscribeLogsResponse::FIELDS_V3[3] = {
    {1, 7, {.offset = PROTO_FIELD_OFFSET(SubscribeLogsResponse, level)}},
    {3, 9, {.offset = PROTO_FIELD_OFFSET(SubscribeLogsResponse, message)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(SubscribeLogsResponse, send_failed)}}};
#ifdef USE_API_NOISE
const FieldMetaV3 NoiseEncryptionSetKeyRequest::FIELDS_V3[1] = {
    {1, 9, {.offset = PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyRequest, key)}}};
const FieldMetaV3 NoiseEncryptionSetKeyResponse::FIELDS_V3[1] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyResponse, success)}}};
#endif
const FieldMetaV3 HomeassistantServiceMap::FIELDS_V3[2] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(HomeassistantServiceMap, key)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(HomeassistantServiceMap, value)}}};
const FieldMetaV3 HomeassistantServiceResponse::FIELDS_V3[2] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(HomeassistantServiceResponse, service)}},
    {5, 0, {.offset = PROTO_FIELD_OFFSET(HomeassistantServiceResponse, is_event)}}};
const RepeatedFieldMetaV3 HomeassistantServiceResponse::REPEATED_FIELDS_V3[3] = {
    {2,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(2 | (((PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data) >> 8) & 0x0F) << 4))}},
    {3,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data_template) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          2 | (((PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data_template) >> 8) & 0x0F) << 4))}},
    {4,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(HomeassistantServiceResponse, variables) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          2 | (((PROTO_FIELD_OFFSET(HomeassistantServiceResponse, variables) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 SubscribeHomeAssistantStateResponse::FIELDS_V3[3] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, entity_id)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, attribute)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, once)}}};
const FieldMetaV3 HomeAssistantStateResponse::FIELDS_V3[3] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(HomeAssistantStateResponse, entity_id)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(HomeAssistantStateResponse, state)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(HomeAssistantStateResponse, attribute)}}};
const FieldMetaV3 GetTimeResponse::FIELDS_V3[1] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(GetTimeResponse, epoch_seconds)}}};
const FieldMetaV3 ListEntitiesServicesArgument::FIELDS_V3[2] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, name)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, type)}}};
const FieldMetaV3 ListEntitiesServicesResponse::FIELDS_V3[2] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, name)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, key)}}};
const RepeatedFieldMetaV3 ListEntitiesServicesResponse::REPEATED_FIELDS_V3[1] = {
    {3,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, args) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(3 | (((PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, args) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 ExecuteServiceArgument::FIELDS_V3[5] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_)}},
    {2, 1, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, legacy_int)}},
    {3, 11, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_)}},
    {5, 5, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_)}}};
const RepeatedFieldMetaV3 ExecuteServiceArgument::REPEATED_FIELDS_V3[4] = {
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_array)}},
    {7, 5, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_array)}},
    {8, 11, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_array)}},
    {9, 8, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_array)}}};
const FieldMetaV3 ExecuteServiceRequest::FIELDS_V3[1] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(ExecuteServiceRequest, key)}}};
const RepeatedFieldMetaV3 ExecuteServiceRequest::REPEATED_FIELDS_V3[1] = {
    {2,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(ExecuteServiceRequest, args) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(4 | (((PROTO_FIELD_OFFSET(ExecuteServiceRequest, args) >> 8) & 0x0F) << 4))}}};
#ifdef USE_CAMERA
const FieldMetaV3 ListEntitiesCameraResponse::FIELDS_V3[8] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, unique_id)}},
    {5, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, disabled_by_default)}},
    {6, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, icon)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, entity_category)}},
    {8, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, device_id)}}};
const FieldMetaV3 CameraImageResponse::FIELDS_V3[3] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(CameraImageResponse, key)}},
    {2, 9, {.offset = PROTO_FIELD_OFFSET(CameraImageResponse, data)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(CameraImageResponse, done)}}};
const FieldMetaV3 CameraImageRequest::FIELDS_V3[2] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(CameraImageRequest, single)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(CameraImageRequest, stream)}}};
#endif
#ifdef USE_CLIMATE
const FieldMetaV3 ListEntitiesClimateResponse::FIELDS_V3[20] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, unique_id)}},
    {5, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_temperature)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_two_point_target_temperature)}},
    {8, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_temperature)}},
    {9, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_temperature)}},
    {10, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_target_temperature_step)}},
    {11, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, legacy_supports_away)}},
    {12, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_action)}},
    {18, 32, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, disabled_by_default)}},
    {19, 40, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, icon)}},
    {20, 39, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, entity_category)}},
    {21, 43, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_current_temperature_step)}},
    {22, 32, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_humidity)}},
    {23, 32, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_target_humidity)}},
    {24, 43, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_humidity)}},
    {25, 43, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_humidity)}},
    {26, 34, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, device_id)}}};
const RepeatedFieldMetaV3 ListEntitiesClimateResponse::REPEATED_FIELDS_V3[6] = {
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_modes)}},
    {13, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_fan_modes)}},
    {14, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_swing_modes)}},
    {15, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_fan_modes)}},
    {16, 39, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_presets)}},
    {17, 40, {.offset = PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_presets)}}};
const FieldMetaV3 ClimateStateResponse::FIELDS_V3[16] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, mode)}},
    {3, 11, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, current_temperature)}},
    {4, 11, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature)}},
    {5, 11, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_low)}},
    {6, 11, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_high)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, unused_legacy_away)}},
    {8, 7, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, action)}},
    {9, 7, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, fan_mode)}},
    {10, 7, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, swing_mode)}},
    {11, 8, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, custom_fan_mode)}},
    {12, 7, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, preset)}},
    {13, 8, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, custom_preset)}},
    {14, 11, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, current_humidity)}},
    {15, 11, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, target_humidity)}},
    {16, 34, {.offset = PROTO_FIELD_OFFSET(ClimateStateResponse, device_id)}}};
const FieldMetaV3 ClimateCommandRequest::FIELDS_V3[23] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_mode)}},
    {3, 7, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, mode)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature)}},
    {5, 11, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_low)}},
    {7, 11, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_low)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_high)}},
    {9, 11, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_high)}},
    {10, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_has_legacy_away)}},
    {11, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_legacy_away)}},
    {12, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_fan_mode)}},
    {13, 7, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, fan_mode)}},
    {14, 0, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_swing_mode)}},
    {15, 7, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, swing_mode)}},
    {16, 32, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_fan_mode)}},
    {17, 40, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_fan_mode)}},
    {18, 32, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_preset)}},
    {19, 39, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, preset)}},
    {20, 32, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_preset)}},
    {21, 40, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_preset)}},
    {22, 32, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_humidity)}},
    {23, 43, {.offset = PROTO_FIELD_OFFSET(ClimateCommandRequest, target_humidity)}}};
#endif
#ifdef USE_NUMBER
const FieldMetaV3 ListEntitiesNumberResponse::FIELDS_V3[14] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, icon)}},
    {6, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, min_value)}},
    {7, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, max_value)}},
    {8, 11, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, step)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, disabled_by_default)}},
    {10, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, entity_category)}},
    {11, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unit_of_measurement)}},
    {12, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, mode)}},
    {13, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_class)}},
    {14, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_id)}}};
const FieldMetaV3 NumberStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(NumberStateResponse, key)}},
    {2, 11, {.offset = PROTO_FIELD_OFFSET(NumberStateResponse, state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(NumberStateResponse, missing_state)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(NumberStateResponse, device_id)}}};
const FieldMetaV3 NumberCommandRequest::FIELDS_V3[2] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(NumberCommandRequest, key)}},
    {2, 11, {.offset = PROTO_FIELD_OFFSET(NumberCommandRequest, state)}}};
#endif
#ifdef USE_SELECT
const FieldMetaV3 ListEntitiesSelectResponse::FIELDS_V3[8] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, icon)}},
    {7, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, disabled_by_default)}},
    {8, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, entity_category)}},
    {9, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, device_id)}}};
const RepeatedFieldMetaV3 ListEntitiesSelectResponse::REPEATED_FIELDS_V3[1] = {
    {6, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, options)}}};
const FieldMetaV3 SelectStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(SelectStateResponse, key)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(SelectStateResponse, state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(SelectStateResponse, missing_state)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(SelectStateResponse, device_id)}}};
const FieldMetaV3 SelectCommandRequest::FIELDS_V3[2] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(SelectCommandRequest, key)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(SelectCommandRequest, state)}}};
#endif
#ifdef USE_SIREN
const FieldMetaV3 ListEntitiesSirenResponse::FIELDS_V3[10] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, disabled_by_default)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_duration)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_volume)}},
    {10, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, entity_category)}},
    {11, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, device_id)}}};
const RepeatedFieldMetaV3 ListEntitiesSirenResponse::REPEATED_FIELDS_V3[1] = {
    {7, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, tones)}}};
const FieldMetaV3 SirenStateResponse::FIELDS_V3[3] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(SirenStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(SirenStateResponse, state)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(SirenStateResponse, device_id)}}};
const FieldMetaV3 SirenCommandRequest::FIELDS_V3[9] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, has_state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, state)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, has_tone)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, tone)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, has_duration)}},
    {7, 2, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, duration)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, has_volume)}},
    {9, 11, {.offset = PROTO_FIELD_OFFSET(SirenCommandRequest, volume)}}};
#endif
#ifdef USE_LOCK
const FieldMetaV3 ListEntitiesLockResponse::FIELDS_V3[12] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, entity_category)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, assumed_state)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, supports_open)}},
    {10, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, requires_code)}},
    {11, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, code_format)}},
    {12, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesLockResponse, device_id)}}};
const FieldMetaV3 LockStateResponse::FIELDS_V3[3] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(LockStateResponse, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(LockStateResponse, state)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(LockStateResponse, device_id)}}};
const FieldMetaV3 LockCommandRequest::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(LockCommandRequest, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(LockCommandRequest, command)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(LockCommandRequest, has_code)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(LockCommandRequest, code)}}};
#endif
#ifdef USE_BUTTON
const FieldMetaV3 ListEntitiesButtonResponse::FIELDS_V3[9] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, entity_category)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_class)}},
    {9, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_id)}}};
const FieldMetaV3 ButtonCommandRequest::FIELDS_V3[1] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(ButtonCommandRequest, key)}}};
#endif
#ifdef USE_MEDIA_PLAYER
const FieldMetaV3 MediaPlayerSupportedFormat::FIELDS_V3[5] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, format)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_rate)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, num_channels)}},
    {4, 7, {.offset = PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, purpose)}},
    {5, 2, {.offset = PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_bytes)}}};
const FieldMetaV3 ListEntitiesMediaPlayerResponse::FIELDS_V3[9] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, entity_category)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supports_pause)}},
    {10, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, device_id)}}};
const RepeatedFieldMetaV3 ListEntitiesMediaPlayerResponse::REPEATED_FIELDS_V3[1] = {
    {9,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supported_formats) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          5 | (((PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supported_formats) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 MediaPlayerStateResponse::FIELDS_V3[5] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(MediaPlayerStateResponse, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(MediaPlayerStateResponse, state)}},
    {3, 11, {.offset = PROTO_FIELD_OFFSET(MediaPlayerStateResponse, volume)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(MediaPlayerStateResponse, muted)}},
    {5, 2, {.offset = PROTO_FIELD_OFFSET(MediaPlayerStateResponse, device_id)}}};
const FieldMetaV3 MediaPlayerCommandRequest::FIELDS_V3[9] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_command)}},
    {3, 7, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, command)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_volume)}},
    {5, 11, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, volume)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_media_url)}},
    {7, 8, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, media_url)}},
    {8, 0, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_announcement)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, announcement)}}};
#endif
#ifdef USE_BLUETOOTH_PROXY
const FieldMetaV3 SubscribeBluetoothLEAdvertisementsRequest::FIELDS_V3[1] = {
    {1, 2, {.offset = PROTO_FIELD_OFFSET(SubscribeBluetoothLEAdvertisementsRequest, flags)}}};
const FieldMetaV3 BluetoothServiceData::FIELDS_V3[2] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(BluetoothServiceData, uuid)}},
    {3, 9, {.offset = PROTO_FIELD_OFFSET(BluetoothServiceData, data)}}};
const RepeatedFieldMetaV3 BluetoothServiceData::REPEATED_FIELDS_V3[1] = {
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothServiceData, legacy_data)}}};
const FieldMetaV3 BluetoothLEAdvertisementResponse::FIELDS_V3[4] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address)}},
    {2, 9, {.offset = PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, name)}},
    {3, 5, {.offset = PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, rssi)}},
    {7, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address_type)}}};
const RepeatedFieldMetaV3 BluetoothLEAdvertisementResponse::REPEATED_FIELDS_V3[3] = {
    {4, 8, {.offset = PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_uuids)}},
    {5,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_data) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          6 | (((PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_data) >> 8) & 0x0F) << 4))}},
    {6,
     10,
     {.offset_low =
          static_cast<uint8_t>(PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, manufacturer_data) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          6 | (((PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, manufacturer_data) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 BluetoothLERawAdvertisement::FIELDS_V3[4] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address)}},
    {2, 5, {.offset = PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, rssi)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address_type)}},
    {4, 9, {.offset = PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, data)}}};
const RepeatedFieldMetaV3 BluetoothLERawAdvertisementsResponse::REPEATED_FIELDS_V3[1] = {
    {1,
     10,
     {.offset_low =
          static_cast<uint8_t>(PROTO_FIELD_OFFSET(BluetoothLERawAdvertisementsResponse, advertisements) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          7 | (((PROTO_FIELD_OFFSET(BluetoothLERawAdvertisementsResponse, advertisements) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 BluetoothDeviceRequest::FIELDS_V3[4] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceRequest, request_type)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceRequest, has_address_type)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address_type)}}};
const FieldMetaV3 BluetoothDeviceConnectionResponse::FIELDS_V3[4] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, address)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, connected)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, mtu)}},
    {4, 1, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, error)}}};
const FieldMetaV3 BluetoothGATTGetServicesRequest::FIELDS_V3[1] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTGetServicesRequest, address)}}};
const FieldMetaV3 BluetoothGATTDescriptor::FIELDS_V3[1] = {
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, handle)}}};
const RepeatedFieldMetaV3 BluetoothGATTDescriptor::REPEATED_FIELDS_V3[1] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, uuid)}}};
const FieldMetaV3 BluetoothGATTCharacteristic::FIELDS_V3[2] = {
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, handle)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, properties)}}};
const RepeatedFieldMetaV3 BluetoothGATTCharacteristic::REPEATED_FIELDS_V3[2] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, uuid)}},
    {4,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, descriptors) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          8 | (((PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, descriptors) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 BluetoothGATTService::FIELDS_V3[1] = {
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTService, handle)}}};
const RepeatedFieldMetaV3 BluetoothGATTService::REPEATED_FIELDS_V3[2] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTService, uuid)}},
    {3,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(BluetoothGATTService, characteristics) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(9 | (((PROTO_FIELD_OFFSET(BluetoothGATTService, characteristics) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 BluetoothGATTGetServicesResponse::FIELDS_V3[1] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, address)}}};
const RepeatedFieldMetaV3 BluetoothGATTGetServicesResponse::REPEATED_FIELDS_V3[1] = {
    {2,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, services) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          10 | (((PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, services) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 BluetoothGATTGetServicesDoneResponse::FIELDS_V3[1] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTGetServicesDoneResponse, address)}}};
const FieldMetaV3 BluetoothGATTReadRequest::FIELDS_V3[2] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, handle)}}};
const FieldMetaV3 BluetoothGATTReadResponse::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, handle)}},
    {3, 9, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, data)}}};
const FieldMetaV3 BluetoothGATTWriteRequest::FIELDS_V3[4] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, handle)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, response)}},
    {4, 9, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, data)}}};
const FieldMetaV3 BluetoothGATTReadDescriptorRequest::FIELDS_V3[2] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, handle)}}};
const FieldMetaV3 BluetoothGATTWriteDescriptorRequest::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, handle)}},
    {3, 9, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, data)}}};
const FieldMetaV3 BluetoothGATTNotifyRequest::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, handle)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, enable)}}};
const FieldMetaV3 BluetoothGATTNotifyDataResponse::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, handle)}},
    {3, 9, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, data)}}};
const FieldMetaV3 BluetoothConnectionsFreeResponse::FIELDS_V3[2] = {
    {1, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, free)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, limit)}}};
const RepeatedFieldMetaV3 BluetoothConnectionsFreeResponse::REPEATED_FIELDS_V3[1] = {
    {3, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, allocated)}}};
const FieldMetaV3 BluetoothGATTErrorResponse::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, handle)}},
    {3, 1, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, error)}}};
const FieldMetaV3 BluetoothGATTWriteResponse::FIELDS_V3[2] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, handle)}}};
const FieldMetaV3 BluetoothGATTNotifyResponse::FIELDS_V3[2] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, address)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, handle)}}};
const FieldMetaV3 BluetoothDevicePairingResponse::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, address)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, paired)}},
    {3, 1, {.offset = PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, error)}}};
const FieldMetaV3 BluetoothDeviceUnpairingResponse::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, address)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, success)}},
    {3, 1, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, error)}}};
const FieldMetaV3 BluetoothDeviceClearCacheResponse::FIELDS_V3[3] = {
    {1, 4, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, address)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, success)}},
    {3, 1, {.offset = PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, error)}}};
const FieldMetaV3 BluetoothScannerStateResponse::FIELDS_V3[2] = {
    {1, 7, {.offset = PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, state)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, mode)}}};
const FieldMetaV3 BluetoothScannerSetModeRequest::FIELDS_V3[1] = {
    {1, 7, {.offset = PROTO_FIELD_OFFSET(BluetoothScannerSetModeRequest, mode)}}};
#endif
#ifdef USE_VOICE_ASSISTANT
const FieldMetaV3 SubscribeVoiceAssistantRequest::FIELDS_V3[2] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, subscribe)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, flags)}}};
const FieldMetaV3 VoiceAssistantAudioSettings::FIELDS_V3[3] = {
    {1, 2, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, noise_suppression_level)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, auto_gain)}},
    {3, 11, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, volume_multiplier)}}};
const FieldMetaV3 VoiceAssistantRequest::FIELDS_V3[5] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantRequest, start)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantRequest, conversation_id)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantRequest, flags)}},
    {4,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(VoiceAssistantRequest, audio_settings) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          105 | (((PROTO_FIELD_OFFSET(VoiceAssistantRequest, audio_settings) >> 8) & 0x0F) << 4))}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantRequest, wake_word_phrase)}}};
const FieldMetaV3 VoiceAssistantResponse::FIELDS_V3[2] = {
    {1, 2, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantResponse, port)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantResponse, error)}}};
const FieldMetaV3 VoiceAssistantEventData::FIELDS_V3[2] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantEventData, name)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantEventData, value)}}};
const FieldMetaV3 VoiceAssistantEventResponse::FIELDS_V3[1] = {
    {1, 7, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, event_type)}}};
const RepeatedFieldMetaV3 VoiceAssistantEventResponse::REPEATED_FIELDS_V3[1] = {
    {2,
     10,
     {.offset_low = static_cast<uint8_t>(PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, data) & 0xFF),
      .message_type_id =
          static_cast<uint8_t>(11 | (((PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, data) >> 8) & 0x0F) << 4))}}};
const FieldMetaV3 VoiceAssistantAudio::FIELDS_V3[2] = {
    {1, 9, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAudio, data)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAudio, end)}}};
const FieldMetaV3 VoiceAssistantTimerEventResponse::FIELDS_V3[6] = {
    {1, 7, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, event_type)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, timer_id)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, name)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, total_seconds)}},
    {5, 2, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, seconds_left)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, is_active)}}};
const FieldMetaV3 VoiceAssistantAnnounceRequest::FIELDS_V3[4] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, media_id)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, text)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, preannounce_media_id)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, start_conversation)}}};
const FieldMetaV3 VoiceAssistantAnnounceFinished::FIELDS_V3[1] = {
    {1, 0, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantAnnounceFinished, success)}}};
const FieldMetaV3 VoiceAssistantWakeWord::FIELDS_V3[2] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, id)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, wake_word)}}};
const RepeatedFieldMetaV3 VoiceAssistantWakeWord::REPEATED_FIELDS_V3[1] = {
    {3, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, trained_languages)}}};
const FieldMetaV3 VoiceAssistantConfigurationResponse::FIELDS_V3[1] = {
    {3, 2, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, max_active_wake_words)}}};
const RepeatedFieldMetaV3 VoiceAssistantConfigurationResponse::REPEATED_FIELDS_V3[2] = {
    {1,
     10,
     {.offset_low =
          static_cast<uint8_t>(PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, available_wake_words) & 0xFF),
      .message_type_id = static_cast<uint8_t>(
          12 | (((PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, available_wake_words) >> 8) & 0x0F) << 4))}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, active_wake_words)}}};
const RepeatedFieldMetaV3 VoiceAssistantSetConfiguration::REPEATED_FIELDS_V3[1] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(VoiceAssistantSetConfiguration, active_wake_words)}}};
#endif
#ifdef USE_ALARM_CONTROL_PANEL
const FieldMetaV3 ListEntitiesAlarmControlPanelResponse::FIELDS_V3[11] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, entity_category)}},
    {8, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, supported_features)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code)}},
    {10, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code_to_arm)}},
    {11, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, device_id)}}};
const FieldMetaV3 AlarmControlPanelStateResponse::FIELDS_V3[3] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, state)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, device_id)}}};
const FieldMetaV3 AlarmControlPanelCommandRequest::FIELDS_V3[3] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, command)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, code)}}};
#endif
#ifdef USE_TEXT
const FieldMetaV3 ListEntitiesTextResponse::FIELDS_V3[12] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, entity_category)}},
    {8, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, min_length)}},
    {9, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, max_length)}},
    {10, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, pattern)}},
    {11, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, mode)}},
    {12, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTextResponse, device_id)}}};
const FieldMetaV3 TextStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(TextStateResponse, key)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(TextStateResponse, state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(TextStateResponse, missing_state)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(TextStateResponse, device_id)}}};
const FieldMetaV3 TextCommandRequest::FIELDS_V3[2] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(TextCommandRequest, key)}},
    {2, 8, {.offset = PROTO_FIELD_OFFSET(TextCommandRequest, state)}}};
#endif
#ifdef USE_DATETIME_DATE
const FieldMetaV3 ListEntitiesDateResponse::FIELDS_V3[8] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, entity_category)}},
    {8, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateResponse, device_id)}}};
const FieldMetaV3 DateStateResponse::FIELDS_V3[6] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(DateStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(DateStateResponse, missing_state)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(DateStateResponse, year)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(DateStateResponse, month)}},
    {5, 2, {.offset = PROTO_FIELD_OFFSET(DateStateResponse, day)}},
    {6, 2, {.offset = PROTO_FIELD_OFFSET(DateStateResponse, device_id)}}};
const FieldMetaV3 DateCommandRequest::FIELDS_V3[4] = {{1, 12, {.offset = PROTO_FIELD_OFFSET(DateCommandRequest, key)}},
                                                      {2, 2, {.offset = PROTO_FIELD_OFFSET(DateCommandRequest, year)}},
                                                      {3, 2, {.offset = PROTO_FIELD_OFFSET(DateCommandRequest, month)}},
                                                      {4, 2, {.offset = PROTO_FIELD_OFFSET(DateCommandRequest, day)}}};
#endif
#ifdef USE_DATETIME_TIME
const FieldMetaV3 ListEntitiesTimeResponse::FIELDS_V3[8] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, entity_category)}},
    {8, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, device_id)}}};
const FieldMetaV3 TimeStateResponse::FIELDS_V3[6] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(TimeStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(TimeStateResponse, missing_state)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(TimeStateResponse, hour)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(TimeStateResponse, minute)}},
    {5, 2, {.offset = PROTO_FIELD_OFFSET(TimeStateResponse, second)}},
    {6, 2, {.offset = PROTO_FIELD_OFFSET(TimeStateResponse, device_id)}}};
const FieldMetaV3 TimeCommandRequest::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(TimeCommandRequest, key)}},
    {2, 2, {.offset = PROTO_FIELD_OFFSET(TimeCommandRequest, hour)}},
    {3, 2, {.offset = PROTO_FIELD_OFFSET(TimeCommandRequest, minute)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(TimeCommandRequest, second)}}};
#endif
#ifdef USE_EVENT
const FieldMetaV3 ListEntitiesEventResponse::FIELDS_V3[9] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, entity_category)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_class)}},
    {10, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_id)}}};
const RepeatedFieldMetaV3 ListEntitiesEventResponse::REPEATED_FIELDS_V3[1] = {
    {9, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesEventResponse, event_types)}}};
const FieldMetaV3 EventResponse::FIELDS_V3[3] = {{1, 12, {.offset = PROTO_FIELD_OFFSET(EventResponse, key)}},
                                                 {2, 8, {.offset = PROTO_FIELD_OFFSET(EventResponse, event_type)}},
                                                 {3, 2, {.offset = PROTO_FIELD_OFFSET(EventResponse, device_id)}}};
#endif
#ifdef USE_VALVE
const FieldMetaV3 ListEntitiesValveResponse::FIELDS_V3[12] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, entity_category)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_class)}},
    {9, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, assumed_state)}},
    {10, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_position)}},
    {11, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_stop)}},
    {12, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_id)}}};
const FieldMetaV3 ValveStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(ValveStateResponse, key)}},
    {2, 11, {.offset = PROTO_FIELD_OFFSET(ValveStateResponse, position)}},
    {3, 7, {.offset = PROTO_FIELD_OFFSET(ValveStateResponse, current_operation)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(ValveStateResponse, device_id)}}};
const FieldMetaV3 ValveCommandRequest::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(ValveCommandRequest, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(ValveCommandRequest, has_position)}},
    {3, 11, {.offset = PROTO_FIELD_OFFSET(ValveCommandRequest, position)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(ValveCommandRequest, stop)}}};
#endif
#ifdef USE_DATETIME_DATETIME
const FieldMetaV3 ListEntitiesDateTimeResponse::FIELDS_V3[8] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, entity_category)}},
    {8, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, device_id)}}};
const FieldMetaV3 DateTimeStateResponse::FIELDS_V3[4] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(DateTimeStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(DateTimeStateResponse, missing_state)}},
    {3, 12, {.offset = PROTO_FIELD_OFFSET(DateTimeStateResponse, epoch_seconds)}},
    {4, 2, {.offset = PROTO_FIELD_OFFSET(DateTimeStateResponse, device_id)}}};
const FieldMetaV3 DateTimeCommandRequest::FIELDS_V3[2] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(DateTimeCommandRequest, key)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(DateTimeCommandRequest, epoch_seconds)}}};
#endif
#ifdef USE_UPDATE
const FieldMetaV3 ListEntitiesUpdateResponse::FIELDS_V3[9] = {
    {1, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, object_id)}},
    {2, 12, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, key)}},
    {3, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, name)}},
    {4, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, unique_id)}},
    {5, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, icon)}},
    {6, 0, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, disabled_by_default)}},
    {7, 7, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, entity_category)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_class)}},
    {9, 2, {.offset = PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_id)}}};
const FieldMetaV3 UpdateStateResponse::FIELDS_V3[11] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, key)}},
    {2, 0, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, missing_state)}},
    {3, 0, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, in_progress)}},
    {4, 0, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, has_progress)}},
    {5, 11, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, progress)}},
    {6, 8, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, current_version)}},
    {7, 8, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, latest_version)}},
    {8, 8, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, title)}},
    {9, 8, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, release_summary)}},
    {10, 8, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, release_url)}},
    {11, 2, {.offset = PROTO_FIELD_OFFSET(UpdateStateResponse, device_id)}}};
const FieldMetaV3 UpdateCommandRequest::FIELDS_V3[2] = {
    {1, 12, {.offset = PROTO_FIELD_OFFSET(UpdateCommandRequest, key)}},
    {2, 7, {.offset = PROTO_FIELD_OFFSET(UpdateCommandRequest, command)}}};
#endif

// Message handler registries for V3
const MessageHandler MESSAGE_HANDLERS[141] = {
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {&encode_message_field<AreaInfo>, &size_message_field<AreaInfo>, &decode_message_field<AreaInfo>},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
#ifdef USE_VOICE_ASSISTANT
    {&encode_message_field<VoiceAssistantAudioSettings>, &size_message_field<VoiceAssistantAudioSettings>,
     &decode_message_field<VoiceAssistantAudioSettings>},
#else
    {nullptr, nullptr, nullptr},
#endif
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr},
    {nullptr, nullptr, nullptr}};
const size_t MESSAGE_HANDLER_COUNT = 141;

const RepeatedMessageHandler REPEATED_MESSAGE_HANDLERS[13] = {
    {&encode_repeated_message_field<DeviceInfo>, &size_repeated_message_field<DeviceInfo>,
     &decode_repeated_message_field<DeviceInfo>},
    {&encode_repeated_message_field<AreaInfo>, &size_repeated_message_field<AreaInfo>,
     &decode_repeated_message_field<AreaInfo>},
    {&encode_repeated_message_field<HomeassistantServiceMap>, &size_repeated_message_field<HomeassistantServiceMap>,
     &decode_repeated_message_field<HomeassistantServiceMap>},
    {&encode_repeated_message_field<ListEntitiesServicesArgument>,
     &size_repeated_message_field<ListEntitiesServicesArgument>,
     &decode_repeated_message_field<ListEntitiesServicesArgument>},
    {&encode_repeated_message_field<ExecuteServiceArgument>, &size_repeated_message_field<ExecuteServiceArgument>,
     &decode_repeated_message_field<ExecuteServiceArgument>},
#ifdef USE_MEDIA_PLAYER
    {&encode_repeated_message_field<MediaPlayerSupportedFormat>,
     &size_repeated_message_field<MediaPlayerSupportedFormat>,
     &decode_repeated_message_field<MediaPlayerSupportedFormat>},
#else
    {nullptr, nullptr, nullptr},
#endif
#ifdef USE_BLUETOOTH_PROXY
    {&encode_repeated_message_field<BluetoothServiceData>, &size_repeated_message_field<BluetoothServiceData>,
     &decode_repeated_message_field<BluetoothServiceData>},
#else
    {nullptr, nullptr, nullptr},
#endif
#ifdef USE_BLUETOOTH_PROXY
    {&encode_repeated_message_field<BluetoothLERawAdvertisement>,
     &size_repeated_message_field<BluetoothLERawAdvertisement>,
     &decode_repeated_message_field<BluetoothLERawAdvertisement>},
#else
    {nullptr, nullptr, nullptr},
#endif
#ifdef USE_BLUETOOTH_PROXY
    {&encode_repeated_message_field<BluetoothGATTDescriptor>, &size_repeated_message_field<BluetoothGATTDescriptor>,
     &decode_repeated_message_field<BluetoothGATTDescriptor>},
#else
    {nullptr, nullptr, nullptr},
#endif
#ifdef USE_BLUETOOTH_PROXY
    {&encode_repeated_message_field<BluetoothGATTCharacteristic>,
     &size_repeated_message_field<BluetoothGATTCharacteristic>,
     &decode_repeated_message_field<BluetoothGATTCharacteristic>},
#else
    {nullptr, nullptr, nullptr},
#endif
#ifdef USE_BLUETOOTH_PROXY
    {&encode_repeated_message_field<BluetoothGATTService>, &size_repeated_message_field<BluetoothGATTService>,
     &decode_repeated_message_field<BluetoothGATTService>},
#else
    {nullptr, nullptr, nullptr},
#endif
#ifdef USE_VOICE_ASSISTANT
    {&encode_repeated_message_field<VoiceAssistantEventData>, &size_repeated_message_field<VoiceAssistantEventData>,
     &decode_repeated_message_field<VoiceAssistantEventData>},
#else
    {nullptr, nullptr, nullptr},
#endif
#ifdef USE_VOICE_ASSISTANT
    {&encode_repeated_message_field<VoiceAssistantWakeWord>, &size_repeated_message_field<VoiceAssistantWakeWord>,
     &decode_repeated_message_field<VoiceAssistantWakeWord>},
#else
    {nullptr, nullptr, nullptr},
#endif
};
const size_t REPEATED_MESSAGE_HANDLER_COUNT = 13;

}  // namespace api
}  // namespace esphome
