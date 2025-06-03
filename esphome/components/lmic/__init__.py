"""ESPHome LoRa component."""

import logging
from typing import Any

import esphome.codegen as cg

# from esphome.components import sensor
from esphome.components.lora import CONF_LORA_ID, LORA_SCHEMA
import esphome.config_validation as cv
from esphome.const import (
    # CONF_BATTERY_LEVEL,
    CONF_ID,
    # CONF_MAX_VALUE,
    # CONF_MIN_VALUE,
    # CONF_SENSOR,
)

CODEOWNERS = ["@dala318"]
DEPENDENCIES = ["lora"]

lmic_ns = cg.esphome_ns.namespace("lmic")
LMICComponent = lmic_ns.class_("LMICComponent", cg.Component)

MULTI_CONF = False  # Static object pointer in callbacks prevent multiple instances

DOMAIN = "lmic"

CONF_LMIC_ID = "lmic_id"

CONF_APP_KEY = "app_key"
CONF_DEV_EUI = "dev_eui"
CONF_JOIN_EUI = "join_eui"
CONF_GEN_APP_KEY = "gen_app_key"
# CONF_PERIODICAL_UPLINK_DELAY = "periodical_uplink_delay"
# CONF_AFTER_JOIN_DELAY = "after_join_delay"

_LOGGER = logging.getLogger(__name__)

CONFIG_SCHEMA = cv.All(
    cv.only_with_arduino,
    cv.require_framework_version(esp32_arduino=cv.Version(0, 0, 0)),
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(LMICComponent),
            cv.Required(CONF_APP_KEY): cv.All(
                cv.ensure_list(cv.hex_uint8_t), cv.Length(min=16, max=16)
            ),
            cv.Required(CONF_DEV_EUI): cv.All(
                cv.ensure_list(cv.hex_uint8_t), cv.Length(min=8, max=8)
            ),
            cv.Required(CONF_JOIN_EUI): cv.All(
                cv.ensure_list(cv.hex_uint8_t), cv.Length(min=8, max=8)
            ),
            cv.Optional(CONF_GEN_APP_KEY): cv.All(
                cv.ensure_list(cv.hex_uint8_t), cv.Length(min=16, max=16)
            ),
            # cv.Optional(
            #     CONF_PERIODICAL_UPLINK_DELAY, default="60s"
            # ): cv.positive_time_period_seconds,
            # cv.Optional(
            #     CONF_AFTER_JOIN_DELAY, default="60s"
            # ): cv.positive_time_period_seconds,
            # cv.Optional(CONF_BATTERY_LEVEL): cv.Any(
            #     cv.use_id(sensor.Sensor),
            #     cv.Schema(
            #         {
            #             cv.Required(CONF_SENSOR): cv.use_id(sensor.Sensor),
            #             cv.Optional(CONF_MIN_VALUE): cv.float_,
            #             cv.Optional(CONF_MAX_VALUE): cv.float_,
            #         }
            #     ),
            # ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(LORA_SCHEMA),
)


async def to_code(config: dict[str, Any]):
    cg.add_library(
        "Arduino-LMIC000", "v5.0.1", "https://github.com/mcci-catena/arduino-lmic"
    )
    # cg.add_build_flag("-DTRANSPARENT_RADIO")

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    lora_var = await cg.get_variable(config[CONF_LORA_ID])
    cg.add(var.set_parent(lora_var))

    cg.add(var.set_app_key(config[CONF_APP_KEY]))
    cg.add(var.set_dev_eui(config[CONF_DEV_EUI]))
    cg.add(var.set_join_eui(config[CONF_JOIN_EUI]))
    if CONF_GEN_APP_KEY in config:
        cg.add(var.set_gen_app_key(config[CONF_GEN_APP_KEY]))
    # cg.add(
    #     var.set_periodicity(
    #         config[CONF_PERIODICAL_UPLINK_DELAY], config[CONF_AFTER_JOIN_DELAY]
    #     )
    # )
    # if battery_config := config.get(CONF_BATTERY_LEVEL):
    #     if isinstance(battery_config, dict) and CONF_SENSOR in battery_config:
    #         battery_sensor = await cg.get_variable(battery_config[CONF_SENSOR])
    #         cg.add(var.set_battery_level_sensor(battery_sensor))
    #         cg.add(
    #             var.set_battery_level_min_max(
    #                 battery_config.get(CONF_MIN_VALUE, 0),
    #                 battery_config.get(CONF_MAX_VALUE, 100),
    #             )
    #         )
    #     else:
    #         battery_sensor = await cg.get_variable(battery_config)
    #         cg.add(var.set_battery_level_sensor(battery_sensor))
    #         cg.add(var.set_battery_level_min_max(0, 100))
