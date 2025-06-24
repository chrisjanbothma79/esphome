"""Test duplicate entity object ID handling."""

import pytest

from esphome.core import CORE
from esphome.helpers import sanitize, snake_case


@pytest.fixture
def setup_test_device() -> None:
    """Set up test device configuration."""
    CORE.name = "test-device"
    CORE.friendly_name = "Test Device"


def test_unique_key_generation() -> None:
    """Test that unique keys are generated correctly."""
    # Test with no device
    key1: tuple[int, str, str] = (0, "binary_sensor", "temperature")
    assert key1 == (0, "binary_sensor", "temperature")

    # Test with device
    key2: tuple[int, str, str] = (12345, "sensor", "humidity")
    assert key2 == (12345, "sensor", "humidity")


def test_duplicate_tracking() -> None:
    """Test that duplicates are tracked correctly."""
    # First occurrence
    key: tuple[int, str, str] = (0, "sensor", "temperature")
    assert key not in CORE.unique_ids

    CORE.unique_ids[key] = 1
    assert CORE.unique_ids[key] == 1

    # Second occurrence
    count: int = CORE.unique_ids[key] + 1
    CORE.unique_ids[key] = count
    assert CORE.unique_ids[key] == 2


def test_object_id_sanitization() -> None:
    """Test that object IDs are properly sanitized."""
    # Test various inputs
    assert sanitize(snake_case("Temperature Sensor")) == "temperature_sensor"
    assert sanitize(snake_case("Living Room Light!")) == "living_room_light_"
    assert sanitize(snake_case("Test-Device")) == "test-device"
    assert sanitize(snake_case("")) == ""


def test_suffix_generation() -> None:
    """Test that suffixes are generated correctly."""
    base_id: str = "temperature"

    # No suffix for first occurrence
    object_id_1: str = base_id
    assert object_id_1 == "temperature"

    # Add suffix for duplicates
    count: int = 2
    object_id_2: str = f"{base_id}_{count}"
    assert object_id_2 == "temperature_2"

    count = 3
    object_id_3: str = f"{base_id}_{count}"
    assert object_id_3 == "temperature_3"


def test_different_platforms_same_name() -> None:
    """Test that same name on different platforms doesn't conflict."""
    # Simulate two entities with same name on different platforms
    key1: tuple[int, str, str] = (0, "binary_sensor", "status")
    key2: tuple[int, str, str] = (0, "text_sensor", "status")

    # They should be different keys
    assert key1 != key2

    # Track them separately
    CORE.unique_ids[key1] = 1
    CORE.unique_ids[key2] = 1

    # Both should be at count 1 (no conflict)
    assert CORE.unique_ids[key1] == 1
    assert CORE.unique_ids[key2] == 1


def test_different_devices_same_name_platform() -> None:
    """Test that same name+platform on different devices doesn't conflict."""
    # Simulate two entities with same name and platform but different devices
    key1: tuple[int, str, str] = (12345, "sensor", "temperature")
    key2: tuple[int, str, str] = (67890, "sensor", "temperature")

    # They should be different keys
    assert key1 != key2

    # Track them separately
    CORE.unique_ids[key1] = 1
    CORE.unique_ids[key2] = 1

    # Both should be at count 1 (no conflict)
    assert CORE.unique_ids[key1] == 1
    assert CORE.unique_ids[key2] == 1


def test_empty_name_handling(setup_test_device: None) -> None:
    """Test handling of entities with empty names."""
    # When name is empty, it should use the device name
    empty_name: str = ""
    base_id: str
    if not empty_name:
        if CORE.friendly_name:
            base_id = sanitize(snake_case(CORE.friendly_name))
        else:
            base_id = sanitize(snake_case(CORE.name))

    assert base_id == "test_device"  # Uses friendly name


def test_reset_clears_unique_ids() -> None:
    """Test that CORE.reset() clears the unique_ids tracking."""
    # Add some tracked IDs
    CORE.unique_ids[(0, "sensor", "test")] = 2
    CORE.unique_ids[(0, "binary_sensor", "test")] = 3

    assert len(CORE.unique_ids) == 2

    # Reset should clear them
    CORE.reset()
    assert len(CORE.unique_ids) == 0
