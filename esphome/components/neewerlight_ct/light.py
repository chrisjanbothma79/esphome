import esphome.codegen as cg
from esphome.components import ble_client, light, output
from esphome.components.color_temperature import light as ct_light
import esphome.config_validation as cv
from esphome.const import (
    CONF_COLD_WHITE_COLOR_TEMPERATURE,
    CONF_NAME,
    CONF_OUTPUT_ID,
    CONF_WARM_WHITE_COLOR_TEMPERATURE,
)

AUTO_LOAD = ["color_temperature", "esp32_ble_tracker", "output"]
CODEOWNERS = ["@khvMX"]
DEPENDENCIES = ["ble_client"]
IS_PLATFORM_COMPONENT = True

neewerlight_ct_ns = cg.esphome_ns.namespace("neewerlight_ct")
NeewerBLEOutput = neewerlight_ct_ns.class_(
    "NeewerBLEOutput", cg.Component, output.FloatOutput, ble_client.BLEClientNode
)
NeewerCTLightOutput = neewerlight_ct_ns.class_(
    "NeewerCTLightOutput",
    ct_light.CTLightOutput,
    NeewerBLEOutput,
)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(NeewerCTLightOutput),
            cv.Required(CONF_NAME): cv.string,
            cv.Required(ble_client.CONF_BLE_CLIENT_ID): cv.use_id(ble_client.BLEClient),
            cv.Required(CONF_COLD_WHITE_COLOR_TEMPERATURE): cv.color_temperature,
            cv.Required(CONF_WARM_WHITE_COLOR_TEMPERATURE): cv.color_temperature,
        }
    )
    .extend(cv.ENTITY_BASE_SCHEMA)
    .extend(light.LIGHT_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await light.register_light(var, config)

    await ble_client.register_ble_node(var, config)

    cg.add(var.set_cold_white_temperature(config[CONF_COLD_WHITE_COLOR_TEMPERATURE]))
    cg.add(var.set_warm_white_temperature(config[CONF_WARM_WHITE_COLOR_TEMPERATURE]))
