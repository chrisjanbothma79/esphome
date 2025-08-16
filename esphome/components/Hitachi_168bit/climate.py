import esphome.codegen as cg
from esphome.components import climate_ir
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_MODEL

AUTO_LOAD = ["climate_ir"]
CODEOWNERS = ["@Rodrigoah"]

# Must match C++ namespace and class names
hitachi_ns = cg.esphome_ns.namespace("hitachi_168bit")
HitachiClimate = hitachi_ns.class_("hitachi_168bitClimate", climate_ir.ClimateIR)

Model = hitachi_ns.enum("Model")

MODELS = {
    "DG11J1-91": Model.MODEL_DG11J1_91,
    "DG11J1-3A": Model.MODEL_DG11J1_3A,
}

CONFIG_SCHEMA = climate_ir.CLIMATE_IR_WITH_RECEIVER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(HitachiClimate),
        # keep case as-is; values include a hyphen
        cv.Optional(CONF_MODEL, default="DG11J1-91"): cv.one_of(*MODELS.keys(), lower=False),
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await climate_ir.register_climate_ir(var, config)
    cg.add(var.set_model(MODELS[config[CONF_MODEL]]))
