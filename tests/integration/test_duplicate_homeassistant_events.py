"""Integration test for duplicate Home Assistant events issue.

Tests that homeassistant.event actions don't generate duplicate events
when multiple API clients are connected to the same ESPHome device.

This addresses the issue where binary_sensor on_press/on_click triggers
would fire duplicate events due to the API server sending the event
to all connected clients instead of just one.
"""

from __future__ import annotations

import asyncio
from collections import defaultdict

from aioesphomeapi import HomeassistantServiceCall
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_duplicate_homeassistant_events(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that homeassistant.event actions don't generate duplicate events with multiple clients."""

    # Track events received by each client
    client1_events: list[HomeassistantServiceCall] = []
    client2_events: list[HomeassistantServiceCall] = []
    all_events: list[HomeassistantServiceCall] = []

    # Track events by event name for easier counting
    event_counts = defaultdict(int)

    def on_service_call_client1(service_call: HomeassistantServiceCall) -> None:
        """Track events received by first client."""
        if service_call.is_event:
            client1_events.append(service_call)
            all_events.append(service_call)
            event_counts[service_call.service] += 1

    def on_service_call_client2(service_call: HomeassistantServiceCall) -> None:
        """Track events received by second client."""
        if service_call.is_event:
            client2_events.append(service_call)
            all_events.append(service_call)
            event_counts[service_call.service] += 1

    # Connect TWO API clients to simulate the real-world scenario
    # where Home Assistant might have multiple connections
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
        entities2, services2 = await client2.list_entities_services()

        # Find the test button service
        test_service = next(
            (s for s in services1 if s.name == "trigger_doorbell_test"), None
        )
        assert test_service is not None, "trigger_doorbell_test service not found"

        # Clear any initial events
        client1_events.clear()
        client2_events.clear()
        all_events.clear()
        event_counts.clear()

        # Trigger the doorbell event multiple times to simulate real usage
        for i in range(3):
            # Execute the service that triggers the doorbell event
            client1.execute_service(test_service, {})

            # Wait a bit for the event to be processed
            await asyncio.sleep(0.1)

        # Wait for all events to be received
        await asyncio.sleep(0.5)

        # Now check the results
        print(f"Client1 received {len(client1_events)} events")
        print(f"Client2 received {len(client2_events)} events")
        print(f"Total events seen: {len(all_events)}")

        # Print event details for debugging
        for i, event in enumerate(all_events):
            print(f"Event {i}: {event.service} (is_event: {event.is_event})")

        # Each button press should generate exactly ONE event total,
        # not one per client. The current bug would show 6 total events
        # (3 button presses × 2 clients = 6 events) instead of 3.

        expected_doorbell_events = 3
        actual_doorbell_events = event_counts.get("esphome.doorbell_pressed", 0)

        assert actual_doorbell_events == expected_doorbell_events, (
            f"Expected {expected_doorbell_events} doorbell events, got {actual_doorbell_events}. "
            f"This indicates duplicate events are being sent to multiple API clients. "
            f"Client1 events: {len(client1_events)}, Client2 events: {len(client2_events)}"
        )

        # Additionally, verify that not both clients received the same events
        # (events should be sent to only one client, not duplicated)
        if len(all_events) == expected_doorbell_events:
            # Events are not duplicated - this is the correct behavior
            print("✓ Events are properly deduplicated")
        else:
            # This is the bug - events are duplicated across clients
            pytest.fail(
                f"Events appear to be duplicated across API clients. "
                f"Expected {expected_doorbell_events} total events, got {len(all_events)}"
            )
