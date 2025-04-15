"""Temperature sensor implementation for WTS01."""

import esphome.codegen as cg
from esphome.components import sensor, uart, wts01
import esphome.config_validation as cv
from esphome.const import (
    CONF_UPDATE_INTERVAL,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
)

CONF_WTS01_ID = "wts01_id"
DEPENDENCIES = wts01.DEPENDENCIES

DEFAULT_UPDATE_INTERVAL = "60s"

wts01_ns = cg.esphome_ns.namespace("wts01")
WTS01Sensor = wts01_ns.class_(
    "WTS01Sensor", cg.Component, uart.UARTDevice, sensor.Sensor
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        WTS01Sensor,
        unit_of_measurement=UNIT_CELSIUS,
        accuracy_decimals=1,
        device_class=DEVICE_CLASS_TEMPERATURE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.Optional(
                CONF_UPDATE_INTERVAL, default=DEFAULT_UPDATE_INTERVAL
            ): cv.update_interval,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_temperature_sensor(var))

    # Always set the update_interval, either from user config or default
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))
