"""String lifetime test - verify scheduler handles string destruction correctly."""

import asyncio
from pathlib import Path
import re

from aioesphomeapi import UserService
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_scheduler_string_lifetime(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that scheduler correctly handles string lifetimes when strings go out of scope."""

    # Get the absolute path to the external components directory
    external_components_path = str(
        Path(__file__).parent / "fixtures" / "external_components"
    )

    # Replace the placeholder in the YAML config with the actual path
    yaml_config = yaml_config.replace(
        "EXTERNAL_COMPONENT_PATH", external_components_path
    )

    # Create a future to signal test completion
    loop = asyncio.get_event_loop()
    test_complete_future: asyncio.Future[None] = loop.create_future()

    # Track test progress
    test_stats = {
        "tests_passed": 0,
        "tests_failed": 0,
        "errors": [],
        "use_after_free_detected": False,
    }

    def on_log_line(line: str) -> None:
        # Track test results from the C++ test output
        if "Tests passed:" in line and "string_lifetime" in line:
            # Extract the number from "Tests passed: 32"
            match = re.search(r"Tests passed:\s*(\d+)", line)
            if match:
                test_stats["tests_passed"] = int(match.group(1))
        elif "Tests failed:" in line and "string_lifetime" in line:
            match = re.search(r"Tests failed:\s*(\d+)", line)
            if match:
                test_stats["tests_failed"] = int(match.group(1))
        elif "ERROR" in line and "string_lifetime" in line:
            test_stats["errors"].append(line)

        # Check for memory corruption indicators
        if any(
            indicator in line.lower()
            for indicator in [
                "use after free",
                "heap corruption",
                "segfault",
                "abort",
                "assertion",
                "sanitizer",
                "bad memory",
                "invalid pointer",
            ]
        ):
            test_stats["use_after_free_detected"] = True
            if not test_complete_future.done():
                test_complete_future.set_exception(
                    Exception(f"Memory corruption detected: {line}")
                )
            return

        # Check for completion
        if "String lifetime tests complete" in line and not test_complete_future.done():
            test_complete_future.set_result(None)

    async with (
        run_compiled(yaml_config, line_callback=on_log_line),
        api_client_connected() as client,
    ):
        # Verify we can connect
        device_info = await client.device_info()
        assert device_info is not None
        assert device_info.name == "scheduler-string-lifetime-test"

        # List entities and services
        _, services = await asyncio.wait_for(
            client.list_entities_services(), timeout=5.0
        )

        # Find our test service
        run_test_service: UserService | None = None
        for service in services:
            if service.name == "run_string_lifetime_test":
                run_test_service = service
                break

        assert run_test_service is not None, (
            "run_string_lifetime_test service not found"
        )

        # Call the service to start the test
        client.execute_service(run_test_service, {})

        # Wait for test to complete
        try:
            await asyncio.wait_for(test_complete_future, timeout=30.0)
        except asyncio.TimeoutError:
            pytest.fail(f"String lifetime test timed out. Stats: {test_stats}")
        except Exception as e:
            pytest.fail(f"Test failed: {e}\nStats: {test_stats}")

        # Check for use-after-free
        assert not test_stats["use_after_free_detected"], "Use-after-free detected!"

        # Check for any errors
        assert test_stats["tests_failed"] == 0, f"Tests failed: {test_stats['errors']}"

        # Verify we had the expected number of passing tests and no failures
        assert test_stats["tests_passed"] == 30, (
            f"Expected exactly 30 tests to pass, but got {test_stats['tests_passed']}"
        )
        assert test_stats["tests_failed"] == 0, (
            f"Expected no test failures, but got {test_stats['tests_failed']} failures"
        )
