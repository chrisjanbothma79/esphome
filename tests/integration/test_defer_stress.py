"""Stress test for defer() thread safety with multiple threads."""

import asyncio

from aioesphomeapi import EntityState, Event, EventInfo, UserService
import pytest

from .types import APIClientConnectedFactory, RunCompiledFunction


@pytest.mark.asyncio
async def test_defer_stress(
    yaml_config: str,
    run_compiled: RunCompiledFunction,
    api_client_connected: APIClientConnectedFactory,
) -> None:
    """Test that defer() doesn't crash when called rapidly from multiple threads."""

    async with run_compiled(yaml_config), api_client_connected() as client:
        # Verify we can connect
        device_info = await client.device_info()
        assert device_info is not None
        assert device_info.name == "defer-stress-test"

        # List entities and services
        entity_info, services = await asyncio.wait_for(
            client.list_entities_services(), timeout=5.0
        )

        # Find our test entities
        test_complete_entity: EventInfo | None = None
        test_result_entity: EventInfo | None = None

        for entity in entity_info:
            if isinstance(entity, EventInfo):
                if entity.object_id == "test_complete":
                    test_complete_entity = entity
                elif entity.object_id == "test_result":
                    test_result_entity = entity

        assert test_complete_entity is not None, "test_complete event not found"
        assert test_result_entity is not None, "test_result event not found"

        # Find our test service
        run_stress_test_service: UserService | None = None
        for service in services:
            if service.name == "run_stress_test":
                run_stress_test_service = service
                break

        assert run_stress_test_service is not None, "run_stress_test service not found"

        # Get the event loop
        loop = asyncio.get_running_loop()

        # Subscribe to states (events are delivered as EventStates through subscribe_states)
        test_complete_future: asyncio.Future[bool] = loop.create_future()
        test_result_future: asyncio.Future[bool] = loop.create_future()

        def on_state(state: EntityState) -> None:
            if isinstance(state, Event):
                if state.key == test_complete_entity.key:
                    if (
                        state.event_type == "test_finished"
                        and not test_complete_future.done()
                    ):
                        test_complete_future.set_result(True)
                elif state.key == test_result_entity.key:
                    if not test_result_future.done():
                        if state.event_type == "passed":
                            test_result_future.set_result(True)
                        elif state.event_type == "failed":
                            test_result_future.set_result(False)

        client.subscribe_states(on_state)

        # Call the run_stress_test service to start the test
        client.execute_service(run_stress_test_service, {})

        # Wait for test completion with a longer timeout (threads run for 100ms + processing time)
        try:
            await asyncio.wait_for(test_complete_future, timeout=10.0)
            test_passed = await asyncio.wait_for(test_result_future, timeout=1.0)
        except asyncio.TimeoutError:
            pytest.fail("Stress test did not complete within 10 seconds")

        # Verify the test passed
        assert test_passed is True, (
            "Stress test failed - defer() crashed or failed under thread pressure"
        )
