#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome {
namespace project_version {

class ProjectVersionTextSensor : public text_sensor::TextSensor, public Component {
 public:
  void set_hide_timestamp(bool hide_timestamp);
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  std::string unique_id() override;

 protected:
  bool hide_timestamp_{false};
};

}  // namespace project_version
}  // namespace esphome
