#!/usr/bin/env python3
"""Determine if integration tests should run based on changed files."""

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
