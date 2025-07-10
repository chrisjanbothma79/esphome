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
const FieldMeta HelloRequest::FIELDS[3] = {{1,
                                            PROTO_FIELD_OFFSET(HelloRequest, client_info),
                                            &encode_string_field,
                                            &size_string_field,
                                            false,
                                            2,
                                            1,
                                            {.decode_length = &decode_string_field}},
                                           {2,
                                            PROTO_FIELD_OFFSET(HelloRequest, api_version_major),
                                            &encode_uint32_field,
                                            &size_uint32_field,
                                            false,
                                            0,
                                            1,
                                            {.decode_varint = &decode_uint32_field}},
                                           {3,
                                            PROTO_FIELD_OFFSET(HelloRequest, api_version_minor),
                                            &encode_uint32_field,
                                            &size_uint32_field,
                                            false,
                                            0,
                                            1,
                                            {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 HelloRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(HelloRequest, client_info), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(HelloRequest, api_version_major), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(HelloRequest, api_version_minor), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta HelloResponse::FIELDS[4] = {{1,
                                             PROTO_FIELD_OFFSET(HelloResponse, api_version_major),
                                             &encode_uint32_field,
                                             &size_uint32_field,
                                             false,
                                             0,
                                             1,
                                             {.decode_varint = &decode_uint32_field}},
                                            {2,
                                             PROTO_FIELD_OFFSET(HelloResponse, api_version_minor),
                                             &encode_uint32_field,
                                             &size_uint32_field,
                                             false,
                                             0,
                                             1,
                                             {.decode_varint = &decode_uint32_field}},
                                            {3,
                                             PROTO_FIELD_OFFSET(HelloResponse, server_info),
                                             &encode_string_field,
                                             &size_string_field,
                                             false,
                                             2,
                                             1,
                                             {.decode_length = &decode_string_field}},
                                            {4,
                                             PROTO_FIELD_OFFSET(HelloResponse, name),
                                             &encode_string_field,
                                             &size_string_field,
                                             false,
                                             2,
                                             1,
                                             {.decode_length = &decode_string_field}}};
const FieldMetaV2 HelloResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(HelloResponse, api_version_major), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(HelloResponse, api_version_minor), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(HelloResponse, server_info), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(HelloResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const FieldMeta ConnectRequest::FIELDS[1] = {{1,
                                              PROTO_FIELD_OFFSET(ConnectRequest, password),
                                              &encode_string_field,
                                              &size_string_field,
                                              false,
                                              2,
                                              1,
                                              {.decode_length = &decode_string_field}}};
const FieldMetaV2 ConnectRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ConnectRequest, password), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const FieldMeta ConnectResponse::FIELDS[1] = {{1,
                                               PROTO_FIELD_OFFSET(ConnectResponse, invalid_password),
                                               &encode_bool_field,
                                               &size_bool_field,
                                               false,
                                               0,
                                               1,
                                               {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 ConnectResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ConnectResponse, invalid_password), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta AreaInfo::FIELDS[2] = {{1,
                                        PROTO_FIELD_OFFSET(AreaInfo, area_id),
                                        &encode_uint32_field,
                                        &size_uint32_field,
                                        false,
                                        0,
                                        1,
                                        {.decode_varint = &decode_uint32_field}},
                                       {2,
                                        PROTO_FIELD_OFFSET(AreaInfo, name),
                                        &encode_string_field,
                                        &size_string_field,
                                        false,
                                        2,
                                        1,
                                        {.decode_length = &decode_string_field}}};
const FieldMetaV2 AreaInfo::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(AreaInfo, area_id), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(AreaInfo, name), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const FieldMeta DeviceInfo::FIELDS[3] = {{1,
                                          PROTO_FIELD_OFFSET(DeviceInfo, device_id),
                                          &encode_uint32_field,
                                          &size_uint32_field,
                                          false,
                                          0,
                                          1,
                                          {.decode_varint = &decode_uint32_field}},
                                         {2,
                                          PROTO_FIELD_OFFSET(DeviceInfo, name),
                                          &encode_string_field,
                                          &size_string_field,
                                          false,
                                          2,
                                          1,
                                          {.decode_length = &decode_string_field}},
                                         {3,
                                          PROTO_FIELD_OFFSET(DeviceInfo, area_id),
                                          &encode_uint32_field,
                                          &size_uint32_field,
                                          false,
                                          0,
                                          1,
                                          {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 DeviceInfo::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(DeviceInfo, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(DeviceInfo, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(DeviceInfo, area_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta DeviceInfoResponse::FIELDS[19] = {
    {1,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, uses_password),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {2,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, mac_address),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, esphome_version),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, compilation_time),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, model),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, has_deep_sleep),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, project_name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, project_version),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, webserver_port),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {11,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_bluetooth_proxy_version),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {15,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_proxy_feature_flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {12,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, manufacturer),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {13,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, friendly_name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {14,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_voice_assistant_version),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {17,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, voice_assistant_feature_flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     2,
     {.decode_varint = &decode_uint32_field}},
    {16,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, suggested_area),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     2,
     {.decode_length = &decode_string_field}},
    {18,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_mac_address),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     2,
     {.decode_length = &decode_string_field}},
    {19,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, api_encryption_supported),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}}};
const RepeatedFieldMeta DeviceInfoResponse::REPEATED_FIELDS[2] = {
    {20,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, devices),
     &encode_repeated_message_field<DeviceInfo>,
     &size_repeated_message_field<DeviceInfo>,
     2,
     2,
     {.decode_length = &decode_repeated_message_field<DeviceInfo>}},
    {21,
     PROTO_FIELD_OFFSET(DeviceInfoResponse, areas),
     &encode_repeated_message_field<AreaInfo>,
     &size_repeated_message_field<AreaInfo>,
     2,
     2,
     {.decode_length = &decode_repeated_message_field<AreaInfo>}}};
const FieldMetaV2 DeviceInfoResponse::FIELDS_V2[20] = {
    {1, PROTO_FIELD_OFFSET(DeviceInfoResponse, uses_password), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(DeviceInfoResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(DeviceInfoResponse, mac_address), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(DeviceInfoResponse, esphome_version), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(DeviceInfoResponse, compilation_time), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(DeviceInfoResponse, model), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(DeviceInfoResponse, has_deep_sleep), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(DeviceInfoResponse, project_name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(DeviceInfoResponse, project_version), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(DeviceInfoResponse, webserver_port), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_bluetooth_proxy_version), ProtoFieldType::TYPE_UINT32, false, 1,
     0},
    {15, PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_proxy_feature_flags), ProtoFieldType::TYPE_UINT32, false, 1,
     0},
    {12, PROTO_FIELD_OFFSET(DeviceInfoResponse, manufacturer), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(DeviceInfoResponse, friendly_name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {14, PROTO_FIELD_OFFSET(DeviceInfoResponse, legacy_voice_assistant_version), ProtoFieldType::TYPE_UINT32, false, 1,
     0},
    {17, PROTO_FIELD_OFFSET(DeviceInfoResponse, voice_assistant_feature_flags), ProtoFieldType::TYPE_UINT32, false, 2,
     0},
    {16, PROTO_FIELD_OFFSET(DeviceInfoResponse, suggested_area), ProtoFieldType::TYPE_STRING, false, 2, 0},
    {18, PROTO_FIELD_OFFSET(DeviceInfoResponse, bluetooth_mac_address), ProtoFieldType::TYPE_STRING, false, 2, 0},
    {19, PROTO_FIELD_OFFSET(DeviceInfoResponse, api_encryption_supported), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {22, PROTO_FIELD_OFFSET(DeviceInfoResponse, area), ProtoFieldType::TYPE_MESSAGE, false, 2, 10}};
const RepeatedFieldMetaV2 DeviceInfoResponse::REPEATED_FIELDS_V2[2] = {
    {20, PROTO_FIELD_OFFSET(DeviceInfoResponse, devices), ProtoFieldType::TYPE_MESSAGE, 2, 11},
    {21, PROTO_FIELD_OFFSET(DeviceInfoResponse, areas), ProtoFieldType::TYPE_MESSAGE, 2, 10}};
#ifdef USE_BINARY_SENSOR
const FieldMeta ListEntitiesBinarySensorResponse::FIELDS[10] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, is_status_binary_sensor),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesBinarySensorResponse::FIELDS_V2[10] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, is_status_binary_sensor), ProtoFieldType::TYPE_BOOL, false,
     1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1,
     0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesBinarySensorResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta BinarySensorStateResponse::FIELDS[4] = {{1,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, key),
                                                         &encode_fixed32_field,
                                                         &size_fixed32_field,
                                                         false,
                                                         5,
                                                         1,
                                                         {.decode_32bit = &decode_fixed32_field}},
                                                        {2,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, state),
                                                         &encode_bool_field,
                                                         &size_bool_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_bool_field}},
                                                        {3,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, missing_state),
                                                         &encode_bool_field,
                                                         &size_bool_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_bool_field}},
                                                        {4,
                                                         PROTO_FIELD_OFFSET(BinarySensorStateResponse, device_id),
                                                         &encode_uint32_field,
                                                         &size_uint32_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 BinarySensorStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BinarySensorStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BinarySensorStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BinarySensorStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(BinarySensorStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
#endif
#ifdef USE_COVER
const FieldMeta ListEntitiesCoverResponse::FIELDS[13] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_position),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_tilt),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_stop),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesCoverResponse::FIELDS_V2[13] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_position), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_tilt), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, supports_stop), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(ListEntitiesCoverResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta CoverStateResponse::FIELDS[6] = {{1,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, legacy_state),
                                                  &encode_enum_field<enums::LegacyCoverState>,
                                                  &size_enum_field<enums::LegacyCoverState>,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_enum_field<enums::LegacyCoverState>}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, position),
                                                  &encode_float_field,
                                                  &size_float_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_float_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, tilt),
                                                  &encode_float_field,
                                                  &size_float_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_float_field}},
                                                 {5,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, current_operation),
                                                  &encode_enum_field<enums::CoverOperation>,
                                                  &size_enum_field<enums::CoverOperation>,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_enum_field<enums::CoverOperation>}},
                                                 {6,
                                                  PROTO_FIELD_OFFSET(CoverStateResponse, device_id),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 CoverStateResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(CoverStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(CoverStateResponse, legacy_state), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(CoverStateResponse, position), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(CoverStateResponse, tilt), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(CoverStateResponse, current_operation), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(CoverStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta CoverCommandRequest::FIELDS[8] = {{1,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, has_legacy_command),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, legacy_command),
                                                   &encode_enum_field<enums::LegacyCoverCommand>,
                                                   &size_enum_field<enums::LegacyCoverCommand>,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_enum_field<enums::LegacyCoverCommand>}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, has_position),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {5,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, position),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {6,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, has_tilt),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {7,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, tilt),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {8,
                                                   PROTO_FIELD_OFFSET(CoverCommandRequest, stop),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 CoverCommandRequest::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(CoverCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(CoverCommandRequest, has_legacy_command), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(CoverCommandRequest, legacy_command), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(CoverCommandRequest, has_position), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(CoverCommandRequest, position), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(CoverCommandRequest, has_tilt), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(CoverCommandRequest, tilt), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(CoverCommandRequest, stop), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
#endif
#ifdef USE_FAN
const FieldMeta ListEntitiesFanResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_oscillation),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_speed),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_direction),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_speed_count),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_int32_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesFanResponse::REPEATED_FIELDS[1] = {
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_preset_modes),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 ListEntitiesFanResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_oscillation), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_speed), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supports_direction), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_speed_count), ProtoFieldType::TYPE_INT32, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 ListEntitiesFanResponse::REPEATED_FIELDS_V2[1] = {
    {12, PROTO_FIELD_OFFSET(ListEntitiesFanResponse, supported_preset_modes), ProtoFieldType::TYPE_STRING, 1, 0}};
const FieldMeta FanStateResponse::FIELDS[8] = {{1,
                                                PROTO_FIELD_OFFSET(FanStateResponse, key),
                                                &encode_fixed32_field,
                                                &size_fixed32_field,
                                                false,
                                                5,
                                                1,
                                                {.decode_32bit = &decode_fixed32_field}},
                                               {2,
                                                PROTO_FIELD_OFFSET(FanStateResponse, state),
                                                &encode_bool_field,
                                                &size_bool_field,
                                                false,
                                                0,
                                                1,
                                                {.decode_varint = &decode_bool_field}},
                                               {3,
                                                PROTO_FIELD_OFFSET(FanStateResponse, oscillating),
                                                &encode_bool_field,
                                                &size_bool_field,
                                                false,
                                                0,
                                                1,
                                                {.decode_varint = &decode_bool_field}},
                                               {4,
                                                PROTO_FIELD_OFFSET(FanStateResponse, speed),
                                                &encode_enum_field<enums::FanSpeed>,
                                                &size_enum_field<enums::FanSpeed>,
                                                false,
                                                0,
                                                1,
                                                {.decode_varint = &decode_enum_field<enums::FanSpeed>}},
                                               {5,
                                                PROTO_FIELD_OFFSET(FanStateResponse, direction),
                                                &encode_enum_field<enums::FanDirection>,
                                                &size_enum_field<enums::FanDirection>,
                                                false,
                                                0,
                                                1,
                                                {.decode_varint = &decode_enum_field<enums::FanDirection>}},
                                               {6,
                                                PROTO_FIELD_OFFSET(FanStateResponse, speed_level),
                                                &encode_int32_field,
                                                &size_int32_field,
                                                false,
                                                0,
                                                1,
                                                {.decode_varint = &decode_int32_field}},
                                               {7,
                                                PROTO_FIELD_OFFSET(FanStateResponse, preset_mode),
                                                &encode_string_field,
                                                &size_string_field,
                                                false,
                                                2,
                                                1,
                                                {.decode_length = &decode_string_field}},
                                               {8,
                                                PROTO_FIELD_OFFSET(FanStateResponse, device_id),
                                                &encode_uint32_field,
                                                &size_uint32_field,
                                                false,
                                                0,
                                                1,
                                                {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 FanStateResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(FanStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(FanStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(FanStateResponse, oscillating), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(FanStateResponse, speed), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(FanStateResponse, direction), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(FanStateResponse, speed_level), ProtoFieldType::TYPE_INT32, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(FanStateResponse, preset_mode), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(FanStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta FanCommandRequest::FIELDS[13] = {{1,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_state),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, state),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_speed),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {5,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, speed),
                                                  &encode_enum_field<enums::FanSpeed>,
                                                  &size_enum_field<enums::FanSpeed>,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_enum_field<enums::FanSpeed>}},
                                                 {6,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_oscillating),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {7,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, oscillating),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {8,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_direction),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {9,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, direction),
                                                  &encode_enum_field<enums::FanDirection>,
                                                  &size_enum_field<enums::FanDirection>,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_enum_field<enums::FanDirection>}},
                                                 {10,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_speed_level),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {11,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, speed_level),
                                                  &encode_int32_field,
                                                  &size_int32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_int32_field}},
                                                 {12,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, has_preset_mode),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {13,
                                                  PROTO_FIELD_OFFSET(FanCommandRequest, preset_mode),
                                                  &encode_string_field,
                                                  &size_string_field,
                                                  false,
                                                  2,
                                                  1,
                                                  {.decode_length = &decode_string_field}}};
const FieldMetaV2 FanCommandRequest::FIELDS_V2[13] = {
    {1, PROTO_FIELD_OFFSET(FanCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(FanCommandRequest, has_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(FanCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(FanCommandRequest, has_speed), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(FanCommandRequest, speed), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(FanCommandRequest, has_oscillating), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(FanCommandRequest, oscillating), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(FanCommandRequest, has_direction), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(FanCommandRequest, direction), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(FanCommandRequest, has_speed_level), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(FanCommandRequest, speed_level), ProtoFieldType::TYPE_INT32, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(FanCommandRequest, has_preset_mode), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(FanCommandRequest, preset_mode), ProtoFieldType::TYPE_STRING, false, 1, 0}};
#endif
#ifdef USE_LIGHT
const FieldMeta ListEntitiesLightResponse::FIELDS[14] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_brightness),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_rgb),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_white_value),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_color_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, min_mireds),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, max_mireds),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {14,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {15,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {16,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     2,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesLightResponse::REPEATED_FIELDS[2] = {
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, supported_color_modes),
     &encode_repeated_enum_field<enums::ColorMode>,
     &size_repeated_enum_field<enums::ColorMode>,
     1,
     0,
     {.decode_varint = &decode_repeated_enum_field<enums::ColorMode>}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesLightResponse, effects),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 ListEntitiesLightResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_brightness), ProtoFieldType::TYPE_BOOL, false, 1,
     0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_rgb), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_white_value), ProtoFieldType::TYPE_BOOL, false, 1,
     0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, legacy_supports_color_temperature), ProtoFieldType::TYPE_BOOL,
     false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, min_mireds), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, max_mireds), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {14, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {15, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {16, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 2, 0}};
const RepeatedFieldMetaV2 ListEntitiesLightResponse::REPEATED_FIELDS_V2[2] = {
    {12, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, supported_color_modes), ProtoFieldType::TYPE_ENUM, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesLightResponse, effects), ProtoFieldType::TYPE_STRING, 1, 0}};
const FieldMeta LightStateResponse::FIELDS[14] = {{1,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, brightness),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {11,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, color_mode),
                                                   &encode_enum_field<enums::ColorMode>,
                                                   &size_enum_field<enums::ColorMode>,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_enum_field<enums::ColorMode>}},
                                                  {10,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, color_brightness),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, red),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {5,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, green),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {6,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, blue),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {7,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, white),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {8,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, color_temperature),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {12,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, cold_white),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {13,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, warm_white),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {9,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, effect),
                                                   &encode_string_field,
                                                   &size_string_field,
                                                   false,
                                                   2,
                                                   1,
                                                   {.decode_length = &decode_string_field}},
                                                  {14,
                                                   PROTO_FIELD_OFFSET(LightStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 LightStateResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(LightStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(LightStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(LightStateResponse, brightness), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(LightStateResponse, color_mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(LightStateResponse, color_brightness), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(LightStateResponse, red), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(LightStateResponse, green), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(LightStateResponse, blue), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(LightStateResponse, white), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(LightStateResponse, color_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(LightStateResponse, cold_white), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(LightStateResponse, warm_white), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(LightStateResponse, effect), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {14, PROTO_FIELD_OFFSET(LightStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta LightCommandRequest::FIELDS[27] = {{1,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {3,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {4,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_brightness),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {5,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, brightness),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {22,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_color_mode),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {23,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, color_mode),
                                                    &encode_enum_field<enums::ColorMode>,
                                                    &size_enum_field<enums::ColorMode>,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_enum_field<enums::ColorMode>}},
                                                   {20,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_color_brightness),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {21,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, color_brightness),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    2,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {6,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_rgb),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {7,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, red),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {8,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, green),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {9,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, blue),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {10,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_white),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {11,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, white),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {12,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_color_temperature),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {13,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, color_temperature),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {24,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_cold_white),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {25,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, cold_white),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    2,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {26,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_warm_white),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {27,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, warm_white),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    2,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {14,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_transition_length),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {15,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, transition_length),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_uint32_field}},
                                                   {16,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_flash_length),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {17,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, flash_length),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_uint32_field}},
                                                   {18,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, has_effect),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    2,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {19,
                                                    PROTO_FIELD_OFFSET(LightCommandRequest, effect),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    2,
                                                    {.decode_length = &decode_string_field}}};
const FieldMetaV2 LightCommandRequest::FIELDS_V2[27] = {
    {1, PROTO_FIELD_OFFSET(LightCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(LightCommandRequest, has_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(LightCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(LightCommandRequest, has_brightness), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(LightCommandRequest, brightness), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {22, PROTO_FIELD_OFFSET(LightCommandRequest, has_color_mode), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {23, PROTO_FIELD_OFFSET(LightCommandRequest, color_mode), ProtoFieldType::TYPE_ENUM, false, 2, 0},
    {20, PROTO_FIELD_OFFSET(LightCommandRequest, has_color_brightness), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {21, PROTO_FIELD_OFFSET(LightCommandRequest, color_brightness), ProtoFieldType::TYPE_FLOAT, false, 2, 0},
    {6, PROTO_FIELD_OFFSET(LightCommandRequest, has_rgb), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(LightCommandRequest, red), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(LightCommandRequest, green), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(LightCommandRequest, blue), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(LightCommandRequest, has_white), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(LightCommandRequest, white), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(LightCommandRequest, has_color_temperature), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(LightCommandRequest, color_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {24, PROTO_FIELD_OFFSET(LightCommandRequest, has_cold_white), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {25, PROTO_FIELD_OFFSET(LightCommandRequest, cold_white), ProtoFieldType::TYPE_FLOAT, false, 2, 0},
    {26, PROTO_FIELD_OFFSET(LightCommandRequest, has_warm_white), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {27, PROTO_FIELD_OFFSET(LightCommandRequest, warm_white), ProtoFieldType::TYPE_FLOAT, false, 2, 0},
    {14, PROTO_FIELD_OFFSET(LightCommandRequest, has_transition_length), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {15, PROTO_FIELD_OFFSET(LightCommandRequest, transition_length), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {16, PROTO_FIELD_OFFSET(LightCommandRequest, has_flash_length), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {17, PROTO_FIELD_OFFSET(LightCommandRequest, flash_length), ProtoFieldType::TYPE_UINT32, false, 2, 0},
    {18, PROTO_FIELD_OFFSET(LightCommandRequest, has_effect), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {19, PROTO_FIELD_OFFSET(LightCommandRequest, effect), ProtoFieldType::TYPE_STRING, false, 2, 0}};
#endif
#ifdef USE_SENSOR
const FieldMeta ListEntitiesSensorResponse::FIELDS[14] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unit_of_measurement),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, accuracy_decimals),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_int32_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, force_update),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, state_class),
     &encode_enum_field<enums::SensorStateClass>,
     &size_enum_field<enums::SensorStateClass>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::SensorStateClass>}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, legacy_last_reset_type),
     &encode_enum_field<enums::SensorLastResetType>,
     &size_enum_field<enums::SensorLastResetType>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::SensorLastResetType>}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {14,
     PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesSensorResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, unit_of_measurement), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, accuracy_decimals), ProtoFieldType::TYPE_INT32, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, force_update), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, state_class), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, legacy_last_reset_type), ProtoFieldType::TYPE_ENUM, false, 1,
     0},
    {12, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {14, PROTO_FIELD_OFFSET(ListEntitiesSensorResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta SensorStateResponse::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, state),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, missing_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(SensorStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 SensorStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(SensorStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SensorStateResponse, state), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(SensorStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(SensorStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
#endif
#ifdef USE_SWITCH
const FieldMeta ListEntitiesSwitchResponse::FIELDS[10] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesSwitchResponse::FIELDS_V2[10] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesSwitchResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta SwitchStateResponse::FIELDS[3] = {{1,
                                                   PROTO_FIELD_OFFSET(SwitchStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SwitchStateResponse, state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SwitchStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 SwitchStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SwitchStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SwitchStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(SwitchStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta SwitchCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(SwitchCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(SwitchCommandRequest, state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 SwitchCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SwitchCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SwitchCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
#endif
#ifdef USE_TEXT_SENSOR
const FieldMeta ListEntitiesTextSensorResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesTextSensorResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1,
     0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesTextSensorResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta TextSensorStateResponse::FIELDS[4] = {{1,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, key),
                                                       &encode_fixed32_field,
                                                       &size_fixed32_field,
                                                       false,
                                                       5,
                                                       1,
                                                       {.decode_32bit = &decode_fixed32_field}},
                                                      {2,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, state),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       1,
                                                       {.decode_length = &decode_string_field}},
                                                      {3,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, missing_state),
                                                       &encode_bool_field,
                                                       &size_bool_field,
                                                       false,
                                                       0,
                                                       1,
                                                       {.decode_varint = &decode_bool_field}},
                                                      {4,
                                                       PROTO_FIELD_OFFSET(TextSensorStateResponse, device_id),
                                                       &encode_uint32_field,
                                                       &size_uint32_field,
                                                       false,
                                                       0,
                                                       1,
                                                       {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 TextSensorStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(TextSensorStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(TextSensorStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(TextSensorStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(TextSensorStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
#endif
const FieldMeta SubscribeLogsRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(SubscribeLogsRequest, level),
                                                    &encode_enum_field<enums::LogLevel>,
                                                    &size_enum_field<enums::LogLevel>,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_enum_field<enums::LogLevel>}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(SubscribeLogsRequest, dump_config),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 SubscribeLogsRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SubscribeLogsRequest, level), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SubscribeLogsRequest, dump_config), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta SubscribeLogsResponse::FIELDS[3] = {{1,
                                                     PROTO_FIELD_OFFSET(SubscribeLogsResponse, level),
                                                     &encode_enum_field<enums::LogLevel>,
                                                     &size_enum_field<enums::LogLevel>,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_enum_field<enums::LogLevel>}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(SubscribeLogsResponse, message),
                                                     &encode_bytes_field,
                                                     &size_bytes_field,
                                                     false,
                                                     2,
                                                     1,
                                                     {.decode_length = &decode_bytes_field}},
                                                    {4,
                                                     PROTO_FIELD_OFFSET(SubscribeLogsResponse, send_failed),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 SubscribeLogsResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SubscribeLogsResponse, level), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(SubscribeLogsResponse, message), ProtoFieldType::TYPE_BYTES, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(SubscribeLogsResponse, send_failed), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
#ifdef USE_API_NOISE
const FieldMeta NoiseEncryptionSetKeyRequest::FIELDS[1] = {{1,
                                                            PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyRequest, key),
                                                            &encode_bytes_field,
                                                            &size_bytes_field,
                                                            false,
                                                            2,
                                                            1,
                                                            {.decode_length = &decode_bytes_field}}};
const FieldMetaV2 NoiseEncryptionSetKeyRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyRequest, key), ProtoFieldType::TYPE_BYTES, false, 1, 0}};
const FieldMeta NoiseEncryptionSetKeyResponse::FIELDS[1] = {{1,
                                                             PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyResponse, success),
                                                             &encode_bool_field,
                                                             &size_bool_field,
                                                             false,
                                                             0,
                                                             1,
                                                             {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 NoiseEncryptionSetKeyResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(NoiseEncryptionSetKeyResponse, success), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
#endif
const FieldMeta HomeassistantServiceMap::FIELDS[2] = {{1,
                                                       PROTO_FIELD_OFFSET(HomeassistantServiceMap, key),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       1,
                                                       {.decode_length = &decode_string_field}},
                                                      {2,
                                                       PROTO_FIELD_OFFSET(HomeassistantServiceMap, value),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       1,
                                                       {.decode_length = &decode_string_field}}};
const FieldMetaV2 HomeassistantServiceMap::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(HomeassistantServiceMap, key), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(HomeassistantServiceMap, value), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const FieldMeta HomeassistantServiceResponse::FIELDS[2] = {{1,
                                                            PROTO_FIELD_OFFSET(HomeassistantServiceResponse, service),
                                                            &encode_string_field,
                                                            &size_string_field,
                                                            false,
                                                            2,
                                                            1,
                                                            {.decode_length = &decode_string_field}},
                                                           {5,
                                                            PROTO_FIELD_OFFSET(HomeassistantServiceResponse, is_event),
                                                            &encode_bool_field,
                                                            &size_bool_field,
                                                            false,
                                                            0,
                                                            1,
                                                            {.decode_varint = &decode_bool_field}}};
const RepeatedFieldMeta HomeassistantServiceResponse::REPEATED_FIELDS[3] = {
    {2,
     PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data),
     &encode_repeated_message_field<HomeassistantServiceMap>,
     &size_repeated_message_field<HomeassistantServiceMap>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<HomeassistantServiceMap>}},
    {3,
     PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data_template),
     &encode_repeated_message_field<HomeassistantServiceMap>,
     &size_repeated_message_field<HomeassistantServiceMap>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<HomeassistantServiceMap>}},
    {4,
     PROTO_FIELD_OFFSET(HomeassistantServiceResponse, variables),
     &encode_repeated_message_field<HomeassistantServiceMap>,
     &size_repeated_message_field<HomeassistantServiceMap>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<HomeassistantServiceMap>}}};
const FieldMetaV2 HomeassistantServiceResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, service), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, is_event), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const RepeatedFieldMetaV2 HomeassistantServiceResponse::REPEATED_FIELDS_V2[3] = {
    {2, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data), ProtoFieldType::TYPE_MESSAGE, 1, 39},
    {3, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, data_template), ProtoFieldType::TYPE_MESSAGE, 1, 39},
    {4, PROTO_FIELD_OFFSET(HomeassistantServiceResponse, variables), ProtoFieldType::TYPE_MESSAGE, 1, 39}};
const FieldMeta SubscribeHomeAssistantStateResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, entity_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, attribute),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, once),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 SubscribeHomeAssistantStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, entity_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, attribute), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(SubscribeHomeAssistantStateResponse, once), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta HomeAssistantStateResponse::FIELDS[3] = {{1,
                                                          PROTO_FIELD_OFFSET(HomeAssistantStateResponse, entity_id),
                                                          &encode_string_field,
                                                          &size_string_field,
                                                          false,
                                                          2,
                                                          1,
                                                          {.decode_length = &decode_string_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(HomeAssistantStateResponse, state),
                                                          &encode_string_field,
                                                          &size_string_field,
                                                          false,
                                                          2,
                                                          1,
                                                          {.decode_length = &decode_string_field}},
                                                         {3,
                                                          PROTO_FIELD_OFFSET(HomeAssistantStateResponse, attribute),
                                                          &encode_string_field,
                                                          &size_string_field,
                                                          false,
                                                          2,
                                                          1,
                                                          {.decode_length = &decode_string_field}}};
const FieldMetaV2 HomeAssistantStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(HomeAssistantStateResponse, entity_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(HomeAssistantStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(HomeAssistantStateResponse, attribute), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const FieldMeta GetTimeResponse::FIELDS[1] = {{1,
                                               PROTO_FIELD_OFFSET(GetTimeResponse, epoch_seconds),
                                               &encode_fixed32_field,
                                               &size_fixed32_field,
                                               false,
                                               5,
                                               1,
                                               {.decode_32bit = &decode_fixed32_field}}};
const FieldMetaV2 GetTimeResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(GetTimeResponse, epoch_seconds), ProtoFieldType::TYPE_FIXED32, false, 1, 0}};
const FieldMeta ListEntitiesServicesArgument::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, type),
     &encode_enum_field<enums::ServiceArgType>,
     &size_enum_field<enums::ServiceArgType>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::ServiceArgType>}}};
const FieldMetaV2 ListEntitiesServicesArgument::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesServicesArgument, type), ProtoFieldType::TYPE_ENUM, false, 1, 0}};
const FieldMeta ListEntitiesServicesResponse::FIELDS[2] = {{1,
                                                            PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, name),
                                                            &encode_string_field,
                                                            &size_string_field,
                                                            false,
                                                            2,
                                                            1,
                                                            {.decode_length = &decode_string_field}},
                                                           {2,
                                                            PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, key),
                                                            &encode_fixed32_field,
                                                            &size_fixed32_field,
                                                            false,
                                                            5,
                                                            1,
                                                            {.decode_32bit = &decode_fixed32_field}}};
const RepeatedFieldMeta ListEntitiesServicesResponse::REPEATED_FIELDS[1] = {
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, args),
     &encode_repeated_message_field<ListEntitiesServicesArgument>,
     &size_repeated_message_field<ListEntitiesServicesArgument>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<ListEntitiesServicesArgument>}}};
const FieldMetaV2 ListEntitiesServicesResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0}};
const RepeatedFieldMetaV2 ListEntitiesServicesResponse::REPEATED_FIELDS_V2[1] = {
    {3, PROTO_FIELD_OFFSET(ListEntitiesServicesResponse, args), ProtoFieldType::TYPE_MESSAGE, 1, 46}};
const FieldMeta ExecuteServiceArgument::FIELDS[5] = {{1,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_),
                                                      &encode_bool_field,
                                                      &size_bool_field,
                                                      false,
                                                      0,
                                                      1,
                                                      {.decode_varint = &decode_bool_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, legacy_int),
                                                      &encode_int32_field,
                                                      &size_int32_field,
                                                      false,
                                                      0,
                                                      1,
                                                      {.decode_varint = &decode_int32_field}},
                                                     {3,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_),
                                                      &encode_float_field,
                                                      &size_float_field,
                                                      false,
                                                      5,
                                                      1,
                                                      {.decode_32bit = &decode_float_field}},
                                                     {4,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_),
                                                      &encode_string_field,
                                                      &size_string_field,
                                                      false,
                                                      2,
                                                      1,
                                                      {.decode_length = &decode_string_field}},
                                                     {5,
                                                      PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_),
                                                      &encode_sint32_field,
                                                      &size_sint32_field,
                                                      false,
                                                      0,
                                                      1,
                                                      {.decode_varint = &decode_sint32_field}}};
const RepeatedFieldMeta ExecuteServiceArgument::REPEATED_FIELDS[4] = {
    {6,
     PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_array),
     &encode_repeated_bool_field,
     &size_repeated_bool_field,
     1,
     0,
     {.decode_varint = &decode_repeated_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_array),
     &encode_repeated_sint32_field,
     &size_repeated_sint32_field,
     1,
     0,
     {.decode_varint = &decode_repeated_sint32_field}},
    {8,
     PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_array),
     &encode_repeated_float_field,
     &size_repeated_float_field,
     1,
     5,
     {.decode_32bit = &decode_repeated_float_field}},
    {9,
     PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_array),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 ExecuteServiceArgument::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ExecuteServiceArgument, legacy_int), ProtoFieldType::TYPE_INT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_), ProtoFieldType::TYPE_SINT32, false, 1, 0}};
const RepeatedFieldMetaV2 ExecuteServiceArgument::REPEATED_FIELDS_V2[4] = {
    {6, PROTO_FIELD_OFFSET(ExecuteServiceArgument, bool_array), ProtoFieldType::TYPE_BOOL, 1, 0},
    {7, PROTO_FIELD_OFFSET(ExecuteServiceArgument, int_array), ProtoFieldType::TYPE_SINT32, 1, 0},
    {8, PROTO_FIELD_OFFSET(ExecuteServiceArgument, float_array), ProtoFieldType::TYPE_FLOAT, 1, 0},
    {9, PROTO_FIELD_OFFSET(ExecuteServiceArgument, string_array), ProtoFieldType::TYPE_STRING, 1, 0}};
const FieldMeta ExecuteServiceRequest::FIELDS[1] = {{1,
                                                     PROTO_FIELD_OFFSET(ExecuteServiceRequest, key),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_fixed32_field}}};
const RepeatedFieldMeta ExecuteServiceRequest::REPEATED_FIELDS[1] = {
    {2,
     PROTO_FIELD_OFFSET(ExecuteServiceRequest, args),
     &encode_repeated_message_field<ExecuteServiceArgument>,
     &size_repeated_message_field<ExecuteServiceArgument>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<ExecuteServiceArgument>}}};
const FieldMetaV2 ExecuteServiceRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ExecuteServiceRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0}};
const RepeatedFieldMetaV2 ExecuteServiceRequest::REPEATED_FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(ExecuteServiceRequest, args), ProtoFieldType::TYPE_MESSAGE, 1, 48}};
#ifdef USE_CAMERA
const FieldMeta ListEntitiesCameraResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesCameraResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesCameraResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta CameraImageResponse::FIELDS[3] = {{1,
                                                   PROTO_FIELD_OFFSET(CameraImageResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(CameraImageResponse, data),
                                                   &encode_bytes_field,
                                                   &size_bytes_field,
                                                   false,
                                                   2,
                                                   1,
                                                   {.decode_length = &decode_bytes_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(CameraImageResponse, done),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 CameraImageResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(CameraImageResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(CameraImageResponse, data), ProtoFieldType::TYPE_BYTES, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(CameraImageResponse, done), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta CameraImageRequest::FIELDS[2] = {{1,
                                                  PROTO_FIELD_OFFSET(CameraImageRequest, single),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(CameraImageRequest, stream),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 CameraImageRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(CameraImageRequest, single), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(CameraImageRequest, stream), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
#endif
#ifdef USE_CLIMATE
const FieldMeta ListEntitiesClimateResponse::FIELDS[20] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_two_point_target_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_temperature),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_temperature),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_target_temperature_step),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, legacy_supports_away),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_action),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {18,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}},
    {19,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     2,
     {.decode_length = &decode_string_field}},
    {20,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     2,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {21,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_current_temperature_step),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     2,
     {.decode_32bit = &decode_float_field}},
    {22,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_humidity),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}},
    {23,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_target_humidity),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}},
    {24,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_humidity),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     2,
     {.decode_32bit = &decode_float_field}},
    {25,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_humidity),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     2,
     {.decode_32bit = &decode_float_field}},
    {26,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     2,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesClimateResponse::REPEATED_FIELDS[6] = {
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_modes),
     &encode_repeated_enum_field<enums::ClimateMode>,
     &size_repeated_enum_field<enums::ClimateMode>,
     1,
     0,
     {.decode_varint = &decode_repeated_enum_field<enums::ClimateMode>}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_fan_modes),
     &encode_repeated_enum_field<enums::ClimateFanMode>,
     &size_repeated_enum_field<enums::ClimateFanMode>,
     1,
     0,
     {.decode_varint = &decode_repeated_enum_field<enums::ClimateFanMode>}},
    {14,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_swing_modes),
     &encode_repeated_enum_field<enums::ClimateSwingMode>,
     &size_repeated_enum_field<enums::ClimateSwingMode>,
     1,
     0,
     {.decode_varint = &decode_repeated_enum_field<enums::ClimateSwingMode>}},
    {15,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_fan_modes),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}},
    {16,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_presets),
     &encode_repeated_enum_field<enums::ClimatePreset>,
     &size_repeated_enum_field<enums::ClimatePreset>,
     2,
     0,
     {.decode_varint = &decode_repeated_enum_field<enums::ClimatePreset>}},
    {17,
     PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_presets),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     2,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 ListEntitiesClimateResponse::FIELDS_V2[20] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_temperature), ProtoFieldType::TYPE_BOOL, false,
     1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_two_point_target_temperature),
     ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_temperature), ProtoFieldType::TYPE_FLOAT, false, 1,
     0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_temperature), ProtoFieldType::TYPE_FLOAT, false, 1,
     0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_target_temperature_step), ProtoFieldType::TYPE_FLOAT,
     false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, legacy_supports_away), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_action), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {18, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {19, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, icon), ProtoFieldType::TYPE_STRING, false, 2, 0},
    {20, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 2, 0},
    {21, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_current_temperature_step), ProtoFieldType::TYPE_FLOAT,
     false, 2, 0},
    {22, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_current_humidity), ProtoFieldType::TYPE_BOOL, false,
     2, 0},
    {23, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supports_target_humidity), ProtoFieldType::TYPE_BOOL, false, 2,
     0},
    {24, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_min_humidity), ProtoFieldType::TYPE_FLOAT, false, 2, 0},
    {25, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, visual_max_humidity), ProtoFieldType::TYPE_FLOAT, false, 2, 0},
    {26, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 2, 0}};
const RepeatedFieldMetaV2 ListEntitiesClimateResponse::REPEATED_FIELDS_V2[6] = {
    {7, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_modes), ProtoFieldType::TYPE_ENUM, 1, 0},
    {13, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_fan_modes), ProtoFieldType::TYPE_ENUM, 1, 0},
    {14, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_swing_modes), ProtoFieldType::TYPE_ENUM, 1, 0},
    {15, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_fan_modes), ProtoFieldType::TYPE_STRING, 1,
     0},
    {16, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_presets), ProtoFieldType::TYPE_ENUM, 2, 0},
    {17, PROTO_FIELD_OFFSET(ListEntitiesClimateResponse, supported_custom_presets), ProtoFieldType::TYPE_STRING, 2, 0}};
const FieldMeta ClimateStateResponse::FIELDS[16] = {{1,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, key),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_fixed32_field}},
                                                    {2,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, mode),
                                                     &encode_enum_field<enums::ClimateMode>,
                                                     &size_enum_field<enums::ClimateMode>,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateMode>}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, current_temperature),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {4,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {5,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_low),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {6,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_high),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {7,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, unused_legacy_away),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_bool_field}},
                                                    {8,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, action),
                                                     &encode_enum_field<enums::ClimateAction>,
                                                     &size_enum_field<enums::ClimateAction>,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateAction>}},
                                                    {9,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, fan_mode),
                                                     &encode_enum_field<enums::ClimateFanMode>,
                                                     &size_enum_field<enums::ClimateFanMode>,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateFanMode>}},
                                                    {10,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, swing_mode),
                                                     &encode_enum_field<enums::ClimateSwingMode>,
                                                     &size_enum_field<enums::ClimateSwingMode>,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_enum_field<enums::ClimateSwingMode>}},
                                                    {11,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, custom_fan_mode),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     1,
                                                     {.decode_length = &decode_string_field}},
                                                    {12,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, preset),
                                                     &encode_enum_field<enums::ClimatePreset>,
                                                     &size_enum_field<enums::ClimatePreset>,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_enum_field<enums::ClimatePreset>}},
                                                    {13,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, custom_preset),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     1,
                                                     {.decode_length = &decode_string_field}},
                                                    {14,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, current_humidity),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {15,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, target_humidity),
                                                     &encode_float_field,
                                                     &size_float_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_float_field}},
                                                    {16,
                                                     PROTO_FIELD_OFFSET(ClimateStateResponse, device_id),
                                                     &encode_uint32_field,
                                                     &size_uint32_field,
                                                     false,
                                                     0,
                                                     2,
                                                     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ClimateStateResponse::FIELDS_V2[16] = {
    {1, PROTO_FIELD_OFFSET(ClimateStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ClimateStateResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ClimateStateResponse, current_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_low), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ClimateStateResponse, target_temperature_high), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ClimateStateResponse, unused_legacy_away), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ClimateStateResponse, action), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ClimateStateResponse, fan_mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ClimateStateResponse, swing_mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ClimateStateResponse, custom_fan_mode), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ClimateStateResponse, preset), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(ClimateStateResponse, custom_preset), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {14, PROTO_FIELD_OFFSET(ClimateStateResponse, current_humidity), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {15, PROTO_FIELD_OFFSET(ClimateStateResponse, target_humidity), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {16, PROTO_FIELD_OFFSET(ClimateStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 2, 0}};
const FieldMeta ClimateCommandRequest::FIELDS[23] = {
    {1,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, mode),
     &encode_enum_field<enums::ClimateMode>,
     &size_enum_field<enums::ClimateMode>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::ClimateMode>}},
    {4,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {5,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {6,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_low),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_low),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {8,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_high),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_high),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {10,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_has_legacy_away),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_legacy_away),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {12,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_fan_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {13,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, fan_mode),
     &encode_enum_field<enums::ClimateFanMode>,
     &size_enum_field<enums::ClimateFanMode>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::ClimateFanMode>}},
    {14,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_swing_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {15,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, swing_mode),
     &encode_enum_field<enums::ClimateSwingMode>,
     &size_enum_field<enums::ClimateSwingMode>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::ClimateSwingMode>}},
    {16,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_fan_mode),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}},
    {17,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_fan_mode),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     2,
     {.decode_length = &decode_string_field}},
    {18,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_preset),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}},
    {19,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, preset),
     &encode_enum_field<enums::ClimatePreset>,
     &size_enum_field<enums::ClimatePreset>,
     false,
     0,
     2,
     {.decode_varint = &decode_enum_field<enums::ClimatePreset>}},
    {20,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_preset),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}},
    {21,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_preset),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     2,
     {.decode_length = &decode_string_field}},
    {22,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_humidity),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     2,
     {.decode_varint = &decode_bool_field}},
    {23,
     PROTO_FIELD_OFFSET(ClimateCommandRequest, target_humidity),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     2,
     {.decode_32bit = &decode_float_field}}};
const FieldMetaV2 ClimateCommandRequest::FIELDS_V2[23] = {
    {1, PROTO_FIELD_OFFSET(ClimateCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_mode), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ClimateCommandRequest, mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_low), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_low), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_temperature_high), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_temperature_high), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_has_legacy_away), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ClimateCommandRequest, unused_legacy_away), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_fan_mode), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(ClimateCommandRequest, fan_mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {14, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_swing_mode), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {15, PROTO_FIELD_OFFSET(ClimateCommandRequest, swing_mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {16, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_fan_mode), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {17, PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_fan_mode), ProtoFieldType::TYPE_STRING, false, 2, 0},
    {18, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_preset), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {19, PROTO_FIELD_OFFSET(ClimateCommandRequest, preset), ProtoFieldType::TYPE_ENUM, false, 2, 0},
    {20, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_custom_preset), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {21, PROTO_FIELD_OFFSET(ClimateCommandRequest, custom_preset), ProtoFieldType::TYPE_STRING, false, 2, 0},
    {22, PROTO_FIELD_OFFSET(ClimateCommandRequest, has_target_humidity), ProtoFieldType::TYPE_BOOL, false, 2, 0},
    {23, PROTO_FIELD_OFFSET(ClimateCommandRequest, target_humidity), ProtoFieldType::TYPE_FLOAT, false, 2, 0}};
#endif
#ifdef USE_NUMBER
const FieldMeta ListEntitiesNumberResponse::FIELDS[14] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, min_value),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, max_value),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, step),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unit_of_measurement),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, mode),
     &encode_enum_field<enums::NumberMode>,
     &size_enum_field<enums::NumberMode>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::NumberMode>}},
    {13,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {14,
     PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesNumberResponse::FIELDS_V2[14] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, min_value), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, max_value), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, step), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, unit_of_measurement), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {13, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {14, PROTO_FIELD_OFFSET(ListEntitiesNumberResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta NumberStateResponse::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, state),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, missing_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(NumberStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 NumberStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(NumberStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(NumberStateResponse, state), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(NumberStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(NumberStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta NumberCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(NumberCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(NumberCommandRequest, state),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}}};
const FieldMetaV2 NumberCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(NumberCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(NumberCommandRequest, state), ProtoFieldType::TYPE_FLOAT, false, 1, 0}};
#endif
#ifdef USE_SELECT
const FieldMeta ListEntitiesSelectResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesSelectResponse::REPEATED_FIELDS[1] = {
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, options),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 ListEntitiesSelectResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 ListEntitiesSelectResponse::REPEATED_FIELDS_V2[1] = {
    {6, PROTO_FIELD_OFFSET(ListEntitiesSelectResponse, options), ProtoFieldType::TYPE_STRING, 1, 0}};
const FieldMeta SelectStateResponse::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, state),
                                                   &encode_string_field,
                                                   &size_string_field,
                                                   false,
                                                   2,
                                                   1,
                                                   {.decode_length = &decode_string_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, missing_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(SelectStateResponse, device_id),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 SelectStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(SelectStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SelectStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(SelectStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(SelectStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta SelectCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(SelectCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(SelectCommandRequest, state),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_string_field}}};
const FieldMetaV2 SelectCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SelectCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SelectCommandRequest, state), ProtoFieldType::TYPE_STRING, false, 1, 0}};
#endif
#ifdef USE_SIREN
const FieldMeta ListEntitiesSirenResponse::FIELDS[10] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_duration),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_volume),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesSirenResponse::REPEATED_FIELDS[1] = {
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, tones),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 ListEntitiesSirenResponse::FIELDS_V2[10] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_duration), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, supports_volume), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 ListEntitiesSirenResponse::REPEATED_FIELDS_V2[1] = {
    {7, PROTO_FIELD_OFFSET(ListEntitiesSirenResponse, tones), ProtoFieldType::TYPE_STRING, 1, 0}};
const FieldMeta SirenStateResponse::FIELDS[3] = {{1,
                                                  PROTO_FIELD_OFFSET(SirenStateResponse, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(SirenStateResponse, state),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(SirenStateResponse, device_id),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 SirenStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(SirenStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SirenStateResponse, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(SirenStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta SirenCommandRequest::FIELDS[9] = {{1,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, state),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_tone),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {5,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, tone),
                                                   &encode_string_field,
                                                   &size_string_field,
                                                   false,
                                                   2,
                                                   1,
                                                   {.decode_length = &decode_string_field}},
                                                  {6,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_duration),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {7,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, duration),
                                                   &encode_uint32_field,
                                                   &size_uint32_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_uint32_field}},
                                                  {8,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, has_volume),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {9,
                                                   PROTO_FIELD_OFFSET(SirenCommandRequest, volume),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}}};
const FieldMetaV2 SirenCommandRequest::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(SirenCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SirenCommandRequest, has_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(SirenCommandRequest, state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(SirenCommandRequest, has_tone), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(SirenCommandRequest, tone), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(SirenCommandRequest, has_duration), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(SirenCommandRequest, duration), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(SirenCommandRequest, has_volume), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(SirenCommandRequest, volume), ProtoFieldType::TYPE_FLOAT, false, 1, 0}};
#endif
#ifdef USE_LOCK
const FieldMeta ListEntitiesLockResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, supports_open),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, requires_code),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, code_format),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesLockResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesLockResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, supports_open), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, requires_code), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, code_format), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ListEntitiesLockResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta LockStateResponse::FIELDS[3] = {{1,
                                                 PROTO_FIELD_OFFSET(LockStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 1,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(LockStateResponse, state),
                                                 &encode_enum_field<enums::LockState>,
                                                 &size_enum_field<enums::LockState>,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_enum_field<enums::LockState>}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(LockStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 LockStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(LockStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(LockStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(LockStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta LockCommandRequest::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, command),
                                                  &encode_enum_field<enums::LockCommand>,
                                                  &size_enum_field<enums::LockCommand>,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_enum_field<enums::LockCommand>}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, has_code),
                                                  &encode_bool_field,
                                                  &size_bool_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_bool_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(LockCommandRequest, code),
                                                  &encode_string_field,
                                                  &size_string_field,
                                                  false,
                                                  2,
                                                  1,
                                                  {.decode_length = &decode_string_field}}};
const FieldMetaV2 LockCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(LockCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(LockCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(LockCommandRequest, has_code), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(LockCommandRequest, code), ProtoFieldType::TYPE_STRING, false, 1, 0}};
#endif
#ifdef USE_BUTTON
const FieldMeta ListEntitiesButtonResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesButtonResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesButtonResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta ButtonCommandRequest::FIELDS[1] = {{1,
                                                    PROTO_FIELD_OFFSET(ButtonCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_fixed32_field}}};
const FieldMetaV2 ButtonCommandRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(ButtonCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0}};
#endif
#ifdef USE_MEDIA_PLAYER
const FieldMeta MediaPlayerSupportedFormat::FIELDS[5] = {
    {1,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, format),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_rate),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, num_channels),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {4,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, purpose),
     &encode_enum_field<enums::MediaPlayerFormatPurpose>,
     &size_enum_field<enums::MediaPlayerFormatPurpose>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::MediaPlayerFormatPurpose>}},
    {5,
     PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_bytes),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 MediaPlayerSupportedFormat::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, format), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_rate), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, num_channels), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, purpose), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(MediaPlayerSupportedFormat, sample_bytes), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta ListEntitiesMediaPlayerResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supports_pause),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesMediaPlayerResponse::REPEATED_FIELDS[1] = {
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supported_formats),
     &encode_repeated_message_field<MediaPlayerSupportedFormat>,
     &size_repeated_message_field<MediaPlayerSupportedFormat>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<MediaPlayerSupportedFormat>}}};
const FieldMetaV2 ListEntitiesMediaPlayerResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1,
     0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supports_pause), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 ListEntitiesMediaPlayerResponse::REPEATED_FIELDS_V2[1] = {
    {9, PROTO_FIELD_OFFSET(ListEntitiesMediaPlayerResponse, supported_formats), ProtoFieldType::TYPE_MESSAGE, 1, 70}};
const FieldMeta MediaPlayerStateResponse::FIELDS[5] = {{1,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, key),
                                                        &encode_fixed32_field,
                                                        &size_fixed32_field,
                                                        false,
                                                        5,
                                                        1,
                                                        {.decode_32bit = &decode_fixed32_field}},
                                                       {2,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, state),
                                                        &encode_enum_field<enums::MediaPlayerState>,
                                                        &size_enum_field<enums::MediaPlayerState>,
                                                        false,
                                                        0,
                                                        1,
                                                        {.decode_varint = &decode_enum_field<enums::MediaPlayerState>}},
                                                       {3,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, volume),
                                                        &encode_float_field,
                                                        &size_float_field,
                                                        false,
                                                        5,
                                                        1,
                                                        {.decode_32bit = &decode_float_field}},
                                                       {4,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, muted),
                                                        &encode_bool_field,
                                                        &size_bool_field,
                                                        false,
                                                        0,
                                                        1,
                                                        {.decode_varint = &decode_bool_field}},
                                                       {5,
                                                        PROTO_FIELD_OFFSET(MediaPlayerStateResponse, device_id),
                                                        &encode_uint32_field,
                                                        &size_uint32_field,
                                                        false,
                                                        0,
                                                        1,
                                                        {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 MediaPlayerStateResponse::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, volume), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, muted), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(MediaPlayerStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta MediaPlayerCommandRequest::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_command),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, command),
     &encode_enum_field<enums::MediaPlayerCommand>,
     &size_enum_field<enums::MediaPlayerCommand>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::MediaPlayerCommand>}},
    {4,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_volume),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {5,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, volume),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}},
    {6,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_media_url),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, media_url),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {8,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_announcement),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {9,
     PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, announcement),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 MediaPlayerCommandRequest::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_command), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_volume), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, volume), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_media_url), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, media_url), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, has_announcement), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(MediaPlayerCommandRequest, announcement), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
#endif
#ifdef USE_BLUETOOTH_PROXY
const FieldMeta SubscribeBluetoothLEAdvertisementsRequest::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(SubscribeBluetoothLEAdvertisementsRequest, flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 SubscribeBluetoothLEAdvertisementsRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(SubscribeBluetoothLEAdvertisementsRequest, flags), ProtoFieldType::TYPE_UINT32, false, 1,
     0}};
const FieldMeta BluetoothServiceData::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(BluetoothServiceData, uuid),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_string_field}},
                                                   {3,
                                                    PROTO_FIELD_OFFSET(BluetoothServiceData, data),
                                                    &encode_bytes_field,
                                                    &size_bytes_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_bytes_field}}};
const RepeatedFieldMeta BluetoothServiceData::REPEATED_FIELDS[1] = {
    {2,
     PROTO_FIELD_OFFSET(BluetoothServiceData, legacy_data),
     &encode_repeated_uint32_field,
     &size_repeated_uint32_field,
     1,
     0,
     {.decode_varint = &decode_repeated_uint32_field}}};
const FieldMetaV2 BluetoothServiceData::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothServiceData, uuid), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothServiceData, data), ProtoFieldType::TYPE_BYTES, false, 1, 0}};
const RepeatedFieldMetaV2 BluetoothServiceData::REPEATED_FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothServiceData, legacy_data), ProtoFieldType::TYPE_UINT32, 1, 0}};
const FieldMeta BluetoothLEAdvertisementResponse::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, name),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     1,
     {.decode_length = &decode_bytes_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, rssi),
     &encode_sint32_field,
     &size_sint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_sint32_field}},
    {7,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address_type),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothLEAdvertisementResponse::REPEATED_FIELDS[3] = {
    {4,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_uuids),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}},
    {5,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_data),
     &encode_repeated_message_field<BluetoothServiceData>,
     &size_repeated_message_field<BluetoothServiceData>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<BluetoothServiceData>}},
    {6,
     PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, manufacturer_data),
     &encode_repeated_message_field<BluetoothServiceData>,
     &size_repeated_message_field<BluetoothServiceData>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<BluetoothServiceData>}}};
const FieldMetaV2 BluetoothLEAdvertisementResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, name), ProtoFieldType::TYPE_BYTES, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, rssi), ProtoFieldType::TYPE_SINT32, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, address_type), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 BluetoothLEAdvertisementResponse::REPEATED_FIELDS_V2[3] = {
    {4, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_uuids), ProtoFieldType::TYPE_STRING, 1, 0},
    {5, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, service_data), ProtoFieldType::TYPE_MESSAGE, 1, 75},
    {6, PROTO_FIELD_OFFSET(BluetoothLEAdvertisementResponse, manufacturer_data), ProtoFieldType::TYPE_MESSAGE, 1, 75}};
const FieldMeta BluetoothLERawAdvertisement::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, rssi),
     &encode_sint32_field,
     &size_sint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_sint32_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address_type),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, data),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     1,
     {.decode_length = &decode_bytes_field}}};
const FieldMetaV2 BluetoothLERawAdvertisement::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, rssi), ProtoFieldType::TYPE_SINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, address_type), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisement, data), ProtoFieldType::TYPE_BYTES, false, 1, 0}};
const RepeatedFieldMeta BluetoothLERawAdvertisementsResponse::REPEATED_FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothLERawAdvertisementsResponse, advertisements),
     &encode_repeated_message_field<BluetoothLERawAdvertisement>,
     &size_repeated_message_field<BluetoothLERawAdvertisement>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<BluetoothLERawAdvertisement>}}};
const RepeatedFieldMetaV2 BluetoothLERawAdvertisementsResponse::REPEATED_FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothLERawAdvertisementsResponse, advertisements), ProtoFieldType::TYPE_MESSAGE, 1, 77}};
const FieldMeta BluetoothDeviceRequest::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, request_type),
     &encode_enum_field<enums::BluetoothDeviceRequestType>,
     &size_enum_field<enums::BluetoothDeviceRequestType>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::BluetoothDeviceRequestType>}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, has_address_type),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address_type),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 BluetoothDeviceRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, request_type), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, has_address_type), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(BluetoothDeviceRequest, address_type), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta BluetoothDeviceConnectionResponse::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, connected),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, mtu),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_int32_field}}};
const FieldMetaV2 BluetoothDeviceConnectionResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, connected), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, mtu), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(BluetoothDeviceConnectionResponse, error), ProtoFieldType::TYPE_INT32, false, 1, 0}};
const FieldMeta BluetoothGATTGetServicesRequest::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}}};
const FieldMetaV2 BluetoothGATTGetServicesRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, 0}};
const FieldMeta BluetoothGATTDescriptor::FIELDS[1] = {{2,
                                                       PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, handle),
                                                       &encode_uint32_field,
                                                       &size_uint32_field,
                                                       false,
                                                       0,
                                                       1,
                                                       {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothGATTDescriptor::REPEATED_FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, uuid),
     &encode_repeated_uint64_field,
     &size_repeated_uint64_field,
     1,
     0,
     {.decode_varint = &decode_repeated_uint64_field}}};
const FieldMetaV2 BluetoothGATTDescriptor::FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 BluetoothGATTDescriptor::REPEATED_FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTDescriptor, uuid), ProtoFieldType::TYPE_UINT64, 1, 0}};
const FieldMeta BluetoothGATTCharacteristic::FIELDS[2] = {{2,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, handle),
                                                           &encode_uint32_field,
                                                           &size_uint32_field,
                                                           false,
                                                           0,
                                                           1,
                                                           {.decode_varint = &decode_uint32_field}},
                                                          {3,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, properties),
                                                           &encode_uint32_field,
                                                           &size_uint32_field,
                                                           false,
                                                           0,
                                                           1,
                                                           {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothGATTCharacteristic::REPEATED_FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, uuid),
     &encode_repeated_uint64_field,
     &size_repeated_uint64_field,
     1,
     0,
     {.decode_varint = &decode_repeated_uint64_field}},
    {4,
     PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, descriptors),
     &encode_repeated_message_field<BluetoothGATTDescriptor>,
     &size_repeated_message_field<BluetoothGATTDescriptor>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<BluetoothGATTDescriptor>}}};
const FieldMetaV2 BluetoothGATTCharacteristic::FIELDS_V2[2] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, properties), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 BluetoothGATTCharacteristic::REPEATED_FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, uuid), ProtoFieldType::TYPE_UINT64, 1, 0},
    {4, PROTO_FIELD_OFFSET(BluetoothGATTCharacteristic, descriptors), ProtoFieldType::TYPE_MESSAGE, 1, 82}};
const FieldMeta BluetoothGATTService::FIELDS[1] = {{2,
                                                    PROTO_FIELD_OFFSET(BluetoothGATTService, handle),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothGATTService::REPEATED_FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTService, uuid),
     &encode_repeated_uint64_field,
     &size_repeated_uint64_field,
     1,
     0,
     {.decode_varint = &decode_repeated_uint64_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothGATTService, characteristics),
     &encode_repeated_message_field<BluetoothGATTCharacteristic>,
     &size_repeated_message_field<BluetoothGATTCharacteristic>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<BluetoothGATTCharacteristic>}}};
const FieldMetaV2 BluetoothGATTService::FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTService, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 BluetoothGATTService::REPEATED_FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTService, uuid), ProtoFieldType::TYPE_UINT64, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTService, characteristics), ProtoFieldType::TYPE_MESSAGE, 1, 83}};
const FieldMeta BluetoothGATTGetServicesResponse::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}}};
const RepeatedFieldMeta BluetoothGATTGetServicesResponse::REPEATED_FIELDS[1] = {
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, services),
     &encode_repeated_message_field<BluetoothGATTService>,
     &size_repeated_message_field<BluetoothGATTService>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<BluetoothGATTService>}}};
const FieldMetaV2 BluetoothGATTGetServicesResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0}};
const RepeatedFieldMetaV2 BluetoothGATTGetServicesResponse::REPEATED_FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesResponse, services), ProtoFieldType::TYPE_MESSAGE, 1, 84}};
const FieldMeta BluetoothGATTGetServicesDoneResponse::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTGetServicesDoneResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}}};
const FieldMetaV2 BluetoothGATTGetServicesDoneResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTGetServicesDoneResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0}};
const FieldMeta BluetoothGATTReadRequest::FIELDS[2] = {{1,
                                                        PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, address),
                                                        &encode_uint64_field,
                                                        &size_uint64_field,
                                                        false,
                                                        0,
                                                        1,
                                                        {.decode_varint = &decode_uint64_field}},
                                                       {2,
                                                        PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, handle),
                                                        &encode_uint32_field,
                                                        &size_uint32_field,
                                                        false,
                                                        0,
                                                        1,
                                                        {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 BluetoothGATTReadRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTReadRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta BluetoothGATTReadResponse::FIELDS[3] = {{1,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, address),
                                                         &encode_uint64_field,
                                                         &size_uint64_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_uint64_field}},
                                                        {2,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, handle),
                                                         &encode_uint32_field,
                                                         &size_uint32_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_uint32_field}},
                                                        {3,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, data),
                                                         &encode_bytes_field,
                                                         &size_bytes_field,
                                                         false,
                                                         2,
                                                         1,
                                                         {.decode_length = &decode_bytes_field}}};
const FieldMetaV2 BluetoothGATTReadResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTReadResponse, data), ProtoFieldType::TYPE_BYTES, false, 1, 0}};
const FieldMeta BluetoothGATTWriteRequest::FIELDS[4] = {{1,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, address),
                                                         &encode_uint64_field,
                                                         &size_uint64_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_uint64_field}},
                                                        {2,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, handle),
                                                         &encode_uint32_field,
                                                         &size_uint32_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_uint32_field}},
                                                        {3,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, response),
                                                         &encode_bool_field,
                                                         &size_bool_field,
                                                         false,
                                                         0,
                                                         1,
                                                         {.decode_varint = &decode_bool_field}},
                                                        {4,
                                                         PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, data),
                                                         &encode_bytes_field,
                                                         &size_bytes_field,
                                                         false,
                                                         2,
                                                         1,
                                                         {.decode_length = &decode_bytes_field}}};
const FieldMetaV2 BluetoothGATTWriteRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, response), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(BluetoothGATTWriteRequest, data), ProtoFieldType::TYPE_BYTES, false, 1, 0}};
const FieldMeta BluetoothGATTReadDescriptorRequest::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, handle),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 BluetoothGATTReadDescriptorRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTReadDescriptorRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta BluetoothGATTWriteDescriptorRequest::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, handle),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, data),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     1,
     {.decode_length = &decode_bytes_field}}};
const FieldMetaV2 BluetoothGATTWriteDescriptorRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTWriteDescriptorRequest, data), ProtoFieldType::TYPE_BYTES, false, 1, 0}};
const FieldMeta BluetoothGATTNotifyRequest::FIELDS[3] = {{1,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, address),
                                                          &encode_uint64_field,
                                                          &size_uint64_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_uint64_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, handle),
                                                          &encode_uint32_field,
                                                          &size_uint32_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_uint32_field}},
                                                         {3,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, enable),
                                                          &encode_bool_field,
                                                          &size_bool_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 BluetoothGATTNotifyRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTNotifyRequest, enable), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta BluetoothGATTNotifyDataResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, handle),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, data),
     &encode_bytes_field,
     &size_bytes_field,
     false,
     2,
     1,
     {.decode_length = &decode_bytes_field}}};
const FieldMetaV2 BluetoothGATTNotifyDataResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTNotifyDataResponse, data), ProtoFieldType::TYPE_BYTES, false, 1, 0}};
const FieldMeta BluetoothConnectionsFreeResponse::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, free),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, limit),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta BluetoothConnectionsFreeResponse::REPEATED_FIELDS[1] = {
    {3,
     PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, allocated),
     &encode_repeated_uint64_field,
     &size_repeated_uint64_field,
     1,
     0,
     {.decode_varint = &decode_repeated_uint64_field}}};
const FieldMetaV2 BluetoothConnectionsFreeResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, free), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, limit), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 BluetoothConnectionsFreeResponse::REPEATED_FIELDS_V2[1] = {
    {3, PROTO_FIELD_OFFSET(BluetoothConnectionsFreeResponse, allocated), ProtoFieldType::TYPE_UINT64, 1, 0}};
const FieldMeta BluetoothGATTErrorResponse::FIELDS[3] = {{1,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, address),
                                                          &encode_uint64_field,
                                                          &size_uint64_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_uint64_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, handle),
                                                          &encode_uint32_field,
                                                          &size_uint32_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_uint32_field}},
                                                         {3,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, error),
                                                          &encode_int32_field,
                                                          &size_int32_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_int32_field}}};
const FieldMetaV2 BluetoothGATTErrorResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothGATTErrorResponse, error), ProtoFieldType::TYPE_INT32, false, 1, 0}};
const FieldMeta BluetoothGATTWriteResponse::FIELDS[2] = {{1,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, address),
                                                          &encode_uint64_field,
                                                          &size_uint64_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_uint64_field}},
                                                         {2,
                                                          PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, handle),
                                                          &encode_uint32_field,
                                                          &size_uint32_field,
                                                          false,
                                                          0,
                                                          1,
                                                          {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 BluetoothGATTWriteResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTWriteResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta BluetoothGATTNotifyResponse::FIELDS[2] = {{1,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, address),
                                                           &encode_uint64_field,
                                                           &size_uint64_field,
                                                           false,
                                                           0,
                                                           1,
                                                           {.decode_varint = &decode_uint64_field}},
                                                          {2,
                                                           PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, handle),
                                                           &encode_uint32_field,
                                                           &size_uint32_field,
                                                           false,
                                                           0,
                                                           1,
                                                           {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 BluetoothGATTNotifyResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothGATTNotifyResponse, handle), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta BluetoothDevicePairingResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, paired),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_int32_field}}};
const FieldMetaV2 BluetoothDevicePairingResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, paired), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothDevicePairingResponse, error), ProtoFieldType::TYPE_INT32, false, 1, 0}};
const FieldMeta BluetoothDeviceUnpairingResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, success),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_int32_field}}};
const FieldMetaV2 BluetoothDeviceUnpairingResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, success), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceUnpairingResponse, error), ProtoFieldType::TYPE_INT32, false, 1, 0}};
const FieldMeta BluetoothDeviceClearCacheResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, address),
     &encode_uint64_field,
     &size_uint64_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint64_field}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, success),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {3,
     PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, error),
     &encode_int32_field,
     &size_int32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_int32_field}}};
const FieldMetaV2 BluetoothDeviceClearCacheResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, address), ProtoFieldType::TYPE_UINT64, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, success), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(BluetoothDeviceClearCacheResponse, error), ProtoFieldType::TYPE_INT32, false, 1, 0}};
const FieldMeta BluetoothScannerStateResponse::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, state),
     &encode_enum_field<enums::BluetoothScannerState>,
     &size_enum_field<enums::BluetoothScannerState>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::BluetoothScannerState>}},
    {2,
     PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, mode),
     &encode_enum_field<enums::BluetoothScannerMode>,
     &size_enum_field<enums::BluetoothScannerMode>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::BluetoothScannerMode>}}};
const FieldMetaV2 BluetoothScannerStateResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(BluetoothScannerStateResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, 0}};
const FieldMeta BluetoothScannerSetModeRequest::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(BluetoothScannerSetModeRequest, mode),
     &encode_enum_field<enums::BluetoothScannerMode>,
     &size_enum_field<enums::BluetoothScannerMode>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::BluetoothScannerMode>}}};
const FieldMetaV2 BluetoothScannerSetModeRequest::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(BluetoothScannerSetModeRequest, mode), ProtoFieldType::TYPE_ENUM, false, 1, 0}};
#endif
#ifdef USE_VOICE_ASSISTANT
const FieldMeta SubscribeVoiceAssistantRequest::FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, subscribe),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {2,
     PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, flags),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 SubscribeVoiceAssistantRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, subscribe), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(SubscribeVoiceAssistantRequest, flags), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta VoiceAssistantAudioSettings::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, noise_suppression_level),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, auto_gain),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, volume_multiplier),
     &encode_float_field,
     &size_float_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_float_field}}};
const FieldMetaV2 VoiceAssistantAudioSettings::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, noise_suppression_level), ProtoFieldType::TYPE_UINT32, false, 1,
     0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, auto_gain), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(VoiceAssistantAudioSettings, volume_multiplier), ProtoFieldType::TYPE_FLOAT, false, 1, 0}};
const FieldMeta VoiceAssistantRequest::FIELDS[4] = {{1,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, start),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_bool_field}},
                                                    {2,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, conversation_id),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     1,
                                                     {.decode_length = &decode_string_field}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, flags),
                                                     &encode_uint32_field,
                                                     &size_uint32_field,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_uint32_field}},
                                                    {5,
                                                     PROTO_FIELD_OFFSET(VoiceAssistantRequest, wake_word_phrase),
                                                     &encode_string_field,
                                                     &size_string_field,
                                                     false,
                                                     2,
                                                     1,
                                                     {.decode_length = &decode_string_field}}};
const FieldMetaV2 VoiceAssistantRequest::FIELDS_V2[5] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantRequest, start), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantRequest, conversation_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(VoiceAssistantRequest, flags), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(VoiceAssistantRequest, audio_settings), ProtoFieldType::TYPE_MESSAGE, false, 1, 106},
    {5, PROTO_FIELD_OFFSET(VoiceAssistantRequest, wake_word_phrase), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const FieldMeta VoiceAssistantResponse::FIELDS[2] = {{1,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantResponse, port),
                                                      &encode_uint32_field,
                                                      &size_uint32_field,
                                                      false,
                                                      0,
                                                      1,
                                                      {.decode_varint = &decode_uint32_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantResponse, error),
                                                      &encode_bool_field,
                                                      &size_bool_field,
                                                      false,
                                                      0,
                                                      1,
                                                      {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 VoiceAssistantResponse::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantResponse, port), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantResponse, error), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta VoiceAssistantEventData::FIELDS[2] = {{1,
                                                       PROTO_FIELD_OFFSET(VoiceAssistantEventData, name),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       1,
                                                       {.decode_length = &decode_string_field}},
                                                      {2,
                                                       PROTO_FIELD_OFFSET(VoiceAssistantEventData, value),
                                                       &encode_string_field,
                                                       &size_string_field,
                                                       false,
                                                       2,
                                                       1,
                                                       {.decode_length = &decode_string_field}}};
const FieldMetaV2 VoiceAssistantEventData::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantEventData, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantEventData, value), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const FieldMeta VoiceAssistantEventResponse::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, event_type),
     &encode_enum_field<enums::VoiceAssistantEvent>,
     &size_enum_field<enums::VoiceAssistantEvent>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::VoiceAssistantEvent>}}};
const RepeatedFieldMeta VoiceAssistantEventResponse::REPEATED_FIELDS[1] = {
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, data),
     &encode_repeated_message_field<VoiceAssistantEventData>,
     &size_repeated_message_field<VoiceAssistantEventData>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<VoiceAssistantEventData>}}};
const FieldMetaV2 VoiceAssistantEventResponse::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, event_type), ProtoFieldType::TYPE_ENUM, false, 1, 0}};
const RepeatedFieldMetaV2 VoiceAssistantEventResponse::REPEATED_FIELDS_V2[1] = {
    {2, PROTO_FIELD_OFFSET(VoiceAssistantEventResponse, data), ProtoFieldType::TYPE_MESSAGE, 1, 109}};
const FieldMeta VoiceAssistantAudio::FIELDS[2] = {{1,
                                                   PROTO_FIELD_OFFSET(VoiceAssistantAudio, data),
                                                   &encode_bytes_field,
                                                   &size_bytes_field,
                                                   false,
                                                   2,
                                                   1,
                                                   {.decode_length = &decode_bytes_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(VoiceAssistantAudio, end),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 VoiceAssistantAudio::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantAudio, data), ProtoFieldType::TYPE_BYTES, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantAudio, end), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta VoiceAssistantTimerEventResponse::FIELDS[6] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, event_type),
     &encode_enum_field<enums::VoiceAssistantTimerEvent>,
     &size_enum_field<enums::VoiceAssistantTimerEvent>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::VoiceAssistantTimerEvent>}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, timer_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, total_seconds),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {5,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, seconds_left),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {6,
     PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, is_active),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 VoiceAssistantTimerEventResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, event_type), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, timer_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, total_seconds), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, seconds_left), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(VoiceAssistantTimerEventResponse, is_active), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta VoiceAssistantAnnounceRequest::FIELDS[4] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, media_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, text),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, preannounce_media_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, start_conversation),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 VoiceAssistantAnnounceRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, media_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, text), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, preannounce_media_id), ProtoFieldType::TYPE_STRING, false, 1,
     0},
    {4, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceRequest, start_conversation), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta VoiceAssistantAnnounceFinished::FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantAnnounceFinished, success),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 VoiceAssistantAnnounceFinished::FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantAnnounceFinished, success), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
const FieldMeta VoiceAssistantWakeWord::FIELDS[2] = {{1,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, id),
                                                      &encode_string_field,
                                                      &size_string_field,
                                                      false,
                                                      2,
                                                      1,
                                                      {.decode_length = &decode_string_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, wake_word),
                                                      &encode_string_field,
                                                      &size_string_field,
                                                      false,
                                                      2,
                                                      1,
                                                      {.decode_length = &decode_string_field}}};
const RepeatedFieldMeta VoiceAssistantWakeWord::REPEATED_FIELDS[1] = {
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, trained_languages),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 VoiceAssistantWakeWord::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, wake_word), ProtoFieldType::TYPE_STRING, false, 1, 0}};
const RepeatedFieldMetaV2 VoiceAssistantWakeWord::REPEATED_FIELDS_V2[1] = {
    {3, PROTO_FIELD_OFFSET(VoiceAssistantWakeWord, trained_languages), ProtoFieldType::TYPE_STRING, 1, 0}};
const FieldMeta VoiceAssistantConfigurationResponse::FIELDS[1] = {
    {3,
     PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, max_active_wake_words),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta VoiceAssistantConfigurationResponse::REPEATED_FIELDS[2] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, available_wake_words),
     &encode_repeated_message_field<VoiceAssistantWakeWord>,
     &size_repeated_message_field<VoiceAssistantWakeWord>,
     1,
     2,
     {.decode_length = &decode_repeated_message_field<VoiceAssistantWakeWord>}},
    {2,
     PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, active_wake_words),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 VoiceAssistantConfigurationResponse::FIELDS_V2[1] = {
    {3, PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, max_active_wake_words), ProtoFieldType::TYPE_UINT32,
     false, 1, 0}};
const RepeatedFieldMetaV2 VoiceAssistantConfigurationResponse::REPEATED_FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, available_wake_words), ProtoFieldType::TYPE_MESSAGE, 1,
     115},
    {2, PROTO_FIELD_OFFSET(VoiceAssistantConfigurationResponse, active_wake_words), ProtoFieldType::TYPE_STRING, 1, 0}};
const RepeatedFieldMeta VoiceAssistantSetConfiguration::REPEATED_FIELDS[1] = {
    {1,
     PROTO_FIELD_OFFSET(VoiceAssistantSetConfiguration, active_wake_words),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const RepeatedFieldMetaV2 VoiceAssistantSetConfiguration::REPEATED_FIELDS_V2[1] = {
    {1, PROTO_FIELD_OFFSET(VoiceAssistantSetConfiguration, active_wake_words), ProtoFieldType::TYPE_STRING, 1, 0}};
#endif
#ifdef USE_ALARM_CONTROL_PANEL
const FieldMeta ListEntitiesAlarmControlPanelResponse::FIELDS[11] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, supported_features),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code_to_arm),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesAlarmControlPanelResponse::FIELDS_V2[11] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL,
     false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1,
     0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, supported_features), ProtoFieldType::TYPE_UINT32,
     false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code), ProtoFieldType::TYPE_BOOL, false, 1,
     0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, requires_code_to_arm), ProtoFieldType::TYPE_BOOL,
     false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesAlarmControlPanelResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1,
     0}};
const FieldMeta AlarmControlPanelStateResponse::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, state),
     &encode_enum_field<enums::AlarmControlPanelState>,
     &size_enum_field<enums::AlarmControlPanelState>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::AlarmControlPanelState>}},
    {3,
     PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 AlarmControlPanelStateResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, state), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(AlarmControlPanelStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta AlarmControlPanelCommandRequest::FIELDS[3] = {
    {1,
     PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {2,
     PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, command),
     &encode_enum_field<enums::AlarmControlPanelStateCommand>,
     &size_enum_field<enums::AlarmControlPanelStateCommand>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::AlarmControlPanelStateCommand>}},
    {3,
     PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, code),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}}};
const FieldMetaV2 AlarmControlPanelCommandRequest::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(AlarmControlPanelCommandRequest, code), ProtoFieldType::TYPE_STRING, false, 1, 0}};
#endif
#ifdef USE_TEXT
const FieldMeta ListEntitiesTextResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, min_length),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, max_length),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, pattern),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, mode),
     &encode_enum_field<enums::TextMode>,
     &size_enum_field<enums::TextMode>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::TextMode>}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesTextResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesTextResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, min_length), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, max_length), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, pattern), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, mode), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ListEntitiesTextResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta TextStateResponse::FIELDS[4] = {{1,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 1,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, state),
                                                 &encode_string_field,
                                                 &size_string_field,
                                                 false,
                                                 2,
                                                 1,
                                                 {.decode_length = &decode_string_field}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, missing_state),
                                                 &encode_bool_field,
                                                 &size_bool_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_bool_field}},
                                                {4,
                                                 PROTO_FIELD_OFFSET(TextStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 TextStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(TextStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(TextStateResponse, state), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(TextStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(TextStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta TextCommandRequest::FIELDS[2] = {{1,
                                                  PROTO_FIELD_OFFSET(TextCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(TextCommandRequest, state),
                                                  &encode_string_field,
                                                  &size_string_field,
                                                  false,
                                                  2,
                                                  1,
                                                  {.decode_length = &decode_string_field}}};
const FieldMetaV2 TextCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(TextCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(TextCommandRequest, state), ProtoFieldType::TYPE_STRING, false, 1, 0}};
#endif
#ifdef USE_DATETIME_DATE
const FieldMeta ListEntitiesDateResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesDateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesDateResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesDateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta DateStateResponse::FIELDS[6] = {{1,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 1,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, missing_state),
                                                 &encode_bool_field,
                                                 &size_bool_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_bool_field}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, year),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {4,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, month),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {5,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, day),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {6,
                                                 PROTO_FIELD_OFFSET(DateStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 DateStateResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(DateStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(DateStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(DateStateResponse, year), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(DateStateResponse, month), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(DateStateResponse, day), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(DateStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta DateCommandRequest::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, year),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, month),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(DateCommandRequest, day),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 DateCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(DateCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(DateCommandRequest, year), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(DateCommandRequest, month), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(DateCommandRequest, day), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
#endif
#ifdef USE_DATETIME_TIME
const FieldMeta ListEntitiesTimeResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesTimeResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesTimeResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta TimeStateResponse::FIELDS[6] = {{1,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, key),
                                                 &encode_fixed32_field,
                                                 &size_fixed32_field,
                                                 false,
                                                 5,
                                                 1,
                                                 {.decode_32bit = &decode_fixed32_field}},
                                                {2,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, missing_state),
                                                 &encode_bool_field,
                                                 &size_bool_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_bool_field}},
                                                {3,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, hour),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {4,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, minute),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {5,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, second),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}},
                                                {6,
                                                 PROTO_FIELD_OFFSET(TimeStateResponse, device_id),
                                                 &encode_uint32_field,
                                                 &size_uint32_field,
                                                 false,
                                                 0,
                                                 1,
                                                 {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 TimeStateResponse::FIELDS_V2[6] = {
    {1, PROTO_FIELD_OFFSET(TimeStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(TimeStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(TimeStateResponse, hour), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(TimeStateResponse, minute), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(TimeStateResponse, second), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(TimeStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta TimeCommandRequest::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, hour),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, minute),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(TimeCommandRequest, second),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 TimeCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(TimeCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(TimeCommandRequest, hour), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(TimeCommandRequest, minute), ProtoFieldType::TYPE_UINT32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(TimeCommandRequest, second), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
#endif
#ifdef USE_EVENT
const FieldMeta ListEntitiesEventResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const RepeatedFieldMeta ListEntitiesEventResponse::REPEATED_FIELDS[1] = {
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesEventResponse, event_types),
     &encode_repeated_string_field,
     &size_repeated_string_field,
     1,
     2,
     {.decode_length = &decode_repeated_string_field}}};
const FieldMetaV2 ListEntitiesEventResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const RepeatedFieldMetaV2 ListEntitiesEventResponse::REPEATED_FIELDS_V2[1] = {
    {9, PROTO_FIELD_OFFSET(ListEntitiesEventResponse, event_types), ProtoFieldType::TYPE_STRING, 1, 0}};
const FieldMeta EventResponse::FIELDS[3] = {{1,
                                             PROTO_FIELD_OFFSET(EventResponse, key),
                                             &encode_fixed32_field,
                                             &size_fixed32_field,
                                             false,
                                             5,
                                             1,
                                             {.decode_32bit = &decode_fixed32_field}},
                                            {2,
                                             PROTO_FIELD_OFFSET(EventResponse, event_type),
                                             &encode_string_field,
                                             &size_string_field,
                                             false,
                                             2,
                                             1,
                                             {.decode_length = &decode_string_field}},
                                            {3,
                                             PROTO_FIELD_OFFSET(EventResponse, device_id),
                                             &encode_uint32_field,
                                             &size_uint32_field,
                                             false,
                                             0,
                                             1,
                                             {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 EventResponse::FIELDS_V2[3] = {
    {1, PROTO_FIELD_OFFSET(EventResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(EventResponse, event_type), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(EventResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
#endif
#ifdef USE_VALVE
const FieldMeta ListEntitiesValveResponse::FIELDS[12] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, assumed_state),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {10,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_position),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {11,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_stop),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {12,
     PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesValveResponse::FIELDS_V2[12] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, assumed_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_position), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, supports_stop), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {12, PROTO_FIELD_OFFSET(ListEntitiesValveResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta ValveStateResponse::FIELDS[4] = {{1,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, key),
                                                  &encode_fixed32_field,
                                                  &size_fixed32_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_fixed32_field}},
                                                 {2,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, position),
                                                  &encode_float_field,
                                                  &size_float_field,
                                                  false,
                                                  5,
                                                  1,
                                                  {.decode_32bit = &decode_float_field}},
                                                 {3,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, current_operation),
                                                  &encode_enum_field<enums::ValveOperation>,
                                                  &size_enum_field<enums::ValveOperation>,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_enum_field<enums::ValveOperation>}},
                                                 {4,
                                                  PROTO_FIELD_OFFSET(ValveStateResponse, device_id),
                                                  &encode_uint32_field,
                                                  &size_uint32_field,
                                                  false,
                                                  0,
                                                  1,
                                                  {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ValveStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(ValveStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ValveStateResponse, position), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ValveStateResponse, current_operation), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ValveStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta ValveCommandRequest::FIELDS[4] = {{1,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, key),
                                                   &encode_fixed32_field,
                                                   &size_fixed32_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_fixed32_field}},
                                                  {2,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, has_position),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}},
                                                  {3,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, position),
                                                   &encode_float_field,
                                                   &size_float_field,
                                                   false,
                                                   5,
                                                   1,
                                                   {.decode_32bit = &decode_float_field}},
                                                  {4,
                                                   PROTO_FIELD_OFFSET(ValveCommandRequest, stop),
                                                   &encode_bool_field,
                                                   &size_bool_field,
                                                   false,
                                                   0,
                                                   1,
                                                   {.decode_varint = &decode_bool_field}}};
const FieldMetaV2 ValveCommandRequest::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(ValveCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ValveCommandRequest, has_position), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ValveCommandRequest, position), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ValveCommandRequest, stop), ProtoFieldType::TYPE_BOOL, false, 1, 0}};
#endif
#ifdef USE_DATETIME_DATETIME
const FieldMeta ListEntitiesDateTimeResponse::FIELDS[8] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesDateTimeResponse::FIELDS_V2[8] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesDateTimeResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta DateTimeStateResponse::FIELDS[4] = {{1,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, key),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_fixed32_field}},
                                                    {2,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, missing_state),
                                                     &encode_bool_field,
                                                     &size_bool_field,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_bool_field}},
                                                    {3,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, epoch_seconds),
                                                     &encode_fixed32_field,
                                                     &size_fixed32_field,
                                                     false,
                                                     5,
                                                     1,
                                                     {.decode_32bit = &decode_fixed32_field}},
                                                    {4,
                                                     PROTO_FIELD_OFFSET(DateTimeStateResponse, device_id),
                                                     &encode_uint32_field,
                                                     &size_uint32_field,
                                                     false,
                                                     0,
                                                     1,
                                                     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 DateTimeStateResponse::FIELDS_V2[4] = {
    {1, PROTO_FIELD_OFFSET(DateTimeStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(DateTimeStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(DateTimeStateResponse, epoch_seconds), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(DateTimeStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta DateTimeCommandRequest::FIELDS[2] = {{1,
                                                      PROTO_FIELD_OFFSET(DateTimeCommandRequest, key),
                                                      &encode_fixed32_field,
                                                      &size_fixed32_field,
                                                      false,
                                                      5,
                                                      1,
                                                      {.decode_32bit = &decode_fixed32_field}},
                                                     {2,
                                                      PROTO_FIELD_OFFSET(DateTimeCommandRequest, epoch_seconds),
                                                      &encode_fixed32_field,
                                                      &size_fixed32_field,
                                                      false,
                                                      5,
                                                      1,
                                                      {.decode_32bit = &decode_fixed32_field}}};
const FieldMetaV2 DateTimeCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(DateTimeCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(DateTimeCommandRequest, epoch_seconds), ProtoFieldType::TYPE_FIXED32, false, 1, 0}};
#endif
#ifdef USE_UPDATE
const FieldMeta ListEntitiesUpdateResponse::FIELDS[9] = {
    {1,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, object_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {2,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, key),
     &encode_fixed32_field,
     &size_fixed32_field,
     false,
     5,
     1,
     {.decode_32bit = &decode_fixed32_field}},
    {3,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, name),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {4,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, unique_id),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {5,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, icon),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {6,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, disabled_by_default),
     &encode_bool_field,
     &size_bool_field,
     false,
     0,
     1,
     {.decode_varint = &decode_bool_field}},
    {7,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, entity_category),
     &encode_enum_field<enums::EntityCategory>,
     &size_enum_field<enums::EntityCategory>,
     false,
     0,
     1,
     {.decode_varint = &decode_enum_field<enums::EntityCategory>}},
    {8,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_class),
     &encode_string_field,
     &size_string_field,
     false,
     2,
     1,
     {.decode_length = &decode_string_field}},
    {9,
     PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_id),
     &encode_uint32_field,
     &size_uint32_field,
     false,
     0,
     1,
     {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 ListEntitiesUpdateResponse::FIELDS_V2[9] = {
    {1, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, object_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, name), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, unique_id), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, icon), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, disabled_by_default), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, entity_category), ProtoFieldType::TYPE_ENUM, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_class), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(ListEntitiesUpdateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta UpdateStateResponse::FIELDS[11] = {{1,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, missing_state),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {3,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, in_progress),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {4,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, has_progress),
                                                    &encode_bool_field,
                                                    &size_bool_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_bool_field}},
                                                   {5,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, progress),
                                                    &encode_float_field,
                                                    &size_float_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_float_field}},
                                                   {6,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, current_version),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_string_field}},
                                                   {7,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, latest_version),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_string_field}},
                                                   {8,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, title),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_string_field}},
                                                   {9,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, release_summary),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_string_field}},
                                                   {10,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, release_url),
                                                    &encode_string_field,
                                                    &size_string_field,
                                                    false,
                                                    2,
                                                    1,
                                                    {.decode_length = &decode_string_field}},
                                                   {11,
                                                    PROTO_FIELD_OFFSET(UpdateStateResponse, device_id),
                                                    &encode_uint32_field,
                                                    &size_uint32_field,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_uint32_field}}};
const FieldMetaV2 UpdateStateResponse::FIELDS_V2[11] = {
    {1, PROTO_FIELD_OFFSET(UpdateStateResponse, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(UpdateStateResponse, missing_state), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {3, PROTO_FIELD_OFFSET(UpdateStateResponse, in_progress), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {4, PROTO_FIELD_OFFSET(UpdateStateResponse, has_progress), ProtoFieldType::TYPE_BOOL, false, 1, 0},
    {5, PROTO_FIELD_OFFSET(UpdateStateResponse, progress), ProtoFieldType::TYPE_FLOAT, false, 1, 0},
    {6, PROTO_FIELD_OFFSET(UpdateStateResponse, current_version), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {7, PROTO_FIELD_OFFSET(UpdateStateResponse, latest_version), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {8, PROTO_FIELD_OFFSET(UpdateStateResponse, title), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {9, PROTO_FIELD_OFFSET(UpdateStateResponse, release_summary), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {10, PROTO_FIELD_OFFSET(UpdateStateResponse, release_url), ProtoFieldType::TYPE_STRING, false, 1, 0},
    {11, PROTO_FIELD_OFFSET(UpdateStateResponse, device_id), ProtoFieldType::TYPE_UINT32, false, 1, 0}};
const FieldMeta UpdateCommandRequest::FIELDS[2] = {{1,
                                                    PROTO_FIELD_OFFSET(UpdateCommandRequest, key),
                                                    &encode_fixed32_field,
                                                    &size_fixed32_field,
                                                    false,
                                                    5,
                                                    1,
                                                    {.decode_32bit = &decode_fixed32_field}},
                                                   {2,
                                                    PROTO_FIELD_OFFSET(UpdateCommandRequest, command),
                                                    &encode_enum_field<enums::UpdateCommand>,
                                                    &size_enum_field<enums::UpdateCommand>,
                                                    false,
                                                    0,
                                                    1,
                                                    {.decode_varint = &decode_enum_field<enums::UpdateCommand>}}};
const FieldMetaV2 UpdateCommandRequest::FIELDS_V2[2] = {
    {1, PROTO_FIELD_OFFSET(UpdateCommandRequest, key), ProtoFieldType::TYPE_FIXED32, false, 1, 0},
    {2, PROTO_FIELD_OFFSET(UpdateCommandRequest, command), ProtoFieldType::TYPE_ENUM, false, 1, 0}};
#endif

// Message type handler implementations
void encode_message_field_by_type(ProtoWriteBuffer &buffer, uint8_t field_num, const void *field_ptr,
                                  uint8_t message_type_id) {
  switch (message_type_id) {
    case 1: {
      const HelloRequest *msg = static_cast<const HelloRequest *>(field_ptr);
      buffer.encode_message<HelloRequest>(field_num, *msg);
      break;
    }
    case 2: {
      const HelloResponse *msg = static_cast<const HelloResponse *>(field_ptr);
      buffer.encode_message<HelloResponse>(field_num, *msg);
      break;
    }
    case 3: {
      const ConnectRequest *msg = static_cast<const ConnectRequest *>(field_ptr);
      buffer.encode_message<ConnectRequest>(field_num, *msg);
      break;
    }
    case 4: {
      const ConnectResponse *msg = static_cast<const ConnectResponse *>(field_ptr);
      buffer.encode_message<ConnectResponse>(field_num, *msg);
      break;
    }
    case 5: {
      const DisconnectRequest *msg = static_cast<const DisconnectRequest *>(field_ptr);
      buffer.encode_message<DisconnectRequest>(field_num, *msg);
      break;
    }
    case 6: {
      const DisconnectResponse *msg = static_cast<const DisconnectResponse *>(field_ptr);
      buffer.encode_message<DisconnectResponse>(field_num, *msg);
      break;
    }
    case 7: {
      const PingRequest *msg = static_cast<const PingRequest *>(field_ptr);
      buffer.encode_message<PingRequest>(field_num, *msg);
      break;
    }
    case 8: {
      const PingResponse *msg = static_cast<const PingResponse *>(field_ptr);
      buffer.encode_message<PingResponse>(field_num, *msg);
      break;
    }
    case 9: {
      const DeviceInfoRequest *msg = static_cast<const DeviceInfoRequest *>(field_ptr);
      buffer.encode_message<DeviceInfoRequest>(field_num, *msg);
      break;
    }
    case 10: {
      const AreaInfo *msg = static_cast<const AreaInfo *>(field_ptr);
      buffer.encode_message<AreaInfo>(field_num, *msg);
      break;
    }
    case 11: {
      const DeviceInfo *msg = static_cast<const DeviceInfo *>(field_ptr);
      buffer.encode_message<DeviceInfo>(field_num, *msg);
      break;
    }
    case 12: {
      const DeviceInfoResponse *msg = static_cast<const DeviceInfoResponse *>(field_ptr);
      buffer.encode_message<DeviceInfoResponse>(field_num, *msg);
      break;
    }
    case 13: {
      const ListEntitiesRequest *msg = static_cast<const ListEntitiesRequest *>(field_ptr);
      buffer.encode_message<ListEntitiesRequest>(field_num, *msg);
      break;
    }
    case 14: {
      const ListEntitiesDoneResponse *msg = static_cast<const ListEntitiesDoneResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesDoneResponse>(field_num, *msg);
      break;
    }
    case 15: {
      const SubscribeStatesRequest *msg = static_cast<const SubscribeStatesRequest *>(field_ptr);
      buffer.encode_message<SubscribeStatesRequest>(field_num, *msg);
      break;
    }
#ifdef USE_BINARY_SENSOR
    case 16: {
      const ListEntitiesBinarySensorResponse *msg = static_cast<const ListEntitiesBinarySensorResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesBinarySensorResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BINARY_SENSOR
    case 17: {
      const BinarySensorStateResponse *msg = static_cast<const BinarySensorStateResponse *>(field_ptr);
      buffer.encode_message<BinarySensorStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_COVER
    case 18: {
      const ListEntitiesCoverResponse *msg = static_cast<const ListEntitiesCoverResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesCoverResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_COVER
    case 19: {
      const CoverStateResponse *msg = static_cast<const CoverStateResponse *>(field_ptr);
      buffer.encode_message<CoverStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_COVER
    case 20: {
      const CoverCommandRequest *msg = static_cast<const CoverCommandRequest *>(field_ptr);
      buffer.encode_message<CoverCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_FAN
    case 21: {
      const ListEntitiesFanResponse *msg = static_cast<const ListEntitiesFanResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesFanResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_FAN
    case 22: {
      const FanStateResponse *msg = static_cast<const FanStateResponse *>(field_ptr);
      buffer.encode_message<FanStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_FAN
    case 23: {
      const FanCommandRequest *msg = static_cast<const FanCommandRequest *>(field_ptr);
      buffer.encode_message<FanCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 24: {
      const ListEntitiesLightResponse *msg = static_cast<const ListEntitiesLightResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesLightResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 25: {
      const LightStateResponse *msg = static_cast<const LightStateResponse *>(field_ptr);
      buffer.encode_message<LightStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 26: {
      const LightCommandRequest *msg = static_cast<const LightCommandRequest *>(field_ptr);
      buffer.encode_message<LightCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SENSOR
    case 27: {
      const ListEntitiesSensorResponse *msg = static_cast<const ListEntitiesSensorResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesSensorResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SENSOR
    case 28: {
      const SensorStateResponse *msg = static_cast<const SensorStateResponse *>(field_ptr);
      buffer.encode_message<SensorStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 29: {
      const ListEntitiesSwitchResponse *msg = static_cast<const ListEntitiesSwitchResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesSwitchResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 30: {
      const SwitchStateResponse *msg = static_cast<const SwitchStateResponse *>(field_ptr);
      buffer.encode_message<SwitchStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 31: {
      const SwitchCommandRequest *msg = static_cast<const SwitchCommandRequest *>(field_ptr);
      buffer.encode_message<SwitchCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 32: {
      const ListEntitiesTextSensorResponse *msg = static_cast<const ListEntitiesTextSensorResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesTextSensorResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 33: {
      const TextSensorStateResponse *msg = static_cast<const TextSensorStateResponse *>(field_ptr);
      buffer.encode_message<TextSensorStateResponse>(field_num, *msg);
      break;
    }
#endif
    case 34: {
      const SubscribeLogsRequest *msg = static_cast<const SubscribeLogsRequest *>(field_ptr);
      buffer.encode_message<SubscribeLogsRequest>(field_num, *msg);
      break;
    }
    case 35: {
      const SubscribeLogsResponse *msg = static_cast<const SubscribeLogsResponse *>(field_ptr);
      buffer.encode_message<SubscribeLogsResponse>(field_num, *msg);
      break;
    }
#ifdef USE_API_NOISE
    case 36: {
      const NoiseEncryptionSetKeyRequest *msg = static_cast<const NoiseEncryptionSetKeyRequest *>(field_ptr);
      buffer.encode_message<NoiseEncryptionSetKeyRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_API_NOISE
    case 37: {
      const NoiseEncryptionSetKeyResponse *msg = static_cast<const NoiseEncryptionSetKeyResponse *>(field_ptr);
      buffer.encode_message<NoiseEncryptionSetKeyResponse>(field_num, *msg);
      break;
    }
#endif
    case 38: {
      const SubscribeHomeassistantServicesRequest *msg =
          static_cast<const SubscribeHomeassistantServicesRequest *>(field_ptr);
      buffer.encode_message<SubscribeHomeassistantServicesRequest>(field_num, *msg);
      break;
    }
    case 39: {
      const HomeassistantServiceMap *msg = static_cast<const HomeassistantServiceMap *>(field_ptr);
      buffer.encode_message<HomeassistantServiceMap>(field_num, *msg);
      break;
    }
    case 40: {
      const HomeassistantServiceResponse *msg = static_cast<const HomeassistantServiceResponse *>(field_ptr);
      buffer.encode_message<HomeassistantServiceResponse>(field_num, *msg);
      break;
    }
    case 41: {
      const SubscribeHomeAssistantStatesRequest *msg =
          static_cast<const SubscribeHomeAssistantStatesRequest *>(field_ptr);
      buffer.encode_message<SubscribeHomeAssistantStatesRequest>(field_num, *msg);
      break;
    }
    case 42: {
      const SubscribeHomeAssistantStateResponse *msg =
          static_cast<const SubscribeHomeAssistantStateResponse *>(field_ptr);
      buffer.encode_message<SubscribeHomeAssistantStateResponse>(field_num, *msg);
      break;
    }
    case 43: {
      const HomeAssistantStateResponse *msg = static_cast<const HomeAssistantStateResponse *>(field_ptr);
      buffer.encode_message<HomeAssistantStateResponse>(field_num, *msg);
      break;
    }
    case 44: {
      const GetTimeRequest *msg = static_cast<const GetTimeRequest *>(field_ptr);
      buffer.encode_message<GetTimeRequest>(field_num, *msg);
      break;
    }
    case 45: {
      const GetTimeResponse *msg = static_cast<const GetTimeResponse *>(field_ptr);
      buffer.encode_message<GetTimeResponse>(field_num, *msg);
      break;
    }
    case 46: {
      const ListEntitiesServicesArgument *msg = static_cast<const ListEntitiesServicesArgument *>(field_ptr);
      buffer.encode_message<ListEntitiesServicesArgument>(field_num, *msg);
      break;
    }
    case 47: {
      const ListEntitiesServicesResponse *msg = static_cast<const ListEntitiesServicesResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesServicesResponse>(field_num, *msg);
      break;
    }
    case 48: {
      const ExecuteServiceArgument *msg = static_cast<const ExecuteServiceArgument *>(field_ptr);
      buffer.encode_message<ExecuteServiceArgument>(field_num, *msg);
      break;
    }
    case 49: {
      const ExecuteServiceRequest *msg = static_cast<const ExecuteServiceRequest *>(field_ptr);
      buffer.encode_message<ExecuteServiceRequest>(field_num, *msg);
      break;
    }
#ifdef USE_CAMERA
    case 50: {
      const ListEntitiesCameraResponse *msg = static_cast<const ListEntitiesCameraResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesCameraResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_CAMERA
    case 51: {
      const CameraImageResponse *msg = static_cast<const CameraImageResponse *>(field_ptr);
      buffer.encode_message<CameraImageResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_CAMERA
    case 52: {
      const CameraImageRequest *msg = static_cast<const CameraImageRequest *>(field_ptr);
      buffer.encode_message<CameraImageRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 53: {
      const ListEntitiesClimateResponse *msg = static_cast<const ListEntitiesClimateResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesClimateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 54: {
      const ClimateStateResponse *msg = static_cast<const ClimateStateResponse *>(field_ptr);
      buffer.encode_message<ClimateStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 55: {
      const ClimateCommandRequest *msg = static_cast<const ClimateCommandRequest *>(field_ptr);
      buffer.encode_message<ClimateCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 56: {
      const ListEntitiesNumberResponse *msg = static_cast<const ListEntitiesNumberResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesNumberResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 57: {
      const NumberStateResponse *msg = static_cast<const NumberStateResponse *>(field_ptr);
      buffer.encode_message<NumberStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 58: {
      const NumberCommandRequest *msg = static_cast<const NumberCommandRequest *>(field_ptr);
      buffer.encode_message<NumberCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SELECT
    case 59: {
      const ListEntitiesSelectResponse *msg = static_cast<const ListEntitiesSelectResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesSelectResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SELECT
    case 60: {
      const SelectStateResponse *msg = static_cast<const SelectStateResponse *>(field_ptr);
      buffer.encode_message<SelectStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SELECT
    case 61: {
      const SelectCommandRequest *msg = static_cast<const SelectCommandRequest *>(field_ptr);
      buffer.encode_message<SelectCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SIREN
    case 62: {
      const ListEntitiesSirenResponse *msg = static_cast<const ListEntitiesSirenResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesSirenResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SIREN
    case 63: {
      const SirenStateResponse *msg = static_cast<const SirenStateResponse *>(field_ptr);
      buffer.encode_message<SirenStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_SIREN
    case 64: {
      const SirenCommandRequest *msg = static_cast<const SirenCommandRequest *>(field_ptr);
      buffer.encode_message<SirenCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_LOCK
    case 65: {
      const ListEntitiesLockResponse *msg = static_cast<const ListEntitiesLockResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesLockResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_LOCK
    case 66: {
      const LockStateResponse *msg = static_cast<const LockStateResponse *>(field_ptr);
      buffer.encode_message<LockStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_LOCK
    case 67: {
      const LockCommandRequest *msg = static_cast<const LockCommandRequest *>(field_ptr);
      buffer.encode_message<LockCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BUTTON
    case 68: {
      const ListEntitiesButtonResponse *msg = static_cast<const ListEntitiesButtonResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesButtonResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BUTTON
    case 69: {
      const ButtonCommandRequest *msg = static_cast<const ButtonCommandRequest *>(field_ptr);
      buffer.encode_message<ButtonCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 70: {
      const MediaPlayerSupportedFormat *msg = static_cast<const MediaPlayerSupportedFormat *>(field_ptr);
      buffer.encode_message<MediaPlayerSupportedFormat>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 71: {
      const ListEntitiesMediaPlayerResponse *msg = static_cast<const ListEntitiesMediaPlayerResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesMediaPlayerResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 72: {
      const MediaPlayerStateResponse *msg = static_cast<const MediaPlayerStateResponse *>(field_ptr);
      buffer.encode_message<MediaPlayerStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 73: {
      const MediaPlayerCommandRequest *msg = static_cast<const MediaPlayerCommandRequest *>(field_ptr);
      buffer.encode_message<MediaPlayerCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 74: {
      const SubscribeBluetoothLEAdvertisementsRequest *msg =
          static_cast<const SubscribeBluetoothLEAdvertisementsRequest *>(field_ptr);
      buffer.encode_message<SubscribeBluetoothLEAdvertisementsRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 75: {
      const BluetoothServiceData *msg = static_cast<const BluetoothServiceData *>(field_ptr);
      buffer.encode_message<BluetoothServiceData>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 76: {
      const BluetoothLEAdvertisementResponse *msg = static_cast<const BluetoothLEAdvertisementResponse *>(field_ptr);
      buffer.encode_message<BluetoothLEAdvertisementResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 77: {
      const BluetoothLERawAdvertisement *msg = static_cast<const BluetoothLERawAdvertisement *>(field_ptr);
      buffer.encode_message<BluetoothLERawAdvertisement>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 78: {
      const BluetoothLERawAdvertisementsResponse *msg =
          static_cast<const BluetoothLERawAdvertisementsResponse *>(field_ptr);
      buffer.encode_message<BluetoothLERawAdvertisementsResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 79: {
      const BluetoothDeviceRequest *msg = static_cast<const BluetoothDeviceRequest *>(field_ptr);
      buffer.encode_message<BluetoothDeviceRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 80: {
      const BluetoothDeviceConnectionResponse *msg = static_cast<const BluetoothDeviceConnectionResponse *>(field_ptr);
      buffer.encode_message<BluetoothDeviceConnectionResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 81: {
      const BluetoothGATTGetServicesRequest *msg = static_cast<const BluetoothGATTGetServicesRequest *>(field_ptr);
      buffer.encode_message<BluetoothGATTGetServicesRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 82: {
      const BluetoothGATTDescriptor *msg = static_cast<const BluetoothGATTDescriptor *>(field_ptr);
      buffer.encode_message<BluetoothGATTDescriptor>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 83: {
      const BluetoothGATTCharacteristic *msg = static_cast<const BluetoothGATTCharacteristic *>(field_ptr);
      buffer.encode_message<BluetoothGATTCharacteristic>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 84: {
      const BluetoothGATTService *msg = static_cast<const BluetoothGATTService *>(field_ptr);
      buffer.encode_message<BluetoothGATTService>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 85: {
      const BluetoothGATTGetServicesResponse *msg = static_cast<const BluetoothGATTGetServicesResponse *>(field_ptr);
      buffer.encode_message<BluetoothGATTGetServicesResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 86: {
      const BluetoothGATTGetServicesDoneResponse *msg =
          static_cast<const BluetoothGATTGetServicesDoneResponse *>(field_ptr);
      buffer.encode_message<BluetoothGATTGetServicesDoneResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 87: {
      const BluetoothGATTReadRequest *msg = static_cast<const BluetoothGATTReadRequest *>(field_ptr);
      buffer.encode_message<BluetoothGATTReadRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 88: {
      const BluetoothGATTReadResponse *msg = static_cast<const BluetoothGATTReadResponse *>(field_ptr);
      buffer.encode_message<BluetoothGATTReadResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 89: {
      const BluetoothGATTWriteRequest *msg = static_cast<const BluetoothGATTWriteRequest *>(field_ptr);
      buffer.encode_message<BluetoothGATTWriteRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 90: {
      const BluetoothGATTReadDescriptorRequest *msg =
          static_cast<const BluetoothGATTReadDescriptorRequest *>(field_ptr);
      buffer.encode_message<BluetoothGATTReadDescriptorRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 91: {
      const BluetoothGATTWriteDescriptorRequest *msg =
          static_cast<const BluetoothGATTWriteDescriptorRequest *>(field_ptr);
      buffer.encode_message<BluetoothGATTWriteDescriptorRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 92: {
      const BluetoothGATTNotifyRequest *msg = static_cast<const BluetoothGATTNotifyRequest *>(field_ptr);
      buffer.encode_message<BluetoothGATTNotifyRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 93: {
      const BluetoothGATTNotifyDataResponse *msg = static_cast<const BluetoothGATTNotifyDataResponse *>(field_ptr);
      buffer.encode_message<BluetoothGATTNotifyDataResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 94: {
      const SubscribeBluetoothConnectionsFreeRequest *msg =
          static_cast<const SubscribeBluetoothConnectionsFreeRequest *>(field_ptr);
      buffer.encode_message<SubscribeBluetoothConnectionsFreeRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 95: {
      const BluetoothConnectionsFreeResponse *msg = static_cast<const BluetoothConnectionsFreeResponse *>(field_ptr);
      buffer.encode_message<BluetoothConnectionsFreeResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 96: {
      const BluetoothGATTErrorResponse *msg = static_cast<const BluetoothGATTErrorResponse *>(field_ptr);
      buffer.encode_message<BluetoothGATTErrorResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 97: {
      const BluetoothGATTWriteResponse *msg = static_cast<const BluetoothGATTWriteResponse *>(field_ptr);
      buffer.encode_message<BluetoothGATTWriteResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 98: {
      const BluetoothGATTNotifyResponse *msg = static_cast<const BluetoothGATTNotifyResponse *>(field_ptr);
      buffer.encode_message<BluetoothGATTNotifyResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 99: {
      const BluetoothDevicePairingResponse *msg = static_cast<const BluetoothDevicePairingResponse *>(field_ptr);
      buffer.encode_message<BluetoothDevicePairingResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 100: {
      const BluetoothDeviceUnpairingResponse *msg = static_cast<const BluetoothDeviceUnpairingResponse *>(field_ptr);
      buffer.encode_message<BluetoothDeviceUnpairingResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 101: {
      const UnsubscribeBluetoothLEAdvertisementsRequest *msg =
          static_cast<const UnsubscribeBluetoothLEAdvertisementsRequest *>(field_ptr);
      buffer.encode_message<UnsubscribeBluetoothLEAdvertisementsRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 102: {
      const BluetoothDeviceClearCacheResponse *msg = static_cast<const BluetoothDeviceClearCacheResponse *>(field_ptr);
      buffer.encode_message<BluetoothDeviceClearCacheResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 103: {
      const BluetoothScannerStateResponse *msg = static_cast<const BluetoothScannerStateResponse *>(field_ptr);
      buffer.encode_message<BluetoothScannerStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 104: {
      const BluetoothScannerSetModeRequest *msg = static_cast<const BluetoothScannerSetModeRequest *>(field_ptr);
      buffer.encode_message<BluetoothScannerSetModeRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 105: {
      const SubscribeVoiceAssistantRequest *msg = static_cast<const SubscribeVoiceAssistantRequest *>(field_ptr);
      buffer.encode_message<SubscribeVoiceAssistantRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 106: {
      const VoiceAssistantAudioSettings *msg = static_cast<const VoiceAssistantAudioSettings *>(field_ptr);
      buffer.encode_message<VoiceAssistantAudioSettings>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 107: {
      const VoiceAssistantRequest *msg = static_cast<const VoiceAssistantRequest *>(field_ptr);
      buffer.encode_message<VoiceAssistantRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 108: {
      const VoiceAssistantResponse *msg = static_cast<const VoiceAssistantResponse *>(field_ptr);
      buffer.encode_message<VoiceAssistantResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 109: {
      const VoiceAssistantEventData *msg = static_cast<const VoiceAssistantEventData *>(field_ptr);
      buffer.encode_message<VoiceAssistantEventData>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 110: {
      const VoiceAssistantEventResponse *msg = static_cast<const VoiceAssistantEventResponse *>(field_ptr);
      buffer.encode_message<VoiceAssistantEventResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 111: {
      const VoiceAssistantAudio *msg = static_cast<const VoiceAssistantAudio *>(field_ptr);
      buffer.encode_message<VoiceAssistantAudio>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 112: {
      const VoiceAssistantTimerEventResponse *msg = static_cast<const VoiceAssistantTimerEventResponse *>(field_ptr);
      buffer.encode_message<VoiceAssistantTimerEventResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 113: {
      const VoiceAssistantAnnounceRequest *msg = static_cast<const VoiceAssistantAnnounceRequest *>(field_ptr);
      buffer.encode_message<VoiceAssistantAnnounceRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 114: {
      const VoiceAssistantAnnounceFinished *msg = static_cast<const VoiceAssistantAnnounceFinished *>(field_ptr);
      buffer.encode_message<VoiceAssistantAnnounceFinished>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 115: {
      const VoiceAssistantWakeWord *msg = static_cast<const VoiceAssistantWakeWord *>(field_ptr);
      buffer.encode_message<VoiceAssistantWakeWord>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 116: {
      const VoiceAssistantConfigurationRequest *msg =
          static_cast<const VoiceAssistantConfigurationRequest *>(field_ptr);
      buffer.encode_message<VoiceAssistantConfigurationRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 117: {
      const VoiceAssistantConfigurationResponse *msg =
          static_cast<const VoiceAssistantConfigurationResponse *>(field_ptr);
      buffer.encode_message<VoiceAssistantConfigurationResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 118: {
      const VoiceAssistantSetConfiguration *msg = static_cast<const VoiceAssistantSetConfiguration *>(field_ptr);
      buffer.encode_message<VoiceAssistantSetConfiguration>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 119: {
      const ListEntitiesAlarmControlPanelResponse *msg =
          static_cast<const ListEntitiesAlarmControlPanelResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesAlarmControlPanelResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 120: {
      const AlarmControlPanelStateResponse *msg = static_cast<const AlarmControlPanelStateResponse *>(field_ptr);
      buffer.encode_message<AlarmControlPanelStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 121: {
      const AlarmControlPanelCommandRequest *msg = static_cast<const AlarmControlPanelCommandRequest *>(field_ptr);
      buffer.encode_message<AlarmControlPanelCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_TEXT
    case 122: {
      const ListEntitiesTextResponse *msg = static_cast<const ListEntitiesTextResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesTextResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_TEXT
    case 123: {
      const TextStateResponse *msg = static_cast<const TextStateResponse *>(field_ptr);
      buffer.encode_message<TextStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_TEXT
    case 124: {
      const TextCommandRequest *msg = static_cast<const TextCommandRequest *>(field_ptr);
      buffer.encode_message<TextCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 125: {
      const ListEntitiesDateResponse *msg = static_cast<const ListEntitiesDateResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesDateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 126: {
      const DateStateResponse *msg = static_cast<const DateStateResponse *>(field_ptr);
      buffer.encode_message<DateStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 127: {
      const DateCommandRequest *msg = static_cast<const DateCommandRequest *>(field_ptr);
      buffer.encode_message<DateCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 128: {
      const ListEntitiesTimeResponse *msg = static_cast<const ListEntitiesTimeResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesTimeResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 129: {
      const TimeStateResponse *msg = static_cast<const TimeStateResponse *>(field_ptr);
      buffer.encode_message<TimeStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 130: {
      const TimeCommandRequest *msg = static_cast<const TimeCommandRequest *>(field_ptr);
      buffer.encode_message<TimeCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_EVENT
    case 131: {
      const ListEntitiesEventResponse *msg = static_cast<const ListEntitiesEventResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesEventResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_EVENT
    case 132: {
      const EventResponse *msg = static_cast<const EventResponse *>(field_ptr);
      buffer.encode_message<EventResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VALVE
    case 133: {
      const ListEntitiesValveResponse *msg = static_cast<const ListEntitiesValveResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesValveResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VALVE
    case 134: {
      const ValveStateResponse *msg = static_cast<const ValveStateResponse *>(field_ptr);
      buffer.encode_message<ValveStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_VALVE
    case 135: {
      const ValveCommandRequest *msg = static_cast<const ValveCommandRequest *>(field_ptr);
      buffer.encode_message<ValveCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 136: {
      const ListEntitiesDateTimeResponse *msg = static_cast<const ListEntitiesDateTimeResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesDateTimeResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 137: {
      const DateTimeStateResponse *msg = static_cast<const DateTimeStateResponse *>(field_ptr);
      buffer.encode_message<DateTimeStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 138: {
      const DateTimeCommandRequest *msg = static_cast<const DateTimeCommandRequest *>(field_ptr);
      buffer.encode_message<DateTimeCommandRequest>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 139: {
      const ListEntitiesUpdateResponse *msg = static_cast<const ListEntitiesUpdateResponse *>(field_ptr);
      buffer.encode_message<ListEntitiesUpdateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 140: {
      const UpdateStateResponse *msg = static_cast<const UpdateStateResponse *>(field_ptr);
      buffer.encode_message<UpdateStateResponse>(field_num, *msg);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 141: {
      const UpdateCommandRequest *msg = static_cast<const UpdateCommandRequest *>(field_ptr);
      buffer.encode_message<UpdateCommandRequest>(field_num, *msg);
      break;
    }
#endif
    default:
      break;
  }
}

void decode_message_field_by_type(void *field_ptr, ProtoLengthDelimited value, uint8_t message_type_id) {
  switch (message_type_id) {
    case 1: {
      HelloRequest *msg = static_cast<HelloRequest *>(field_ptr);
      *msg = value.as_message<HelloRequest>();
      break;
    }
    case 2: {
      HelloResponse *msg = static_cast<HelloResponse *>(field_ptr);
      *msg = value.as_message<HelloResponse>();
      break;
    }
    case 3: {
      ConnectRequest *msg = static_cast<ConnectRequest *>(field_ptr);
      *msg = value.as_message<ConnectRequest>();
      break;
    }
    case 4: {
      ConnectResponse *msg = static_cast<ConnectResponse *>(field_ptr);
      *msg = value.as_message<ConnectResponse>();
      break;
    }
    case 5: {
      DisconnectRequest *msg = static_cast<DisconnectRequest *>(field_ptr);
      *msg = value.as_message<DisconnectRequest>();
      break;
    }
    case 6: {
      DisconnectResponse *msg = static_cast<DisconnectResponse *>(field_ptr);
      *msg = value.as_message<DisconnectResponse>();
      break;
    }
    case 7: {
      PingRequest *msg = static_cast<PingRequest *>(field_ptr);
      *msg = value.as_message<PingRequest>();
      break;
    }
    case 8: {
      PingResponse *msg = static_cast<PingResponse *>(field_ptr);
      *msg = value.as_message<PingResponse>();
      break;
    }
    case 9: {
      DeviceInfoRequest *msg = static_cast<DeviceInfoRequest *>(field_ptr);
      *msg = value.as_message<DeviceInfoRequest>();
      break;
    }
    case 10: {
      AreaInfo *msg = static_cast<AreaInfo *>(field_ptr);
      *msg = value.as_message<AreaInfo>();
      break;
    }
    case 11: {
      DeviceInfo *msg = static_cast<DeviceInfo *>(field_ptr);
      *msg = value.as_message<DeviceInfo>();
      break;
    }
    case 12: {
      DeviceInfoResponse *msg = static_cast<DeviceInfoResponse *>(field_ptr);
      *msg = value.as_message<DeviceInfoResponse>();
      break;
    }
    case 13: {
      ListEntitiesRequest *msg = static_cast<ListEntitiesRequest *>(field_ptr);
      *msg = value.as_message<ListEntitiesRequest>();
      break;
    }
    case 14: {
      ListEntitiesDoneResponse *msg = static_cast<ListEntitiesDoneResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesDoneResponse>();
      break;
    }
    case 15: {
      SubscribeStatesRequest *msg = static_cast<SubscribeStatesRequest *>(field_ptr);
      *msg = value.as_message<SubscribeStatesRequest>();
      break;
    }
#ifdef USE_BINARY_SENSOR
    case 16: {
      ListEntitiesBinarySensorResponse *msg = static_cast<ListEntitiesBinarySensorResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesBinarySensorResponse>();
      break;
    }
#endif
#ifdef USE_BINARY_SENSOR
    case 17: {
      BinarySensorStateResponse *msg = static_cast<BinarySensorStateResponse *>(field_ptr);
      *msg = value.as_message<BinarySensorStateResponse>();
      break;
    }
#endif
#ifdef USE_COVER
    case 18: {
      ListEntitiesCoverResponse *msg = static_cast<ListEntitiesCoverResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesCoverResponse>();
      break;
    }
#endif
#ifdef USE_COVER
    case 19: {
      CoverStateResponse *msg = static_cast<CoverStateResponse *>(field_ptr);
      *msg = value.as_message<CoverStateResponse>();
      break;
    }
#endif
#ifdef USE_COVER
    case 20: {
      CoverCommandRequest *msg = static_cast<CoverCommandRequest *>(field_ptr);
      *msg = value.as_message<CoverCommandRequest>();
      break;
    }
#endif
#ifdef USE_FAN
    case 21: {
      ListEntitiesFanResponse *msg = static_cast<ListEntitiesFanResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesFanResponse>();
      break;
    }
#endif
#ifdef USE_FAN
    case 22: {
      FanStateResponse *msg = static_cast<FanStateResponse *>(field_ptr);
      *msg = value.as_message<FanStateResponse>();
      break;
    }
#endif
#ifdef USE_FAN
    case 23: {
      FanCommandRequest *msg = static_cast<FanCommandRequest *>(field_ptr);
      *msg = value.as_message<FanCommandRequest>();
      break;
    }
#endif
#ifdef USE_LIGHT
    case 24: {
      ListEntitiesLightResponse *msg = static_cast<ListEntitiesLightResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesLightResponse>();
      break;
    }
#endif
#ifdef USE_LIGHT
    case 25: {
      LightStateResponse *msg = static_cast<LightStateResponse *>(field_ptr);
      *msg = value.as_message<LightStateResponse>();
      break;
    }
#endif
#ifdef USE_LIGHT
    case 26: {
      LightCommandRequest *msg = static_cast<LightCommandRequest *>(field_ptr);
      *msg = value.as_message<LightCommandRequest>();
      break;
    }
#endif
#ifdef USE_SENSOR
    case 27: {
      ListEntitiesSensorResponse *msg = static_cast<ListEntitiesSensorResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesSensorResponse>();
      break;
    }
#endif
#ifdef USE_SENSOR
    case 28: {
      SensorStateResponse *msg = static_cast<SensorStateResponse *>(field_ptr);
      *msg = value.as_message<SensorStateResponse>();
      break;
    }
#endif
#ifdef USE_SWITCH
    case 29: {
      ListEntitiesSwitchResponse *msg = static_cast<ListEntitiesSwitchResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesSwitchResponse>();
      break;
    }
#endif
#ifdef USE_SWITCH
    case 30: {
      SwitchStateResponse *msg = static_cast<SwitchStateResponse *>(field_ptr);
      *msg = value.as_message<SwitchStateResponse>();
      break;
    }
#endif
#ifdef USE_SWITCH
    case 31: {
      SwitchCommandRequest *msg = static_cast<SwitchCommandRequest *>(field_ptr);
      *msg = value.as_message<SwitchCommandRequest>();
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 32: {
      ListEntitiesTextSensorResponse *msg = static_cast<ListEntitiesTextSensorResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesTextSensorResponse>();
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 33: {
      TextSensorStateResponse *msg = static_cast<TextSensorStateResponse *>(field_ptr);
      *msg = value.as_message<TextSensorStateResponse>();
      break;
    }
#endif
    case 34: {
      SubscribeLogsRequest *msg = static_cast<SubscribeLogsRequest *>(field_ptr);
      *msg = value.as_message<SubscribeLogsRequest>();
      break;
    }
    case 35: {
      SubscribeLogsResponse *msg = static_cast<SubscribeLogsResponse *>(field_ptr);
      *msg = value.as_message<SubscribeLogsResponse>();
      break;
    }
#ifdef USE_API_NOISE
    case 36: {
      NoiseEncryptionSetKeyRequest *msg = static_cast<NoiseEncryptionSetKeyRequest *>(field_ptr);
      *msg = value.as_message<NoiseEncryptionSetKeyRequest>();
      break;
    }
#endif
#ifdef USE_API_NOISE
    case 37: {
      NoiseEncryptionSetKeyResponse *msg = static_cast<NoiseEncryptionSetKeyResponse *>(field_ptr);
      *msg = value.as_message<NoiseEncryptionSetKeyResponse>();
      break;
    }
#endif
    case 38: {
      SubscribeHomeassistantServicesRequest *msg = static_cast<SubscribeHomeassistantServicesRequest *>(field_ptr);
      *msg = value.as_message<SubscribeHomeassistantServicesRequest>();
      break;
    }
    case 39: {
      HomeassistantServiceMap *msg = static_cast<HomeassistantServiceMap *>(field_ptr);
      *msg = value.as_message<HomeassistantServiceMap>();
      break;
    }
    case 40: {
      HomeassistantServiceResponse *msg = static_cast<HomeassistantServiceResponse *>(field_ptr);
      *msg = value.as_message<HomeassistantServiceResponse>();
      break;
    }
    case 41: {
      SubscribeHomeAssistantStatesRequest *msg = static_cast<SubscribeHomeAssistantStatesRequest *>(field_ptr);
      *msg = value.as_message<SubscribeHomeAssistantStatesRequest>();
      break;
    }
    case 42: {
      SubscribeHomeAssistantStateResponse *msg = static_cast<SubscribeHomeAssistantStateResponse *>(field_ptr);
      *msg = value.as_message<SubscribeHomeAssistantStateResponse>();
      break;
    }
    case 43: {
      HomeAssistantStateResponse *msg = static_cast<HomeAssistantStateResponse *>(field_ptr);
      *msg = value.as_message<HomeAssistantStateResponse>();
      break;
    }
    case 44: {
      GetTimeRequest *msg = static_cast<GetTimeRequest *>(field_ptr);
      *msg = value.as_message<GetTimeRequest>();
      break;
    }
    case 45: {
      GetTimeResponse *msg = static_cast<GetTimeResponse *>(field_ptr);
      *msg = value.as_message<GetTimeResponse>();
      break;
    }
    case 46: {
      ListEntitiesServicesArgument *msg = static_cast<ListEntitiesServicesArgument *>(field_ptr);
      *msg = value.as_message<ListEntitiesServicesArgument>();
      break;
    }
    case 47: {
      ListEntitiesServicesResponse *msg = static_cast<ListEntitiesServicesResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesServicesResponse>();
      break;
    }
    case 48: {
      ExecuteServiceArgument *msg = static_cast<ExecuteServiceArgument *>(field_ptr);
      *msg = value.as_message<ExecuteServiceArgument>();
      break;
    }
    case 49: {
      ExecuteServiceRequest *msg = static_cast<ExecuteServiceRequest *>(field_ptr);
      *msg = value.as_message<ExecuteServiceRequest>();
      break;
    }
#ifdef USE_CAMERA
    case 50: {
      ListEntitiesCameraResponse *msg = static_cast<ListEntitiesCameraResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesCameraResponse>();
      break;
    }
#endif
#ifdef USE_CAMERA
    case 51: {
      CameraImageResponse *msg = static_cast<CameraImageResponse *>(field_ptr);
      *msg = value.as_message<CameraImageResponse>();
      break;
    }
#endif
#ifdef USE_CAMERA
    case 52: {
      CameraImageRequest *msg = static_cast<CameraImageRequest *>(field_ptr);
      *msg = value.as_message<CameraImageRequest>();
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 53: {
      ListEntitiesClimateResponse *msg = static_cast<ListEntitiesClimateResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesClimateResponse>();
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 54: {
      ClimateStateResponse *msg = static_cast<ClimateStateResponse *>(field_ptr);
      *msg = value.as_message<ClimateStateResponse>();
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 55: {
      ClimateCommandRequest *msg = static_cast<ClimateCommandRequest *>(field_ptr);
      *msg = value.as_message<ClimateCommandRequest>();
      break;
    }
#endif
#ifdef USE_NUMBER
    case 56: {
      ListEntitiesNumberResponse *msg = static_cast<ListEntitiesNumberResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesNumberResponse>();
      break;
    }
#endif
#ifdef USE_NUMBER
    case 57: {
      NumberStateResponse *msg = static_cast<NumberStateResponse *>(field_ptr);
      *msg = value.as_message<NumberStateResponse>();
      break;
    }
#endif
#ifdef USE_NUMBER
    case 58: {
      NumberCommandRequest *msg = static_cast<NumberCommandRequest *>(field_ptr);
      *msg = value.as_message<NumberCommandRequest>();
      break;
    }
#endif
#ifdef USE_SELECT
    case 59: {
      ListEntitiesSelectResponse *msg = static_cast<ListEntitiesSelectResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesSelectResponse>();
      break;
    }
#endif
#ifdef USE_SELECT
    case 60: {
      SelectStateResponse *msg = static_cast<SelectStateResponse *>(field_ptr);
      *msg = value.as_message<SelectStateResponse>();
      break;
    }
#endif
#ifdef USE_SELECT
    case 61: {
      SelectCommandRequest *msg = static_cast<SelectCommandRequest *>(field_ptr);
      *msg = value.as_message<SelectCommandRequest>();
      break;
    }
#endif
#ifdef USE_SIREN
    case 62: {
      ListEntitiesSirenResponse *msg = static_cast<ListEntitiesSirenResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesSirenResponse>();
      break;
    }
#endif
#ifdef USE_SIREN
    case 63: {
      SirenStateResponse *msg = static_cast<SirenStateResponse *>(field_ptr);
      *msg = value.as_message<SirenStateResponse>();
      break;
    }
#endif
#ifdef USE_SIREN
    case 64: {
      SirenCommandRequest *msg = static_cast<SirenCommandRequest *>(field_ptr);
      *msg = value.as_message<SirenCommandRequest>();
      break;
    }
#endif
#ifdef USE_LOCK
    case 65: {
      ListEntitiesLockResponse *msg = static_cast<ListEntitiesLockResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesLockResponse>();
      break;
    }
#endif
#ifdef USE_LOCK
    case 66: {
      LockStateResponse *msg = static_cast<LockStateResponse *>(field_ptr);
      *msg = value.as_message<LockStateResponse>();
      break;
    }
#endif
#ifdef USE_LOCK
    case 67: {
      LockCommandRequest *msg = static_cast<LockCommandRequest *>(field_ptr);
      *msg = value.as_message<LockCommandRequest>();
      break;
    }
#endif
#ifdef USE_BUTTON
    case 68: {
      ListEntitiesButtonResponse *msg = static_cast<ListEntitiesButtonResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesButtonResponse>();
      break;
    }
#endif
#ifdef USE_BUTTON
    case 69: {
      ButtonCommandRequest *msg = static_cast<ButtonCommandRequest *>(field_ptr);
      *msg = value.as_message<ButtonCommandRequest>();
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 70: {
      MediaPlayerSupportedFormat *msg = static_cast<MediaPlayerSupportedFormat *>(field_ptr);
      *msg = value.as_message<MediaPlayerSupportedFormat>();
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 71: {
      ListEntitiesMediaPlayerResponse *msg = static_cast<ListEntitiesMediaPlayerResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesMediaPlayerResponse>();
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 72: {
      MediaPlayerStateResponse *msg = static_cast<MediaPlayerStateResponse *>(field_ptr);
      *msg = value.as_message<MediaPlayerStateResponse>();
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 73: {
      MediaPlayerCommandRequest *msg = static_cast<MediaPlayerCommandRequest *>(field_ptr);
      *msg = value.as_message<MediaPlayerCommandRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 74: {
      SubscribeBluetoothLEAdvertisementsRequest *msg =
          static_cast<SubscribeBluetoothLEAdvertisementsRequest *>(field_ptr);
      *msg = value.as_message<SubscribeBluetoothLEAdvertisementsRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 75: {
      BluetoothServiceData *msg = static_cast<BluetoothServiceData *>(field_ptr);
      *msg = value.as_message<BluetoothServiceData>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 76: {
      BluetoothLEAdvertisementResponse *msg = static_cast<BluetoothLEAdvertisementResponse *>(field_ptr);
      *msg = value.as_message<BluetoothLEAdvertisementResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 77: {
      BluetoothLERawAdvertisement *msg = static_cast<BluetoothLERawAdvertisement *>(field_ptr);
      *msg = value.as_message<BluetoothLERawAdvertisement>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 78: {
      BluetoothLERawAdvertisementsResponse *msg = static_cast<BluetoothLERawAdvertisementsResponse *>(field_ptr);
      *msg = value.as_message<BluetoothLERawAdvertisementsResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 79: {
      BluetoothDeviceRequest *msg = static_cast<BluetoothDeviceRequest *>(field_ptr);
      *msg = value.as_message<BluetoothDeviceRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 80: {
      BluetoothDeviceConnectionResponse *msg = static_cast<BluetoothDeviceConnectionResponse *>(field_ptr);
      *msg = value.as_message<BluetoothDeviceConnectionResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 81: {
      BluetoothGATTGetServicesRequest *msg = static_cast<BluetoothGATTGetServicesRequest *>(field_ptr);
      *msg = value.as_message<BluetoothGATTGetServicesRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 82: {
      BluetoothGATTDescriptor *msg = static_cast<BluetoothGATTDescriptor *>(field_ptr);
      *msg = value.as_message<BluetoothGATTDescriptor>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 83: {
      BluetoothGATTCharacteristic *msg = static_cast<BluetoothGATTCharacteristic *>(field_ptr);
      *msg = value.as_message<BluetoothGATTCharacteristic>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 84: {
      BluetoothGATTService *msg = static_cast<BluetoothGATTService *>(field_ptr);
      *msg = value.as_message<BluetoothGATTService>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 85: {
      BluetoothGATTGetServicesResponse *msg = static_cast<BluetoothGATTGetServicesResponse *>(field_ptr);
      *msg = value.as_message<BluetoothGATTGetServicesResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 86: {
      BluetoothGATTGetServicesDoneResponse *msg = static_cast<BluetoothGATTGetServicesDoneResponse *>(field_ptr);
      *msg = value.as_message<BluetoothGATTGetServicesDoneResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 87: {
      BluetoothGATTReadRequest *msg = static_cast<BluetoothGATTReadRequest *>(field_ptr);
      *msg = value.as_message<BluetoothGATTReadRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 88: {
      BluetoothGATTReadResponse *msg = static_cast<BluetoothGATTReadResponse *>(field_ptr);
      *msg = value.as_message<BluetoothGATTReadResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 89: {
      BluetoothGATTWriteRequest *msg = static_cast<BluetoothGATTWriteRequest *>(field_ptr);
      *msg = value.as_message<BluetoothGATTWriteRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 90: {
      BluetoothGATTReadDescriptorRequest *msg = static_cast<BluetoothGATTReadDescriptorRequest *>(field_ptr);
      *msg = value.as_message<BluetoothGATTReadDescriptorRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 91: {
      BluetoothGATTWriteDescriptorRequest *msg = static_cast<BluetoothGATTWriteDescriptorRequest *>(field_ptr);
      *msg = value.as_message<BluetoothGATTWriteDescriptorRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 92: {
      BluetoothGATTNotifyRequest *msg = static_cast<BluetoothGATTNotifyRequest *>(field_ptr);
      *msg = value.as_message<BluetoothGATTNotifyRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 93: {
      BluetoothGATTNotifyDataResponse *msg = static_cast<BluetoothGATTNotifyDataResponse *>(field_ptr);
      *msg = value.as_message<BluetoothGATTNotifyDataResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 94: {
      SubscribeBluetoothConnectionsFreeRequest *msg =
          static_cast<SubscribeBluetoothConnectionsFreeRequest *>(field_ptr);
      *msg = value.as_message<SubscribeBluetoothConnectionsFreeRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 95: {
      BluetoothConnectionsFreeResponse *msg = static_cast<BluetoothConnectionsFreeResponse *>(field_ptr);
      *msg = value.as_message<BluetoothConnectionsFreeResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 96: {
      BluetoothGATTErrorResponse *msg = static_cast<BluetoothGATTErrorResponse *>(field_ptr);
      *msg = value.as_message<BluetoothGATTErrorResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 97: {
      BluetoothGATTWriteResponse *msg = static_cast<BluetoothGATTWriteResponse *>(field_ptr);
      *msg = value.as_message<BluetoothGATTWriteResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 98: {
      BluetoothGATTNotifyResponse *msg = static_cast<BluetoothGATTNotifyResponse *>(field_ptr);
      *msg = value.as_message<BluetoothGATTNotifyResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 99: {
      BluetoothDevicePairingResponse *msg = static_cast<BluetoothDevicePairingResponse *>(field_ptr);
      *msg = value.as_message<BluetoothDevicePairingResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 100: {
      BluetoothDeviceUnpairingResponse *msg = static_cast<BluetoothDeviceUnpairingResponse *>(field_ptr);
      *msg = value.as_message<BluetoothDeviceUnpairingResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 101: {
      UnsubscribeBluetoothLEAdvertisementsRequest *msg =
          static_cast<UnsubscribeBluetoothLEAdvertisementsRequest *>(field_ptr);
      *msg = value.as_message<UnsubscribeBluetoothLEAdvertisementsRequest>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 102: {
      BluetoothDeviceClearCacheResponse *msg = static_cast<BluetoothDeviceClearCacheResponse *>(field_ptr);
      *msg = value.as_message<BluetoothDeviceClearCacheResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 103: {
      BluetoothScannerStateResponse *msg = static_cast<BluetoothScannerStateResponse *>(field_ptr);
      *msg = value.as_message<BluetoothScannerStateResponse>();
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 104: {
      BluetoothScannerSetModeRequest *msg = static_cast<BluetoothScannerSetModeRequest *>(field_ptr);
      *msg = value.as_message<BluetoothScannerSetModeRequest>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 105: {
      SubscribeVoiceAssistantRequest *msg = static_cast<SubscribeVoiceAssistantRequest *>(field_ptr);
      *msg = value.as_message<SubscribeVoiceAssistantRequest>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 106: {
      VoiceAssistantAudioSettings *msg = static_cast<VoiceAssistantAudioSettings *>(field_ptr);
      *msg = value.as_message<VoiceAssistantAudioSettings>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 107: {
      VoiceAssistantRequest *msg = static_cast<VoiceAssistantRequest *>(field_ptr);
      *msg = value.as_message<VoiceAssistantRequest>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 108: {
      VoiceAssistantResponse *msg = static_cast<VoiceAssistantResponse *>(field_ptr);
      *msg = value.as_message<VoiceAssistantResponse>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 109: {
      VoiceAssistantEventData *msg = static_cast<VoiceAssistantEventData *>(field_ptr);
      *msg = value.as_message<VoiceAssistantEventData>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 110: {
      VoiceAssistantEventResponse *msg = static_cast<VoiceAssistantEventResponse *>(field_ptr);
      *msg = value.as_message<VoiceAssistantEventResponse>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 111: {
      VoiceAssistantAudio *msg = static_cast<VoiceAssistantAudio *>(field_ptr);
      *msg = value.as_message<VoiceAssistantAudio>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 112: {
      VoiceAssistantTimerEventResponse *msg = static_cast<VoiceAssistantTimerEventResponse *>(field_ptr);
      *msg = value.as_message<VoiceAssistantTimerEventResponse>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 113: {
      VoiceAssistantAnnounceRequest *msg = static_cast<VoiceAssistantAnnounceRequest *>(field_ptr);
      *msg = value.as_message<VoiceAssistantAnnounceRequest>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 114: {
      VoiceAssistantAnnounceFinished *msg = static_cast<VoiceAssistantAnnounceFinished *>(field_ptr);
      *msg = value.as_message<VoiceAssistantAnnounceFinished>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 115: {
      VoiceAssistantWakeWord *msg = static_cast<VoiceAssistantWakeWord *>(field_ptr);
      *msg = value.as_message<VoiceAssistantWakeWord>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 116: {
      VoiceAssistantConfigurationRequest *msg = static_cast<VoiceAssistantConfigurationRequest *>(field_ptr);
      *msg = value.as_message<VoiceAssistantConfigurationRequest>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 117: {
      VoiceAssistantConfigurationResponse *msg = static_cast<VoiceAssistantConfigurationResponse *>(field_ptr);
      *msg = value.as_message<VoiceAssistantConfigurationResponse>();
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 118: {
      VoiceAssistantSetConfiguration *msg = static_cast<VoiceAssistantSetConfiguration *>(field_ptr);
      *msg = value.as_message<VoiceAssistantSetConfiguration>();
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 119: {
      ListEntitiesAlarmControlPanelResponse *msg = static_cast<ListEntitiesAlarmControlPanelResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesAlarmControlPanelResponse>();
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 120: {
      AlarmControlPanelStateResponse *msg = static_cast<AlarmControlPanelStateResponse *>(field_ptr);
      *msg = value.as_message<AlarmControlPanelStateResponse>();
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 121: {
      AlarmControlPanelCommandRequest *msg = static_cast<AlarmControlPanelCommandRequest *>(field_ptr);
      *msg = value.as_message<AlarmControlPanelCommandRequest>();
      break;
    }
#endif
#ifdef USE_TEXT
    case 122: {
      ListEntitiesTextResponse *msg = static_cast<ListEntitiesTextResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesTextResponse>();
      break;
    }
#endif
#ifdef USE_TEXT
    case 123: {
      TextStateResponse *msg = static_cast<TextStateResponse *>(field_ptr);
      *msg = value.as_message<TextStateResponse>();
      break;
    }
#endif
#ifdef USE_TEXT
    case 124: {
      TextCommandRequest *msg = static_cast<TextCommandRequest *>(field_ptr);
      *msg = value.as_message<TextCommandRequest>();
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 125: {
      ListEntitiesDateResponse *msg = static_cast<ListEntitiesDateResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesDateResponse>();
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 126: {
      DateStateResponse *msg = static_cast<DateStateResponse *>(field_ptr);
      *msg = value.as_message<DateStateResponse>();
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 127: {
      DateCommandRequest *msg = static_cast<DateCommandRequest *>(field_ptr);
      *msg = value.as_message<DateCommandRequest>();
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 128: {
      ListEntitiesTimeResponse *msg = static_cast<ListEntitiesTimeResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesTimeResponse>();
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 129: {
      TimeStateResponse *msg = static_cast<TimeStateResponse *>(field_ptr);
      *msg = value.as_message<TimeStateResponse>();
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 130: {
      TimeCommandRequest *msg = static_cast<TimeCommandRequest *>(field_ptr);
      *msg = value.as_message<TimeCommandRequest>();
      break;
    }
#endif
#ifdef USE_EVENT
    case 131: {
      ListEntitiesEventResponse *msg = static_cast<ListEntitiesEventResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesEventResponse>();
      break;
    }
#endif
#ifdef USE_EVENT
    case 132: {
      EventResponse *msg = static_cast<EventResponse *>(field_ptr);
      *msg = value.as_message<EventResponse>();
      break;
    }
#endif
#ifdef USE_VALVE
    case 133: {
      ListEntitiesValveResponse *msg = static_cast<ListEntitiesValveResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesValveResponse>();
      break;
    }
#endif
#ifdef USE_VALVE
    case 134: {
      ValveStateResponse *msg = static_cast<ValveStateResponse *>(field_ptr);
      *msg = value.as_message<ValveStateResponse>();
      break;
    }
#endif
#ifdef USE_VALVE
    case 135: {
      ValveCommandRequest *msg = static_cast<ValveCommandRequest *>(field_ptr);
      *msg = value.as_message<ValveCommandRequest>();
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 136: {
      ListEntitiesDateTimeResponse *msg = static_cast<ListEntitiesDateTimeResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesDateTimeResponse>();
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 137: {
      DateTimeStateResponse *msg = static_cast<DateTimeStateResponse *>(field_ptr);
      *msg = value.as_message<DateTimeStateResponse>();
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 138: {
      DateTimeCommandRequest *msg = static_cast<DateTimeCommandRequest *>(field_ptr);
      *msg = value.as_message<DateTimeCommandRequest>();
      break;
    }
#endif
#ifdef USE_UPDATE
    case 139: {
      ListEntitiesUpdateResponse *msg = static_cast<ListEntitiesUpdateResponse *>(field_ptr);
      *msg = value.as_message<ListEntitiesUpdateResponse>();
      break;
    }
#endif
#ifdef USE_UPDATE
    case 140: {
      UpdateStateResponse *msg = static_cast<UpdateStateResponse *>(field_ptr);
      *msg = value.as_message<UpdateStateResponse>();
      break;
    }
#endif
#ifdef USE_UPDATE
    case 141: {
      UpdateCommandRequest *msg = static_cast<UpdateCommandRequest *>(field_ptr);
      *msg = value.as_message<UpdateCommandRequest>();
      break;
    }
#endif
    default:
      break;
  }
}

void size_message_field_by_type(uint32_t &total_size, uint8_t precalced_field_id_size, const void *field_ptr,
                                uint8_t message_type_id, bool force) {
  switch (message_type_id) {
    case 1: {
      const HelloRequest *msg = static_cast<const HelloRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 2: {
      const HelloResponse *msg = static_cast<const HelloResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 3: {
      const ConnectRequest *msg = static_cast<const ConnectRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 4: {
      const ConnectResponse *msg = static_cast<const ConnectResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 5: {
      const DisconnectRequest *msg = static_cast<const DisconnectRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 6: {
      const DisconnectResponse *msg = static_cast<const DisconnectResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 7: {
      const PingRequest *msg = static_cast<const PingRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 8: {
      const PingResponse *msg = static_cast<const PingResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 9: {
      const DeviceInfoRequest *msg = static_cast<const DeviceInfoRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 10: {
      const AreaInfo *msg = static_cast<const AreaInfo *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 11: {
      const DeviceInfo *msg = static_cast<const DeviceInfo *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 12: {
      const DeviceInfoResponse *msg = static_cast<const DeviceInfoResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 13: {
      const ListEntitiesRequest *msg = static_cast<const ListEntitiesRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 14: {
      const ListEntitiesDoneResponse *msg = static_cast<const ListEntitiesDoneResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 15: {
      const SubscribeStatesRequest *msg = static_cast<const SubscribeStatesRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#ifdef USE_BINARY_SENSOR
    case 16: {
      const ListEntitiesBinarySensorResponse *msg = static_cast<const ListEntitiesBinarySensorResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BINARY_SENSOR
    case 17: {
      const BinarySensorStateResponse *msg = static_cast<const BinarySensorStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_COVER
    case 18: {
      const ListEntitiesCoverResponse *msg = static_cast<const ListEntitiesCoverResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_COVER
    case 19: {
      const CoverStateResponse *msg = static_cast<const CoverStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_COVER
    case 20: {
      const CoverCommandRequest *msg = static_cast<const CoverCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_FAN
    case 21: {
      const ListEntitiesFanResponse *msg = static_cast<const ListEntitiesFanResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_FAN
    case 22: {
      const FanStateResponse *msg = static_cast<const FanStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_FAN
    case 23: {
      const FanCommandRequest *msg = static_cast<const FanCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 24: {
      const ListEntitiesLightResponse *msg = static_cast<const ListEntitiesLightResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 25: {
      const LightStateResponse *msg = static_cast<const LightStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 26: {
      const LightCommandRequest *msg = static_cast<const LightCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SENSOR
    case 27: {
      const ListEntitiesSensorResponse *msg = static_cast<const ListEntitiesSensorResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SENSOR
    case 28: {
      const SensorStateResponse *msg = static_cast<const SensorStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 29: {
      const ListEntitiesSwitchResponse *msg = static_cast<const ListEntitiesSwitchResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 30: {
      const SwitchStateResponse *msg = static_cast<const SwitchStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 31: {
      const SwitchCommandRequest *msg = static_cast<const SwitchCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 32: {
      const ListEntitiesTextSensorResponse *msg = static_cast<const ListEntitiesTextSensorResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 33: {
      const TextSensorStateResponse *msg = static_cast<const TextSensorStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
    case 34: {
      const SubscribeLogsRequest *msg = static_cast<const SubscribeLogsRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 35: {
      const SubscribeLogsResponse *msg = static_cast<const SubscribeLogsResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#ifdef USE_API_NOISE
    case 36: {
      const NoiseEncryptionSetKeyRequest *msg = static_cast<const NoiseEncryptionSetKeyRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_API_NOISE
    case 37: {
      const NoiseEncryptionSetKeyResponse *msg = static_cast<const NoiseEncryptionSetKeyResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
    case 38: {
      const SubscribeHomeassistantServicesRequest *msg =
          static_cast<const SubscribeHomeassistantServicesRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 39: {
      const HomeassistantServiceMap *msg = static_cast<const HomeassistantServiceMap *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 40: {
      const HomeassistantServiceResponse *msg = static_cast<const HomeassistantServiceResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 41: {
      const SubscribeHomeAssistantStatesRequest *msg =
          static_cast<const SubscribeHomeAssistantStatesRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 42: {
      const SubscribeHomeAssistantStateResponse *msg =
          static_cast<const SubscribeHomeAssistantStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 43: {
      const HomeAssistantStateResponse *msg = static_cast<const HomeAssistantStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 44: {
      const GetTimeRequest *msg = static_cast<const GetTimeRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 45: {
      const GetTimeResponse *msg = static_cast<const GetTimeResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 46: {
      const ListEntitiesServicesArgument *msg = static_cast<const ListEntitiesServicesArgument *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 47: {
      const ListEntitiesServicesResponse *msg = static_cast<const ListEntitiesServicesResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 48: {
      const ExecuteServiceArgument *msg = static_cast<const ExecuteServiceArgument *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
    case 49: {
      const ExecuteServiceRequest *msg = static_cast<const ExecuteServiceRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#ifdef USE_CAMERA
    case 50: {
      const ListEntitiesCameraResponse *msg = static_cast<const ListEntitiesCameraResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_CAMERA
    case 51: {
      const CameraImageResponse *msg = static_cast<const CameraImageResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_CAMERA
    case 52: {
      const CameraImageRequest *msg = static_cast<const CameraImageRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 53: {
      const ListEntitiesClimateResponse *msg = static_cast<const ListEntitiesClimateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 54: {
      const ClimateStateResponse *msg = static_cast<const ClimateStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 55: {
      const ClimateCommandRequest *msg = static_cast<const ClimateCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 56: {
      const ListEntitiesNumberResponse *msg = static_cast<const ListEntitiesNumberResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 57: {
      const NumberStateResponse *msg = static_cast<const NumberStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 58: {
      const NumberCommandRequest *msg = static_cast<const NumberCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SELECT
    case 59: {
      const ListEntitiesSelectResponse *msg = static_cast<const ListEntitiesSelectResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SELECT
    case 60: {
      const SelectStateResponse *msg = static_cast<const SelectStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SELECT
    case 61: {
      const SelectCommandRequest *msg = static_cast<const SelectCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SIREN
    case 62: {
      const ListEntitiesSirenResponse *msg = static_cast<const ListEntitiesSirenResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SIREN
    case 63: {
      const SirenStateResponse *msg = static_cast<const SirenStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_SIREN
    case 64: {
      const SirenCommandRequest *msg = static_cast<const SirenCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_LOCK
    case 65: {
      const ListEntitiesLockResponse *msg = static_cast<const ListEntitiesLockResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_LOCK
    case 66: {
      const LockStateResponse *msg = static_cast<const LockStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_LOCK
    case 67: {
      const LockCommandRequest *msg = static_cast<const LockCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BUTTON
    case 68: {
      const ListEntitiesButtonResponse *msg = static_cast<const ListEntitiesButtonResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BUTTON
    case 69: {
      const ButtonCommandRequest *msg = static_cast<const ButtonCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 70: {
      const MediaPlayerSupportedFormat *msg = static_cast<const MediaPlayerSupportedFormat *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 71: {
      const ListEntitiesMediaPlayerResponse *msg = static_cast<const ListEntitiesMediaPlayerResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 72: {
      const MediaPlayerStateResponse *msg = static_cast<const MediaPlayerStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 73: {
      const MediaPlayerCommandRequest *msg = static_cast<const MediaPlayerCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 74: {
      const SubscribeBluetoothLEAdvertisementsRequest *msg =
          static_cast<const SubscribeBluetoothLEAdvertisementsRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 75: {
      const BluetoothServiceData *msg = static_cast<const BluetoothServiceData *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 76: {
      const BluetoothLEAdvertisementResponse *msg = static_cast<const BluetoothLEAdvertisementResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 77: {
      const BluetoothLERawAdvertisement *msg = static_cast<const BluetoothLERawAdvertisement *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 78: {
      const BluetoothLERawAdvertisementsResponse *msg =
          static_cast<const BluetoothLERawAdvertisementsResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 79: {
      const BluetoothDeviceRequest *msg = static_cast<const BluetoothDeviceRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 80: {
      const BluetoothDeviceConnectionResponse *msg = static_cast<const BluetoothDeviceConnectionResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 81: {
      const BluetoothGATTGetServicesRequest *msg = static_cast<const BluetoothGATTGetServicesRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 82: {
      const BluetoothGATTDescriptor *msg = static_cast<const BluetoothGATTDescriptor *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 83: {
      const BluetoothGATTCharacteristic *msg = static_cast<const BluetoothGATTCharacteristic *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 84: {
      const BluetoothGATTService *msg = static_cast<const BluetoothGATTService *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 85: {
      const BluetoothGATTGetServicesResponse *msg = static_cast<const BluetoothGATTGetServicesResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 86: {
      const BluetoothGATTGetServicesDoneResponse *msg =
          static_cast<const BluetoothGATTGetServicesDoneResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 87: {
      const BluetoothGATTReadRequest *msg = static_cast<const BluetoothGATTReadRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 88: {
      const BluetoothGATTReadResponse *msg = static_cast<const BluetoothGATTReadResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 89: {
      const BluetoothGATTWriteRequest *msg = static_cast<const BluetoothGATTWriteRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 90: {
      const BluetoothGATTReadDescriptorRequest *msg =
          static_cast<const BluetoothGATTReadDescriptorRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 91: {
      const BluetoothGATTWriteDescriptorRequest *msg =
          static_cast<const BluetoothGATTWriteDescriptorRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 92: {
      const BluetoothGATTNotifyRequest *msg = static_cast<const BluetoothGATTNotifyRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 93: {
      const BluetoothGATTNotifyDataResponse *msg = static_cast<const BluetoothGATTNotifyDataResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 94: {
      const SubscribeBluetoothConnectionsFreeRequest *msg =
          static_cast<const SubscribeBluetoothConnectionsFreeRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 95: {
      const BluetoothConnectionsFreeResponse *msg = static_cast<const BluetoothConnectionsFreeResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 96: {
      const BluetoothGATTErrorResponse *msg = static_cast<const BluetoothGATTErrorResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 97: {
      const BluetoothGATTWriteResponse *msg = static_cast<const BluetoothGATTWriteResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 98: {
      const BluetoothGATTNotifyResponse *msg = static_cast<const BluetoothGATTNotifyResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 99: {
      const BluetoothDevicePairingResponse *msg = static_cast<const BluetoothDevicePairingResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 100: {
      const BluetoothDeviceUnpairingResponse *msg = static_cast<const BluetoothDeviceUnpairingResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 101: {
      const UnsubscribeBluetoothLEAdvertisementsRequest *msg =
          static_cast<const UnsubscribeBluetoothLEAdvertisementsRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 102: {
      const BluetoothDeviceClearCacheResponse *msg = static_cast<const BluetoothDeviceClearCacheResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 103: {
      const BluetoothScannerStateResponse *msg = static_cast<const BluetoothScannerStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 104: {
      const BluetoothScannerSetModeRequest *msg = static_cast<const BluetoothScannerSetModeRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 105: {
      const SubscribeVoiceAssistantRequest *msg = static_cast<const SubscribeVoiceAssistantRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 106: {
      const VoiceAssistantAudioSettings *msg = static_cast<const VoiceAssistantAudioSettings *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 107: {
      const VoiceAssistantRequest *msg = static_cast<const VoiceAssistantRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 108: {
      const VoiceAssistantResponse *msg = static_cast<const VoiceAssistantResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 109: {
      const VoiceAssistantEventData *msg = static_cast<const VoiceAssistantEventData *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 110: {
      const VoiceAssistantEventResponse *msg = static_cast<const VoiceAssistantEventResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 111: {
      const VoiceAssistantAudio *msg = static_cast<const VoiceAssistantAudio *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 112: {
      const VoiceAssistantTimerEventResponse *msg = static_cast<const VoiceAssistantTimerEventResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 113: {
      const VoiceAssistantAnnounceRequest *msg = static_cast<const VoiceAssistantAnnounceRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 114: {
      const VoiceAssistantAnnounceFinished *msg = static_cast<const VoiceAssistantAnnounceFinished *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 115: {
      const VoiceAssistantWakeWord *msg = static_cast<const VoiceAssistantWakeWord *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 116: {
      const VoiceAssistantConfigurationRequest *msg =
          static_cast<const VoiceAssistantConfigurationRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 117: {
      const VoiceAssistantConfigurationResponse *msg =
          static_cast<const VoiceAssistantConfigurationResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 118: {
      const VoiceAssistantSetConfiguration *msg = static_cast<const VoiceAssistantSetConfiguration *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 119: {
      const ListEntitiesAlarmControlPanelResponse *msg =
          static_cast<const ListEntitiesAlarmControlPanelResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 120: {
      const AlarmControlPanelStateResponse *msg = static_cast<const AlarmControlPanelStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 121: {
      const AlarmControlPanelCommandRequest *msg = static_cast<const AlarmControlPanelCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_TEXT
    case 122: {
      const ListEntitiesTextResponse *msg = static_cast<const ListEntitiesTextResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_TEXT
    case 123: {
      const TextStateResponse *msg = static_cast<const TextStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_TEXT
    case 124: {
      const TextCommandRequest *msg = static_cast<const TextCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 125: {
      const ListEntitiesDateResponse *msg = static_cast<const ListEntitiesDateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 126: {
      const DateStateResponse *msg = static_cast<const DateStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 127: {
      const DateCommandRequest *msg = static_cast<const DateCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 128: {
      const ListEntitiesTimeResponse *msg = static_cast<const ListEntitiesTimeResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 129: {
      const TimeStateResponse *msg = static_cast<const TimeStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 130: {
      const TimeCommandRequest *msg = static_cast<const TimeCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_EVENT
    case 131: {
      const ListEntitiesEventResponse *msg = static_cast<const ListEntitiesEventResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_EVENT
    case 132: {
      const EventResponse *msg = static_cast<const EventResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VALVE
    case 133: {
      const ListEntitiesValveResponse *msg = static_cast<const ListEntitiesValveResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VALVE
    case 134: {
      const ValveStateResponse *msg = static_cast<const ValveStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_VALVE
    case 135: {
      const ValveCommandRequest *msg = static_cast<const ValveCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 136: {
      const ListEntitiesDateTimeResponse *msg = static_cast<const ListEntitiesDateTimeResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 137: {
      const DateTimeStateResponse *msg = static_cast<const DateTimeStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 138: {
      const DateTimeCommandRequest *msg = static_cast<const DateTimeCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 139: {
      const ListEntitiesUpdateResponse *msg = static_cast<const ListEntitiesUpdateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 140: {
      const UpdateStateResponse *msg = static_cast<const UpdateStateResponse *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 141: {
      const UpdateCommandRequest *msg = static_cast<const UpdateCommandRequest *>(field_ptr);
      ProtoSize::add_message_object(total_size, precalced_field_id_size, *msg, force);
      break;
    }
#endif
    default:
      break;
  }
}

void encode_repeated_message_field_by_type(ProtoWriteBuffer &buffer, uint8_t field_num, const void *field_ptr,
                                           uint8_t message_type_id) {
  switch (message_type_id) {
    case 1: {
      const std::vector<HelloRequest> *vec = static_cast<const std::vector<HelloRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<HelloRequest>(field_num, msg, true);
      }
      break;
    }
    case 2: {
      const std::vector<HelloResponse> *vec = static_cast<const std::vector<HelloResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<HelloResponse>(field_num, msg, true);
      }
      break;
    }
    case 3: {
      const std::vector<ConnectRequest> *vec = static_cast<const std::vector<ConnectRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ConnectRequest>(field_num, msg, true);
      }
      break;
    }
    case 4: {
      const std::vector<ConnectResponse> *vec = static_cast<const std::vector<ConnectResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ConnectResponse>(field_num, msg, true);
      }
      break;
    }
    case 5: {
      const std::vector<DisconnectRequest> *vec = static_cast<const std::vector<DisconnectRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DisconnectRequest>(field_num, msg, true);
      }
      break;
    }
    case 6: {
      const std::vector<DisconnectResponse> *vec = static_cast<const std::vector<DisconnectResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DisconnectResponse>(field_num, msg, true);
      }
      break;
    }
    case 7: {
      const std::vector<PingRequest> *vec = static_cast<const std::vector<PingRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<PingRequest>(field_num, msg, true);
      }
      break;
    }
    case 8: {
      const std::vector<PingResponse> *vec = static_cast<const std::vector<PingResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<PingResponse>(field_num, msg, true);
      }
      break;
    }
    case 9: {
      const std::vector<DeviceInfoRequest> *vec = static_cast<const std::vector<DeviceInfoRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DeviceInfoRequest>(field_num, msg, true);
      }
      break;
    }
    case 10: {
      const std::vector<AreaInfo> *vec = static_cast<const std::vector<AreaInfo> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<AreaInfo>(field_num, msg, true);
      }
      break;
    }
    case 11: {
      const std::vector<DeviceInfo> *vec = static_cast<const std::vector<DeviceInfo> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DeviceInfo>(field_num, msg, true);
      }
      break;
    }
    case 12: {
      const std::vector<DeviceInfoResponse> *vec = static_cast<const std::vector<DeviceInfoResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DeviceInfoResponse>(field_num, msg, true);
      }
      break;
    }
    case 13: {
      const std::vector<ListEntitiesRequest> *vec = static_cast<const std::vector<ListEntitiesRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesRequest>(field_num, msg, true);
      }
      break;
    }
    case 14: {
      const std::vector<ListEntitiesDoneResponse> *vec =
          static_cast<const std::vector<ListEntitiesDoneResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesDoneResponse>(field_num, msg, true);
      }
      break;
    }
    case 15: {
      const std::vector<SubscribeStatesRequest> *vec =
          static_cast<const std::vector<SubscribeStatesRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeStatesRequest>(field_num, msg, true);
      }
      break;
    }
#ifdef USE_BINARY_SENSOR
    case 16: {
      const std::vector<ListEntitiesBinarySensorResponse> *vec =
          static_cast<const std::vector<ListEntitiesBinarySensorResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesBinarySensorResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BINARY_SENSOR
    case 17: {
      const std::vector<BinarySensorStateResponse> *vec =
          static_cast<const std::vector<BinarySensorStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BinarySensorStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_COVER
    case 18: {
      const std::vector<ListEntitiesCoverResponse> *vec =
          static_cast<const std::vector<ListEntitiesCoverResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesCoverResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_COVER
    case 19: {
      const std::vector<CoverStateResponse> *vec = static_cast<const std::vector<CoverStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<CoverStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_COVER
    case 20: {
      const std::vector<CoverCommandRequest> *vec = static_cast<const std::vector<CoverCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<CoverCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_FAN
    case 21: {
      const std::vector<ListEntitiesFanResponse> *vec =
          static_cast<const std::vector<ListEntitiesFanResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesFanResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_FAN
    case 22: {
      const std::vector<FanStateResponse> *vec = static_cast<const std::vector<FanStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<FanStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_FAN
    case 23: {
      const std::vector<FanCommandRequest> *vec = static_cast<const std::vector<FanCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<FanCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_LIGHT
    case 24: {
      const std::vector<ListEntitiesLightResponse> *vec =
          static_cast<const std::vector<ListEntitiesLightResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesLightResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_LIGHT
    case 25: {
      const std::vector<LightStateResponse> *vec = static_cast<const std::vector<LightStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<LightStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_LIGHT
    case 26: {
      const std::vector<LightCommandRequest> *vec = static_cast<const std::vector<LightCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<LightCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SENSOR
    case 27: {
      const std::vector<ListEntitiesSensorResponse> *vec =
          static_cast<const std::vector<ListEntitiesSensorResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesSensorResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SENSOR
    case 28: {
      const std::vector<SensorStateResponse> *vec = static_cast<const std::vector<SensorStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SensorStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SWITCH
    case 29: {
      const std::vector<ListEntitiesSwitchResponse> *vec =
          static_cast<const std::vector<ListEntitiesSwitchResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesSwitchResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SWITCH
    case 30: {
      const std::vector<SwitchStateResponse> *vec = static_cast<const std::vector<SwitchStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SwitchStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SWITCH
    case 31: {
      const std::vector<SwitchCommandRequest> *vec = static_cast<const std::vector<SwitchCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SwitchCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 32: {
      const std::vector<ListEntitiesTextSensorResponse> *vec =
          static_cast<const std::vector<ListEntitiesTextSensorResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesTextSensorResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 33: {
      const std::vector<TextSensorStateResponse> *vec =
          static_cast<const std::vector<TextSensorStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<TextSensorStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
    case 34: {
      const std::vector<SubscribeLogsRequest> *vec = static_cast<const std::vector<SubscribeLogsRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeLogsRequest>(field_num, msg, true);
      }
      break;
    }
    case 35: {
      const std::vector<SubscribeLogsResponse> *vec =
          static_cast<const std::vector<SubscribeLogsResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeLogsResponse>(field_num, msg, true);
      }
      break;
    }
#ifdef USE_API_NOISE
    case 36: {
      const std::vector<NoiseEncryptionSetKeyRequest> *vec =
          static_cast<const std::vector<NoiseEncryptionSetKeyRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<NoiseEncryptionSetKeyRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_API_NOISE
    case 37: {
      const std::vector<NoiseEncryptionSetKeyResponse> *vec =
          static_cast<const std::vector<NoiseEncryptionSetKeyResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<NoiseEncryptionSetKeyResponse>(field_num, msg, true);
      }
      break;
    }
#endif
    case 38: {
      const std::vector<SubscribeHomeassistantServicesRequest> *vec =
          static_cast<const std::vector<SubscribeHomeassistantServicesRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeHomeassistantServicesRequest>(field_num, msg, true);
      }
      break;
    }
    case 39: {
      const std::vector<HomeassistantServiceMap> *vec =
          static_cast<const std::vector<HomeassistantServiceMap> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<HomeassistantServiceMap>(field_num, msg, true);
      }
      break;
    }
    case 40: {
      const std::vector<HomeassistantServiceResponse> *vec =
          static_cast<const std::vector<HomeassistantServiceResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<HomeassistantServiceResponse>(field_num, msg, true);
      }
      break;
    }
    case 41: {
      const std::vector<SubscribeHomeAssistantStatesRequest> *vec =
          static_cast<const std::vector<SubscribeHomeAssistantStatesRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeHomeAssistantStatesRequest>(field_num, msg, true);
      }
      break;
    }
    case 42: {
      const std::vector<SubscribeHomeAssistantStateResponse> *vec =
          static_cast<const std::vector<SubscribeHomeAssistantStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeHomeAssistantStateResponse>(field_num, msg, true);
      }
      break;
    }
    case 43: {
      const std::vector<HomeAssistantStateResponse> *vec =
          static_cast<const std::vector<HomeAssistantStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<HomeAssistantStateResponse>(field_num, msg, true);
      }
      break;
    }
    case 44: {
      const std::vector<GetTimeRequest> *vec = static_cast<const std::vector<GetTimeRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<GetTimeRequest>(field_num, msg, true);
      }
      break;
    }
    case 45: {
      const std::vector<GetTimeResponse> *vec = static_cast<const std::vector<GetTimeResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<GetTimeResponse>(field_num, msg, true);
      }
      break;
    }
    case 46: {
      const std::vector<ListEntitiesServicesArgument> *vec =
          static_cast<const std::vector<ListEntitiesServicesArgument> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesServicesArgument>(field_num, msg, true);
      }
      break;
    }
    case 47: {
      const std::vector<ListEntitiesServicesResponse> *vec =
          static_cast<const std::vector<ListEntitiesServicesResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesServicesResponse>(field_num, msg, true);
      }
      break;
    }
    case 48: {
      const std::vector<ExecuteServiceArgument> *vec =
          static_cast<const std::vector<ExecuteServiceArgument> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ExecuteServiceArgument>(field_num, msg, true);
      }
      break;
    }
    case 49: {
      const std::vector<ExecuteServiceRequest> *vec =
          static_cast<const std::vector<ExecuteServiceRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ExecuteServiceRequest>(field_num, msg, true);
      }
      break;
    }
#ifdef USE_CAMERA
    case 50: {
      const std::vector<ListEntitiesCameraResponse> *vec =
          static_cast<const std::vector<ListEntitiesCameraResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesCameraResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_CAMERA
    case 51: {
      const std::vector<CameraImageResponse> *vec = static_cast<const std::vector<CameraImageResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<CameraImageResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_CAMERA
    case 52: {
      const std::vector<CameraImageRequest> *vec = static_cast<const std::vector<CameraImageRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<CameraImageRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 53: {
      const std::vector<ListEntitiesClimateResponse> *vec =
          static_cast<const std::vector<ListEntitiesClimateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesClimateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 54: {
      const std::vector<ClimateStateResponse> *vec = static_cast<const std::vector<ClimateStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ClimateStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 55: {
      const std::vector<ClimateCommandRequest> *vec =
          static_cast<const std::vector<ClimateCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ClimateCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_NUMBER
    case 56: {
      const std::vector<ListEntitiesNumberResponse> *vec =
          static_cast<const std::vector<ListEntitiesNumberResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesNumberResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_NUMBER
    case 57: {
      const std::vector<NumberStateResponse> *vec = static_cast<const std::vector<NumberStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<NumberStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_NUMBER
    case 58: {
      const std::vector<NumberCommandRequest> *vec = static_cast<const std::vector<NumberCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<NumberCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SELECT
    case 59: {
      const std::vector<ListEntitiesSelectResponse> *vec =
          static_cast<const std::vector<ListEntitiesSelectResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesSelectResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SELECT
    case 60: {
      const std::vector<SelectStateResponse> *vec = static_cast<const std::vector<SelectStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SelectStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SELECT
    case 61: {
      const std::vector<SelectCommandRequest> *vec = static_cast<const std::vector<SelectCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SelectCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SIREN
    case 62: {
      const std::vector<ListEntitiesSirenResponse> *vec =
          static_cast<const std::vector<ListEntitiesSirenResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesSirenResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SIREN
    case 63: {
      const std::vector<SirenStateResponse> *vec = static_cast<const std::vector<SirenStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SirenStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_SIREN
    case 64: {
      const std::vector<SirenCommandRequest> *vec = static_cast<const std::vector<SirenCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SirenCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_LOCK
    case 65: {
      const std::vector<ListEntitiesLockResponse> *vec =
          static_cast<const std::vector<ListEntitiesLockResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesLockResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_LOCK
    case 66: {
      const std::vector<LockStateResponse> *vec = static_cast<const std::vector<LockStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<LockStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_LOCK
    case 67: {
      const std::vector<LockCommandRequest> *vec = static_cast<const std::vector<LockCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<LockCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BUTTON
    case 68: {
      const std::vector<ListEntitiesButtonResponse> *vec =
          static_cast<const std::vector<ListEntitiesButtonResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesButtonResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BUTTON
    case 69: {
      const std::vector<ButtonCommandRequest> *vec = static_cast<const std::vector<ButtonCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ButtonCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 70: {
      const std::vector<MediaPlayerSupportedFormat> *vec =
          static_cast<const std::vector<MediaPlayerSupportedFormat> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<MediaPlayerSupportedFormat>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 71: {
      const std::vector<ListEntitiesMediaPlayerResponse> *vec =
          static_cast<const std::vector<ListEntitiesMediaPlayerResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesMediaPlayerResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 72: {
      const std::vector<MediaPlayerStateResponse> *vec =
          static_cast<const std::vector<MediaPlayerStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<MediaPlayerStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 73: {
      const std::vector<MediaPlayerCommandRequest> *vec =
          static_cast<const std::vector<MediaPlayerCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<MediaPlayerCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 74: {
      const std::vector<SubscribeBluetoothLEAdvertisementsRequest> *vec =
          static_cast<const std::vector<SubscribeBluetoothLEAdvertisementsRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeBluetoothLEAdvertisementsRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 75: {
      const std::vector<BluetoothServiceData> *vec = static_cast<const std::vector<BluetoothServiceData> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothServiceData>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 76: {
      const std::vector<BluetoothLEAdvertisementResponse> *vec =
          static_cast<const std::vector<BluetoothLEAdvertisementResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothLEAdvertisementResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 77: {
      const std::vector<BluetoothLERawAdvertisement> *vec =
          static_cast<const std::vector<BluetoothLERawAdvertisement> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothLERawAdvertisement>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 78: {
      const std::vector<BluetoothLERawAdvertisementsResponse> *vec =
          static_cast<const std::vector<BluetoothLERawAdvertisementsResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothLERawAdvertisementsResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 79: {
      const std::vector<BluetoothDeviceRequest> *vec =
          static_cast<const std::vector<BluetoothDeviceRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothDeviceRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 80: {
      const std::vector<BluetoothDeviceConnectionResponse> *vec =
          static_cast<const std::vector<BluetoothDeviceConnectionResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothDeviceConnectionResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 81: {
      const std::vector<BluetoothGATTGetServicesRequest> *vec =
          static_cast<const std::vector<BluetoothGATTGetServicesRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTGetServicesRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 82: {
      const std::vector<BluetoothGATTDescriptor> *vec =
          static_cast<const std::vector<BluetoothGATTDescriptor> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTDescriptor>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 83: {
      const std::vector<BluetoothGATTCharacteristic> *vec =
          static_cast<const std::vector<BluetoothGATTCharacteristic> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTCharacteristic>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 84: {
      const std::vector<BluetoothGATTService> *vec = static_cast<const std::vector<BluetoothGATTService> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTService>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 85: {
      const std::vector<BluetoothGATTGetServicesResponse> *vec =
          static_cast<const std::vector<BluetoothGATTGetServicesResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTGetServicesResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 86: {
      const std::vector<BluetoothGATTGetServicesDoneResponse> *vec =
          static_cast<const std::vector<BluetoothGATTGetServicesDoneResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTGetServicesDoneResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 87: {
      const std::vector<BluetoothGATTReadRequest> *vec =
          static_cast<const std::vector<BluetoothGATTReadRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTReadRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 88: {
      const std::vector<BluetoothGATTReadResponse> *vec =
          static_cast<const std::vector<BluetoothGATTReadResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTReadResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 89: {
      const std::vector<BluetoothGATTWriteRequest> *vec =
          static_cast<const std::vector<BluetoothGATTWriteRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTWriteRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 90: {
      const std::vector<BluetoothGATTReadDescriptorRequest> *vec =
          static_cast<const std::vector<BluetoothGATTReadDescriptorRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTReadDescriptorRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 91: {
      const std::vector<BluetoothGATTWriteDescriptorRequest> *vec =
          static_cast<const std::vector<BluetoothGATTWriteDescriptorRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTWriteDescriptorRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 92: {
      const std::vector<BluetoothGATTNotifyRequest> *vec =
          static_cast<const std::vector<BluetoothGATTNotifyRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTNotifyRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 93: {
      const std::vector<BluetoothGATTNotifyDataResponse> *vec =
          static_cast<const std::vector<BluetoothGATTNotifyDataResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTNotifyDataResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 94: {
      const std::vector<SubscribeBluetoothConnectionsFreeRequest> *vec =
          static_cast<const std::vector<SubscribeBluetoothConnectionsFreeRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeBluetoothConnectionsFreeRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 95: {
      const std::vector<BluetoothConnectionsFreeResponse> *vec =
          static_cast<const std::vector<BluetoothConnectionsFreeResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothConnectionsFreeResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 96: {
      const std::vector<BluetoothGATTErrorResponse> *vec =
          static_cast<const std::vector<BluetoothGATTErrorResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTErrorResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 97: {
      const std::vector<BluetoothGATTWriteResponse> *vec =
          static_cast<const std::vector<BluetoothGATTWriteResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTWriteResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 98: {
      const std::vector<BluetoothGATTNotifyResponse> *vec =
          static_cast<const std::vector<BluetoothGATTNotifyResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothGATTNotifyResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 99: {
      const std::vector<BluetoothDevicePairingResponse> *vec =
          static_cast<const std::vector<BluetoothDevicePairingResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothDevicePairingResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 100: {
      const std::vector<BluetoothDeviceUnpairingResponse> *vec =
          static_cast<const std::vector<BluetoothDeviceUnpairingResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothDeviceUnpairingResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 101: {
      const std::vector<UnsubscribeBluetoothLEAdvertisementsRequest> *vec =
          static_cast<const std::vector<UnsubscribeBluetoothLEAdvertisementsRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<UnsubscribeBluetoothLEAdvertisementsRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 102: {
      const std::vector<BluetoothDeviceClearCacheResponse> *vec =
          static_cast<const std::vector<BluetoothDeviceClearCacheResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothDeviceClearCacheResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 103: {
      const std::vector<BluetoothScannerStateResponse> *vec =
          static_cast<const std::vector<BluetoothScannerStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothScannerStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 104: {
      const std::vector<BluetoothScannerSetModeRequest> *vec =
          static_cast<const std::vector<BluetoothScannerSetModeRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<BluetoothScannerSetModeRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 105: {
      const std::vector<SubscribeVoiceAssistantRequest> *vec =
          static_cast<const std::vector<SubscribeVoiceAssistantRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<SubscribeVoiceAssistantRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 106: {
      const std::vector<VoiceAssistantAudioSettings> *vec =
          static_cast<const std::vector<VoiceAssistantAudioSettings> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantAudioSettings>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 107: {
      const std::vector<VoiceAssistantRequest> *vec =
          static_cast<const std::vector<VoiceAssistantRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 108: {
      const std::vector<VoiceAssistantResponse> *vec =
          static_cast<const std::vector<VoiceAssistantResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 109: {
      const std::vector<VoiceAssistantEventData> *vec =
          static_cast<const std::vector<VoiceAssistantEventData> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantEventData>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 110: {
      const std::vector<VoiceAssistantEventResponse> *vec =
          static_cast<const std::vector<VoiceAssistantEventResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantEventResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 111: {
      const std::vector<VoiceAssistantAudio> *vec = static_cast<const std::vector<VoiceAssistantAudio> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantAudio>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 112: {
      const std::vector<VoiceAssistantTimerEventResponse> *vec =
          static_cast<const std::vector<VoiceAssistantTimerEventResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantTimerEventResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 113: {
      const std::vector<VoiceAssistantAnnounceRequest> *vec =
          static_cast<const std::vector<VoiceAssistantAnnounceRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantAnnounceRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 114: {
      const std::vector<VoiceAssistantAnnounceFinished> *vec =
          static_cast<const std::vector<VoiceAssistantAnnounceFinished> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantAnnounceFinished>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 115: {
      const std::vector<VoiceAssistantWakeWord> *vec =
          static_cast<const std::vector<VoiceAssistantWakeWord> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantWakeWord>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 116: {
      const std::vector<VoiceAssistantConfigurationRequest> *vec =
          static_cast<const std::vector<VoiceAssistantConfigurationRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantConfigurationRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 117: {
      const std::vector<VoiceAssistantConfigurationResponse> *vec =
          static_cast<const std::vector<VoiceAssistantConfigurationResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantConfigurationResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 118: {
      const std::vector<VoiceAssistantSetConfiguration> *vec =
          static_cast<const std::vector<VoiceAssistantSetConfiguration> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<VoiceAssistantSetConfiguration>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 119: {
      const std::vector<ListEntitiesAlarmControlPanelResponse> *vec =
          static_cast<const std::vector<ListEntitiesAlarmControlPanelResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesAlarmControlPanelResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 120: {
      const std::vector<AlarmControlPanelStateResponse> *vec =
          static_cast<const std::vector<AlarmControlPanelStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<AlarmControlPanelStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 121: {
      const std::vector<AlarmControlPanelCommandRequest> *vec =
          static_cast<const std::vector<AlarmControlPanelCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<AlarmControlPanelCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_TEXT
    case 122: {
      const std::vector<ListEntitiesTextResponse> *vec =
          static_cast<const std::vector<ListEntitiesTextResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesTextResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_TEXT
    case 123: {
      const std::vector<TextStateResponse> *vec = static_cast<const std::vector<TextStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<TextStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_TEXT
    case 124: {
      const std::vector<TextCommandRequest> *vec = static_cast<const std::vector<TextCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<TextCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 125: {
      const std::vector<ListEntitiesDateResponse> *vec =
          static_cast<const std::vector<ListEntitiesDateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesDateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 126: {
      const std::vector<DateStateResponse> *vec = static_cast<const std::vector<DateStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DateStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 127: {
      const std::vector<DateCommandRequest> *vec = static_cast<const std::vector<DateCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DateCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 128: {
      const std::vector<ListEntitiesTimeResponse> *vec =
          static_cast<const std::vector<ListEntitiesTimeResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesTimeResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 129: {
      const std::vector<TimeStateResponse> *vec = static_cast<const std::vector<TimeStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<TimeStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 130: {
      const std::vector<TimeCommandRequest> *vec = static_cast<const std::vector<TimeCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<TimeCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_EVENT
    case 131: {
      const std::vector<ListEntitiesEventResponse> *vec =
          static_cast<const std::vector<ListEntitiesEventResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesEventResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_EVENT
    case 132: {
      const std::vector<EventResponse> *vec = static_cast<const std::vector<EventResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<EventResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VALVE
    case 133: {
      const std::vector<ListEntitiesValveResponse> *vec =
          static_cast<const std::vector<ListEntitiesValveResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesValveResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VALVE
    case 134: {
      const std::vector<ValveStateResponse> *vec = static_cast<const std::vector<ValveStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ValveStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_VALVE
    case 135: {
      const std::vector<ValveCommandRequest> *vec = static_cast<const std::vector<ValveCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ValveCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 136: {
      const std::vector<ListEntitiesDateTimeResponse> *vec =
          static_cast<const std::vector<ListEntitiesDateTimeResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesDateTimeResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 137: {
      const std::vector<DateTimeStateResponse> *vec =
          static_cast<const std::vector<DateTimeStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DateTimeStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 138: {
      const std::vector<DateTimeCommandRequest> *vec =
          static_cast<const std::vector<DateTimeCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<DateTimeCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_UPDATE
    case 139: {
      const std::vector<ListEntitiesUpdateResponse> *vec =
          static_cast<const std::vector<ListEntitiesUpdateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<ListEntitiesUpdateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_UPDATE
    case 140: {
      const std::vector<UpdateStateResponse> *vec = static_cast<const std::vector<UpdateStateResponse> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<UpdateStateResponse>(field_num, msg, true);
      }
      break;
    }
#endif
#ifdef USE_UPDATE
    case 141: {
      const std::vector<UpdateCommandRequest> *vec = static_cast<const std::vector<UpdateCommandRequest> *>(field_ptr);
      for (const auto &msg : *vec) {
        buffer.encode_message<UpdateCommandRequest>(field_num, msg, true);
      }
      break;
    }
#endif
    default:
      break;
  }
}

void decode_repeated_message_field_by_type(void *field_ptr, ProtoLengthDelimited value, uint8_t message_type_id) {
  switch (message_type_id) {
    case 1: {
      std::vector<HelloRequest> *vec = static_cast<std::vector<HelloRequest> *>(field_ptr);
      vec->push_back(value.as_message<HelloRequest>());
      break;
    }
    case 2: {
      std::vector<HelloResponse> *vec = static_cast<std::vector<HelloResponse> *>(field_ptr);
      vec->push_back(value.as_message<HelloResponse>());
      break;
    }
    case 3: {
      std::vector<ConnectRequest> *vec = static_cast<std::vector<ConnectRequest> *>(field_ptr);
      vec->push_back(value.as_message<ConnectRequest>());
      break;
    }
    case 4: {
      std::vector<ConnectResponse> *vec = static_cast<std::vector<ConnectResponse> *>(field_ptr);
      vec->push_back(value.as_message<ConnectResponse>());
      break;
    }
    case 5: {
      std::vector<DisconnectRequest> *vec = static_cast<std::vector<DisconnectRequest> *>(field_ptr);
      vec->push_back(value.as_message<DisconnectRequest>());
      break;
    }
    case 6: {
      std::vector<DisconnectResponse> *vec = static_cast<std::vector<DisconnectResponse> *>(field_ptr);
      vec->push_back(value.as_message<DisconnectResponse>());
      break;
    }
    case 7: {
      std::vector<PingRequest> *vec = static_cast<std::vector<PingRequest> *>(field_ptr);
      vec->push_back(value.as_message<PingRequest>());
      break;
    }
    case 8: {
      std::vector<PingResponse> *vec = static_cast<std::vector<PingResponse> *>(field_ptr);
      vec->push_back(value.as_message<PingResponse>());
      break;
    }
    case 9: {
      std::vector<DeviceInfoRequest> *vec = static_cast<std::vector<DeviceInfoRequest> *>(field_ptr);
      vec->push_back(value.as_message<DeviceInfoRequest>());
      break;
    }
    case 10: {
      std::vector<AreaInfo> *vec = static_cast<std::vector<AreaInfo> *>(field_ptr);
      vec->push_back(value.as_message<AreaInfo>());
      break;
    }
    case 11: {
      std::vector<DeviceInfo> *vec = static_cast<std::vector<DeviceInfo> *>(field_ptr);
      vec->push_back(value.as_message<DeviceInfo>());
      break;
    }
    case 12: {
      std::vector<DeviceInfoResponse> *vec = static_cast<std::vector<DeviceInfoResponse> *>(field_ptr);
      vec->push_back(value.as_message<DeviceInfoResponse>());
      break;
    }
    case 13: {
      std::vector<ListEntitiesRequest> *vec = static_cast<std::vector<ListEntitiesRequest> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesRequest>());
      break;
    }
    case 14: {
      std::vector<ListEntitiesDoneResponse> *vec = static_cast<std::vector<ListEntitiesDoneResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesDoneResponse>());
      break;
    }
    case 15: {
      std::vector<SubscribeStatesRequest> *vec = static_cast<std::vector<SubscribeStatesRequest> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeStatesRequest>());
      break;
    }
#ifdef USE_BINARY_SENSOR
    case 16: {
      std::vector<ListEntitiesBinarySensorResponse> *vec =
          static_cast<std::vector<ListEntitiesBinarySensorResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesBinarySensorResponse>());
      break;
    }
#endif
#ifdef USE_BINARY_SENSOR
    case 17: {
      std::vector<BinarySensorStateResponse> *vec = static_cast<std::vector<BinarySensorStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<BinarySensorStateResponse>());
      break;
    }
#endif
#ifdef USE_COVER
    case 18: {
      std::vector<ListEntitiesCoverResponse> *vec = static_cast<std::vector<ListEntitiesCoverResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesCoverResponse>());
      break;
    }
#endif
#ifdef USE_COVER
    case 19: {
      std::vector<CoverStateResponse> *vec = static_cast<std::vector<CoverStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<CoverStateResponse>());
      break;
    }
#endif
#ifdef USE_COVER
    case 20: {
      std::vector<CoverCommandRequest> *vec = static_cast<std::vector<CoverCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<CoverCommandRequest>());
      break;
    }
#endif
#ifdef USE_FAN
    case 21: {
      std::vector<ListEntitiesFanResponse> *vec = static_cast<std::vector<ListEntitiesFanResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesFanResponse>());
      break;
    }
#endif
#ifdef USE_FAN
    case 22: {
      std::vector<FanStateResponse> *vec = static_cast<std::vector<FanStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<FanStateResponse>());
      break;
    }
#endif
#ifdef USE_FAN
    case 23: {
      std::vector<FanCommandRequest> *vec = static_cast<std::vector<FanCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<FanCommandRequest>());
      break;
    }
#endif
#ifdef USE_LIGHT
    case 24: {
      std::vector<ListEntitiesLightResponse> *vec = static_cast<std::vector<ListEntitiesLightResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesLightResponse>());
      break;
    }
#endif
#ifdef USE_LIGHT
    case 25: {
      std::vector<LightStateResponse> *vec = static_cast<std::vector<LightStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<LightStateResponse>());
      break;
    }
#endif
#ifdef USE_LIGHT
    case 26: {
      std::vector<LightCommandRequest> *vec = static_cast<std::vector<LightCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<LightCommandRequest>());
      break;
    }
#endif
#ifdef USE_SENSOR
    case 27: {
      std::vector<ListEntitiesSensorResponse> *vec = static_cast<std::vector<ListEntitiesSensorResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesSensorResponse>());
      break;
    }
#endif
#ifdef USE_SENSOR
    case 28: {
      std::vector<SensorStateResponse> *vec = static_cast<std::vector<SensorStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<SensorStateResponse>());
      break;
    }
#endif
#ifdef USE_SWITCH
    case 29: {
      std::vector<ListEntitiesSwitchResponse> *vec = static_cast<std::vector<ListEntitiesSwitchResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesSwitchResponse>());
      break;
    }
#endif
#ifdef USE_SWITCH
    case 30: {
      std::vector<SwitchStateResponse> *vec = static_cast<std::vector<SwitchStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<SwitchStateResponse>());
      break;
    }
#endif
#ifdef USE_SWITCH
    case 31: {
      std::vector<SwitchCommandRequest> *vec = static_cast<std::vector<SwitchCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<SwitchCommandRequest>());
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 32: {
      std::vector<ListEntitiesTextSensorResponse> *vec =
          static_cast<std::vector<ListEntitiesTextSensorResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesTextSensorResponse>());
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 33: {
      std::vector<TextSensorStateResponse> *vec = static_cast<std::vector<TextSensorStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<TextSensorStateResponse>());
      break;
    }
#endif
    case 34: {
      std::vector<SubscribeLogsRequest> *vec = static_cast<std::vector<SubscribeLogsRequest> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeLogsRequest>());
      break;
    }
    case 35: {
      std::vector<SubscribeLogsResponse> *vec = static_cast<std::vector<SubscribeLogsResponse> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeLogsResponse>());
      break;
    }
#ifdef USE_API_NOISE
    case 36: {
      std::vector<NoiseEncryptionSetKeyRequest> *vec =
          static_cast<std::vector<NoiseEncryptionSetKeyRequest> *>(field_ptr);
      vec->push_back(value.as_message<NoiseEncryptionSetKeyRequest>());
      break;
    }
#endif
#ifdef USE_API_NOISE
    case 37: {
      std::vector<NoiseEncryptionSetKeyResponse> *vec =
          static_cast<std::vector<NoiseEncryptionSetKeyResponse> *>(field_ptr);
      vec->push_back(value.as_message<NoiseEncryptionSetKeyResponse>());
      break;
    }
#endif
    case 38: {
      std::vector<SubscribeHomeassistantServicesRequest> *vec =
          static_cast<std::vector<SubscribeHomeassistantServicesRequest> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeHomeassistantServicesRequest>());
      break;
    }
    case 39: {
      std::vector<HomeassistantServiceMap> *vec = static_cast<std::vector<HomeassistantServiceMap> *>(field_ptr);
      vec->push_back(value.as_message<HomeassistantServiceMap>());
      break;
    }
    case 40: {
      std::vector<HomeassistantServiceResponse> *vec =
          static_cast<std::vector<HomeassistantServiceResponse> *>(field_ptr);
      vec->push_back(value.as_message<HomeassistantServiceResponse>());
      break;
    }
    case 41: {
      std::vector<SubscribeHomeAssistantStatesRequest> *vec =
          static_cast<std::vector<SubscribeHomeAssistantStatesRequest> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeHomeAssistantStatesRequest>());
      break;
    }
    case 42: {
      std::vector<SubscribeHomeAssistantStateResponse> *vec =
          static_cast<std::vector<SubscribeHomeAssistantStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeHomeAssistantStateResponse>());
      break;
    }
    case 43: {
      std::vector<HomeAssistantStateResponse> *vec = static_cast<std::vector<HomeAssistantStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<HomeAssistantStateResponse>());
      break;
    }
    case 44: {
      std::vector<GetTimeRequest> *vec = static_cast<std::vector<GetTimeRequest> *>(field_ptr);
      vec->push_back(value.as_message<GetTimeRequest>());
      break;
    }
    case 45: {
      std::vector<GetTimeResponse> *vec = static_cast<std::vector<GetTimeResponse> *>(field_ptr);
      vec->push_back(value.as_message<GetTimeResponse>());
      break;
    }
    case 46: {
      std::vector<ListEntitiesServicesArgument> *vec =
          static_cast<std::vector<ListEntitiesServicesArgument> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesServicesArgument>());
      break;
    }
    case 47: {
      std::vector<ListEntitiesServicesResponse> *vec =
          static_cast<std::vector<ListEntitiesServicesResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesServicesResponse>());
      break;
    }
    case 48: {
      std::vector<ExecuteServiceArgument> *vec = static_cast<std::vector<ExecuteServiceArgument> *>(field_ptr);
      vec->push_back(value.as_message<ExecuteServiceArgument>());
      break;
    }
    case 49: {
      std::vector<ExecuteServiceRequest> *vec = static_cast<std::vector<ExecuteServiceRequest> *>(field_ptr);
      vec->push_back(value.as_message<ExecuteServiceRequest>());
      break;
    }
#ifdef USE_CAMERA
    case 50: {
      std::vector<ListEntitiesCameraResponse> *vec = static_cast<std::vector<ListEntitiesCameraResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesCameraResponse>());
      break;
    }
#endif
#ifdef USE_CAMERA
    case 51: {
      std::vector<CameraImageResponse> *vec = static_cast<std::vector<CameraImageResponse> *>(field_ptr);
      vec->push_back(value.as_message<CameraImageResponse>());
      break;
    }
#endif
#ifdef USE_CAMERA
    case 52: {
      std::vector<CameraImageRequest> *vec = static_cast<std::vector<CameraImageRequest> *>(field_ptr);
      vec->push_back(value.as_message<CameraImageRequest>());
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 53: {
      std::vector<ListEntitiesClimateResponse> *vec =
          static_cast<std::vector<ListEntitiesClimateResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesClimateResponse>());
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 54: {
      std::vector<ClimateStateResponse> *vec = static_cast<std::vector<ClimateStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<ClimateStateResponse>());
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 55: {
      std::vector<ClimateCommandRequest> *vec = static_cast<std::vector<ClimateCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<ClimateCommandRequest>());
      break;
    }
#endif
#ifdef USE_NUMBER
    case 56: {
      std::vector<ListEntitiesNumberResponse> *vec = static_cast<std::vector<ListEntitiesNumberResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesNumberResponse>());
      break;
    }
#endif
#ifdef USE_NUMBER
    case 57: {
      std::vector<NumberStateResponse> *vec = static_cast<std::vector<NumberStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<NumberStateResponse>());
      break;
    }
#endif
#ifdef USE_NUMBER
    case 58: {
      std::vector<NumberCommandRequest> *vec = static_cast<std::vector<NumberCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<NumberCommandRequest>());
      break;
    }
#endif
#ifdef USE_SELECT
    case 59: {
      std::vector<ListEntitiesSelectResponse> *vec = static_cast<std::vector<ListEntitiesSelectResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesSelectResponse>());
      break;
    }
#endif
#ifdef USE_SELECT
    case 60: {
      std::vector<SelectStateResponse> *vec = static_cast<std::vector<SelectStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<SelectStateResponse>());
      break;
    }
#endif
#ifdef USE_SELECT
    case 61: {
      std::vector<SelectCommandRequest> *vec = static_cast<std::vector<SelectCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<SelectCommandRequest>());
      break;
    }
#endif
#ifdef USE_SIREN
    case 62: {
      std::vector<ListEntitiesSirenResponse> *vec = static_cast<std::vector<ListEntitiesSirenResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesSirenResponse>());
      break;
    }
#endif
#ifdef USE_SIREN
    case 63: {
      std::vector<SirenStateResponse> *vec = static_cast<std::vector<SirenStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<SirenStateResponse>());
      break;
    }
#endif
#ifdef USE_SIREN
    case 64: {
      std::vector<SirenCommandRequest> *vec = static_cast<std::vector<SirenCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<SirenCommandRequest>());
      break;
    }
#endif
#ifdef USE_LOCK
    case 65: {
      std::vector<ListEntitiesLockResponse> *vec = static_cast<std::vector<ListEntitiesLockResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesLockResponse>());
      break;
    }
#endif
#ifdef USE_LOCK
    case 66: {
      std::vector<LockStateResponse> *vec = static_cast<std::vector<LockStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<LockStateResponse>());
      break;
    }
#endif
#ifdef USE_LOCK
    case 67: {
      std::vector<LockCommandRequest> *vec = static_cast<std::vector<LockCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<LockCommandRequest>());
      break;
    }
#endif
#ifdef USE_BUTTON
    case 68: {
      std::vector<ListEntitiesButtonResponse> *vec = static_cast<std::vector<ListEntitiesButtonResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesButtonResponse>());
      break;
    }
#endif
#ifdef USE_BUTTON
    case 69: {
      std::vector<ButtonCommandRequest> *vec = static_cast<std::vector<ButtonCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<ButtonCommandRequest>());
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 70: {
      std::vector<MediaPlayerSupportedFormat> *vec = static_cast<std::vector<MediaPlayerSupportedFormat> *>(field_ptr);
      vec->push_back(value.as_message<MediaPlayerSupportedFormat>());
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 71: {
      std::vector<ListEntitiesMediaPlayerResponse> *vec =
          static_cast<std::vector<ListEntitiesMediaPlayerResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesMediaPlayerResponse>());
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 72: {
      std::vector<MediaPlayerStateResponse> *vec = static_cast<std::vector<MediaPlayerStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<MediaPlayerStateResponse>());
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 73: {
      std::vector<MediaPlayerCommandRequest> *vec = static_cast<std::vector<MediaPlayerCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<MediaPlayerCommandRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 74: {
      std::vector<SubscribeBluetoothLEAdvertisementsRequest> *vec =
          static_cast<std::vector<SubscribeBluetoothLEAdvertisementsRequest> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeBluetoothLEAdvertisementsRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 75: {
      std::vector<BluetoothServiceData> *vec = static_cast<std::vector<BluetoothServiceData> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothServiceData>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 76: {
      std::vector<BluetoothLEAdvertisementResponse> *vec =
          static_cast<std::vector<BluetoothLEAdvertisementResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothLEAdvertisementResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 77: {
      std::vector<BluetoothLERawAdvertisement> *vec =
          static_cast<std::vector<BluetoothLERawAdvertisement> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothLERawAdvertisement>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 78: {
      std::vector<BluetoothLERawAdvertisementsResponse> *vec =
          static_cast<std::vector<BluetoothLERawAdvertisementsResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothLERawAdvertisementsResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 79: {
      std::vector<BluetoothDeviceRequest> *vec = static_cast<std::vector<BluetoothDeviceRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothDeviceRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 80: {
      std::vector<BluetoothDeviceConnectionResponse> *vec =
          static_cast<std::vector<BluetoothDeviceConnectionResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothDeviceConnectionResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 81: {
      std::vector<BluetoothGATTGetServicesRequest> *vec =
          static_cast<std::vector<BluetoothGATTGetServicesRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTGetServicesRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 82: {
      std::vector<BluetoothGATTDescriptor> *vec = static_cast<std::vector<BluetoothGATTDescriptor> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTDescriptor>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 83: {
      std::vector<BluetoothGATTCharacteristic> *vec =
          static_cast<std::vector<BluetoothGATTCharacteristic> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTCharacteristic>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 84: {
      std::vector<BluetoothGATTService> *vec = static_cast<std::vector<BluetoothGATTService> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTService>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 85: {
      std::vector<BluetoothGATTGetServicesResponse> *vec =
          static_cast<std::vector<BluetoothGATTGetServicesResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTGetServicesResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 86: {
      std::vector<BluetoothGATTGetServicesDoneResponse> *vec =
          static_cast<std::vector<BluetoothGATTGetServicesDoneResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTGetServicesDoneResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 87: {
      std::vector<BluetoothGATTReadRequest> *vec = static_cast<std::vector<BluetoothGATTReadRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTReadRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 88: {
      std::vector<BluetoothGATTReadResponse> *vec = static_cast<std::vector<BluetoothGATTReadResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTReadResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 89: {
      std::vector<BluetoothGATTWriteRequest> *vec = static_cast<std::vector<BluetoothGATTWriteRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTWriteRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 90: {
      std::vector<BluetoothGATTReadDescriptorRequest> *vec =
          static_cast<std::vector<BluetoothGATTReadDescriptorRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTReadDescriptorRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 91: {
      std::vector<BluetoothGATTWriteDescriptorRequest> *vec =
          static_cast<std::vector<BluetoothGATTWriteDescriptorRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTWriteDescriptorRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 92: {
      std::vector<BluetoothGATTNotifyRequest> *vec = static_cast<std::vector<BluetoothGATTNotifyRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTNotifyRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 93: {
      std::vector<BluetoothGATTNotifyDataResponse> *vec =
          static_cast<std::vector<BluetoothGATTNotifyDataResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTNotifyDataResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 94: {
      std::vector<SubscribeBluetoothConnectionsFreeRequest> *vec =
          static_cast<std::vector<SubscribeBluetoothConnectionsFreeRequest> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeBluetoothConnectionsFreeRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 95: {
      std::vector<BluetoothConnectionsFreeResponse> *vec =
          static_cast<std::vector<BluetoothConnectionsFreeResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothConnectionsFreeResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 96: {
      std::vector<BluetoothGATTErrorResponse> *vec = static_cast<std::vector<BluetoothGATTErrorResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTErrorResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 97: {
      std::vector<BluetoothGATTWriteResponse> *vec = static_cast<std::vector<BluetoothGATTWriteResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTWriteResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 98: {
      std::vector<BluetoothGATTNotifyResponse> *vec =
          static_cast<std::vector<BluetoothGATTNotifyResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothGATTNotifyResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 99: {
      std::vector<BluetoothDevicePairingResponse> *vec =
          static_cast<std::vector<BluetoothDevicePairingResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothDevicePairingResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 100: {
      std::vector<BluetoothDeviceUnpairingResponse> *vec =
          static_cast<std::vector<BluetoothDeviceUnpairingResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothDeviceUnpairingResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 101: {
      std::vector<UnsubscribeBluetoothLEAdvertisementsRequest> *vec =
          static_cast<std::vector<UnsubscribeBluetoothLEAdvertisementsRequest> *>(field_ptr);
      vec->push_back(value.as_message<UnsubscribeBluetoothLEAdvertisementsRequest>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 102: {
      std::vector<BluetoothDeviceClearCacheResponse> *vec =
          static_cast<std::vector<BluetoothDeviceClearCacheResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothDeviceClearCacheResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 103: {
      std::vector<BluetoothScannerStateResponse> *vec =
          static_cast<std::vector<BluetoothScannerStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothScannerStateResponse>());
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 104: {
      std::vector<BluetoothScannerSetModeRequest> *vec =
          static_cast<std::vector<BluetoothScannerSetModeRequest> *>(field_ptr);
      vec->push_back(value.as_message<BluetoothScannerSetModeRequest>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 105: {
      std::vector<SubscribeVoiceAssistantRequest> *vec =
          static_cast<std::vector<SubscribeVoiceAssistantRequest> *>(field_ptr);
      vec->push_back(value.as_message<SubscribeVoiceAssistantRequest>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 106: {
      std::vector<VoiceAssistantAudioSettings> *vec =
          static_cast<std::vector<VoiceAssistantAudioSettings> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantAudioSettings>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 107: {
      std::vector<VoiceAssistantRequest> *vec = static_cast<std::vector<VoiceAssistantRequest> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantRequest>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 108: {
      std::vector<VoiceAssistantResponse> *vec = static_cast<std::vector<VoiceAssistantResponse> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantResponse>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 109: {
      std::vector<VoiceAssistantEventData> *vec = static_cast<std::vector<VoiceAssistantEventData> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantEventData>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 110: {
      std::vector<VoiceAssistantEventResponse> *vec =
          static_cast<std::vector<VoiceAssistantEventResponse> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantEventResponse>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 111: {
      std::vector<VoiceAssistantAudio> *vec = static_cast<std::vector<VoiceAssistantAudio> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantAudio>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 112: {
      std::vector<VoiceAssistantTimerEventResponse> *vec =
          static_cast<std::vector<VoiceAssistantTimerEventResponse> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantTimerEventResponse>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 113: {
      std::vector<VoiceAssistantAnnounceRequest> *vec =
          static_cast<std::vector<VoiceAssistantAnnounceRequest> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantAnnounceRequest>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 114: {
      std::vector<VoiceAssistantAnnounceFinished> *vec =
          static_cast<std::vector<VoiceAssistantAnnounceFinished> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantAnnounceFinished>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 115: {
      std::vector<VoiceAssistantWakeWord> *vec = static_cast<std::vector<VoiceAssistantWakeWord> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantWakeWord>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 116: {
      std::vector<VoiceAssistantConfigurationRequest> *vec =
          static_cast<std::vector<VoiceAssistantConfigurationRequest> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantConfigurationRequest>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 117: {
      std::vector<VoiceAssistantConfigurationResponse> *vec =
          static_cast<std::vector<VoiceAssistantConfigurationResponse> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantConfigurationResponse>());
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 118: {
      std::vector<VoiceAssistantSetConfiguration> *vec =
          static_cast<std::vector<VoiceAssistantSetConfiguration> *>(field_ptr);
      vec->push_back(value.as_message<VoiceAssistantSetConfiguration>());
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 119: {
      std::vector<ListEntitiesAlarmControlPanelResponse> *vec =
          static_cast<std::vector<ListEntitiesAlarmControlPanelResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesAlarmControlPanelResponse>());
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 120: {
      std::vector<AlarmControlPanelStateResponse> *vec =
          static_cast<std::vector<AlarmControlPanelStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<AlarmControlPanelStateResponse>());
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 121: {
      std::vector<AlarmControlPanelCommandRequest> *vec =
          static_cast<std::vector<AlarmControlPanelCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<AlarmControlPanelCommandRequest>());
      break;
    }
#endif
#ifdef USE_TEXT
    case 122: {
      std::vector<ListEntitiesTextResponse> *vec = static_cast<std::vector<ListEntitiesTextResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesTextResponse>());
      break;
    }
#endif
#ifdef USE_TEXT
    case 123: {
      std::vector<TextStateResponse> *vec = static_cast<std::vector<TextStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<TextStateResponse>());
      break;
    }
#endif
#ifdef USE_TEXT
    case 124: {
      std::vector<TextCommandRequest> *vec = static_cast<std::vector<TextCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<TextCommandRequest>());
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 125: {
      std::vector<ListEntitiesDateResponse> *vec = static_cast<std::vector<ListEntitiesDateResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesDateResponse>());
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 126: {
      std::vector<DateStateResponse> *vec = static_cast<std::vector<DateStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<DateStateResponse>());
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 127: {
      std::vector<DateCommandRequest> *vec = static_cast<std::vector<DateCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<DateCommandRequest>());
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 128: {
      std::vector<ListEntitiesTimeResponse> *vec = static_cast<std::vector<ListEntitiesTimeResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesTimeResponse>());
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 129: {
      std::vector<TimeStateResponse> *vec = static_cast<std::vector<TimeStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<TimeStateResponse>());
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 130: {
      std::vector<TimeCommandRequest> *vec = static_cast<std::vector<TimeCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<TimeCommandRequest>());
      break;
    }
#endif
#ifdef USE_EVENT
    case 131: {
      std::vector<ListEntitiesEventResponse> *vec = static_cast<std::vector<ListEntitiesEventResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesEventResponse>());
      break;
    }
#endif
#ifdef USE_EVENT
    case 132: {
      std::vector<EventResponse> *vec = static_cast<std::vector<EventResponse> *>(field_ptr);
      vec->push_back(value.as_message<EventResponse>());
      break;
    }
#endif
#ifdef USE_VALVE
    case 133: {
      std::vector<ListEntitiesValveResponse> *vec = static_cast<std::vector<ListEntitiesValveResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesValveResponse>());
      break;
    }
#endif
#ifdef USE_VALVE
    case 134: {
      std::vector<ValveStateResponse> *vec = static_cast<std::vector<ValveStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<ValveStateResponse>());
      break;
    }
#endif
#ifdef USE_VALVE
    case 135: {
      std::vector<ValveCommandRequest> *vec = static_cast<std::vector<ValveCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<ValveCommandRequest>());
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 136: {
      std::vector<ListEntitiesDateTimeResponse> *vec =
          static_cast<std::vector<ListEntitiesDateTimeResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesDateTimeResponse>());
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 137: {
      std::vector<DateTimeStateResponse> *vec = static_cast<std::vector<DateTimeStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<DateTimeStateResponse>());
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 138: {
      std::vector<DateTimeCommandRequest> *vec = static_cast<std::vector<DateTimeCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<DateTimeCommandRequest>());
      break;
    }
#endif
#ifdef USE_UPDATE
    case 139: {
      std::vector<ListEntitiesUpdateResponse> *vec = static_cast<std::vector<ListEntitiesUpdateResponse> *>(field_ptr);
      vec->push_back(value.as_message<ListEntitiesUpdateResponse>());
      break;
    }
#endif
#ifdef USE_UPDATE
    case 140: {
      std::vector<UpdateStateResponse> *vec = static_cast<std::vector<UpdateStateResponse> *>(field_ptr);
      vec->push_back(value.as_message<UpdateStateResponse>());
      break;
    }
#endif
#ifdef USE_UPDATE
    case 141: {
      std::vector<UpdateCommandRequest> *vec = static_cast<std::vector<UpdateCommandRequest> *>(field_ptr);
      vec->push_back(value.as_message<UpdateCommandRequest>());
      break;
    }
#endif
    default:
      break;
  }
}

void size_repeated_message_field_by_type(uint32_t &total_size, uint8_t precalced_field_id_size, const void *field_ptr,
                                         uint8_t message_type_id) {
  switch (message_type_id) {
    case 1: {
      const std::vector<HelloRequest> *vec = static_cast<const std::vector<HelloRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<HelloRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 2: {
      const std::vector<HelloResponse> *vec = static_cast<const std::vector<HelloResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<HelloResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 3: {
      const std::vector<ConnectRequest> *vec = static_cast<const std::vector<ConnectRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<ConnectRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 4: {
      const std::vector<ConnectResponse> *vec = static_cast<const std::vector<ConnectResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ConnectResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 5: {
      const std::vector<DisconnectRequest> *vec = static_cast<const std::vector<DisconnectRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<DisconnectRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 6: {
      const std::vector<DisconnectResponse> *vec = static_cast<const std::vector<DisconnectResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<DisconnectResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 7: {
      const std::vector<PingRequest> *vec = static_cast<const std::vector<PingRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<PingRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 8: {
      const std::vector<PingResponse> *vec = static_cast<const std::vector<PingResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<PingResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 9: {
      const std::vector<DeviceInfoRequest> *vec = static_cast<const std::vector<DeviceInfoRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<DeviceInfoRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 10: {
      const std::vector<AreaInfo> *vec = static_cast<const std::vector<AreaInfo> *>(field_ptr);
      ProtoSize::add_repeated_message<AreaInfo>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 11: {
      const std::vector<DeviceInfo> *vec = static_cast<const std::vector<DeviceInfo> *>(field_ptr);
      ProtoSize::add_repeated_message<DeviceInfo>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 12: {
      const std::vector<DeviceInfoResponse> *vec = static_cast<const std::vector<DeviceInfoResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<DeviceInfoResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 13: {
      const std::vector<ListEntitiesRequest> *vec = static_cast<const std::vector<ListEntitiesRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 14: {
      const std::vector<ListEntitiesDoneResponse> *vec =
          static_cast<const std::vector<ListEntitiesDoneResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesDoneResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 15: {
      const std::vector<SubscribeStatesRequest> *vec =
          static_cast<const std::vector<SubscribeStatesRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeStatesRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#ifdef USE_BINARY_SENSOR
    case 16: {
      const std::vector<ListEntitiesBinarySensorResponse> *vec =
          static_cast<const std::vector<ListEntitiesBinarySensorResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesBinarySensorResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BINARY_SENSOR
    case 17: {
      const std::vector<BinarySensorStateResponse> *vec =
          static_cast<const std::vector<BinarySensorStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BinarySensorStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_COVER
    case 18: {
      const std::vector<ListEntitiesCoverResponse> *vec =
          static_cast<const std::vector<ListEntitiesCoverResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesCoverResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_COVER
    case 19: {
      const std::vector<CoverStateResponse> *vec = static_cast<const std::vector<CoverStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<CoverStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_COVER
    case 20: {
      const std::vector<CoverCommandRequest> *vec = static_cast<const std::vector<CoverCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<CoverCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_FAN
    case 21: {
      const std::vector<ListEntitiesFanResponse> *vec =
          static_cast<const std::vector<ListEntitiesFanResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesFanResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_FAN
    case 22: {
      const std::vector<FanStateResponse> *vec = static_cast<const std::vector<FanStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<FanStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_FAN
    case 23: {
      const std::vector<FanCommandRequest> *vec = static_cast<const std::vector<FanCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<FanCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 24: {
      const std::vector<ListEntitiesLightResponse> *vec =
          static_cast<const std::vector<ListEntitiesLightResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesLightResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 25: {
      const std::vector<LightStateResponse> *vec = static_cast<const std::vector<LightStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<LightStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_LIGHT
    case 26: {
      const std::vector<LightCommandRequest> *vec = static_cast<const std::vector<LightCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<LightCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SENSOR
    case 27: {
      const std::vector<ListEntitiesSensorResponse> *vec =
          static_cast<const std::vector<ListEntitiesSensorResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesSensorResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SENSOR
    case 28: {
      const std::vector<SensorStateResponse> *vec = static_cast<const std::vector<SensorStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<SensorStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 29: {
      const std::vector<ListEntitiesSwitchResponse> *vec =
          static_cast<const std::vector<ListEntitiesSwitchResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesSwitchResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 30: {
      const std::vector<SwitchStateResponse> *vec = static_cast<const std::vector<SwitchStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<SwitchStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SWITCH
    case 31: {
      const std::vector<SwitchCommandRequest> *vec = static_cast<const std::vector<SwitchCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SwitchCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 32: {
      const std::vector<ListEntitiesTextSensorResponse> *vec =
          static_cast<const std::vector<ListEntitiesTextSensorResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesTextSensorResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_TEXT_SENSOR
    case 33: {
      const std::vector<TextSensorStateResponse> *vec =
          static_cast<const std::vector<TextSensorStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<TextSensorStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
    case 34: {
      const std::vector<SubscribeLogsRequest> *vec = static_cast<const std::vector<SubscribeLogsRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeLogsRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 35: {
      const std::vector<SubscribeLogsResponse> *vec =
          static_cast<const std::vector<SubscribeLogsResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeLogsResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#ifdef USE_API_NOISE
    case 36: {
      const std::vector<NoiseEncryptionSetKeyRequest> *vec =
          static_cast<const std::vector<NoiseEncryptionSetKeyRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<NoiseEncryptionSetKeyRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_API_NOISE
    case 37: {
      const std::vector<NoiseEncryptionSetKeyResponse> *vec =
          static_cast<const std::vector<NoiseEncryptionSetKeyResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<NoiseEncryptionSetKeyResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
    case 38: {
      const std::vector<SubscribeHomeassistantServicesRequest> *vec =
          static_cast<const std::vector<SubscribeHomeassistantServicesRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeHomeassistantServicesRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 39: {
      const std::vector<HomeassistantServiceMap> *vec =
          static_cast<const std::vector<HomeassistantServiceMap> *>(field_ptr);
      ProtoSize::add_repeated_message<HomeassistantServiceMap>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 40: {
      const std::vector<HomeassistantServiceResponse> *vec =
          static_cast<const std::vector<HomeassistantServiceResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<HomeassistantServiceResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 41: {
      const std::vector<SubscribeHomeAssistantStatesRequest> *vec =
          static_cast<const std::vector<SubscribeHomeAssistantStatesRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeHomeAssistantStatesRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 42: {
      const std::vector<SubscribeHomeAssistantStateResponse> *vec =
          static_cast<const std::vector<SubscribeHomeAssistantStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeHomeAssistantStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 43: {
      const std::vector<HomeAssistantStateResponse> *vec =
          static_cast<const std::vector<HomeAssistantStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<HomeAssistantStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 44: {
      const std::vector<GetTimeRequest> *vec = static_cast<const std::vector<GetTimeRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<GetTimeRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 45: {
      const std::vector<GetTimeResponse> *vec = static_cast<const std::vector<GetTimeResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<GetTimeResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 46: {
      const std::vector<ListEntitiesServicesArgument> *vec =
          static_cast<const std::vector<ListEntitiesServicesArgument> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesServicesArgument>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 47: {
      const std::vector<ListEntitiesServicesResponse> *vec =
          static_cast<const std::vector<ListEntitiesServicesResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesServicesResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 48: {
      const std::vector<ExecuteServiceArgument> *vec =
          static_cast<const std::vector<ExecuteServiceArgument> *>(field_ptr);
      ProtoSize::add_repeated_message<ExecuteServiceArgument>(total_size, precalced_field_id_size, *vec);
      break;
    }
    case 49: {
      const std::vector<ExecuteServiceRequest> *vec =
          static_cast<const std::vector<ExecuteServiceRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<ExecuteServiceRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#ifdef USE_CAMERA
    case 50: {
      const std::vector<ListEntitiesCameraResponse> *vec =
          static_cast<const std::vector<ListEntitiesCameraResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesCameraResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_CAMERA
    case 51: {
      const std::vector<CameraImageResponse> *vec = static_cast<const std::vector<CameraImageResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<CameraImageResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_CAMERA
    case 52: {
      const std::vector<CameraImageRequest> *vec = static_cast<const std::vector<CameraImageRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<CameraImageRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 53: {
      const std::vector<ListEntitiesClimateResponse> *vec =
          static_cast<const std::vector<ListEntitiesClimateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesClimateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 54: {
      const std::vector<ClimateStateResponse> *vec = static_cast<const std::vector<ClimateStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ClimateStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_CLIMATE
    case 55: {
      const std::vector<ClimateCommandRequest> *vec =
          static_cast<const std::vector<ClimateCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<ClimateCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 56: {
      const std::vector<ListEntitiesNumberResponse> *vec =
          static_cast<const std::vector<ListEntitiesNumberResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesNumberResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 57: {
      const std::vector<NumberStateResponse> *vec = static_cast<const std::vector<NumberStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<NumberStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_NUMBER
    case 58: {
      const std::vector<NumberCommandRequest> *vec = static_cast<const std::vector<NumberCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<NumberCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SELECT
    case 59: {
      const std::vector<ListEntitiesSelectResponse> *vec =
          static_cast<const std::vector<ListEntitiesSelectResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesSelectResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SELECT
    case 60: {
      const std::vector<SelectStateResponse> *vec = static_cast<const std::vector<SelectStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<SelectStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SELECT
    case 61: {
      const std::vector<SelectCommandRequest> *vec = static_cast<const std::vector<SelectCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SelectCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SIREN
    case 62: {
      const std::vector<ListEntitiesSirenResponse> *vec =
          static_cast<const std::vector<ListEntitiesSirenResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesSirenResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SIREN
    case 63: {
      const std::vector<SirenStateResponse> *vec = static_cast<const std::vector<SirenStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<SirenStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_SIREN
    case 64: {
      const std::vector<SirenCommandRequest> *vec = static_cast<const std::vector<SirenCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SirenCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_LOCK
    case 65: {
      const std::vector<ListEntitiesLockResponse> *vec =
          static_cast<const std::vector<ListEntitiesLockResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesLockResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_LOCK
    case 66: {
      const std::vector<LockStateResponse> *vec = static_cast<const std::vector<LockStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<LockStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_LOCK
    case 67: {
      const std::vector<LockCommandRequest> *vec = static_cast<const std::vector<LockCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<LockCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BUTTON
    case 68: {
      const std::vector<ListEntitiesButtonResponse> *vec =
          static_cast<const std::vector<ListEntitiesButtonResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesButtonResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BUTTON
    case 69: {
      const std::vector<ButtonCommandRequest> *vec = static_cast<const std::vector<ButtonCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<ButtonCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 70: {
      const std::vector<MediaPlayerSupportedFormat> *vec =
          static_cast<const std::vector<MediaPlayerSupportedFormat> *>(field_ptr);
      ProtoSize::add_repeated_message<MediaPlayerSupportedFormat>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 71: {
      const std::vector<ListEntitiesMediaPlayerResponse> *vec =
          static_cast<const std::vector<ListEntitiesMediaPlayerResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesMediaPlayerResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 72: {
      const std::vector<MediaPlayerStateResponse> *vec =
          static_cast<const std::vector<MediaPlayerStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<MediaPlayerStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_MEDIA_PLAYER
    case 73: {
      const std::vector<MediaPlayerCommandRequest> *vec =
          static_cast<const std::vector<MediaPlayerCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<MediaPlayerCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 74: {
      const std::vector<SubscribeBluetoothLEAdvertisementsRequest> *vec =
          static_cast<const std::vector<SubscribeBluetoothLEAdvertisementsRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeBluetoothLEAdvertisementsRequest>(total_size, precalced_field_id_size,
                                                                                 *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 75: {
      const std::vector<BluetoothServiceData> *vec = static_cast<const std::vector<BluetoothServiceData> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothServiceData>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 76: {
      const std::vector<BluetoothLEAdvertisementResponse> *vec =
          static_cast<const std::vector<BluetoothLEAdvertisementResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothLEAdvertisementResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 77: {
      const std::vector<BluetoothLERawAdvertisement> *vec =
          static_cast<const std::vector<BluetoothLERawAdvertisement> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothLERawAdvertisement>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 78: {
      const std::vector<BluetoothLERawAdvertisementsResponse> *vec =
          static_cast<const std::vector<BluetoothLERawAdvertisementsResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothLERawAdvertisementsResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 79: {
      const std::vector<BluetoothDeviceRequest> *vec =
          static_cast<const std::vector<BluetoothDeviceRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothDeviceRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 80: {
      const std::vector<BluetoothDeviceConnectionResponse> *vec =
          static_cast<const std::vector<BluetoothDeviceConnectionResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothDeviceConnectionResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 81: {
      const std::vector<BluetoothGATTGetServicesRequest> *vec =
          static_cast<const std::vector<BluetoothGATTGetServicesRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTGetServicesRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 82: {
      const std::vector<BluetoothGATTDescriptor> *vec =
          static_cast<const std::vector<BluetoothGATTDescriptor> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTDescriptor>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 83: {
      const std::vector<BluetoothGATTCharacteristic> *vec =
          static_cast<const std::vector<BluetoothGATTCharacteristic> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTCharacteristic>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 84: {
      const std::vector<BluetoothGATTService> *vec = static_cast<const std::vector<BluetoothGATTService> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTService>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 85: {
      const std::vector<BluetoothGATTGetServicesResponse> *vec =
          static_cast<const std::vector<BluetoothGATTGetServicesResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTGetServicesResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 86: {
      const std::vector<BluetoothGATTGetServicesDoneResponse> *vec =
          static_cast<const std::vector<BluetoothGATTGetServicesDoneResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTGetServicesDoneResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 87: {
      const std::vector<BluetoothGATTReadRequest> *vec =
          static_cast<const std::vector<BluetoothGATTReadRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTReadRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 88: {
      const std::vector<BluetoothGATTReadResponse> *vec =
          static_cast<const std::vector<BluetoothGATTReadResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTReadResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 89: {
      const std::vector<BluetoothGATTWriteRequest> *vec =
          static_cast<const std::vector<BluetoothGATTWriteRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTWriteRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 90: {
      const std::vector<BluetoothGATTReadDescriptorRequest> *vec =
          static_cast<const std::vector<BluetoothGATTReadDescriptorRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTReadDescriptorRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 91: {
      const std::vector<BluetoothGATTWriteDescriptorRequest> *vec =
          static_cast<const std::vector<BluetoothGATTWriteDescriptorRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTWriteDescriptorRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 92: {
      const std::vector<BluetoothGATTNotifyRequest> *vec =
          static_cast<const std::vector<BluetoothGATTNotifyRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTNotifyRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 93: {
      const std::vector<BluetoothGATTNotifyDataResponse> *vec =
          static_cast<const std::vector<BluetoothGATTNotifyDataResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTNotifyDataResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 94: {
      const std::vector<SubscribeBluetoothConnectionsFreeRequest> *vec =
          static_cast<const std::vector<SubscribeBluetoothConnectionsFreeRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeBluetoothConnectionsFreeRequest>(total_size, precalced_field_id_size,
                                                                                *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 95: {
      const std::vector<BluetoothConnectionsFreeResponse> *vec =
          static_cast<const std::vector<BluetoothConnectionsFreeResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothConnectionsFreeResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 96: {
      const std::vector<BluetoothGATTErrorResponse> *vec =
          static_cast<const std::vector<BluetoothGATTErrorResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTErrorResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 97: {
      const std::vector<BluetoothGATTWriteResponse> *vec =
          static_cast<const std::vector<BluetoothGATTWriteResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTWriteResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 98: {
      const std::vector<BluetoothGATTNotifyResponse> *vec =
          static_cast<const std::vector<BluetoothGATTNotifyResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothGATTNotifyResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 99: {
      const std::vector<BluetoothDevicePairingResponse> *vec =
          static_cast<const std::vector<BluetoothDevicePairingResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothDevicePairingResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 100: {
      const std::vector<BluetoothDeviceUnpairingResponse> *vec =
          static_cast<const std::vector<BluetoothDeviceUnpairingResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothDeviceUnpairingResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 101: {
      const std::vector<UnsubscribeBluetoothLEAdvertisementsRequest> *vec =
          static_cast<const std::vector<UnsubscribeBluetoothLEAdvertisementsRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<UnsubscribeBluetoothLEAdvertisementsRequest>(total_size, precalced_field_id_size,
                                                                                   *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 102: {
      const std::vector<BluetoothDeviceClearCacheResponse> *vec =
          static_cast<const std::vector<BluetoothDeviceClearCacheResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothDeviceClearCacheResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 103: {
      const std::vector<BluetoothScannerStateResponse> *vec =
          static_cast<const std::vector<BluetoothScannerStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothScannerStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_BLUETOOTH_PROXY
    case 104: {
      const std::vector<BluetoothScannerSetModeRequest> *vec =
          static_cast<const std::vector<BluetoothScannerSetModeRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<BluetoothScannerSetModeRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 105: {
      const std::vector<SubscribeVoiceAssistantRequest> *vec =
          static_cast<const std::vector<SubscribeVoiceAssistantRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<SubscribeVoiceAssistantRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 106: {
      const std::vector<VoiceAssistantAudioSettings> *vec =
          static_cast<const std::vector<VoiceAssistantAudioSettings> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantAudioSettings>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 107: {
      const std::vector<VoiceAssistantRequest> *vec =
          static_cast<const std::vector<VoiceAssistantRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 108: {
      const std::vector<VoiceAssistantResponse> *vec =
          static_cast<const std::vector<VoiceAssistantResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 109: {
      const std::vector<VoiceAssistantEventData> *vec =
          static_cast<const std::vector<VoiceAssistantEventData> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantEventData>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 110: {
      const std::vector<VoiceAssistantEventResponse> *vec =
          static_cast<const std::vector<VoiceAssistantEventResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantEventResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 111: {
      const std::vector<VoiceAssistantAudio> *vec = static_cast<const std::vector<VoiceAssistantAudio> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantAudio>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 112: {
      const std::vector<VoiceAssistantTimerEventResponse> *vec =
          static_cast<const std::vector<VoiceAssistantTimerEventResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantTimerEventResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 113: {
      const std::vector<VoiceAssistantAnnounceRequest> *vec =
          static_cast<const std::vector<VoiceAssistantAnnounceRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantAnnounceRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 114: {
      const std::vector<VoiceAssistantAnnounceFinished> *vec =
          static_cast<const std::vector<VoiceAssistantAnnounceFinished> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantAnnounceFinished>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 115: {
      const std::vector<VoiceAssistantWakeWord> *vec =
          static_cast<const std::vector<VoiceAssistantWakeWord> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantWakeWord>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 116: {
      const std::vector<VoiceAssistantConfigurationRequest> *vec =
          static_cast<const std::vector<VoiceAssistantConfigurationRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantConfigurationRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 117: {
      const std::vector<VoiceAssistantConfigurationResponse> *vec =
          static_cast<const std::vector<VoiceAssistantConfigurationResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantConfigurationResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VOICE_ASSISTANT
    case 118: {
      const std::vector<VoiceAssistantSetConfiguration> *vec =
          static_cast<const std::vector<VoiceAssistantSetConfiguration> *>(field_ptr);
      ProtoSize::add_repeated_message<VoiceAssistantSetConfiguration>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 119: {
      const std::vector<ListEntitiesAlarmControlPanelResponse> *vec =
          static_cast<const std::vector<ListEntitiesAlarmControlPanelResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesAlarmControlPanelResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 120: {
      const std::vector<AlarmControlPanelStateResponse> *vec =
          static_cast<const std::vector<AlarmControlPanelStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<AlarmControlPanelStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_ALARM_CONTROL_PANEL
    case 121: {
      const std::vector<AlarmControlPanelCommandRequest> *vec =
          static_cast<const std::vector<AlarmControlPanelCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<AlarmControlPanelCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_TEXT
    case 122: {
      const std::vector<ListEntitiesTextResponse> *vec =
          static_cast<const std::vector<ListEntitiesTextResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesTextResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_TEXT
    case 123: {
      const std::vector<TextStateResponse> *vec = static_cast<const std::vector<TextStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<TextStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_TEXT
    case 124: {
      const std::vector<TextCommandRequest> *vec = static_cast<const std::vector<TextCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<TextCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 125: {
      const std::vector<ListEntitiesDateResponse> *vec =
          static_cast<const std::vector<ListEntitiesDateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesDateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 126: {
      const std::vector<DateStateResponse> *vec = static_cast<const std::vector<DateStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<DateStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_DATE
    case 127: {
      const std::vector<DateCommandRequest> *vec = static_cast<const std::vector<DateCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<DateCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 128: {
      const std::vector<ListEntitiesTimeResponse> *vec =
          static_cast<const std::vector<ListEntitiesTimeResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesTimeResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 129: {
      const std::vector<TimeStateResponse> *vec = static_cast<const std::vector<TimeStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<TimeStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_TIME
    case 130: {
      const std::vector<TimeCommandRequest> *vec = static_cast<const std::vector<TimeCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<TimeCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_EVENT
    case 131: {
      const std::vector<ListEntitiesEventResponse> *vec =
          static_cast<const std::vector<ListEntitiesEventResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesEventResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_EVENT
    case 132: {
      const std::vector<EventResponse> *vec = static_cast<const std::vector<EventResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<EventResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VALVE
    case 133: {
      const std::vector<ListEntitiesValveResponse> *vec =
          static_cast<const std::vector<ListEntitiesValveResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesValveResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VALVE
    case 134: {
      const std::vector<ValveStateResponse> *vec = static_cast<const std::vector<ValveStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ValveStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_VALVE
    case 135: {
      const std::vector<ValveCommandRequest> *vec = static_cast<const std::vector<ValveCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<ValveCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 136: {
      const std::vector<ListEntitiesDateTimeResponse> *vec =
          static_cast<const std::vector<ListEntitiesDateTimeResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesDateTimeResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 137: {
      const std::vector<DateTimeStateResponse> *vec =
          static_cast<const std::vector<DateTimeStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<DateTimeStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_DATETIME_DATETIME
    case 138: {
      const std::vector<DateTimeCommandRequest> *vec =
          static_cast<const std::vector<DateTimeCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<DateTimeCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 139: {
      const std::vector<ListEntitiesUpdateResponse> *vec =
          static_cast<const std::vector<ListEntitiesUpdateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<ListEntitiesUpdateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 140: {
      const std::vector<UpdateStateResponse> *vec = static_cast<const std::vector<UpdateStateResponse> *>(field_ptr);
      ProtoSize::add_repeated_message<UpdateStateResponse>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
#ifdef USE_UPDATE
    case 141: {
      const std::vector<UpdateCommandRequest> *vec = static_cast<const std::vector<UpdateCommandRequest> *>(field_ptr);
      ProtoSize::add_repeated_message<UpdateCommandRequest>(total_size, precalced_field_id_size, *vec);
      break;
    }
#endif
    default:
      break;
  }
}

}  // namespace api
}  // namespace esphome
