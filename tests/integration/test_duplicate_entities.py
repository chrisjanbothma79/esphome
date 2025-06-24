"""Integration test for duplicate entity handling."""

from __future__ import annotations

import asyncio

from aioesphomeapi import EntityInfo
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_duplicate_entities(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that duplicate entity names are automatically suffixed with _2, _3, _4."""
    async with run_compiled(yaml_config), api_client_connected() as client:
        # Get device info
        device_info = await client.device_info()
        assert device_info is not None

        # Get devices
        devices = device_info.devices
        assert len(devices) >= 2, f"Expected at least 2 devices, got {len(devices)}"

        # Find our test devices
        controller_1 = next((d for d in devices if d.name == "Controller 1"), None)
        controller_2 = next((d for d in devices if d.name == "Controller 2"), None)

        assert controller_1 is not None, "Controller 1 device not found"
        assert controller_2 is not None, "Controller 2 device not found"

        # Get entity list
        entities = await client.list_entities_services()
        all_entities: list[EntityInfo] = []
        for entity_list in entities[0]:
            if hasattr(entity_list, "object_id"):
                all_entities.append(entity_list)

        # Group entities by type for easier testing
        sensors = [e for e in all_entities if e.__class__.__name__ == "SensorInfo"]
        binary_sensors = [
            e for e in all_entities if e.__class__.__name__ == "BinarySensorInfo"
        ]
        text_sensors = [
            e for e in all_entities if e.__class__.__name__ == "TextSensorInfo"
        ]
        switches = [e for e in all_entities if e.__class__.__name__ == "SwitchInfo"]

        # Scenario 1: Check sensors with duplicate "Temperature" names
        temp_sensors = [s for s in sensors if s.name == "Temperature"]
        temp_object_ids = sorted([s.object_id for s in temp_sensors])

        # Should have temperature, temperature_2, temperature_3, temperature_4
        assert len(temp_object_ids) >= 4, (
            f"Expected at least 4 temperature sensors, got {len(temp_object_ids)}"
        )
        assert "temperature" in temp_object_ids, (
            "First temperature sensor should not have suffix"
        )
        assert "temperature_2" in temp_object_ids, (
            "Second temperature sensor should be temperature_2"
        )
        assert "temperature_3" in temp_object_ids, (
            "Third temperature sensor should be temperature_3"
        )
        assert "temperature_4" in temp_object_ids, (
            "Fourth temperature sensor should be temperature_4"
        )

        # Scenario 2: Check device-specific sensors don't conflict
        device_temp_sensors = [s for s in sensors if s.name == "Device Temperature"]

        # Group by device
        controller_1_temps = [
            s
            for s in device_temp_sensors
            if getattr(s, "device_id", None) == controller_1.device_id
        ]
        controller_2_temps = [
            s
            for s in device_temp_sensors
            if getattr(s, "device_id", None) == controller_2.device_id
        ]

        # Controller 1 should have device_temperature, device_temperature_2, device_temperature_3
        c1_object_ids = sorted([s.object_id for s in controller_1_temps])
        assert len(c1_object_ids) >= 3, (
            f"Expected at least 3 sensors on controller_1, got {len(c1_object_ids)}"
        )
        assert "device_temperature" in c1_object_ids, (
            "First device sensor should not have suffix"
        )
        assert "device_temperature_2" in c1_object_ids, (
            "Second device sensor should be device_temperature_2"
        )
        assert "device_temperature_3" in c1_object_ids, (
            "Third device sensor should be device_temperature_3"
        )

        # Controller 2 should have only device_temperature (no suffix)
        c2_object_ids = [s.object_id for s in controller_2_temps]
        assert len(c2_object_ids) >= 1, (
            f"Expected at least 1 sensor on controller_2, got {len(c2_object_ids)}"
        )
        assert "device_temperature" in c2_object_ids, (
            "Controller 2 sensor should not have suffix"
        )

        # Scenario 3: Check binary sensors (different platform, same name)
        temp_binary = [b for b in binary_sensors if b.name == "Temperature"]
        binary_object_ids = sorted([b.object_id for b in temp_binary])

        # Should have temperature, temperature_2, temperature_3 (no conflict with sensor platform)
        assert len(binary_object_ids) >= 3, (
            f"Expected at least 3 binary sensors, got {len(binary_object_ids)}"
        )
        assert "temperature" in binary_object_ids, (
            "First binary sensor should not have suffix"
        )
        assert "temperature_2" in binary_object_ids, (
            "Second binary sensor should be temperature_2"
        )
        assert "temperature_3" in binary_object_ids, (
            "Third binary sensor should be temperature_3"
        )

        # Scenario 4: Check text sensors with special characters
        status_sensors = [t for t in text_sensors if t.name == "Status Message!"]
        status_object_ids = sorted([t.object_id for t in status_sensors])

        # Special characters should be sanitized to _
        assert len(status_object_ids) >= 3, (
            f"Expected at least 3 status sensors, got {len(status_object_ids)}"
        )
        assert "status_message_" in status_object_ids, (
            "First status sensor should be status_message_"
        )
        assert "status_message__2" in status_object_ids, (
            "Second status sensor should be status_message__2"
        )
        assert "status_message__3" in status_object_ids, (
            "Third status sensor should be status_message__3"
        )

        # Scenario 5: Check switches with duplicate names
        power_switches = [s for s in switches if s.name == "Power Switch"]
        power_object_ids = sorted([s.object_id for s in power_switches])

        # Should have power_switch, power_switch_2
        assert len(power_object_ids) >= 2, (
            f"Expected at least 2 power switches, got {len(power_object_ids)}"
        )
        assert "power_switch" in power_object_ids, (
            "First power switch should be power_switch"
        )
        assert "power_switch_2" in power_object_ids, (
            "Second power switch should be power_switch_2"
        )

        # Verify we can get states for all entities (ensures they're functional)
        loop = asyncio.get_running_loop()
        states_future: asyncio.Future[bool] = loop.create_future()
        state_count = 0
        expected_count = (
            len(sensors) + len(binary_sensors) + len(text_sensors) + len(switches)
        )

        def on_state(state) -> None:
            nonlocal state_count
            state_count += 1
            if state_count >= expected_count and not states_future.done():
                states_future.set_result(True)

        client.subscribe_states(on_state)

        # Wait for all entity states
        try:
            await asyncio.wait_for(states_future, timeout=10.0)
        except asyncio.TimeoutError:
            pytest.fail(
                f"Did not receive all entity states within 10 seconds. "
                f"Expected {expected_count}, received {state_count}"
            )
