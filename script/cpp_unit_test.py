#!/usr/bin/env python3
import argparse
import hashlib
import os
from pathlib import Path
import subprocess
import sys

from esphome.__main__ import command_compile, parse_args
from esphome.config import validate_config
from esphome.core import CORE
from esphome.loader import ComponentManifest, get_component
from esphome.platformio_api import get_idedata

# This must coincide with the version in /platformio.ini
PLATFORMIO_GOOGLE_TEST_LIB = "google/googletest@^1.15.2"

# Path to the current Python file
CURRENT_FILE = Path(__file__).resolve()

# Path to /tests/components
COMPONENTS_TESTS_DIR = CURRENT_FILE.parent.parent / "tests" / "components"

# Path to list-components.py
LIST_COMPONENTS_SCRIPT = CURRENT_FILE.parent / "list-components.py"


def get_all_components():
    try:
        result = subprocess.run(
            [sys.executable, str(LIST_COMPONENTS_SCRIPT)],
            check=True,
            stdout=subprocess.PIPE,
            text=True,
        )
        return [line.strip() for line in result.stdout.splitlines() if line.strip()]
    except subprocess.CalledProcessError as e:
        print(f"Error invoking list-components.py: {e}", file=sys.stderr)
        return []


def hash_components(components):
    key = ",".join(components)
    return hashlib.sha256(key.encode()).hexdigest()[:16]


def _process_dependencies(components: list[str], manifests: set[ComponentManifest]):
    for component_name in components:
        m = get_component(component_name)
        if m is None:
            raise ValueError(
                f"Component '{component_name}' not found. Make sure it is a valid component."
            )

        if m not in manifests:
            manifests.add(m)
            _process_dependencies(m.dependencies, manifests)


def get_component_name(module_name):
    parts = module_name.strip(".").split(".")
    if parts:
        return parts[-1]
    else:
        raise ValueError(f"Invalid module name {module_name}")


def process_dependencies(components: list[str]):
    manifests: set[ComponentManifest] = set()
    _process_dependencies(components, manifests)
    return sorted([get_component_name(m.module.__name__) for m in manifests])


def filter_components_without_tests(components: list[str]) -> list[str]:
    """
    Filter out components that do not have a corresponding test file.
    This is done by checking if the component's directory contains at least a .cpp file.
    """
    filtered_components = []
    for component in components:
        test_dir = COMPONENTS_TESTS_DIR / component
        if test_dir.is_dir() and any(test_dir.glob("*.cpp")):
            filtered_components.append(component)
        else:
            print(
                f"WARNING: No tests found for component '{component}', skipping.",
                file=sys.stderr,
            )
    return filtered_components


def run_tests(selected_components):
    # Skip tests on Windows
    if os.name == "nt":
        print("Skipping esphome tests on Windows", file=sys.stderr)
        return 1

    # Remove components that do not have tests
    components = filter_components_without_tests(selected_components)

    if len(components) == 0:
        print(
            "No components specified or no tests found for the specified components.",
            file=sys.stderr,
        )
        return 0

    components = sorted(components)

    # Obtain possible dependencies for the requested components:
    components_with_dependencies = process_dependencies(components)

    # Build a list of include folders, one folder per component containing tests.
    # A special replacement main.cpp is located in /tests/components/main.cpp
    includes = ["main.cpp"] + components

    # Create a unique name for this config based on the actual components being tested
    # to maximize cache during testing
    config_name = "cpptests-" + hash_components(components)

    config = {
        "esphome": {
            "name": config_name,
            "friendly_name": "CPP Unit Tests",
            "libraries": PLATFORMIO_GOOGLE_TEST_LIB,
            "platformio_options": {
                "build_type": "debug",
                "build_unflags": [
                    "-Os",  # remove size-opt flag
                ],
                "build_flags": [
                    "-Og",  # optimize for debug
                ],
                "debug_build_flags": [  # only for debug builds
                    "-g3",  # max debug info
                    "-ggdb3",
                ],
            },
            "includes": includes,
        },
        "host": {},
        "logger": {"level": "DEBUG"},
    }

    CORE.config_path = str(COMPONENTS_TESTS_DIR / "dummy.yaml")
    CORE.dashboard = None

    # Validate config will expand the above with defaults:
    config = validate_config(config, {})

    # Add all components and dependencies to the base configuration after validation, so their files
    # are added to the build.
    # These components are not configured in any way. The below will just make them present
    # so they are picked up by the compile step
    config.update({key: {} for key in components_with_dependencies})

    print(f"Testing components: {', '.join(components)}")
    CORE.config = config
    args = parse_args(["program", "compile", CORE.config_path])
    try:
        exit_code = command_compile(args, config)

        if exit_code != 0:
            print(f"Error compiling unit tests for {', '.join(components)}")
            return exit_code
    except Exception as e:
        print(
            f"Error compiling unit tests for {', '.join(components)}. Check path. : {e}"
        )
        return 2

    # After a successful compilation, locate the executable and run it:
    idedata = get_idedata(config)
    if idedata is None:
        print("Cannot find executable")
        return 1

    program_path = idedata.raw["prog_path"]
    run_cmd = [program_path]
    run_proc = subprocess.run(run_cmd, check=False)
    return run_proc.returncode


def main():
    parser = argparse.ArgumentParser(
        description="Run C++ unit tests for ESPHome components."
    )
    parser.add_argument(
        "components",
        nargs="*",
        help="List of components to test. Use --all to test all known components.",
    )
    parser.add_argument("--all", action="store_true", help="Test all known components.")

    args = parser.parse_args()

    if args.all:
        components = get_all_components()
    else:
        components = args.components

    sys.exit(run_tests(components))


if __name__ == "__main__":
    main()
