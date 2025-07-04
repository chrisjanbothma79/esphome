"""Stress test for defer() thread safety with multiple threads."""

import asyncio
from pathlib import Path

from aioesphomeapi import UserService
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_defer_stress(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that defer() doesn't crash when called rapidly from multiple threads."""

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
    test_complete_future: asyncio.Future[bool] = loop.create_future()

    def on_log_line(line: str) -> None:
        if not test_complete_future.done():
            if "✓ Stress test PASSED" in line:
                test_complete_future.set_result(True)
            elif "✗ Stress test FAILED" in line:
                test_complete_future.set_result(False)

    async with (
        run_compiled(yaml_config, line_callback=on_log_line),
        api_client_connected() as client,
    ):
        # Verify we can connect
        device_info = await client.device_info()
        assert device_info is not None
        assert device_info.name == "defer-stress-test"

        # List entities and services
        entity_info, services = await asyncio.wait_for(
            client.list_entities_services(), timeout=5.0
        )

        # Find our test service
        run_stress_test_service: UserService | None = None
        for service in services:
            if service.name == "run_stress_test":
                run_stress_test_service = service
                break

        assert run_stress_test_service is not None, "run_stress_test service not found"

        # Call the run_stress_test service to start the test
        client.execute_service(run_stress_test_service, {})

        # Wait for test completion
        try:
            test_passed = await asyncio.wait_for(test_complete_future, timeout=15.0)
        except asyncio.TimeoutError:
            pytest.fail("Stress test did not complete within 15 seconds")

        # Verify the test passed
        assert test_passed is True, (
            "Stress test failed - defer() crashed or failed under thread pressure"
        )
