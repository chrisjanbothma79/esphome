#!/usr/bin/env python3
"""Determine if integration tests should run based on changed files."""

from __future__ import annotations

import argparse
from pathlib import Path
import sys
from typing import Any

from helpers import changed_files
import yaml

from esphome.const import KEY_CORE
from esphome.core import CORE
from esphome.loader import get_component


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


def get_all_dependencies(component_names: set[str]) -> set[str]:
    """Get all dependencies for a set of components."""
    all_components: set[str] = set(component_names)

    # Set up fake config path for component loading
    root = Path(__file__).parent.parent
    CORE.config_path = str(root)
    CORE.data[KEY_CORE] = {}

    # Keep finding dependencies until no new ones are found
    while True:
        new_components: set[str] = set()

        for comp_name in all_components:
            comp = get_component(comp_name)
            if not comp:
                continue

            # Add dependencies (extract component name before '.')
            new_components.update(dep.split(".")[0] for dep in comp.dependencies)

            # Add auto_load components
            new_components.update(comp.auto_load)

        # Check if we found any new components
        new_components -= all_components
        if not new_components:
            break

        all_components.update(new_components)

    return all_components


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-b", "--branch", help="Branch to compare changed files against"
    )
    args = parser.parse_args()

    if args.branch:
        changed: list[str] = changed_files(args.branch)
    else:
        changed: list[str] = changed_files()

    # Check if any core files changed (esphome/core/*)
    for file in changed:
        if file.startswith("esphome/core/"):
            print("true")
            sys.exit(0)

    # Check if any Python files outside components changed
    for file in changed:
        if file.startswith("esphome/") and file.endswith(".py"):
            if not file.startswith("esphome/components/"):
                print("true")
                sys.exit(0)

    # Check if any integration test files changed
    if any("tests/integration" in file for file in changed):
        print("true")
        sys.exit(0)

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
                    print("true")
                    sys.exit(0)

    print("false")
    sys.exit(0)


if __name__ == "__main__":
    main()
