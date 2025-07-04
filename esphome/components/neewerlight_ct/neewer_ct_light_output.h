#pragma once

#include "esphome/components/color_temperature/ct_light_output.h"
#include "esphome/components/ble_client/ble_client.h"
#include "neewer_ble_client.h"
#include "neewer_ble_message.h"
#include "neewer_light_state.h"

#ifdef USE_ESP32

namespace esphome {
namespace neewerlight_ct {

class NeewerCTLightOutput : public Component,
                            public color_temperature::CTLightOutput,
                            public ble_client::BLEClientNode {
 public:
  explicit NeewerCTLightOutput();
  void dump_config() override;

  // BLEClientNode override
  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                           esp_ble_gattc_cb_param_t *param) override;

 protected:
  void write_state(light::LightState *state) override;

  // Methods to prepare messages and send them via BLE
  void turn_on_off(OnOffState on_off);
  void change_color_temperature_and_brightness(int color_temperature, int brightness);
  void change_brightness(int brightness_percent);
  void send_via_ble(const NeewerBleMessage &msg);

  NeewerLightState old_state_;
  NeewerBleClient ble_;
  NeewerBleMessage msg_;

  const std::string SERVICE_UUID = "69400001-B5A3-F393-E0A9-E50E24DCCA99";
  const std::string CHARACTERISTIC_UUID = "69400002-B5A3-F393-E0A9-E50E24DCCA99";
};

}  // namespace neewerlight_ct
}  // namespace esphome

#endif  // USE_ESP32