"""Integration test for loop disable/enable functionality."""

from __future__ import annotations

import asyncio
import logging
from pathlib import Path
from typing import Any

import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction

_LOGGER = logging.getLogger(__name__)


@pytest.mark.asyncio
async def test_loop_disable_enable(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that components can disable and enable their loop() method."""
    # Get the absolute path to the external components directory
    external_components_path = str(
        Path(__file__).parent / "fixtures" / "external_components"
    )

    # Replace the placeholder in the YAML config with the actual path
    yaml_config = yaml_config.replace(
        "EXTERNAL_COMPONENT_PATH", external_components_path
    )

    log_messages: list[tuple[int, str]] = []

    def on_log(msg: Any) -> None:
        """Capture log messages."""
        if hasattr(msg, "level") and hasattr(msg, "message"):
            log_messages.append((msg.level, msg.message.decode("utf-8")))
            _LOGGER.info(f"ESPHome log: [{msg.level}] {msg.message.decode('utf-8')}")

    # Write, compile and run the ESPHome device, then connect to API
    async with run_compiled(yaml_config), api_client_connected() as client:
        # Subscribe to logs (not awaitable)
        client.subscribe_logs(on_log)

        # Wait for the component to run through its test sequence
        # The component should:
        # 1. Try to disable/enable in setup (before calculate_looping_components_)
        # 2. Run loop 50 times then disable itself
        # 3. Not run loop again after disabling

        await asyncio.sleep(5.0)  # Give it time to run

        # Debug: Print all captured logs
        _LOGGER.info(f"Total logs captured: {len(log_messages)}")
        for level, msg in log_messages[:20]:  # First 20 logs
            _LOGGER.info(f"Log: {msg}")

        # Analyze captured logs
        setup_logs = [msg for level, msg in log_messages if "setup()" in msg]
        loop_logs = [msg for level, msg in log_messages if "Loop count:" in msg]
        disable_logs = [msg for level, msg in log_messages if "Disabling loop" in msg]
        error_logs = [msg for level, msg in log_messages if "ERROR" in msg]

        # Verify setup was called
        assert len(setup_logs) > 0, "Component setup() was not called"

        # Verify loop was called multiple times
        assert len(loop_logs) > 0, "Component loop() was never called"

        # Extract loop counts from logs
        loop_counts = []
        for _, msg in loop_logs:
            # Parse "Loop count: X" messages
            if "Loop count:" in msg:
                try:
                    count = int(msg.split("Loop count:")[1].strip())
                    loop_counts.append(count)
                except (ValueError, IndexError):
                    pass

        # Verify loop ran exactly 50 times before disabling
        assert max(loop_counts) == 50, (
            f"Expected max loop count 50, got {max(loop_counts)}"
        )

        # Verify disable message was logged
        assert any(
            "Disabling loop after 50 iterations" in msg for _, msg in disable_logs
        ), "Component did not log disable message"

        # Verify no errors (loop should not be called after disable)
        assert len(error_logs) == 0, f"Found error logs: {error_logs}"

        # Wait a bit more to ensure loop doesn't continue
        await asyncio.sleep(2.0)

        # Re-check - should still be no errors
        error_logs_2 = [msg for level, msg in log_messages if "ERROR" in msg]
        assert len(error_logs_2) == 0, f"Found error logs after wait: {error_logs_2}"

        # The final loop count should still be 50
        final_loop_logs = [msg for _, msg in log_messages if "Loop count:" in msg]
        final_counts = []
        for msg in final_loop_logs:
            if "Loop count:" in msg:
                try:
                    count = int(msg.split("Loop count:")[1].strip())
                    final_counts.append(count)
                except (ValueError, IndexError):
                    pass

        assert max(final_counts) == 50, (
            f"Loop continued after disable! Max count: {max(final_counts)}"
        )


@pytest.mark.asyncio
async def test_loop_disable_enable_reentrant(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that disable_loop is reentrant (component can disable itself during its own loop)."""
    # Get the absolute path to the external components directory
    external_components_path = str(
        Path(__file__).parent / "fixtures" / "external_components"
    )

    # Replace the placeholder in the YAML config with the actual path
    yaml_config = yaml_config.replace(
        "EXTERNAL_COMPONENT_PATH", external_components_path
    )

    # The basic test above already tests this - the component disables itself
    # during its own loop() call at iteration 50

    # This test just verifies that specific behavior more explicitly
    log_messages: list[tuple[int, str]] = []

    def on_log(msg: Any) -> None:
        """Capture log messages."""
        if hasattr(msg, "level") and hasattr(msg, "message"):
            log_messages.append((msg.level, msg.message.decode("utf-8")))

    async with run_compiled(yaml_config), api_client_connected() as client:
        client.subscribe_logs(on_log)
        await asyncio.sleep(5.0)

        # Look for the sequence: Loop count 50 -> Disable message -> No more loops
        found_50 = False
        found_disable = False
        found_51_error = False

        for i, (_, msg) in enumerate(log_messages):
            if "Loop count: 50" in msg:
                found_50 = True
                # Check next few messages for disable
                for j in range(i, min(i + 5, len(log_messages))):
                    if "Disabling loop after 50 iterations" in log_messages[j][1]:
                        found_disable = True
                        break
            elif "Loop count: 51" in msg or "ERROR" in msg:
                found_51_error = True

        assert found_50, "Component did not reach loop count 50"
        assert found_disable, "Component did not disable itself at count 50"
        assert not found_51_error, (
            "Component continued looping after disable or had errors"
        )
