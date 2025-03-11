#include "socket.h"
#include "esphome/core/defines.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

#ifdef USE_SOCKET_IMPL_ZEPHYR_SOCKETS

#include <errno.h>
#include <string.h>
#include <vector>

#include <zephyr/net/socket.h>
#include <zephyr/net/net_ip.h>

#ifdef USE_OPENTHREAD_ZEPHYR
#include <openthread/instance.h>
#include <openthread/netdata.h>
#include <openthread/border_router.h>
#include <openthread/ip6.h>
#include "esphome/components/openthread_zephyr/openthread.h"
extern otInstance *openthread_get_default_instance(void);
#endif

// Undefine macros to avoid conflicts with method names
#undef socket
#undef connect
#undef bind
#undef listen
#undef accept
#undef send
#undef recv
#undef sendto
#undef recvfrom
#undef getsockopt
#undef setsockopt
#undef getpeername
#undef getsockname
#undef close
#undef shutdown
#undef fcntl
#undef inet_ntop
#undef inet_pton

// Define missing constants if not provided by Zephyr
#ifndef F_GETFL
#define F_GETFL 3
#endif
#ifndef F_SETFL
#define F_SETFL 4
#endif
#ifndef O_NONBLOCK
#define O_NONBLOCK 1
#endif

namespace esphome {
namespace socket {

// Cache for the NAT64 prefix
static bool nat64_prefix_cached = false;
static uint8_t nat64_prefix_cache[12] = {0};

// Function to clear the NAT64 prefix cache
void clear_nat64_prefix_cache() {
  nat64_prefix_cached = false;
}

// Add Socket destructor implementation
Socket::~Socket() {}

std::string format_sockaddr(const struct sockaddr_storage &storage) {
  if (storage.ss_family == AF_INET) {
    const struct sockaddr_in *addr = reinterpret_cast<const struct sockaddr_in *>(&storage);
    char buf[INET_ADDRSTRLEN];
    if (zsock_inet_ntop(AF_INET, &addr->sin_addr, buf, sizeof(buf)) != nullptr)
      return std::string{buf};
  }
#if defined(CONFIG_NET_IPV6)
  else if (storage.ss_family == AF_INET6) {
    const struct sockaddr_in6 *addr = reinterpret_cast<const struct sockaddr_in6 *>(&storage);
    char buf[INET6_ADDRSTRLEN];
    if (zsock_inet_ntop(AF_INET6, &addr->sin6_addr, buf, sizeof(buf)) != nullptr)
      return std::string{buf};
  }
#endif
  return {};
}

class ZephyrSocketImpl : public Socket {
 public:
  ZephyrSocketImpl(int fd) : fd_(fd) {
    // Get the socket type
    int type;
    socklen_t len = sizeof(type);
    if (zsock_getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &len) == 0) {
      socket_type_ = type;
      ESP_LOGD("socket", "Socket fd=%d has type %d", fd_, socket_type_);
    } else {
      ESP_LOGW("socket", "Failed to get socket type for fd=%d, errno: %d (%s)", fd_, errno, strerror(errno));
    }
  }
  
  ~ZephyrSocketImpl() override {
    if (!closed_) {
      close();  // NOLINT(clang-analyzer-optin.cplusplus.VirtualCall)
    }
  }
  
  int connect(const struct sockaddr *addr, socklen_t addrlen) override { 
    ESP_LOGD("socket", "Connecting socket fd=%d (type=%d)", fd_, socket_type_);
    return zsock_connect(fd_, addr, addrlen); 
  }
  
  std::unique_ptr<Socket> accept(struct sockaddr *addr, socklen_t *addrlen) override {
    if (socket_type_ != SOCK_STREAM) {
      ESP_LOGE("socket", "Cannot accept on non-stream socket fd=%d (type=%d)", fd_, socket_type_);
      return nullptr;
    }
    
    int fd = zsock_accept(fd_, addr, addrlen);
    if (fd == -1)
      return {};
    return make_unique<ZephyrSocketImpl>(fd);
  }
  
  int bind(const struct sockaddr *addr, socklen_t addrlen) override { 
    ESP_LOGD("socket", "Binding socket fd=%d (type=%d)", fd_, socket_type_);
    return zsock_bind(fd_, addr, addrlen); 
  }
  
  int close() override {
    if (closed_)
      return 0;
    closed_ = true;
    return zsock_close(fd_);
  }
  
  int shutdown(int how) override { 
    if (socket_type_ != SOCK_STREAM) {
      ESP_LOGW("socket", "Shutdown on non-stream socket fd=%d (type=%d)", fd_, socket_type_);
    }
    return zsock_shutdown(fd_, how); 
  }

  int getpeername(struct sockaddr *addr, socklen_t *addrlen) override { return zsock_getpeername(fd_, addr, addrlen); }
  std::string getpeername() override {
    struct sockaddr_storage storage;
    socklen_t len = sizeof(storage);
    int err = this->getpeername((struct sockaddr *) &storage, &len);
    if (err != 0)
      return {};
    return format_sockaddr(storage);
  }
  int getsockname(struct sockaddr *addr, socklen_t *addrlen) override { return zsock_getsockname(fd_, addr, addrlen); }
  std::string getsockname() override {
    struct sockaddr_storage storage;
    socklen_t len = sizeof(storage);
    int err = this->getsockname((struct sockaddr *) &storage, &len);
    if (err != 0)
      return {};
    return format_sockaddr(storage);
  }
  int getsockopt(int level, int optname, void *optval, socklen_t *optlen) override {
    return zsock_getsockopt(fd_, level, optname, optval, optlen);
  }
  int setsockopt(int level, int optname, const void *optval, socklen_t optlen) override {
    return zsock_setsockopt(fd_, level, optname, optval, optlen);
  }
  int listen(int backlog) override { return zsock_listen(fd_, backlog); }
  ssize_t read(void *buf, size_t len) override { 
    if (socket_type_ == SOCK_STREAM) {
      return zsock_recv(fd_, buf, len, 0); 
    } else if (socket_type_ == SOCK_DGRAM) {
      struct sockaddr_storage from;
      socklen_t from_len = sizeof(from);
      return zsock_recvfrom(fd_, buf, len, 0, (struct sockaddr *)&from, &from_len);
    } else {
      ESP_LOGW("socket", "Read on socket fd=%d with unsupported type %d", fd_, socket_type_);
      return -1;
    }
  }
  ssize_t recvfrom(void *buf, size_t len, sockaddr *addr, socklen_t *addr_len) override {
    return zsock_recvfrom(fd_, buf, len, 0, addr, addr_len);
  }
  ssize_t readv(const struct iovec *iov, int iovcnt) override {
    // Zephyr doesn't have readv, so we need to implement it ourselves
    if (iovcnt <= 0)
      return 0;
    
    // Calculate total length
    size_t total_len = 0;
    for (int i = 0; i < iovcnt; i++) {
      total_len += iov[i].iov_len;
    }
    
    if (total_len == 0)
      return 0;
    
    // Create a temporary buffer
    std::vector<uint8_t> temp_buffer(total_len);
    
    // Read into the temporary buffer
    ssize_t ret = this->read(temp_buffer.data(), total_len);
    if (ret <= 0)
      return ret;
    
    // Copy data to the iovec buffers
    size_t copied = 0;
    for (int i = 0; i < iovcnt && copied < static_cast<size_t>(ret); i++) {
      size_t to_copy = std::min(iov[i].iov_len, static_cast<size_t>(ret) - copied);
      memcpy(iov[i].iov_base, temp_buffer.data() + copied, to_copy);
      copied += to_copy;
    }
    
    return ret;
  }
  ssize_t write(const void *buf, size_t len) override { 
    if (socket_type_ == SOCK_STREAM) {
      return zsock_send(fd_, buf, len, 0); 
    } else if (socket_type_ == SOCK_DGRAM) {
      // For datagram sockets, we need a destination address
      ESP_LOGW("socket", "Write on datagram socket fd=%d without destination address", fd_);
      return -1;
    } else {
      ESP_LOGW("socket", "Write on socket fd=%d with unsupported type %d", fd_, socket_type_);
      return -1;
    }
  }
  ssize_t writev(const struct iovec *iov, int iovcnt) override {
    // Similar to readv, implement using multiple sends or a buffer
    if (iovcnt == 1) {
      return this->write(iov[0].iov_base, iov[0].iov_len);
    }
    
    // For multiple buffers, we'll need to copy to a temporary buffer and then send
    size_t total_len = 0;
    for (int i = 0; i < iovcnt; i++) {
      total_len += iov[i].iov_len;
    }
    
    std::vector<uint8_t> temp_buffer(total_len);
    size_t offset = 0;
    for (int i = 0; i < iovcnt; i++) {
      memcpy(temp_buffer.data() + offset, iov[i].iov_base, iov[i].iov_len);
      offset += iov[i].iov_len;
    }
    
    return this->write(temp_buffer.data(), total_len);
  }

  ssize_t sendto(const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen) override {
    ESP_LOGD("socket", "Sending to socket fd=%d (type=%d)", fd_, socket_type_);
    return zsock_sendto(fd_, buf, len, flags, to, tolen);
  }

  int setblocking(bool blocking) override {
    int flags = zsock_fcntl(fd_, F_GETFL, 0);
    if (blocking) {
      flags &= ~O_NONBLOCK;
    } else {
      flags |= O_NONBLOCK;
    }
    return zsock_fcntl(fd_, F_SETFL, flags);
  }

 protected:
  int fd_;
  bool closed_ = false;
  int socket_type_ = SOCK_STREAM;
};

std::unique_ptr<Socket> socket(int domain, int type, int protocol) {
  int ret = zsock_socket(domain, type, protocol);
  if (ret == -1)
    return nullptr;
  return std::unique_ptr<Socket>{new ZephyrSocketImpl(ret)};
}

// Implement socket_ip for Zephyr
std::unique_ptr<Socket> socket_ip(int type, int protocol) {
  std::unique_ptr<Socket> ret = nullptr;
  int sock_fd = -1;
  
#if defined(CONFIG_NET_IPV6)
  // Always try IPv6 first for Thread
  ESP_LOGD("socket", "Creating IPv6 socket for OpenThread...");
  sock_fd = zsock_socket(AF_INET6, type, protocol);
  if (sock_fd >= 0) {
    ESP_LOGD("socket", "Successfully created IPv6 socket: fd=%d", sock_fd);
    
    // Set IPV6_V6ONLY to 0 to allow IPv4-mapped IPv6 addresses
    int off = 0;
    if (zsock_setsockopt(sock_fd, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(off)) < 0) {
      ESP_LOGW("socket", "Failed to set IPV6_V6ONLY=0, errno: %d (%s)", errno, strerror(errno));
      // Continue anyway, as this is not critical
    } else {
      ESP_LOGD("socket", "Set IPV6_V6ONLY=0 to allow IPv4-mapped addresses");
    }
    
    return std::unique_ptr<Socket>{new ZephyrSocketImpl(sock_fd)};
  }
  ESP_LOGW("socket", "Failed to create IPv6 socket, errno: %d (%s)", errno, strerror(errno));
#endif

#if defined(CONFIG_NET_IPV4)
  // Only try IPv4 if IPv6 failed and IPv4 is enabled
  ESP_LOGD("socket", "Trying to create IPv4 socket...");
  sock_fd = zsock_socket(AF_INET, type, protocol);
  if (sock_fd >= 0) {
    ESP_LOGD("socket", "Successfully created IPv4 socket: fd=%d", sock_fd);
    return std::unique_ptr<Socket>{new ZephyrSocketImpl(sock_fd)};
  }
  ESP_LOGW("socket", "Failed to create IPv4 socket, errno: %d (%s)", errno, strerror(errno));
#endif

  ESP_LOGE("socket", "Failed to create any socket");
  return nullptr;
}

// Get NAT64 prefix from OpenThread network data
bool get_nat64_prefix(uint8_t *prefix, size_t prefix_len) {
#ifdef USE_OPENTHREAD_ZEPHYR
  if (prefix_len < 12) {
    ESP_LOGE("socket", "Buffer too small for NAT64 prefix");
    return false;
  }

  // If we have a cached prefix, use it
  if (nat64_prefix_cached) {
    memcpy(prefix, nat64_prefix_cache, 12);
    return true;
  }

  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE("socket", "OpenThread instance not available");
    return false;
  }

  // Get network data
  otNetworkDataIterator iterator = OT_NETWORK_DATA_ITERATOR_INIT;
  otExternalRouteConfig config;
  bool found_nat64 = false;

  // Look for the NAT64 prefix in the network data
  // NAT64 prefixes typically have a /96 prefix length
  while (otNetDataGetNextRoute(instance, &iterator, &config) == OT_ERROR_NONE) {
    char buf[OT_IP6_PREFIX_STRING_SIZE];
    otIp6PrefixToString(&config.mPrefix, buf, sizeof(buf));
    
    // Check if this is a NAT64 prefix (typically /96)
    if (config.mPrefix.mLength == 96) {
      // Copy the prefix bytes (12 bytes for a /96 prefix)
      memcpy(prefix, config.mPrefix.mPrefix.mFields.m8, 12);
      
      ESP_LOGD("socket", "Found NAT64 prefix: %s", buf);
      found_nat64 = true;
      break;
    }
  }

  // If we didn't find a /96 route, try again looking for a route with "ffff:0:0::/96" in the name
  // This is a common pattern for NAT64 prefixes
  if (!found_nat64) {
    iterator = OT_NETWORK_DATA_ITERATOR_INIT;
    while (otNetDataGetNextRoute(instance, &iterator, &config) == OT_ERROR_NONE) {
      char buf[OT_IP6_PREFIX_STRING_SIZE];
      otIp6PrefixToString(&config.mPrefix, buf, sizeof(buf));
      
      // Look for "ffff:0:0::" pattern in the prefix string which is common for NAT64
      if (strstr(buf, "ffff:0:0::") != nullptr || strstr(buf, "ffff::") != nullptr) {
        // Copy the prefix bytes (12 bytes for a /96 prefix)
        memcpy(prefix, config.mPrefix.mPrefix.mFields.m8, 12);
        
        ESP_LOGD("socket", "Found NAT64 prefix by pattern matching: %s", buf);
        found_nat64 = true;
        break;
      }
    }
  }

  if (found_nat64) {
    // Cache the prefix for future use
    memcpy(nat64_prefix_cache, prefix, 12);
    nat64_prefix_cached = true;
  } else {
    ESP_LOGW("socket", "NAT64 prefix not found in network data, using default");
    return false;
  }

  return found_nat64;
#else
  ESP_LOGW("socket", "OpenThread not available, cannot get NAT64 prefix");
  return false;
#endif
}

// Add NAT64 translation function for OpenThread
socklen_t set_sockaddr_nat64(struct sockaddr *addr, socklen_t addrlen, const std::string &ipv4_address, uint16_t port) {
  if (addrlen < sizeof(struct sockaddr_in6)) {
    ESP_LOGE("socket", "Buffer too small for IPv6 address: %u < %u", addrlen, sizeof(struct sockaddr_in6));
    return 0;
  }

  // IPv4 address that needs NAT64 translation
  struct sockaddr_in6 *addr_in6 = reinterpret_cast<struct sockaddr_in6 *>(addr);
  memset(addr_in6, 0, sizeof(*addr_in6));
  addr_in6->sin6_family = AF_INET6;
  addr_in6->sin6_port = htons(port);
  
  // Parse the IPv4 address
  struct in_addr ipv4_addr;
  if (zsock_inet_pton(AF_INET, ipv4_address.c_str(), &ipv4_addr) != 1) {
    ESP_LOGE("socket", "Failed to parse IPv4 address: %s", ipv4_address.c_str());
    return 0;
  }
  
  // Convert IPv4 address to OpenThread NAT64 format
  uint8_t *ipv6_addr = reinterpret_cast<uint8_t *>(&addr_in6->sin6_addr);
  
  // Try to get the NAT64 prefix from OpenThread network data
  bool prefix_found = get_nat64_prefix(ipv6_addr, 12);
  
  if (!prefix_found) {
    // If no NAT64 prefix is found, return an error
    ESP_LOGE("socket", "No NAT64 prefix found in network data, cannot translate IPv4 address: %s", ipv4_address.c_str());
    return 0;
  }
  
  // Convert IPv4 address to the format used by OpenThread
  // Example: 10.0.1.195 -> a00:1c3
  uint32_t ipv4_value = ntohl(ipv4_addr.s_addr);
  
  // Extract the bytes from the IPv4 address
  uint8_t b1 = (ipv4_value >> 24) & 0xff;  // 10
  uint8_t b2 = (ipv4_value >> 16) & 0xff;  // 0
  uint8_t b3 = (ipv4_value >> 8) & 0xff;   // 1
  uint8_t b4 = ipv4_value & 0xff;          // 195
  
  // Format according to OpenThread NAT64: prefix::a00:1c3
  ipv6_addr[12] = b1;  // 10 -> 0x0a
  ipv6_addr[13] = b2;  // 0 -> 0x00
  ipv6_addr[14] = b3;  // 1 -> 0x01
  ipv6_addr[15] = b4;  // 195 -> 0xc3
  
  // Print the NAT64 translated address for debugging
  char buf[INET6_ADDRSTRLEN];
  if (zsock_inet_ntop(AF_INET6, &addr_in6->sin6_addr, buf, sizeof(buf)) != nullptr) {
    ESP_LOGD("socket", "OpenThread NAT64 translated address: %s:%u", buf, port);
  } else {
    ESP_LOGW("socket", "Failed to convert NAT64 address to string");
  }
  
  return sizeof(struct sockaddr_in6);
}

// Update the set_sockaddr function to use NAT64 for IPv4 addresses when using IPv6 sockets
socklen_t set_sockaddr(struct sockaddr *addr, socklen_t addrlen, const std::string &ip_address, uint16_t port) {
  // Check if this is an IPv6 address (contains ':')
  bool is_ipv6 = ip_address.find(':') != std::string::npos;

  if (is_ipv6) {
    // Handle IPv6 address
    // ... existing IPv6 code ...
    if (addrlen < sizeof(struct sockaddr_in6)) {
      ESP_LOGE("socket", "Buffer too small for IPv6 address: %u < %u", addrlen, sizeof(struct sockaddr_in6));
      return 0;
    }

    struct sockaddr_in6 *addr_in6 = reinterpret_cast<struct sockaddr_in6 *>(addr);
    memset(addr_in6, 0, sizeof(*addr_in6));
    addr_in6->sin6_family = AF_INET6;
    addr_in6->sin6_port = htons(port);

    // Convert string to IPv6 address
    if (zsock_inet_pton(AF_INET6, ip_address.c_str(), &addr_in6->sin6_addr) != 1) {
      ESP_LOGE("socket", "Failed to parse IPv6 address: %s", ip_address.c_str());
      return 0;
    }

    ESP_LOGD("socket", "Successfully converted IPv6 address: %s", ip_address.c_str());
    return sizeof(struct sockaddr_in6);
  } else {
    // Check if we're using an IPv6 socket with an IPv4 address
    // This is determined by checking if the address family is already set to AF_INET6
    if (addr->sa_family == AF_INET6) {
      // Use NAT64 translation for IPv4 address with IPv6 socket
      ESP_LOGD("socket", "Using NAT64 translation for IPv4 address: %s", ip_address.c_str());
      return set_sockaddr_nat64(addr, addrlen, ip_address, port);
    }

    // Handle IPv4 address normally
    // ... existing IPv4 code ...
    if (addrlen < sizeof(struct sockaddr_in)) {
      ESP_LOGE("socket", "Buffer too small for IPv4 address: %u < %u", addrlen, sizeof(struct sockaddr_in));
      return 0;
    }

    struct sockaddr_in *addr_in = reinterpret_cast<struct sockaddr_in *>(addr);
    memset(addr_in, 0, sizeof(*addr_in));
    addr_in->sin_family = AF_INET;
    addr_in->sin_port = htons(port);

    // Convert string to IPv4 address
    if (zsock_inet_pton(AF_INET, ip_address.c_str(), &addr_in->sin_addr) != 1) {
      ESP_LOGE("socket", "Failed to parse IPv4 address: %s", ip_address.c_str());
      return 0;
    }

    ESP_LOGD("socket", "Successfully converted IPv4 address: %s", ip_address.c_str());
    return sizeof(struct sockaddr_in);
  }
}

// Implement set_sockaddr_any for Zephyr
socklen_t set_sockaddr_any(struct sockaddr *addr, socklen_t addrlen, uint16_t port) {
  struct sockaddr_in *addr_in = reinterpret_cast<struct sockaddr_in *>(addr);
  memset(addr_in, 0, sizeof(*addr_in));
  addr_in->sin_family = AF_INET;
  addr_in->sin_port = htons(port);
  addr_in->sin_addr.s_addr = INADDR_ANY;
  return sizeof(*addr_in);
}

}  // namespace socket
}  // namespace esphome

#endif  // USE_SOCKET_IMPL_ZEPHYR_SOCKETS 