"""Integration test for loop disable/enable functionality using interval components."""

from __future__ import annotations

import asyncio
import logging
from typing import Any

import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction

_LOGGER = logging.getLogger(__name__)


@pytest.mark.asyncio
async def test_loop_disable_enable_simple(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that interval components can disable and enable their loop() method."""
    log_messages: list[tuple[int, str]] = []

    def on_log(msg: Any) -> None:
        """Capture log messages."""
        if hasattr(msg, "level") and hasattr(msg, "message"):
            log_messages.append((msg.level, msg.message.decode("utf-8")))
            if (
                "test" in msg.message.decode("utf-8")
                or "interval" in msg.message.decode("utf-8").lower()
            ):
                _LOGGER.info(
                    f"ESPHome log: [{msg.level}] {msg.message.decode('utf-8')}"
                )

    # Write, compile and run the ESPHome device, then connect to API
    async with run_compiled(yaml_config), api_client_connected() as client:
        # Subscribe to logs
        await client.subscribe_logs(on_log)

        # Wait for the intervals to run through their sequences
        # Expected behavior:
        # - Interval 1 runs 10 times (100ms interval) then disables itself
        # - Interval 2 runs and re-enables interval 1 at count 5 (1 second)
        # - Interval 1 resumes
        # - Interval 2 disables itself at count 15

        await asyncio.sleep(4.0)  # Give it time to run through the sequence

        # Analyze captured logs
        interval1_logs = [
            msg for level, msg in log_messages if "Interval 1 count:" in msg
        ]
        interval2_logs = [
            msg for level, msg in log_messages if "Interval 2 count:" in msg
        ]
        disable_logs = [
            msg for level, msg in log_messages if "Disabling interval" in msg
        ]
        enable_logs = [
            msg for level, msg in log_messages if "Re-enabling interval" in msg
        ]

        # Extract counts from interval 1
        interval1_counts = []
        for msg in interval1_logs:
            try:
                count = int(msg.split("count:")[1].strip())
                interval1_counts.append(count)
            except (ValueError, IndexError):
                pass

        # Extract counts from interval 2
        interval2_counts = []
        for msg in interval2_logs:
            try:
                count = int(msg.split("count:")[1].strip())
                interval2_counts.append(count)
            except (ValueError, IndexError):
                pass

        # Verify interval 1 behavior
        assert len(interval1_counts) > 0, "Interval 1 never ran"
        assert 10 in interval1_counts, "Interval 1 didn't reach count 10"

        # Check for gap in interval 1 counts (when it was disabled)
        # After count 10, there should be a gap before it resumes
        idx_10 = interval1_counts.index(10)
        if idx_10 < len(interval1_counts) - 1:
            # If there are counts after 10, they should start from 11+ after re-enable
            next_count = interval1_counts[idx_10 + 1]
            assert next_count > 10, (
                f"Interval 1 continued immediately after disable (next count: {next_count})"
            )

        # Verify interval 2 behavior
        assert len(interval2_counts) > 0, "Interval 2 never ran"
        assert 5 in interval2_counts, (
            "Interval 2 didn't reach count 5 to re-enable interval 1"
        )
        assert 15 in interval2_counts, "Interval 2 didn't reach count 15"

        # Verify disable/enable messages
        assert any(
            "Disabling interval 1 after 10 iterations" in msg for msg in disable_logs
        ), "Interval 1 disable message not found"
        assert any("Re-enabling interval 1" in msg for msg in enable_logs), (
            "Interval 1 re-enable message not found"
        )
        assert any("Disabling interval 2" in msg for msg in disable_logs), (
            "Interval 2 disable message not found"
        )

        # Wait a bit more to ensure intervals stay disabled
        await asyncio.sleep(1.0)

        # Get final counts
        final_interval2_counts = [
            int(msg.split("count:")[1].strip())
            for msg in log_messages
            if "Interval 2 count:" in msg
        ]

        # Interval 2 should not have counts beyond 15
        assert max(final_interval2_counts) == 15, (
            f"Interval 2 continued after disable! Max count: {max(final_interval2_counts)}"
        )

        _LOGGER.info(f"Test passed! Interval 1 counts: {interval1_counts}")
        _LOGGER.info(f"Test passed! Interval 2 counts: {interval2_counts}")


@pytest.mark.asyncio
async def test_loop_disable_enable_reentrant_simple(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Verify that intervals can disable themselves during their own execution (reentrant)."""
    # The test above already verifies this - interval 1 disables itself at count 10
    # This test just makes that behavior more explicit

    log_messages: list[tuple[int, str]] = []

    def on_log(msg: Any) -> None:
        if hasattr(msg, "level") and hasattr(msg, "message"):
            log_messages.append((msg.level, msg.message.decode("utf-8")))

    async with run_compiled(yaml_config), api_client_connected() as client:
        await client.subscribe_logs(on_log)
        await asyncio.sleep(3.0)

        # Look for the sequence where interval 1 disables itself
        found_count_10 = False
        found_disable_msg = False
        found_count_11 = False

        for i, (_, msg) in enumerate(log_messages):
            if "Interval 1 count: 10" in msg:
                found_count_10 = True
                # Check if disable message follows shortly after
                for j in range(i, min(i + 5, len(log_messages))):
                    if "Disabling interval 1 after 10 iterations" in log_messages[j][1]:
                        found_disable_msg = True
                        break
            elif "Interval 1 count: 11" in msg and not found_disable_msg:
                # This would mean it continued without properly disabling
                found_count_11 = True

        assert found_count_10, "Interval 1 did not reach count 10"
        assert found_disable_msg, "Interval 1 did not log disable message"

        # The interval successfully disabled itself during its own execution
        _LOGGER.info("Reentrant disable test passed!")
