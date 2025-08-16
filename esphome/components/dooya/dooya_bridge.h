#pragma once

#include <cinttypes>

#include "esphome/core/component.h"
#include "esphome/core/defines.h"

#include "esphome/components/uart/uart.h"

namespace esphome {
namespace dooya {

class DooyaComponent;

class DooyaBridge : public Component, public uart::UARTDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  float get_setup_priority() const override { return setup_priority::BLUETOOTH; }

  bool is_setup_done() { return this->setup_.is_done; };

  void register_subcomponent(DooyaComponent *component) { this->subcomponents_.push_back(component); }

  bool start_pairing();

 protected:
  void parse_packet_();

  std::string rx_buf_;
  std::string address_;
  std::vector<std::string> paired_addresses_;
  std::vector<DooyaComponent *> subcomponents_;
  struct {
    bool in_progress{false};
    uint32_t start;
    bool req_sent{false};
  } pairing_;
  struct {
    bool is_done{false};
    uint32_t start_time;
  } setup_;
};

}  // namespace dooya
}  // namespace esphome
