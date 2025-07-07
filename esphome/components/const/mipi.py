# Various constants used in MIPI DBI communication
# Various configuration constants for MIPI displays
# Various utility functions for MIPI DBI configuration

from esphome.components.display import display_ns
import esphome.config_validation as cv
from esphome.const import (
    CONF_DIMENSIONS,
    CONF_HEIGHT,
    CONF_MIRROR_X,
    CONF_MIRROR_Y,
    CONF_OFFSET_HEIGHT,
    CONF_OFFSET_WIDTH,
    CONF_ROTATION,
    CONF_SWAP_XY,
    CONF_TRANSFORM,
    CONF_WIDTH,
)
from esphome.core import TimePeriod

ColorOrder = display_ns.enum("ColorMode")

NOP = 0x00
SWRESET = 0x01
RDDID = 0x04
RDDST = 0x09
RDMODE = 0x0A
RDMADCTL = 0x0B
RDPIXFMT = 0x0C
RDIMGFMT = 0x0D
RDSELFDIAG = 0x0F
SLEEP_IN = 0x10
SLPIN = 0x10
SLEEP_OUT = 0x11
SLPOUT = 0x11
PTLON = 0x12
NORON = 0x13
INVERT_OFF = 0x20
INVOFF = 0x20
INVERT_ON = 0x21
INVON = 0x21
ALL_ON = 0x23
WRAM = 0x24
GAMMASET = 0x26
MIPI = 0x26
DISPOFF = 0x28
DISPON = 0x29
CASET = 0x2A
PASET = 0x2B
RASET = 0x2B
RAMWR = 0x2C
WDATA = 0x2C
RAMRD = 0x2E
PTLAR = 0x30
VSCRDEF = 0x33
TEON = 0x35
MADCTL = 0x36
MADCTL_CMD = 0x36
VSCRSADD = 0x37
IDMOFF = 0x38
IDMON = 0x39
COLMOD = 0x3A
PIXFMT = 0x3A
GETSCANLINE = 0x45
BRIGHTNESS = 0x51
WRDISBV = 0x51
RDDISBV = 0x52
WRCTRLD = 0x53
SWIRE1 = 0x5A
SWIRE2 = 0x5B
IFMODE = 0xB0
FRMCTR1 = 0xB1
FRMCTR2 = 0xB2
FRMCTR3 = 0xB3
INVCTR = 0xB4
DFUNCTR = 0xB6
ETMOD = 0xB7
PWCTR1 = 0xC0
PWCTR2 = 0xC1
PWCTR3 = 0xC2
PWCTR4 = 0xC3
PWCTR5 = 0xC4
VMCTR1 = 0xC5
IFCTR = 0xC6
VMCTR2 = 0xC7
GMCTR = 0xC8
SETEXTC = 0xC8
PWSET = 0xD0
VMCTR = 0xD1
PWSETN = 0xD2
RDID4 = 0xD3
RDINDEX = 0xD9
RDID1 = 0xDA
RDID2 = 0xDB
RDID3 = 0xDC
RDIDX = 0xDD
GMCTRP1 = 0xE0
GMCTRN1 = 0xE1
CSCON = 0xF0
PWCTR6 = 0xF6
ADJCTL3 = 0xF7
PAGESEL = 0xFE

# Special constant for delays in command sequences
DELAY_FLAG = 0xFF

CONF_PIXEL_MODE = "pixel_mode"
CONF_USE_AXIS_FLIPS = "use_axis_flips"

PIXEL_MODE_18BIT = "18bit"
PIXEL_MODE_16BIT = "16bit"

PIXEL_MODES = {
    PIXEL_MODE_16BIT: 0x55,
    PIXEL_MODE_18BIT: 0x66,
}

MODE_RGB = "RGB"
MODE_BGR = "BGR"
COLOR_ORDERS = {
    MODE_RGB: ColorOrder.COLOR_ORDER_RGB,
    MODE_BGR: ColorOrder.COLOR_ORDER_BGR,
}

CONF_HSYNC_PULSE_WIDTH = "hsync_pulse_width"
CONF_HSYNC_BACK_PORCH = "hsync_back_porch"
CONF_HSYNC_FRONT_PORCH = "hsync_front_porch"
CONF_VSYNC_PULSE_WIDTH = "vsync_pulse_width"
CONF_VSYNC_BACK_PORCH = "vsync_back_porch"
CONF_VSYNC_FRONT_PORCH = "vsync_front_porch"
CONF_NATIVE_WIDTH = "native_width"
CONF_NATIVE_HEIGHT = "native_height"
CONF_BYTE_ORDER = "byte_order"


def rotation_as_transform(model, config):
    """
    Check if a rotation can be implemented in hardware using the MADCTL register.
    A rotation of 180 is always possible, 90 and 270 are possible if the model supports swapping X and Y.
    """
    rotation = config.get(CONF_ROTATION, 0)
    return rotation and (
        model.get_default(CONF_SWAP_XY) != cv.UNDEFINED or rotation == 180
    )


def power_of_two(value):
    value = cv.int_range(1, 128)(value)
    if value & (value - 1) != 0:
        raise cv.Invalid("value must be a power of two")
    return value


def get_transform(model, config):
    can_transform = rotation_as_transform(model, config)
    transform = config.get(
        CONF_TRANSFORM,
        {
            CONF_MIRROR_X: model.get_default(CONF_MIRROR_X, False),
            CONF_MIRROR_Y: model.get_default(CONF_MIRROR_Y, False),
            CONF_SWAP_XY: model.get_default(CONF_SWAP_XY, False),
        },
    )

    # Can we use the MADCTL register to set the rotation?
    if can_transform and CONF_TRANSFORM not in config:
        rotation = config[CONF_ROTATION]
        if rotation == 180:
            transform[CONF_MIRROR_X] = not transform[CONF_MIRROR_X]
            transform[CONF_MIRROR_Y] = not transform[CONF_MIRROR_Y]
        elif rotation == 90:
            transform[CONF_SWAP_XY] = not transform[CONF_SWAP_XY]
            transform[CONF_MIRROR_X] = not transform[CONF_MIRROR_X]
        else:
            transform[CONF_SWAP_XY] = not transform[CONF_SWAP_XY]
            transform[CONF_MIRROR_Y] = not transform[CONF_MIRROR_Y]
        transform[CONF_TRANSFORM] = True
    return transform


def validate_dimension(rounding):
    def validator(value):
        value = cv.positive_int(value)
        if value % rounding != 0:
            raise cv.Invalid(f"Dimensions and offsets must be divisible by {rounding}")
        return value

    return validator


def dimension_schema(rounding):
    return cv.Any(
        cv.dimensions,
        cv.Schema(
            {
                cv.Required(CONF_WIDTH): validate_dimension(rounding),
                cv.Required(CONF_HEIGHT): validate_dimension(rounding),
                cv.Optional(CONF_OFFSET_HEIGHT, default=0): validate_dimension(
                    rounding
                ),
                cv.Optional(CONF_OFFSET_WIDTH, default=0): validate_dimension(rounding),
            }
        ),
    )


def map_sequence(value):
    """
    The format is a repeated sequence of [CMD, <data>] where <data> is s a sequence of bytes. The length is inferred
    from the length of the sequence and should not be explicit.
    A delay can be inserted by specifying "- delay N" where N is in ms
    """
    if isinstance(value, str) and value.lower().startswith("delay "):
        value = value.lower()[6:]
        delay = cv.All(
            cv.positive_time_period_milliseconds,
            cv.Range(TimePeriod(milliseconds=1), TimePeriod(milliseconds=255)),
        )(value)
        return DELAY_FLAG, delay.total_milliseconds
    if isinstance(value, int):
        return (value,)
    value = cv.All(cv.ensure_list(cv.int_range(0, 255)), cv.Length(1, 254))(value)
    return tuple(value)


def get_dimensions(model, config):
    if CONF_DIMENSIONS in config:
        # Explicit dimensions, just use as is
        dimensions = config[CONF_DIMENSIONS]
        if isinstance(dimensions, dict):
            width = dimensions[CONF_WIDTH]
            height = dimensions[CONF_HEIGHT]
            offset_width = dimensions[CONF_OFFSET_WIDTH]
            offset_height = dimensions[CONF_OFFSET_HEIGHT]
            return width, height, offset_width, offset_height
        (width, height) = dimensions
        return width, height, 0, 0

    # Default dimensions, use model defaults
    transform = get_transform(model, config)

    width = model.get_default(CONF_WIDTH)
    height = model.get_default(CONF_HEIGHT)
    offset_width = model.get_default(CONF_OFFSET_WIDTH, 0)
    offset_height = model.get_default(CONF_OFFSET_HEIGHT, 0)

    # if mirroring axes and there are offsets, also mirror the offsets to cater for situations where
    # the offset is asymmetric
    if transform[CONF_MIRROR_X]:
        native_width = model.get_default(CONF_NATIVE_WIDTH, width + offset_width * 2)
        offset_width = native_width - width - offset_width
    if transform[CONF_MIRROR_Y]:
        native_height = model.get_default(
            CONF_NATIVE_HEIGHT, height + offset_height * 2
        )
        offset_height = native_height - height - offset_height
    # Swap default dimensions if swap_xy is set
    if transform[CONF_SWAP_XY] is True:
        width, height = height, width
        offset_height, offset_width = offset_width, offset_height
    return width, height, offset_width, offset_height
