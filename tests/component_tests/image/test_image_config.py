"""Tests for image configuration validation."""

from pathlib import Path

import pytest

from esphome import config_validation as cv


def _test_failure(config, error_msg: str) -> None:
    """Helper function to test failure of configuration validation."""
    from esphome.components.image import CONFIG_SCHEMA
    from esphome.core import CORE

    CORE.config_path = __file__

    with pytest.raises(cv.Invalid) as exc_info:
        CONFIG_SCHEMA(config)
    assert error_msg in str(exc_info.value)


def test_image_configuration_errors() -> None:
    """Test detection of invalid configuration"""
    from esphome.core import CORE

    CORE.config_path = "tests/component_tests/image/test_image_config.py"

    _test_failure(
        "a string", "Badly formed image configuration, expected a list or a dictionary"
    )
    _test_failure(
        {"id": "image_id", "type": "rgb565"},
        "required key not provided @ data[0]['file']",
    )
    _test_failure(
        {"file": "image.png", "type": "rgb565"},
        "required key not provided @ data[0]['id']",
    )
    _test_failure(
        {"id": "mdi_id", "file": "mdi:weather-##", "type": "rgb565"},
        "Could not parse mdi icon name",
    )
    _test_failure(
        {
            "id": "image_id",
            "file": "image.png",
            "type": "binary",
            "transparency": "alpha_channel",
        },
        "Image format 'BINARY' cannot have transparency",
    )
    _test_failure(
        {
            "id": "image_id",
            "file": "image.png",
            "type": "rgb565",
            "transparency": "chroma_key",
            "invert_alpha": True,
        },
        "No alpha channel to invert",
    )
    _test_failure(
        {
            "id": "image_id",
            "file": "image.png",
            "type": "binary",
            "byte_order": "big_endian",
        },
        "Image format 'BINARY' does not support byte order configuration",
    )
    _test_failure(
        {"id": "image_id", "file": "bad.png", "type": "binary"},
        "File can't be opened as image",
    )
    _test_failure(
        {"defaults": {}, "images": [{"id": "image_id", "file": "image.png"}]},
        "Type is required either in the image config or in the defaults",
    )


def test_image_configuration_success() -> None:
    """Test successful configuration validation."""
    from esphome.components.image import CONFIG_SCHEMA
    from esphome.core import CORE

    CORE.config_path = "tests/component_tests/image/test_image_config.py"

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
