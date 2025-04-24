#include "esphome/core/log.h"
#include "bh1900nux.h"

namespace esphome {
namespace bh1900nux_i2c {

static const char *TAG = "bh1900nux_i2c.sensor";

void EmptyI2CSensor::setup() {}

void EmptyI2CSensor::update() {}

void EmptyI2CSensor::dump_config() {}

}  // namespace bh1900nux_i2c
}  // namespace esphome
