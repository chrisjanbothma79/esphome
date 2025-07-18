# How to write C++ ESPHome unit tests

1. Locate the folder with your component or create a new one with the same name as the component.
2. Write the tests. You can add as many .cpp and .h files as you need to organize your tests.

## Running component unit tests

(from the repository root)
```bash
./script/cpp_unit_test.py component1 component2 ...
```

The above will compile and run the provided components and their tests.

To run a specific test suite, you can provide a Google Test filter:

```bash
GTEST_FILTER='UART*' ./script/cpp_unit_test.py uart modbus
```

The process will return `0` for succcess or nonzero for failure. In case of failure, the errors will be printed out to the console.
