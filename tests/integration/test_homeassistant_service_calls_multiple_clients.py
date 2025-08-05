"""Integration test to verify that homeassistant.service calls are still sent to all clients.

This test ensures that our fix for duplicate events doesn't break the expected
behavior for service calls, which should be sent to all connected clients.
"""

from __future__ import annotations

import asyncio

from aioesphomeapi import HomeassistantServiceCall
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_homeassistant_service_calls_to_all_clients(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that homeassistant.service calls are sent to all connected clients."""

    # Track service calls received by each client
    client1_service_calls: list[HomeassistantServiceCall] = []
    client2_service_calls: list[HomeassistantServiceCall] = []

    def on_service_call_client1(service_call: HomeassistantServiceCall) -> None:
        """Track service calls received by first client."""
        if not service_call.is_event:  # Only track service calls, not events
            client1_service_calls.append(service_call)

    def on_service_call_client2(service_call: HomeassistantServiceCall) -> None:
        """Track service calls received by second client."""
        if not service_call.is_event:  # Only track service calls, not events
            client2_service_calls.append(service_call)

    # Connect TWO API clients
    async with (
        run_compiled(yaml_config),
        api_client_connected() as client1,
        api_client_connected() as client2,
    ):
        # Subscribe both clients to service calls
        client1.subscribe_service_calls(on_service_call_client1)
        client2.subscribe_service_calls(on_service_call_client2)

        # Get device info to ensure both clients are connected
        device_info1 = await client1.device_info()
        device_info2 = await client2.device_info()
        assert device_info1 is not None
        assert device_info2 is not None
        assert device_info1.name == device_info2.name

        # List entities and services
        entities1, services1 = await client1.list_entities_services()

        # Find the test service
        test_service = next(
            (s for s in services1 if s.name == "trigger_service_call_test"), None
        )
        assert test_service is not None, "trigger_service_call_test service not found"

        # Clear any initial service calls
        client1_service_calls.clear()
        client2_service_calls.clear()

        # Trigger the service call
        client1.execute_service(test_service, {})

        # Wait for service calls to be processed
        await asyncio.sleep(0.5)

        # Now check the results
        print(f"Client1 received {len(client1_service_calls)} service calls")
        print(f"Client2 received {len(client2_service_calls)} service calls")

        # For service calls (not events), both clients should receive the call
        # This is the correct behavior for service calls
        assert len(client1_service_calls) > 0, (
            "Client1 should have received service calls"
        )
        assert len(client2_service_calls) > 0, (
            "Client2 should have received service calls"
        )

        # Both clients should have received the same service calls
        assert len(client1_service_calls) == len(client2_service_calls), (
            f"Both clients should receive the same number of service calls. "
            f"Client1: {len(client1_service_calls)}, Client2: {len(client2_service_calls)}"
        )

        # Verify the service call details
        for call1, call2 in zip(client1_service_calls, client2_service_calls):
            assert call1.service == call2.service, "Service names should match"
            assert not call1.is_event, "These should be service calls, not events"
            assert not call2.is_event, "These should be service calls, not events"
