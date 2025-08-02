import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_DIRECTION, CONF_TYPE

from ..defines import (
    CONF_CONTAINER,
    CONF_FLEX_ALIGN_CROSS,
    CONF_FLEX_ALIGN_MAIN,
    CONF_FLEX_ALIGN_TRACK,
    CONF_FLEX_FLOW,
    CONF_LAYOUT,
    CONF_MAIN,
    CONF_SCROLLBAR,
    FLEX_FLOWS,
    TYPE_FLEX,
)
from ..helpers import add_lv_use
from ..lvcode import LV, lv
from ..schemas import LAYOUTS
from ..styles import create_style
from ..types import WidgetType, lv_obj_t

TYPE_VERTICAL = "vertical"
TYPE_HORIZONTAL = "horizontal"

STYLE_BASE = {
    CONF_TYPE: TYPE_FLEX,
    CONF_FLEX_ALIGN_MAIN: str(LV.FLEX_ALIGNMENTS_SPACE_EVENLY),
    CONF_FLEX_ALIGN_TRACK: str(LV.FLEX_ALIGNMENTS_CENTER),
    CONF_FLEX_ALIGN_CROSS: str(LV.FLEX_ALIGNMENTS_CENTER),
}
STYLE_VERTICAL = {
    CONF_FLEX_FLOW: FLEX_FLOWS.process("COLUMN"),
    **STYLE_BASE,
}
STYLE_HORIZONTAL = {
    CONF_FLEX_FLOW: FLEX_FLOWS.process("ROW"),
    **STYLE_BASE,
}

CONTAINER_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_DIRECTION): cv.one_of(
            TYPE_VERTICAL,
            TYPE_HORIZONTAL,
            lower=True,
        ),
        cv.Optional(CONF_LAYOUT): LAYOUTS[TYPE_FLEX],
    }
)


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
        )
        self._vertical_style = None
        self._horizontal_style = None

    @property
    def vertical_style(self):
        if self._vertical_style is None:
            self._vertical_style = create_style(
                STYLE_VERTICAL, "_lv_container_vertical_style"
            )
        return self._vertical_style

    @property
    def horizontal_style(self):
        if self._horizontal_style is None:
            self._horizontal_style = create_style(
                STYLE_HORIZONTAL, "_lv_container_horizontal_style"
            )
        return self._horizontal_style

    async def to_code(self, w, config):
        add_lv_use(TYPE_FLEX)
        if config[CONF_DIRECTION] == TYPE_VERTICAL:
            flex = self.vertical_style
        else:
            flex = self.horizontal_style
        cg.add(lv.obj_remove_style_all(w.obj))
        cg.add(lv.obj_add_style(w.obj, flex))
        if layout := config[CONF_LAYOUT]:
            flex.update(layout)
        cg.add(lv.obj_set_layout(w.obj, LV.LAYOUT_FLEX))


container_spec = ContainerType()
