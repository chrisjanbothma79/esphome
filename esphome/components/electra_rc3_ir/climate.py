import esphome.codegen as cg
from esphome.components import climate_ir
from esphome.const import CONF_ID

AUTO_LOAD = ["climate_ir"]
CODEOWNERS = ["@roygolds"]

electra_rc3_ir_ns = cg.esphome_ns.namespace("electra_rc3_ir")
ElectraRC3IR = electra_rc3_ir_ns.class_("ElectraRC3IR", climate_ir.ClimateIR)

CONFIG_SCHEMA = climate_ir.climate_ir_with_receiver_schema(ElectraRC3IR)

# .extend(
#     {
#         cv.GenerateID(): cv.declare_id(ElectraRC3IR),
#     }
# )


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await climate_ir.register_climate_ir(var, config)
