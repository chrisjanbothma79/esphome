from esphome.components.mipi import DriverChip
from esphome.config_validation import UNDEFINED

wave_4_3 = DriverChip(
    "ESP32-S3-TOUCH-LCD-4.3",
    swap_xy=UNDEFINED,
    initsequence=(),
    width=800,
    height=480,
    pclk_frequency="16MHz",
    reset_pin={"ch422g": None, "number": 3},
    enable_pin={"ch422g": None, "number": 2},
    de_pin=5,
    hsync_pin={"number": 46, "ignore_strapping_warning": True},
    vsync_pin={"number": 3, "ignore_strapping_warning": True},
    pclk_pin=7,
    pclk_inverted=True,
    hsync_front_porch=210,
    hsync_pulse_width=30,
    hsync_back_porch=30,
    vsync_front_porch=4,
    vsync_pulse_width=4,
    vsync_back_porch=4,
    data_pins={
        "red": [1, 2, 42, 41, 40],
        "green": [39, 0, 45, 48, 47, 21],
        "blue": [14, 38, 18, 17, 10],
    },
)
wave_4_3.extend(
    "ESP32-S3-TOUCH-LCD-7-800X480",
    enable_pin=[{"ch422g": None, "number": 2}, {"ch422g": None, "number": 6}],
    hsync_back_porch=8,
    hsync_front_porch=8,
    hsync_pulse_width=4,
    vsync_back_porch=16,
    vsync_front_porch=16,
    vsync_pulse_width=4,
)
