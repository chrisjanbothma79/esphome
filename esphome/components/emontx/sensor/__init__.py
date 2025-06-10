import esphome.codegen as cg
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    # DEVICE_CLASS_ENERGY,
    # DEVICE_CLASS_POWER,
    # DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLTAGE,
    STATE_CLASS_MEASUREMENT,
    # STATE_CLASS_TOTAL_INCREASING,
    # UNIT_CELSIUS,
    UNIT_VOLT,
    # UNIT_WATT,
    # UNIT_WATT_HOURS,
)

from .. import CONF_EMONTX_ID, CONF_TAG_NAME, EMONTX_LISTENER_SCHEMA, emontx_ns

EmonTxSensor = emontx_ns.class_("EmonTxSensor", sensor.Sensor, cg.Component)

CONFIG_SCHEMA = sensor.sensor_schema(
    EmonTxSensor,
    unit_of_measurement=UNIT_VOLT,
    device_class=DEVICE_CLASS_VOLTAGE,
    state_class=STATE_CLASS_MEASUREMENT,
    accuracy_decimals=2,
).extend(EMONTX_LISTENER_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_TAG_NAME])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    emontx = await cg.get_variable(config[CONF_EMONTX_ID])
    cg.add(emontx.register_emontx_listener(var))
