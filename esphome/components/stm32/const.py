import esphome.codegen as cg

KEY_BOARD = "board"
KEY_STM32 = "stm32"
KEY_UART_INSTANCES = "uart_instances"
KEY_GPIO_CLOCK_ENABLED = "gpio_clock_enabled"

CONF_BOARD_SERIES = "board_series"
CONF_AF = "af"

stm32_ns = cg.esphome_ns.namespace("stm32")
