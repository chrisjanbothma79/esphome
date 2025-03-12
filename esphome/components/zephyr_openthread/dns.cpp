#include "dns.h"
#include "esphome/core/log.h"

#include <errno.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/dns_resolve.h>

// OpenThread DNS client includes
#include <openthread/dns_client.h>
#include <openthread/error.h>
#include <openthread/instance.h>

// Include OpenThread Zephyr component to access the OpenThread instance
#include "openthread.h"

// Forward declaration for OpenThread instance getter
extern "C" otInstance *openthread_get_default_instance(void);

namespace esphome {
namespace zephyr_openthread {

static const char *const TAG = "openthread_dns";

// Global component instance
OpenThreadDNSComponent *global_openthread_dns_component = nullptr;

// Structure to hold DNS resolution result
struct DnsResolutionContext {
  bool completed;
  bool success;
  otIp6Address ipv6_address;
  struct k_sem *sem;
};

// DNS resolution callback function
static void dns_resolution_callback(otError error, const otDnsAddressResponse *response, void *context) {
  auto *result = static_cast<DnsResolutionContext *>(context);

  if (error != OT_ERROR_NONE) {
    ESP_LOGW(TAG, "DNS resolution failed: %d", error);
    result->success = false;
    result->completed = true;
    k_sem_give(result->sem);
    return;
  }

  // Get the IPv6 address from the response
  uint32_t ttl;
  otError addr_error = otDnsAddressResponseGetAddress(response, 0, &result->ipv6_address, &ttl);

  if (addr_error == OT_ERROR_NONE) {
    result->success = true;

    // Log the resolved address
    char addr_str[INET6_ADDRSTRLEN];
    struct in6_addr ipv6_addr;
    memcpy(&ipv6_addr, &result->ipv6_address, sizeof(otIp6Address));
    inet_ntop(AF_INET6, &ipv6_addr, addr_str, sizeof(addr_str));
    ESP_LOGD(TAG, "DNS resolved successfully to IPv6 address: %s, TTL: %d", addr_str, ttl);
  } else {
    ESP_LOGE(TAG, "Failed to get IPv6 address from DNS response: %d", addr_error);
    result->success = false;
  }

  result->completed = true;
  k_sem_give(result->sem);
}

void OpenThreadDNSComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up OpenThread DNS resolver...");
  global_openthread_dns_component = this;

  if (init_dns_resolver()) {
    ESP_LOGI(TAG, "OpenThread DNS resolver initialized successfully");
  } else {
    ESP_LOGE(TAG, "Failed to initialize OpenThread DNS resolver");
    this->mark_failed();
  }
}

void OpenThreadDNSComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "OpenThread DNS:");
  ESP_LOGCONFIG(TAG, "  DNS Resolver: %s", init_dns_resolver() ? "Initialized" : "Not initialized");
}

// Initialize DNS resolver
bool init_dns_resolver() {
  // Check if OpenThread is available
  if (global_openthread_component == nullptr) {
    ESP_LOGE(TAG, "OpenThread component not available");
    return false;
  }

  // Check if OpenThread is connected
  if (!global_openthread_component->is_connected()) {
    ESP_LOGW(TAG, "OpenThread is not connected");
    return false;
  }

  ESP_LOGD(TAG, "OpenThread DNS resolver initialized successfully");
  return true;
}

// Clear DNS cache
void clear_dns_cache() { ESP_LOGD(TAG, "OpenThread DNS cache clearing not supported"); }

// Resolve hostname to IP address using OpenThread DNS client
bool resolve_hostname(const std::string &hostname, struct sockaddr_storage *result, uint16_t port) {
  if (hostname.empty()) {
    ESP_LOGE(TAG, "Empty hostname provided");
    return false;
  }

  // Check if OpenThread is available and connected
  if (global_openthread_component == nullptr || !global_openthread_component->is_connected()) {
    ESP_LOGE(TAG, "OpenThread not available or not connected");
    return false;
  }

  // Get OpenThread instance
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "Failed to get OpenThread instance");
    return false;
  }

  ESP_LOGD(TAG, "Resolving hostname using OpenThread DNS client: %s", hostname.c_str());

  // Create a semaphore to wait for DNS resolution
  struct k_sem dns_sem;
  k_sem_init(&dns_sem, 0, 1);

  // Create a structure to hold the result
  DnsResolutionContext dns_result = {.completed = false, .success = false, .ipv6_address = {}, .sem = &dns_sem};

  // Create a DNS query config
  otDnsQueryConfig config;
  memset(&config, 0, sizeof(config));
  config.mResponseTimeout = 5000;  // 5 seconds timeout

  // First try IPv4 resolution (which will return IPv6 addresses via NAT64)
  ESP_LOGD(TAG, "Resolving %s using IPv4 resolution (NAT64)", hostname.c_str());
  otError error =
      otDnsClientResolveIp4Address(instance, hostname.c_str(), dns_resolution_callback, &dns_result, &config);

  if (error != OT_ERROR_NONE) {
    ESP_LOGW(TAG, "Failed to start IPv4 DNS query: %d", error);

    // Fall back to IPv6 resolution
    ESP_LOGD(TAG, "Falling back to IPv6 resolution for %s", hostname.c_str());
    error = otDnsClientResolveAddress(instance, hostname.c_str(), dns_resolution_callback, &dns_result, &config);

    if (error != OT_ERROR_NONE) {
      ESP_LOGE(TAG, "Failed to start IPv6 DNS query: %d", error);
      return false;
    }
  }

  // Wait for the DNS resolution to complete (with timeout)
  if (k_sem_take(&dns_sem, K_MSEC(6000)) != 0) {  // 6 seconds timeout (slightly longer than DNS timeout)
    ESP_LOGE(TAG, "DNS resolution timed out");
    return false;
  }

  // Check if the DNS resolution was successful
  if (!dns_result.success) {
    ESP_LOGE(TAG, "DNS resolution failed for %s", hostname.c_str());
    return false;
  }

  // DNS resolution was successful, convert the result to sockaddr_in6
  struct sockaddr_in6 *addr6 = reinterpret_cast<struct sockaddr_in6 *>(result);
  memset(addr6, 0, sizeof(*addr6));
  addr6->sin6_family = AF_INET6;
  addr6->sin6_port = htons(port);
  memcpy(&addr6->sin6_addr, &dns_result.ipv6_address, sizeof(otIp6Address));

  // Log the resolved address
  char addr_str[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, &addr6->sin6_addr, addr_str, sizeof(addr_str));
  ESP_LOGD(TAG, "Resolved %s to IPv6 address: %s", hostname.c_str(), addr_str);

  return true;
}

}  // namespace zephyr_openthread
}  // namespace esphome