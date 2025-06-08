#include "esphome/core/log.h"
#include "emontx_text_sensor.h"
namespace esphome {
namespace emontx {
static const char *const TAG = "emontx_text_sensor";
EmonTxTextSensor::EmonTxTextSensor(const char *tag) { this->tag = std::string(tag); }
void EmonTxTextSensor::publish_val(const std::string &val) { publish_state(val); }
void EmonTxTextSensor::dump_config() { LOG_TEXT_SENSOR("  ", "EmonTx Text Sensor", this); }
}  // namespace emontx
}  // namespace esphome
