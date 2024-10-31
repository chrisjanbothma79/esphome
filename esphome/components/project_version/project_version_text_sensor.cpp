#include "project_version_text_sensor.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/version.h"

namespace esphome {
namespace project_version {

static const char *const TAG = "project_version.text_sensor";

void ProjectVersionTextSensor::setup() {
  if (this->hide_timestamp_) {
    this->publish_state(ESPHOME_PROJECT_VERSION);
  } else {
    this->publish_state(ESPHOME_PROJECT_VERSION " " + App.get_compilation_time());
  }
}
float ProjectVersionTextSensor::get_setup_priority() const { return setup_priority::DATA; }
void ProjectVersionTextSensor::set_hide_timestamp(bool hide_timestamp) { this->hide_timestamp_ = hide_timestamp; }
std::string ProjectVersionTextSensor::unique_id() { return get_mac_address() + "-project_version"; }
void ProjectVersionTextSensor::dump_config() { LOG_TEXT_SENSOR("", "Project Version Text Sensor", this); }

}  // namespace project_version
}  // namespace esphome
