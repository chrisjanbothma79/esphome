#!/usr/bin/env python3
"""Determine which tests should run based on changed files.

This script is a centralized way to determine which CI tests need to run based on
what files have changed. It outputs JSON with the following structure:

{
  "integration_tests": true/false,
  "clang_tidy": true/false,
  "changed_components": ["component1", "component2", ...],
  "component_test_count": 5
}

The CI workflow uses this information to:
- Skip or run integration tests
- Skip or run clang-tidy (and whether to do a full scan)
- Determine which components to test individually
- Decide how to split component tests (if there are many)

Usage:
  python script/determine_tests_to_run.py [-b BRANCH]

Options:
  -b, --branch BRANCH  Branch to compare against (default: dev)
"""

from __future__ import annotations

import argparse
import json
from typing import Any

from helpers import (
    get_changed_components,
    should_run_clang_tidy,
    should_run_integration_tests,
)


def main() -> None:
    """Main function that determines which tests to run."""
    parser = argparse.ArgumentParser(
        description="Determine which tests should run based on changed files"
    )
    parser.add_argument(
        "-b", "--branch", help="Branch to compare changed files against"
    )
    args = parser.parse_args()

    # Determine what should run
    run_integration = should_run_integration_tests(args.branch)
    run_clang_tidy = should_run_clang_tidy(args.branch)

    # Get changed components
    changed_components = get_changed_components()

    # Build output
    output: dict[str, Any] = {
        "integration_tests": run_integration,
        "clang_tidy": run_clang_tidy,
    }

    # Only include component info if we successfully got the list
    if changed_components is not None:
        output["changed_components"] = changed_components
        output["component_test_count"] = len(changed_components)
    else:
        # None means all components need testing (e.g., core files changed)
        output["changed_components"] = []
        output["component_test_count"] = -1  # Indicates "test all"

    # Output as JSON
    print(json.dumps(output))


if __name__ == "__main__":
    main()
