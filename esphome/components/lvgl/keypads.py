from esphome import automation, codegen as cg
from esphome.components.binary_sensor import BinarySensor
import esphome.config_validation as cv
from esphome.const import CONF_GROUP, CONF_ID

from .defines import (
    CONF_ENCODERS,
    CONF_INITIAL_FOCUS,
    CONF_KEYPADS,
    CONF_LONG_PRESS_REPEAT_TIME,
    CONF_LONG_PRESS_TIME,
    literal,
)
from .encoders import set_group_to_code as encoders_set_group_to_code
from .helpers import lvgl_components_required
from .lvcode import lv
from .schemas import ENCODER_SCHEMA, set_group_schema
from .types import LvglAction, lv_indev_type_t

KEYPAD_KEYS = (
    "up",
    "down",
    "right",
    "left",
    "esc",
    "del",
    "backspace",
    "enter",
    "next",
    "prev",
    "home",
    "end",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "#",
    "*",
)

KEYPADS_CONFIG = cv.ensure_list(
    ENCODER_SCHEMA.extend(
        {cv.Optional(key): cv.use_id(BinarySensor) for key in KEYPAD_KEYS}
    )
)


async def keypads_to_code(var, config, default_group):
    for enc_conf in config[CONF_KEYPADS]:
        lvgl_components_required.add("KEY_LISTENER")
        lpt = enc_conf[CONF_LONG_PRESS_TIME].total_milliseconds
        lprt = enc_conf[CONF_LONG_PRESS_REPEAT_TIME].total_milliseconds
        listener = cg.new_Pvariable(
            enc_conf[CONF_ID], lv_indev_type_t.LV_INDEV_TYPE_KEYPAD, lpt, lprt
        )
        await cg.register_parented(listener, var)
        for key in [x for x in enc_conf if x in KEYPAD_KEYS]:
            b_sensor = await cg.get_variable(enc_conf[key])
            cg.add(listener.add_button(b_sensor, literal(f"LV_KEY_{key.upper()}")))

        if group := enc_conf.get(CONF_GROUP):
            group = await cg.get_variable(group)
        else:
            group = default_group
        cg.add(listener.set_group(group))


async def initial_focus_to_code(config):
    for enc_conf in config[CONF_ENCODERS]:
        if default_focus := enc_conf.get(CONF_INITIAL_FOCUS):
            obj = await cg.get_variable(default_focus)
            lv.group_focus_obj(obj)


@automation.register_action("lvgl.keypad.set_group", LvglAction, set_group_schema())
async def set_group_to_code(config, action_id, template_arg, args):
    return await encoders_set_group_to_code(config, action_id, template_arg, args)
