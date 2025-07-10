"""
Test ESP32 configuration
"""

from esphome.components.esp32 import STANDARD_BOARDS
from esphome.const import PlatformFramework


def test_esp32_config(set_core_config) -> None:
    set_core_config(PlatformFramework.ESP32_IDF)

    from esphome.components.esp32 import CONFIG_SCHEMA
    from esphome.components.esp32.const import VARIANT_ESP32, VARIANT_FRIENDLY

    # Example ESP32 configuration
    config = {
        "board": "esp32dev",
        "variant": VARIANT_ESP32,
        "cpu_frequency": "240MHz",
        "flash_size": "4MB",
        "framework": {
            "type": "esp-idf",
        },
    }

    # Check if the variant is valid
    config = CONFIG_SCHEMA(config)
    assert config["variant"] == VARIANT_ESP32

    # Check that defining a variant sets the board name correctly
    for variant in STANDARD_BOARDS:
        config = CONFIG_SCHEMA(
            {
                "variant": variant,
            }
        )
        assert VARIANT_FRIENDLY[variant].lower() in config["board"]
