#include "vbus_binary_sensor.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace vbus {

static const char *const TAG = "vbus.binary_sensor";

void DeltaSolBSPlusBSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Deltasol BS Plus:");
  LOG_BINARY_SENSOR("  ", "Relay 1 On", this->relay1_bsensor_);
  LOG_BINARY_SENSOR("  ", "Relay 2 On", this->relay2_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 1 Error", this->s1_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 2 Error", this->s2_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 3 Error", this->s3_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 4 Error", this->s4_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Option Collector Max", this->collector_max_bsensor_);
  LOG_BINARY_SENSOR("  ", "Option Collector Min", this->collector_min_bsensor_);
  LOG_BINARY_SENSOR("  ", "Option Collector Frost", this->collector_frost_bsensor_);
  LOG_BINARY_SENSOR("  ", "Option Tube Collector", this->tube_collector_bsensor_);
  LOG_BINARY_SENSOR("  ", "Option Recooling", this->recooling_bsensor_);
  LOG_BINARY_SENSOR("  ", "Option Heat Quantity Measurement", this->hqm_bsensor_);
}

void DeltaSolBSPlusBSensor::handle_message(std::vector<uint8_t> &message) {
  if (this->relay1_bsensor_ != nullptr)
    this->relay1_bsensor_->publish_state(message[10] & 1);
  if (this->relay2_bsensor_ != nullptr)
    this->relay2_bsensor_->publish_state(message[10] & 2);
  if (this->s1_error_bsensor_ != nullptr)
    this->s1_error_bsensor_->publish_state(message[11] & 1);
  if (this->s2_error_bsensor_ != nullptr)
    this->s2_error_bsensor_->publish_state(message[11] & 2);
  if (this->s3_error_bsensor_ != nullptr)
    this->s3_error_bsensor_->publish_state(message[11] & 4);
  if (this->s4_error_bsensor_ != nullptr)
    this->s4_error_bsensor_->publish_state(message[11] & 8);
  if (this->collector_max_bsensor_ != nullptr)
    this->collector_max_bsensor_->publish_state(message[15] & 1);
  if (this->collector_min_bsensor_ != nullptr)
    this->collector_min_bsensor_->publish_state(message[15] & 2);
  if (this->collector_frost_bsensor_ != nullptr)
    this->collector_frost_bsensor_->publish_state(message[15] & 4);
  if (this->tube_collector_bsensor_ != nullptr)
    this->tube_collector_bsensor_->publish_state(message[15] & 8);
  if (this->recooling_bsensor_ != nullptr)
    this->recooling_bsensor_->publish_state(message[15] & 0x10);
  if (this->hqm_bsensor_ != nullptr)
    this->hqm_bsensor_->publish_state(message[15] & 0x20);
}

void DeltaSolBS2009BSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Deltasol BS 2009:");
  LOG_BINARY_SENSOR("  ", "Sensor 1 Error", this->s1_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 2 Error", this->s2_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 3 Error", this->s3_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 4 Error", this->s4_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Frost Protection Active", this->frost_protection_active_bsensor_);
}

void DeltaSolBS2009BSensor::handle_message(std::vector<uint8_t> &message) {
  if (this->s1_error_bsensor_ != nullptr)
    this->s1_error_bsensor_->publish_state(message[20] & 1);
  if (this->s2_error_bsensor_ != nullptr)
    this->s2_error_bsensor_->publish_state(message[20] & 2);
  if (this->s3_error_bsensor_ != nullptr)
    this->s3_error_bsensor_->publish_state(message[20] & 4);
  if (this->s4_error_bsensor_ != nullptr)
    this->s4_error_bsensor_->publish_state(message[20] & 8);
  if (this->frost_protection_active_bsensor_ != nullptr)
    this->frost_protection_active_bsensor_->publish_state(message[25] & 1);
}

void DeltaSolBXBSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Deltasol BX:");
  LOG_BINARY_SENSOR("  ", "Sensor 1 Error", this->s1_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 2 Error", this->s2_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 3 Error", this->s3_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 4 Error", this->s4_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 5 Error", this->s5_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 6 Error", this->s6_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 7 Error", this->s7_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 8 Error", this->s8_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 9 Error", this->s9_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "V40 Error", this->v40_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Leakage", this->leakage_bsensor_);
  LOG_BINARY_SENSOR("  ", "Overpressure", this->overpressure_bsensor_);
  LOG_BINARY_SENSOR("  ", "Flow Rate Error", this->flow_rate_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Blocking Protection 1", this->blocking_protection1_bsensor_);
  LOG_BINARY_SENSOR("  ", "Blocking Protection 2", this->blocking_protection2_bsensor_);
  LOG_BINARY_SENSOR("  ", "Blocking Protection 3", this->blocking_protection3_bsensor_);
  LOG_BINARY_SENSOR("  ", "Blocking Protection 4", this->blocking_protection4_bsensor_);
  LOG_BINARY_SENSOR("  ", "Initialisation", this->initialisation_bsensor_);
  LOG_BINARY_SENSOR("  ", "Filling", this->filling_bsensor_);
  LOG_BINARY_SENSOR("  ", "Stabilisation", this->stabilisation_bsensor_);
  LOG_BINARY_SENSOR("  ", "Pump Delay", this->pump_delay_bsensor_);
  LOG_BINARY_SENSOR("  ", "Heat Dump", this->heat_dump_bsensor_);
  LOG_BINARY_SENSOR("  ", "Overrun", this->overrun_bsensor_);
  LOG_BINARY_SENSOR("  ", "Thermal Disinfection", this->thermal_disinfection_bsensor_);
  LOG_BINARY_SENSOR("  ", "System Cooling", this->system_cooling_bsensor_);
  LOG_BINARY_SENSOR("  ", "Store Cooling", this->store_cooling_bsensor_);
  LOG_BINARY_SENSOR("  ", "Spreading", this->spreading_bsensor_);
  LOG_BINARY_SENSOR("  ", "Antifreeze", this->antifreeze_bsensor_);
  LOG_BINARY_SENSOR("  ", "Collector Cooling", this->collector_cooling_bsensor_);
}

void DeltaSolBXBSensor::handle_message(std::vector<uint8_t> &message) {
  if (this->s1_error_bsensor_ != nullptr)
    this->s1_error_bsensor_->publish_state(message[44] & 0x01);
  if (this->s2_error_bsensor_ != nullptr)
    this->s2_error_bsensor_->publish_state(message[44] & 0x02);
  if (this->s3_error_bsensor_ != nullptr)
    this->s3_error_bsensor_->publish_state(message[44] & 0x04);
  if (this->s4_error_bsensor_ != nullptr)
    this->s4_error_bsensor_->publish_state(message[44] & 0x08);
  if (this->s5_error_bsensor_ != nullptr)
    this->s5_error_bsensor_->publish_state(message[44] & 0x10);
  if (this->s6_error_bsensor_ != nullptr)
    this->s6_error_bsensor_->publish_state(message[44] & 0x20);
  if (this->s7_error_bsensor_ != nullptr)
    this->s7_error_bsensor_->publish_state(message[44] & 0x40);
  if (this->s8_error_bsensor_ != nullptr)
    this->s8_error_bsensor_->publish_state(message[44] & 0x80);
  if (this->s9_error_bsensor_ != nullptr)
    this->s9_error_bsensor_->publish_state(message[45] & 0x01);
  if (this->v40_error_bsensor_ != nullptr)
    this->v40_error_bsensor_->publish_state(message[45] & 0x02);
  if (this->leakage_bsensor_ != nullptr)
    this->leakage_bsensor_->publish_state(message[45] & 0x04);
  if (this->overpressure_bsensor_ != nullptr)
    this->overpressure_bsensor_->publish_state(message[45] & 0x08);
  if (this->flow_rate_error_bsensor_ != nullptr)
    this->flow_rate_error_bsensor_->publish_state(message[45] & 0x10);
  if (this->blocking_protection1_bsensor_ != nullptr)
    this->blocking_protection1_bsensor_->publish_state(message[46] & 0x01);
  if (this->blocking_protection2_bsensor_ != nullptr)
    this->blocking_protection2_bsensor_->publish_state(message[46] & 0x02);
  if (this->blocking_protection3_bsensor_ != nullptr)
    this->blocking_protection3_bsensor_->publish_state(message[46] & 0x04);
  if (this->blocking_protection4_bsensor_ != nullptr)
    this->blocking_protection4_bsensor_->publish_state(message[46] & 0x08);
  if (this->initialisation_bsensor_ != nullptr)
    this->initialisation_bsensor_->publish_state(message[46] & 0x10);
  if (this->filling_bsensor_ != nullptr)
    this->filling_bsensor_->publish_state(message[46] & 0x20);
  if (this->stabilisation_bsensor_ != nullptr)
    this->stabilisation_bsensor_->publish_state(message[46] & 0x40);
  if (this->pump_delay_bsensor_ != nullptr)
    this->pump_delay_bsensor_->publish_state(message[46] & 0x80);
  if (this->heat_dump_bsensor_ != nullptr)
    this->heat_dump_bsensor_->publish_state(message[47] & 0x01);
  if (this->overrun_bsensor_ != nullptr)
    this->overrun_bsensor_->publish_state(message[47] & 0x02);
  if (this->thermal_disinfection_bsensor_ != nullptr)
    this->thermal_disinfection_bsensor_->publish_state(message[47] & 0x04);
  if (this->system_cooling_bsensor_ != nullptr)
    this->system_cooling_bsensor_->publish_state(message[47] & 0x08);
  if (this->store_cooling_bsensor_ != nullptr)
    this->store_cooling_bsensor_->publish_state(message[47] & 0x10);
  if (this->spreading_bsensor_ != nullptr)
    this->spreading_bsensor_->publish_state(message[47] & 0x20);
  if (this->antifreeze_bsensor_ != nullptr)
    this->antifreeze_bsensor_->publish_state(message[47] & 0x40);
  if (this->collector_cooling_bsensor_ != nullptr)
    this->collector_cooling_bsensor_->publish_state(message[47] & 0x80);
}

void DeltaSolCBSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Deltasol C:");
  LOG_BINARY_SENSOR("  ", "Sensor 1 Error", this->s1_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 2 Error", this->s2_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 3 Error", this->s3_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 4 Error", this->s4_error_bsensor_);
}

void DeltaSolCBSensor::handle_message(std::vector<uint8_t> &message) {
  if (this->s1_error_bsensor_ != nullptr)
    this->s1_error_bsensor_->publish_state(message[10] & 1);
  if (this->s2_error_bsensor_ != nullptr)
    this->s2_error_bsensor_->publish_state(message[10] & 2);
  if (this->s3_error_bsensor_ != nullptr)
    this->s3_error_bsensor_->publish_state(message[10] & 4);
  if (this->s4_error_bsensor_ != nullptr)
    this->s4_error_bsensor_->publish_state(message[10] & 8);
}

void DeltaSolCS2BSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Deltasol CS2:");
  LOG_BINARY_SENSOR("  ", "Sensor 1 Error", this->s1_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 2 Error", this->s2_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 3 Error", this->s3_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 4 Error", this->s4_error_bsensor_);
}

void DeltaSolCS2BSensor::handle_message(std::vector<uint8_t> &message) {
  if (this->s1_error_bsensor_ != nullptr)
    this->s1_error_bsensor_->publish_state(message[18] & 1);
  if (this->s2_error_bsensor_ != nullptr)
    this->s2_error_bsensor_->publish_state(message[18] & 2);
  if (this->s3_error_bsensor_ != nullptr)
    this->s3_error_bsensor_->publish_state(message[18] & 4);
  if (this->s4_error_bsensor_ != nullptr)
    this->s4_error_bsensor_->publish_state(message[18] & 8);
}

void DeltaSolCSPlusBSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Deltasol CS Plus:");
  LOG_BINARY_SENSOR("  ", "Sensor 1 Error", this->s1_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 2 Error", this->s2_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 3 Error", this->s3_error_bsensor_);
  LOG_BINARY_SENSOR("  ", "Sensor 4 Error", this->s4_error_bsensor_);
}

void DeltaSolCSPlusBSensor::handle_message(std::vector<uint8_t> &message) {
  if (this->s1_error_bsensor_ != nullptr)
    this->s1_error_bsensor_->publish_state(message[20] & 1);
  if (this->s2_error_bsensor_ != nullptr)
    this->s2_error_bsensor_->publish_state(message[20] & 2);
  if (this->s3_error_bsensor_ != nullptr)
    this->s3_error_bsensor_->publish_state(message[20] & 4);
  if (this->s4_error_bsensor_ != nullptr)
    this->s4_error_bsensor_->publish_state(message[20] & 8);
}

void VBusCustomBSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "VBus Custom Binary Sensor:");
  if (this->source_ == 0xffff) {
    ESP_LOGCONFIG(TAG, "  Source address: ANY");
  } else {
    ESP_LOGCONFIG(TAG, "  Source address: 0x%04x", this->source_);
  }
  if (this->dest_ == 0xffff) {
    ESP_LOGCONFIG(TAG, "  Dest address: ANY");
  } else {
    ESP_LOGCONFIG(TAG, "  Dest address: 0x%04x", this->dest_);
  }
  if (this->command_ == 0xffff) {
    ESP_LOGCONFIG(TAG, "  Command: ANY");
  } else {
    ESP_LOGCONFIG(TAG, "  Command: 0x%04x", this->command_);
  }
  ESP_LOGCONFIG(TAG, "  Binary Sensors:");
  for (VBusCustomSubBSensor *bsensor : this->bsensors_) {
    LOG_BINARY_SENSOR("  ", "-", bsensor);
  }
}

void VBusCustomBSensor::handle_message(std::vector<uint8_t> &message) {
  for (VBusCustomSubBSensor *bsensor : this->bsensors_)
    bsensor->parse_message(message);
}

void VBusCustomSubBSensor::parse_message(std::vector<uint8_t> &message) {
  this->publish_state(this->message_parser_(message));
}

}  // namespace vbus
}  // namespace esphome
