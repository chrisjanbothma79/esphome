import re

from esphome.components.lvgl.defines import (
    CONF_FLEX_ALIGN_CROSS,
    CONF_FLEX_ALIGN_MAIN,
    CONF_FLEX_ALIGN_TRACK,
    CONF_FLEX_FLOW,
    CONF_FLEX_GROW,
    CONF_GRID_CELL_COLUMN_POS,
    CONF_GRID_CELL_COLUMN_SPAN,
    CONF_GRID_CELL_ROW_POS,
    CONF_GRID_CELL_ROW_SPAN,
    CONF_GRID_CELL_X_ALIGN,
    CONF_GRID_CELL_Y_ALIGN,
    CONF_GRID_COLUMN_ALIGN,
    CONF_GRID_COLUMNS,
    CONF_GRID_ROW_ALIGN,
    CONF_GRID_ROWS,
    CONF_LAYOUT,
    CONF_PAD_COLUMN,
    CONF_PAD_ROW,
    CONF_WIDGETS,
    FLEX_FLOWS,
    LV_FLEX_CROSS_ALIGNMENTS,
    TYPE_FLEX,
    TYPE_GRID,
    TYPE_NONE,
)
from esphome.components.lvgl.lv_validation import padding, size
from esphome.components.lvgl.schemas import (
    FLEX_OBJ_SCHEMA,
    GRID_CELL_SCHEMA,
    flex_alignments,
    grid_alignments,
    grid_spec,
)
import esphome.config_validation as cv
from esphome.const import CONF_HEIGHT, CONF_TYPE, CONF_WIDTH


class Layout:
    """
    Define properties for a layout
    The base class is layout "none"
    """

    _GRID_LAYOUT_REGEX = re.compile(r"^\s*(\d+)\s*x\s*(\d+)\s*$")

    @classmethod
    def get_type(cls):
        return TYPE_NONE

    @classmethod
    def layout_schema(cls, config: dict):
        """
        Get the schema for this layout to validate the `layout:` key data
        """
        return

    @classmethod
    def child_schema(cls, config: dict):
        """
        Get additional options for child object in the layout
        :return:
        """
        return {}

    @classmethod
    def validate(cls, config):
        """
        Validate the layout configuration. This is called late in the schema validation
        :param config: The input configuration
        :return: The validated configuration
        """
        return config


class FlexLayout(Layout):
    @classmethod
    def get_type(cls):
        return TYPE_FLEX

    @classmethod
    def layout_schema(cls, config: dict):
        layout = config.get(CONF_LAYOUT)
        if isinstance(layout, str):
            if str.lower(layout) == TYPE_FLEX:
                return TYPE_FLEX
            # Not a valid flex layout string
            return None

        if not isinstance(layout, dict) or layout.get(CONF_TYPE) != TYPE_FLEX:
            return None
        return {
            cv.Required(CONF_TYPE): cv.one_of(TYPE_FLEX, lower=True),
            cv.Optional(CONF_FLEX_FLOW, default="row_wrap"): FLEX_FLOWS.one_of,
            cv.Optional(CONF_FLEX_ALIGN_MAIN, default="start"): flex_alignments,
            cv.Optional(
                CONF_FLEX_ALIGN_CROSS, default="start"
            ): LV_FLEX_CROSS_ALIGNMENTS.one_of,
            cv.Optional(CONF_FLEX_ALIGN_TRACK, default="start"): flex_alignments,
            cv.Optional(CONF_PAD_ROW): padding,
            cv.Optional(CONF_PAD_COLUMN): padding,
            cv.Optional(CONF_FLEX_GROW): cv.int_,
        }

    @classmethod
    def child_schema(cls, config: dict):
        return FLEX_OBJ_SCHEMA

    @classmethod
    def validate(cls, config):
        """
        Perform validation on the container and its children for this layout
        :param config:
        :return:
        """
        return config


class GridLayout(Layout):
    @classmethod
    def get_type(cls):
        return TYPE_GRID

    @classmethod
    def layout_schema(cls, config: dict):
        layout = config.get(CONF_LAYOUT)
        if isinstance(layout, str):
            match = Layout._GRID_LAYOUT_REGEX.match(layout)
            if match:
                return cv.string
            # Not a valid grid layout string
            return None

        if not isinstance(layout, dict) or layout.get(CONF_TYPE) != TYPE_GRID:
            return None
        return {
            cv.Required(CONF_TYPE): cv.one_of(TYPE_GRID, lower=True),
            cv.Required(CONF_GRID_ROWS): [grid_spec],
            cv.Required(CONF_GRID_COLUMNS): [grid_spec],
            cv.Optional(CONF_GRID_COLUMN_ALIGN): grid_alignments,
            cv.Optional(CONF_GRID_ROW_ALIGN): grid_alignments,
            cv.Optional(CONF_PAD_ROW): padding,
            cv.Optional(CONF_PAD_COLUMN): padding,
        }

    @classmethod
    def child_schema(cls, config: dict):
        return {
            cv.Optional(CONF_GRID_CELL_ROW_POS): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_COLUMN_POS): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_ROW_SPAN, default=1): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_COLUMN_SPAN, default=1): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_X_ALIGN): grid_alignments,
            cv.Optional(CONF_GRID_CELL_Y_ALIGN): grid_alignments,
        }

    @classmethod
    def validate(self, config: dict):
        """
        Validate the grid layout.
        The `layout:` key may be a dictionary with `rows` and `columns` keys, or a string in the format "rows x columns".
        Either all cells must have a row and column,
        or none, in which case the grid layout is auto-generated.
        :param config:
        :return: The config updated with auto-generated values
        """
        layout = config.get(CONF_LAYOUT)
        if isinstance(layout, str):
            # If the layout is a string, assume it is in the format "rows x columns", implying
            # a grid layout with the specified number of rows and columns each with CONTENT sizing.
            layout = layout.strip()
            match = Layout._GRID_LAYOUT_REGEX.match(layout)
            if match:
                rows = int(match.group(1))
                cols = int(match.group(2))
                layout = {
                    CONF_GRID_ROWS: ["LV_GRID_CONTENT"] * rows,
                    CONF_GRID_COLUMNS: ["LV_GRID_CONTENT"] * cols,
                }
                config[CONF_LAYOUT] = layout
            else:
                raise cv.Invalid(
                    f"Invalid grid layout format: {config}, expected 'rows x columns'",
                    [CONF_LAYOUT],
                )
        # should be guaranteed to be a dict at this point
        assert isinstance(layout, dict)
        assert layout.get(CONF_TYPE) == TYPE_GRID
        rows = len(layout[CONF_GRID_ROWS])
        columns = len(layout[CONF_GRID_COLUMNS])
        used_cells = [[None] * columns for _ in range(rows)]
        for index, widget in enumerate(config.get(CONF_WIDGETS, [])):
            _, w = next(iter(widget.items()))
            if (CONF_GRID_CELL_COLUMN_POS in w) != (CONF_GRID_CELL_ROW_POS in w):
                # pylint: disable=raise-missing-from
                raise cv.Invalid(
                    "Both row and column positions must be specified, or both omitted",
                    [CONF_WIDGETS, index],
                )
            if CONF_GRID_CELL_ROW_POS in w:
                row = w[CONF_GRID_CELL_ROW_POS]
                column = w[CONF_GRID_CELL_COLUMN_POS]
            else:
                try:
                    row, column = next(
                        (r_idx, c_idx)
                        for r_idx, row in enumerate(used_cells)
                        for c_idx, value in enumerate(row)
                        if value is None
                    )
                except StopIteration:
                    # pylint: disable=raise-missing-from
                    raise cv.Invalid(
                        "No free cells available in grid layout", [CONF_WIDGETS, index]
                    )
                w[CONF_GRID_CELL_ROW_POS] = row
                w[CONF_GRID_CELL_COLUMN_POS] = column

            for i in range(w[CONF_GRID_CELL_ROW_SPAN]):
                for j in range(w[CONF_GRID_CELL_COLUMN_SPAN]):
                    if row + i >= rows or column + j >= columns:
                        # pylint: disable=raise-missing-from
                        raise cv.Invalid(
                            f"Cell at {row}/{column} span {w[CONF_GRID_CELL_ROW_SPAN]}x{w[CONF_GRID_CELL_COLUMN_SPAN]} "
                            f"exceeds grid size {rows}x{columns}",
                            [CONF_WIDGETS, index],
                        )
                    if used_cells[row + i][column + j] is not None:
                        # pylint: disable=raise-missing-from
                        raise cv.Invalid(
                            f"Cell span {row + i}/{column + j} already occupied by widget at index {used_cells[row + i][column + j]}",
                            [CONF_WIDGETS, index],
                        )
                    used_cells[row + i][column + j] = index

        return config


LAYOUT_CLASSES = (Layout, FlexLayout, GridLayout)


def get_layout_schema(config: dict):
    """
    Get the child layout schema for a given widget based on its layout type.
    :param config: The config to check
    :return: A schema for the layout including a widgets key
    """
    for layout_class in LAYOUT_CLASSES:
        schema = layout_class.layout_schema(config)
        if schema:
            return cv.Schema(
                {
                    cv.Optional(CONF_LAYOUT, default=layout_class.TYPE_NONE): schema,
                    cv.Required(CONF_WIDGETS): cv.ensure_list(
                        cv.Schema(layout_class.child_schema())
                    ),
                }
            )
    layout = config.get(CONF_LAYOUT, {})
    ltype = layout.get(CONF_TYPE, TYPE_NONE)
    schema = {}
    if ltype == TYPE_GRID:
        schema = GRID_CELL_SCHEMA
    elif ltype == TYPE_FLEX:
        if grow := layout[CONF_FLEX_GROW]:
            schema = {cv.Optional(CONF_FLEX_GROW, default=grow): cv.int_}
        else:
            schema = FLEX_OBJ_SCHEMA
        # Polyfill to implement stretch alignment for flex containers
        # LVGL does not support this natively, so we add a 100% size property to the children in the cross-axis
        if layout[CONF_FLEX_ALIGN_CROSS] == "LV_FLEX_ALIGN_STRETCH":
            dimension = (
                CONF_WIDTH
                if "COLUMN" in layout[CONF_FLEX_FLOW].upper()
                else CONF_HEIGHT
            )
            schema[cv.Optional(dimension, default="100%")] = size
        # Pass through the default flex grow value if specified

    return schema


def get_layout_class(config):
    layout = config.get(CONF_LAYOUT, TYPE_NONE)
    if isinstance(layout, dict):
        layout_type = layout.get(CONF_TYPE, TYPE_NONE)
    for layout_class in LAYOUT_CLASSES:
        if layout_class.parse_shorthand(layout) is not None:
            return layout_class
