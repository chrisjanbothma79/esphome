from esphome import automation
from esphome.components import nrf24, light, spi
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_LIGHT_ID,
    CONF_TRANSITION_LENGTH,
)

DEPENDENCIES = ["spi", "light"]
AUTO_LOAD = ["nrf24"]
# MULTI_CONF = True

mijia_light_bar_ns = cg.esphome_ns.namespace("mijia_light_bar")
MijiaLightBarComponent = mijia_light_bar_ns.class_("MijiaLightBarComponent", nrf24.NRF24Device, light.LightOutput)

# Actions
ToggleAction = mijia_light_bar_ns.class_("ToggleAction", automation.Action)

# Configuration constants
CONF_REMOTE_ID = "remote_id"
CONF_REPETITIONS = "repetitions"
CONF_DELAY_MS = "delay_ms"

# Base schema for Mijia-specific settings
CONFIG_SCHEMA = nrf24.NRF24_DEVICE_SCHEMA.extend(
    {
        cv.GenerateID(CONF_LIGHT_ID): cv.declare_id(MijiaLightBarComponent),
        cv.Optional(nrf24.CONF_CHANNEL, default=68): cv.one_of(6, 7, 15, 16, 43, 44, 68, 69, int=True),
        cv.Optional(nrf24.CONF_PA_LEVEL, default="low"): cv.enum(nrf24.PA_LEVELS, lower=True),
        cv.Optional(nrf24.CONF_RF_DATA_RATE, default="2mbps"): cv.enum(nrf24.DATA_RATES, lower=True),

        cv.Optional(CONF_REMOTE_ID, default=0x00000000): cv.hex_uint32_t,
        cv.Optional(CONF_REPETITIONS, default=3): cv.int_range(min=1, max=10),
        cv.Optional(CONF_DELAY_MS, default=20): cv.int_range(min=1, max=100),
}).extend(light.LIGHT_SCHEMA).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_LIGHT_ID])
    await cg.register_component(var, config)
    await nrf24.register_nrf24_device(var, config)

    # Set fixed Mijia Light Bar nrf24 values
    cg.add(var.set_payload_size(17))
    cg.add(var.set_crc_length(nrf24.NRF24CRCLength.RF24_CRC_DISABLED))
    cg.add(var.set_auto_ack(False))
    cg.add(var.set_write_address(0x5555555555))

    # Configure Mijia-specific settings
    cg.add(var.set_remote_id(config[CONF_REMOTE_ID]))
    cg.add(var.set_repetitions(config[CONF_REPETITIONS]))
    cg.add(var.set_delay_ms(config[CONF_DELAY_MS]))
    await light.register_light(var, config)
