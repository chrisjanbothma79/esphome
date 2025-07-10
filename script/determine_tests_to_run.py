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
from pathlib import Path
import subprocess
import sys
from typing import Any

from helpers import (
    should_run_clang_format,
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
    run_clang_format = should_run_clang_format(args.branch)

    # Get changed components using list-components.py for exact compatibility
    script_path = Path(__file__).parent / "list-components.py"
    cmd = [sys.executable, str(script_path), "--changed"]
    if args.branch:
        cmd.extend(["-b", args.branch])

    result = subprocess.run(cmd, capture_output=True, text=True, check=True)
    # list-components.py outputs one component per line
    components_output = result.stdout.strip()
    if components_output:
        changed_components = components_output.split("\n")
    else:
        changed_components = []

    # Build output
    output: dict[str, Any] = {
        "integration_tests": run_integration,
        "clang_tidy": run_clang_tidy,
        "clang_format": run_clang_format,
        "changed_components": changed_components,
        "component_test_count": len(changed_components),
    }

    # Output as JSON
    print(json.dumps(output))


if __name__ == "__main__":
    main()
