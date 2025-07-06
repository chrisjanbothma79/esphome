"""Tests for mpip_spi configuration validation."""

import contextvars
from pathlib import Path

import pytest

from esphome import config_validation as cv
from esphome.components.esp32 import (
    FRAMEWORK_ARDUINO,
    FRAMEWORK_ESP_IDF,
    KEY_BOARD,
    KEY_ESP32,
    VARIANT_ESP32S3,
)
from esphome.const import (
    KEY_CORE,
    KEY_TARGET_FRAMEWORK,
    KEY_TARGET_PLATFORM,
    KEY_VARIANT,
    PLATFORM_ESP32,
)


def _config_setup():
    from esphome import config
    from esphome.core import CORE

    CORE.config_path = __file__
    CORE.data[KEY_CORE] = {KEY_TARGET_PLATFORM: PLATFORM_ESP32}
    CORE.data[KEY_ESP32] = {
        KEY_VARIANT: VARIANT_ESP32S3,
        KEY_BOARD: "esp32-s3-devkitc-1",
    }
    config.path_context = contextvars.ContextVar("Config path")
    config.path_context.set([])


def _test_failure(config, error_msg: str, validator=None) -> None:
    """Helper function to test failure of configuration validation."""
    from esphome.components.mipi_spi.display import CONFIG_SCHEMA

    validator = validator or CONFIG_SCHEMA

    with pytest.raises(cv.Invalid) as exc_info:
        validator(config)
    assert error_msg in str(exc_info.value)


def test_image_configuration_errors() -> None:
    """Test detection of invalid configuration"""

    _config_setup()

    from esphome.components.mipi_spi.display import dimension_schema
    from esphome.core import CORE

    _test_failure("a string", "expected a dictionary")
    _test_failure({"id": "display_id"}, "required key not provided @ data['model']")
    _test_failure(
        {"id": "display_id", "model": "custom", "init_sequence": [[0x36, 0x01]]},
        "required key not provided @ data['dimensions']",
    )
    _test_failure(
        {"model": "custom", "dc_pin": 11, "dimensions": {"width": 320, "height": 240}},
        "required key not provided @ data['init_sequence']",
    )

    _test_failure(
        {
            "id": "display_id",
            "model": "custom",
            "dimensions": {"width": 320, "height": 240},
            "draw_rounding": 13,
        },
        "value must be a power of two for dictionary value @ data['draw_rounding']",
    )
    _test_failure(
        {"width": 320},
        "required key not provided @ data['height']",
        dimension_schema(4),
    )
    _test_failure(
        {"width": 320, "height": 111},
        "Dimensions and offsets must be divisible by 32",
        dimension_schema(32),
    )

    CORE.data[KEY_CORE][KEY_TARGET_FRAMEWORK] = FRAMEWORK_ARDUINO

    _test_failure(
        {"model": "wt32-sc01-plus"},
        "This feature is only available with frameworks ['esp-idf']",
    )

    CORE.data[KEY_CORE][KEY_TARGET_FRAMEWORK] = FRAMEWORK_ESP_IDF

    _test_failure(
        {
            "model": "JC3248W535",
            "transform": {"mirror_x": False, "mirror_y": True, "swap_xy": True},
        },
        "Axis swapping not supported by this model",
    )
    _test_failure(
        {
            "model": "JC3248W535",
            "transform": {"mirror_x": False, "mirror_y": True, "swap_xy": False},
            "init_sequence": [[0x36, 0x01]],
        },
        "transform is not supported when MADCTL (0X36) is in the init sequence",
    )
    _test_failure(
        {"model": "JC3248W535", "init_sequence": [[0x3A, 0x01]]},
        "PIXFMT (0X3A) should not be in the init sequence, it will be set automatically",
    )
    _test_failure(
        {"model": "t4-s3", "dc_pin": 11},
        "DC pin is not supported in quad mode",
    )

    _test_failure(
        {"model": "t4-s3", "color_depth": 18},
        "Unknown value '18', valid options are '16', '16bit",
    )

    _test_failure(
        {"model": "t-embed", "color_depth": 24},
        "Unknown value '24', valid options are '16', '8",
    )

    _test_failure(
        {"model": "ili9488"},
        "DC pin is required in single mode",
    )
    _test_failure(
        {"model": "wt32-sc01-plus", "brightness": 128},
        "extra keys not allowed @ data['brightness']",
    )


def test_image_configuration_success() -> None:
    """Test successful configuration validation."""
    from esphome.components.image import CONFIG_SCHEMA
    from esphome.core import CORE

    CORE.config_path = __file__

    # Valid image configuration
    CONFIG_SCHEMA(
        {
            "id": "image_id",
            "file": "image.png",
            "type": "rgb565",
            "transparency": "chroma_key",
            "byte_order": "little_endian",
            "dither": "FloydSteinberg",
            "resize": "100x100",
            "invert_alpha": False,
        }
    )
    CONFIG_SCHEMA(
        [
            {
                "id": "image_id",
                "file": "image.png",
                "type": "binary",
            }
        ]
    )
    CONFIG_SCHEMA(
        {
            "defaults": {
                "type": "rgb565",
                "transparency": "chroma_key",
                "byte_order": "little_endian",
                "dither": "FloydSteinberg",
                "resize": "100x100",
                "invert_alpha": False,
            },
            "images": [
                {
                    "id": "image_id",
                    "file": "image.png",
                }
            ],
        }
    )
    CONFIG_SCHEMA(
        {
            "rgb565": {
                "alpha_channel": [
                    {
                        "id": "image_id",
                        "file": "image.png",
                        "transparency": "alpha_channel",
                        "byte_order": "little_endian",
                        "dither": "FloydSteinberg",
                        "resize": "100x100",
                        "invert_alpha": False,
                    }
                ]
            },
            "binary": [
                {
                    "id": "image_id",
                    "file": "image.png",
                    "transparency": "opaque",
                    "dither": "FloydSteinberg",
                    "resize": "100x100",
                    "invert_alpha": False,
                }
            ],
        }
    )


def _get_path(file_name: str) -> Path:
    """Helper function to get the absolute path of a file relative to the test script."""
    return (Path(__file__).parent / file_name).absolute()


def test_image_generation(generate_main) -> None:
    """Test image generation configuration."""
    from esphome.core import CORE

    CORE.config_path = __file__

    main_cpp = generate_main(_get_path("image_test.yaml"))
    assert "uint8_t_id[] PROGMEM = {0x24, 0x21, 0x24, 0x21" in main_cpp
    assert (
        "cat_img = new image::Image(uint8_t_id, 32, 24, image::IMAGE_TYPE_RGB565, image::TRANSPARENCY_OPAQUE);"
        in main_cpp
    )
