"""Common fixtures for integration tests."""

from __future__ import annotations

import asyncio
from collections.abc import AsyncGenerator, Generator
from contextlib import AbstractAsyncContextManager, asynccontextmanager
from pathlib import Path
import signal
import socket
import tempfile

from aioesphomeapi import APIClient, APIConnectionError, ReconnectLogic
import pytest
import pytest_asyncio

from .types import (
    APIClientConnectedFactory,
    APIClientFactory,
    CompileFunction,
    ConfigWriter,
    RunCompiledFunction,
    RunFunction,
)


@pytest.fixture
def integration_test_dir() -> Generator[Path]:
    """Create a temporary directory for integration tests."""
    with tempfile.TemporaryDirectory() as tmpdir:
        yield Path(tmpdir)


@pytest.fixture
def unused_tcp_port() -> int:
    """Find an unused TCP port."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind(("", 0))
        return s.getsockname()[1]


@pytest_asyncio.fixture
async def yaml_config(request: pytest.FixtureRequest, unused_tcp_port: int) -> str:
    """Load YAML configuration based on test name."""
    # Get the test function name
    test_name = request.node.name
    # Extract the base test name (remove test_ prefix and any parametrization)
    base_name = test_name.replace("test_", "").split("[")[0]

    # Check if yaml_fixture marker is present
    markers = request.node.iter_markers("yaml_fixture")
    fixture_names = []
    for marker in markers:
        if marker.args:
            fixture_names.extend(marker.args)

    # If no explicit fixture name, use the base test name
    if not fixture_names:
        fixture_names = [base_name]

    # Try to load fixtures in order using executor
    loop = asyncio.get_running_loop()
    for fixture_name in fixture_names:
        fixture_path = Path(__file__).parent / "fixtures" / f"{fixture_name}.yaml"
        if fixture_path.exists():
            content = await loop.run_in_executor(None, fixture_path.read_text)
            # Replace the port in the config if it contains api section
            if "api:" in content:
                # Add port configuration after api:
                content = content.replace("api:", f"api:\n  port: {unused_tcp_port}")
            return content

    # Fallback to default config with dynamic port
    return f"""
esphome:
  name: host-test
host:
api:
  port: {unused_tcp_port}
logger:
"""


@pytest_asyncio.fixture
async def write_yaml_config(
    integration_test_dir: Path, request: pytest.FixtureRequest
) -> AsyncGenerator[ConfigWriter]:
    """Write YAML configuration to a file."""
    # Get the test name for default filename
    test_name = request.node.name
    base_name = test_name.replace("test_", "").split("[")[0]

    async def _write_config(content: str, filename: str | None = None) -> Path:
        if filename is None:
            filename = f"{base_name}.yaml"
        config_path = integration_test_dir / filename
        loop = asyncio.get_running_loop()
        await loop.run_in_executor(None, config_path.write_text, content)
        return config_path

    yield _write_config


async def _run_esphome_command(
    command: str,
    config_path: Path,
    cwd: Path,
) -> asyncio.subprocess.Process:
    """Run an ESPHome command with the given arguments."""
    return await asyncio.create_subprocess_exec(
        "esphome",
        command,
        str(config_path),
        cwd=cwd,
        stdout=None,  # Inherit stdout
        stderr=None,  # Inherit stderr
        stdin=asyncio.subprocess.DEVNULL,
        # Start in a new process group to isolate signal handling
        start_new_session=True,
    )


@pytest_asyncio.fixture
async def compile_esphome(
    integration_test_dir: Path,
) -> AsyncGenerator[CompileFunction]:
    """Compile an ESPHome configuration."""

    async def _compile(config_path: Path) -> None:
        proc = await _run_esphome_command("compile", config_path, integration_test_dir)
        await proc.wait()
        if proc.returncode != 0:
            raise RuntimeError(
                f"Failed to compile {config_path}, return code: {proc.returncode}"
            )

    yield _compile


@pytest_asyncio.fixture
async def run_esphome_process(
    integration_test_dir: Path,
) -> AsyncGenerator[RunFunction]:
    """Run an ESPHome process and manage its lifecycle."""
    processes: list[asyncio.subprocess.Process] = []

    async def _run(config_path: Path) -> asyncio.subprocess.Process:
        process = await _run_esphome_command("run", config_path, integration_test_dir)
        processes.append(process)
        return process

    yield _run

    # Cleanup: terminate all "run" processes gracefully
    for process in processes:
        if process.returncode is None:
            # Send SIGINT (Ctrl+C) for graceful shutdown of the running ESPHome instance
            process.send_signal(signal.SIGINT)
            try:
                await asyncio.wait_for(process.wait(), timeout=5)
            except asyncio.TimeoutError:
                # If SIGINT didn't work, try SIGTERM
                process.terminate()
                try:
                    await asyncio.wait_for(process.wait(), timeout=2)
                except asyncio.TimeoutError:
                    # Last resort: SIGKILL
                    process.kill()
                    await process.wait()


@asynccontextmanager
async def create_api_client(
    address: str = "localhost",
    port: int = 6053,
    password: str = "",
    client_info: str = "integration-test",
) -> AsyncGenerator[APIClient]:
    """Create an API client context manager."""
    client = APIClient(
        address=address, port=port, password=password, client_info=client_info
    )
    try:
        yield client
    finally:
        await client.disconnect()


@pytest_asyncio.fixture
async def api_client_factory(
    unused_tcp_port: int,
) -> AsyncGenerator[APIClientFactory]:
    """Factory for creating API client context managers."""

    def _create_client(
        address: str = "localhost",
        port: int | None = None,
        password: str = "",
        client_info: str = "integration-test",
    ) -> AbstractAsyncContextManager[APIClient]:
        return create_api_client(
            address=address,
            port=port if port is not None else unused_tcp_port,
            password=password,
            client_info=client_info,
        )

    yield _create_client


@asynccontextmanager
async def wait_and_connect_api_client(
    address: str = "localhost",
    port: int = 6053,
    password: str = "",
    client_info: str = "integration-test",
    timeout: float = 30,
) -> AsyncGenerator[APIClient]:
    """Wait for API to be available and connect."""
    client = APIClient(
        address=address, port=port, password=password, client_info=client_info
    )

    # Create a future to signal when connected
    loop = asyncio.get_running_loop()
    connected_future: asyncio.Future[None] = loop.create_future()

    async def on_connect() -> None:
        """Called when successfully connected."""
        if not connected_future.done():
            connected_future.set_result(None)

    async def on_disconnect(expected_disconnect: bool) -> None:
        """Called when disconnected."""
        if not connected_future.done() and not expected_disconnect:
            connected_future.set_exception(
                APIConnectionError("Disconnected before fully connected")
            )

    async def on_connect_error(err: Exception) -> None:
        """Called when connection fails."""
        if not connected_future.done():
            connected_future.set_exception(err)

    # Create and start the reconnect logic
    reconnect_logic = ReconnectLogic(
        client=client,
        on_connect=on_connect,
        on_disconnect=on_disconnect,
        zeroconf_instance=None,  # Not using zeroconf for integration tests
        name=f"{address}:{port}",
        on_connect_error=on_connect_error,
    )

    try:
        # Start the connection
        await reconnect_logic.start()

        # Wait for connection with timeout
        try:
            await asyncio.wait_for(connected_future, timeout=timeout)
        except asyncio.TimeoutError:
            raise TimeoutError(f"Failed to connect to API after {timeout} seconds")

        yield client
    finally:
        # Stop reconnect logic and disconnect
        await reconnect_logic.stop()
        await client.disconnect()


@pytest_asyncio.fixture
async def api_client_connected(
    unused_tcp_port: int,
) -> AsyncGenerator[APIClientConnectedFactory]:
    """Factory for creating connected API client context managers."""

    def _connect_client(
        address: str = "localhost",
        port: int | None = None,
        password: str = "",
        client_info: str = "integration-test",
        timeout: float = 30,
    ) -> AbstractAsyncContextManager[APIClient]:
        return wait_and_connect_api_client(
            address=address,
            port=port if port is not None else unused_tcp_port,
            password=password,
            client_info=client_info,
            timeout=timeout,
        )

    yield _connect_client


@asynccontextmanager
async def run_compiled_context(
    yaml_content: str,
    filename: str | None,
    write_yaml_config: ConfigWriter,
    compile_esphome: CompileFunction,
    run_esphome_process: RunFunction,
) -> AsyncGenerator[asyncio.subprocess.Process]:
    """Context manager to write, compile and run an ESPHome configuration."""
    # Write the YAML config
    config_path = await write_yaml_config(yaml_content, filename)

    # Compile the configuration
    await compile_esphome(config_path)

    # Run the ESPHome device
    process = await run_esphome_process(config_path)
    assert process.returncode is None, "Process died immediately"

    # Give the process a moment to actually start listening
    await asyncio.sleep(1)

    try:
        yield process
    finally:
        # Process cleanup is handled by run_esphome_process fixture
        pass


@pytest_asyncio.fixture
async def run_compiled(
    write_yaml_config: ConfigWriter,
    compile_esphome: CompileFunction,
    run_esphome_process: RunFunction,
) -> AsyncGenerator[RunCompiledFunction]:
    """Write, compile and run an ESPHome configuration."""

    def _run_compiled(
        yaml_content: str, filename: str | None = None
    ) -> AbstractAsyncContextManager[asyncio.subprocess.Process]:
        return run_compiled_context(
            yaml_content,
            filename,
            write_yaml_config,
            compile_esphome,
            run_esphome_process,
        )

    yield _run_compiled
