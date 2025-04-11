#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h" // For get_mac_address if needed, or core/util.h
#include "esphome/core/helpers.h" // For format_hex
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/entity_base.h" // Include EntityBase for attributes

#ifdef USE_ZEPHYR_OPENTHREAD // Check specifically for Zephyr OpenThread

#include "esphome/components/zephyr_openthread/openthread.h" // Include Zephyr OT component

#include <openthread/dataset.h>
#include <openthread/ip6.h>
#include <openthread/link.h>
#include <openthread/thread.h>

#include <string>
#include <vector>
#include <array>
#include <optional> // Still needed for potential future use, and standard types
#include <algorithm> // For std::equal, std::copy
#include <cstdio> // For snprintf

namespace esphome {
namespace openthread_info {

// Helper function to get the OT instance safely
inline otInstance *get_ot_instance() {
  if (zephyr_openthread::global_openthread_component == nullptr) {
    ESP_LOGW("openthread_info", "Zephyr OpenThread component not available");
    return nullptr;
  }
  // In Zephyr, the instance is managed by the OS functions
  return openthread_get_default_instance();
}


class IPAddressOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
    if (zephyr_openthread::global_openthread_component == nullptr) {
       ESP_LOGW("openthread_info", "Zephyr OpenThread component not available for IP Address sensor");
       // Report empty state if component is gone and it changed or first report
       if (!this->last_ip_.empty() || !this->has_reported_state_) {
           this->publish_state("");
           this->last_ip_ = "";
           this->has_reported_state_ = true;
       }
       return; // Cannot get address if component is not running
    }

    // Use the method provided by the Zephyr OpenThread component
    std::string ip = zephyr_openthread::global_openthread_component->get_ipv6_address();

    if (ip.empty()) {
        // Handle case where no address is available yet or component is not connected
        if (!this->last_ip_.empty() || !this->has_reported_state_) { // Report empty state if it changed or first report
            this->publish_state("");
            this->last_ip_ = "";
            this->has_reported_state_ = true;
        }
        return;
    }

    if (this->last_ip_ != ip) {
      this->last_ip_ = ip;
      this->publish_state(this->last_ip_);
      this->has_reported_state_ = true;
    }
  }
  // Method to get all addresses as JSON string - called by lambda
  std::string get_all_ipv6_addresses_json() {
    std::string addresses_json = "[";
    bool first = true;
    otInstance *instance = get_ot_instance();
    if (instance) {
      const otNetifAddress *unicast_addrs = otIp6GetUnicastAddresses(instance);
      for (const otNetifAddress *addr = unicast_addrs; addr; addr = addr->mNext) {
        char addr_str[OT_IP6_ADDRESS_STRING_SIZE];
        otIp6AddressToString(&addr->mAddress, addr_str, sizeof(addr_str));
        if (!first) {
          addresses_json += ", "; // Add comma and space for readability
        }
        addresses_json += "\"" + std::string(addr_str) + "\"";
        first = false;
      }
    }
    addresses_json += "]";
    return addresses_json;
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-ip"; }
  void dump_config() override;

 protected:
  std::string last_ip_;
  bool has_reported_state_{false}; // Track if initial state reported
};

class IPAddressOpenThreadInfo; // Forward declaration

class RoleOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
    otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    otDeviceRole role = otThreadGetDeviceRole(instance);

    if (this->last_role_ != role || !this->has_reported_state_) {
      this->last_role_ = role;
      this->publish_state(otThreadDeviceRoleToString(this->last_role_));
      this->has_reported_state_ = true;
    }
  }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-role"; }
  void dump_config() override;

 protected:
  otDeviceRole last_role_{OT_DEVICE_ROLE_DISABLED}; // Initialize to a default
  bool has_reported_state_{false};
};

class Rloc16OpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
     otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    uint16_t rloc16 = otThreadGetRloc16(instance);
    if (this->last_rloc16_ != rloc16 || !this->has_reported_state_) {
      this->last_rloc16_ = rloc16;
      char buf[7]; // Need 7 bytes for "0xABCD\0"
      snprintf(buf, sizeof(buf), "0x%04X", rloc16);
      this->publish_state(buf);
      this->has_reported_state_ = true;
    }
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-rloc16"; }
  void dump_config() override;

 protected:
  uint16_t last_rloc16_{0xFFFF}; // Initialize to an invalid value
  bool has_reported_state_{false};
};

class ExtAddrOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
    otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    auto extaddr = otLinkGetExtendedAddress(instance);
    if (extaddr == nullptr) return; // Check if pointer is valid

    if (!std::equal(this->last_extaddr_.begin(), this->last_extaddr_.end(), extaddr->m8) || !this->has_reported_state_) {
      std::copy(extaddr->m8, extaddr->m8 + 8, this->last_extaddr_.begin());
      this->publish_state(format_hex_pretty(this->last_extaddr_.data(), 8)); // Use pretty format
      this->has_reported_state_ = true;
    }
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-extaddr"; }
  void dump_config() override;

 protected:
  std::array<uint8_t, 8> last_extaddr_{};
  bool has_reported_state_{false};
};

class Eui64OpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
     otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    otExtAddress addr;
    otLinkGetFactoryAssignedIeeeEui64(instance, &addr);
    // No error check needed as the function returns void

    if (!std::equal(this->last_eui64_.begin(), this->last_eui64_.end(), addr.m8) || !this->has_reported_state_) {
      std::copy(addr.m8, addr.m8 + 8, this->last_eui64_.begin());
      this->publish_state(format_hex_pretty(this->last_eui64_.data(), 8)); // Use pretty format
      this->has_reported_state_ = true;
    }
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  // Correct unique ID
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-eui64"; }
  void dump_config() override;

 protected:
  std::array<uint8_t, 8> last_eui64_{};
  bool has_reported_state_{false};
};

class ChannelOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
    otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    uint8_t channel = otLinkGetChannel(instance);
    if (this->last_channel_ != channel || !this->has_reported_state_) {
      this->last_channel_ = channel;
      this->publish_state(std::to_string(this->last_channel_));
      this->has_reported_state_ = true;
    }
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  // Correct unique ID
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-channel"; }
  void dump_config() override;

 protected:
  uint8_t last_channel_{0}; // Initialize
  bool has_reported_state_{false};
};


// Base class DatasetOpenThreadInfo removed - functionality moved into specific sensors

class NetworkNameOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
    otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    otOperationalDataset dataset;
    if (otDatasetGetActive(instance, &dataset) != OT_ERROR_NONE) {
      // Publish empty state if dataset cannot be read and it changed or first report
       if (!this->last_network_name_.empty() || !this->has_reported_state_) {
            this->publish_state("");
            this->last_network_name_ = "";
            this->has_reported_state_ = true;
        }
      return;
    }
    // Check if network name is present in the dataset
    if (!dataset.mComponents.mIsNetworkNamePresent) {
       if (!this->last_network_name_.empty() || !this->has_reported_state_) {
            this->publish_state(""); // Report empty if not present
            this->last_network_name_ = "";
            this->has_reported_state_ = true;
        }
      return;
    }

    std::string current_name = (const char *) dataset.mNetworkName.m8;
    if (this->last_network_name_ != current_name || !this->has_reported_state_) {
      this->last_network_name_ = current_name;
      this->publish_state(this->last_network_name_);
       this->has_reported_state_ = true;
    }
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-networkname"; }
  void dump_config() override;

 protected:
  std::string last_network_name_;
   bool has_reported_state_{false};
};

class NetworkKeyOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
    otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    otOperationalDataset dataset;
     if (otDatasetGetActive(instance, &dataset) != OT_ERROR_NONE || !dataset.mComponents.mIsNetworkKeyPresent) {
       // Publish empty state if dataset cannot be read/key not present and it changed or first report
       if (this->has_value_ || !this->has_reported_state_) {
            this->publish_state("");
            this->has_value_ = false; // Mark as not having a value
            this->has_reported_state_ = true;
        }
      return;
    }

    if (!std::equal(this->last_key_.begin(), this->last_key_.end(), dataset.mNetworkKey.m8) || !this->has_reported_state_) {
      std::copy(dataset.mNetworkKey.m8, dataset.mNetworkKey.m8 + OT_NETWORK_KEY_SIZE, this->last_key_.begin());
      this->publish_state(format_hex_pretty(this->last_key_.data(), OT_NETWORK_KEY_SIZE));
      this->has_value_ = true;
       this->has_reported_state_ = true;
    }
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-networkkey"; }
  void dump_config() override;

 protected:
  std::array<uint8_t, OT_NETWORK_KEY_SIZE> last_key_{};
  bool has_value_{false}; // Track if we have ever had a valid key
   bool has_reported_state_{false};
};

class PanIdOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
  void update() override {
    otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    otOperationalDataset dataset;
    if (otDatasetGetActive(instance, &dataset) != OT_ERROR_NONE || !dataset.mComponents.mIsPanIdPresent) {
      // Publish empty state if dataset cannot be read/PAN ID not present and it changed or first report
       if (this->has_value_ || !this->has_reported_state_) {
            this->publish_state("");
            this->has_value_ = false;
            this->has_reported_state_ = true;
        }
      return;
    }

    uint16_t panid = dataset.mPanId;
    if (this->last_panid_ != panid || !this->has_reported_state_) {
      this->last_panid_ = panid;
      char buf[7]; // Need 7 bytes for "0xABCD\0"
      snprintf(buf, sizeof(buf), "0x%04X", panid);
      this->publish_state(buf);
      this->has_value_ = true;
       this->has_reported_state_ = true;
    }
  }
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-panid"; }
  void dump_config() override;

 protected:
  uint16_t last_panid_{0xFFFF}; // Initialize
  bool has_value_{false};
   bool has_reported_state_{false};
};

class ExtPanIdOpenThreadInfo : public PollingComponent, public text_sensor::TextSensor {
 public:
   void update() override {
    otInstance *instance = get_ot_instance();
    if (instance == nullptr) return;

    otOperationalDataset dataset;
    if (otDatasetGetActive(instance, &dataset) != OT_ERROR_NONE || !dataset.mComponents.mIsExtendedPanIdPresent) {
       // Publish empty state if dataset cannot be read/XPANID not present and it changed or first report
       if (this->has_value_ || !this->has_reported_state_) {
            this->publish_state("");
            this->has_value_ = false;
            this->has_reported_state_ = true;
        }
      return;
    }

    if (!std::equal(this->last_extpanid_.begin(), this->last_extpanid_.end(), dataset.mExtendedPanId.m8) || !this->has_reported_state_) {
      std::copy(dataset.mExtendedPanId.m8, dataset.mExtendedPanId.m8 + OT_EXT_PAN_ID_SIZE, this->last_extpanid_.begin());
      this->publish_state(format_hex_pretty(this->last_extpanid_.data(), OT_EXT_PAN_ID_SIZE));
       this->has_value_ = true;
       this->has_reported_state_ = true;
    }
  }

  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }
  std::string unique_id() override { return get_mac_address() + "-openthreadinfo-extpanid"; }
  void dump_config() override;

 protected:
  std::array<uint8_t, OT_EXT_PAN_ID_SIZE> last_extpanid_{};
   bool has_value_{false};
    bool has_reported_state_{false};
};

}  // namespace openthread_info
}  // namespace esphome
#endif // USE_ZEPHYR_OPENTHREAD
