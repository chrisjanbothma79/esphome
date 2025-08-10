from pathlib import Path
import platform
import subprocess

import pytest

pytestmark = pytest.mark.skipif(
    platform.system() == "Windows", reason="test not supported on Windows"
)


def _compile_and_run(code: str, tmp_path: Path, extra_flags=None) -> None:
    source = tmp_path / "test.cpp"
    source.write_text(code)
    binary = tmp_path / "test"
    helper_cpp = (
        Path(__file__).resolve().parents[2] / "esphome" / "core" / "helpers.cpp"
    )
    cmd = [
        "g++",
        "-std=c++20",
        "-O2",
        "-ffunction-sections",
        "-fdata-sections",
        "-DUSE_HOST",
        "-DUSE_ESPHOME_HOST_MAC_ADDRESS={0,0,0,0,0,0}",
        "-I",
        str(Path(__file__).resolve().parents[1] / ".."),
        "-I",
        str(Path(__file__).resolve().parents[2] / "esphome"),
        str(helper_cpp),
        str(source),
        "-o",
        str(binary),
    ]
    link_flags = []
    if platform.system() == "Linux":
        link_flags.append("-Wl,--gc-sections")
    elif platform.system() == "Darwin":
        link_flags.append("-Wl,-dead_strip")
    cmd.extend(link_flags)
    if extra_flags:
        cmd.extend(extra_flags)
    subprocess.check_call(cmd)
    subprocess.check_call([str(binary)])


def test_format_hex_pretty_dash(tmp_path: Path):
    _compile_and_run(
        """
#include \"esphome/core/helpers.h\"
#include <cassert>
int main() {
    uint8_t buf[] = {0x12, 0x34};
    return esphome::format_hex_pretty(buf, 2, '-', false) == "12-34" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_format_hex_pretty_default(tmp_path: Path):
    _compile_and_run(
        """
#include \"esphome/core/helpers.h\"
#include <cassert>
int main() {
    uint8_t buf[] = {1,2,3,4,5};
    return esphome::format_hex_pretty(buf, 5) == "01.02.03.04.05 (5)" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_format_hex_pretty_empty(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t *buf = nullptr;
    return esphome::format_hex_pretty(buf, 0).empty() ? 0 : 1;
}
""",
        tmp_path,
    )


def test_format_hex_pretty_nullptr(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t *buf = nullptr;
    return esphome::format_hex_pretty(buf, 5).empty() ? 0 : 1;
}
""",
        tmp_path,
    )


def test_one_byte_no_len(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t buf[] = {0xAB};
    return esphome::format_hex_pretty(buf, 1, '.', false) == "AB" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_one_byte_with_len(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t buf[] = {0x7F};
    return esphome::format_hex_pretty(buf, 1) == "7F" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_no_separator(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t buf[] = {0x12,0x34,0x56};
    return esphome::format_hex_pretty(buf, 3, '\0', false) == "123456" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_colon_separator(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t buf[] = {0xAA,0xBB,0xCC,0xDD,0xEE};
    return esphome::format_hex_pretty(buf, 5, ':') == "AA:BB:CC:DD:EE (5)" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_large_buffer(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
#include <vector>
int main() {
    std::vector<uint8_t> v(300, 0x01);
    auto s = esphome::format_hex_pretty(v, '.', false);
    return s.size() == (300*3-1) ? 0 : 1;
}
""",
        tmp_path,
    )


def test_uint16_vector(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
#include <vector>
int main() {
    std::vector<uint16_t> v = {0x1234,0xABCD};
    return esphome::format_hex_pretty(v) == "1234.ABCD" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_uint64_t(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint64_t val = 0x1122334455667788ULL;
    return esphome::format_hex_pretty(val, ':', false) == "11:22:33:44:55:66:77:88" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_vector_no_len(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
#include <vector>
int main() {
    std::vector<uint8_t> v = {0xDE,0xAD,0xBE,0xEF,0x01,0x02};
    return esphome::format_hex_pretty(v, '-', false) == "DE-AD-BE-EF-01-02" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_no_separator_overflow(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
#include <cassert>
int main() {
    uint8_t buf[] = {1, 2, 3, 4};
    auto s = esphome::format_hex_pretty(buf, 4, '\0', false);
    return (s == "01020304" && s.size() == 8) ? 0 : 1;
}
""",
        tmp_path,
        extra_flags=["-fsanitize=address"],
    )


def test_wrong_separator_bug(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t buf[] = {0xAA, 0xBB, 0xCC};
    return esphome::format_hex_pretty(buf, 3, '-', false) == "AA-BB-CC" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_uint16_separator_position(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
#include <vector>
int main() {
    std::vector<uint16_t> v = {0x1234, 0x5678};
    return esphome::format_hex_pretty(v, ':', false) == "1234:5678" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_no_sep_len1(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t buf[] = {0x5A};
    return esphome::format_hex_pretty(buf, 1, '\0', false) == "5A" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_no_sep_len2(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
int main() {
    uint8_t buf[] = {0xAA, 0xBB};
    return esphome::format_hex_pretty(buf, 2, '\0', false) == "AABB" ? 0 : 1;
}
""",
        tmp_path,
    )


def test_no_sep_vector_len4(tmp_path: Path):
    _compile_and_run(
        r"""
#include "esphome/core/helpers.h"
#include <vector>
int main() {
    std::vector<uint8_t> v = {0x01, 0x02, 0x03, 0x04};
    return esphome::format_hex_pretty(v, '\0', false) == "01020304" ? 0 : 1;
}
""",
        tmp_path,
    )
