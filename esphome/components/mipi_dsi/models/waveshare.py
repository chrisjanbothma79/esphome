from . import DriverChip

DriverChip(
    "WAVESHARE-P4-NANO-10.1",
    height=1280,
    width=800,
    hsync_back_porch=20,
    hsync_pulse_width=20,
    hsync_front_porch=40,
    vsync_back_porch=12,
    vsync_pulse_width=4,
    vsync_front_porch=30,
    data_rate="80MHZ",
    reset_pin=27,
    init_sequence=[[0xB0, 0x01], [0xB1, 0x01], [0xB2, 0x01]],
)
models = {}
