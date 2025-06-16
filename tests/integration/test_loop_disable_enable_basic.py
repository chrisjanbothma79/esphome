"""Basic integration test to verify loop disable/enable compiles."""

from __future__ import annotations

import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_loop_disable_enable_compiles(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that components with loop disable/enable compile and run."""
    # Get the absolute path to the external components directory
    from pathlib import Path

    external_components_path = str(
        Path(__file__).parent / "fixtures" / "external_components"
    )

    # Replace the placeholder in the YAML config with the actual path
    yaml_config = yaml_config.replace(
        "EXTERNAL_COMPONENT_PATH", external_components_path
    )

    # Write, compile and run the ESPHome device, then connect to API
    async with run_compiled(yaml_config), api_client_connected() as client:
        # Verify we can get device info
        device_info = await client.device_info()
        assert device_info is not None
        assert device_info.name == "loop-test"

        # If we get here, the code compiled and ran successfully
        # The partitioned vector implementation is working
