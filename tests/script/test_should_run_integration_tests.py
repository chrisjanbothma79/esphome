"""Unit tests for script/should_run_integration_tests.py module."""

from collections.abc import Generator
import os
from pathlib import Path
import sys
from typing import Any
from unittest.mock import Mock, mock_open, patch

import pytest
import yaml

# Add the script directory to Python path so we can import the module
sys.path.insert(
    0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "script"))
)

import should_run_integration_tests  # noqa: E402


@pytest.fixture
def mock_changed_files() -> Generator[Mock, None, None]:
    """Mock the changed_files function from helpers."""
    with patch("should_run_integration_tests.changed_files") as mock:
        yield mock


@pytest.fixture
def mock_glob() -> Generator[Mock, None, None]:
    """Mock pathlib.Path.glob."""
    with patch("pathlib.Path.glob") as mock:
        yield mock


@pytest.fixture
def mock_open_file() -> Generator[Mock, None, None]:
    """Mock builtins.open."""
    with patch("builtins.open", mock_open()) as mock:
        yield mock


@pytest.fixture
def mock_yaml_load() -> Generator[Mock, None, None]:
    """Mock yaml.safe_load."""
    with patch("yaml.safe_load") as mock:
        yield mock


@pytest.fixture
def mock_get_component() -> Generator[Mock, None, None]:
    """Mock get_component from esphome.loader."""
    with patch("should_run_integration_tests.get_component") as mock:
        yield mock


@pytest.fixture
def mock_get_fixtures() -> Generator[Mock, None, None]:
    """Mock get_components_from_fixtures."""
    with patch("should_run_integration_tests.get_components_from_fixtures") as mock:
        yield mock


@pytest.fixture
def mock_get_deps() -> Generator[Mock, None, None]:
    """Mock get_all_dependencies."""
    with patch("should_run_integration_tests.get_all_dependencies") as mock:
        yield mock


@pytest.fixture
def mock_argv_with_branch() -> Generator[None, None, None]:
    """Mock sys.argv with branch argument."""
    with patch("sys.argv", ["script.py", "-b", "main"]):
        yield


@pytest.mark.parametrize(
    ("yaml_content", "expected_components"),
    [
        # Test extraction of top-level components and platforms
        (
            {
                "sensor": [{"platform": "template", "name": "test"}],
                "binary_sensor": [{"platform": "gpio", "pin": 5}],
                "esphome": {"name": "test"},
                "api": {},
            },
            {"sensor", "binary_sensor", "esphome", "api", "template", "gpio"},
        ),
        # Test extraction of platform components only
        (
            {
                "output": [
                    {"platform": "template", "id": "test_out"},
                    {"platform": "gpio", "pin": 5},
                ],
                "light": [{"platform": "rgb", "name": "test_light"}],
            },
            {"output", "light", "template", "gpio", "rgb"},
        ),
        # Test handling of non-list component values
        (
            {
                "esphome": {"name": "test"},  # Dict value
                "logger": None,  # None value
                "api": {},  # Empty dict
                "sensor": [{"platform": "dht"}],  # List value
            },
            {"esphome", "logger", "api", "sensor", "dht"},
        ),
    ],
)
def test_get_components_from_fixtures_extracts_components(
    yaml_content: dict[str, Any],
    expected_components: set[str],
    mock_glob: Mock,
    mock_open_file: Mock,
    mock_yaml_load: Mock,
) -> None:
    """Test extraction of components from fixture YAML files."""
    mock_glob.return_value = [Path("test1.yaml")]
    mock_yaml_load.return_value = yaml_content

    components: set[str] = should_run_integration_tests.get_components_from_fixtures()

    assert components == expected_components


def test_get_components_from_fixtures_handles_empty_config(
    mock_glob: Mock, mock_open_file: Mock, mock_yaml_load: Mock
) -> None:
    """Test handling of empty YAML files."""
    mock_glob.return_value = [Path("test1.yaml"), Path("test2.yaml")]
    mock_yaml_load.side_effect = [None, {"sensor": []}]

    components: set[str] = should_run_integration_tests.get_components_from_fixtures()

    assert components == {"sensor"}


def test_get_components_from_fixtures_propagates_yaml_errors(
    mock_glob: Mock, mock_open_file: Mock, mock_yaml_load: Mock
) -> None:
    """Test that YAML parse errors are not caught."""
    mock_glob.return_value = [Path("test1.yaml")]
    mock_yaml_load.side_effect = yaml.YAMLError("Invalid YAML")

    with pytest.raises(yaml.YAMLError):
        should_run_integration_tests.get_components_from_fixtures()


@pytest.mark.parametrize(
    ("component_configs", "initial_components", "expected_components"),
    [
        # No dependencies
        (
            {"sensor": ([], [])},  # (dependencies, auto_load)
            {"sensor"},
            {"sensor"},
        ),
        # Simple dependencies
        (
            {
                "sensor": (["esp32"], []),
                "esp32": ([], []),
            },
            {"sensor"},
            {"sensor", "esp32"},
        ),
        # Auto-load components
        (
            {
                "light": ([], ["output", "power_supply"]),
                "output": ([], []),
                "power_supply": ([], []),
            },
            {"light"},
            {"light", "output", "power_supply"},
        ),
        # Transitive dependencies
        (
            {
                "comp_a": (["comp_b"], []),
                "comp_b": (["comp_c"], []),
                "comp_c": ([], []),
            },
            {"comp_a"},
            {"comp_a", "comp_b", "comp_c"},
        ),
        # Dependencies with dots (sensor.base)
        (
            {
                "my_comp": (["sensor.base", "binary_sensor.base"], []),
                "sensor": ([], []),
                "binary_sensor": ([], []),
            },
            {"my_comp"},
            {"my_comp", "sensor", "binary_sensor"},
        ),
    ],
)
def test_get_all_dependencies(
    component_configs: dict[str, tuple[list[str], list[str]]],
    initial_components: set[str],
    expected_components: set[str],
    mock_get_component: Mock,
) -> None:
    """Test dependency resolution for components."""

    def get_component_side_effect(name: str) -> Mock | None:
        if name in component_configs:
            deps, auto_load = component_configs[name]
            comp = Mock()
            comp.dependencies = deps
            comp.auto_load = auto_load
            return comp
        return None

    mock_get_component.side_effect = get_component_side_effect

    result: set[str] = should_run_integration_tests.get_all_dependencies(
        initial_components
    )

    assert result == expected_components


def test_get_all_dependencies_handles_missing_components(
    mock_get_component: Mock,
) -> None:
    """Test handling of components that can't be loaded."""
    # First component exists, its dependency doesn't
    comp: Mock = Mock()
    comp.dependencies = ["missing_comp"]
    comp.auto_load = []

    mock_get_component.side_effect = lambda name: comp if name == "existing" else None

    result: set[str] = should_run_integration_tests.get_all_dependencies(
        {"existing", "nonexistent"}
    )

    # Should still include all components, even if some can't be loaded
    assert result == {"existing", "nonexistent", "missing_comp"}


@pytest.mark.parametrize(
    ("changed_files", "expected_output"),
    [
        # Core files changed
        (
            ["esphome/core/component.cpp", "esphome/components/sensor/sensor.cpp"],
            "true",
        ),
        # Python files outside components
        (
            ["esphome/config.py", "esphome/util.py"],
            "true",
        ),
        # Integration test files
        (
            [
                "tests/integration/test_something.py",
                "tests/integration/fixtures/test.yaml",
            ],
            "true",
        ),
    ],
)
def test_main_triggers_on_core_and_test_changes(
    changed_files: list[str],
    expected_output: str,
    mock_changed_files: Mock,
    mock_glob: Mock,
    mock_open_file: Mock,
    mock_yaml_load: Mock,
) -> None:
    """Test that core files and test files trigger integration tests."""
    mock_changed_files.return_value = changed_files
    mock_glob.return_value = []
    mock_yaml_load.return_value = {}

    result: bool = should_run_integration_tests.should_run_integration_tests()

    assert result == (expected_output == "true")


def test_main_triggers_on_component_changes(
    mock_changed_files: Mock,
    mock_glob: Mock,
    mock_open_file: Mock,
    mock_yaml_load: Mock,
    mock_get_component: Mock,
) -> None:
    """Test that changes to components used in fixtures trigger tests."""
    mock_changed_files.return_value = [
        "esphome/components/sensor/sensor.cpp",
        "esphome/components/api/api.cpp",
    ]

    # Mock fixture files
    mock_glob.return_value = [Path("test.yaml")]
    mock_yaml_load.return_value = {"sensor": [], "light": []}

    # Mock component dependencies
    def get_component_side_effect(name: str) -> Mock | None:
        comps: dict[str, tuple[list[str], list[str]]] = {
            "sensor": ([], []),
            "light": ([], ["api"]),
            "api": ([], []),
        }
        if name in comps:
            deps, auto = comps[name]
            comp = Mock()
            comp.dependencies = deps
            comp.auto_load = auto
            return comp
        return None

    mock_get_component.side_effect = get_component_side_effect

    result: bool = should_run_integration_tests.should_run_integration_tests()

    assert result is True


def test_main_does_not_trigger_on_unrelated_changes(
    mock_changed_files: Mock,
    mock_get_fixtures: Mock,
    mock_get_deps: Mock,
) -> None:
    """Test that changes to unrelated components don't trigger tests."""
    mock_changed_files.return_value = [
        "esphome/components/unrelated/unrelated.cpp",
        "esphome/components/another/another.h",
    ]
    mock_get_fixtures.return_value = {"sensor", "light"}
    mock_get_deps.return_value = {"sensor", "light", "api"}

    result: bool = should_run_integration_tests.should_run_integration_tests()

    assert result is False


def test_main_with_branch_argument(
    mock_changed_files: Mock,
) -> None:
    """Test using branch argument."""
    mock_changed_files.return_value = []

    result: bool = should_run_integration_tests.should_run_integration_tests("main")

    assert result is False
    mock_changed_files.assert_called_with("main")


def test_simple_mock_check(
    mock_changed_files: Mock,
) -> None:
    """Simple test to check mocking."""
    mock_changed_files.return_value = ["test.py"]

    # Check that the mock is working
    result: list[str] = should_run_integration_tests.changed_files()
    assert result == ["test.py"]


def test_main_with_no_changes(
    mock_changed_files: Mock,
) -> None:
    """Test when no files have changed."""
    mock_changed_files.return_value = []

    result: bool = should_run_integration_tests.should_run_integration_tests()

    assert result is False


def test_main_function_with_args(
    mock_argv_with_branch: None,
    mock_changed_files: Mock,
) -> None:
    """Test that main() correctly parses arguments and calls should_run_integration_tests."""
    mock_changed_files.return_value = []

    result: bool = should_run_integration_tests.main()

    assert result is False
    mock_changed_files.assert_called_with("main")
