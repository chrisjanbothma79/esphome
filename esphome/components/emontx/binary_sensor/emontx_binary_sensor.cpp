#include "esphome/core/log.h"
#include "emontx_binary_sensor.h"
namespace esphome {
namespace emontx {
static const char *const TAG = "emontx_binary_sensor";
EmonTxBinarySensor::EmonTxBinarySensor(const char *tag) { this->tag = std::string(tag); }
void EmonTxBinarySensor::publish_val(const std::string &val) {
  // Convert the string value to a boolean (e.g., "1" -> true, "0" -> false)
  bool state = (val != "0");
  publish_state(state);
}
void EmonTxBinarySensor::dump_config() { LOG_BINARY_SENSOR("  ", "EmonTx Binary Sensor", this); }
}  // namespace emontx
}  // namespace esphome
