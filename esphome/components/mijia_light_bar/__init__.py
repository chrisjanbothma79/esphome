from esphome import automation
from esphome.components import spi, nrf24, light
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_TRANSITION_LENGTH,
)

DEPENDENCIES = ["nrf24"]
AUTO_LOAD = ["nrf24"]

mijia_lightbar_ns = cg.esphome_ns.namespace("mijia_light_bar")
MijiaLightBarComponent = mijia_lightbar_ns.class_("MijiaLightBarComponent", light.LightOutput)

# Actions
ToggleAction = mijia_lightbar_ns.class_("ToggleAction", automation.Action)

# Configuration constants
CONF_REMOTE_ID = "remote_id"
CONF_REPETITIONS = "repetitions"
CONF_DELAY_MS = "delay_ms"

# Base schema for Mijia-specific settings
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(MijiaLightBarComponent),
        # cv.Optional(nrf24.CONF_CHANNEL, default=68): cv.one_of(6, 7, 15, 16, 43, 44, 68, 69, int=True),
        # cv.Optional(nrf24.CONF_PA_LEVEL, default="low"): cv.enum(nrf24.PA_LEVELS, lower=True),
        # cv.Optional(nrf24.CONF_DATA_RATE, default="2mbps"): cv.enum(nrf24.DATA_RATES, lower=True),

        cv.Optional(CONF_REMOTE_ID, default=0x00000000): cv.hex_uint32_t,
        cv.Optional(CONF_REPETITIONS, default=3): cv.int_range(min=1, max=10),
        cv.Optional(CONF_DELAY_MS, default=20): cv.int_range(min=1, max=100),
}).extend(light.LIGHT_SCHEMA)

async def to_code(config):
    """Generate code for the Mijia Light Bar component."""
    var = cg.new_Pvariable(config[CONF_ID])

    # Register as component first
    await cg.register_component(var, config)

    # Register as light output
    # await light.register_light(var, config)

    # Set fixed Mijia Light Bar values
    cg.add(var.set_payload_size(17))
    cg.add(var.set_crc_length(nrf24.NRF24CRCLength.RF24_CRC_DISABLED))
    cg.add(var.set_auto_ack(False))
    cg.add(var.set_write_address(0x5555555555))

    # Configure Mijia-specific settings
    cg.add(var.set_remote_id(config[CONF_REMOTE_ID]))
    cg.add(var.set_repetitions(config[CONF_REPETITIONS]))
    cg.add(var.set_delay_ms(config[CONF_DELAY_MS]))

@automation.register_action(
    "mijia_light_bar.toggle",
    ToggleAction,
    automation.maybe_simple_id({
        cv.Required(CONF_ID): cv.use_id(MijiaLightBarComponent),
        cv.Optional(CONF_TRANSITION_LENGTH): cv.positive_time_period_milliseconds,
    }),
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
