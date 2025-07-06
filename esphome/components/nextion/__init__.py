import esphome.codegen as cg
from esphome.components import uart
from esphome.const import PlatformFramework

nextion_ns = cg.esphome_ns.namespace("nextion")
Nextion = nextion_ns.class_("Nextion", cg.PollingComponent, uart.UARTDevice)
nextion_ref = Nextion.operator("ref")

CONF_NEXTION_ID = "nextion_id"
CONF_PUBLISH_STATE = "publish_state"
CONF_SEND_TO_NEXTION = "send_to_nextion"

PLATFORM_SOURCE_FILES: dict[str, set[PlatformFramework]] = {
    "nextion_upload_arduino.cpp": {
        PlatformFramework.ESP32_ARDUINO,
        PlatformFramework.ESP8266_ARDUINO,
        PlatformFramework.RP2040_ARDUINO,
        PlatformFramework.BK72XX_ARDUINO,
        PlatformFramework.RTL87XX_ARDUINO,
        PlatformFramework.LN882X_ARDUINO,
    },
    "nextion_upload_idf.cpp": {PlatformFramework.ESP32_IDF},
}
