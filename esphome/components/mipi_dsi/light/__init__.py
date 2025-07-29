import esphome.codegen as cg
from esphome.components import i2c, light
from esphome.components.light import LIGHT_STATE_SCHEMA, RESTORE_MODES
import esphome.config_validation as cv
from esphome.const import (
    CONF_BRIGHTNESS,
    CONF_DEFAULT_TRANSITION_LENGTH,
    CONF_GAMMA_CORRECT,
    CONF_INITIAL_STATE,
    CONF_OUTPUT_ID,
    CONF_RESTORE_MODE,
)

from .. import mipi_dsi_ns

DsiBacklight = mipi_dsi_ns.class_(
    "DsiBacklight", light.LightOutput, cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(DsiBacklight),
        cv.Optional(CONF_RESTORE_MODE, default="RESTORE_DEFAULT_ON"): cv.enum(
            RESTORE_MODES, upper=True, space="_"
        ),
        cv.Optional(CONF_GAMMA_CORRECT, default=2.0): cv.positive_float,
        cv.Optional(
            CONF_DEFAULT_TRANSITION_LENGTH, default="0s"
        ): cv.positive_time_period_milliseconds,
        cv.Optional(
            CONF_INITIAL_STATE, default={CONF_BRIGHTNESS: 0.5}
        ): LIGHT_STATE_SCHEMA,
    }
).extend(i2c.i2c_device_schema(0x45))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    await i2c.register_i2c_device(var, config)
