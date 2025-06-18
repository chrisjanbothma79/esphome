import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_TOPIC_PREFIX

AUTO_LOAD = ["json"]
CODEOWNERS = ["@FredM67"]
DEPENDENCIES = ["uart", "network"]

emontx_ns = cg.esphome_ns.namespace("emontx")
EmonTx = emontx_ns.class_("EmonTx", cg.PollingComponent, uart.UARTDevice)

CONF_EMONTX_ID = "emontx_id"
CONF_TAG_NAME = "tag_name"

# EmonCMS config
CONF_EMONCMS = "emoncms"
CONF_SERVER = "server"
CONF_NODE = "node"
CONF_APIKEY = "apikey"
CONF_HTTP_ID = "http_id"

# MQTT forwarding config
CONF_MQTT_FORWARD = "mqtt_forward"

# Base schema without EmonCMS or MQTT
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
            # MQTT forwarding config (simpler than EmonCMS!)
            cv.Optional(CONF_MQTT_FORWARD): cv.Schema(
                {cv.Required(CONF_TOPIC_PREFIX): cv.string}
            ),
            # Keep existing EmonCMS config
            cv.Optional(CONF_EMONCMS): cv.Any(dict),
        }
    )
    .extend(cv.polling_component_schema("10s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)


# Create a reusable function to validate non-empty strings
def not_empty(name):
    def validator(value):
        value = cv.string(value)
        if not value:
            raise cv.Invalid(f"{name} cannot be empty")
        return value

    return validator


# Simple yet effective server URL validation
def validate_server_url(value):
    value = cv.string(value)
    if not value:
        raise cv.Invalid("Server URL cannot be empty")

    # Add https:// prefix if no protocol specified
    if not value.startswith(("http://", "https://")):
        value = "https://" + value

    # Let ESPHome's URL validator handle the rest
    try:
        return cv.url(value)
    except Exception as exc:  # Capture the exception as a variable
        raise cv.Invalid("Please enter a valid server URL") from exc


# Conditionally add EmonCMS schema
def validate_emoncms(config):
    if CONF_EMONCMS in config:
        from esphome.components import http_request

        cg.add_define("USE_HTTP_REQUEST")

        emoncms_schema = cv.Schema(
            {
                cv.Required(CONF_SERVER): validate_server_url,
                cv.Required(CONF_NODE): not_empty("Node name"),
                cv.Required(CONF_APIKEY): not_empty("API key"),
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

    # Set MQTT forwarding if configured
    if CONF_MQTT_FORWARD in config:
        cg.add_define("USE_MQTT_FORWARD")
        # Make sure MQTT component is loaded
        await cg.ensure_linked_dependency("mqtt")
        mqtt_config = config[CONF_MQTT_FORWARD]
        cg.add(var.set_mqtt_forward(mqtt_config[CONF_TOPIC_PREFIX]))

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
