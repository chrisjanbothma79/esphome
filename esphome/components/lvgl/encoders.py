from esphome import automation, codegen as cg
from esphome.components.binary_sensor import BinarySensor
from esphome.components.rotary_encoder.sensor import RotaryEncoderSensor
import esphome.config_validation as cv
from esphome.const import CONF_GROUP, CONF_ID, CONF_SENSOR

from .defines import (
    CONF_ENCODERS,
    CONF_ENTER_BUTTON,
    CONF_INITIAL_FOCUS,
    CONF_LEFT_BUTTON,
    CONF_LONG_PRESS_REPEAT_TIME,
    CONF_LONG_PRESS_TIME,
    CONF_LVGL_ID,
    CONF_RIGHT_BUTTON,
)
from .helpers import lvgl_components_required, requires_component
from .lvcode import LVGL_COMP_ARG, LambdaContext, add_line_marks, lv, lv_add
from .schemas import ENCODER_SCHEMA, SET_GROUP_ACTION_SCHEMA
from .types import LvglAction, lv_indev_type_t, lv_key_t
from .widgets import get_widgets

ENCODERS_CONFIG = cv.ensure_list(
    ENCODER_SCHEMA.extend(
        {
            cv.Required(CONF_ENTER_BUTTON): cv.use_id(BinarySensor),
            cv.Required(CONF_SENSOR): cv.Any(
                cv.All(
                    cv.use_id(RotaryEncoderSensor), requires_component("rotary_encoder")
                ),
                cv.Schema(
                    {
                        cv.Required(CONF_LEFT_BUTTON): cv.use_id(BinarySensor),
                        cv.Required(CONF_RIGHT_BUTTON): cv.use_id(BinarySensor),
                    }
                ),
            ),
        }
    )
)


async def encoders_to_code(var, config, default_group):
    for enc_conf in config[CONF_ENCODERS]:
        lvgl_components_required.add("KEY_LISTENER")
        lpt = enc_conf[CONF_LONG_PRESS_TIME].total_milliseconds
        lprt = enc_conf[CONF_LONG_PRESS_REPEAT_TIME].total_milliseconds
        listener = cg.new_Pvariable(
            enc_conf[CONF_ID], lv_indev_type_t.LV_INDEV_TYPE_ENCODER, lpt, lprt
        )
        await cg.register_parented(listener, var)
        if sensor_config := enc_conf.get(CONF_SENSOR):
            if isinstance(sensor_config, dict):
                b_sensor = await cg.get_variable(sensor_config[CONF_LEFT_BUTTON])
                cg.add(listener.add_button(b_sensor, lv_key_t.LV_KEY_LEFT))
                b_sensor = await cg.get_variable(sensor_config[CONF_RIGHT_BUTTON])
                cg.add(listener.add_button(b_sensor, lv_key_t.LV_KEY_RIGHT))
            else:
                sensor_config = await cg.get_variable(sensor_config)
                lv_add(listener.set_sensor(sensor_config))
        b_sensor = await cg.get_variable(enc_conf[CONF_ENTER_BUTTON])
        cg.add(listener.add_button(b_sensor, lv_key_t.LV_KEY_ENTER))

        group = (
            await cg.get_variable(enc_conf[CONF_GROUP])
            if CONF_GROUP in enc_conf
            else default_group
        )
        cg.add(listener.set_group(group))


async def encoder_initial_focus_to_code(config):
    for enc_conf in config[CONF_ENCODERS]:
        if default_focus := enc_conf.get(CONF_INITIAL_FOCUS):
            widget = await get_widgets(default_focus)
            lv.group_focus_obj(widget[0].obj)


@automation.register_action(
    "lvgl.encoder.set_group", LvglAction, SET_GROUP_ACTION_SCHEMA
)
async def set_group_to_code(config, action_id, template_arg, args):
    listener = await cg.get_variable(config[CONF_ID])
    group = await cg.get_variable(config[CONF_GROUP])
    async with LambdaContext(LVGL_COMP_ARG) as context:
        add_line_marks(action_id)
        lv_add(listener.set_group(group))
    var = cg.new_Pvariable(action_id, template_arg, await context.get_lambda())
    await cg.register_parented(var, config[CONF_LVGL_ID])
    return var
