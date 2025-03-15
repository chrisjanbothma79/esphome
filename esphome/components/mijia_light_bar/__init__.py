from esphome import automation, pins
from esphome.components import spi
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_TRANSITION_LENGTH,

)

DEPENDENCIES = ["spi"]

mijia_lightbar_ns = cg.esphome_ns.namespace("mijia_light_bar")
spi_device = mijia_lightbar_ns.class_("MijiaLightBarComponent", cg.Component, spi.SPIDevice)

ToggleAction = mijia_lightbar_ns.class_("ToggleAction", automation.Action)

CONF_CE_PIN_KEY = 'ce_pin'

CONFIG_SCHEMA = cv.Schema({
  cv.GenerateID(CONF_ID): cv.declare_id(spi_device),
  cv.Required(CONF_CE_PIN_KEY): pins.gpio_output_pin_schema,
}).extend(spi.spi_device_schema(True, "1MHz"))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    pin = await cg.gpio_pin_expression(config[CONF_CE_PIN_KEY])
    cg.add(var.set_ce_pin(pin))
    await spi.register_spi_device(var, config)

@automation.register_action(
    "mijia_light_bar.toggle",
    ToggleAction,
    automation.maybe_simple_id(
        {
            cv.Required(CONF_ID): cv.use_id(spi_device),
            cv.Optional(CONF_TRANSITION_LENGTH): cv.templatable(
                cv.positive_time_period_milliseconds
            ),
        }
    ),
)
async def light_toggle_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    if CONF_TRANSITION_LENGTH in config:
        template_ = await cg.templatable(
            config[CONF_TRANSITION_LENGTH], args, cg.uint32
        )
        cg.add(var.set_transition_length(template_))
    return var
