"""Tests for mpip_spi configuration validation."""

import pytest

from esphome import config_validation as cv
from esphome.components.esp32 import (
    FRAMEWORK_ARDUINO,
    FRAMEWORK_ESP_IDF,
    VARIANT_ESP32,
    VARIANT_ESP32S3,
)
from esphome.const import (
    CONF_DC_PIN,
    CONF_DIMENSIONS,
    CONF_HEIGHT,
    CONF_INIT_SEQUENCE,
    CONF_WIDTH,
    PLATFORM_ESP32,
)


def test_configuration_errors(
    core_reset, set_core_config, choose_variant_with_pins
) -> None:
    """Test detection of invalid configuration"""

    set_core_config(PLATFORM_ESP32, FRAMEWORK_ESP_IDF, "esp32dev", VARIANT_ESP32)

    from esphome.components.mipi_spi.display import dimension_schema

    def test_config(config):
        from esphome.components.mipi_spi.display import (
            CONFIG_SCHEMA,
            FINAL_VALIDATE_SCHEMA,
        )

        FINAL_VALIDATE_SCHEMA(CONFIG_SCHEMA(config))

    with pytest.raises(cv.Invalid, match="expected a dictionary"):
        test_config("a string")

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['model'\]"
    ):
        test_config({"id": "display_id"})

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['dimensions'\]"
    ):
        test_config(
            {"id": "display_id", "model": "custom", "init_sequence": [[0x36, 0x01]]}
        )

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['init_sequence'\]"
    ):
        test_config(
            {
                "model": "custom",
                "dc_pin": 18,
                "dimensions": {"width": 320, "height": 240},
            }
        )

    with pytest.raises(
        cv.Invalid,
        match=r"value must be a power of two for dictionary value @ data\['draw_rounding'\]",
    ):
        test_config(
            {
                "id": "display_id",
                "model": "custom",
                "dimensions": {"width": 320, "height": 240},
                "draw_rounding": 13,
            }
        )

    with pytest.raises(
        cv.Invalid, match=r"required key not provided @ data\['height'\]"
    ):
        dimension_schema(4)({"width": 320})

    with pytest.raises(
        cv.Invalid, match="Dimensions and offsets must be divisible by 32"
    ):
        dimension_schema(32)({"width": 320, "height": 111})

    with pytest.raises(cv.Invalid, match="Axis swapping not supported by this model"):
        test_config(
            {
                "model": "JC3248W535",
                "transform": {"mirror_x": False, "mirror_y": True, "swap_xy": True},
            }
        )

    with pytest.raises(
        cv.Invalid,
        match=r"transform is not supported when MADCTL \(0X36\) is in the init sequence",
    ):
        test_config(
            {
                "model": "custom",
                "dimensions": {"width": 320, "height": 240},
                "transform": {"mirror_x": False, "mirror_y": True, "swap_xy": False},
                "init_sequence": [[0x36, 0x01]],
            }
        )

    with pytest.raises(
        cv.Invalid,
        match=r"PIXFMT \(0X3A\) should not be in the init sequence, it will be set automatically",
    ):
        test_config(
            {
                "model": "custom",
                "dimensions": {"width": 320, "height": 240},
                "init_sequence": [[0x3A, 0x01]],
            }
        )

    set_core_config(PLATFORM_ESP32, FRAMEWORK_ESP_IDF, "esp32dev", VARIANT_ESP32S3)

    with pytest.raises(cv.Invalid, match="DC pin is not supported in quad mode"):
        test_config({"model": "t4-s3", "dc_pin": 18})

    with pytest.raises(
        cv.Invalid, match="Unknown value '18', valid options are '16', '16bit"
    ):
        test_config({"model": "t4-s3", "color_depth": 18})

    with pytest.raises(
        cv.Invalid, match="Unknown value '24', valid options are '16', '8"
    ):
        test_config({"model": "t-embed", "color_depth": 24})

    with pytest.raises(cv.Invalid, match="DC pin is required in single mode"):
        test_config({"model": "ili9488"})

    # Brightness is not supported except for specific models
    with pytest.raises(
        cv.Invalid, match=r"extra keys not allowed @ data\['brightness'\]"
    ):
        test_config({"model": "wt32-sc01-plus", "brightness": 128})

    with pytest.raises(cv.Invalid, match="PSRAM is required for this display"):
        test_config({"model": "T-DISPLAY-S3-PRO"})

    set_core_config(PLATFORM_ESP32, FRAMEWORK_ARDUINO, "esp32dev", VARIANT_ESP32)

    with pytest.raises(
        cv.Invalid,
        match=r"This feature is only available with frameworks \['esp-idf'\]",
    ):
        test_config({"model": "wt32-sc01-plus"})

    core_reset()


def test_configuration_success(
    set_core_config, set_component_config, choose_variant_with_pins
) -> None:
    """Test successful configuration validation."""
    set_core_config(PLATFORM_ESP32, FRAMEWORK_ESP_IDF, "esp32dev", VARIANT_ESP32S3)

    from esphome.components.mipi_spi.display import (
        CONF_BUS_MODE,
        CONF_NATIVE_HEIGHT,
        MODELS,
    )

    def success(config):
        from esphome.components.mipi_spi.display import (
            CONFIG_SCHEMA,
            FINAL_VALIDATE_SCHEMA,
        )

        FINAL_VALIDATE_SCHEMA(CONFIG_SCHEMA(config))

    # Custom model with all options
    success(
        {
            "model": "custom",
            "pixel_mode": "18bit",
            "color_depth": 8,
            "id": "display_id",
            "byte_order": "little_endian",
            "bus_mode": "single",
            "color_order": "rgb",
            "dc_pin": 11,
            "reset_pin": 12,
            "enable_pin": 13,
            "cs_pin": 14,
            "init_sequence": [[0xA0, 0x01]],
            "dimensions": {
                "width": 320,
                "height": 240,
                "offset_width": 32,
                "offset_height": 32,
            },
            "invert_colors": True,
            "transform": {"mirror_x": True, "mirror_y": True, "swap_xy": False},
            "spi_mode": "mode0",
            "data_rate": "40MHz",
            "use_axis_flips": True,
            "draw_rounding": 4,
            "spi_16": True,
            "buffer_size": 0.25,
        }
    )

    # Enable PSRAM for the remainder
    set_component_config("psram", True)

    # Test all models, providing default values where necessary
    for name, model in MODELS.items():
        config = {"model": name}
        pins = [
            pin
            for pin in [
                model.get_default(pin, None)
                for pin in ("dc_pin", "reset_pin", "cs_pin")
            ]
            if pin is not None
        ]
        choose_variant_with_pins(pins)

        if (
            not model.get_default(CONF_DC_PIN)
            and model.get_default(CONF_BUS_MODE) != "quad"
        ):
            config[CONF_DC_PIN] = 14
        if not model.get_default(CONF_NATIVE_HEIGHT):
            config[CONF_DIMENSIONS] = {CONF_HEIGHT: 240, CONF_WIDTH: 320}
        if model.initsequence is None:
            config[CONF_INIT_SEQUENCE] = [[0xA0, 0x01]]
        success(config)


def test_native_generation(generate_main, get_path) -> None:
    """Test code generation for display."""

    main_cpp = generate_main(get_path("native.yaml"))
    assert (
        "mipi_spi::MipiSpiBuffer<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_QUAD, 360, 360, 0, 1, display::DISPLAY_ROTATION_0_DEGREES, 1>()"
        in main_cpp
    )
    assert "set_init_sequence({240, 1, 8, 242" in main_cpp
    assert "show_test_card();" in main_cpp
    assert "set_write_only(true);" in main_cpp


def test_lvgl_generation(generate_main, get_path) -> None:
    main_cpp = generate_main(get_path("lvgl.yaml"))
    assert (
        "mipi_spi::MipiSpi<uint16_t, mipi_spi::PIXEL_MODE_16, true, mipi_spi::PIXEL_MODE_16, mipi_spi::BUS_TYPE_SINGLE, 128, 160, 0, 0>();"
        in main_cpp
    )
    assert "set_init_sequence({1, 0, 10, 255, 177" in main_cpp
    assert "show_test_card();" not in main_cpp
    assert "set_auto_clear(false);" in main_cpp
