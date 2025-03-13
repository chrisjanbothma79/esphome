#pragma once

#include "esphome/core/defines.h"

#ifdef USE_ZEPHYR

// Include Zephyr-specific headers
#include <zephyr/kernel.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/net_ip.h>

// Define platform-specific macros and functions for the API component
namespace esphome {
namespace api {

// Helper function to check if network is connected
inline bool is_network_connected() {
  struct net_if *iface = net_if_get_default();
  return iface != nullptr && net_if_is_up(iface);
}

// Helper function to get IP address as string
inline std::string get_ip_address() {
  struct net_if *iface = net_if_get_default();
  if (iface == nullptr)
    return "";

  char buf[NET_IPV4_ADDR_LEN];

  // Get the first IPv4 address
  for (int i = 0; i < NET_IF_MAX_IPV4_ADDR; i++) {
    struct net_if_ipv4 *ipv4 = iface->config.ip.ipv4;
    if (ipv4 && ipv4->unicast[i].is_used) {
      net_addr_ntop(AF_INET, &ipv4->unicast[i].address.in_addr, buf, sizeof(buf));
      return std::string(buf);
    }
  }

  return "";
}

}  // namespace api
}  // namespace esphome

#endif  // USE_ZEPHYR