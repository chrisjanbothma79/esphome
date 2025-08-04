import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_SIGNAL_STRENGTH, DEVICE_CLASS_EMPTY
import esphome.final_validate as fv

from .. import (
    CONF_MODEL,
    CONF_MODEM_ID,
    MODEM_COMPONENT_SCHEMA,
    final_validate_platform,
    modem_ns,
)

CODEOWNERS = ["@oarcher"]

AUTO_LOAD = []

DEPENDENCIES = ["modem"]

IS_PLATFORM_COMPONENT = True

CONF_NETWORK_TYPE = "network_type"
CONF_NMEA = "nmea"

MODEM_MODELS_GNSS_QUERY = {
    "SIM7600": {"command": "AT+CGNSSINFO", "parser": "CGNSSINFO16"},
    "SIM7670": {"command": "AT+CGNSSINFO", "parser": "CGNSSINFO18"},
}

ModemTextSensor = modem_ns.class_("ModemTextSensor", cg.PollingComponent)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ModemTextSensor),
            cv.Optional(CONF_NETWORK_TYPE): text_sensor.text_sensor_schema(
                device_class=DEVICE_CLASS_EMPTY,
            ),
            cv.Optional(CONF_SIGNAL_STRENGTH): text_sensor.text_sensor_schema(
                device_class=DEVICE_CLASS_EMPTY,
                icon="mdi:signal",
            ),
            cv.Optional(CONF_NMEA): text_sensor.text_sensor_schema(
                device_class=DEVICE_CLASS_EMPTY,
            ),
        }
    )
    .extend(MODEM_COMPONENT_SCHEMA)
    .extend(cv.polling_component_schema("60s"))
)

CONF_GNSS_COMMAND = "gnss_command"
CONF_GNSS_PARSER = "gnss_parser"


def _final_validate_nmea(config):
    if CONF_NMEA in config:
        fconf = fv.full_config.get()
        modem_path = fconf.get_path_for_id(config[CONF_MODEM_ID])[:-1]
        modem_config = fconf.get_config_for_path(modem_path)
        model = modem_config.get(CONF_MODEL, None)

        if model not in MODEM_MODELS_GNSS_QUERY:
            raise cv.Invalid(
                f"NMEA not supported for modem '{model}'. Supported models: {', '.join(MODEM_MODELS_GNSS_QUERY)}"
            )

        gnss = MODEM_MODELS_GNSS_QUERY[model]
        config[CONF_GNSS_COMMAND] = gnss["command"]
        config[CONF_GNSS_PARSER] = gnss["parser"]

    return config


FINAL_VALIDATE_SCHEMA = cv.All(final_validate_platform, _final_validate_nmea)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    if network_type := config.get(CONF_NETWORK_TYPE, None):
        network_type_text_sensor = await text_sensor.new_text_sensor(network_type)
        cg.add(var.set_network_type_text_sensor(network_type_text_sensor))

    if signal_strength := config.get(CONF_SIGNAL_STRENGTH, None):
        signal_strength_text_sensor = await text_sensor.new_text_sensor(signal_strength)
        cg.add(var.set_signal_strength_text_sensor(signal_strength_text_sensor))

    if nmea := config.get(CONF_NMEA, None):
        nmea_text_sensor = await text_sensor.new_text_sensor(nmea)
        cg.add(var.set_nmea_text_sensor(nmea_text_sensor))
        cg.add(var.set_gnss_command(config[CONF_GNSS_COMMAND]))
        parser_flag = f"USE_MODEM_GNSS_PARSER_{config[CONF_GNSS_PARSER].upper()}"
        cg.add_define(parser_flag)
    await cg.register_component(var, config)
