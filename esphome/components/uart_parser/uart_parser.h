#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace uart_parser {

class UartParser : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace empty_component
}  // namespace esphome