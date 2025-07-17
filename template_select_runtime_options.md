# Template Select with Runtime Options

This refactored template select component allows you to define options dynamically at runtime instead of only at compile time.

## Configuration Options

### Static Options (Original Behavior)
```yaml
select:
  - platform: template
    name: "Static Example"
    options:
      - "Option 1"
      - "Option 2" 
      - "Option 3"
    initial_option: "Option 1"
    optimistic: true
```

### Dynamic Options using Lambda
```yaml
select:
  - platform: template
    name: "Dynamic Example"
    options_lambda: |-
      // Return options based on runtime conditions
      std::vector<std::string> options;
      if (id(some_sensor).state > 10) {
        options = {"High", "Very High", "Critical"};
      } else {
        options = {"Low", "Normal", "Medium"};
      }
      return options;
    lambda: |-
      // Return current value based on sensor state
      if (id(some_sensor).state > 50) {
        return std::string{"Critical"};
      } else if (id(some_sensor).state > 20) {
        return std::string{"High"};
      } else {
        return std::string{"Normal"};
      }
    update_interval: 5s
```

## C++ API Usage

The following methods are now available for runtime option management:

### Set Complete Options List
```cpp
// Replace all options with new list
std::vector<std::string> new_options = {"Option A", "Option B", "Option C"};
id(my_select).set_options(new_options);
```

### Add Single Option
```cpp
// Add a new option to the existing list
id(my_select).add_option("New Option");
```

### Remove Single Option
```cpp
// Remove an option from the list
id(my_select).remove_option("Unwanted Option");
```

### Clear and Set New Options
```cpp
// Clear all existing options and set new ones
std::vector<std::string> fresh_options = {"Fresh 1", "Fresh 2"};
id(my_select).clear_and_set_options(fresh_options);
```

## Use Cases

1. **Conditional Options**: Show different options based on sensor values, time of day, or system state
2. **Dynamic Discovery**: Add/remove options as devices come online/offline
3. **User Configuration**: Allow options to be modified through other components
4. **External Data**: Update options based on API responses or external databases

## Example: Network Device Discovery

```yaml
select:
  - platform: template
    name: "Available Devices"
    id: device_selector
    options_lambda: |-
      std::vector<std::string> devices;
      // Scan for available devices and populate options
      for (auto& device : discovered_devices) {
        if (device.is_online()) {
          devices.push_back(device.get_name());
        }
      }
      return devices.empty() ? std::vector<std::string>{"No devices"} : devices;
    update_interval: 30s
    optimistic: true
```

## Notes

- When using `options_lambda`, you cannot specify static `options`
- The options lambda is called during `update()` cycles
- If options change, the current state is validated and may be reset to the first available option
- Empty options lists from lambda are ignored with a warning
- The component automatically handles state validation when options change
