# ESPHome Integration Tests

This directory contains end-to-end integration tests for ESPHome, focusing on testing the complete flow from YAML configuration to running devices with API connections.

## Structure

- `conftest.py` - Common fixtures and utilities
- `fixtures/` - YAML configuration files for tests
- `test_*.py` - Individual test files

## How it works

### Automatic YAML Loading

The `yaml_config` fixture automatically loads YAML configurations based on the test name:

1. By default, it looks for a file named after the test function (e.g., `test_host_mode_basic` → `fixtures/host_mode_basic.yaml`)
2. You can override this with the `@pytest.mark.yaml_fixture("custom_name")` decorator
3. If no fixture file is found, it falls back to a default configuration

### Writing Tests

Each test should:
1. Use the `yaml_config` fixture to get its configuration
2. Write the config to a file using `write_yaml_config`
3. Compile the configuration using `compile_esphome`
4. Run the device using `run_esphome_process`
5. Connect and test using `api_client_connected` context manager

### Example

```python
@pytest.mark.asyncio
@pytest.mark.yaml_fixture("my_custom_fixture")  # Optional: specify custom fixture
async def test_my_feature(
    yaml_config: str,
    write_yaml_config: ConfigWriter,
    compile_esphome: CompileFunction,
    run_esphome_process: RunFunction,
    api_client_connected: Callable[..., AsyncContextManager[APIClient]],
) -> None:
    config_path = await write_yaml_config("test.yaml", yaml_config)
    await compile_esphome(config_path)
    process = await run_esphome_process(config_path)
    
    async with api_client_connected() as client:
        # Test your feature
        pass
```

## Running Tests

```bash
# Run all integration tests
script/integration_test

# Run a specific test
pytest -vv tests/integration/test_host_mode_basic.py
```