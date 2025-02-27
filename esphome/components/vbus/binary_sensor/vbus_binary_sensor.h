#pragma once

#include "../vbus.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

namespace esphome {
namespace vbus {

class DeltaSolBSPlusBSensor : public VBusListener, public Component {
 public:
  void dump_config() override;
  void set_relay1_bsensor(binary_sensor::BinarySensor *bsensor) { this->relay1_bsensor_ = bsensor; }
  void set_relay2_bsensor(binary_sensor::BinarySensor *bsensor) { this->relay2_bsensor_ = bsensor; }
  void set_s1_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s1_error_bsensor_ = bsensor; }
  void set_s2_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s2_error_bsensor_ = bsensor; }
  void set_s3_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s3_error_bsensor_ = bsensor; }
  void set_s4_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s4_error_bsensor_ = bsensor; }
  void set_collector_max_bsensor(binary_sensor::BinarySensor *bsensor) { this->collector_max_bsensor_ = bsensor; }
  void set_collector_min_bsensor(binary_sensor::BinarySensor *bsensor) { this->collector_min_bsensor_ = bsensor; }
  void set_collector_frost_bsensor(binary_sensor::BinarySensor *bsensor) { this->collector_frost_bsensor_ = bsensor; }
  void set_tube_collector_bsensor(binary_sensor::BinarySensor *bsensor) { this->tube_collector_bsensor_ = bsensor; }
  void set_recooling_bsensor(binary_sensor::BinarySensor *bsensor) { this->recooling_bsensor_ = bsensor; }
  void set_hqm_bsensor(binary_sensor::BinarySensor *bsensor) { this->hqm_bsensor_ = bsensor; }

 protected:
  binary_sensor::BinarySensor *relay1_bsensor_{nullptr};
  binary_sensor::BinarySensor *relay2_bsensor_{nullptr};
  binary_sensor::BinarySensor *s1_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s2_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s3_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s4_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *collector_max_bsensor_{nullptr};
  binary_sensor::BinarySensor *collector_min_bsensor_{nullptr};
  binary_sensor::BinarySensor *collector_frost_bsensor_{nullptr};
  binary_sensor::BinarySensor *tube_collector_bsensor_{nullptr};
  binary_sensor::BinarySensor *recooling_bsensor_{nullptr};
  binary_sensor::BinarySensor *hqm_bsensor_{nullptr};

  void handle_message(std::vector<uint8_t> &message) override;
};

class DeltaSolBS2009BSensor : public VBusListener, public Component {
 public:
  void dump_config() override;
  void set_s1_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s1_error_bsensor_ = bsensor; }
  void set_s2_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s2_error_bsensor_ = bsensor; }
  void set_s3_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s3_error_bsensor_ = bsensor; }
  void set_s4_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s4_error_bsensor_ = bsensor; }
  void set_frost_protection_active_bsensor(binary_sensor::BinarySensor *bsensor) {
    this->frost_protection_active_bsensor_ = bsensor;
  }

 protected:
  binary_sensor::BinarySensor *s1_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s2_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s3_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s4_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *frost_protection_active_bsensor_{nullptr};

  void handle_message(std::vector<uint8_t> &message) override;
};

class DeltaSolBXBSensor : public VBusListener, public Component {
 public:
  void dump_config() override;
  void set_s1_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s1_error_bsensor_ = bsensor; }
  void set_s2_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s2_error_bsensor_ = bsensor; }
  void set_s3_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s3_error_bsensor_ = bsensor; }
  void set_s4_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s4_error_bsensor_ = bsensor; }
  void set_s5_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s5_error_bsensor_ = bsensor; }
  void set_s6_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s6_error_bsensor_ = bsensor; }
  void set_s7_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s7_error_bsensor_ = bsensor; }
  void set_s8_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s8_error_bsensor_ = bsensor; }
  void set_s9_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s9_error_bsensor_ = bsensor; }
  void set_v40_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->v40_error_bsensor_ = bsensor; }
  void set_leakage_bsensor(binary_sensor::BinarySensor *bsensor) { this->leakage_bsensor_ = bsensor; }
  void set_overpressure_bsensor(binary_sensor::BinarySensor *bsensor) { this->overpressure_bsensor_ = bsensor; }
  void set_flow_rate_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->flow_rate_error_bsensor_ = bsensor; }
  void set_blocking_protection1_bsensor(binary_sensor::BinarySensor *bsensor) {
    this->blocking_protection1_bsensor_ = bsensor;
  }
  void set_blocking_protection2_bsensor(binary_sensor::BinarySensor *bsensor) {
    this->blocking_protection2_bsensor_ = bsensor;
  }
  void set_blocking_protection3_bsensor(binary_sensor::BinarySensor *bsensor) {
    this->blocking_protection3_bsensor_ = bsensor;
  }
  void set_blocking_protection4_bsensor(binary_sensor::BinarySensor *bsensor) {
    this->blocking_protection4_bsensor_ = bsensor;
  }
  void set_initialisation_bsensor(binary_sensor::BinarySensor *bsensor) { this->initialisation_bsensor_ = bsensor; }
  void set_filling_bsensor(binary_sensor::BinarySensor *bsensor) { this->filling_bsensor_ = bsensor; }
  void set_stabilisation_bsensor(binary_sensor::BinarySensor *bsensor) { this->stabilisation_bsensor_ = bsensor; }
  void set_pump_delay_bsensor(binary_sensor::BinarySensor *bsensor) { this->pump_delay_bsensor_ = bsensor; }
  void set_heat_dump_bsensor(binary_sensor::BinarySensor *bsensor) { this->heat_dump_bsensor_ = bsensor; }
  void set_overrun_bsensor(binary_sensor::BinarySensor *bsensor) { this->overrun_bsensor_ = bsensor; }
  void set_thermal_disinfection_bsensor(binary_sensor::BinarySensor *bsensor) {
    this->thermal_disinfection_bsensor_ = bsensor;
  }
  void set_system_cooling_bsensor(binary_sensor::BinarySensor *bsensor) { this->system_cooling_bsensor_ = bsensor; }
  void set_store_cooling_bsensor(binary_sensor::BinarySensor *bsensor) { this->store_cooling_bsensor_ = bsensor; }
  void set_spreading_bsensor(binary_sensor::BinarySensor *bsensor) { this->spreading_bsensor_ = bsensor; }
  void set_antifreeze_bsensor(binary_sensor::BinarySensor *bsensor) { this->antifreeze_bsensor_ = bsensor; }
  void set_collector_cooling_bsensor(binary_sensor::BinarySensor *bsensor) {
    this->collector_cooling_bsensor_ = bsensor;
  }

 protected:
  binary_sensor::BinarySensor *s1_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s2_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s3_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s4_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s5_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s6_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s7_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s8_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s9_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *v40_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *leakage_bsensor_{nullptr};
  binary_sensor::BinarySensor *overpressure_bsensor_{nullptr};
  binary_sensor::BinarySensor *flow_rate_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *blocking_protection1_bsensor_{nullptr};
  binary_sensor::BinarySensor *blocking_protection2_bsensor_{nullptr};
  binary_sensor::BinarySensor *blocking_protection3_bsensor_{nullptr};
  binary_sensor::BinarySensor *blocking_protection4_bsensor_{nullptr};
  binary_sensor::BinarySensor *initialisation_bsensor_{nullptr};
  binary_sensor::BinarySensor *filling_bsensor_{nullptr};
  binary_sensor::BinarySensor *stabilisation_bsensor_{nullptr};
  binary_sensor::BinarySensor *pump_delay_bsensor_{nullptr};
  binary_sensor::BinarySensor *heat_dump_bsensor_{nullptr};
  binary_sensor::BinarySensor *overrun_bsensor_{nullptr};
  binary_sensor::BinarySensor *thermal_disinfection_bsensor_{nullptr};
  binary_sensor::BinarySensor *system_cooling_bsensor_{nullptr};
  binary_sensor::BinarySensor *store_cooling_bsensor_{nullptr};
  binary_sensor::BinarySensor *spreading_bsensor_{nullptr};
  binary_sensor::BinarySensor *antifreeze_bsensor_{nullptr};
  binary_sensor::BinarySensor *collector_cooling_bsensor_{nullptr};

  void handle_message(std::vector<uint8_t> &message) override;
};

class DeltaSolCBSensor : public VBusListener, public Component {
 public:
  void dump_config() override;
  void set_s1_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s1_error_bsensor_ = bsensor; }
  void set_s2_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s2_error_bsensor_ = bsensor; }
  void set_s3_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s3_error_bsensor_ = bsensor; }
  void set_s4_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s4_error_bsensor_ = bsensor; }

 protected:
  binary_sensor::BinarySensor *s1_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s2_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s3_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s4_error_bsensor_{nullptr};

  void handle_message(std::vector<uint8_t> &message) override;
};

class DeltaSolCS2BSensor : public VBusListener, public Component {
 public:
  void dump_config() override;
  void set_s1_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s1_error_bsensor_ = bsensor; }
  void set_s2_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s2_error_bsensor_ = bsensor; }
  void set_s3_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s3_error_bsensor_ = bsensor; }
  void set_s4_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s4_error_bsensor_ = bsensor; }

 protected:
  binary_sensor::BinarySensor *s1_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s2_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s3_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s4_error_bsensor_{nullptr};

  void handle_message(std::vector<uint8_t> &message) override;
};

class DeltaSolCSPlusBSensor : public VBusListener, public Component {
 public:
  void dump_config() override;
  void set_s1_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s1_error_bsensor_ = bsensor; }
  void set_s2_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s2_error_bsensor_ = bsensor; }
  void set_s3_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s3_error_bsensor_ = bsensor; }
  void set_s4_error_bsensor(binary_sensor::BinarySensor *bsensor) { this->s4_error_bsensor_ = bsensor; }

 protected:
  binary_sensor::BinarySensor *s1_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s2_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s3_error_bsensor_{nullptr};
  binary_sensor::BinarySensor *s4_error_bsensor_{nullptr};

  void handle_message(std::vector<uint8_t> &message) override;
};

class VBusCustomSubBSensor;

class VBusCustomBSensor : public VBusListener, public Component {
 public:
  void dump_config() override;
  void set_bsensors(std::vector<VBusCustomSubBSensor *> bsensors) { this->bsensors_ = std::move(bsensors); };

 protected:
  std::vector<VBusCustomSubBSensor *> bsensors_;
  void handle_message(std::vector<uint8_t> &message) override;
};

class VBusCustomSubBSensor : public binary_sensor::BinarySensor, public Component {
 public:
  void set_message_parser(message_parser_t parser) { this->message_parser_ = std::move(parser); };
  void parse_message(std::vector<uint8_t> &message);

 protected:
  message_parser_t message_parser_;
};

}  // namespace vbus
}  // namespace esphome
