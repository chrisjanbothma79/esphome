"""Test get_base_entity_object_id function matches C++ behavior."""

from esphome.core import CORE
from esphome.entity import get_base_entity_object_id
from esphome.helpers import sanitize, snake_case


class TestGetBaseEntityObjectId:
    """Test that get_base_entity_object_id matches C++ EntityBase::get_object_id behavior."""

    def test_with_entity_name(self) -> None:
        """Test when entity has its own name - should use entity name."""
        # Simple name
        assert (
            get_base_entity_object_id("Temperature Sensor", None)
            == "temperature_sensor"
        )
        assert (
            get_base_entity_object_id("Temperature Sensor", "Device Name")
            == "temperature_sensor"
        )

        # Name with special characters
        assert (
            get_base_entity_object_id("Temp!@#$%^&*()Sensor", None)
            == "temp__________sensor"
        )
        assert get_base_entity_object_id("Temp-Sensor_123", None) == "temp-sensor_123"

        # Already snake_case
        assert (
            get_base_entity_object_id("temperature_sensor", None)
            == "temperature_sensor"
        )

        # Mixed case
        assert (
            get_base_entity_object_id("TemperatureSensor", None) == "temperaturesensor"
        )
        assert (
            get_base_entity_object_id("TEMPERATURE SENSOR", None)
            == "temperature_sensor"
        )

    def test_empty_name_with_friendly_name(self) -> None:
        """Test when entity has empty name - should use friendly name."""
        # C++ behavior: when has_own_name is false, uses App.get_friendly_name()
        assert get_base_entity_object_id("", "Friendly Device") == "friendly_device"
        assert (
            get_base_entity_object_id("", "Kitchen Controller") == "kitchen_controller"
        )
        assert get_base_entity_object_id("", "Test-Device_123") == "test-device_123"

        # Special characters in friendly name
        assert get_base_entity_object_id("", "Device!@#$%") == "device_____"

    def test_empty_name_no_friendly_name(self) -> None:
        """Test when entity has empty name and no friendly name - should use device name."""
        # Save original values
        original_name = getattr(CORE, "name", None)

        try:
            # Test with CORE.name set
            CORE.name = "device-name"
            assert get_base_entity_object_id("", None) == "device-name"

            CORE.name = "Test Device"
            assert get_base_entity_object_id("", None) == "test_device"

        finally:
            # Restore original value
            if original_name is not None:
                CORE.name = original_name

    def test_edge_cases(self) -> None:
        """Test edge cases."""
        # Only spaces
        assert get_base_entity_object_id("   ", None) == "___"

        # Unicode characters (should be replaced)
        assert get_base_entity_object_id("Température", None) == "temp_rature"
        assert get_base_entity_object_id("测试", None) == "__"

        # Empty string with empty friendly name (empty friendly name is treated as None)
        # Falls back to CORE.name
        original_name = getattr(CORE, "name", None)
        try:
            CORE.name = "device"
            assert get_base_entity_object_id("", "") == "device"
        finally:
            if original_name is not None:
                CORE.name = original_name

        # Very long name (should work fine)
        long_name = "a" * 100 + " " + "b" * 100
        expected = "a" * 100 + "_" + "b" * 100
        assert get_base_entity_object_id(long_name, None) == expected

    def test_matches_cpp_helpers(self) -> None:
        """Test that the logic matches using snake_case and sanitize directly."""
        test_cases = [
            ("Temperature Sensor", "temperature_sensor"),
            ("Living Room Light", "living_room_light"),
            ("Test-Device_123", "test-device_123"),
            ("Special!@#Chars", "special___chars"),
            ("UPPERCASE NAME", "uppercase_name"),
            ("lowercase name", "lowercase_name"),
            ("Mixed Case Name", "mixed_case_name"),
            ("   Spaces   ", "___spaces___"),
        ]

        for name, expected in test_cases:
            # For non-empty names, verify our function produces same result as direct snake_case + sanitize
            assert get_base_entity_object_id(name, None) == sanitize(snake_case(name))
            assert get_base_entity_object_id(name, None) == expected

        # Empty name is handled specially - it doesn't just use sanitize(snake_case(""))
        # Instead it falls back to friendly_name or CORE.name
        assert sanitize(snake_case("")) == ""  # Direct conversion gives empty string
        # But our function returns a fallback
        original_name = getattr(CORE, "name", None)
        try:
            CORE.name = "device"
            assert get_base_entity_object_id("", None) == "device"  # Uses device name
        finally:
            if original_name is not None:
                CORE.name = original_name

    def test_name_add_mac_suffix_behavior(self) -> None:
        """Test behavior related to name_add_mac_suffix.

        In C++, when name_add_mac_suffix is enabled and entity has no name,
        get_object_id() returns str_sanitize(str_snake_case(App.get_friendly_name()))
        dynamically. Our function always returns the same result since we're
        calculating the base for duplicate tracking.
        """
        # The function should always return the same result regardless of
        # name_add_mac_suffix setting, as we're calculating the base object_id
        assert get_base_entity_object_id("", "Test Device") == "test_device"
        assert get_base_entity_object_id("Entity Name", "Test Device") == "entity_name"
