"""Fixtures for component tests."""

from __future__ import annotations

from collections.abc import Callable, Generator
from pathlib import Path
import sys

import pytest

# Add package root to python path
here: Path = Path(__file__).parent
package_root: Path = here.parent.parent
sys.path.insert(0, package_root.as_posix())

from esphome.__main__ import generate_cpp_contents  # noqa: E402
from esphome.config import read_config  # noqa: E402
from esphome.core import CORE  # noqa: E402


@pytest.fixture(autouse=True)
def config_path(request: pytest.FixtureRequest) -> Generator[None]:
    """Set CORE.config_path to the test file's path and reset it after the test."""
    original_path: str | None = CORE.config_path
    CORE.config_path = str(request.fspath)
    yield
    CORE.config_path = original_path


@pytest.fixture
def generate_main() -> Generator[Callable[[str | Path], str]]:
    """Generates the C++ main.cpp file and returns it in string form."""

    def generator(path: str | Path) -> str:
        CORE.config_path = str(path)
        CORE.config = read_config({})
        generate_cpp_contents(CORE.config)
        print(CORE.cpp_main_section)
        return CORE.cpp_main_section

    yield generator

    CORE.reset()
