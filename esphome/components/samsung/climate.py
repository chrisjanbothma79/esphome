import esphome.codegen as cg
from esphome.components import climate_ir
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@jorofi"]

AUTO_LOAD = ["climate_ir"]

samsung_ns = cg.esphome_ns.namespace("samsung")
SamsungClimate = samsung_ns.class_("SamsungClimate", climate_ir.ClimateIR)

CONFIG_SCHEMA = climate_ir.climare_ir_with_receiver_schema(SamsungClimate)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    await climate_ir.register_climate_ir(var, config)
