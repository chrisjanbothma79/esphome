"""Tests for image configuration validation."""

from __future__ import annotations

from collections.abc import Callable
from pathlib import Path
from typing import Any

import pytest

from esphome import config_validation as cv
from esphome.components.image import CONFIG_SCHEMA


def test_image_configuration_errors() -> None:
    """Test detection of invalid configuration."""

    with pytest.raises(
        cv.Invalid,
        match="Badly formed image configuration, expected a list or a dictionary",
    ):
        CONFIG_SCHEMA("a string")

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\[0\]\['file'\]"
    ):
        CONFIG_SCHEMA({"id": "image_id", "type": "rgb565"})

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\[0\]\['id'\]"
    ):
        CONFIG_SCHEMA({"file": "image.png", "type": "rgb565"})

    with pytest.raises(cv.Invalid, match="Could not parse mdi icon name"):
        CONFIG_SCHEMA({"id": "mdi_id", "file": "mdi:weather-##", "type": "rgb565"})

    with pytest.raises(
        cv.Invalid, match="Image format 'BINARY' cannot have transparency"
    ):
        CONFIG_SCHEMA(
            {
                "id": "image_id",
                "file": "image.png",
                "type": "binary",
                "transparency": "alpha_channel",
            }
        )

    with pytest.raises(cv.Invalid, match="No alpha channel to invert"):
        CONFIG_SCHEMA(
            {
                "id": "image_id",
                "file": "image.png",
                "type": "rgb565",
                "transparency": "chroma_key",
                "invert_alpha": True,
            }
        )

    with pytest.raises(
        cv.Invalid,
        match="Image format 'BINARY' does not support byte order configuration",
    ):
        CONFIG_SCHEMA(
            {
                "id": "image_id",
                "file": "image.png",
                "type": "binary",
                "byte_order": "big_endian",
            }
        )

    with pytest.raises(cv.Invalid, match="File can't be opened as image"):
        CONFIG_SCHEMA({"id": "image_id", "file": "bad.png", "type": "binary"})

    with pytest.raises(
        cv.Invalid,
        match="Type is required either in the image config or in the defaults",
    ):
        CONFIG_SCHEMA(
            {"defaults": {}, "images": [{"id": "image_id", "file": "image.png"}]}
        )


@pytest.mark.parametrize(
    "config",
    [
        pytest.param(
            {
                "id": "image_id",
                "file": "image.png",
                "type": "rgb565",
                "transparency": "chroma_key",
                "byte_order": "little_endian",
                "dither": "FloydSteinberg",
                "resize": "100x100",
                "invert_alpha": False,
            },
            id="single_image_all_options",
        ),
        pytest.param(
            [
                {
                    "id": "image_id",
                    "file": "image.png",
                    "type": "binary",
                }
            ],
            id="list_of_images",
        ),
        pytest.param(
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
            },
            id="images_with_defaults",
        ),
        pytest.param(
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
            },
            id="type_based_organization",
        ),
    ],
)
def test_image_configuration_success(
    config: dict[str, Any] | list[dict[str, Any]],
) -> None:
    """Test successful configuration validation."""
    CONFIG_SCHEMA(config)


def test_image_generation(
    generate_main: Callable[[str | Path], str],
    component_config_path: Callable[[str], Path],
) -> None:
    """Test image generation configuration."""

    main_cpp: str = generate_main(component_config_path("image_test.yaml"))
    assert "uint8_t_id[] PROGMEM = {0x24, 0x21, 0x24, 0x21" in main_cpp
    assert (
        "cat_img = new image::Image(uint8_t_id, 32, 24, image::IMAGE_TYPE_RGB565, image::TRANSPARENCY_OPAQUE);"
        in main_cpp
    )
