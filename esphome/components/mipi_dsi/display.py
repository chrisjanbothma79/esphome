import logging

from esphome import pins
import esphome.codegen as cg
from esphome.components import display
from esphome.components.const.mipi import (
    CONF_BYTE_ORDER,
    CONF_HSYNC_BACK_PORCH,
    CONF_HSYNC_FRONT_PORCH,
    CONF_HSYNC_PULSE_WIDTH,
    CONF_PIXEL_MODE,
    CONF_USE_AXIS_FLIPS,
    CONF_VSYNC_BACK_PORCH,
    CONF_VSYNC_FRONT_PORCH,
    CONF_VSYNC_PULSE_WIDTH,
    DISPON,
    INVOFF,
    INVON,
    MADCTL,
    MODE_BGR,
    PIXEL_MODE_16BIT,
    PIXEL_MODES,
    PIXFMT,
    SLPOUT,
    dimension_schema,
    get_dimensions,
    get_transform,
    map_sequence,
    power_of_two,
)
from esphome.components.esp32 import const, only_on_variant
import esphome.config_validation as cv
from esphome.const import (
    CONF_COLOR_ORDER,
    CONF_DATA_RATE,
    CONF_DIMENSIONS,
    CONF_ENABLE_PIN,
    CONF_ID,
    CONF_INIT_SEQUENCE,
    CONF_INVERT_COLORS,
    CONF_LAMBDA,
    CONF_MIRROR_X,
    CONF_MIRROR_Y,
    CONF_MODEL,
    CONF_RESET_PIN,
    CONF_SWAP_XY,
    CONF_TRANSFORM,
    CONF_WIDTH,
)

from ...cpp_generator import TemplateArguments
from ..const import CONF_DRAW_ROUNDING
from .models import (
    DELAY_FLAG,
    MADCTL_BGR,
    MADCTL_MV,
    MADCTL_MX,
    MADCTL_MY,
    MADCTL_XFLIP,
    MADCTL_YFLIP,
    DriverChip,
    waveshare,
)

DEPENDENCIES = ["esp32"]
DOMAIN = "mipi_dsi"

LOGGER = logging.getLogger(DOMAIN)

mipi_dsi_ns = cg.esphome_ns.namespace("mipi_dsi")
MIPI_DSI = mipi_dsi_ns.class_("MIPI_DSI", display.Display, cg.Component)
ColorOrder = display.display_ns.enum("ColorMode")

COLOR_ORDERS = {
    "RGB": ColorOrder.COLOR_ORDER_RGB,
    "BGR": ColorOrder.COLOR_ORDER_BGR,
}

DriverChip("CUSTOM")

MODELS = DriverChip.models

# This loop is a noop, but suppresses linting of side-effect-only imports
for _ in (waveshare,):
    pass


def get_sequence(config):
    """
    Create the init sequence for the display.
    Use the default sequence from the model, if any, and append any custom sequence provided in the config.
    Append SLPOUT (if not already in the sequence) and DISPON to the end of the sequence
    Pixel format, color order, and orientation will be set.
    """
    model = DriverChip.models[config[CONF_MODEL].upper()]
    sequence = list(model.initsequence)
    custom_sequence = config.get(CONF_INIT_SEQUENCE, [])
    sequence.extend(custom_sequence)
    # Ensure each command is a tuple
    sequence = [x if isinstance(x, tuple) else (x,) for x in sequence]
    commands = [x[0] for x in sequence]
    # Set pixel format if not already in the custom sequence
    if PIXFMT not in commands:
        pixel_mode = config[CONF_PIXEL_MODE]
        if not isinstance(pixel_mode, int):
            pixel_mode = PIXEL_MODES[pixel_mode]
        sequence.append((PIXFMT, pixel_mode))
    # Does the chip use the flipping bits for mirroring rather than the reverse order bits?
    use_flip = config[CONF_USE_AXIS_FLIPS]
    if MADCTL not in commands:
        madctl = 0
        transform = get_transform(model, config)
        if transform.get(CONF_TRANSFORM):
            LOGGER.info("Using hardware transform to implement rotation")
        if transform.get(CONF_MIRROR_X):
            madctl |= MADCTL_XFLIP if use_flip else MADCTL_MX
        if transform.get(CONF_MIRROR_Y):
            madctl |= MADCTL_YFLIP if use_flip else MADCTL_MY
        if transform.get(CONF_SWAP_XY) is True:  # Exclude Undefined
            madctl |= MADCTL_MV
        if config[CONF_COLOR_ORDER] == MODE_BGR:
            madctl |= MADCTL_BGR
        sequence.append((MADCTL, madctl))
    if INVON not in commands and INVOFF not in commands:
        if config[CONF_INVERT_COLORS]:
            sequence.append((INVON,))
        else:
            sequence.append((INVOFF,))
    if SLPOUT not in commands:
        sequence.append((SLPOUT,))
    sequence.append((DISPON,))

    # Flatten the sequence into a list of bytes, with the length of each command
    # or the delay flag inserted where needed
    return sum(
        tuple(
            (x[1], 0xFF) if x[0] == DELAY_FLAG else (x[0], len(x) - 1) + x[1:]
            for x in sequence
        ),
        (),
    )


def model_schema(config):
    model = DriverChip.models[config[CONF_MODEL].upper()]
    transform = cv.Schema(
        {
            cv.Required(CONF_MIRROR_X): cv.boolean,
            cv.Required(CONF_MIRROR_Y): cv.boolean,
        }
    )
    if model.get_default(CONF_SWAP_XY, False) == cv.UNDEFINED:
        transform = transform.extend(
            {
                cv.Optional(CONF_SWAP_XY): cv.invalid(
                    "Axis swapping not supported by this model"
                )
            }
        )
    else:
        transform = transform.extend(
            {
                cv.Required(CONF_SWAP_XY): cv.boolean,
            }
        )
    # CUSTOM model will need to provide a custom init sequence
    iseqconf = (
        cv.Required(CONF_INIT_SEQUENCE)
        if model.initsequence is None
        else cv.Optional(CONF_INIT_SEQUENCE)
    )
    # Dimensions are optional if the model has a default width and the transform is not overridden
    swap_xy = config.get(CONF_TRANSFORM, {}).get(CONF_SWAP_XY, False)

    cv_dimensions = (
        cv.Optional if model.get_default(CONF_WIDTH) and not swap_xy else cv.Required
    )
    pixel_modes = (PIXEL_MODE_16BIT,)
    schema = display.FULL_DISPLAY_SCHEMA.extend(
        {
            model.option(CONF_RESET_PIN, cv.UNDEFINED): pins.gpio_output_pin_schema,
            cv.GenerateID(): cv.declare_id(MIPI_DSI),
            cv_dimensions(CONF_DIMENSIONS): dimension_schema(
                model.get_default(CONF_DRAW_ROUNDING, 1)
            ),
            model.option(CONF_ENABLE_PIN, cv.UNDEFINED): cv.ensure_list(
                pins.gpio_output_pin_schema
            ),
            model.option(CONF_COLOR_ORDER, MODE_BGR): cv.enum(COLOR_ORDERS, upper=True),
            model.option(CONF_DRAW_ROUNDING, 2): power_of_two,
            model.option(CONF_PIXEL_MODE, PIXEL_MODE_16BIT): cv.one_of(
                *pixel_modes, lower=True
            ),
            cv.Optional(CONF_TRANSFORM): transform,
            cv.Required(CONF_MODEL): cv.one_of(model.name, upper=True),
            model.option(CONF_INVERT_COLORS): cv.boolean,
            model.option(CONF_USE_AXIS_FLIPS): cv.boolean,
            model.option(CONF_DATA_RATE): cv.All(
                cv.frequency, cv.Range(min=4e6, max=100e6)
            ),
            iseqconf: cv.ensure_list(map_sequence),
            model.option(CONF_BYTE_ORDER, "little_endian"): cv.one_of(
                "big_endian", "little_endian", lower=True
            ),
        }
    )
    return cv.All(
        schema,
        only_on_variant(supported=[const.VARIANT_ESP32P4]),
        cv.only_with_esp_idf,
    )


def _config_schema(config):
    # First get the model and bus mode
    config = cv.Schema(
        {
            cv.Required(CONF_MODEL): cv.one_of(*MODELS, upper=True),
        },
        extra=cv.ALLOW_EXTRA,
    )(config)
    config = model_schema(config)(config)
    if init_sequence := config.get(CONF_INIT_SEQUENCE):
        if MADCTL in [x[0] for x in init_sequence] and CONF_TRANSFORM in config:
            raise cv.Invalid(
                f"transform is not supported when MADCTL ({MADCTL:#X}) is in the init sequence"
            )
    return config


CONFIG_SCHEMA = _config_schema


async def to_code(config):
    model = DriverChip.models[config[CONF_MODEL].upper()]
    width, height, _offset_width, _offset_height = get_dimensions(model, config)
    template_arguments = [
        width,
        height,
        config[CONF_BYTE_ORDER] == "big_endian",
    ]
    var = cg.new_Pvariable(config[CONF_ID], TemplateArguments(template_arguments))
    await display.register_display(var, config)

    cg.add(var.set_model(config[CONF_MODEL]))
    cg.add(var.set_draw_rounding(config[CONF_DRAW_ROUNDING]))
    cg.add(var.set_init_sequence(get_sequence(config)))
    cg.add(var.set_invert_colors(config[CONF_INVERT_COLORS]))
    cg.add(var.set_hsync_pulse_width(config[CONF_HSYNC_PULSE_WIDTH]))
    cg.add(var.set_hsync_back_porch(config[CONF_HSYNC_BACK_PORCH]))
    cg.add(var.set_hsync_front_porch(config[CONF_HSYNC_FRONT_PORCH]))
    cg.add(var.set_vsync_pulse_width(config[CONF_VSYNC_PULSE_WIDTH]))
    cg.add(var.set_vsync_back_porch(config[CONF_VSYNC_BACK_PORCH]))
    cg.add(var.set_vsync_front_porch(config[CONF_VSYNC_FRONT_PORCH]))
    cg.add(var.set_data_rate(int(config[CONF_DATA_RATE]) / 1e6))
    if reset_pin := config.get(CONF_RESET_PIN):
        reset = await cg.gpio_pin_expression(reset_pin)
        cg.add(var.set_reset_pin(reset))

    if lamb := config.get(CONF_LAMBDA):
        lambda_ = await cg.process_lambda(
            lamb, [(display.DisplayRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
