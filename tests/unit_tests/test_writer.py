"""Test writer module functionality."""

from collections.abc import Callable
from typing import Any

import pytest

from esphome.storage_json import StorageJSON
from esphome.writer import storage_should_clean


@pytest.fixture
def create_storage() -> Callable[..., StorageJSON]:
    """Factory fixture to create StorageJSON instances."""

    def _create(
        loaded_integrations: list[str] | None = None, **kwargs: Any
    ) -> StorageJSON:
        return StorageJSON(
            storage_version=kwargs.get("storage_version", 1),
            name=kwargs.get("name", "test"),
            friendly_name=kwargs.get("friendly_name", "Test Device"),
            comment=kwargs.get("comment"),
            esphome_version=kwargs.get("esphome_version", "2025.1.0"),
            src_version=kwargs.get("src_version", 1),
            address=kwargs.get("address", "test.local"),
            web_port=kwargs.get("web_port", 80),
            target_platform=kwargs.get("target_platform", "ESP32"),
            build_path=kwargs.get("build_path", "/build"),
            firmware_bin_path=kwargs.get("firmware_bin_path", "/firmware.bin"),
            loaded_integrations=set(loaded_integrations or []),
            loaded_platforms=kwargs.get("loaded_platforms", set()),
            no_mdns=kwargs.get("no_mdns", False),
            framework=kwargs.get("framework", "arduino"),
            core_platform=kwargs.get("core_platform", "esp32"),
        )

    return _create


def test_storage_should_clean_when_old_is_none(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is triggered when old storage is None."""
    new = create_storage(loaded_integrations=["api", "wifi"])
    assert storage_should_clean(None, new) is True


def test_storage_should_clean_when_src_version_changes(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is triggered when src_version changes."""
    old = create_storage(loaded_integrations=["api", "wifi"], src_version=1)
    new = create_storage(loaded_integrations=["api", "wifi"], src_version=2)
    assert storage_should_clean(old, new) is True


def test_storage_should_clean_when_build_path_changes(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is triggered when build_path changes."""
    old = create_storage(loaded_integrations=["api", "wifi"], build_path="/build1")
    new = create_storage(loaded_integrations=["api", "wifi"], build_path="/build2")
    assert storage_should_clean(old, new) is True


def test_storage_should_clean_when_component_removed(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is triggered when a component is removed."""
    old = create_storage(
        loaded_integrations=["api", "wifi", "bluetooth_proxy", "esp32_ble_tracker"]
    )
    new = create_storage(loaded_integrations=["api", "wifi", "esp32_ble_tracker"])
    assert storage_should_clean(old, new) is True


def test_storage_should_clean_when_multiple_components_removed(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is triggered when multiple components are removed."""
    old = create_storage(
        loaded_integrations=["api", "wifi", "ota", "web_server", "logger"]
    )
    new = create_storage(loaded_integrations=["api", "wifi", "logger"])
    assert storage_should_clean(old, new) is True


def test_storage_should_not_clean_when_nothing_changes(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is not triggered when nothing changes."""
    old = create_storage(loaded_integrations=["api", "wifi", "logger"])
    new = create_storage(loaded_integrations=["api", "wifi", "logger"])
    assert storage_should_clean(old, new) is False


def test_storage_should_not_clean_when_component_added(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is not triggered when a component is only added."""
    old = create_storage(loaded_integrations=["api", "wifi"])
    new = create_storage(loaded_integrations=["api", "wifi", "ota"])
    assert storage_should_clean(old, new) is False


def test_storage_should_not_clean_when_other_fields_change(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test that clean is not triggered when non-relevant fields change."""
    old = create_storage(
        loaded_integrations=["api", "wifi"],
        friendly_name="Old Name",
        esphome_version="2024.12.0",
    )
    new = create_storage(
        loaded_integrations=["api", "wifi"],
        friendly_name="New Name",
        esphome_version="2025.1.0",
    )
    assert storage_should_clean(old, new) is False


def test_storage_edge_case_empty_integrations(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test edge case when old has integrations but new has none."""
    old = create_storage(loaded_integrations=["api", "wifi"])
    new = create_storage(loaded_integrations=[])
    assert storage_should_clean(old, new) is True


def test_storage_edge_case_from_empty_integrations(
    create_storage: Callable[..., StorageJSON],
) -> None:
    """Test edge case when old has no integrations but new has some."""
    old = create_storage(loaded_integrations=[])
    new = create_storage(loaded_integrations=["api", "wifi"])
    assert storage_should_clean(old, new) is False
