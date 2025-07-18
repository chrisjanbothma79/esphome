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

    # Track events via futures
    script_started_future = loop.create_future()
    script_restarted_future = loop.create_future()
    delay_completed_future = loop.create_future()
    test_complete_future = loop.create_future()

    # Track counts
    script_started_count = 0
    delay_completed_count = 0

    # Patterns to match
    script_start_pattern = re.compile(r"Script execution started \(run number (\d+)\)")
    script_restart_pattern = re.compile(r"restarting \(mode: restart\)")
    delay_complete_pattern = re.compile(r"Delay completed! Total completions: (\d+)")
    test_complete_pattern = re.compile(r"Test completed with (\d+) delay completions")

    def check_output(line: str) -> None:
        """Check log output for expected messages."""
        nonlocal script_started_count, delay_completed_count

        # Check for script start
        start_match = script_start_pattern.search(line)
        if start_match:
            script_started_count += 1
            if not script_started_future.done():
                script_started_future.set_result(True)

        # Check for script restart
        if script_restart_pattern.search(line):
            if not script_restarted_future.done():
                script_restarted_future.set_result(True)

        # Check for delay completion
        complete_match = delay_complete_pattern.search(line)
        if complete_match:
            delay_completed_count = int(complete_match.group(1))
            if not delay_completed_future.done():
                delay_completed_future.set_result(delay_completed_count)

        # Check for test completion
        test_match = test_complete_pattern.search(line)
        if test_match:
            final_count = int(test_match.group(1))
            if not test_complete_future.done():
                test_complete_future.set_result(final_count)

    async with (
        run_compiled(yaml_config, line_callback=check_output),
        api_client_connected() as client,
    ):
        # Get services
        entities, services = await client.list_entities_services()

        # Find our test services
        start_service = next((s for s in services if s.name == "start_script"), None)
        restart_service = next(
            (s for s in services if s.name == "restart_script"), None
        )
        check_result_service = next(
            (s for s in services if s.name == "check_result"), None
        )

        assert start_service is not None, "start_script service not found"
        assert restart_service is not None, "restart_script service not found"
        assert check_result_service is not None, "check_result service not found"

        # Start the script
        client.execute_service(start_service, {})

        # Wait for script to start
        await asyncio.wait_for(script_started_future, timeout=5.0)
        assert script_started_count == 1, "Script should have started once"

        # Restart the script
        client.execute_service(restart_service, {})

        # Wait for restart confirmation
        await asyncio.wait_for(script_restarted_future, timeout=2.0)

        # Wait for the restarted script to complete its delay
        await asyncio.wait_for(delay_completed_future, timeout=1.0)

        # Check the final result
        client.execute_service(check_result_service, {})
        final_count = await asyncio.wait_for(test_complete_future, timeout=5.0)

        # If DelayAction cancellation works correctly, we should only have 1 completion
        # (from the restarted script). If it doesn't work, we'd have 2 completions.
        assert final_count == 1, (
            f"Expected 1 delay completion after restart, but got {final_count}"
        )
