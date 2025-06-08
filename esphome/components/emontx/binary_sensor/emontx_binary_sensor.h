#pragma once

#include "esphome/components/emontx/emontx.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace emontx {
class emonTxBinarySensor : public emonTxListener, public binary_sensor::BinarySensor, public Component {
 public:
  explicit emonTxBinarySensor(const char *tag);
  void publish_val(const std::string &val) override;
  void dump_config() override;
};

}  // namespace emontx
}  // namespace esphome
