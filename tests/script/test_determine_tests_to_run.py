"""Unit tests for script/determine_tests_to_run.py module."""

from collections.abc import Generator
import json
import os
import subprocess
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
    with patch("determine_tests_to_run.should_run_integration_tests") as mock:
        yield mock


@pytest.fixture
def mock_should_run_clang_tidy() -> Generator[Mock, None, None]:
    """Mock should_run_clang_tidy from helpers."""
    with patch("determine_tests_to_run.should_run_clang_tidy") as mock:
        yield mock


@pytest.fixture
def mock_should_run_clang_format() -> Generator[Mock, None, None]:
    """Mock should_run_clang_format from helpers."""
    with patch("determine_tests_to_run.should_run_clang_format") as mock:
        yield mock


@pytest.fixture
def mock_subprocess_run() -> Generator[Mock, None, None]:
    """Mock subprocess.run for list-components.py calls."""
    with patch("determine_tests_to_run.subprocess.run") as mock:
        yield mock


def test_main_all_tests_should_run(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_should_run_clang_format: Mock,
    mock_subprocess_run: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test when all tests should run."""
    mock_should_run_integration_tests.return_value = True
    mock_should_run_clang_tidy.return_value = True
    mock_should_run_clang_format.return_value = True

    # Mock list-components.py output
    mock_result = Mock()
    mock_result.stdout = "wifi\napi\nsensor\n"
    mock_subprocess_run.return_value = mock_result

    # Run main function with mocked argv
    with patch("sys.argv", ["determine_tests_to_run.py"]):
        determine_tests_to_run.main()

    # Check output
    captured = capsys.readouterr()
    output = json.loads(captured.out)

    assert output["integration_tests"] is True
    assert output["clang_tidy"] is True
    assert output["clang_format"] is True
    assert output["changed_components"] == ["wifi", "api", "sensor"]
    assert output["component_test_count"] == 3


def test_main_no_tests_should_run(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_should_run_clang_format: Mock,
    mock_subprocess_run: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test when no tests should run."""
    mock_should_run_integration_tests.return_value = False
    mock_should_run_clang_tidy.return_value = False
    mock_should_run_clang_format.return_value = False

    # Mock empty list-components.py output
    mock_result = Mock()
    mock_result.stdout = ""
    mock_subprocess_run.return_value = mock_result

    # Run main function with mocked argv
    with patch("sys.argv", ["determine_tests_to_run.py"]):
        determine_tests_to_run.main()

    # Check output
    captured = capsys.readouterr()
    output = json.loads(captured.out)

    assert output["integration_tests"] is False
    assert output["clang_tidy"] is False
    assert output["clang_format"] is False
    assert output["changed_components"] == []
    assert output["component_test_count"] == 0


def test_main_list_components_fails(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_should_run_clang_format: Mock,
    mock_subprocess_run: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test when list-components.py fails."""
    mock_should_run_integration_tests.return_value = True
    mock_should_run_clang_tidy.return_value = True
    mock_should_run_clang_format.return_value = True

    # Mock list-components.py failure
    mock_subprocess_run.side_effect = subprocess.CalledProcessError(1, "cmd")

    # Run main function with mocked argv - should raise
    with patch("sys.argv", ["determine_tests_to_run.py"]):
        with pytest.raises(subprocess.CalledProcessError):
            determine_tests_to_run.main()


def test_main_with_branch_argument(
    mock_should_run_integration_tests: Mock,
    mock_should_run_clang_tidy: Mock,
    mock_should_run_clang_format: Mock,
    mock_subprocess_run: Mock,
    capsys: pytest.CaptureFixture[str],
) -> None:
    """Test with branch argument."""
    mock_should_run_integration_tests.return_value = False
    mock_should_run_clang_tidy.return_value = True
    mock_should_run_clang_format.return_value = False

    # Mock list-components.py output
    mock_result = Mock()
    mock_result.stdout = "mqtt\n"
    mock_subprocess_run.return_value = mock_result

    with patch("sys.argv", ["script.py", "-b", "main"]):
        determine_tests_to_run.main()

    # Check that functions were called with branch
    mock_should_run_integration_tests.assert_called_once_with("main")
    mock_should_run_clang_tidy.assert_called_once_with("main")
    mock_should_run_clang_format.assert_called_once_with("main")

    # Check that list-components.py was called with branch
    mock_subprocess_run.assert_called_once()
    call_args = mock_subprocess_run.call_args[0][0]
    assert "--changed" in call_args
    assert "-b" in call_args
    assert "main" in call_args

    # Check output
    captured = capsys.readouterr()
    output = json.loads(captured.out)

    assert output["integration_tests"] is False
    assert output["clang_tidy"] is True
    assert output["clang_format"] is False
    assert output["changed_components"] == ["mqtt"]
    assert output["component_test_count"] == 1
