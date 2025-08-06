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
    TYPE_GRID,
    TYPE_NONE,
)
from esphome.components.lvgl.lv_validation import padding
from esphome.components.lvgl.schemas import (
    FLEX_OBJ_SCHEMA,
    flex_alignments,
    grid_alignments,
    grid_spec,
)
import esphome.config_validation as cv
from esphome.const import CONF_TYPE


class Layout:
    """
    Define properties for a layout
    The base class is layout "none"
    """

    @classmethod
    def layout_schema(cls):
        """
        Get the schema for this layout to validate the `layout:` key data
        """
        return {}

    @classmethod
    def child_schema(cls):
        """
        Get additional options for child object in the layout
        :return:
        """
        return {}

    @classmethod
    def parse_shorthand(cls, data):
        if data.lower == TYPE_NONE:
            return {}
        return None


class FlexLayout(Layout):
    @classmethod
    def layout_schema(cls):
        return {
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
    def child_schema(cls):
        return FLEX_OBJ_SCHEMA

    @classmethod
    def parse_shorthand(cls, data):
        """
        If the shorthand matches this layout, return a schema to populate the
        layout key.
        :return: None if no match, a dict otherwise
        """
        return

    @classmethod
    def validate(cls, config):
        """
        Perform validation on the container and its children for this layout
        :param config:
        :return:
        """


class GridLayout(Layout):
    @classmethod
    def layout_schema(cls):
        return {
            cv.Required(CONF_GRID_ROWS): [grid_spec],
            cv.Required(CONF_GRID_COLUMNS): [grid_spec],
            cv.Optional(CONF_GRID_COLUMN_ALIGN): grid_alignments,
            cv.Optional(CONF_GRID_ROW_ALIGN): grid_alignments,
            cv.Optional(CONF_PAD_ROW): padding,
            cv.Optional(CONF_PAD_COLUMN): padding,
        }

    @classmethod
    def child_schema(cls):
        return {
            cv.Optional(CONF_GRID_CELL_ROW_POS): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_COLUMN_POS): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_ROW_SPAN, default=1): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_COLUMN_SPAN, default=1): cv.positive_int,
            cv.Optional(CONF_GRID_CELL_X_ALIGN): grid_alignments,
            cv.Optional(CONF_GRID_CELL_Y_ALIGN): grid_alignments,
        }

    @classmethod
    def parse_shorthand(cls, data):
        return None

    def validate(self, config):
        """
        Validate the grid layout. Either all cells must have a row and column,
        or none, in which case the grid layout is auto-generated.
        :param config:
        :return: The config updated with auto-generated values
        """
        if isinstance(config, str):
            config = config.strip()
            match = re.match(r"^\s*(\d+)\s*x\s*(\d+)\s*$", config)
            if match:
                config = {CONF_GRID_ROWS: [{"fr": int(match.group(1))}], CONF_GRID_COLUMNS: [{"fr": int(match.group(2))}]}
            else:
                raise cv.Invalid(
                    f"Invalid grid layout shorthand: {config}",
                )
        layout = config.get(CONF_LAYOUT, TYPE_NONE)
        if layout != TYPE_GRID:
            raise cv.Invalid(
                f"Invalid layout type: {layout}",
            )
        rows = len(layout[CONF_GRID_ROWS])
        columns = len(layout[CONF_GRID_COLUMNS])
        used_cells = [[None] * columns for _ in range(rows)]
        for index, widget in enumerate(config[CONF_WIDGETS]):
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


def get_layout_class(config):
    layout = config.get(CONF_LAYOUT, TYPE_NONE)
    if isinstance(layout, dict):
        layout_type = layout.get(CONF_TYPE, TYPE_NONE)
    for layout_class in LAYOUT_CLASSES:
        if layout_class.parse_shorthand(layout) is not None:
            return layout_class
