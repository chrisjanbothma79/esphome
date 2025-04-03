from esphome import pins
import esphome.codegen as cg
from esphome.components import i2c, sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ADDRESS,
    CONF_ENABLE_PIN,
    CONF_TIMEOUT,
    ICON_ARROW_EXPAND_VERTICAL,
    STATE_CLASS_MEASUREMENT,
    UNIT_METER,
)

CODEOWNERS = ["@ccutrer"]
CONFLICTS_WITH = ["vl53l0x"]
DEPENDENCIES = ["i2c"]

vl53l1x_ns = cg.esphome_ns.namespace("vl53l1x")
VL53L1XSensor = vl53l1x_ns.class_(
    "VL53L1XSensor", sensor.Sensor, cg.PollingComponent, i2c.I2CDevice
)

CONF_DISTANCE_MODE = "distance_mode"
CONF_MEASUREMENT_TIMING_BUDGET = "measurement_timing_budget"

DistanceMode = vl53l1x_ns.enum("DistanceMode")
DISTANCE_MODE = {
    "SHORT": DistanceMode.SHORT,
    "MEDIUM": DistanceMode.MEDIUM,
    "LONG": DistanceMode.LONG,
}


def check_keys(obj):
    if obj[CONF_ADDRESS] != 0x29 and CONF_ENABLE_PIN not in obj:
        msg = "Address other then 0x29 requires enable_pin definition to allow sensor\r"
        msg += "re-addressing. Also if you have more then one VL53 device on the same\r"
        msg += "i2c bus, then all VL53 devices must have enable_pin defined."
        raise cv.Invalid(msg)
    return obj


def check_timeout(value):
    value = cv.positive_time_period_microseconds(value)
    if value.total_seconds > 60:
        raise cv.Invalid("Maximum timeout can not be greater than 60 seconds")
    return value


def check_measurement_timing_budget(value):
    value = cv.positive_time_period_microseconds(value)
    if value.total_microseconds <= 20000:
        raise cv.Invalid("Measurement timing budget cannot be less than 20ms")
    if value.total_microseconds > 1000000:
        raise cv.Invalid("Measurement timing budget can not be greater than 1000ms")
    return value


CONFIG_SCHEMA = cv.All(
    sensor.sensor_schema(
        VL53L1XSensor,
        unit_of_measurement=UNIT_METER,
        icon=ICON_ARROW_EXPAND_VERTICAL,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.Optional(CONF_TIMEOUT, default="50ms"): check_timeout,
            cv.Optional(CONF_DISTANCE_MODE, default="long"): cv.enum(
                DISTANCE_MODE, upper=True
            ),
            cv.Optional(
                CONF_MEASUREMENT_TIMING_BUDGET, default="50ms"
            ): check_measurement_timing_budget,
            cv.Optional(CONF_ENABLE_PIN): pins.gpio_output_pin_schema,
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x29)),
    check_keys,
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    cg.add(var.set_timeout_us(config[CONF_TIMEOUT]))
    cg.add(var.set_distance_mode(config[CONF_DISTANCE_MODE]))
    cg.add(var.set_measurement_timing_budget_us(config[CONF_MEASUREMENT_TIMING_BUDGET]))

    if CONF_ENABLE_PIN in config:
        enable = await cg.gpio_pin_expression(config[CONF_ENABLE_PIN])
        cg.add(var.set_enable_pin(enable))

    await i2c.register_i2c_device(var, config)
