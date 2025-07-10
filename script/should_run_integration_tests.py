#!/usr/bin/env python3
"""Determine if integration tests should run based on changed files.

This script is used by the CI workflow to intelligently skip integration tests when they're
not needed, saving significant CI time and resources.

Integration tests will run when ANY of the following conditions are met:

1. Core C++ files changed (esphome/core/*)
   - Any .cpp, .h, .tcc files in the core directory
   - These files contain fundamental functionality used throughout ESPHome
   - Examples: esphome/core/component.cpp, esphome/core/application.h

2. Python files directly in esphome/ directory changed
   - Only .py files directly in esphome/ (not in subdirectories)
   - These are core Python files that affect the entire system
   - Examples: esphome/config.py, esphome/core.py, esphome/__init__.py
   - NOT included: esphome/dashboard/*.py, esphome/components/*/*.py

3. Integration test files changed
   - Any file in tests/integration/ directory
   - This includes test files themselves and fixture YAML files
   - Examples: tests/integration/test_api.py, tests/integration/fixtures/api.yaml

4. Components used by integration tests (or their dependencies) changed
   - The script parses all YAML files in tests/integration/fixtures/
   - Extracts which components are used in integration tests
   - Recursively finds all dependencies of those components
   - If any of these components have changes, tests must run
   - Example: If api.yaml uses 'sensor' and 'api' components, and 'api' depends on 'socket',
     then changes to sensor/, api/, or socket/ components trigger tests

The script returns:
- "true" (exit 0): Integration tests should run
- "false" (exit 0): Integration tests can be skipped

Usage:
  python script/should_run_integration_tests.py [-b BRANCH]

Options:
  -b, --branch BRANCH  Branch to compare against (default: dev)
"""

from __future__ import annotations

import argparse
from pathlib import Path
import sys
from typing import Any

from helpers import changed_files, get_all_dependencies
import yaml


def get_components_from_fixtures() -> set[str]:
    """Extract all components used in integration test fixtures."""
    components: set[str] = set()
    fixtures_dir = Path(__file__).parent.parent / "tests" / "integration" / "fixtures"

    for yaml_file in fixtures_dir.glob("*.yaml"):
        with open(yaml_file) as f:
            config: dict[str, Any] | None = yaml.safe_load(f)
            if not config:
                continue

            # Add all top-level component keys
            components.update(config.keys())

            # Add platform components (e.g., output.template)
            for value in config.values():
                if not isinstance(value, list):
                    continue

                for item in value:
                    if isinstance(item, dict) and "platform" in item:
                        components.add(item["platform"])

    return components


def should_run_integration_tests(branch: str | None = None) -> bool:
    """Determine if integration tests should run based on changed files.

    Args:
        branch: Branch to compare against. If None, uses default.

    Returns:
        True if integration tests should run, False otherwise.
    """
    if branch:
        changed: list[str] = changed_files(branch)
    else:
        changed: list[str] = changed_files()

    # Check if any core files changed (esphome/core/*)
    for file in changed:
        if file.startswith("esphome/core/"):
            return True

    # Check if any Python files directly in esphome/ changed (not in subdirs)
    for file in changed:
        if file.startswith("esphome/") and file.endswith(".py"):
            # Check if it's directly in esphome/ (no additional slashes after esphome/)
            if file.count("/") == 1:
                return True

    # Check if any integration test files changed
    if any("tests/integration" in file for file in changed):
        return True

    # Get all components used in integration tests and their dependencies
    fixture_components: set[str] = get_components_from_fixtures()
    all_required_components: set[str] = get_all_dependencies(fixture_components)

    # Check if any required components changed
    for file in changed:
        if file.startswith("esphome/components/"):
            parts = file.split("/")
            if len(parts) >= 3:
                component = parts[2]
                if component in all_required_components:
                    return True

    return False


def main() -> bool:
    """Main function that parses arguments and calls should_run_integration_tests."""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-b", "--branch", help="Branch to compare changed files against"
    )
    args = parser.parse_args()

    return should_run_integration_tests(args.branch)


if __name__ == "__main__":
    result = main()
    print("true" if result else "false")
    sys.exit(0)
