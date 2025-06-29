#include "list_entities.h"
#ifdef USE_API
#include "api_connection.h"
#include "api_pb2.h"
#include "esphome/core/application.h"
#include "esphome/core/log.h"
#include "esphome/core/util.h"

namespace esphome {
namespace api {

#ifdef USE_BINARY_SENSOR
bool ListEntitiesIterator::on_binary_sensor(binary_sensor::BinarySensor *binary_sensor) {
  return this->client_->schedule_message_(binary_sensor, &APIConnection::try_send_binary_sensor_info,
                                          ListEntitiesBinarySensorResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_COVER
bool ListEntitiesIterator::on_cover(cover::Cover *cover) {
  return this->client_->schedule_message_(cover, &APIConnection::try_send_cover_info,
                                          ListEntitiesCoverResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_FAN
bool ListEntitiesIterator::on_fan(fan::Fan *fan) {
  return this->client_->schedule_message_(fan, &APIConnection::try_send_fan_info,
                                          ListEntitiesFanResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_LIGHT
bool ListEntitiesIterator::on_light(light::LightState *light) {
  return this->client_->schedule_message_(light, &APIConnection::try_send_light_info,
                                          ListEntitiesLightResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_SENSOR
bool ListEntitiesIterator::on_sensor(sensor::Sensor *sensor) {
  return this->client_->schedule_message_(sensor, &APIConnection::try_send_sensor_info,
                                          ListEntitiesSensorResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_SWITCH
bool ListEntitiesIterator::on_switch(switch_::Switch *a_switch) {
  return this->client_->schedule_message_(a_switch, &APIConnection::try_send_switch_info,
                                          ListEntitiesSwitchResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_BUTTON
bool ListEntitiesIterator::on_button(button::Button *button) {
  return this->client_->schedule_message_(button, &APIConnection::try_send_button_info,
                                          ListEntitiesButtonResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_TEXT_SENSOR
bool ListEntitiesIterator::on_text_sensor(text_sensor::TextSensor *text_sensor) {
  return this->client_->schedule_message_(text_sensor, &APIConnection::try_send_text_sensor_info,
                                          ListEntitiesTextSensorResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_LOCK
bool ListEntitiesIterator::on_lock(lock::Lock *a_lock) {
  return this->client_->schedule_message_(a_lock, &APIConnection::try_send_lock_info,
                                          ListEntitiesLockResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_VALVE
bool ListEntitiesIterator::on_valve(valve::Valve *valve) {
  return this->client_->schedule_message_(valve, &APIConnection::try_send_valve_info,
                                          ListEntitiesValveResponse::MESSAGE_TYPE);
}
#endif

bool ListEntitiesIterator::on_end() { return this->client_->send_list_info_done(); }
ListEntitiesIterator::ListEntitiesIterator(APIConnection *client) : client_(client) {}
bool ListEntitiesIterator::on_service(UserServiceDescriptor *service) {
  auto resp = service->encode_list_service_response();
  return this->client_->send_message(resp);
}

#ifdef USE_ESP32_CAMERA
bool ListEntitiesIterator::on_camera(esp32_camera::ESP32Camera *camera) {
  return this->client_->schedule_message_(camera, &APIConnection::try_send_camera_info,
                                          ListEntitiesCameraResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_CLIMATE
bool ListEntitiesIterator::on_climate(climate::Climate *climate) {
  return this->client_->schedule_message_(climate, &APIConnection::try_send_climate_info,
                                          ListEntitiesClimateResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_NUMBER
bool ListEntitiesIterator::on_number(number::Number *number) {
  return this->client_->schedule_message_(number, &APIConnection::try_send_number_info,
                                          ListEntitiesNumberResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_DATETIME_DATE
bool ListEntitiesIterator::on_date(datetime::DateEntity *date) {
  return this->client_->schedule_message_(date, &APIConnection::try_send_date_info,
                                          ListEntitiesDateResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_DATETIME_TIME
bool ListEntitiesIterator::on_time(datetime::TimeEntity *time) {
  return this->client_->schedule_message_(time, &APIConnection::try_send_time_info,
                                          ListEntitiesTimeResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_DATETIME_DATETIME
bool ListEntitiesIterator::on_datetime(datetime::DateTimeEntity *datetime) {
  return this->client_->schedule_message_(datetime, &APIConnection::try_send_datetime_info,
                                          ListEntitiesDateTimeResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_TEXT
bool ListEntitiesIterator::on_text(text::Text *text) {
  return this->client_->schedule_message_(text, &APIConnection::try_send_text_info,
                                          ListEntitiesTextResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_SELECT
bool ListEntitiesIterator::on_select(select::Select *select) {
  return this->client_->schedule_message_(select, &APIConnection::try_send_select_info,
                                          ListEntitiesSelectResponse::MESSAGE_TYPE);
}
#endif

#ifdef USE_MEDIA_PLAYER
bool ListEntitiesIterator::on_media_player(media_player::MediaPlayer *media_player) {
  return this->client_->schedule_message_(media_player, &APIConnection::try_send_media_player_info,
                                          ListEntitiesMediaPlayerResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_ALARM_CONTROL_PANEL
bool ListEntitiesIterator::on_alarm_control_panel(alarm_control_panel::AlarmControlPanel *a_alarm_control_panel) {
  return this->client_->schedule_message_(a_alarm_control_panel, &APIConnection::try_send_alarm_control_panel_info,
                                          ListEntitiesAlarmControlPanelResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_EVENT
bool ListEntitiesIterator::on_event(event::Event *event) {
  return this->client_->schedule_message_(event, &APIConnection::try_send_event_info,
                                          ListEntitiesEventResponse::MESSAGE_TYPE);
}
#endif
#ifdef USE_UPDATE
bool ListEntitiesIterator::on_update(update::UpdateEntity *update) {
  return this->client_->schedule_message_(update, &APIConnection::try_send_update_info,
                                          ListEntitiesUpdateResponse::MESSAGE_TYPE);
}
#endif

}  // namespace api
}  // namespace esphome
#endif
