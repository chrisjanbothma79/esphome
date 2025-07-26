from esphome.components.mipi_rgb.models.st7701s import st7701s

st7701s.extend(
    "GUITION-4848S040",
    width=480,
    height=480,
    data_rate="2MHz",
    cs_pin=39,
    de_pin=18,
    hsync_pin=16,
    vsync_pin=17,
    pclk_pin=21,
    pclk_frequency="12MHz",
    hsync_pulse_width=8,
    hsync_front_porch=10,
    hsync_back_porch=20,
    vsync_pulse_width=8,
    vsync_front_porch=10,
    vsync_back_porch=10,
    init_sequence=((0xCD, 0x00),),
    data_pins={
        "red": [11, 12, 13, 14, 0],
        "green": [8, 20, 3, 46, 9, 10],
        "blue": [4, 5, 6, 7, 15],
    },
)
