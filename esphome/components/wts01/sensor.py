"""Temperature sensor implementation for WTS01."""

import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_TEMPERATURE,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
)

CONF_WTS01_ID = "wts01_id"

DEPENDENCIES = ["wts01"]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_WTS01_ID): cv.use_id("WTS01Component"),
        cv.Required(CONF_TEMPERATURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_WTS01_ID])

    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        # Créer une lambda qui appelle get_temperature() sur le parent
        cg.add(sens.set_state_lambda(f"return {parent.get_id()}->get_temperature();"))
