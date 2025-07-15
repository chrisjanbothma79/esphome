import esphome.codegen as cg
from esphome.components import i2c, light
import esphome.config_validation as cv
from esphome.const import CONF_OUTPUT_ID

from .. import mipi_dsi_ns

DsiBacklight = mipi_dsi_ns.class_(
    "DsiBacklight", light.LightOutput, cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(DsiBacklight),
    }
).extend(i2c.i2c_device_schema(0x45))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    await i2c.register_i2c_device(var, config)
