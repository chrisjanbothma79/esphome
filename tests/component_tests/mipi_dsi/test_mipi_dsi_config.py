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
        cv.Invalid,
        match=r"string value is None for dictionary value @ data\['lane_bit_rate'\]",
    ):
        CONFIG_SCHEMA(
            {"id": "display_id", "model": "custom", "init_sequence": [[0x36, 0x01]]}
        )

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['dimensions'\]"
    ):
        CONFIG_SCHEMA(
            {
                "id": "display_id",
                "model": "custom",
                "init_sequence": [[0x36, 0x01]],
                "lane_bit_rate": "1.5Gbps",
            }
        )

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['init_sequence'\]"
    ):
        CONFIG_SCHEMA(
            {
                "model": "custom",
                "lane_bit_rate": "1.5Gbps",
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
            "transform": {"mirror_x": True, "mirror_y": True},
            "pclk_frequency": "40MHz",
            "lane_bit_rate": "1.5Gbps",
            "lanes": 2,
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
        if not model.get_default("lane_bit_rate"):
            config["lane_bit_rate"] = "1.5Gbps"
        CONFIG_SCHEMA(config)


def test_code_generation(generate_main, get_path) -> None:
    """Test code generation for display."""

    main_cpp = generate_main(get_path("mipi_dsi.yaml"))
    assert "new mipi_dsi::MIPI_DSI(800, 1280);" in main_cpp
    assert "set_init_sequence({224, 1, 0, 225, 1, 147, 226, 1," in main_cpp
    assert "mipi_dsi_mipi_dsi_id->set_lane_bit_rate(1500);" in main_cpp
    assert "backlight_id = new light::LightState(mipi_dsi_dsibacklight_id);" in main_cpp
