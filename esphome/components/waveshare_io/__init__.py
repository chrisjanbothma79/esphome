from esphome import pins
import esphome.codegen as cg
from esphome.components import i2c
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_INPUT,
    CONF_INVERTED,
    CONF_MODE,
    CONF_NUMBER,
    CONF_OUTPUT,
)

CODEOWNERS = ["@latonita"]

AUTO_LOAD = ["gpio_expander"]
DEPENDENCIES = ["i2c"]
MULTI_CONF = True

waveshare_io_ns = cg.esphome_ns.namespace("waveshare_io")

WaveshareIOComponent = waveshare_io_ns.class_(
    "WaveshareIOComponent", cg.Component, i2c.I2CDevice
)
WaveshareIOGPIOPin = waveshare_io_ns.class_(
    "WaveshareIOGPIOPin", cg.GPIOPin, cg.Parented.template(WaveshareIOComponent)
)

CONF_WAVESHARE_IO = "waveshare_io"
CONF_WAVESHARE_IO_ID = "waveshare_io_id"
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(CONF_ID): cv.declare_id(WaveshareIOComponent),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x24))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)


def validate_mode(value):
    if not (value[CONF_INPUT] or value[CONF_OUTPUT]):
        raise cv.Invalid("Mode must be either input or output")
    if value[CONF_INPUT] and value[CONF_OUTPUT]:
        raise cv.Invalid("Mode must be either input or output")
    return value


WAVESHARE_IO_PIN_SCHEMA = pins.gpio_base_schema(
    WaveshareIOGPIOPin,
    cv.int_range(min=0, max=7),
    modes=[CONF_INPUT, CONF_OUTPUT],
    mode_validator=validate_mode,
    invertible=True,
).extend(
    {
        cv.Required(CONF_WAVESHARE_IO): cv.use_id(WaveshareIOComponent),
    }
)


@pins.PIN_SCHEMA_REGISTRY.register(CONF_WAVESHARE_IO, WAVESHARE_IO_PIN_SCHEMA)
async def waveshare_io_pin_to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    parent = await cg.get_variable(config[CONF_WAVESHARE_IO])

    cg.add(var.set_parent(parent))

    num = config[CONF_NUMBER]
    cg.add(var.set_pin(num))
    cg.add(var.set_inverted(config[CONF_INVERTED]))
    cg.add(var.set_flags(pins.gpio_flags_expr(config[CONF_MODE])))
    return var
