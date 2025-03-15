from esphome import automation, pins
from esphome.components import spi, nrf24
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_ID,
    CONF_TRANSITION_LENGTH,
)

DEPENDENCIES = ["nrf24"]
AUTO_LOAD = ["nrf24"]

mijia_lightbar_ns = cg.esphome_ns.namespace("mijia_light_bar")
MijiaLightBarComponent = mijia_lightbar_ns.class_("MijiaLightBarComponent", nrf24.NRF24Component)

# Actions
ToggleAction = mijia_lightbar_ns.class_("ToggleAction", automation.Action)

# Configuration constants
CONF_REMOTE_ID = "remote_id"
CONF_REPETITIONS = "repetitions"
CONF_DELAY_MS = "delay_ms"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(MijiaLightBarComponent),
    cv.Optional(CONF_REMOTE_ID, default=0x00000000): cv.hex_uint32_t,
    cv.Optional(CONF_REPETITIONS, default=3): cv.int_range(min=1, max=10),
    cv.Optional(CONF_DELAY_MS, default=20): cv.int_range(min=1, max=100),
}).extend(nrf24.CONFIG_SCHEMA.schema)

# Override nRF24 defaults with hardcoded values specific to Mijia Light Bar
CONFIG_SCHEMA = CONFIG_SCHEMA.extend({
    cv.Optional(nrf24.CONF_CHANNEL, default=68): cv.one_of(6, 7, 15, 16, 43, 44, 68, 69, int=True),
    # These values are fixed for the Mijia Light Bar protocol
    cv.Optional(nrf24.CONF_PAYLOAD_SIZE, default=17): cv.remove,
    cv.Optional(nrf24.CONF_CRC, default="disabled"): cv.remove,
    cv.Optional(nrf24.CONF_AUTO_ACK, default=False): cv.remove,
    cv.Optional(nrf24.CONF_WRITE_ADDRESS, default=0x5555555555): cv.remove,
    cv.Optional(nrf24.CONF_READ_PIPES): cv.remove,
})

# Apply the hardcoded values during component registration
async def register_nrf24(var, config):
    await nrf24.register_spi_device(var, config)

    # Set CE pin
    ce_pin = await cg.gpio_pin_expression(config[nrf24.CONF_CE_PIN])
    cg.add(var.set_ce_pin(ce_pin))

    cg.add(var.set_channel(config[nrf24.CONF_CHANNEL]))
    cg.add(var.set_data_rate(config[nrf24.CONF_DATA_RATE]))
    cg.add(var.set_pa_level(config[nrf24.CONF_PA_LEVEL]))

    # Set hardcoded values required by Mijia Light Bar
    cg.add(var.set_payload_size(17))
    cg.add(var.set_crc_length(nrf24.NRF24CRCLength.RF24_CRC_DISABLED))
    cg.add(var.set_auto_ack(False))
    cg.add(var.set_write_address(0x5555555555))

    # Apply any remaining user-configurable options
    if nrf24.CONF_RETRIES in config:
        retries = config[nrf24.CONF_RETRIES]
        cg.add(var.set_retries(retries[nrf24.CONF_RETRY_DELAY], retries[nrf24.CONF_RETRY_COUNT]))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await nrf24.register_nrf24(var, config)

    # Configure Mijia-specific settings
    cg.add(var.set_remote_id(config[CONF_REMOTE_ID]))
    cg.add(var.set_repetitions(config[CONF_REPETITIONS]))
    cg.add(var.set_delay_ms(config[CONF_DELAY_MS]))

@automation.register_action(
    "mijia_light_bar.toggle",
    ToggleAction,
    automation.maybe_simple_id(
        {
            cv.Required(CONF_ID): cv.use_id(MijiaLightBarComponent),
            cv.Optional(CONF_TRANSITION_LENGTH): cv.positive_time_period_milliseconds,
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
