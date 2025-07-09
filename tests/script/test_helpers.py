"""Unit tests for script/helpers.py module."""

import json
import os
from pathlib import Path
import subprocess
import sys
from unittest.mock import Mock, patch

import pytest
from pytest import MonkeyPatch

# Add the script directory to Python path so we can import helpers
sys.path.insert(
    0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", "script"))
)

import helpers  # noqa: E402

changed_files = helpers.changed_files
filter_changed = helpers.filter_changed
get_changed_components = helpers.get_changed_components
_get_changed_files_from_command = helpers._get_changed_files_from_command
_get_pr_number_from_github_env = helpers._get_pr_number_from_github_env
_get_changed_files_github_actions = helpers._get_changed_files_github_actions


@pytest.mark.parametrize(
    ("github_ref", "expected_pr_number"),
    [
        ("refs/pull/1234/merge", "1234"),
        ("refs/pull/5678/head", "5678"),
        ("refs/pull/999/merge", "999"),
        ("refs/heads/main", None),
        ("", None),
    ],
)
def test_get_pr_number_from_github_env_ref(
    monkeypatch: MonkeyPatch, github_ref: str, expected_pr_number: str | None
) -> None:
    """Test extracting PR number from GITHUB_REF."""
    monkeypatch.setenv("GITHUB_REF", github_ref)
    # Make sure GITHUB_EVENT_PATH is not set
    monkeypatch.delenv("GITHUB_EVENT_PATH", raising=False)

    result = _get_pr_number_from_github_env()

    assert result == expected_pr_number


def test_get_pr_number_from_github_env_event_file(
    monkeypatch: MonkeyPatch, tmp_path: Path
) -> None:
    """Test extracting PR number from GitHub event file."""
    # No PR number in ref
    monkeypatch.setenv("GITHUB_REF", "refs/heads/feature-branch")

    event_file = tmp_path / "event.json"
    event_data = {"pull_request": {"number": 5678}}
    event_file.write_text(json.dumps(event_data))
    monkeypatch.setenv("GITHUB_EVENT_PATH", str(event_file))

    result = _get_pr_number_from_github_env()

    assert result == "5678"


def test_get_pr_number_from_github_env_no_pr(
    monkeypatch: MonkeyPatch, tmp_path: Path
) -> None:
    """Test when no PR number is available."""
    monkeypatch.setenv("GITHUB_REF", "refs/heads/main")

    event_file = tmp_path / "event.json"
    event_data = {"push": {"head_commit": {"id": "abc123"}}}
    event_file.write_text(json.dumps(event_data))
    monkeypatch.setenv("GITHUB_EVENT_PATH", str(event_file))

    result = _get_pr_number_from_github_env()

    assert result is None


@pytest.mark.parametrize(
    "github_ref,expected_pr_number",
    [
        ("refs/pull/1234/merge", "1234"),
        ("refs/pull/5678/head", "5678"),
        ("refs/pull/999/merge", "999"),
    ],
)
def test_github_actions_pull_request_with_pr_number_in_ref(
    monkeypatch: MonkeyPatch, github_ref: str, expected_pr_number: str
) -> None:
    """Test PR detection via GITHUB_REF."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")
    monkeypatch.setenv("GITHUB_EVENT_NAME", "pull_request")
    monkeypatch.setenv("GITHUB_REF", github_ref)

    expected_files = ["file1.py", "file2.cpp"]

    with patch("helpers._get_changed_files_from_command") as mock_get:
        mock_get.return_value = expected_files

        result = changed_files()

        mock_get.assert_called_once_with(
            ["gh", "pr", "diff", expected_pr_number, "--name-only"]
        )
        assert result == expected_files


def test_github_actions_pull_request_with_event_file(
    monkeypatch: MonkeyPatch, tmp_path: Path
) -> None:
    """Test PR detection via GitHub event file."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")
    monkeypatch.setenv("GITHUB_EVENT_NAME", "pull_request")
    monkeypatch.setenv("GITHUB_REF", "refs/heads/feature-branch")

    event_file = tmp_path / "event.json"
    event_data = {"pull_request": {"number": 5678}}
    event_file.write_text(json.dumps(event_data))
    monkeypatch.setenv("GITHUB_EVENT_PATH", str(event_file))

    expected_files = ["file1.py", "file2.cpp"]

    with patch("helpers._get_changed_files_from_command") as mock_get:
        mock_get.return_value = expected_files

        result = changed_files()

        mock_get.assert_called_once_with(["gh", "pr", "diff", "5678", "--name-only"])
        assert result == expected_files


def test_github_actions_push_event(monkeypatch: MonkeyPatch) -> None:
    """Test push event handling."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")
    monkeypatch.setenv("GITHUB_EVENT_NAME", "push")

    expected_files = ["file1.py", "file2.cpp"]

    with patch("helpers._get_changed_files_from_command") as mock_get:
        mock_get.return_value = expected_files

        result = changed_files()

        mock_get.assert_called_once_with(["git", "diff", "HEAD~1..HEAD", "--name-only"])
        assert result == expected_files


def test_get_changed_files_github_actions_pull_request(
    monkeypatch: MonkeyPatch,
) -> None:
    """Test _get_changed_files_github_actions for pull request event."""
    monkeypatch.setenv("GITHUB_EVENT_NAME", "pull_request")

    expected_files = ["file1.py", "file2.cpp"]

    with (
        patch("helpers._get_pr_number_from_github_env", return_value="1234"),
        patch("helpers._get_changed_files_from_command") as mock_get,
    ):
        mock_get.return_value = expected_files

        result = _get_changed_files_github_actions()

        mock_get.assert_called_once_with(["gh", "pr", "diff", "1234", "--name-only"])
        assert result == expected_files


def test_get_changed_files_github_actions_pull_request_no_pr_number(
    monkeypatch: MonkeyPatch,
) -> None:
    """Test _get_changed_files_github_actions when no PR number is found."""
    monkeypatch.setenv("GITHUB_EVENT_NAME", "pull_request")

    with patch("helpers._get_pr_number_from_github_env", return_value=None):
        result = _get_changed_files_github_actions()

        assert result is None


def test_get_changed_files_github_actions_push(monkeypatch: MonkeyPatch) -> None:
    """Test _get_changed_files_github_actions for push event."""
    monkeypatch.setenv("GITHUB_EVENT_NAME", "push")

    expected_files = ["file1.py", "file2.cpp"]

    with patch("helpers._get_changed_files_from_command") as mock_get:
        mock_get.return_value = expected_files

        result = _get_changed_files_github_actions()

        mock_get.assert_called_once_with(["git", "diff", "HEAD~1..HEAD", "--name-only"])
        assert result == expected_files


def test_get_changed_files_github_actions_push_fallback(
    monkeypatch: MonkeyPatch,
) -> None:
    """Test _get_changed_files_github_actions fallback for push event."""
    monkeypatch.setenv("GITHUB_EVENT_NAME", "push")

    with patch("helpers._get_changed_files_from_command") as mock_get:
        mock_get.side_effect = Exception("Failed")

        result = _get_changed_files_github_actions()

        assert result is None


def test_get_changed_files_github_actions_other_event(monkeypatch: MonkeyPatch) -> None:
    """Test _get_changed_files_github_actions for other event types."""
    monkeypatch.setenv("GITHUB_EVENT_NAME", "workflow_dispatch")

    result = _get_changed_files_github_actions()

    assert result is None


def test_github_actions_push_event_fallback(monkeypatch: MonkeyPatch) -> None:
    """Test push event fallback to git merge-base."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")
    monkeypatch.setenv("GITHUB_EVENT_NAME", "push")

    expected_files = ["file1.py", "file2.cpp"]

    with (
        patch("helpers._get_changed_files_from_command") as mock_get,
        patch("helpers.get_output") as mock_output,
    ):
        # First call fails, triggering fallback
        mock_get.side_effect = [
            Exception("Failed"),
            expected_files,
        ]

        mock_output.side_effect = [
            "origin\nupstream\n",  # git remote
            "abc123\n",  # merge base
        ]

        result = changed_files()

        assert mock_get.call_count == 2
        assert result == expected_files


@pytest.mark.parametrize(
    "branch,merge_base",
    [
        (None, "abc123"),  # Default branch (dev)
        ("release", "def456"),
        ("beta", "ghi789"),
    ],
)
def test_local_development_branches(
    monkeypatch: MonkeyPatch, branch: str | None, merge_base: str
) -> None:
    """Test local development with different branches."""
    monkeypatch.delenv("GITHUB_ACTIONS", raising=False)

    expected_files = ["file1.py", "file2.cpp"]

    with (
        patch("helpers.get_output") as mock_output,
        patch("helpers._get_changed_files_from_command") as mock_get,
    ):
        if branch is None:
            # For default branch, helpers.get_output is called twice (git remote and merge-base)
            mock_output.side_effect = [
                "origin\nupstream\n",  # git remote
                f"{merge_base}\n",  # merge base for upstream/dev
            ]
        else:
            # For custom branch, may need more calls if trying multiple remotes
            mock_output.side_effect = [
                "origin\nupstream\n",  # git remote
                Exception("not found"),  # upstream/{branch} may fail
                f"{merge_base}\n",  # merge base for origin/{branch}
            ]

        mock_get.return_value = expected_files

        result = changed_files(branch)

        mock_get.assert_called_once_with(["git", "diff", merge_base, "--name-only"])
        assert result == expected_files


def test_local_development_no_remotes_configured(monkeypatch: MonkeyPatch) -> None:
    """Test error when no git remotes are configured."""
    monkeypatch.delenv("GITHUB_ACTIONS", raising=False)

    with patch("helpers.get_output") as mock_output:
        # The function calls get_output multiple times:
        # 1. First to get list of remotes: git remote
        # 2. Then for each remote it tries: git merge-base
        # We simulate having some remotes but all merge-base attempts fail
        def side_effect_func(*args):
            if args == ("git", "remote"):
                return "origin\nupstream\n"
            else:
                # All merge-base attempts fail
                raise Exception("Command failed")

        mock_output.side_effect = side_effect_func

        with pytest.raises(ValueError, match="Git not configured"):
            changed_files()


@pytest.mark.parametrize(
    "stdout,expected",
    [
        ("file1.py\nfile2.cpp\n\n", ["file1.py", "file2.cpp"]),
        ("\n\n", []),
        ("single.py\n", ["single.py"]),
        (
            "path/to/file.cpp\nanother/path.h\n",
            ["another/path.h", "path/to/file.cpp"],
        ),  # Sorted
    ],
)
def test_get_changed_files_from_command_successful(
    stdout: str, expected: list[str]
) -> None:
    """Test successful command execution with various outputs."""
    mock_result = Mock()
    mock_result.returncode = 0
    mock_result.stdout = stdout

    with patch("subprocess.run", return_value=mock_result):
        result = _get_changed_files_from_command(["git", "diff"])

        assert result == expected


@pytest.mark.parametrize(
    "returncode,stderr",
    [
        (1, "Error: command failed"),
        (128, "fatal: not a git repository"),
        (2, "Unknown error"),
    ],
)
def test_get_changed_files_from_command_failed(returncode: int, stderr: str) -> None:
    """Test command failure handling."""
    mock_result = Mock()
    mock_result.returncode = returncode
    mock_result.stderr = stderr

    with patch("subprocess.run", return_value=mock_result):
        with pytest.raises(Exception) as exc_info:
            _get_changed_files_from_command(["git", "diff"])
        assert "Command failed" in str(exc_info.value)
        assert stderr in str(exc_info.value)


def test_get_changed_files_from_command_relative_paths() -> None:
    """Test that paths are made relative to current directory."""
    mock_result = Mock()
    mock_result.returncode = 0
    mock_result.stdout = "/some/project/file1.py\n/some/project/sub/file2.cpp\n"

    with (
        patch("subprocess.run", return_value=mock_result),
        patch(
            "os.path.relpath", side_effect=["file1.py", "sub/file2.cpp"]
        ) as mock_relpath,
        patch("os.getcwd", return_value="/some/project"),
    ):
        result = _get_changed_files_from_command(["git", "diff"])

        # Check relpath was called with correct arguments
        assert mock_relpath.call_count == 2
        assert result == ["file1.py", "sub/file2.cpp"]


@pytest.mark.parametrize(
    "changed_files_list",
    [
        ["esphome/core/component.h", "esphome/components/wifi/wifi.cpp"],
        ["esphome/core/helpers.cpp"],
        ["esphome/core/application.h", "esphome/core/defines.h"],
    ],
)
def test_get_changed_components_core_files_trigger_full_scan(
    changed_files_list: list[str],
) -> None:
    """Test that core file changes trigger full scan without calling subprocess."""
    with patch("helpers.changed_files") as mock_changed:
        mock_changed.return_value = changed_files_list

        # Should return None without calling subprocess
        result = get_changed_components()
        assert result is None


@pytest.mark.parametrize(
    ("changed_files_list", "expected"),
    [
        # Only component files changed
        (
            ["esphome/components/wifi/wifi.cpp", "esphome/components/api/api.cpp"],
            ["wifi", "api"],
        ),
        # Non-component files only
        (["README.md", "script/clang-tidy"], []),
        # Single component
        (["esphome/components/mqtt/mqtt_client.cpp"], ["mqtt"]),
    ],
)
def test_get_changed_components_returns_component_list(
    changed_files_list: list[str], expected: list[str]
) -> None:
    """Test component detection returns correct component list."""
    with patch("helpers.changed_files") as mock_changed:
        mock_changed.return_value = changed_files_list

        mock_result = Mock()
        mock_result.stdout = "\n".join(expected) + "\n" if expected else "\n"

        with patch("subprocess.run", return_value=mock_result):
            result = get_changed_components()
            assert result == expected


def test_get_changed_components_script_failure() -> None:
    """Test fallback to full scan when script fails."""
    with patch("helpers.changed_files") as mock_changed:
        mock_changed.return_value = ["esphome/components/wifi/wifi_component.cpp"]

        with patch("subprocess.run") as mock_run:
            mock_run.side_effect = subprocess.CalledProcessError(1, "cmd")

            result = get_changed_components()

            assert result is None  # None means full scan


@pytest.mark.parametrize(
    ("components", "all_files", "expected_files"),
    [
        # Core files changed (full scan)
        (
            None,
            ["esphome/components/wifi/wifi.cpp", "esphome/core/helpers.cpp"],
            ["esphome/components/wifi/wifi.cpp", "esphome/core/helpers.cpp"],
        ),
        # Specific components
        (
            ["wifi", "api"],
            [
                "esphome/components/wifi/wifi.cpp",
                "esphome/components/wifi/wifi.h",
                "esphome/components/api/api.cpp",
                "esphome/components/mqtt/mqtt.cpp",
            ],
            [
                "esphome/components/wifi/wifi.cpp",
                "esphome/components/wifi/wifi.h",
                "esphome/components/api/api.cpp",
            ],
        ),
        # No components changed
        (
            [],
            ["esphome/components/wifi/wifi.cpp", "script/clang-tidy"],
            ["script/clang-tidy"],  # Only non-component changed files
        ),
    ],
)
def test_filter_changed_ci_mode(
    monkeypatch: MonkeyPatch,
    components: list[str] | None,
    all_files: list[str],
    expected_files: list[str],
) -> None:
    """Test filter_changed in CI mode with different component scenarios."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")

    with patch("helpers.get_changed_components") as mock_components:
        mock_components.return_value = components

        if components == []:
            # No components changed scenario needs changed_files mock
            with patch("helpers.changed_files") as mock_changed:
                mock_changed.return_value = ["script/clang-tidy", "README.md"]
                result = filter_changed(all_files)
        else:
            result = filter_changed(all_files)

        assert set(result) == set(expected_files)


def test_filter_changed_local_mode(monkeypatch: MonkeyPatch) -> None:
    """Test filter_changed in local mode filters files directly."""
    monkeypatch.delenv("GITHUB_ACTIONS", raising=False)

    all_files = [
        "esphome/components/wifi/wifi.cpp",
        "esphome/components/api/api.cpp",
        "esphome/core/helpers.cpp",
    ]

    with patch("helpers.changed_files") as mock_changed:
        mock_changed.return_value = [
            "esphome/components/wifi/wifi.cpp",
            "esphome/core/helpers.cpp",
        ]

        result = filter_changed(all_files)

        # Should only include files that actually changed
        expected = ["esphome/components/wifi/wifi.cpp", "esphome/core/helpers.cpp"]
        assert set(result) == set(expected)


def test_filter_changed_component_path_parsing(monkeypatch: MonkeyPatch) -> None:
    """Test correct parsing of component paths."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")

    all_files = [
        "esphome/components/wifi/wifi_component.cpp",
        "esphome/components/wifi_info/wifi_info_text_sensor.cpp",  # Different component
        "esphome/components/api/api_server.cpp",
        "esphome/components/api/custom_api_device.h",
    ]

    with patch("helpers.get_changed_components") as mock_components:
        mock_components.return_value = ["wifi"]  # Only wifi, not wifi_info

        result = filter_changed(all_files)

        # Should only include files from wifi component, not wifi_info
        expected = ["esphome/components/wifi/wifi_component.cpp"]
        assert result == expected


def test_filter_changed_prints_output(
    monkeypatch: MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    """Test that appropriate messages are printed."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")

    all_files = ["esphome/components/wifi/wifi_component.cpp"]

    with patch("helpers.get_changed_components") as mock_components:
        mock_components.return_value = ["wifi"]

        filter_changed(all_files)

        # Check that output was produced (not checking exact messages)
        captured = capsys.readouterr()
        assert len(captured.out) > 0


@pytest.mark.parametrize(
    ("files", "expected_empty"),
    [
        ([], True),
        (["file.cpp"], False),
    ],
    ids=["empty_files", "non_empty_files"],
)
def test_filter_changed_empty_file_handling(
    monkeypatch: MonkeyPatch, files: list[str], expected_empty: bool
) -> None:
    """Test handling of empty file lists."""
    monkeypatch.setenv("GITHUB_ACTIONS", "true")

    with patch("helpers.get_changed_components") as mock_components:
        mock_components.return_value = ["wifi"]

        result = filter_changed(files)

        # Both cases should be empty:
        # - Empty files list -> empty result
        # - file.cpp doesn't match esphome/components/wifi/* pattern -> filtered out
        assert len(result) == 0
