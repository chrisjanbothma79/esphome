import esphome.codegen as cg
from esphome.components import i2c
from esphome.components.audio_dac import AudioDac
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@P4uLT"]
DEPENDENCIES = ["i2c"]

es8388_ns = cg.esphome_ns.namespace("es8388")
ES8388 = es8388_ns.class_("ES8388", AudioDac, cg.Component, i2c.I2CDevice)

CONF_DAC_OUTPUT = "dac_output"

ES8388_DACOutput = es8388_ns.enum("ES8388_DACOutput")
DAC_OUTPUT = {
    "LINE1": ES8388_DACOutput.DAC_OUTPUT_LINE1,
    "LINE2": ES8388_DACOutput.DAC_OUTPUT_LINE2,
    "BOTH": ES8388_DACOutput.DAC_OUTPUT_BOTH,
}

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ES8388),
            cv.Optional(CONF_DAC_OUTPUT, default="BOTH"): cv.enum(
                DAC_OUTPUT, upper=True, space="_"
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x10))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    cg.add(var.set_dac_output(config[CONF_DAC_OUTPUT]))
