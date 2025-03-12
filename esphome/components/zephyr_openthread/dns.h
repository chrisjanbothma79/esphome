#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"

#include <openthread/instance.h>
#include <openthread/message.h>
#include <openthread/platform/dns.h>
#include <openthread/ip6.h>
#include <zephyr/net/socket.h>

namespace esphome {
namespace zephyr_openthread {

// Public DNS resolver functions
bool init_dns_resolver();
bool resolve_hostname(const std::string &hostname, struct sockaddr_storage *result, uint16_t port);
void clear_dns_cache();

class OpenThreadDNSComponent : public Component {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
};

// Global component instance
extern OpenThreadDNSComponent *global_openthread_dns_component;

}  // namespace zephyr_openthread
}  // namespace esphome
