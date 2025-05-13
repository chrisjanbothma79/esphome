from esphome import pins
import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_PRESSURE,
    CONF_TEMPERATURE,
    DEVICE_CLASS_PRESSURE,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_HECTOPASCAL,
)

CODEOWNERS = ["@kenavn"]  # Replace with your GitHub username
DEPENDENCIES = []
AUTO_LOAD = ["sensor"]

m3200_ns = cg.esphome_ns.namespace("m3200")
M3200Component = m3200_ns.class_("M3200Component", cg.PollingComponent)

CONF_SDA_PIN = "sda_pin"
CONF_SCL_PIN = "scl_pin"
CONF_ADDRESS = "address"
CONF_MIN_PRESSURE = "min_pressure"
CONF_MAX_PRESSURE = "max_pressure"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(M3200Component),
        cv.Required(CONF_SDA_PIN): pins.gpio_output_pin_schema,
        cv.Required(CONF_SCL_PIN): pins.gpio_output_pin_schema,
        cv.Optional(CONF_ADDRESS, default=0x28): cv.hex_uint8_t,
        cv.Optional(CONF_PRESSURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_HECTOPASCAL,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_PRESSURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_MIN_PRESSURE, default=0): cv.float_,
        cv.Optional(CONF_MAX_PRESSURE, default=100): cv.float_,
    }
).extend(cv.polling_component_schema("10s"))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # Configure pins
    sda_pin = await cg.gpio_pin_expression(config[CONF_SDA_PIN])
    scl_pin = await cg.gpio_pin_expression(config[CONF_SCL_PIN])
    cg.add(var.set_sda_pin(sda_pin))
    cg.add(var.set_scl_pin(scl_pin))

    # Configure address
    cg.add(var.set_address(config[CONF_ADDRESS]))

    # Configure pressure range
    cg.add(var.set_pressure_range(config[CONF_MIN_PRESSURE], config[CONF_MAX_PRESSURE]))

    # Set up sensors
    if CONF_PRESSURE in config:
        sens = await sensor.new_sensor(config[CONF_PRESSURE])
        cg.add(var.set_pressure_sensor(sens))

    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(sens))
