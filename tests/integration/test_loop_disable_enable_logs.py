"""Test that we can receive logs from the device."""

from __future__ import annotations

import asyncio
import logging
from typing import Any

import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction

_LOGGER = logging.getLogger(__name__)


@pytest.mark.asyncio
async def test_logs_received(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that we can receive logs from the ESPHome device."""
    # Get the absolute path to the external components directory
    from pathlib import Path

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
            message = (
                msg.message.decode("utf-8")
                if isinstance(msg.message, bytes)
                else str(msg.message)
            )
            log_messages.append((msg.level, message))
            _LOGGER.info(f"ESPHome log: [{msg.level}] {message}")

    # Write, compile and run the ESPHome device, then connect to API
    async with run_compiled(yaml_config), api_client_connected() as client:
        # Subscribe to logs
        client.subscribe_logs(on_log)

        # Wait a bit to receive some logs
        await asyncio.sleep(3.0)

        # Check if we received any logs at all
        _LOGGER.info(f"Total logs captured: {len(log_messages)}")

        # Print all logs for debugging
        for level, msg in log_messages:
            _LOGGER.info(f"Captured: [{level}] {msg}")

        # We should have received at least some logs
        assert len(log_messages) > 0, "No logs received from device"

        # Check for specific expected logs
        boot_logs = [msg for level, msg in log_messages if "System booted" in msg]
        interval_logs = [msg for level, msg in log_messages if "Interval tick" in msg]

        _LOGGER.info(f"Boot logs: {len(boot_logs)}")
        _LOGGER.info(f"Interval logs: {len(interval_logs)}")

        # We expect at least one boot log and some interval logs
        assert len(boot_logs) > 0, "No boot log found"
        assert len(interval_logs) > 0, "No interval logs found"
