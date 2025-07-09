from __future__ import annotations

import json
import os.path
from pathlib import Path
import re
import subprocess

import colorama

root_path = os.path.abspath(os.path.normpath(os.path.join(__file__, "..", "..")))
basepath = os.path.join(root_path, "esphome")
temp_folder = os.path.join(root_path, ".temp")
temp_header_file = os.path.join(temp_folder, "all-include.cpp")


def styled(color, msg, reset=True):
    prefix = "".join(color) if isinstance(color, tuple) else color
    suffix = colorama.Style.RESET_ALL if reset else ""
    return prefix + msg + suffix


def print_error_for_file(file, body):
    print(
        styled(colorama.Fore.GREEN, "### File ")
        + styled((colorama.Fore.GREEN, colorama.Style.BRIGHT), file)
    )
    print()
    if body is not None:
        print(body)
        print()


def build_all_include():
    # Build a cpp file that includes all header files in this repo.
    # Otherwise header-only integrations would not be tested by clang-tidy
    headers = []
    for path in walk_files(basepath):
        filetypes = (".h",)
        ext = os.path.splitext(path)[1]
        if ext in filetypes:
            path = os.path.relpath(path, root_path)
            include_p = path.replace(os.path.sep, "/")
            headers.append(f'#include "{include_p}"')
    headers.sort()
    headers.append("")
    content = "\n".join(headers)
    p = Path(temp_header_file)
    p.parent.mkdir(exist_ok=True)
    p.write_text(content, encoding="utf-8")


def walk_files(path):
    for root, _, files in os.walk(path):
        for name in files:
            yield os.path.join(root, name)


def get_output(*args):
    with subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE) as proc:
        output, _ = proc.communicate()
    return output.decode("utf-8")


def get_err(*args):
    with subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE) as proc:
        _, err = proc.communicate()
    return err.decode("utf-8")


def splitlines_no_ends(string: str) -> list[str]:
    return [s.strip() for s in string.splitlines()]


def changed_files(branch: str = "dev") -> list[str]:
    check_remotes = ["upstream", "origin"]
    check_remotes.extend(splitlines_no_ends(get_output("git", "remote")))
    for remote in check_remotes:
        command = ["git", "merge-base", f"refs/remotes/{remote}/{branch}", "HEAD"]
        try:
            merge_base = splitlines_no_ends(get_output(*command))[0]
            break
        # pylint: disable=bare-except
        except:  # noqa: E722
            pass
    else:
        raise ValueError("Git not configured")
    command = ["git", "diff", merge_base, "--name-only"]
    changed = splitlines_no_ends(get_output(*command))
    changed = [os.path.relpath(f, os.getcwd()) for f in changed]
    changed.sort()
    return changed


def get_header_dependencies(headers: list[str]) -> set[str]:
    """Find all cpp files that include the given header files (directly or transitively).

    Args:
        headers: List of header files that changed

    Returns:
        Set of cpp files that depend on the changed headers

    Note:
        This function requires ripgrep to be installed.
        It's only called when --from-ci is used, where ripgrep is guaranteed to be available.
    """
    dependent_files: set[str] = set()
    headers_to_check: set[str] = set(headers)
    checked_headers: set[str] = set()

    # First, find all headers that transitively include the changed headers
    while headers_to_check:
        current_header = headers_to_check.pop()
        if current_header in checked_headers:
            continue
        checked_headers.add(current_header)

        header_name = os.path.basename(current_header)
        patterns = [f'#include "{header_name}"', f'#include "{current_header}"']

        for pattern in patterns:
            # Search in header files
            cmd = ["rg", "-l", "--type-add", "header:*.h", "--type", "header", pattern]
            result = subprocess.run(
                cmd, capture_output=True, text=True, check=False, close_fds=False
            )
            if result.returncode == 0 and result.stdout:
                for file in result.stdout.strip().split("\n"):
                    if file and file not in checked_headers:
                        headers_to_check.add(file)

    # Now find all cpp files that include any of these headers
    all_headers = checked_headers

    # Use ripgrep for fast searching
    for header in all_headers:
        header_name = os.path.basename(header)

        # Search for #include statements with this header
        patterns = [f'#include "{header_name}"', f'#include "{header}"']

        for pattern in patterns:
            # Use ripgrep to find files containing the pattern
            cmd = ["rg", "-l", "--type", "cpp", pattern]
            result = subprocess.run(
                cmd, capture_output=True, text=True, check=False, close_fds=False
            )
            if result.returncode == 0 and result.stdout:
                for file in result.stdout.strip().split("\n"):
                    if file:
                        dependent_files.add(file)

    return dependent_files


def filter_changed(files: list[str], from_ci: bool = False) -> list[str]:
    """Filter files to only those that changed or depend on changed headers.

    Args:
        files: List of files to filter
        from_ci: If True, also checks for header dependencies (requires ripgrep)
    """
    changed: list[str] = changed_files()

    # Only check header dependencies when running from CI
    if from_ci:
        # Find changed header files
        changed_headers = [f for f in changed if f.endswith(".h")]

        # If headers changed, add files that include them
        if changed_headers:
            print(f"Changed headers detected: {', '.join(changed_headers)}")
            print("Finding dependent files (including transitive dependencies)...")
            dependent_files = get_header_dependencies(changed_headers)
            if dependent_files:
                print(
                    f"Found {len(dependent_files)} files that depend on changed headers"
                )
                # Add dependent files to the changed set
                changed = list(set(changed) | dependent_files)

    files = [f for f in files if f in changed]
    print("Changed files:")
    if not files:
        print("    No changed files!")
    for c in sorted(files):
        print(f"    {c}")
    return files


def filter_grep(files: list[str], value: str) -> list[str]:
    matched = []
    for file in files:
        with open(file, encoding="utf-8") as handle:
            contents = handle.read()
        if value in contents:
            matched.append(file)
    return matched


def git_ls_files(patterns: list[str] | None = None) -> dict[str, int]:
    command = ["git", "ls-files", "-s"]
    if patterns is not None:
        command.extend(patterns)
    with subprocess.Popen(command, stdout=subprocess.PIPE) as proc:
        output, _ = proc.communicate()
    lines = [x.split() for x in output.decode("utf-8").splitlines()]
    return {s[3].strip(): int(s[0]) for s in lines}


def load_idedata(environment):
    platformio_ini = Path(root_path) / "platformio.ini"
    temp_idedata = Path(temp_folder) / f"idedata-{environment}.json"
    changed = False
    if not platformio_ini.is_file() or not temp_idedata.is_file():
        changed = True
    elif platformio_ini.stat().st_mtime >= temp_idedata.stat().st_mtime:
        changed = True

    if "idf" in environment:
        # remove full sdkconfig when the defaults have changed so that it is regenerated
        default_sdkconfig = Path(root_path) / "sdkconfig.defaults"
        temp_sdkconfig = Path(temp_folder) / f"sdkconfig-{environment}"

        if not temp_sdkconfig.is_file():
            changed = True
        elif default_sdkconfig.stat().st_mtime >= temp_sdkconfig.stat().st_mtime:
            temp_sdkconfig.unlink()
            changed = True

    if not changed:
        return json.loads(temp_idedata.read_text())

    # ensure temp directory exists before running pio, as it writes sdkconfig to it
    Path(temp_folder).mkdir(exist_ok=True)

    if "nrf" in environment:
        from helpers_zephyr import load_idedata as zephyr_load_idedata

        data = zephyr_load_idedata(environment, temp_folder, platformio_ini)
    else:
        stdout = subprocess.check_output(
            ["pio", "run", "-t", "idedata", "-e", environment]
        )
        match = re.search(r'{\s*".*}', stdout.decode("utf-8"))
        data = json.loads(match.group())
    temp_idedata.write_text(json.dumps(data, indent=2) + "\n")
    return data


def get_binary(name: str, version: str) -> str:
    binary_file = f"{name}-{version}"
    try:
        result = subprocess.check_output([binary_file, "-version"])
        return binary_file
    except FileNotFoundError:
        pass
    binary_file = name
    try:
        result = subprocess.run(
            [binary_file, "-version"], text=True, capture_output=True, check=False
        )
        if result.returncode == 0 and (f"version {version}") in result.stdout:
            return binary_file
        raise FileNotFoundError(f"{name} not found")

    except FileNotFoundError:
        print(
            f"""
            Oops. It looks like {name} is not installed. It should be available under venv/bin
            and in PATH after running in turn:
              script/setup
              source venv/bin/activate.

            Please confirm you can run "{name} -version" or "{name}-{version} -version"
            in your terminal and install
            {name} (v{version}) if necessary.

            Note you can also upload your code as a pull request on GitHub and see the CI check
            output to apply {name}
            """
        )
        raise


def get_usable_cpu_count() -> int:
    """Return the number of CPUs that can be used for processes.

    On Python 3.13+ this is the number of CPUs that can be used for processes.
    On older Python versions this is the number of CPUs.
    """
    return (
        os.process_cpu_count() if hasattr(os, "process_cpu_count") else os.cpu_count()
    )
