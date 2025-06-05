import esphome.codegen as cg
from esphome.components.const import CONF_ADJUSTABLE
from esphome.components.esp32 import VARIANT_ESP32P4, only_on_variant
import esphome.config_validation as cv
from esphome.const import CONF_CHANNEL, CONF_ID, CONF_VOLTAGE

CODEOWNERS = ["@clydebarrow"]

DOMAIN = "esp_ldo"
MULTI_CONF = True

esp_ldo_ns = cg.esphome_ns.namespace("esp_ldo")
EspLdo = esp_ldo_ns.class_("EspLdo", cg.Component)

CONFIG_SCHEMA = cv.All(
    {
        cv.GenerateID(): cv.declare_id(EspLdo),
        cv.Required(CONF_VOLTAGE): cv.All(cv.voltage, cv.float_range(min=0.5, max=2.7)),
        cv.Required(CONF_CHANNEL): cv.int_range(min=3, max=4),
        cv.Optional(CONF_ADJUSTABLE, default=False): cv.boolean,
    },
    cv.only_with_esp_idf,
    only_on_variant(supported=[VARIANT_ESP32P4]),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_CHANNEL])
    await cg.register_component(var, config)
    voltage = config[CONF_VOLTAGE]
    cg.add(var.set_millivolts(voltage * 1000))
    cg.add(var.set_adjustable(config[CONF_ADJUSTABLE]))
