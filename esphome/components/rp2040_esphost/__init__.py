import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components.spi import (
    CONF_INTERFACE_INDEX,
    SPIComponent,
    SPIDataRate,
)
from esphome.const import CONF_CS_PIN, CONF_DATA_RATE, CONF_RESET_PIN, CONF_SPI_ID
from esphome.core import CORE

DEPENDENCIES = ["spi"]
CODEOWNERS = ["@kuba2k2"]

CONF_HANDSHAKE_PIN = "handshake_pin"
CONF_DATA_READY_PIN = "data_ready_pin"


ESPHOST_DATA_RATE_OPTIONS = {
    10e6: SPIDataRate.DATA_RATE_10MHZ,
    8e6: SPIDataRate.DATA_RATE_8MHZ,
    5e6: SPIDataRate.DATA_RATE_5MHZ,
    4e6: SPIDataRate.DATA_RATE_4MHZ,
    2e6: SPIDataRate.DATA_RATE_2MHZ,
    1e6: SPIDataRate.DATA_RATE_1MHZ,
}

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_SPI_ID): cv.use_id(SPIComponent),
        cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
        cv.Required(CONF_HANDSHAKE_PIN): pins.gpio_input_pin_schema,
        cv.Required(CONF_DATA_READY_PIN): pins.gpio_input_pin_schema,
        cv.Required(CONF_RESET_PIN): pins.gpio_output_pin_schema,
        cv.Optional(CONF_DATA_RATE, default="1MHz"): cv.All(
            cv.frequency, cv.enum(ESPHOST_DATA_RATE_OPTIONS)
        ),
    }
)


async def to_code(config):
    parent = config[CONF_SPI_ID]
    parent_path = CORE.config.get_path_for_id(parent)
    spi_config = CORE.config.get_config_for_path(parent_path[:-1])

    spi_interface = spi_config[CONF_INTERFACE_INDEX]
    cs_pin = config[CONF_CS_PIN]["number"]
    handshake_pin = config[CONF_HANDSHAKE_PIN]["number"]
    data_ready_pin = config[CONF_DATA_READY_PIN]["number"]
    reset_pin = config[CONF_RESET_PIN]["number"]
    data_rate_mhz = int(config[CONF_DATA_RATE] / 1e6)

    cg.add_define("USE_RP2040_ESPHOST")
    cg.add_build_flag(f"-DESPHOSTSPI=SPI{spi_interface}")
    cg.add_build_flag(f"-DESPHOST_CS={cs_pin}")
    cg.add_build_flag(f"-DESPHOST_HANDSHAKE={handshake_pin}")
    cg.add_build_flag(f"-DESPHOST_DATA_READY={data_ready_pin}")
    cg.add_build_flag(f"-DESPHOST_RESET={reset_pin}")
    cg.add_build_flag(f"-DESPHOSTSPI_MHZ={data_rate_mhz}")
