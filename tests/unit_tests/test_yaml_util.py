from __future__ import annotations

from collections.abc import Callable, Generator
import os
from pathlib import Path
import tempfile
import time
from typing import Any
from unittest.mock import patch

import pytest

from esphome import yaml_util
from esphome.components import substitutions
from esphome.core import EsphomeError


def test_include_with_vars(fixture_path):
    yaml_file = fixture_path / "yaml_util" / "includetest.yaml"

    actual = yaml_util.load_yaml(yaml_file)
    substitutions.do_substitution_pass(actual, None)
    assert actual["esphome"]["name"] == "original"
    assert actual["esphome"]["libraries"][0] == "Wire"
    assert actual["esp8266"]["board"] == "nodemcu"
    assert actual["wifi"]["ssid"] == "my_custom_ssid"


def test_loading_a_broken_yaml_file(fixture_path):
    """Ensure we fallback to pure python to give good errors."""
    yaml_file = fixture_path / "yaml_util" / "broken_includetest.yaml"

    try:
        yaml_util.load_yaml(yaml_file)
    except EsphomeError as err:
        assert "broken_included.yaml" in str(err)


def test_loading_a_yaml_file_with_a_missing_component(fixture_path):
    """Ensure we show the filename for a yaml file with a missing component."""
    yaml_file = fixture_path / "yaml_util" / "missing_comp.yaml"

    try:
        yaml_util.load_yaml(yaml_file)
    except EsphomeError as err:
        assert "missing_comp.yaml" in str(err)


def test_loading_a_missing_file(fixture_path):
    """We throw EsphomeError when loading a missing file."""
    yaml_file = fixture_path / "yaml_util" / "missing.yaml"

    try:
        yaml_util.load_yaml(yaml_file)
    except EsphomeError as err:
        assert "missing.yaml" in str(err)


def test_parsing_with_custom_loader(fixture_path):
    """Test custom loader used for vscode connection
    Default loader is tested in test_include_with_vars
    """
    yaml_file = fixture_path / "yaml_util" / "includetest.yaml"

    loader_calls = []

    def custom_loader(fname):
        loader_calls.append(fname)

    with open(yaml_file, encoding="utf-8") as f_handle:
        yaml_util.parse_yaml(yaml_file, f_handle, custom_loader)

    assert len(loader_calls) == 3
    assert loader_calls[0].endswith("includes/included.yaml")
    assert loader_calls[1].endswith("includes/list.yaml")
    assert loader_calls[2].endswith("includes/scalar.yaml")


# Caching tests


@pytest.fixture
def clear_caches() -> Generator[None]:
    """Clear all YAML caches before and after tests."""
    yaml_util._YAML_FILE_CACHE.clear()
    yaml_util._SECRET_FILE_CACHE.clear()
    yaml_util._SECRET_VALUES.clear()
    yaml_util._SECRET_CACHE.clear()
    yield
    yaml_util._YAML_FILE_CACHE.clear()
    yaml_util._SECRET_FILE_CACHE.clear()
    yaml_util._SECRET_VALUES.clear()
    yaml_util._SECRET_CACHE.clear()


@pytest.fixture
def small_yaml_cache_size() -> Generator[None]:
    """Temporarily set a small YAML cache size for testing."""
    original_size = yaml_util._MAX_YAML_CACHE_SIZE
    yaml_util._MAX_YAML_CACHE_SIZE = 3
    yield
    yaml_util._MAX_YAML_CACHE_SIZE = original_size


@pytest.fixture
def temp_yaml_file() -> str:
    """Create a temporary YAML file for testing."""
    with tempfile.NamedTemporaryFile(mode="w", suffix=".yaml", delete=False) as f:
        f.write("test: value\n")
        f.write("nested:\n")
        f.write("  key: value\n")
        temp_path = f.name

    yield temp_path

    # Cleanup
    try:
        os.unlink(temp_path)
    except OSError:
        pass


@pytest.fixture
def temp_secrets_file() -> str:
    """Create a temporary secrets file for testing."""
    with tempfile.NamedTemporaryFile(mode="w", suffix=".yaml", delete=False) as f:
        f.write("wifi_password: supersecret\n")
        f.write("api_key: myapikey123\n")
        temp_path = f.name

    yield temp_path

    # Cleanup
    try:
        os.unlink(temp_path)
    except OSError:
        pass


def test_load_with_cache_hit(temp_yaml_file: str) -> None:
    """Test that cache returns same content without reloading."""
    cache: dict[str, tuple[float, int, dict[str, Any]]] = {}
    load_count = 0

    def loader(path: str) -> dict[str, Any]:
        nonlocal load_count
        load_count += 1
        with open(path) as f:
            return {"loaded": f.read(), "count": load_count}

    # First load
    result1 = yaml_util._load_with_cache(cache, temp_yaml_file, loader)
    assert load_count == 1
    assert temp_yaml_file in cache

    # Second load should use cache
    result2 = yaml_util._load_with_cache(cache, temp_yaml_file, loader)
    assert load_count == 1  # Should not increment
    assert result1 == result2


def test_load_with_cache_invalidation_on_file_change(temp_yaml_file: str) -> None:
    """Test that cache is invalidated when file is modified."""
    cache: dict[str, tuple[float, int, dict[str, Any]]] = {}
    load_count = 0

    def loader(path: str) -> dict[str, Any]:
        nonlocal load_count
        load_count += 1
        with open(path) as f:
            return {"content": f.read(), "count": load_count}

    # First load
    result1 = yaml_util._load_with_cache(cache, temp_yaml_file, loader)
    assert load_count == 1

    # Modify file (with small delay to ensure mtime changes)
    time.sleep(0.01)
    with open(temp_yaml_file, "w") as f:
        f.write("modified: true\n")

    # Second load should reload due to mtime change
    result2 = yaml_util._load_with_cache(cache, temp_yaml_file, loader)
    assert load_count == 2
    assert result1["content"] != result2["content"]


def test_load_with_cache_invalidation_on_size_change(temp_yaml_file: str) -> None:
    """Test that cache is invalidated when file size changes but mtime doesn't."""
    cache: dict[str, tuple[float, int, dict[str, Any]]] = {}
    load_count = 0

    def loader(path: str) -> dict[str, Any]:
        nonlocal load_count
        load_count += 1
        with open(path) as f:
            return {"content": f.read(), "count": load_count}

    # First load
    result1 = yaml_util._load_with_cache(cache, temp_yaml_file, loader)
    assert load_count == 1

    # Get current mtime
    stat = os.stat(temp_yaml_file)
    mtime = stat.st_mtime

    # Modify file content but keep same length initially
    with open(temp_yaml_file, "w") as f:
        f.write("test: value\nnested:\n  key: value\n")  # Same content

    # Restore original mtime
    os.utime(temp_yaml_file, (mtime, mtime))

    # Second load should use cache (same mtime and size)
    yaml_util._load_with_cache(cache, temp_yaml_file, loader)
    assert load_count == 1  # No reload

    # Now change content with different size
    with open(temp_yaml_file, "w") as f:
        f.write("test: much_longer_value_here\n")  # Different size

    # Restore original mtime again
    os.utime(temp_yaml_file, (mtime, mtime))

    # Third load should reload due to size change
    result3 = yaml_util._load_with_cache(cache, temp_yaml_file, loader)
    assert load_count == 2  # Reloaded due to size change
    assert result3["content"] != result1["content"]


def test_load_with_cache_missing_file() -> None:
    """Test behavior when file doesn't exist."""
    cache: dict[str, tuple[float, int, dict[str, Any]]] = {}

    def loader(path: str) -> dict[str, Any]:
        raise OSError(f"File not found: {path}")

    with pytest.raises(OSError):
        yaml_util._load_with_cache(cache, "/nonexistent/file.yaml", loader)


@pytest.mark.usefixtures("clear_caches")
def test_yaml_cache_deep_copy(temp_yaml_file: str) -> None:
    """Test that YAML cache returns deep copies to prevent mutations."""
    # Load YAML file
    result1 = yaml_util.load_yaml(temp_yaml_file)

    # Modify the returned object
    result1["new_key"] = "new_value"

    # Load again - should get original without modifications
    result2 = yaml_util.load_yaml(temp_yaml_file, clear_secrets=False)

    assert "new_key" not in result2
    assert result1 != result2


@pytest.mark.usefixtures("clear_caches")
def test_yaml_file_caching(temp_yaml_file: str) -> None:
    """Test that YAML files are cached properly."""

    # Track parse_yaml calls
    parse_count = 0
    original_parse = yaml_util.parse_yaml

    def counting_parse(*args: Any, **kwargs: Any) -> Any:
        nonlocal parse_count
        parse_count += 1
        return original_parse(*args, **kwargs)

    with patch.object(yaml_util, "parse_yaml", counting_parse):
        # First load
        result1 = yaml_util._load_yaml_internal(temp_yaml_file)
        assert parse_count == 1

        # Second load should use cache
        result2 = yaml_util._load_yaml_internal(temp_yaml_file)
        assert parse_count == 1  # Should not increment

        # Results should be equal but different objects (deep copy)
        assert result1 == result2
        assert result1 is not result2


def test_yaml_cache_cleared_on_load(temp_yaml_file: str) -> None:
    """Test that cache is cleared when clear_secrets=True."""
    # Load file first time
    yaml_util.load_yaml(temp_yaml_file)
    assert len(yaml_util._YAML_FILE_CACHE) > 0

    # Load with clear_secrets=True (default)
    yaml_util.load_yaml(temp_yaml_file)
    # Cache should be cleared and repopulated
    assert len(yaml_util._YAML_FILE_CACHE) == 1

    # Load with clear_secrets=False
    yaml_util.load_yaml(temp_yaml_file, clear_secrets=False)
    # Cache should remain
    assert len(yaml_util._YAML_FILE_CACHE) == 1


@pytest.mark.usefixtures("clear_caches")
def test_secrets_file_caching(temp_secrets_file: str, tmp_path: Path) -> None:
    """Test that secrets files are cached properly."""
    # Create a test YAML file that uses secrets
    yaml_content = """
esphome:
  name: test

wifi:
  password: !secret wifi_password
"""
    yaml_file = tmp_path / "test.yaml"
    yaml_file.write_text(yaml_content)

    # Create secrets file in same directory
    secrets_file = tmp_path / "secrets.yaml"
    secrets_file.write_text("wifi_password: cached_secret\n")

    # Track _load_with_cache calls for secrets
    load_count = 0
    original_load_with_cache = yaml_util._load_with_cache

    def counting_load_with_cache(
        cache: dict[str, tuple[float, int, dict[str, Any]]],
        file_path: str,
        loader_func: Callable[[str], dict[str, Any]],
    ) -> dict[str, Any]:
        nonlocal load_count
        if cache is yaml_util._SECRET_FILE_CACHE and "secrets.yaml" in str(file_path):
            load_count += 1
        return original_load_with_cache(cache, file_path, loader_func)

    try:
        # Patch the _load_with_cache function
        yaml_util._load_with_cache = counting_load_with_cache

        # First load
        result1 = yaml_util.load_yaml(str(yaml_file))
        assert load_count == 1
        assert result1["wifi"]["password"] == "cached_secret"

        # Second load should use cache
        result2 = yaml_util.load_yaml(str(yaml_file), clear_secrets=False)
        assert load_count == 1  # Should not increment due to cache
        assert result2["wifi"]["password"] == "cached_secret"

    finally:
        yaml_util._load_with_cache = original_load_with_cache


def test_secrets_fallback_to_main_config(tmp_path: Path) -> None:
    """Test that secrets falls back to main config directory."""
    # Setup directory structure
    main_dir = tmp_path / "main"
    sub_dir = tmp_path / "main" / "subdir"
    main_dir.mkdir()
    sub_dir.mkdir()

    # Create main secrets file
    main_secrets = main_dir / "secrets.yaml"
    main_secrets.write_text("main_secret: from_main\n")

    # Create config in subdirectory that references secret
    sub_config = sub_dir / "config.yaml"
    sub_config.write_text("value: !secret main_secret\n")

    # Mock CORE.config_path to point to main config
    with patch.object(yaml_util.CORE, "config_path", str(main_dir / "main.yaml")):
        result = yaml_util.load_yaml(str(sub_config))
        assert result["value"] == "from_main"


def test_secrets_cache_invalidation(tmp_path: Path) -> None:
    """Test that secrets cache is invalidated on file change."""
    # Create secrets file
    secrets_file = tmp_path / "secrets.yaml"
    secrets_file.write_text("test_secret: original\n")

    # Create config that uses secret
    config_file = tmp_path / "config.yaml"
    config_file.write_text("value: !secret test_secret\n")

    # Clear caches
    yaml_util._SECRET_FILE_CACHE.clear()
    yaml_util._YAML_FILE_CACHE.clear()

    # First load
    result1 = yaml_util.load_yaml(str(config_file))
    assert result1["value"] == "original"

    # Modify secrets file
    time.sleep(0.01)  # Ensure mtime changes
    secrets_file.write_text("test_secret: modified\n")

    # Second load should see the change
    result2 = yaml_util.load_yaml(str(config_file))
    assert result2["value"] == "modified"


def test_file_permissions_error(tmp_path: Path) -> None:
    """Test handling of permission errors."""
    # Create a file
    test_file = tmp_path / "test.yaml"
    test_file.write_text("test: value\n")

    # Make it unreadable (Unix only)
    if os.name != "nt":  # Skip on Windows
        os.chmod(test_file, 0o000)

        try:
            with pytest.raises(EsphomeError) as exc_info:
                yaml_util.load_yaml(str(test_file))
            assert "Error reading file" in str(exc_info.value)
        finally:
            # Restore permissions for cleanup
            os.chmod(test_file, 0o644)


@pytest.mark.usefixtures("clear_caches")
def test_concurrent_cache_access(temp_yaml_file: str) -> None:
    """Test that cache handles concurrent access correctly."""
    import threading

    results: list[Any] = []
    errors: list[Exception] = []

    def load_yaml() -> None:
        try:
            result = yaml_util.load_yaml(temp_yaml_file, clear_secrets=False)
            results.append(result)
        except Exception as e:
            errors.append(e)

    # Create multiple threads that load the same file
    threads: list[threading.Thread] = []
    for _ in range(10):
        t = threading.Thread(target=load_yaml)
        threads.append(t)
        t.start()

    # Wait for all threads
    for t in threads:
        t.join()

    # Check results
    assert len(errors) == 0
    assert len(results) == 10
    # All results should be equal
    for r in results[1:]:
        assert r == results[0]


@pytest.mark.usefixtures("clear_caches", "small_yaml_cache_size")
def test_yaml_cache_lru_eviction(tmp_path: Path) -> None:
    """Test that YAML cache implements LRU eviction when size limit is reached."""
    # Create 5 YAML files
    files: list[Path] = []
    for i in range(5):
        yaml_file = tmp_path / f"test{i}.yaml"
        yaml_file.write_text(f"value: {i}\n")
        files.append(yaml_file)

    # Load files 0, 1, 2 (cache will be full)
    for i in range(3):
        result = yaml_util.load_yaml(str(files[i]), clear_secrets=False)
        assert result["value"] == i

    assert len(yaml_util._YAML_FILE_CACHE) == 3
    assert str(files[0]) in yaml_util._YAML_FILE_CACHE
    assert str(files[1]) in yaml_util._YAML_FILE_CACHE
    assert str(files[2]) in yaml_util._YAML_FILE_CACHE

    # Load file 3 (should evict file 0)
    result = yaml_util.load_yaml(str(files[3]), clear_secrets=False)
    assert result["value"] == 3

    assert len(yaml_util._YAML_FILE_CACHE) == 3
    assert str(files[0]) not in yaml_util._YAML_FILE_CACHE  # Evicted
    assert str(files[1]) in yaml_util._YAML_FILE_CACHE
    assert str(files[2]) in yaml_util._YAML_FILE_CACHE
    assert str(files[3]) in yaml_util._YAML_FILE_CACHE

    # Access file 1 (should move it to end)
    result = yaml_util.load_yaml(str(files[1]), clear_secrets=False)
    assert result["value"] == 1

    # Load file 4 (should evict file 2, not file 1)
    result = yaml_util.load_yaml(str(files[4]), clear_secrets=False)
    assert result["value"] == 4

    assert len(yaml_util._YAML_FILE_CACHE) == 3
    assert (
        str(files[1]) in yaml_util._YAML_FILE_CACHE
    )  # Still there (recently accessed)
    assert str(files[2]) not in yaml_util._YAML_FILE_CACHE  # Evicted
    assert str(files[3]) in yaml_util._YAML_FILE_CACHE
    assert str(files[4]) in yaml_util._YAML_FILE_CACHE
