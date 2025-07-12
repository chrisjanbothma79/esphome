#include "component_iterator.h"

#include "esphome/core/application.h"

#ifdef USE_API
#include "esphome/components/api/api_server.h"
#endif
#ifdef USE_API_SERVICES
#include "esphome/components/api/user_services.h"
#endif

namespace esphome {

#define ITER_COMPONENT(state_enum, vector, item_name, method) \
  case state_enum: { \
    if (this->at_ >= (vector).size()) { \
      advance_platform_(); \
    } else { \
      auto *(item_name) = (vector)[this->at_]; \
      if ((item_name)->is_internal() && !this->include_internal_) { \
        this->at_++; \
      } else if (this->method(item_name)) { \
        this->at_++; \
      } \
    } \
  } break;

void ComponentIterator::begin(bool include_internal) {
  this->state_ = IteratorState::BEGIN;
  this->at_ = 0;
  this->include_internal_ = include_internal;
}

void ComponentIterator::advance_platform_() {
  this->state_ = static_cast<IteratorState>(static_cast<uint32_t>(this->state_) + 1);
  this->at_ = 0;
}

void ComponentIterator::advance() {
  switch (this->state_) {
    case IteratorState::NONE:
      // not started
      return;
    case IteratorState::BEGIN:
      if (this->on_begin()) {
        advance_platform_();
      }
      break;

#ifdef USE_BINARY_SENSOR
      ITER_COMPONENT(IteratorState::BINARY_SENSOR, App.get_binary_sensors(), binary_sensor, on_binary_sensor)
#endif

#ifdef USE_COVER
      ITER_COMPONENT(IteratorState::COVER, App.get_covers(), cover, on_cover)
#endif

#ifdef USE_FAN
      ITER_COMPONENT(IteratorState::FAN, App.get_fans(), fan, on_fan)
#endif

#ifdef USE_LIGHT
      ITER_COMPONENT(IteratorState::LIGHT, App.get_lights(), light, on_light)
#endif

#ifdef USE_SENSOR
      ITER_COMPONENT(IteratorState::SENSOR, App.get_sensors(), sensor, on_sensor)
#endif

#ifdef USE_SWITCH
      ITER_COMPONENT(IteratorState::SWITCH, App.get_switches(), a_switch, on_switch)
#endif

#ifdef USE_BUTTON
      ITER_COMPONENT(IteratorState::BUTTON, App.get_buttons(), button, on_button)
#endif

#ifdef USE_TEXT_SENSOR
      ITER_COMPONENT(IteratorState::TEXT_SENSOR, App.get_text_sensors(), text_sensor, on_text_sensor)
#endif

#ifdef USE_API_SERVICES
      ITER_COMPONENT(IteratorState::SERVICE, api::global_api_server->get_user_services(), service, on_service)
#endif

#ifdef USE_CAMERA
    case IteratorState::CAMERA: {
      camera::Camera *camera_instance = camera::Camera::instance();
      if (camera_instance != nullptr && (!camera_instance->is_internal() || this->include_internal_)) {
        this->on_camera(camera_instance);
      }
      advance_platform_();
    } break;
#endif

#ifdef USE_CLIMATE
      ITER_COMPONENT(IteratorState::CLIMATE, App.get_climates(), climate, on_climate)
#endif

#ifdef USE_NUMBER
      ITER_COMPONENT(IteratorState::NUMBER, App.get_numbers(), number, on_number)
#endif

#ifdef USE_DATETIME_DATE
      ITER_COMPONENT(IteratorState::DATETIME_DATE, App.get_dates(), date, on_date)
#endif

#ifdef USE_DATETIME_TIME
      ITER_COMPONENT(IteratorState::DATETIME_TIME, App.get_times(), time, on_time)
#endif

#ifdef USE_DATETIME_DATETIME
      ITER_COMPONENT(IteratorState::DATETIME_DATETIME, App.get_datetimes(), datetime, on_datetime)
#endif

#ifdef USE_TEXT
      ITER_COMPONENT(IteratorState::TEXT, App.get_texts(), text, on_text)
#endif

#ifdef USE_SELECT
      ITER_COMPONENT(IteratorState::SELECT, App.get_selects(), select, on_select)
#endif

#ifdef USE_LOCK
      ITER_COMPONENT(IteratorState::LOCK, App.get_locks(), lock, on_lock)
#endif

#ifdef USE_VALVE
      ITER_COMPONENT(IteratorState::VALVE, App.get_valves(), valve, on_valve)
#endif

#ifdef USE_MEDIA_PLAYER
      ITER_COMPONENT(IteratorState::MEDIA_PLAYER, App.get_media_players(), media_player, on_media_player)
#endif

#ifdef USE_ALARM_CONTROL_PANEL
      ITER_COMPONENT(IteratorState::ALARM_CONTROL_PANEL, App.get_alarm_control_panels(), alarm_control_panel,
                     on_alarm_control_panel)
#endif

#ifdef USE_EVENT
      ITER_COMPONENT(IteratorState::EVENT, App.get_events(), event, on_event)
#endif

#ifdef USE_UPDATE
      ITER_COMPONENT(IteratorState::UPDATE, App.get_updates(), update, on_update)
#endif

    case IteratorState::MAX:
      if (this->on_end()) {
        this->state_ = IteratorState::NONE;
      }
      return;
  }
}

bool ComponentIterator::on_end() { return true; }
bool ComponentIterator::on_begin() { return true; }
#ifdef USE_API_SERVICES
bool ComponentIterator::on_service(api::UserServiceDescriptor *service) { return true; }
#endif
#ifdef USE_CAMERA
bool ComponentIterator::on_camera(camera::Camera *camera) { return true; }
#endif
#ifdef USE_MEDIA_PLAYER
bool ComponentIterator::on_media_player(media_player::MediaPlayer *media_player) { return true; }
#endif
}  // namespace esphome
