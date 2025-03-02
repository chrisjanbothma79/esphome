#pragma once

#include "esphome/components/zigbee/zigbee_component.h"
#ifdef USE_ZIGBEE
#include "esphome/core/component.h"
#include "esphome/components/time/real_time_clock.h"

extern "C" {
#include <zboss_api.h>
#include <zboss_api_addons.h>
}

#define ESPHOME_ZB_HA_DECLARE_TIME_CLUSTER_LIST(cluster_list_name, time_attr_list, basic_attr_list, \
                                                identify_attr_list, groups_attr_list, scenes_attr_list) \
  zb_zcl_cluster_desc_t cluster_list_name[] = { \
      ZB_ZCL_CLUSTER_DESC(ZB_ZCL_CLUSTER_ID_BASIC, ZB_ZCL_ARRAY_SIZE(basic_attr_list, zb_zcl_attr_t), \
                          (basic_attr_list), ZB_ZCL_CLUSTER_SERVER_ROLE, ZB_ZCL_MANUF_CODE_INVALID), \
      ZB_ZCL_CLUSTER_DESC(ZB_ZCL_CLUSTER_ID_IDENTIFY, ZB_ZCL_ARRAY_SIZE(identify_attr_list, zb_zcl_attr_t), \
                          (identify_attr_list), ZB_ZCL_CLUSTER_SERVER_ROLE, ZB_ZCL_MANUF_CODE_INVALID), \
      ZB_ZCL_CLUSTER_DESC(ZB_ZCL_CLUSTER_ID_TIME, ZB_ZCL_ARRAY_SIZE(time_attr_list, zb_zcl_attr_t), (time_attr_list), \
                          ZB_ZCL_CLUSTER_SERVER_ROLE, ZB_ZCL_MANUF_CODE_INVALID), \
      ZB_ZCL_CLUSTER_DESC(ZB_ZCL_CLUSTER_ID_SCENES, ZB_ZCL_ARRAY_SIZE(scenes_attr_list, zb_zcl_attr_t), \
                          (scenes_attr_list), ZB_ZCL_CLUSTER_SERVER_ROLE, ZB_ZCL_MANUF_CODE_INVALID), \
      ZB_ZCL_CLUSTER_DESC(ZB_ZCL_CLUSTER_ID_GROUPS, ZB_ZCL_ARRAY_SIZE(groups_attr_list, zb_zcl_attr_t), \
                          (groups_attr_list), ZB_ZCL_CLUSTER_SERVER_ROLE, ZB_ZCL_MANUF_CODE_INVALID), \
      ZB_ZCL_CLUSTER_DESC(ZB_ZCL_CLUSTER_ID_TIME, 0, NULL, ZB_ZCL_CLUSTER_CLIENT_ROLE, ZB_ZCL_MANUF_CODE_INVALID)}

namespace esphome {
namespace zigbee {

class ZigbeeTime : public time::RealTimeClock, public ZigbeeEntity {
 public:
  void setup() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE - 1.0f; }
  void dump_config() override;
  void update() override;

  void set_cluster_attributes(zb_zcl_time_attrs_t &cluster_attributes) {
    this->cluster_attributes_ = &cluster_attributes;
  }

  void set_epoch_time(uint32_t epoch);

 protected:
  void zcl_device_cb_(zb_bufid_t bufid);
  zb_zcl_time_attrs_t *cluster_attributes_{nullptr};

  bool has_time_{false};
};

}  // namespace zigbee
}  // namespace esphome

#endif