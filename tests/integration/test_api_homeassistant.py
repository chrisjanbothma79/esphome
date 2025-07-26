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

    # Create futures for all expected log patterns
    test_started_future = loop.create_future()
    basic_service_future = loop.create_future()
    basic_data_future = loop.create_future()
    templated_service_future = loop.create_future()
    lambda_computed_future = loop.create_future()
    empty_string_future = loop.create_future()
    empty_title_future = loop.create_future()
    empty_target_future = loop.create_future()
    empty_sound_future = loop.create_future()
    multiple_fields_future = loop.create_future()
    complex_lambda_future = loop.create_future()
    all_empty_future = loop.create_future()
    rapid_calls_future = loop.create_future()
    rapid_complete_future = loop.create_future()

    # State reading futures
    reading_states_future = loop.create_future()
    ha_temp_state_future = loop.create_future()
    ha_humidity_state_future = loop.create_future()
    ha_motion_state_future = loop.create_future()
    ha_weather_state_future = loop.create_future()
    ha_empty_state_future = loop.create_future()

    # State update futures
    temp_update_future = loop.create_future()
    humidity_update_future = loop.create_future()
    motion_update_future = loop.create_future()
    weather_update_future = loop.create_future()

    # Number and switch futures
    ha_number_future = loop.create_future()
    ha_switch_on_future = loop.create_future()
    ha_switch_off_future = loop.create_future()

    tests_complete_future = loop.create_future()

    # Patterns to match in logs
    test_started_pattern = re.compile(r"=== Starting Home Assistant API Tests ===")
    basic_service_pattern = re.compile(
        r"Sending HomeAssistant service call: light\.turn_on"
    )
    basic_data_pattern = re.compile(
        r"Service data: entity_id=light\.test_light brightness=255"
    )
    templated_service_pattern = re.compile(r"Testing templated service call")
    lambda_computed_pattern = re.compile(r"Lambda computed value: (\d+)")
    empty_string_pattern = re.compile(r"Testing empty string values")
    empty_title_pattern = re.compile(r"Empty value for key: title")
    empty_target_pattern = re.compile(r"Empty value for key: target")
    empty_sound_pattern = re.compile(r"Empty value for key: sound")
    multiple_fields_pattern = re.compile(r"Testing multiple data fields")
    complex_lambda_pattern = re.compile(r"Testing complex lambda expressions")
    all_empty_pattern = re.compile(r"All empty service call completed")
    rapid_calls_pattern = re.compile(r"Testing rapid service calls")
    rapid_complete_pattern = re.compile(r"Rapid service calls completed")

    # State patterns
    reading_states_pattern = re.compile(r"Reading current HA states")
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
    ha_empty_state_pattern = re.compile(r"HA Empty State has no value \(expected\)")

    # State update patterns
    temp_update_pattern = re.compile(r"HA Temperature state updated: ([\d.]+)")
    humidity_update_pattern = re.compile(r"HA Humidity state updated: ([\d.]+)")
    motion_update_pattern = re.compile(r"HA Motion state changed: (ON|OFF)")
    weather_update_pattern = re.compile(r"HA Weather condition updated: (\w+)")

    # Number and switch patterns
    ha_number_pattern = re.compile(r"Setting HA number to: ([\d.]+)")
    ha_switch_on_pattern = re.compile(r"Toggling HA switch: switch\.test_switch ON")
    ha_switch_off_pattern = re.compile(r"Toggling HA switch: switch\.test_switch OFF")

    tests_complete_pattern = re.compile(r"=== All tests completed ===")

    # Track all log lines for debugging
    log_lines: list[str] = []

    def check_output(line: str) -> None:
        """Check log output for expected messages."""
        log_lines.append(line)

        # Check test flow patterns
        if not test_started_future.done() and test_started_pattern.search(line):
            test_started_future.set_result(True)
        elif not basic_service_future.done() and basic_service_pattern.search(line):
            basic_service_future.set_result(True)
        elif not basic_data_future.done() and basic_data_pattern.search(line):
            basic_data_future.set_result(True)
        elif not templated_service_future.done() and templated_service_pattern.search(
            line
        ):
            templated_service_future.set_result(True)
        elif not lambda_computed_future.done():
            match = lambda_computed_pattern.search(line)
            if match:
                lambda_computed_future.set_result(match.group(1))
        elif not empty_string_future.done() and empty_string_pattern.search(line):
            empty_string_future.set_result(True)
        elif not empty_title_future.done() and empty_title_pattern.search(line):
            empty_title_future.set_result(True)
        elif not empty_target_future.done() and empty_target_pattern.search(line):
            empty_target_future.set_result(True)
        elif not empty_sound_future.done() and empty_sound_pattern.search(line):
            empty_sound_future.set_result(True)
        elif not multiple_fields_future.done() and multiple_fields_pattern.search(line):
            multiple_fields_future.set_result(True)
        elif not complex_lambda_future.done() and complex_lambda_pattern.search(line):
            complex_lambda_future.set_result(True)
        elif not all_empty_future.done() and all_empty_pattern.search(line):
            all_empty_future.set_result(True)
        elif not rapid_calls_future.done() and rapid_calls_pattern.search(line):
            rapid_calls_future.set_result(True)
        elif not rapid_complete_future.done() and rapid_complete_pattern.search(line):
            rapid_complete_future.set_result(True)

        # Check state reading patterns
        elif not reading_states_future.done() and reading_states_pattern.search(line):
            reading_states_future.set_result(True)
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
        elif not ha_empty_state_future.done() and ha_empty_state_pattern.search(line):
            ha_empty_state_future.set_result(True)

        # Check state update patterns
        elif not temp_update_future.done() and temp_update_pattern.search(line):
            temp_update_future.set_result(line)
        elif not humidity_update_future.done() and humidity_update_pattern.search(line):
            humidity_update_future.set_result(line)
        elif not motion_update_future.done() and motion_update_pattern.search(line):
            motion_update_future.set_result(line)
        elif not weather_update_future.done() and weather_update_pattern.search(line):
            weather_update_future.set_result(line)

        # Check number and switch patterns
        elif not ha_number_future.done() and ha_number_pattern.search(line):
            match = ha_number_pattern.search(line)
            if match:
                ha_number_future.set_result(match.group(1))
        elif not ha_switch_on_future.done() and ha_switch_on_pattern.search(line):
            ha_switch_on_future.set_result(True)
        elif not ha_switch_off_future.done() and ha_switch_off_pattern.search(line):
            ha_switch_off_future.set_result(True)

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

        # List entities and services
        entities, services = await client.list_entities_services()

        # Find the trigger service
        trigger_service = next(
            (s for s in services if s.name == "trigger_all_tests"), None
        )
        assert trigger_service is not None, "trigger_all_tests service not found"

        # Execute all tests
        client.execute_service(trigger_service, {})

        # Wait for all tests to complete with appropriate timeouts
        try:
            # Test flow checks
            await asyncio.wait_for(test_started_future, timeout=5.0)
            await asyncio.wait_for(basic_service_future, timeout=5.0)
            await asyncio.wait_for(basic_data_future, timeout=5.0)

            # Templated service test - the main bug fix
            await asyncio.wait_for(templated_service_future, timeout=5.0)
            computed_value = await asyncio.wait_for(lambda_computed_future, timeout=5.0)
            # Verify the computed value is reasonable (75 * 255 / 100 = 191.25 -> 191)
            assert computed_value in ["191", "192"], (
                f"Unexpected computed value: {computed_value}"
            )

            # Empty string tests
            await asyncio.wait_for(empty_string_future, timeout=5.0)
            await asyncio.wait_for(empty_title_future, timeout=5.0)
            await asyncio.wait_for(empty_target_future, timeout=5.0)
            await asyncio.wait_for(empty_sound_future, timeout=5.0)

            # Other service tests
            await asyncio.wait_for(multiple_fields_future, timeout=5.0)
            await asyncio.wait_for(complex_lambda_future, timeout=5.0)
            await asyncio.wait_for(all_empty_future, timeout=5.0)
            await asyncio.wait_for(rapid_calls_future, timeout=5.0)
            await asyncio.wait_for(rapid_complete_future, timeout=5.0)

            # State reading test
            await asyncio.wait_for(reading_states_future, timeout=5.0)

            # Check state reads (these will show "has no state" in test environment)
            await asyncio.wait_for(ha_temp_state_future, timeout=5.0)
            await asyncio.wait_for(ha_humidity_state_future, timeout=5.0)
            await asyncio.wait_for(ha_motion_state_future, timeout=5.0)
            await asyncio.wait_for(ha_weather_state_future, timeout=5.0)
            await asyncio.wait_for(ha_empty_state_future, timeout=5.0)

            # Number and switch tests
            number_value = await asyncio.wait_for(ha_number_future, timeout=5.0)
            assert number_value == "42.5", f"Unexpected number value: {number_value}"

            await asyncio.wait_for(ha_switch_on_future, timeout=5.0)
            await asyncio.wait_for(ha_switch_off_future, timeout=5.0)

            # Wait for completion
            await asyncio.wait_for(tests_complete_future, timeout=5.0)

        except TimeoutError as e:
            # Show recent log lines for debugging
            recent_logs = "\n".join(log_lines[-20:])
            pytest.fail(
                f"Test timed out waiting for expected log pattern. Error: {e}\n\nRecent log lines:\n{recent_logs}"
            )
