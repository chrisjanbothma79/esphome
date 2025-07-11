"""Integration test for API password authentication."""

from __future__ import annotations

import asyncio

from aioesphomeapi import APIConnectionError
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_host_mode_api_password(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test API authentication with password."""
    async with run_compiled(yaml_config):
        # First, try to connect without password - should fail
        with pytest.raises(APIConnectionError, match="Authentication"):
            async with api_client_connected(password=""):
                pass  # Should not reach here

        # Now connect with correct password
        async with api_client_connected(password="test_password_123") as client:
            # Verify we can get device info
            device_info = await client.device_info()
            assert device_info is not None
            assert device_info.uses_password is True
            assert device_info.name == "host-mode-api-password"

            # Subscribe to states to ensure authenticated connection works
            states = {}

            def on_state(state):
                states[state.key] = state

            await client.subscribe_states(on_state)

            # Wait a bit to receive the test sensor state
            await asyncio.sleep(0.5)

            # Should have received at least one state (the test sensor)
            assert len(states) > 0

        # Test with wrong password - should fail
        with pytest.raises(APIConnectionError, match="Authentication"):
            async with api_client_connected(password="wrong_password"):
                pass  # Should not reach here
