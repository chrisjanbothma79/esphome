import esphome.codegen as cg
from esphome.components import output
import esphome.config_validation as cv
from esphome.const import CONF_ID

from .. import CONF_WAVESHARE_IO_ID, WaveshareIOComponent, waveshare_io_ns

DEPENDENCIES = ["waveshare_io"]

WaveshareIOOutput = waveshare_io_ns.class_(
    "WaveshareIOOutput", output.FloatOutput, cg.Parented.template(WaveshareIOComponent)
)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(WaveshareIOOutput),
        cv.GenerateID(CONF_WAVESHARE_IO_ID): cv.use_id(WaveshareIOComponent),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    await cg.register_parented(var, config[CONF_WAVESHARE_IO_ID])
