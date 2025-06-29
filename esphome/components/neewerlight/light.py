import esphome.codegen as cg
from esphome.components import ble_client, light
from esphome.components.color_temperature import light as ct_light
from esphome.components.neewerlight import output as nw_output
import esphome.config_validation as cv
from esphome.const import CONF_NAME, CONF_OUTPUT_ID

DEPENDENCIES = ["ble_client"]
AUTO_LOAD = ["output", "color_temperature"]
IS_PLATFORM_COMPONENT = True

neewerlight_ns = cg.esphome_ns.namespace("neewerlight")
ct_ns = cg.esphome_ns.namespace("color_temperature")

NeewerCTLightOutput = neewerlight_ns.class_(
    "NeewerCTLightOutput",
    ct_light.CTLightOutput,
    nw_output.NeewerBLEOutput,
)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(NeewerCTLightOutput),
            cv.Required(CONF_NAME): cv.string,
            cv.Required(ble_client.CONF_BLE_CLIENT_ID): cv.use_id(ble_client.BLEClient),
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
