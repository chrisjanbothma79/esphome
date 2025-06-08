#include "esphome/core/log.h"
#include "emontx_text_sensor.h"
namespace esphome {
namespace emontx {
static const char *const TAG = "emontx_text_sensor";
emonTxTextSensor::emonTxTextSensor(const char *tag) { this->tag = std::string(tag); }
void emonTxTextSensor::publish_val(const std::string &val) { publish_state(val); }
void emonTxTextSensor::dump_config() { LOG_TEXT_SENSOR("  ", "emonTx Text Sensor", this); }
}  // namespace emontx
}  // namespace esphome
