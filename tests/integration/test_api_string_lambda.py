"""Integration test for TemplatableStringValue with string lambdas."""

from __future__ import annotations

import asyncio
import re

import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_api_string_lambda(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test TemplatableStringValue works with lambdas that return strings (e.g., x.c_str())."""
    loop = asyncio.get_running_loop()

    # Track log messages
    service_called_future = loop.create_future()

    # Pattern to match in logs - confirms the lambda compiled and executed
    service_pattern = re.compile(r"Service called with string: STRING_FROM_LAMBDA")

    def check_output(line: str) -> None:
        """Check log output for expected messages."""
        if not service_called_future.done() and service_pattern.search(line):
            service_called_future.set_result(True)

    # Run with log monitoring
    async with (
        run_compiled(yaml_config, line_callback=check_output),
        api_client_connected() as client,
    ):
        # Verify device info
        device_info = await client.device_info()
        assert device_info is not None
        assert device_info.name == "api-string-lambda-test"

        # List services to find our test service
        _, services = await client.list_entities_services()

        # Find the test service that uses a string lambda
        test_service = next(
            (s for s in services if s.name == "test_string_lambda"), None
        )
        assert test_service is not None, "test_string_lambda service not found"

        # Execute the service - this will test the string lambda functionality
        client.execute_service(test_service, {"input_string": "STRING_FROM_LAMBDA"})

        # Wait for the service log message
        # This confirms the lambda compiled successfully and executed
        try:
            await asyncio.wait_for(service_called_future, timeout=5.0)
        except TimeoutError:
            pytest.fail(
                "Service log message not received - lambda may have failed to compile or execute"
            )
