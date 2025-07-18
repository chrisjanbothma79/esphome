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

    # Track log messages with timestamps
    log_entries: list[tuple[float, str]] = []
    script_starts: list[float] = []
    delay_completions: list[float] = []
    script_restart_logged = False
    test_started_time = None

    # Patterns to match
    test_start_pattern = re.compile(r"Starting first script execution")
    script_start_pattern = re.compile(r"Script started, beginning delay")
    restart_pattern = re.compile(r"Restarting script \(should cancel first delay\)")
    delay_complete_pattern = re.compile(r"Delay completed successfully")

    # Future to track when we can check results
    second_script_started = loop.create_future()

    def check_output(line: str) -> None:
        """Check log output for expected messages."""
        nonlocal script_restart_logged, test_started_time

        current_time = loop.time()
        log_entries.append((current_time, line))

        if test_start_pattern.search(line):
            test_started_time = current_time
        elif script_start_pattern.search(line) and test_started_time:
            script_starts.append(current_time)
            if len(script_starts) == 2 and not second_script_started.done():
                second_script_started.set_result(True)
        elif restart_pattern.search(line):
            script_restart_logged = True
        elif delay_complete_pattern.search(line):
            delay_completions.append(current_time)

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

        # Wait for potential delay completion
        await asyncio.sleep(1.5)  # Original delay was 1s

        # Check results
        assert len(script_starts) == 2, (
            f"Script should have started twice, but started {len(script_starts)} times"
        )
        assert script_restart_logged, "Script restart was not logged"

        # The key assertion: we should only see ONE delay completion (from the second script)
        if len(delay_completions) > 1:
            # Print timing analysis
            timing_info = []
            if len(script_starts) >= 2 and len(delay_completions) >= 1:
                first_start = script_starts[0]
                second_start = script_starts[1]
                timing_info.append(
                    f"First script started at: +{first_start - test_started_time:.3f}s"
                )
                timing_info.append(
                    f"Second script started at: +{second_start - test_started_time:.3f}s"
                )
                timing_info.append(
                    f"Time between starts: {second_start - first_start:.3f}s"
                )
                for i, completion in enumerate(delay_completions):
                    timing_info.append(
                        f"Delay {i + 1} completed at: +{completion - test_started_time:.3f}s"
                    )
                    if i == 0:
                        timing_info.append(
                            f"  Time from first start: {completion - first_start:.3f}s"
                        )
                    timing_info.append(
                        f"  Time from second start: {completion - second_start:.3f}s"
                    )

            pytest.fail(
                f"Found {len(delay_completions)} delay completions, but expected only 1!\n"
                "The first delay should have been cancelled by the script restart.\n"
                f"Timing analysis:\n" + "\n".join(timing_info)
            )

        # Verify we got exactly one completion and it happened ~5s after the second start
        assert len(delay_completions) == 1, (
            f"Expected 1 delay completion, got {len(delay_completions)}"
        )
        if len(script_starts) >= 2 and len(delay_completions) >= 1:
            time_from_second_start = delay_completions[0] - script_starts[1]
            assert 0.8 < time_from_second_start < 1.2, (
                f"Delay completed {time_from_second_start:.3f}s after second start, expected ~1s"
            )
