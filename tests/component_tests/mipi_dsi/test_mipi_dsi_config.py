"""Tests for mpip_spi configuration validation."""

import pytest

from esphome import config_validation as cv
from esphome.components.esp32 import FRAMEWORK_ESP_IDF, VARIANT_ESP32P4
from esphome.const import (
    CONF_DIMENSIONS,
    CONF_HEIGHT,
    CONF_INIT_SEQUENCE,
    CONF_WIDTH,
    PLATFORM_ESP32,
)


def test_configuration_errors(set_core_config) -> None:
    """Test detection of invalid configuration"""

    set_core_config(PLATFORM_ESP32, FRAMEWORK_ESP_IDF, "esp32dev", VARIANT_ESP32P4)

    from esphome.components.mipi_dsi.display import CONFIG_SCHEMA

    with pytest.raises(cv.Invalid, match="expected a dictionary"):
        CONFIG_SCHEMA("a string")

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['model'\]"
    ):
        CONFIG_SCHEMA({"id": "display_id"})

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['dimensions'\]"
    ):
        CONFIG_SCHEMA(
            {"id": "display_id", "model": "custom", "init_sequence": [[0x36, 0x01]]}
        )

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['init_sequence'\]"
    ):
        CONFIG_SCHEMA(
            {
                "model": "custom",
                "dimensions": {"width": 320, "height": 240},
            }
        )


def test_configuration_success(
    set_core_config, set_component_config, choose_variant_with_pins
) -> None:
    """Test successful configuration validation."""
    set_core_config(PLATFORM_ESP32, FRAMEWORK_ESP_IDF, "esp32dev", VARIANT_ESP32P4)

    from esphome.components.mipi_dsi.display import CONFIG_SCHEMA, MODELS

    # Custom model with all options
    CONFIG_SCHEMA(
        {
            "model": "custom",
            "pixel_mode": "16bit",
            "id": "display_id",
            "byte_order": "little_endian",
            "color_order": "rgb",
            "reset_pin": 12,
            "init_sequence": [[0xA0, 0x01]],
            "dimensions": {
                "width": 320,
                "height": 240,
            },
            "invert_colors": True,
            "transform": {"mirror_x": True, "mirror_y": True, "swap_xy": False},
            "data_rate": "40MHz",
            "use_axis_flips": True,
        }
    )

    # Test all models, providing default values where necessary
    for name, model in MODELS.items():
        config = {"model": name}
        if model.initsequence is None:
            config[CONF_INIT_SEQUENCE] = [[0xA0, 0x01]]
        if not model.get_default(CONF_DIMENSIONS):
            config[CONF_DIMENSIONS] = {CONF_WIDTH: 400, CONF_HEIGHT: 300}
        CONFIG_SCHEMA(config)


def test_native_generation(generate_main, get_path) -> None:
    """Test code generation for display."""

    main_cpp = generate_main(get_path("native.yaml"))
    assert (
        "mipi_dsi::MipiSpiBuffer<uint16_t, mipi_dsi::PIXEL_MODE_16, true, mipi_dsi::PIXEL_MODE_16, mipi_dsi::BUS_TYPE_QUAD, 360, 360, 0, 1, display::DISPLAY_ROTATION_0_DEGREES, 1>()"
        in main_cpp
    )
    assert "set_init_sequence({240, 1, 8, 242" in main_cpp
    assert "show_test_card();" in main_cpp
    assert "set_write_only(true);" in main_cpp


def test_lvgl_generation(generate_main, get_path) -> None:
    main_cpp = generate_main(get_path("lvgl.yaml"))
    assert (
        "mipi_dsi::MipiSpi<uint16_t, mipi_dsi::PIXEL_MODE_16, true, mipi_dsi::PIXEL_MODE_16, mipi_dsi::BUS_TYPE_SINGLE, 128, 160, 0, 0>();"
        in main_cpp
    )
    assert "set_init_sequence({1, 0, 10, 255, 177" in main_cpp
    assert "show_test_card();" not in main_cpp
    assert "set_auto_clear(false);" in main_cpp
