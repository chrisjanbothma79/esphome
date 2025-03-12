#include "esphome/core/defines.h"
#include "openthread.h"

#if defined(USE_ZEPHYR) && defined(USE_ZEPHYR_OPENTHREAD)

#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "esphome/core/application.h"

#include <zephyr/kernel.h>
#include <zephyr/net/openthread.h>
#include <zephyr/net/net_if.h>
#include <zephyr/net/net_l2.h>
#include <openthread/thread.h>
#include <openthread/ip6.h>
#include <openthread/dataset.h>
#include <openthread/platform/radio.h>
#include <openthread/srp_client.h>
#include <openthread/dataset_ftd.h>
#include <openthread/netdata.h>
#include "esphome/components/socket/socket.h"

namespace esphome {
namespace zephyr_openthread {

static const char *const TAG = "zephyr_openthread";

// Add a global variable for the OpenThreadZephyr component
OpenThreadZephyr *global_openthread_component = nullptr;

void OpenThreadZephyr::setup() {
  ESP_LOGCONFIG(TAG, "Setting up OpenThread Zephyr...");

  // Set the global variable
  global_openthread_component = this;

  // Initialize OpenThread stack
  int ret = openthread_start(openthread_get_default_context());
  if (ret != 0) {
    ESP_LOGE(TAG, "Failed to initialize OpenThread stack: %d", ret);
    this->mark_failed();
    return;
  }

  // Configure operational dataset if needed
  if (this->force_dataset_) {
    this->configure_operational_dataset();
  }

  // Start OpenThread network
  this->start_thread_network();

  // Enable SRP client auto-start
  otInstance *instance = openthread_get_default_instance();
  if (instance != nullptr) {
    // Setup SRP services using mDNS component
    this->setup_srp_services();

    ESP_LOGI(TAG, "SRP services registered");
  } else {
    ESP_LOGE(TAG, "OpenThread instance not available, SRP services not registered");
  }
}

void OpenThreadZephyr::loop() {
  // Add debug logging
  static uint32_t last_debug_log = 0;
  if (millis() - last_debug_log > 5000) {  // Log every 5 seconds
    last_debug_log = millis();
  }

  if (!this->thread_started_)
    return;

  // Check connection status
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGW(TAG, "OpenThread instance not available");
    return;
  }

  uint8_t role = otThreadGetDeviceRole(instance);
  bool is_connected = role >= OT_DEVICE_ROLE_CHILD;

  if (role != this->thread_role_) {
    this->thread_role_ = role;
    const char *role_str = "Unknown";
    switch (role) {
      case OT_DEVICE_ROLE_DISABLED:
        role_str = "Disabled";
        break;
      case OT_DEVICE_ROLE_DETACHED:
        role_str = "Detached";
        break;
      case OT_DEVICE_ROLE_CHILD:
        role_str = "Child";
        break;
      case OT_DEVICE_ROLE_ROUTER:
        role_str = "Router";
        break;
      case OT_DEVICE_ROLE_LEADER:
        role_str = "Leader";
        break;
    }
    ESP_LOGI(TAG, "Thread role changed to: %s", role_str);
  }

  if (is_connected != this->connected_) {
    this->connected_ = is_connected;
    if (this->connected_) {
      ESP_LOGI(TAG, "Connected to Thread network");

      // Update IPv6 addresses
      this->update_ipv6_addresses();

      // Note: SRP entries will be automatically updated when Off-Mesh-Routable prefix changes
      // due to otSrpClientEnableAutoHostAddress being enabled in setup_srp_services()
    } else {
      ESP_LOGW(TAG, "Disconnected from Thread network");
      this->has_ipv6_address_ = false;
      this->ipv6_address_ = "";
    }
  }

  // Periodically update IPv6 addresses when connected
  static uint32_t last_ipv6_update = 0;
  if (this->connected_ && (millis() - last_ipv6_update > 30000)) {  // Every 30 seconds
    this->update_ipv6_addresses();
    last_ipv6_update = millis();
  }
}

void OpenThreadZephyr::dump_config() {
  ESP_LOGCONFIG(TAG, "OpenThread Zephyr:");
  ESP_LOGCONFIG(TAG, "  Channel: %u", this->channel_);
  ESP_LOGCONFIG(TAG, "  PAN ID: 0x%04X", this->panid_);
  ESP_LOGCONFIG(TAG, "  Network Name: %s", this->network_name_.c_str());
  ESP_LOGCONFIG(TAG, "  Extended PAN ID: %s", this->xpanid_.c_str());
  ESP_LOGCONFIG(TAG, "  Radio TX Power: %d dBm", this->radio_tx_power_);
  ESP_LOGCONFIG(TAG, "  Force Dataset: %s", YESNO(this->force_dataset_));
  ESP_LOGCONFIG(TAG, "  Connected: %s", YESNO(this->connected_));

  if (this->has_ipv6_address_) {
    ESP_LOGCONFIG(TAG, "  IPv6 Address: %s", this->ipv6_address_.c_str());
  }
}

void OpenThreadZephyr::configure_operational_dataset() {
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "OpenThread instance not available");
    return;
  }

  otOperationalDataset dataset;
  memset(&dataset, 0, sizeof(dataset));

  // Set active timestamp
  dataset.mActiveTimestamp.mSeconds = 1;
  dataset.mActiveTimestamp.mTicks = 0;
  dataset.mActiveTimestamp.mAuthoritative = false;
  dataset.mComponents.mIsActiveTimestampPresent = true;

  // Set channel
  dataset.mChannel = this->channel_;
  dataset.mComponents.mIsChannelPresent = true;

  // Set PAN ID
  dataset.mPanId = this->panid_;
  dataset.mComponents.mIsPanIdPresent = true;

  // Set Extended PAN ID - Fixed implementation
  const char *xpanid_str = this->xpanid_.c_str();
  for (size_t i = 0; i < sizeof(dataset.mExtendedPanId.m8); i++) {
    char hex[3] = {xpanid_str[i * 2], xpanid_str[i * 2 + 1], 0};
    dataset.mExtendedPanId.m8[i] = strtoul(hex, nullptr, 16);
  }
  dataset.mComponents.mIsExtendedPanIdPresent = true;

  // Set network key - Fixed implementation
  const char *key_str = this->network_key_.c_str();
  for (size_t i = 0; i < sizeof(dataset.mNetworkKey.m8); i++) {
    char hex[3] = {key_str[i * 2], key_str[i * 2 + 1], 0};
    dataset.mNetworkKey.m8[i] = strtoul(hex, nullptr, 16);
  }
  dataset.mComponents.mIsNetworkKeyPresent = true;

  // Set network name
  strncpy(dataset.mNetworkName.m8, this->network_name_.c_str(), sizeof(dataset.mNetworkName.m8) - 1);
  dataset.mComponents.mIsNetworkNamePresent = true;

  // Set PSKC - Fixed implementation
  const char *pskc_str = this->pskc_.c_str();
  for (size_t i = 0; i < sizeof(dataset.mPskc.m8); i++) {
    char hex[3] = {pskc_str[i * 2], pskc_str[i * 2 + 1], 0};
    dataset.mPskc.m8[i] = strtoul(hex, nullptr, 16);
  }
  dataset.mComponents.mIsPskcPresent = true;

  // Set the operational dataset
  otError error = otDatasetSetActive(instance, &dataset);
  if (error != OT_ERROR_NONE) {
    ESP_LOGE(TAG, "Failed to set operational dataset: %d", error);
  } else {
    ESP_LOGI(TAG, "Successfully set operational dataset");
  }
}

void OpenThreadZephyr::start_thread_network() {
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "OpenThread instance not available");
    return;
  }

  if (!this->force_dataset_) {
    // Set extended PAN ID - Fixed implementation
    otExtendedPanId xpanid;
    const char *xpanid_str = this->xpanid_.c_str();
    for (size_t i = 0; i < sizeof(xpanid.m8); i++) {
      char hex[3] = {xpanid_str[i * 2], xpanid_str[i * 2 + 1], 0};
      xpanid.m8[i] = strtoul(hex, nullptr, 16);
    }
    otError error = otThreadSetExtendedPanId(instance, &xpanid);
    if (error != OT_ERROR_NONE) {
      ESP_LOGE(TAG, "Failed to set extended PAN ID: %d", error);
    }

    // Set network key - Fixed implementation
    otNetworkKey network_key;
    const char *key_str = this->network_key_.c_str();
    for (size_t i = 0; i < sizeof(network_key.m8); i++) {
      char hex[3] = {key_str[i * 2], key_str[i * 2 + 1], 0};
      network_key.m8[i] = strtoul(hex, nullptr, 16);
    }
    error = otThreadSetNetworkKey(instance, &network_key);
    if (error != OT_ERROR_NONE) {
      ESP_LOGE(TAG, "Failed to set network key: %d", error);
    }

    // Set channel
    error = otLinkSetChannel(instance, this->channel_);
    if (error != OT_ERROR_NONE) {
      ESP_LOGE(TAG, "Failed to set channel: %d", error);
    }

    // Set PAN ID
    error = otLinkSetPanId(instance, this->panid_);
    if (error != OT_ERROR_NONE) {
      ESP_LOGE(TAG, "Failed to set PAN ID: %d", error);
    }

    // Set network name
    error = otThreadSetNetworkName(instance, this->network_name_.c_str());
    if (error != OT_ERROR_NONE) {
      ESP_LOGE(TAG, "Failed to set network name: %d", error);
    }
  }

  // Set radio TX power
  otPlatRadioSetTransmitPower(instance, this->radio_tx_power_);

  // Enable Thread
  otError error = otThreadSetEnabled(instance, true);
  if (error != OT_ERROR_NONE) {
    ESP_LOGE(TAG, "Failed to enable Thread: %d", error);
    return;
  }

  ESP_LOGI(TAG, "Started Thread network");
  this->thread_started_ = true;
}

void OpenThreadZephyr::stop_thread_network() {
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "OpenThread instance not available");
    return;
  }

  otError error = otThreadSetEnabled(instance, false);
  if (error != OT_ERROR_NONE) {
    ESP_LOGE(TAG, "Failed to disable Thread: %d", error);
    return;
  }

  ESP_LOGI(TAG, "Stopped Thread network");
  this->thread_started_ = false;
  this->connected_ = false;
  this->has_ipv6_address_ = false;
  this->ipv6_address_ = "";
}

void OpenThreadZephyr::update_ipv6_addresses() {
  ESP_LOGD(TAG, "Updating IPv6 addresses...");

  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGW(TAG, "OpenThread instance not available");
    return;
  }

  // Get unicast addresses
  const otNetifAddress *unicast_addrs = otIp6GetUnicastAddresses(instance);
  bool found_mesh_local = false;
  bool found_global = false;
  std::string mesh_local_addr;
  std::string global_addr;
  bool found_omr_prefix = false;

  ESP_LOGD(TAG, "Scanning IPv6 addresses:");
  int addr_count = 0;

  for (const otNetifAddress *addr = unicast_addrs; addr; addr = addr->mNext) {
    addr_count++;
    char addr_str[OT_IP6_ADDRESS_STRING_SIZE];
    otIp6AddressToString(&addr->mAddress, addr_str, sizeof(addr_str));

    // Log all addresses
    ESP_LOGD(TAG, "  Address %d: %s/%d", addr_count, addr_str, addr->mPrefixLength);

    // Check if mesh-local address (fd prefix)
    if (addr->mAddress.mFields.m8[0] == 0xfd) {
      found_mesh_local = true;
      mesh_local_addr = addr_str;
      ESP_LOGD(TAG, "  -> Mesh-local IPv6 Address: %s", addr_str);
    }
    // Check if global address (2xxx or 3xxx prefix)
    else if ((addr->mAddress.mFields.m8[0] == 0x20 || addr->mAddress.mFields.m8[0] == 0x30) &&
             addr->mPrefixLength == 64) {
      found_global = true;
      global_addr = addr_str;
      ESP_LOGD(TAG, "  -> Global IPv6 Address: %s", addr_str);
      found_omr_prefix = true;
      ESP_LOGD(TAG, "  -> Off-Mesh-Routable (OMR) prefix detected: %s/%d", addr_str, addr->mPrefixLength);
    }
    // Check if link-local address (fe80 prefix)
    else if (addr->mAddress.mFields.m8[0] == 0xfe && addr->mAddress.mFields.m8[1] == 0x80) {
      ESP_LOGD(TAG, "  -> Link-local IPv6 Address: %s", addr_str);
      // If we don't have a better address, use link-local as fallback
      if (!found_mesh_local && !found_global) {
        mesh_local_addr = addr_str;
      }
    }
  }

  if (addr_count == 0) {
    ESP_LOGD(TAG, "  No IPv6 addresses found");
  }

  // Update IPv6 address status
  bool had_ipv6 = this->has_ipv6_address_;
  this->has_ipv6_address_ = found_mesh_local || found_global;

  // Prefer global address, fall back to mesh-local
  if (found_global) {
    this->ipv6_address_ = global_addr;
    ESP_LOGI(TAG, "Using global IPv6 address: %s", global_addr.c_str());
  } else if (found_mesh_local) {
    this->ipv6_address_ = mesh_local_addr;
    ESP_LOGI(TAG, "Using mesh-local IPv6 address: %s", mesh_local_addr.c_str());
  }

  // Log if IPv6 status changed
  if (had_ipv6 != this->has_ipv6_address_) {
    if (this->has_ipv6_address_) {
      ESP_LOGI(TAG, "IPv6 address acquired: %s", this->ipv6_address_.c_str());

      ESP_LOGD(TAG, "Thread network interface initialized");

      // If we have an OMR prefix, SRP auto host address will handle updating SRP entries
      if (found_omr_prefix) {
        ESP_LOGD(TAG, "OMR prefix available - SRP entries will be updated automatically");
      }
    } else {
      ESP_LOGW(TAG, "IPv6 address lost");
    }
  }
}

void OpenThreadZephyr::setup_srp_services() {
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "OpenThread instance not available for SRP setup");
    return;
  }

  // Enable SRP client auto-start mode
  otSrpClientEnableAutoStartMode(instance, nullptr, nullptr);
  ESP_LOGD(TAG, "SRP client auto-start enabled");

  // Enable automatic host address updates when Off-Mesh-Routable prefix changes
  otError auto_addr_error = otSrpClientEnableAutoHostAddress(instance);
  if (auto_addr_error != OT_ERROR_NONE) {
    ESP_LOGE(TAG, "Failed to enable SRP auto host address: %d", auto_addr_error);
  } else {
    ESP_LOGD(TAG, "SRP auto host address enabled - will update when Off-Mesh-Routable prefix changes");
  }

  // Register device with SRP using the actual device name
  std::string hostname_str = App.get_name();  // Store in a string to ensure lifetime
  const char *hostname = hostname_str.c_str();
  otError error = otSrpClientSetHostName(instance, hostname);
  if (error != OT_ERROR_NONE) {
    ESP_LOGE(TAG, "Failed to set SRP hostname: %d", error);
    return;
  }

  // Add host address
  const otIp6Address *hostAddress = otThreadGetMeshLocalEid(instance);
  error = otSrpClientSetHostAddresses(instance, hostAddress, 1);
  if (error != OT_ERROR_NONE) {
    ESP_LOGE(TAG, "Failed to set SRP host address: %d", error);
    return;
  }

  // If mDNS component is available, use its services
  if (this->mdns_ != nullptr) {
    // Get mDNS services
    this->mdns_services_ = this->mdns_->get_services();
    ESP_LOGD(TAG, "Setting up SRP services from mDNS. Count = %d", this->mdns_services_.size());

    // Store service names and other strings to ensure proper lifetime
    std::vector<std::string> service_names;
    std::vector<std::vector<std::string>> txt_keys;
    std::vector<std::vector<std::string>> txt_values;

    for (const auto &service : this->mdns_services_) {
      // Create a service structure
      otSrpClientService srp_service;
      memset(&srp_service, 0, sizeof(srp_service));

      // Set service name and type - store in a string to ensure lifetime
      std::string full_service = service.service_type + "." + service.proto;
      service_names.push_back(full_service);

      srp_service.mName = service_names.back().c_str();
      srp_service.mInstanceName = hostname;
      srp_service.mPort = service.port;
      srp_service.mWeight = 0;
      srp_service.mPriority = 0;

      // Set TXT records if available
      if (!service.txt_records.empty()) {
        // Store TXT keys and values
        txt_keys.push_back(std::vector<std::string>());
        txt_values.push_back(std::vector<std::string>());

        // Allocate memory for TXT entries
        otDnsTxtEntry *txt_entries = new otDnsTxtEntry[service.txt_records.size()];

        // Fill TXT entries
        for (size_t i = 0; i < service.txt_records.size(); i++) {
          const auto &txt = service.txt_records[i];

          // Store keys and values
          txt_keys.back().push_back(txt.key);
          txt_values.back().push_back(txt.value);

          txt_entries[i].mKey = txt_keys.back().back().c_str();
          txt_entries[i].mValue = reinterpret_cast<const uint8_t *>(txt_values.back().back().c_str());
          txt_entries[i].mValueLength = txt_values.back().back().size();
        }

        srp_service.mTxtEntries = txt_entries;
        srp_service.mNumTxtEntries = service.txt_records.size();
      } else {
        srp_service.mNumTxtEntries = 0;
        srp_service.mTxtEntries = nullptr;
      }

      // Register the service
      error = otSrpClientAddService(instance, &srp_service);
      if (error != OT_ERROR_NONE) {
        ESP_LOGE(TAG, "Failed to add SRP service '%s': %d", full_service.c_str(), error);
      } else {
        ESP_LOGD(TAG, "Added SRP service: %s", full_service.c_str());
      }

      // Free allocated memory for TXT entries if any
      if (srp_service.mTxtEntries != nullptr) {
        delete[] srp_service.mTxtEntries;
      }
    }
  } else {
    // Fallback to default service if mDNS is not available
    ESP_LOGW(TAG, "mDNS component not available, using default service");

    // Create a default service structure
    otSrpClientService service;
    memset(&service, 0, sizeof(service));

    // Set service name and type
    std::string service_type = "_esphome._tcp";
    service.mInstanceName = hostname;
    service.mName = service_type.c_str();
    service.mPort = 80;
    service.mWeight = 0;
    service.mPriority = 0;
    service.mNumTxtEntries = 0;
    service.mTxtEntries = nullptr;

    // Register the service
    error = otSrpClientAddService(instance, &service);
    if (error != OT_ERROR_NONE) {
      ESP_LOGE(TAG, "Failed to add default SRP service: %d", error);
    } else {
      ESP_LOGD(TAG, "Added default SRP service: _esphome._tcp");
    }
  }
}

void OpenThreadZephyr::on_shutdown() {
  // Stop the Thread network
  this->stop_thread_network();

  // Clean up SRP services if needed
  otInstance *instance = openthread_get_default_instance();
  if (instance != nullptr) {
    // Disable SRP client
    otSrpClientStop(instance);
    ESP_LOGD(TAG, "SRP client stopped");
  }
}

network::IPAddresses OpenThreadZephyr::get_ip_addresses() {
  network::IPAddresses addresses{};
  size_t i = 0;

  if (!this->has_ipv6_address_) {
    return addresses;
  }

  // Get OpenThread instance
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGW(TAG, "OpenThread instance not available for getting IP addresses");
    return addresses;
  }

  // Get unicast addresses
  const otNetifAddress *unicast_addrs = otIp6GetUnicastAddresses(instance);

  for (const otNetifAddress *addr = unicast_addrs; addr && i < addresses.size(); addr = addr->mNext) {
    char addr_str[OT_IP6_ADDRESS_STRING_SIZE];
    otIp6AddressToString(&addr->mAddress, addr_str, sizeof(addr_str));

    // Convert to IPAddress and add to array
    addresses[i] = network::IPAddress(addr_str);
    i++;
  }

  return addresses;
}

}  // namespace zephyr_openthread
}  // namespace esphome

#endif  // defined(USE_ZEPHYR) && defined(USE_ZEPHYR_OPENTHREAD)
