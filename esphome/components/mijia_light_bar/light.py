import esphome.codegen as cg
from esphome.components import light
import esphome.config_validation as cv
from esphome.const import CONF_ID
from . import MijiaLightBarComponent

DEPENDENCIES = ["mijia_light_bar"]

CONFIG_SCHEMA = light.LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.use_id(MijiaLightBarComponent),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_ID])
