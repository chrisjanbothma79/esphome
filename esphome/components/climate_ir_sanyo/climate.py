import esphome.codegen as cg
from esphome.components import climate_ir
import esphome.config_validation as cv
from esphome.const import CONF_ID

AUTO_LOAD = ["climate_ir"]

climate_ir_sanyo_ns = cg.esphome_ns.namespace("climate_ir_sanyo")
SanyoIrClimate = climate_ir_sanyo_ns.class_("SanyoIrClimate", climate_ir.ClimateIR)

CONFIG_SCHEMA = climate_ir.CLIMATE_IR_WITH_RECEIVER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(SanyoIrClimate),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await climate_ir.register_climate_ir(var, config)
