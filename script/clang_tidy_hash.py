#!/usr/bin/env python3
"""Calculate and manage hash for clang-tidy configuration."""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path
import sys

# Add the script directory to path to import helpers
script_dir = Path(__file__).parent
sys.path.insert(0, str(script_dir))


def get_clang_tidy_version_from_requirements() -> str:
    """Get clang-tidy version from requirements_dev.txt"""
    requirements_path = Path(__file__).parent.parent / "requirements_dev.txt"
    with open(requirements_path) as f:
        for line in f:
            line = line.strip()
            if line.startswith("clang-tidy=="):
                # Return the full line including version and comment
                return line
    return "clang-tidy version not found"


def extract_platformio_flags() -> str:
    """Extract clang-tidy related flags from platformio.ini"""
    flags: list[str] = []
    in_clangtidy_section = False

    platformio_path = Path(__file__).parent.parent / "platformio.ini"
    with open(platformio_path) as f:
        for line in f:
            line = line.strip()
            if line.startswith("[flags:clangtidy]"):
                in_clangtidy_section = True
                continue
            elif line.startswith("[") and in_clangtidy_section:
                break
            elif in_clangtidy_section and line and not line.startswith("#"):
                flags.append(line)

    return "\n".join(sorted(flags))


def calculate_clang_tidy_hash() -> str:
    """Calculate hash of clang-tidy configuration and version"""
    hasher = hashlib.sha256()

    # Hash .clang-tidy file
    clang_tidy_path = Path(__file__).parent.parent / ".clang-tidy"
    with open(clang_tidy_path, "rb") as f:
        hasher.update(f.read())

    # Hash clang-tidy version from requirements_dev.txt
    version = get_clang_tidy_version_from_requirements()
    hasher.update(version.encode())

    # Hash relevant platformio.ini sections
    pio_flags = extract_platformio_flags()
    hasher.update(pio_flags.encode())

    return hasher.hexdigest()


def read_stored_hash() -> str | None:
    """Read the stored hash from file"""
    hash_file = Path(__file__).parent.parent / ".clang-tidy.hash"
    if hash_file.exists():
        with open(hash_file) as f:
            return f.read().strip()
    return None


def write_hash(hash_value: str) -> None:
    """Write hash to file"""
    hash_file = Path(__file__).parent.parent / ".clang-tidy.hash"
    with open(hash_file, "w") as f:
        f.write(hash_value)


def main() -> None:
    parser = argparse.ArgumentParser(description="Manage clang-tidy configuration hash")
    parser.add_argument(
        "--check",
        action="store_true",
        help="Check if full scan needed (exit 0 if needed)",
    )
    parser.add_argument("--update", action="store_true", help="Update the hash file")
    parser.add_argument(
        "--update-if-changed",
        action="store_true",
        help="Update hash only if configuration changed (for pre-commit)",
    )
    parser.add_argument(
        "--verify", action="store_true", help="Verify hash matches (for CI)"
    )

    args = parser.parse_args()

    current_hash = calculate_clang_tidy_hash()
    stored_hash = read_stored_hash()

    if args.check:
        # Exit 0 if full scan needed (hash changed or no hash file)
        sys.exit(0 if current_hash != stored_hash else 1)

    elif args.update:
        write_hash(current_hash)
        print(f"Hash updated: {current_hash}")

    elif args.update_if_changed:
        if current_hash != stored_hash:
            write_hash(current_hash)
            print(f"Clang-tidy hash updated: {current_hash}")
            # Exit 0 so pre-commit can stage the file
            sys.exit(0)
        else:
            print("Clang-tidy hash unchanged")
            sys.exit(0)

    elif args.verify:
        if current_hash != stored_hash:
            print("ERROR: Clang-tidy configuration has changed but hash not updated!")
            print(f"Expected: {current_hash}")
            print(f"Found: {stored_hash}")
            print("\nPlease run: script/clang_tidy_hash.py --update")
            sys.exit(1)
        print("Hash verification passed")

    else:
        print(f"Current hash: {current_hash}")
        print(f"Stored hash: {stored_hash}")
        print(f"Match: {current_hash == stored_hash}")


if __name__ == "__main__":
    main()
