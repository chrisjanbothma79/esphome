"""Unit tests for script/determine_tests_to_run.py module."""

from collections.abc import Generator
import json
import os
import sys
from unittest.mock import Mock, patch

import pytest

# Add the script directory to Python path so we can import the module
sys.path.insert(
    0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "script"))
)

import determine_tests_to_run  # noqa: E402


@pytest.fixture
def mock_should_run_integration_tests() -> Generator[Mock, None, None]:
    """Mock should_run_integration_tests from helpers."""
    with patch("helpers.should_run_integration_tests") as mock:
        yield mock


@pytest.fixture
def mock_should_run_clang_tidy() -> Generator[Mock, None, None]:
    """Mock should_run_clang_tidy from helpers."""
    with patch("helpers.should_run_clang_tidy") as mock:
        yield mock


@pytest.fixture
def mock_get_changed_components() -> Generator[Mock, None, None]:
    """Mock get_changed_components from helpers."""
    with patch("helpers.get_changed_components") as mock:
        yield mock


def test_main_all_tests_should_run(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_get_changed_components: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test when all tests should run."""
    mock_should_run_integration_tests.return_value = True
    mock_should_run_clang_tidy.return_value = True
    mock_get_changed_components.return_value = ["wifi", "api", "sensor"]

    # Run main function
    determine_tests_to_run.main()

    # Check output
    captured = capsys.readouterr()
    output = json.loads(captured.out)

    assert output["integration_tests"] is True
    assert output["clang_tidy"] is True
    assert output["changed_components"] == ["wifi", "api", "sensor"]
    assert output["component_test_count"] == 3


def test_main_no_tests_should_run(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_get_changed_components: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test when no tests should run."""
    mock_should_run_integration_tests.return_value = False
    mock_should_run_clang_tidy.return_value = False
    mock_get_changed_components.return_value = []

    # Run main function
    determine_tests_to_run.main()

    # Check output
    captured = capsys.readouterr()
    output = json.loads(captured.out)

    assert output["integration_tests"] is False
    assert output["clang_tidy"] is False
    assert output["changed_components"] == []
    assert output["component_test_count"] == 0


def test_main_core_files_changed(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_get_changed_components: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test when core files changed (get_changed_components returns None)."""
    mock_should_run_integration_tests.return_value = True
    mock_should_run_clang_tidy.return_value = True
    mock_get_changed_components.return_value = None  # Core files changed

    # Run main function
    determine_tests_to_run.main()

    # Check output
    captured = capsys.readouterr()
    output = json.loads(captured.out)

    assert output["integration_tests"] is True
    assert output["clang_tidy"] is True
    assert output["changed_components"] == []
    assert output["component_test_count"] == -1  # Special value for "test all"


def test_main_with_branch_argument(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_get_changed_components: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test with branch argument."""
    mock_should_run_integration_tests.return_value = False
    mock_should_run_clang_tidy.return_value = True
    mock_get_changed_components.return_value = ["mqtt"]

    with patch("sys.argv", ["script.py", "-b", "main"]):
        determine_tests_to_run.main()

    # Check that functions were called with branch
    mock_should_run_integration_tests.assert_called_once_with("main")
    mock_should_run_clang_tidy.assert_called_once_with("main")

    # Check output
    captured = capsys.readouterr()
    output = json.loads(captured.out)

    assert output["integration_tests"] is False
    assert output["clang_tidy"] is True
    assert output["changed_components"] == ["mqtt"]
    assert output["component_test_count"] == 1
