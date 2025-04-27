#pragma once

namespace esphome {
namespace syslog {
class Syslog {
 public:
  void setup() override;
  void dump_config() override;
};
}  // namespace syslog
}  // namespace esphome
