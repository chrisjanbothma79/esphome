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
#include <openthread/srp_client_buffers.h>
#include <openthread/dataset_ftd.h>
#include <openthread/netdata.h>
#include <zephyr/mgmt/mcumgr/transport/smp_udp.h>
#include <set>

namespace esphome {
namespace zephyr_openthread {

static const char *const TAG = "zephyr_openthread";

// Add a global variable for the OpenThreadZephyr component
OpenThreadZephyr *global_openthread_component = nullptr;

// SRP client callbacks
void srpCallback(otError aError, const otSrpClientHostInfo *aHostInfo, const otSrpClientService *aServices,
                 const otSrpClientService *aRemovedServices, void *aContext) {
  if (aError == OT_ERROR_NONE) {
    ESP_LOGI(TAG, "SRP client registration successful");
  } else {
    ESP_LOGW(TAG, "SRP client registration failed: %s", otThreadErrorToString(aError));
  }
}

void srpStartCallback(const otSockAddr *aServerSockAddr, void *aContext) { ESP_LOGI(TAG, "SRP client has started"); }

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

      // Reset SRP services registration flag when disconnected
      this->srp_services_registered_ = false;
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

void OpenThreadZephyr::start_thread_network() {
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "OpenThread instance not available");
    return;
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

  // Track address changes
  std::string previous_ipv6_address = this->ipv6_address_;
  
  // Set to store current addresses for comparison
  std::set<std::string> current_addresses;
  bool new_global_address_found = false;
  int addr_count = 0;

  for (const otNetifAddress *addr = unicast_addrs; addr; addr = addr->mNext) {
    addr_count++;
    char addr_str[OT_IP6_ADDRESS_STRING_SIZE];
    otIp6AddressToString(&addr->mAddress, addr_str, sizeof(addr_str));
    
    // Add to current addresses set
    std::string address_string(addr_str);
    current_addresses.insert(address_string);
    
    // Check if this is a new address we haven't seen before
    bool is_new_address = this->known_addresses_.find(address_string) == this->known_addresses_.end();
    
    // Log new addresses
    if (is_new_address) {
      ESP_LOGD(TAG, "New IPv6 address found: %s/%d", addr_str, addr->mPrefixLength);
      this->known_addresses_.insert(address_string);
    }

    // Check if mesh-local address (fd prefix)
    if (addr->mAddress.mFields.m8[0] == 0xfd) {
      found_mesh_local = true;
      mesh_local_addr = addr_str;
      
      // Flag for MCUMGR restart if it's a new mesh-local address
      if (is_new_address) {
        new_global_address_found = true;
      }
    }
    // Check if global address (2xxx or 3xxx prefix)
    else if ((addr->mAddress.mFields.m8[0] == 0x20 || addr->mAddress.mFields.m8[0] == 0x30) &&
             addr->mPrefixLength == 64) {
      found_global = true;
      global_addr = addr_str;
      
      // Log new global addresses explicitly
      if (is_new_address) {
        ESP_LOGI(TAG, "New global IPv6 address found: %s", addr_str);
        new_global_address_found = true;
      }
      
      found_omr_prefix = true;
    }
    // Check if link-local address (fe80 prefix)
    else if (addr->mAddress.mFields.m8[0] == 0xfe && addr->mAddress.mFields.m8[1] == 0x80) {
      // If we don't have a better address, use link-local as fallback
      if (!found_mesh_local && !found_global) {
        mesh_local_addr = addr_str;
      }
    }
  }

  // Detect addresses that disappeared
  std::vector<std::string> removed_addresses;
  for (const auto &known_addr : this->known_addresses_) {
    if (current_addresses.find(known_addr) == current_addresses.end()) {
      removed_addresses.push_back(known_addr);
      ESP_LOGD(TAG, "IPv6 address removed: %s", known_addr.c_str());
    }
  }
  
  // Remove disappeared addresses from known set
  for (const auto &removed : removed_addresses) {
    this->known_addresses_.erase(removed);
  }

  if (addr_count == 0 && this->known_addresses_.empty()) {
    ESP_LOGD(TAG, "No IPv6 addresses found");
  }

  // Update IPv6 address status
  bool had_ipv6 = this->has_ipv6_address_;
  this->has_ipv6_address_ = found_mesh_local || found_global;

  // Prefer global address, fall back to mesh-local
  std::string new_ipv6_address;
  if (found_global) {
    new_ipv6_address = global_addr;
    // Only log if it's a new primary address
    if (new_ipv6_address != previous_ipv6_address) {
      ESP_LOGI(TAG, "Using global IPv6 address: %s", global_addr.c_str());
    }
  } else if (found_mesh_local) {
    new_ipv6_address = mesh_local_addr;
    // Only log if it's a new primary address
    if (new_ipv6_address != previous_ipv6_address) {
      ESP_LOGI(TAG, "Using mesh-local IPv6 address: %s", mesh_local_addr.c_str());
    }
  }
  
  // Update the stored IP address
  this->ipv6_address_ = new_ipv6_address;

  // Address status changed (gained or lost an address)
  if (had_ipv6 != this->has_ipv6_address_) {
    if (this->has_ipv6_address_) {
      ESP_LOGI(TAG, "IPv6 address acquired: %s", this->ipv6_address_.c_str());

      // Setup SRP services once when the first IPv6 address is acquired
      if (!this->srp_services_registered_ && this->mdns_ != nullptr) {
        ESP_LOGI(TAG, "Setting up SRP services now that we have an IP address");
        this->setup_srp_services();
        this->srp_services_registered_ = true; // Mark as registered
      }

    } else {
      ESP_LOGI(TAG, "IPv6 address lost");
    }
  }
  
  // Restart MCUMGR UDP transport if we found new global addresses and it's already running
  if (new_global_address_found) {
    ESP_LOGI(TAG, "New IPv6 address detected, restarting MCUMGR UDP transport to listen on new interfaces");
    if (this->mcumgr_udp_started_) {
      smp_udp_close();
    }
    int ret = smp_udp_open();
    if (ret == 0) {
      ESP_LOGI(TAG, "MCUMGR UDP transport restarted successfully.");
      this->mcumgr_udp_started_ = true;
    } else {
      ESP_LOGE(TAG, "Failed to restart MCUMGR UDP transport: %d", ret);
      this->mcumgr_udp_started_ = false; // Mark as stopped since restart failed
    }
  }
}

void *OpenThreadZephyr::pool_alloc_(size_t size) {
  uint8_t *ptr = new uint8_t[size];
  this->memory_pool_.emplace_back(std::unique_ptr<uint8_t[]>(ptr));
  return ptr;
}

void OpenThreadZephyr::setup_srp_services() {
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "OpenThread instance not available for SRP setup");
    return;
  }

  // Set up the SRP client callback (only needs to be done once)
  otSrpClientSetCallback(instance, srpCallback, nullptr);

  // Set the host name using the project name
  std::string hostname_str = App.get_name();
  this->host_name_ = hostname_str;

  // Get buffer and set hostname
  uint16_t size;
  char *existing_host_name = otSrpClientBuffersGetHostNameString(instance, &size);
  uint16_t len = this->host_name_.size();
  if (len + 1 > size) { // +1 for null terminator
    ESP_LOGW(TAG, "Hostname '%s' is too long (max %d), choose a shorter project name", hostname_str.c_str(), size - 1);
    return; // Don't proceed if hostname is too long
  }
  memcpy(existing_host_name, this->host_name_.c_str(), len + 1);

  // Set the hostname
  otError error = otSrpClientSetHostName(instance, existing_host_name);
  if (error != OT_ERROR_NONE) {
    ESP_LOGW(TAG, "Could not set host name: %s", otThreadErrorToString(error));
    // Don't return here, attempt to register services anyway
  }

  // Enable automatic host address updates (uses current addresses)
  error = otSrpClientEnableAutoHostAddress(instance);
  if (error != OT_ERROR_NONE) {
    ESP_LOGW(TAG, "Could not enable auto host address: %s", otThreadErrorToString(error));
  }

  // Register mDNS services if available
  if (this->mdns_ != nullptr) {
    this->mdns_services_ = this->mdns_->get_services();
    ESP_LOGI(TAG, "Registering %d SRP services", this->mdns_services_.size());

    for (const auto &service : this->mdns_services_) {
      std::string service_type = service.service_type + "." + service.proto;

      otSrpClientBuffersServiceEntry *entry = otSrpClientBuffersAllocateService(instance);
      if (!entry) {
        ESP_LOGW(TAG, "Failed to allocate service entry for %s", service_type.c_str());
        continue; // Try next service
      }

      // Populate service entry
      char *buffer;
      uint16_t buffer_size;
      bool success = true; // Track if entry population succeeds

      // Set service name (type._proto)
      buffer = otSrpClientBuffersGetServiceEntryServiceNameString(entry, &buffer_size);
      if (service_type.size() + 1 > buffer_size) {
        ESP_LOGW(TAG, "Service name too long: %s", service_type.c_str());
        success = false;
      }
      if (success) {
         memcpy(buffer, service_type.c_str(), service_type.size() + 1);
      }

      // Set instance name (use host name) - only if previous steps succeeded
      if (success) {
          buffer = otSrpClientBuffersGetServiceEntryInstanceNameString(entry, &buffer_size);
          if (this->host_name_.size() + 1 > buffer_size) {
            ESP_LOGW(TAG, "Instance name too long: %s", this->host_name_.c_str());
            success = false;
          } else {
            memcpy(buffer, this->host_name_.c_str(), this->host_name_.size() + 1);
          }
      }

      // Set port - only if previous steps succeeded
      if (success) {
          entry->mService.mPort = service.port;
      }

      // Set TXT records - only if previous steps succeeded
      entry->mService.mNumTxtEntries = 0;
      entry->mService.mTxtEntries = nullptr;
      if (success && !service.txt_records.empty()) {
        otDnsTxtEntry *mTxtEntries = reinterpret_cast<otDnsTxtEntry *>(
            this->pool_alloc_(sizeof(otDnsTxtEntry) * service.txt_records.size()));
        // NOTE: pool_alloc_ return not checked
        for (size_t i = 0; i < service.txt_records.size(); i++) {
          const auto &txt = service.txt_records[i];
          mTxtEntries[i].mKey = txt.key.c_str();
          mTxtEntries[i].mValue = reinterpret_cast<const uint8_t *>(txt.value.c_str());
          mTxtEntries[i].mValueLength = txt.value.size();
        }
        entry->mService.mTxtEntries = mTxtEntries;
        entry->mService.mNumTxtEntries = service.txt_records.size();
      }
      this->srp_service_entries_.push_back(entry); // Store pointer on success

      if (success) {
        // Now, add the service (which acts as registration or update)
        error = otSrpClientAddService(instance, &entry->mService);
        if (error != OT_ERROR_NONE) {
          ESP_LOGW(TAG, "Failed to add/update SRP service %s: %s", service_type.c_str(), otThreadErrorToString(error));
        } else {
          ESP_LOGI(TAG, "Added/Updated SRP service: %s", service_type.c_str());
        }
      } else {
         ESP_LOGW(TAG, "Skipping addition of service %s due to population error.", service_type.c_str());
      }
    }
  } else {
    ESP_LOGW(TAG, "mDNS component not available, SRP services will not be registered");
  }

  // Enable auto start mode for SRP client
  otSrpClientEnableAutoStartMode(instance, srpStartCallback, nullptr);
  ESP_LOGI(TAG, "SRP setup complete, client auto-start enabled.");
}

void OpenThreadZephyr::on_shutdown() {
  // Stop the Thread network
  this->stop_thread_network();

  // Stop MCUMGR UDP transport if it was started
  if (this->mcumgr_udp_started_) {
    ESP_LOGI(TAG, "Stopping MCUMGR UDP transport...");
    smp_udp_close();
    this->mcumgr_udp_started_ = false;
    ESP_LOGI(TAG, "MCUMGR UDP transport stopped.");
  }

  // Clean up SRP services if needed
  otInstance *instance = openthread_get_default_instance();
  if (instance != nullptr) {
    // Free allocated SRP service entries
    ESP_LOGD(TAG, "Freeing %d allocated SRP service entries...", this->srp_service_entries_.size());
    this->srp_service_entries_.clear();

    // Disable SRP client (stops communication and removes services from server)
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

void OpenThreadZephyr::configure_operational_dataset() {
  ESP_LOGI(TAG, "Forcing OpenThread operational dataset configuration");
  
  otInstance *instance = openthread_get_default_instance();
  if (instance == nullptr) {
    ESP_LOGE(TAG, "OpenThread instance not available");
    return;
  }

  // Create operational dataset
  otOperationalDataset dataset = {};
  
  // Set active timestamp
  dataset.mActiveTimestamp.mSeconds = 1;
  dataset.mActiveTimestamp.mTicks = 0;
  dataset.mActiveTimestamp.mAuthoritative = true;
  dataset.mComponents.mIsActiveTimestampPresent = true;
  
  // Set network key
  otNetworkKey key;
  const char *network_key = this->network_key_.c_str();
  for (int i = 0; i < OT_NETWORK_KEY_SIZE; i++) {
    char byte_str[3] = {network_key[i * 2], network_key[i * 2 + 1], '\0'};
    key.m8[i] = static_cast<uint8_t>(strtoul(byte_str, nullptr, 16));
  }
  memcpy(dataset.mNetworkKey.m8, key.m8, OT_NETWORK_KEY_SIZE);
  dataset.mComponents.mIsNetworkKeyPresent = true;
  
  // Set network name
  strncpy(dataset.mNetworkName.m8, this->network_name_.c_str(), OT_NETWORK_NAME_MAX_SIZE);
  dataset.mNetworkName.m8[OT_NETWORK_NAME_MAX_SIZE - 1] = '\0';  // Ensure null termination
  dataset.mComponents.mIsNetworkNamePresent = true;
  
  // Set extended PAN ID
  const char *xpanid_str = this->xpanid_.c_str();
  for (int i = 0; i < OT_EXT_PAN_ID_SIZE; i++) {
    char byte_str[3] = {xpanid_str[i * 2], xpanid_str[i * 2 + 1], '\0'};
    dataset.mExtendedPanId.m8[i] = static_cast<uint8_t>(strtoul(byte_str, nullptr, 16));
  }
  dataset.mComponents.mIsExtendedPanIdPresent = true;
  
  // Set PAN ID
  dataset.mPanId = this->panid_;
  dataset.mComponents.mIsPanIdPresent = true;
  
  // Set channel
  dataset.mChannel = this->channel_;
  dataset.mComponents.mIsChannelPresent = true;
  
  // Set PSKc if available
  const char *pskc_str = this->pskc_.c_str();
  for (int i = 0; i < OT_PSKC_MAX_SIZE; i++) {
    char byte_str[3] = {pskc_str[i * 2], pskc_str[i * 2 + 1], '\0'};
    dataset.mPskc.m8[i] = static_cast<uint8_t>(strtoul(byte_str, nullptr, 16));
  }
  dataset.mComponents.mIsPskcPresent = true;
  
  // Set dataset as active
  otError error = otDatasetSetActive(instance, &dataset);
  if (error != OT_ERROR_NONE) {
    ESP_LOGE(TAG, "Failed to set active dataset: %s", otThreadErrorToString(error));
    return;
  }

  ESP_LOGI(TAG, "Successfully configured and set active dataset");
}

}  // namespace zephyr_openthread
}  // namespace esphome

#endif  // defined(USE_ZEPHYR) && defined(USE_ZEPHYR_OPENTHREAD)
