from esphome import automation, config_validation as cv
from esphome.components.display_menu_base import CONF_LABEL
from esphome.components.lvgl.automation import action_to_code
from esphome.components.lvgl.defines import CONF_OPA, CONF_POINTS, CONF_X, CONF_Y
from esphome.components.lvgl.lv_validation import (
    lv_color,
    opacity,
    pixels_or_percent,
    size,
)
from esphome.components.lvgl.lvcode import LocalVariable, lv, lv_assign
from esphome.components.lvgl.types import LvType, ObjUpdateAction
from esphome.components.lvgl.widgets.img import CONF_IMAGE
from esphome.const import CONF_COLOR, CONF_HEIGHT, CONF_ID, CONF_WIDTH
from esphome.cpp_generator import Literal, MockObj

from ..defines import CONF_MAIN, literal
from ..schemas import POINT_SCHEMA, STYLE_PROPS, STYLE_REMAP
from ..types import WidgetType
from . import Widget, get_widgets

CONF_CANVAS = "canvas"
CONF_BUFFER_ID = "buffer_id"
CONF_USE_ALPHA = "use_alpha"

lv_canvas_t = LvType("lv_canvas_t")


class CanvasType(WidgetType):
    def __init__(self):
        super().__init__(
            CONF_CANVAS,
            lv_canvas_t,
            (CONF_MAIN,),
            cv.Schema(
                {
                    cv.Required(CONF_WIDTH): size,
                    cv.Required(CONF_HEIGHT): size,
                    cv.Optional(CONF_USE_ALPHA, default=False): cv.boolean,
                }
            ),
        )

    def get_uses(self):
        return "img", CONF_IMAGE, CONF_LABEL

    async def to_code(self, w: Widget, config):
        width = config[CONF_WIDTH]
        height = config[CONF_HEIGHT]
        use_alpha = "_ALPHA" if config[CONF_USE_ALPHA] else ""
        lv.canvas_set_buffer(
            w.obj,
            lv.custom_mem_alloc(
                literal(f"LV_CANVAS_BUF_SIZE_TRUE_COLOR{use_alpha}({width}, {height})")
            ),
            width,
            height,
            literal(f"LV_IMG_CF_TRUE_COLOR{use_alpha}"),
        )


canvas_spec = CanvasType()


@automation.register_action(
    "lvgl.canvas.fill",
    ObjUpdateAction,
    cv.Schema(
        {
            cv.GenerateID(CONF_ID): cv.use_id(lv_canvas_t),
            cv.Required(CONF_COLOR): lv_color,
            cv.Optional(CONF_OPA, default="COVER"): opacity,
        },
    ),
)
async def canvas_fill(config, action_id, template_arg, args):
    widget = await get_widgets(config)
    color = await lv_color.process(config[CONF_COLOR])
    opa = await opacity.process(config[CONF_OPA])

    async def do_fill(w: Widget):
        lv.canvas_fill_bg(w.obj, color, opa)

    return await action_to_code(widget, do_fill, action_id, template_arg, args)


@automation.register_action(
    "lvgl.canvas.set_pixels",
    ObjUpdateAction,
    cv.Schema(
        {
            cv.GenerateID(CONF_ID): cv.use_id(lv_canvas_t),
            cv.Required(CONF_COLOR): lv_color,
            cv.Optional(CONF_OPA): opacity,
            cv.Required(CONF_POINTS): cv.ensure_list(POINT_SCHEMA),
        },
    ),
)
async def canvas_set_pixel(config, action_id, template_arg, args):
    widget = await get_widgets(config)
    color = await lv_color.process(config[CONF_COLOR])
    opa = await opacity.process(config.get(CONF_OPA))
    points = [
        (
            await pixels_or_percent.process(p[CONF_X]),
            await pixels_or_percent.process(p[CONF_Y]),
        )
        for p in config[CONF_POINTS]
    ]

    async def do_set_pixels(w: Widget):
        if isinstance(color, MockObj):
            for point in points:
                x, y = point
                lv.canvas_set_px_color(w.obj, x, y, color)
        else:
            with LocalVariable("color", "lv_color_t", modifier="") as color_var:
                lv_assign(color_var, color)
                for point in points:
                    x, y = point
                    lv.canvas_set_px_color(w.obj, x, y, color_var)
        if opa:
            if isinstance(opa, Literal):
                for point in points:
                    x, y = point
                    lv.canvas_set_px_opa(w.obj, x, y, opa)
            else:
                with LocalVariable("opa", "lv_opa_t") as opa_var:
                    lv_assign(opa_var, opa)
                    for point in points:
                        x, y = point
                        lv.canvas_set_px_opa(w.obj, x, y, opa_var)

    return await action_to_code(widget, do_set_pixels, action_id, template_arg, args)


RECT_PROPS = (
    "radius",
    "bg_opa",
    "bg_color",
    "bg_grad",
    "bg_image_src",
    "bg_image_recolor",
    "bg_image_opa",
    "bg_image_recolor_opa",
    "bg_image_tiled",
    "border_color",
    "border_width",
    "border_opa",
    "outline_color",
    "outline_width",
    "outline_pad",
    "outline_opa",
    "shadow_color",
    "shadow_width",
    "shadow_ofs_x",
    "shadow_ofs_y",
    "shadow_spread",
    "shadow_opa",
)


def prop_map(prop):
    return cv.Optional(prop), STYLE_PROPS[prop]


@automation.register_action(
    "lvgl.canvas.draw_rectangle",
    ObjUpdateAction,
    cv.Schema(
        {
            cv.GenerateID(CONF_ID): cv.use_id(lv_canvas_t),
            cv.Required(CONF_X): cv.templatable(cv.int_),
            cv.Required(CONF_Y): cv.templatable(cv.int_),
            cv.Required(CONF_WIDTH): cv.templatable(cv.int_),
            cv.Required(CONF_HEIGHT): cv.templatable(cv.int_),
        },
    ).extend(dict([prop_map(prop) for prop in RECT_PROPS])),
)
async def canvas_draw_rect(config, action_id, template_arg, args):
    widget = await get_widgets(config)
    x = await pixels_or_percent.process(config[CONF_X])
    y = await pixels_or_percent.process(config[CONF_Y])
    width = await pixels_or_percent.process(config[CONF_WIDTH])
    height = await pixels_or_percent.process(config[CONF_HEIGHT])

    async def do_draw_rect(w: Widget):
        with LocalVariable("dsc", "lv_draw_rect_dsc_t", modifier="") as dsc:
            dsc_addr = literal(f"&{dsc}")
            lv.draw_rect_dsc_init(dsc_addr)
            for prop in RECT_PROPS:
                if prop in config:
                    value = await STYLE_PROPS[prop].process(config[prop])
                    mapped_prop = STYLE_REMAP.get(prop, prop)
                    lv_assign(getattr(dsc, mapped_prop), value)
            lv.canvas_draw_rect(w.obj, x, y, width, height, dsc_addr)

    return await action_to_code(widget, do_draw_rect, action_id, template_arg, args)
