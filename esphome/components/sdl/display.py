import subprocess

import esphome.codegen as cg
from esphome.components import display
import esphome.config_validation as cv
from esphome.const import (
    CONF_DIMENSIONS,
    CONF_HEIGHT,
    CONF_ID,
    CONF_LAMBDA,
    CONF_POSITION,
    CONF_WIDTH,
    PLATFORM_HOST,
)

sdl_ns = cg.esphome_ns.namespace("sdl")
Sdl = sdl_ns.class_("Sdl", display.Display, cg.Component)


CONF_SDL_OPTIONS = "sdl_options"
CONF_SDL_ID = "sdl_id"
CONF_WINDOW_OPTIONS = "window_options"
CONF_BORDERLESS = "borderless"
CONF_ALWAYS_ON_TOP = "always_on_top"
CONF_FULLSCREEN = "fullscreen"
CONF_SKIP_TASKBAR = "skip_taskbar"
CONF_X = "x"
CONF_Y = "y"


def get_sdl_options(value):
    if value != "":
        return value
    try:
        return subprocess.check_output(["sdl2-config", "--cflags", "--libs"]).decode()
    except Exception as e:
        raise cv.Invalid("Unable to run sdl2-config - have you installed sdl2?") from e


CONFIG_SCHEMA = cv.All(
    display.FULL_DISPLAY_SCHEMA.extend(
        cv.Schema(
            {
                cv.GenerateID(): cv.declare_id(Sdl),
                cv.Optional(CONF_SDL_OPTIONS, default=""): get_sdl_options,
                cv.Required(CONF_DIMENSIONS): cv.Any(
                    cv.dimensions,
                    cv.Schema(
                        {
                            cv.Required(CONF_WIDTH): cv.int_,
                            cv.Required(CONF_HEIGHT): cv.int_,
                        }
                    ),
                ),
                cv.Optional(CONF_WINDOW_OPTIONS): cv.Any(
                    None,
                    cv.Schema(
                        {
                            cv.Optional(CONF_BORDERLESS, default=False): cv.boolean,
                            cv.Optional(CONF_ALWAYS_ON_TOP, default=False): cv.boolean,
                            cv.Optional(CONF_FULLSCREEN, default=False): cv.boolean,
                            cv.Optional(CONF_SKIP_TASKBAR, default=False): cv.boolean,
                            cv.Optional(CONF_POSITION): cv.Any(
                                None,
                                cv.Schema(
                                    {
                                        cv.Required(CONF_X): cv.int_,
                                        cv.Required(CONF_Y): cv.int_,
                                    }
                                ),
                            ),
                        }
                    ),
                ),
            }
        )
    ),
    cv.only_on(PLATFORM_HOST),
)


async def to_code(config):
    for option in config[CONF_SDL_OPTIONS].split():
        cg.add_build_flag(option)
    cg.add_build_flag("-DSDL_BYTEORDER=4321")
    var = cg.new_Pvariable(config[CONF_ID])
    await display.register_display(var, config)

    dimensions = config[CONF_DIMENSIONS]
    if isinstance(dimensions, dict):
        cg.add(var.set_dimensions(dimensions[CONF_WIDTH], dimensions[CONF_HEIGHT]))
    else:
        (width, height) = dimensions
        cg.add(var.set_dimensions(width, height))

    if window_options := config.get(CONF_WINDOW_OPTIONS):
        cg.add(var.set_borderless(window_options[CONF_BORDERLESS]))
        cg.add(var.set_always_on_top(window_options[CONF_ALWAYS_ON_TOP]))
        cg.add(var.set_fullscreen(window_options[CONF_FULLSCREEN]))
        cg.add(var.set_skip_taskbar(window_options[CONF_SKIP_TASKBAR]))

        if position := window_options.get(CONF_POSITION):
            if isinstance(position, dict):
                cg.add(var.set_position(position[CONF_X], position[CONF_Y]))
            else:
                (pos_x, pos_y) = position
                cg.add(var.set_position(pos_x, pos_y))

    if lamb := config.get(CONF_LAMBDA):
        lambda_ = await cg.process_lambda(
            lamb, [(display.DisplayRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
