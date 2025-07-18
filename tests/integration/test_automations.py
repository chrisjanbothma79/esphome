"""Test ESPHome automations functionality."""

from __future__ import annotations

import asyncio
import re

import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_delay_action_cancellation(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that delay actions can be properly cancelled when script restarts."""
    loop = asyncio.get_running_loop()

    # Track log messages
    log_lines: list[str] = []
    script_start_count = 0
    first_delay_completed = False
    script_restart_logged = False
    test_started = False

    # Patterns to match
    test_start_pattern = re.compile(r"Starting first script execution")
    script_start_pattern = re.compile(r"Script started, beginning delay")
    restart_pattern = re.compile(r"Restarting script \(should cancel first delay\)")
    error_pattern = re.compile(r"ERROR: First delay completed")

    # Future to track when we can check results
    second_script_started = loop.create_future()

    def check_output(line: str) -> None:
        """Check log output for expected messages."""
        nonlocal \
            script_start_count, \
            first_delay_completed, \
            script_restart_logged, \
            test_started

        log_lines.append(line)

        if test_start_pattern.search(line):
            test_started = True
        elif script_start_pattern.search(line) and test_started:
            script_start_count += 1
            if script_start_count == 2 and not second_script_started.done():
                second_script_started.set_result(True)
        elif restart_pattern.search(line):
            script_restart_logged = True
        elif error_pattern.search(line):
            first_delay_completed = True

    async with (
        run_compiled(yaml_config, line_callback=check_output),
        api_client_connected() as client,
    ):
        # Get services
        entities, services = await client.list_entities_services()

        # Find our test service
        test_service = next(
            (s for s in services if s.name == "start_delay_then_restart"), None
        )
        assert test_service is not None, "start_delay_then_restart service not found"

        # Execute the test sequence
        client.execute_service(test_service, {})

        # Wait for the second script to start
        await asyncio.wait_for(second_script_started, timeout=5.0)

        # Wait a bit more to ensure first delay would have completed if not cancelled
        await asyncio.sleep(6.0)  # Original delay was 5s

        # Check results
        assert script_start_count == 2, (
            f"Script should have started twice, but started {script_start_count} times"
        )
        assert script_restart_logged, "Script restart was not logged"

        # This is the key assertion - the first delay should NOT have completed
        if first_delay_completed:
            # Print relevant logs for debugging
            relevant_logs = [
                line
                for line in log_lines
                if any(
                    pattern in line
                    for pattern in ["Script", "delay", "ERROR", "Restart"]
                )
            ]
            pytest.fail(
                "First delay completed even though script was restarted! "
                "This means DelayAction is not being cancelled properly.\n"
                "Log output:\n" + "\n".join(relevant_logs[-20:])
            )
