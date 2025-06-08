#pragma once

#include "esphome/components/emontx/emontx.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace emontx {
class emonTxSensor : public emonTxListener, public sensor::Sensor, public Component {
 public:
  emonTxSensor(const char *tag);
  void publish_val(const std::string &val) override;
  void dump_config() override;
};

}  // namespace emontx
}  // namespace esphome
