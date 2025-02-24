import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC, ICON_TIMER

uptime_ns = cg.esphome_ns.namespace("uptime")
UptimeTextSensor = uptime_ns.class_(
    "UptimeTextSensor", text_sensor.TextSensor, cg.PollingComponent
)

CONF_SEPARATOR = "separator"

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema(
        UptimeTextSensor,
        icon=ICON_TIMER,
        entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
    )
    .extend({cv.Optional(CONF_SEPARATOR, default=""): cv.string})
    .extend(cv.polling_component_schema("30s"))
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    cg.add(var.set_separator(config[CONF_SEPARATOR]))
    await cg.register_component(var, config)
