import esphome.config_validation as cv
from esphome.const import CONF_DIRECTION, CONF_HEIGHT, CONF_TYPE, CONF_WIDTH
from esphome.cpp_generator import MockObjClass

from ..defines import (
    CONF_CONTAINER,
    CONF_FLEX_ALIGN_CROSS,
    CONF_FLEX_ALIGN_MAIN,
    CONF_FLEX_ALIGN_TRACK,
    CONF_FLEX_FLOW,
    CONF_FLEX_GROW,
    CONF_LAYOUT,
    CONF_MAIN,
    CONF_OBJ,
    CONF_PAD_COLUMN,
    CONF_PAD_ROW,
    CONF_SCROLLBAR,
    TYPE_FLEX,
)
from ..lv_validation import size
from ..lvcode import lv
from ..schemas import LAYOUTS
from ..types import WidgetType, lv_obj_t

TYPE_VERTICAL = "vertical"
TYPE_HORIZONTAL = "horizontal"

STYLE_BASE = {
    CONF_FLEX_ALIGN_MAIN: "SPACE_EVENLY",
    CONF_FLEX_ALIGN_TRACK: "CENTER",
    CONF_FLEX_ALIGN_CROSS: "STRETCH",
    CONF_FLEX_GROW: 1,
    CONF_PAD_ROW: 0,
    CONF_PAD_COLUMN: 0,
}

FLOWS = {
    TYPE_VERTICAL: "LV_FLEX_FLOW_COLUMN",
    TYPE_HORIZONTAL: "LV_FLEX_FLOW_ROW",
}

FLEX_LAYOUT = LAYOUTS[TYPE_FLEX]
FLEX_OPTIONS = [key.schema for key in FLEX_LAYOUT]


def validate_container(config):
    direction = config[CONF_DIRECTION]
    defaults = STYLE_BASE.copy()
    flow = FLOWS[direction]
    defaults.update({CONF_FLEX_FLOW: flow})
    schema = cv.Schema(
        {
            cv.Optional(CONF_FLEX_FLOW, default=flow): cv.one_of(flow, upper=True),
            cv.Optional(CONF_TYPE, default=TYPE_FLEX): cv.one_of(TYPE_FLEX, lower=True),
            **{
                cv.Optional(key, default=defaults[key]): FLEX_LAYOUT[key]
                for key in STYLE_BASE
            },
        }
    )
    result = config.copy()
    result[CONF_LAYOUT] = schema(config[CONF_LAYOUT])
    return result


CONTAINER_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_DIRECTION): cv.one_of(*FLOWS, lower=True),
        cv.Optional(CONF_LAYOUT, default={CONF_TYPE: TYPE_FLEX}): dict,
        cv.Optional(CONF_HEIGHT, default="100%"): size,
        cv.Optional(CONF_WIDTH, default="100%"): size,
    }
).add_extra(validate_container)


class ContainerType(WidgetType):
    """
    A simple container widget that can hold other widgets. Made from an obj with all styles removed and layout
    added.
    """

    def __init__(self):
        super().__init__(
            CONF_CONTAINER,
            lv_obj_t,
            (CONF_MAIN, CONF_SCROLLBAR),
            schema=CONTAINER_SCHEMA,
            modify_schema={},
            lv_name=CONF_OBJ,
        )
        self.styles = {}

    def on_create(self, var: MockObjClass, config: dict):
        lv.obj_remove_style_all(var)

    async def to_code(self, w, config):
        pass


container_spec = ContainerType()
