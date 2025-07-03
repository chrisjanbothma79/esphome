"""Integration test for API default batch_delay with rapid state transitions."""

from __future__ import annotations

import asyncio
import time

from aioesphomeapi import BinarySensorInfo, BinarySensorState, EntityState
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_batch_delay_default_rapid_transitions(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that rapid binary sensor transitions may be lost with default batch_delay."""
    async with run_compiled(yaml_config), api_client_connected() as client:
        # Track state changes
        state_changes: list[tuple[bool, float]] = []

        def on_state(state: EntityState) -> None:
            """Track state changes with timestamps."""
            if isinstance(state, BinarySensorState):
                state_changes.append((state.state, time.monotonic()))

        # Subscribe to state changes
        client.subscribe_states(on_state)

        # Wait for entity info
        entity_info, _ = await client.list_entities_services()
        binary_sensors = [e for e in entity_info if isinstance(e, BinarySensorInfo)]
        assert len(binary_sensors) == 1, "Expected 1 binary sensor"

        # Collect states for 2 seconds
        await asyncio.sleep(2.1)

        # Count ON->OFF transitions
        on_off_count = 0
        for i in range(1, len(state_changes)):
            if state_changes[i - 1][0] and not state_changes[i][0]:  # ON to OFF
                on_off_count += 1

        # With default batch_delay (100ms), we expect FEWER transitions to be captured
        # because rapid ON->OFF within the batch window will be collapsed
        # The fixture generates ~20 ON/OFF cycles in 2 seconds (100ms per cycle)
        # But with 100ms batching, many of the 30ms ON periods may be lost

        # This test demonstrates the problem but doesn't fail - it shows why batch_delay: 0 is needed
        # We just verify we got some state changes, but likely missed many rapid transitions

        # Just verify we got some state changes
        assert len(state_changes) >= 2, (
            "Should have captured at least some state changes"
        )
