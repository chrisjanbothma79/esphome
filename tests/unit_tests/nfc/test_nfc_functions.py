from pathlib import Path
import subprocess

from hypothesis import given, settings, strategies as st
import pytest

ROOT = Path(__file__).resolve().parents[3]
SRC = ROOT / "tests" / "unit_tests" / "nfc" / "nfc_test_main.cpp"
NFC_CPP = ROOT / "esphome" / "components" / "nfc" / "nfc.cpp"


@pytest.fixture(scope="module")
def nfc_binary(tmp_path_factory):
    build_dir = tmp_path_factory.mktemp("nfc_build")
    binary = build_dir / "nfc_test"
    subprocess.check_call(
        [
            "g++",
            str(SRC),
            str(NFC_CPP),
            "-I",
            str(ROOT),
            "-DUSE_HOST",
            "-std=c++20",
            "-Wall",
            "-Wextra",
            "-o",
            str(binary),
        ]
    )
    return binary


def run(binary, *args):
    out = subprocess.check_output([str(binary), *args])
    return out.decode().strip()


@pytest.mark.parametrize(
    "length,expected",
    [
        (0, "99"),
        (4, "0"),
        (7, "2"),
        (10, "2"),
        (8, "99"),
    ],
)
def test_guess_tag_type(nfc_binary, length, expected):
    assert run(nfc_binary, "guess", str(length)) == expected


@pytest.mark.parametrize(
    "data,expected",
    [
        (["00", "00", "03"], "2"),
        (["00", "ff"], "-2"),
        (["00"] * 4, "-1"),
        (["03", "aa"], "0"),
        (["00"] * 4 + ["03"], "4"),
    ],
)
def test_get_mifare_classic_ndef_start_index(nfc_binary, data, expected):
    assert run(nfc_binary, "start_index", *data) == expected


@pytest.mark.parametrize(
    "hexbytes,exp",
    [
        (["03", "fe"] + ["00"] * 254, "ok 254 2"),
        (["03", "ff", "00", "ff"] + ["00"] * 255, "ok 255 4"),
    ],
)
def test_max_lengths(nfc_binary, hexbytes, exp):
    assert run(nfc_binary, "decode", *hexbytes) == exp


@pytest.mark.parametrize(
    "hexbytes,exp",
    [
        (["03", "04", "00"], "fail"),
        (["03", "ff", "00"], "fail"),
    ],
)
def test_decode_short_buffers(nfc_binary, hexbytes, exp):
    assert run(nfc_binary, "decode", *hexbytes) == exp


@pytest.mark.parametrize(
    "hexbytes,exp",
    [
        (["00", "ab", "03"], "-2"),
        (["00"] * 16, "-1"),
        (["00"] * 15 + ["03"], "15"),
    ],
)
def test_get_mifare_classic_ndef_start_index_additional(nfc_binary, hexbytes, exp):
    assert run(nfc_binary, "start_index", *hexbytes) == exp


def test_buffer_size(nfc_binary):
    assert run(nfc_binary, "size", "300") == "320"


def test_decode_with_terminator(nfc_binary):
    hexbytes = ["03", "02", "aa", "bb", "fe"]
    assert run(nfc_binary, "decode", *hexbytes) == "ok 2 2"


@settings(max_examples=1000)
@given(st.lists(st.integers(min_value=0, max_value=255), min_size=16, max_size=32))
def test_fuzz_decode(nfc_binary, buf):
    res = run(nfc_binary, "decode", *[f"{b:02x}" for b in buf])
    assert res.startswith("ok") or res == "fail"


def test_round_trip(nfc_binary):
    for n in range(1, 33):
        hexbytes = ["03", f"{n:02x}", "00", "00"] + ["00"] * n
        assert run(nfc_binary, "decode", *hexbytes) == f"ok {n} 2"

    # Long TLV round-trip
    long_n = 300
    hexbytes = [
        "03",
        "ff",
        f"{(long_n >> 8) & 0xFF:02x}",
        f"{long_n & 0xFF:02x}",
        "00",
        "00",
    ] + ["00"] * long_n
    assert run(nfc_binary, "decode", *hexbytes) == f"ok {long_n} 4"
