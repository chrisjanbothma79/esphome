import esphome.codegen as cg
from esphome.components import gpio, spi, spi_device
import esphome.config_validation as cv
from esphome.const import CONF_CHANNEL, CONF_DATA_RATE, CONF_ID, CONF_SPI_ID

CONF_CE_PIN = "ce_pin"
CONF_PA_LEVEL = "pa_level"
CONF_PAYLOAD_SIZE = "payload_size"
CONF_RETRIES = "retries"
CONF_RETRY_DELAY = "delay"
CONF_RETRY_COUNT = "count"
CONF_ADDRESS = "address"

nrf24l01_ns = cg.esphome_ns.namespace("nrf24l01")
NRF24L01 = nrf24l01_ns.class_("NRF24L01", spi_device.SPIDevice, cg.Component)
NRF24L01PALevel = nrf24l01_ns.enum("NRF24L01PALevel")

PA_LEVELS = {
    "low": NRF24L01PALevel.LOW,
    "medium": NRF24L01PALevel.MEDIUM,
    "high": NRF24L01PALevel.HIGH,
    "max": NRF24L01PALevel.MAX,
}


def validate_address(value):
    value = cv.positive_int(value)
    if value > 0xFFFFFFFFFF:
        raise cv.Invalid("Address must be a 5-byte address (max 0xFFFFFFFFFF)")
    return value


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(NRF24L01),
        cv.Required(CONF_CE_PIN): cv.use_id(gpio.GPIOPin),
        cv.Optional(CONF_CHANNEL, default=76): cv.int_range(min=0, max=127),
        cv.Optional(CONF_PA_LEVEL, default="high"): cv.enum(PA_LEVELS, lower=True),
        cv.Optional(CONF_DATA_RATE, default="1mbps"): cv.enum(
            {
                "250kbps": cg.RawExpression("RF24_250KBPS"),
                "1mbps": cg.RawExpression("RF24_1MBPS"),
                "2mbps": cg.RawExpression("RF24_2MBPS"),
            },
            lower=True,
        ),
        cv.Optional(CONF_PAYLOAD_SIZE, default=32): cv.int_range(min=1, max=32),
        cv.Optional(CONF_RETRIES): cv.Schema(
            {
                cv.Optional(CONF_RETRY_DELAY, default=15): cv.int_range(min=0, max=15),
                cv.Optional(CONF_RETRY_COUNT, default=15): cv.int_range(min=0, max=15),
            }
        ),
        cv.Optional(CONF_ADDRESS, default="0x1234567890"): validate_address,
    }
).extend(
    spi_device.spi_device_schema(cs_pin_required=False)
)  # cs_pin is managed by spi_device
CONFIG_SCHEMA = CONFIG_SCHEMA.extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(
        config[CONF_ID],
        cg.new_args(
            config[CONF_CE_PIN],
        ),
    )
    await cg.register_component(var, config)
    await spi_device.register_spi_device(var, config)

    cg.add(var.set_channel(config[CONF_CHANNEL]))
    cg.add(var.set_pa_level(config[CONF_PA_LEVEL]))
    cg.add(var.set_data_rate(config[CONF_DATA_RATE]))
    cg.add(var.set_payload_size(config[CONF_PAYLOAD_SIZE]))
    cg.add(var.set_address(config[CONF_ADDRESS]))

    if CONF_RETRIES in config:
        retries = config[CONF_RETRIES]
        cg.add(var.set_retries(retries[CONF_RETRY_DELAY], retries[CONF_RETRY_COUNT]))
