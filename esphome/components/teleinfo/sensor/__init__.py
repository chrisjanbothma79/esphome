import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ACCURACY_DECIMALS,
    CONF_DEVICE_CLASS,
    CONF_ID,
    CONF_STATE_CLASS,
    CONF_UNIT_OF_MEASUREMENT,
    DEVICE_CLASS_APPARENT_POWER,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_REACTIVE_POWER,
    DEVICE_CLASS_VOLTAGE,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_AMPERE,
    UNIT_VOLT,
    UNIT_VOLT_AMPS,
    UNIT_VOLT_AMPS_REACTIVE_HOURS,
    UNIT_WATT,
    UNIT_WATT_HOURS,
)

from .. import CONF_TAG_NAME, CONF_TELEINFO_ID, TELEINFO_LISTENER_SCHEMA, teleinfo_ns

TeleInfoSensor = teleinfo_ns.class_("TeleInfoSensor", sensor.Sensor, cg.Component)


# Define sensor type configurations by prefix
TIC_TAG_CONFIGS = {
    # Energy tags (Wh) - All tags starting with EA
    "EA": {
        CONF_UNIT_OF_MEASUREMENT: UNIT_WATT_HOURS,
        CONF_DEVICE_CLASS: DEVICE_CLASS_ENERGY,
        CONF_STATE_CLASS: STATE_CLASS_TOTAL_INCREASING,
        CONF_ACCURACY_DECIMALS: 0,
    },
    "ER": {
        CONF_UNIT_OF_MEASUREMENT: UNIT_VOLT_AMPS_REACTIVE_HOURS,
        CONF_DEVICE_CLASS: DEVICE_CLASS_REACTIVE_POWER,
        CONF_STATE_CLASS: STATE_CLASS_TOTAL_INCREASING,
        CONF_ACCURACY_DECIMALS: 0,
    },
    # Current tags (A)
    "IRMS": {
        CONF_UNIT_OF_MEASUREMENT: UNIT_AMPERE,
        CONF_DEVICE_CLASS: DEVICE_CLASS_CURRENT,
        CONF_STATE_CLASS: STATE_CLASS_MEASUREMENT,
        CONF_ACCURACY_DECIMALS: 0,
    },
    # Voltage tags (V)
    "U": {
        CONF_UNIT_OF_MEASUREMENT: UNIT_VOLT,
        CONF_DEVICE_CLASS: DEVICE_CLASS_VOLTAGE,
        CONF_STATE_CLASS: STATE_CLASS_MEASUREMENT,
        CONF_ACCURACY_DECIMALS: 0,
    },
    "SINST": {
        CONF_UNIT_OF_MEASUREMENT: UNIT_VOLT_AMPS,
        CONF_DEVICE_CLASS: DEVICE_CLASS_APPARENT_POWER,
        CONF_STATE_CLASS: STATE_CLASS_MEASUREMENT,
        CONF_ACCURACY_DECIMALS: 0,
    },
    "SMAX": {
        CONF_UNIT_OF_MEASUREMENT: UNIT_VOLT_AMPS,
        CONF_DEVICE_CLASS: DEVICE_CLASS_APPARENT_POWER,
        CONF_STATE_CLASS: STATE_CLASS_MEASUREMENT,
        CONF_ACCURACY_DECIMALS: 0,
    },
    "CC": {
        CONF_UNIT_OF_MEASUREMENT: UNIT_WATT,
        CONF_DEVICE_CLASS: DEVICE_CLASS_POWER,
        CONF_STATE_CLASS: STATE_CLASS_MEASUREMENT,
        CONF_ACCURACY_DECIMALS: 0,
    },
}


def apply_tag_config(config):
    """Apply preset configurations based on the tag name."""
    if CONF_TAG_NAME not in config:
        return config

    tag_name = config[CONF_TAG_NAME]

    # Check for prefix matches
    for prefix, preset in TIC_TAG_CONFIGS.items():
        if tag_name.startswith(prefix):
            for key, value in preset.items():
                if key not in config:
                    config[key] = value
            break

    return config


CONFIG_SCHEMA = cv.All(
    sensor.sensor_schema(
        TeleInfoSensor,
        accuracy_decimals=0,
    ).extend(TELEINFO_LISTENER_SCHEMA),
    apply_tag_config,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_TAG_NAME])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
    teleinfo = await cg.get_variable(config[CONF_TELEINFO_ID])
    cg.add(teleinfo.register_teleinfo_listener(var))
