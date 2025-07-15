import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import CONF_ID, ENTITY_CATEGORY_CONFIG, ICON_POWER

from .. import CONF_DEEPSLEEP, DeepSleepComponent, deep_sleep_ns

CODEOWNERS = ["@nielsnl68"]

DeepSleepButton = deep_sleep_ns.class_(
    "DeepSleepButton",
    button.Button,
    cg.Component,
    cg.Parented.template(DeepSleepComponent),
)

CONF_OVERRIDE = "override"

CONFIG_SCHEMA = (
    button.button_schema(
        DeepSleepButton, entity_category=ENTITY_CATEGORY_CONFIG, icon=ICON_POWER
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(
        cv.Schema(
            {
                cv.GenerateID(CONF_DEEPSLEEP): cv.use_id(DeepSleepComponent),
                cv.Optional(CONF_OVERRIDE, default=False): cv.boolean,
            }
        )
    )
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await button.register_button(var, config)

    comp = await cg.get_variable(config[CONF_DEEPSLEEP])
    cg.add(var.set_parent(comp))
    cg.add(var.set_override(config[CONF_OVERRIDE]))
