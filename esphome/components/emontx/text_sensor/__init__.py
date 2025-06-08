import esphome.codegen as cg
from esphome.components import text_sensor
from esphome.const import CONF_ID

from .. import CONF_EMONTX_ID, CONF_TAG_NAME, EMONTX_LISTENER_SCHEMA, emontx_ns

EmonTxTextSensor = emontx_ns.class_(
    "EmonTxTextSensor", text_sensor.TextSensor, cg.Component
)

CONFIG_SCHEMA = text_sensor.text_sensor_schema(EmonTxTextSensor).extend(
    EMONTX_LISTENER_SCHEMA
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_TAG_NAME])
    await cg.register_component(var, config)
    await text_sensor.register_text_sensor(var, config)
    emontx = await cg.get_variable(config[CONF_EMONTX_ID])
    cg.add(emontx.register_emontx_listener(var))
