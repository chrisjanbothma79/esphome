from esphome import pins
import esphome.codegen as cg
from esphome.components import esp32, media_player
from esphome.config_helpers import filter_source_files_from_platform
import esphome.config_validation as cv
from esphome.const import CONF_MODE, PlatformFramework
from esphome.core import CORE

from .. import (
    CONF_I2S_AUDIO_ID,
    CONF_I2S_DOUT_PIN,
    CONF_LEFT,
    CONF_MONO,
    CONF_RIGHT,
    CONF_STEREO,
    I2SAudioComponent,
    I2SAudioOut,
    i2s_audio_ns,
    use_legacy,
)

CODEOWNERS = ["@jesserockz"]
DEPENDENCIES = ["i2s_audio"]

I2SAudioMediaPlayer = i2s_audio_ns.class_(
    "I2SAudioMediaPlayer", cg.Component, media_player.MediaPlayer, I2SAudioOut
)

i2s_dac_mode_t = cg.global_ns.enum("i2s_dac_mode_t")

CONF_MUTE_PIN = "mute_pin"
CONF_AUDIO_ID = "audio_id"
CONF_DAC_TYPE = "dac_type"
CONF_I2S_COMM_FMT = "i2s_comm_fmt"

INTERNAL_DAC_OPTIONS = {
    CONF_LEFT: i2s_dac_mode_t.I2S_DAC_CHANNEL_LEFT_EN,
    CONF_RIGHT: i2s_dac_mode_t.I2S_DAC_CHANNEL_RIGHT_EN,
    CONF_STEREO: i2s_dac_mode_t.I2S_DAC_CHANNEL_BOTH_EN,
}

EXTERNAL_DAC_OPTIONS = [CONF_MONO, CONF_STEREO]

NO_INTERNAL_DAC_VARIANTS = [esp32.const.VARIANT_ESP32S2]

I2C_COMM_FMT_OPTIONS = ["lsb", "msb"]

# Filter source files based on platform framework
FILTER_SOURCE_FILES = filter_source_files_from_platform(
    {
        "i2s_audio_media_player_arduino.cpp": {  # Arduino implementation
            PlatformFramework.ESP32_ARDUINO,
        },
        "i2s_audio_media_player_idf.cpp": {  # ESP-IDF implementation
            PlatformFramework.ESP32_IDF,
        },
    }
)


def validate_esp32_variant(config):
    """Validate ESP32 variant supports the requested DAC type."""
    if config[CONF_DAC_TYPE] != "internal":
        return config
    variant = esp32.get_esp32_variant()
    if variant in NO_INTERNAL_DAC_VARIANTS:
        raise cv.Invalid(f"{variant} does not have an internal DAC")
    return config


def validate_framework_compatibility(config):
    """Validate framework-specific compatibility requirements."""
    if config[CONF_DAC_TYPE] == "internal":
        # Internal DAC requires legacy I2S driver
        if not use_legacy():
            if CORE.using_esp_idf:
                raise cv.Invalid(
                    "Internal DAC requires legacy I2S driver. Set 'use_legacy: true' in i2s_audio configuration."
                )
    return config


CONFIG_SCHEMA = cv.All(
    cv.typed_schema(
        {
            "internal": media_player.media_player_schema(I2SAudioMediaPlayer)
            .extend(
                {
                    cv.GenerateID(CONF_I2S_AUDIO_ID): cv.use_id(I2SAudioComponent),
                    cv.Required(CONF_MODE): cv.enum(INTERNAL_DAC_OPTIONS, lower=True),
                }
            )
            .extend(cv.COMPONENT_SCHEMA),
            "external": media_player.media_player_schema(I2SAudioMediaPlayer)
            .extend(
                {
                    cv.GenerateID(CONF_I2S_AUDIO_ID): cv.use_id(I2SAudioComponent),
                    cv.Required(
                        CONF_I2S_DOUT_PIN
                    ): pins.internal_gpio_output_pin_number,
                    cv.Optional(CONF_MUTE_PIN): pins.gpio_output_pin_schema,
                    cv.Optional(CONF_MODE, default="mono"): cv.one_of(
                        *EXTERNAL_DAC_OPTIONS, lower=True
                    ),
                    cv.Optional(CONF_I2S_COMM_FMT, default="msb"): cv.one_of(
                        *I2C_COMM_FMT_OPTIONS, lower=True
                    ),
                }
            )
            .extend(cv.COMPONENT_SCHEMA),
        },
        key=CONF_DAC_TYPE,
    ),
    validate_esp32_variant,
    validate_framework_compatibility,
)


def _final_validate(config):
    """Final validation for framework-specific requirements."""
    if config[CONF_DAC_TYPE] == "internal" and not use_legacy():
        raise cv.Invalid("Internal DAC is only compatible with legacy i2s driver.")


FINAL_VALIDATE_SCHEMA = _final_validate


async def to_code(config):
    """Generate code for the I2S audio media player component."""
    var = await media_player.new_media_player(config)
    await cg.register_component(var, config)

    await cg.register_parented(var, config[CONF_I2S_AUDIO_ID])

    if config[CONF_DAC_TYPE] == "internal":
        cg.add(var.set_internal_dac_mode(config[CONF_MODE]))
    else:
        cg.add(var.set_dout_pin(config[CONF_I2S_DOUT_PIN]))
        if CONF_MUTE_PIN in config:
            pin = await cg.gpio_pin_expression(config[CONF_MUTE_PIN])
            cg.add(var.set_mute_pin(pin))
        cg.add(var.set_external_dac_channels(2 if config[CONF_MODE] == "stereo" else 1))
        cg.add(var.set_i2s_comm_fmt_lsb(config[CONF_I2S_COMM_FMT] == "lsb"))

    # Add framework-specific libraries and build flags
    if CORE.using_arduino:
        # Arduino framework dependencies
        cg.add_library("NetworkClientSecure", None)
        cg.add_library("HTTPClient", None)
        cg.add_library("WiFi", None)  # Required by ESP32-audioI2S library
        cg.add_library("esphome/ESP32-audioI2S", "2.3.0")
        cg.add_build_flag("-DAUDIO_NO_SD_FS")
        # Disable WiFi features in the audio library
        cg.add_build_flag("-DAUDIO_NO_WIFI")  
    # ESP-IDF framework uses built-in HTTP client and I2S drivers
    # No additional libraries needed for ESP-IDF
