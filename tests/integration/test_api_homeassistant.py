"""Integration test for Home Assistant API functionality.

Tests:
- Home Assistant service calls with templated values (main bug fix)
- Service calls with empty string values
- Home Assistant state reading (sensors, binary sensors, text sensors)
- Home Assistant number and switch component control
- Complex lambda expressions and string handling
"""

from __future__ import annotations

import asyncio
import re

from aioesphomeapi import HomeassistantServiceCall
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_api_homeassistant(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Comprehensive test for Home Assistant API functionality."""
    loop = asyncio.get_running_loop()

    # Create futures for patterns that capture values
    lambda_computed_future = loop.create_future()
    ha_temp_state_future = loop.create_future()
    ha_humidity_state_future = loop.create_future()
    ha_motion_state_future = loop.create_future()
    ha_weather_state_future = loop.create_future()

    # State update futures
    temp_update_future = loop.create_future()
    humidity_update_future = loop.create_future()
    motion_update_future = loop.create_future()
    weather_update_future = loop.create_future()

    # Number future
    ha_number_future = loop.create_future()

    tests_complete_future = loop.create_future()

    # Patterns to match in logs - only keeping patterns that capture values
    lambda_computed_pattern = re.compile(r"Lambda computed value: (\d+)")
    ha_temp_state_pattern = re.compile(
        r"Current HA Temperature: ([\d.]+)|HA Temperature has no state"
    )
    ha_humidity_state_pattern = re.compile(
        r"Current HA Humidity: ([\d.]+)|HA Humidity has no state"
    )
    ha_motion_state_pattern = re.compile(r"Current HA Motion: (ON|OFF)")
    ha_weather_state_pattern = re.compile(
        r"Current HA Weather: (\w+)|HA Weather has no state"
    )

    # State update patterns
    temp_update_pattern = re.compile(r"HA Temperature state updated: ([\d.]+)")
    humidity_update_pattern = re.compile(r"HA Humidity state updated: ([\d.]+)")
    motion_update_pattern = re.compile(r"HA Motion state changed: (ON|OFF)")
    weather_update_pattern = re.compile(r"HA Weather condition updated: (\w+)")

    # Number pattern
    ha_number_pattern = re.compile(r"Setting HA number to: ([\d.]+)")

    tests_complete_pattern = re.compile(r"=== All tests completed ===")

    # Track all log lines for debugging
    log_lines: list[str] = []

    # Track HomeAssistant service calls
    ha_service_calls: list[HomeassistantServiceCall] = []

    # Service call futures
    basic_service_call_future = loop.create_future()
    templated_service_call_future = loop.create_future()
    empty_string_service_call_future = loop.create_future()
    multiple_fields_service_call_future = loop.create_future()
    complex_lambda_service_call_future = loop.create_future()
    all_empty_service_call_future = loop.create_future()
    ha_number_service_call_future = loop.create_future()
    ha_switch_on_service_call_future = loop.create_future()
    ha_switch_off_service_call_future = loop.create_future()

    def on_service_call(service_call: HomeassistantServiceCall) -> None:
        """Capture HomeAssistant service calls."""
        ha_service_calls.append(service_call)
        # Debug log
        log_lines.append(f"[DEBUG] Received service call: {service_call.service}")

        # Check for specific service calls
        if service_call.service == "light.turn_on":
            # Check if this is the templated service call (has data_template)
            if service_call.data_template and not templated_service_call_future.done():
                templated_service_call_future.set_result(service_call)
            elif (
                not service_call.data_template and not basic_service_call_future.done()
            ):
                # This is the basic service call
                basic_service_call_future.set_result(service_call)
        elif (
            service_call.service == "notify.test"
            and not empty_string_service_call_future.done()
        ):
            empty_string_service_call_future.set_result(service_call)
        elif (
            service_call.service == "climate.set_temperature"
            and not multiple_fields_service_call_future.done()
        ):
            multiple_fields_service_call_future.set_result(service_call)
        elif (
            service_call.service == "script.test_script"
            and not complex_lambda_service_call_future.done()
        ):
            complex_lambda_service_call_future.set_result(service_call)
        elif (
            service_call.service == "test.empty"
            and not all_empty_service_call_future.done()
        ):
            all_empty_service_call_future.set_result(service_call)
        elif (
            service_call.service == "input_number.set_value"
            and not ha_number_service_call_future.done()
        ):
            ha_number_service_call_future.set_result(service_call)
        elif (
            service_call.service == "switch.turn_on"
            and not ha_switch_on_service_call_future.done()
        ):
            ha_switch_on_service_call_future.set_result(service_call)
        elif (
            service_call.service == "switch.turn_off"
            and not ha_switch_off_service_call_future.done()
        ):
            ha_switch_off_service_call_future.set_result(service_call)

    def check_output(line: str) -> None:
        """Check log output for expected messages."""
        log_lines.append(line)

        # Check for patterns that capture values
        if not lambda_computed_future.done():
            match = lambda_computed_pattern.search(line)
            if match:
                lambda_computed_future.set_result(match.group(1))
        elif not ha_temp_state_future.done() and ha_temp_state_pattern.search(line):
            ha_temp_state_future.set_result(line)
        elif not ha_humidity_state_future.done() and ha_humidity_state_pattern.search(
            line
        ):
            ha_humidity_state_future.set_result(line)
        elif not ha_motion_state_future.done() and ha_motion_state_pattern.search(line):
            ha_motion_state_future.set_result(line)
        elif not ha_weather_state_future.done() and ha_weather_state_pattern.search(
            line
        ):
            ha_weather_state_future.set_result(line)

        # Check state update patterns
        elif not temp_update_future.done() and temp_update_pattern.search(line):
            temp_update_future.set_result(line)
        elif not humidity_update_future.done() and humidity_update_pattern.search(line):
            humidity_update_future.set_result(line)
        elif not motion_update_future.done() and motion_update_pattern.search(line):
            motion_update_future.set_result(line)
        elif not weather_update_future.done() and weather_update_pattern.search(line):
            weather_update_future.set_result(line)

        # Check number pattern
        elif not ha_number_future.done() and ha_number_pattern.search(line):
            match = ha_number_pattern.search(line)
            if match:
                ha_number_future.set_result(match.group(1))

        elif not tests_complete_future.done() and tests_complete_pattern.search(line):
            tests_complete_future.set_result(True)

    # Run with log monitoring
    async with (
        run_compiled(yaml_config, line_callback=check_output),
        api_client_connected() as client,
    ):
        # Verify device info
        device_info = await client.device_info()
        assert device_info is not None
        assert device_info.name == "test-ha-api"

        # Subscribe to HomeAssistant service calls
        client.subscribe_service_calls(on_service_call)

        # List entities and services
        _, services = await client.list_entities_services()

        # Find the trigger service
        trigger_service = next(
            (s for s in services if s.name == "trigger_all_tests"), None
        )
        assert trigger_service is not None, "trigger_all_tests service not found"

        # Execute all tests
        client.execute_service(trigger_service, {})

        # Wait for all tests to complete with appropriate timeouts
        try:
            # Give the tests time to execute
            await asyncio.sleep(0.5)

            # Templated service test - the main bug fix
            computed_value = await asyncio.wait_for(lambda_computed_future, timeout=5.0)
            # Verify the computed value is reasonable (75 * 255 / 100 = 191.25 -> 191)
            assert computed_value in ["191", "192"], (
                f"Unexpected computed value: {computed_value}"
            )

            # Check state reads (these will show "has no state" in test environment)
            await asyncio.wait_for(ha_temp_state_future, timeout=5.0)
            await asyncio.wait_for(ha_humidity_state_future, timeout=5.0)
            await asyncio.wait_for(ha_motion_state_future, timeout=5.0)
            await asyncio.wait_for(ha_weather_state_future, timeout=5.0)

            # Number test
            number_value = await asyncio.wait_for(ha_number_future, timeout=5.0)
            assert number_value == "42.5", f"Unexpected number value: {number_value}"

            # Wait for completion
            await asyncio.wait_for(tests_complete_future, timeout=5.0)

            # Give a bit of time for all service calls to be received
            await asyncio.sleep(0.5)

            # Now verify the protobuf messages
            # 1. Basic service call
            basic_call = await asyncio.wait_for(basic_service_call_future, timeout=2.0)
            assert basic_call.service == "light.turn_on"
            assert "entity_id" in basic_call.data, (
                f"entity_id not found in data: {basic_call.data}"
            )
            assert basic_call.data["entity_id"] == "light.test_light", (
                f"Wrong entity_id: {basic_call.data['entity_id']}"
            )
            assert "brightness" in basic_call.data, (
                f"brightness not found in data: {basic_call.data}"
            )
            assert basic_call.data["brightness"] == "255", (
                f"Wrong brightness: {basic_call.data['brightness']}"
            )

            # 2. Templated service call - verify the temporary string issue is fixed
            templated_call = await asyncio.wait_for(
                templated_service_call_future, timeout=2.0
            )
            assert templated_call.service == "light.turn_on"
            # Check the computed brightness value
            assert "brightness" in templated_call.data
            assert templated_call.data["brightness"] in ["191", "192"]  # 75 * 255 / 100
            # Check data_template
            assert "color_name" in templated_call.data_template
            assert templated_call.data_template["color_name"] == "test_value"
            # Check variables
            assert "transition" in templated_call.variables
            assert templated_call.variables["transition"] == "2.5"

            # 3. Empty string service call
            empty_call = await asyncio.wait_for(
                empty_string_service_call_future, timeout=2.0
            )
            assert empty_call.service == "notify.test"
            # Verify empty strings are properly handled
            assert "title" in empty_call.data and empty_call.data["title"] == ""
            assert (
                "target" in empty_call.data_template
                and empty_call.data_template["target"] == ""
            )
            assert (
                "sound" in empty_call.variables and empty_call.variables["sound"] == ""
            )

            # 4. Multiple fields service call
            multi_call = await asyncio.wait_for(
                multiple_fields_service_call_future, timeout=2.0
            )
            assert multi_call.service == "climate.set_temperature"
            assert multi_call.data["temperature"] == "22"
            assert multi_call.data["hvac_mode"] == "heat"
            assert multi_call.data_template["target_temp_high"] == "24"
            assert multi_call.variables["preset_mode"] == "comfort"

            # 5. Complex lambda service call
            complex_call = await asyncio.wait_for(
                complex_lambda_service_call_future, timeout=2.0
            )
            assert complex_call.service == "script.test_script"
            assert complex_call.data["entity_id"] == "light.living_room"
            assert complex_call.data["brightness_pct"] == "99"  # 42 * 2.38 ≈ 99
            # Check message includes sensor value
            assert "message" in complex_call.data_template
            assert "Sensor: 42.0" in complex_call.data_template["message"]

            # 6. All empty service call
            all_empty_call = await asyncio.wait_for(
                all_empty_service_call_future, timeout=2.0
            )
            assert all_empty_call.service == "test.empty"
            # All fields should be empty strings
            assert all(v == "" for v in all_empty_call.data.values())
            assert all(v == "" for v in all_empty_call.data_template.values())
            assert all(v == "" for v in all_empty_call.variables.values())

            # 7. HA Number service call
            number_call = await asyncio.wait_for(
                ha_number_service_call_future, timeout=2.0
            )
            assert number_call.service == "input_number.set_value"
            assert number_call.data["entity_id"] == "input_number.test_number"
            # The value might be formatted with trailing zeros
            assert float(number_call.data["value"]) == 42.5

            # 8. HA Switch service calls
            switch_on_call = await asyncio.wait_for(
                ha_switch_on_service_call_future, timeout=2.0
            )
            assert switch_on_call.service == "switch.turn_on"
            assert switch_on_call.data["entity_id"] == "switch.test_switch"

            switch_off_call = await asyncio.wait_for(
                ha_switch_off_service_call_future, timeout=2.0
            )
            assert switch_off_call.service == "switch.turn_off"
            assert switch_off_call.data["entity_id"] == "switch.test_switch"

        except TimeoutError as e:
            # Show recent log lines for debugging
            recent_logs = "\n".join(log_lines[-20:])
            service_calls_summary = "\n".join(
                f"- {call.service}" for call in ha_service_calls
            )
            pytest.fail(
                f"Test timed out waiting for expected log pattern or service call. Error: {e}\n\n"
                f"Recent log lines:\n{recent_logs}\n\n"
                f"Received service calls:\n{service_calls_summary}"
            )
