import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID

AUTO_LOAD = ["json"]
CODEOWNERS = ["@FredM67"]
DEPENDENCIES = ["uart", "network"]

emontx_ns = cg.esphome_ns.namespace("emontx")
EmonTx = emontx_ns.class_("EmonTx", cg.PollingComponent, uart.UARTDevice)

CONF_EMONTX_ID = "emontx_id"
CONF_TAG_NAME = "tag_name"

CONF_EMONCMS = "emoncms"
CONF_SERVER = "server"
CONF_NODE = "node"
CONF_APIKEY = "apikey"
CONF_HTTP_ID = "http_id"

EMONTX_LISTENER_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_EMONTX_ID): cv.use_id(EmonTx),
        cv.Required(CONF_TAG_NAME): cv.string,
    }
)

# Base schema without EmonCMS
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(EmonTx),
        }
    )
    .extend(cv.polling_component_schema("10s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)


# Conditionally add EmonCMS schema
def validate_emoncms(config):
    from esphome.components import http_request

    if CONF_EMONCMS in config:
        emoncms_schema = cv.Schema(
            {
                cv.Required(CONF_SERVER): cv.url,
                cv.Required(CONF_NODE): cv.string,
                cv.Required(CONF_APIKEY): cv.string,
                cv.Required(CONF_HTTP_ID): cv.use_id(http_request.HttpRequestComponent),
            }
        )
        config[CONF_EMONCMS] = emoncms_schema(config[CONF_EMONCMS])
    return config


# Apply conditional schema
CONFIG_SCHEMA = cv.All(
    CONFIG_SCHEMA.extend(
        {
            cv.Optional(CONF_EMONCMS): cv.Any(dict),
        }
    ),
    validate_emoncms,
)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "emontx",
    baud_rate=115200,
    require_tx=False,
    require_rx=True,
    data_bits=8,
    parity=None,
    stop_bits=1,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    # Set EmonCMS configuration if provided
    if CONF_EMONCMS in config:
        emoncms_config = config[CONF_EMONCMS]
        http_var = await cg.get_variable(emoncms_config[CONF_HTTP_ID])
        cg.add(
            var.set_emoncms_config(
                emoncms_config[CONF_SERVER],
                emoncms_config[CONF_NODE],
                emoncms_config[CONF_APIKEY],
                http_var,
            )
        )
