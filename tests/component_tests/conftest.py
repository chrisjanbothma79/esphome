"""Fixtures for component tests."""

from __future__ import annotations

from collections.abc import Callable, Generator
from pathlib import Path
import sys
from typing import Any

import pytest

from esphome import config, final_validate
from esphome.components.esp32 import KEY_BOARD, KEY_ESP32, VARIANTS
from esphome.components.esp32.gpio import validate_gpio_pin
import esphome.config_validation as cv
from esphome.const import (
    KEY_CORE,
    KEY_TARGET_FRAMEWORK,
    KEY_TARGET_PLATFORM,
    KEY_VARIANT,
    PlatformFramework,
)
from esphome.pins import internal_gpio_pin_number

# Add package root to python path
here = Path(__file__).parent
package_root = here.parent.parent
sys.path.insert(0, package_root.as_posix())

from esphome.__main__ import generate_cpp_contents  # noqa: E402
from esphome.config import Config, read_config  # noqa: E402
from esphome.core import CORE  # noqa: E402


@pytest.fixture(autouse=True)
def config_path(request: pytest.FixtureRequest) -> Generator[None]:
    """Set CORE.config_path to the component's config directory and reset it after the test."""
    original_path = CORE.config_path
    config_dir = Path(request.fspath).parent / "config"

    # Check if config directory exists, if not use parent directory
    if config_dir.exists():
        # Set config_path to a dummy yaml file in the config directory
        # This ensures CORE.config_dir points to the config directory
        CORE.config_path = str(config_dir / "dummy.yaml")
    else:
        CORE.config_path = str(Path(request.fspath).parent / "dummy.yaml")

    yield
    CORE.config_path = original_path


@pytest.fixture(autouse=True)
def reset_core() -> Generator[None]:
    """Reset CORE after each test."""
    yield
    CORE.reset()


@pytest.fixture
def get_path(request: pytest.FixtureRequest) -> Callable[[str], Path]:
    """Fixture to get the absolute path of a file relative to the test script."""

    def getter(filename: str) -> Path:
        return (Path(request.fspath).parent / filename).absolute()

    return getter


@pytest.fixture
def set_core_config(request: pytest.FixtureRequest) -> Generator[Callable[..., None]]:
    """Fixture to set up the core configuration for tests."""

    def setter(
        platform_framework: PlatformFramework,
        /,
        *,
        board: str,
        variant: str | None = None,
        path: str | None = None,
    ) -> None:
        platform, framework = platform_framework.value
        if path is None:
            path = str(Path(request.fspath).parent / "dummy.yaml")
        CORE.config_path = path
        CORE.data[KEY_CORE] = {
            KEY_TARGET_PLATFORM: platform.value,
            KEY_TARGET_FRAMEWORK: framework.value,
        }
        CORE.data[platform.value] = {
            KEY_VARIANT: variant,
            KEY_BOARD: board,
        }
        config.path_context.set([])
        final_validate.full_config.set(Config())

    yield setter


@pytest.fixture
def set_component_config() -> Callable[[str, Any], None]:
    """
    Fixture to set a component configuration in the mock config.
    This must be used after the core configuration has been set up.
    """

    def setter(name: str, value: Any) -> None:
        final_validate.full_config.get()[name] = value

    return setter


@pytest.fixture
def choose_variant_with_pins() -> Callable[..., None]:
    """
    Set the ESP32 variant for the given model based on pins. For ESP32 only since the other platforms
    do not have variants.
    """

    def chooser(*pins: int | str | None) -> None:
        for v in VARIANTS:
            try:
                CORE.data[KEY_ESP32][KEY_VARIANT] = v
                for pin in pins:
                    if pin is not None:
                        pin = internal_gpio_pin_number(pin)
                        validate_gpio_pin(pin)
                return
            except cv.Invalid:
                continue

    return chooser


@pytest.fixture
def component_fixture_path(request: pytest.FixtureRequest) -> Callable[[str], Path]:
    """Return a function to get absolute paths relative to the component's fixtures directory."""

    def _get_path(file_name: str) -> Path:
        """Get the absolute path of a file relative to the component's fixtures directory."""
        return (Path(request.fspath).parent / "fixtures" / file_name).absolute()

    return _get_path


@pytest.fixture
def component_config_path(request: pytest.FixtureRequest) -> Callable[[str], Path]:
    """Return a function to get absolute paths relative to the component's config directory."""

    def _get_path(file_name: str) -> Path:
        """Get the absolute path of a file relative to the component's config directory."""
        return (Path(request.fspath).parent / "config" / file_name).absolute()

    return _get_path


@pytest.fixture
def generate_main() -> Generator[Callable[[str | Path], str]]:
    """Generates the C++ main.cpp from a given yaml file and returns it in string form."""

    def generator(path: str | Path) -> str:
        CORE.config_path = str(path)
        CORE.config = read_config({})
        generate_cpp_contents(CORE.config)
        return CORE.cpp_main_section

    yield generator
