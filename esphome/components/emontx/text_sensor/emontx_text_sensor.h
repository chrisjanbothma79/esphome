#pragma once

#include "esphome/components/emontx/emontx.h"
#include "esphome/components/text_sensor/text_sensor.h"
namespace esphome {
namespace emontx {
class EmonTxTextSensor : public EmonTxListener, public text_sensor::TextSensor, public Component {
 public:
  EmonTxTextSensor(const char *tag);
  void publish_val(const std::string &val) override;
  void dump_config() override;
};
}  // namespace emontx
}  // namespace esphome
