import re

from esphome import pins
import esphome.codegen as cg
from esphome.components import i2c, sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ADDRESS,
    CONF_ENABLE_PIN,
    CONF_HEIGHT,
    CONF_OFFSET_X,
    CONF_OFFSET_Y,
    CONF_TIMEOUT,
    CONF_WIDTH,
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
CONF_REGION_OF_INTEREST = "region_of_interest"
CONF_CENTER_SPAD = "center_spad"

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


def check_dimensions(value):
    if isinstance(value, list):
        if len(value) != 2:
            raise cv.Invalid(f"Dimensions must have a length of two, not {len(value)}")
        try:
            width, height = int(value[0]), int(value[1])
        except ValueError:
            # pylint: disable=raise-missing-from
            raise cv.Invalid("Width and height dimensions must be integers")
        if width < 4 or height < 4:
            raise cv.Invalid("Width and height must at least be 4")
        if width > 16 or height > 16:
            raise cv.Invalid("Width and height must be at most 16")
        return [width, height]
    value = cv.string(value)
    match = re.match(r"\s*([0-9]+)\s*[xX]\s*([0-9]+)\s*", value)
    if not match:
        raise cv.Invalid(
            "Invalid value '{}' for dimensions. Only WIDTHxHEIGHT is allowed."
        )
    return check_dimensions([match.group(1), match.group(2)])


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
            cv.Optional(CONF_REGION_OF_INTEREST): cv.Any(
                check_dimensions,
                cv.Schema(
                    {
                        cv.Required(CONF_WIDTH): cv.int_range(min=4, max=16),
                        cv.Required(CONF_HEIGHT): cv.int_range(min=4, max=16),
                        cv.Optional(CONF_OFFSET_X, default=0): cv.int_range(
                            min=-7, max=8
                        ),
                        cv.Optional(CONF_OFFSET_Y, default=0): cv.int_range(
                            min=-7, max=8
                        ),
                    }
                ),
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

    if CONF_REGION_OF_INTEREST in config:
        dimensions = config[CONF_REGION_OF_INTEREST]
        if isinstance(dimensions, dict):
            # yes, this calculation is very confusing
            # see the comments above apply_region_of_interest in vl53l1x_sensor.cpp
            # for how it maps out. we're pre-mirroring it here
            x = dimensions[CONF_OFFSET_X] + 7
            y = dimensions[CONF_OFFSET_Y] + 7
            if y < 8:
                x = 15 - x
                center_spad = 128 + y + x * 8
            else:
                y = 15 - y
                center_spad = y + x * 8

            cg.add(
                var.set_region_of_interest(
                    dimensions[CONF_WIDTH], dimensions[CONF_HEIGHT]
                )
            )
            cg.add(var.set_region_of_interest_center_spad(center_spad))
        else:
            (width, height) = dimensions
            cg.add(var.set_region_of_interest(width, height))

    await i2c.register_i2c_device(var, config)
