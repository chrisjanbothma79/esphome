from esphome.automation import Trigger, build_automation, validate_automation
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_TRIGGER_ID,
    PLATFORM_BK72XX,
    PLATFORM_ESP32,
    PLATFORM_ESP8266,
    PLATFORM_LN882X,
    PLATFORM_RTL87XX,
)

CODEOWNERS = ["@anatoly-savchenkov"]

factory_reset_ns = cg.esphome_ns.namespace("factory_reset")
FactoryResetComponent = factory_reset_ns.class_("FactoryResetComponent", cg.Component)
FastBootTrigger = factory_reset_ns.class_("FastBootTrigger", Trigger, cg.Component)

CONF_RESET_AFTER_FAST_POWER_CYCLES = "reset_after_fast_power_cycles"
CONF_MAX_DELAY_BETWEEN_POWER_CYCLES = "max_delay_between_power_cycles"
CONF_ON_INCREMEMT = "on_increment"


def _validate(config):
    if CONF_RESET_AFTER_FAST_POWER_CYCLES in config:
        return cv.only_on(
            [
                PLATFORM_BK72XX,
                PLATFORM_ESP32,
                PLATFORM_ESP8266,
                PLATFORM_RTL87XX,
                PLATFORM_LN882X,
            ]
        )(config)

    elif CONF_ON_INCREMEMT in config:
        raise cv.Invalid(
            f"'{CONF_ON_INCREMEMT}' requires a value for '{CONF_RESET_AFTER_FAST_POWER_CYCLES}'"
        )
    return config


CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(FactoryResetComponent),
            cv.Optional(CONF_MAX_DELAY_BETWEEN_POWER_CYCLES, default="10s"): cv.All(
                cv.positive_time_period_seconds,
                cv.Range(min=cv.TimePeriod(milliseconds=1000)),
            ),
            cv.Optional(CONF_RESET_AFTER_FAST_POWER_CYCLES): cv.positive_not_null_int,
            cv.Optional(CONF_ON_INCREMEMT): validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(FastBootTrigger),
                }
            ),
        }
    ).extend(cv.COMPONENT_SCHEMA),
    _validate,
)


async def to_code(config):
    if reset_count := config.get(CONF_RESET_AFTER_FAST_POWER_CYCLES):
        var = cg.new_Pvariable(
            config[CONF_ID],
            reset_count,
            config[CONF_MAX_DELAY_BETWEEN_POWER_CYCLES].total_milliseconds,
        )
        await cg.register_component(var, config)
        for conf in config.get(CONF_ON_INCREMEMT, []):
            trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
            await build_automation(
                trigger,
                [
                    (cg.uint8, "x"),
                    (cg.uint8, "target"),
                ],
                conf,
            )
