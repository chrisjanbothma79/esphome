#include "openthread_info_text_sensor.h"
#include "esphome/core/log.h"

#ifdef USE_ZEPHYR_OPENTHREAD

namespace esphome {
namespace openthread_info {

static const char *const TAG = "openthread_info";

void IPAddressOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread IP Address: '%s'", this->get_name().c_str()); }
void RoleOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread Role: '%s'", this->get_name().c_str()); }
void Rloc16OpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread RLOC16: '%s'", this->get_name().c_str()); }
void ExtAddrOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread Ext Addr: '%s'", this->get_name().c_str()); }
void Eui64OpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread EUI64: '%s'", this->get_name().c_str()); }
void ChannelOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread Channel: '%s'", this->get_name().c_str()); }
void NetworkNameOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread Network Name: '%s'", this->get_name().c_str()); }
void NetworkKeyOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread Network Key: '%s'", this->get_name().c_str()); }
void PanIdOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread PAN ID: '%s'", this->get_name().c_str()); }
void ExtPanIdOpenThreadInfo::dump_config() { ESP_LOGCONFIG(TAG, "OpenThread Ext PAN ID: '%s'", this->get_name().c_str()); }

}  // namespace openthread_info
}  // namespace esphome

#endif // USE_ZEPHYR_OPENTHREAD
