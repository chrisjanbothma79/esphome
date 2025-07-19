import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@anatoly-savchenkov"]

factory_reset_ns = cg.esphome_ns.namespace("factory_reset")
FactoryResetComponent = factory_reset_ns.class_("FactoryResetComponent", cg.Component)

CONF_RESET_AFTER_FAST_POWER_CYCLES = "reset_after_fast_power_cycles"
CONF_MAX_DELAY_BETWEEN_POWER_CYCLES = "max_delay_between_power_cycles"

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(FactoryResetComponent),
            cv.Optional(CONF_MAX_DELAY_BETWEEN_POWER_CYCLES, default="10s"): cv.All(
                cv.positive_time_period_seconds,
                cv.Range(min=cv.TimePeriod(milliseconds=1000)),
            ),
            cv.Optional(CONF_RESET_AFTER_FAST_POWER_CYCLES): cv.positive_not_null_int,
        }
    ).extend(cv.COMPONENT_SCHEMA),
)


async def to_code(config):
    if reset_count := config.get(CONF_RESET_AFTER_FAST_POWER_CYCLES):
        var = cg.new_Pvariable(
            config[CONF_ID],
            reset_count,
            config[CONF_MAX_DELAY_BETWEEN_POWER_CYCLES].total_milliseconds,
        )
        await cg.register_component(var, config)
