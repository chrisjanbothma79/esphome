import esphome.codegen as cg
from esphome.components import climate_ir
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_MODEL

AUTO_LOAD = ["climate_ir"]
CODEOWNERS = ["@Rodrigoah"]

# Must match C++: namespace esphome::hitachi_168bit { class Hitachi168bitClimate ... }
hitachi_ns = cg.esphome_ns.namespace("hitachi_168bit")
Hitachi168bitClimate = hitachi_ns.class_("Hitachi168bitClimate", climate_ir.ClimateIR)
Model = hitachi_ns.enum("Model")

MODEL_MAP = {
    "DG11J1-91": Model.MODEL_DG11J1_91,
    "DG11J1-3A": Model.MODEL_DG11J1_3A,
}

CONFIG_SCHEMA = climate_ir.CLIMATE_IR_WITH_RECEIVER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(Hitachi168bitClimate),
        cv.Optional(CONF_MODEL, default="DG11J1-91"): cv.one_of(
            *MODEL_MAP.keys(), lower=False
        ),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await climate_ir.register_climate_ir(var, config)
    cg.add(var.set_model(MODEL_MAP[config[CONF_MODEL]]))
