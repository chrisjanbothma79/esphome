import esphome.codegen as cg
from esphome.components import binary_sensor
from esphome.const import CONF_ID

from .. import CONF_EMONTX_ID, CONF_TAG_NAME, EMONTX_LISTENER_SCHEMA, emontx_ns

emonTxBinarySensor = emontx_ns.class_(
    "emonTxBinarySensor", binary_sensor.BinarySensor, cg.Component
)

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema(emonTxBinarySensor).extend(
    EMONTX_LISTENER_SCHEMA
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_TAG_NAME])
    await cg.register_component(var, config)
    await binary_sensor.register_binary_sensor(var, config)
    emontx = await cg.get_variable(config[CONF_EMONTX_ID])
    cg.add(emontx.register_emontx_listener(var))
