#pragma once
#include "esphome/core/defines.h"
#ifdef USE_MDNS
#include <array>
#include <string>
#include <vector>
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace mdns {

struct MDNSTXTRecord {
  std::string key;
  TemplatableValue<std::string> value;
};

struct MDNSService {
  // service name _including_ underscore character prefix
  // as defined in RFC6763 Section 7
  std::string service_type;
  // second label indicating protocol _including_ underscore character prefix
  // as defined in RFC6763 Section 7, like "_tcp" or "_udp"
  std::string proto;
  TemplatableValue<uint16_t> port;
  std::vector<MDNSTXTRecord> txt_records;
};

class MDNSComponent : public Component {
 public:
  void setup() override;
  void dump_config() override;

#if (defined(USE_ESP8266) || defined(USE_RP2040)) && defined(USE_ARDUINO)
  void loop() override;
#endif
  float get_setup_priority() const override { return setup_priority::AFTER_CONNECTION; }

#ifdef USE_MDNS_EXTRA_SERVICES
  void add_extra_service(MDNSService service) { services_extra_.push_back(std::move(service)); }
#endif

  const std::array<MDNSService, MDNS_SERVICE_COUNT> &get_services() const { return this->services_; }
  size_t get_service_count() const { return this->service_count_; }

  void on_shutdown() override;

 protected:
#ifdef USE_MDNS_EXTRA_SERVICES
  std::vector<MDNSService> services_extra_{};
#endif
  std::array<MDNSService, MDNS_SERVICE_COUNT> services_{};
  size_t service_count_{0};  // Track how many services are actually populated
  std::string hostname_;
  void compile_records_();
};

}  // namespace mdns
}  // namespace esphome
#endif
