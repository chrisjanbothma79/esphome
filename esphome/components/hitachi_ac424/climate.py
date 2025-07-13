import esphome.codegen as cg
from esphome.components import climate_ir
import esphome.config_validation as cv

AUTO_LOAD = ["climate_ir"]

hitachi_ac424_ns = cg.esphome_ns.namespace("hitachi_ac424")
HitachiClimate = hitachi_ac424_ns.class_("HitachiClimate", climate_ir.ClimateIR)

CONF_INTERNAL_CLEANING = "internal_cleaning"
CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(HitachiClimate).extend(
    {
        cv.Optional(CONF_INTERNAL_CLEANING, default=False): cv.boolean,
    }
)


async def to_code(config):
    var = await climate_ir.new_climate_ir(config)

    cg.add(var.set_internal_cleaning(config[CONF_INTERNAL_CLEANING]))
