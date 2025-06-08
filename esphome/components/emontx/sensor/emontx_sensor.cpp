#include "esphome/core/log.h"
#include "emontx_sensor.h"
namespace esphome {
namespace emontx {
static const char *const TAG = "emontx_sensor";
emonTxSensor::emonTxSensor(const char *tag) { this->tag = std::string(tag); }
void emonTxSensor::publish_val(const std::string &val) {
  auto newval = parse_number<float>(val).value_or(0.0f);
  publish_state(newval);
}
void emonTxSensor::dump_config() { LOG_SENSOR("  ", "emonTx Sensor", this); }
}  // namespace emontx
}  // namespace esphome
