import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_CONFIG, ICON_POWER

from .. import CONF_DEEPSLEEP, DeepSleepComponent, deep_sleep_ns

CODEOWNERS = ["@nielsnl68"]

PreventSleepSwitch = deep_sleep_ns.class_(
    "PreventSleepSwitch",
    switch.Switch,
    cg.Component,
    cg.Parented.template(DeepSleepComponent),
)

CONFIG_SCHEMA = (
    switch.switch_schema(
        PreventSleepSwitch,
        icon=ICON_POWER,
        entity_category=ENTITY_CATEGORY_CONFIG,
        block_inverted=True,
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(
        cv.Schema(
            {
                cv.GenerateID(CONF_DEEPSLEEP): cv.use_id(DeepSleepComponent),
            }
        )
    )
)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)

    comp = await cg.get_variable(config[CONF_DEEPSLEEP])
    cg.add(var.set_parent(comp))
