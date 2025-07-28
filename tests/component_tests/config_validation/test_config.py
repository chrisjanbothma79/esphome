"""
Test ESP32 configuration
"""

from typing import Any

import esphome.config_validation as cv


def test_config_extend() -> None:
    """Test that schema.extend correctly merges schemas with extras."""

    def func1(data: dict[str, Any]) -> dict[str, Any]:
        data["extra_1"] = "value1"
        return data

    def func2(data: dict[str, Any]) -> dict[str, Any]:
        data["extra_2"] = "value2"
        return data

    schema1 = cv.Schema(
        {
            cv.Required("key1"): cv.string,
        }
    )
    schema1.add_extra(func1)
    schema2 = cv.Schema(
        {
            cv.Required("key2"): cv.string,
        }
    )
    schema2.add_extra(func2)
    extended_schema1 = schema1.extend(schema2)
    config = {
        "key1": "initial_value1",
        "key2": "initial_value2",
    }
    config = extended_schema1(config)
    assert config["key1"] == "initial_value1"
    assert config["key2"] == "initial_value2"
    assert config["extra_1"] == "value1"
    assert config["extra_2"] == "value2"
