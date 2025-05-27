"""Integration test for Host mode with sensor."""

from __future__ import annotations

import asyncio

from aioesphomeapi import EntityState
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_host_mode_with_sensor(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test Host mode with a sensor component."""
    # Write, compile and run the ESPHome device, then connect to API
    async with run_compiled(yaml_config), api_client_connected() as client:
        # Subscribe to state changes
        states: dict[int, EntityState] = {}

        def on_state(state: EntityState) -> None:
            states[state.key] = state

        client.subscribe_states(on_state)

        # Wait for sensor data
        await asyncio.sleep(0.2)

        # Verify we received sensor data
        assert len(states) > 0, "No states received"

        # We should have received a sensor state with value 42.0
        sensor_states = [
            state
            for state in states.values()
            if hasattr(state, "state") and state.state == 42.0
        ]
        assert len(sensor_states) > 0, "No sensor state with value 42.0 found"

        test_sensor_state = sensor_states[0]
        assert test_sensor_state.state == 42.0
