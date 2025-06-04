from esphome import pins
import esphome.codegen as cg
from esphome.components import spi
from esphome.components.esp32.const import KEY_ESP32, VARIANT_ESP32, VARIANT_ESP32S3
import esphome.config_validation as cv
from esphome.const import (
    # CONF_CLK_PIN,
    # CONF_CS_PIN,
    CONF_ID,
    CONF_PATH,
    CONF_TYPE,
    # KEY_CORE,
    # KEY_TARGET_FRAMEWORK,
    KEY_VARIANT,
    PLATFORM_ESP32,
    PLATFORM_ESP8266,
    # PLATFORM_ESP8266,
)
from esphome.core import CORE

CONF_BUS_WIDTH = "bus_width"
CONF_SCLK_PIN = "clk_pin"
CONF_BUS_SLOT = "bus_slot"
CONF_CMD_PIN = "cmd_pin"
CONF_DATA0_PIN = "data0_pin"
CONF_DATA1_PIN = "data1_pin"
CONF_DATA2_PIN = "data2_pin"
CONF_DATA3_PIN = "data3_pin"
CONF_DATA4_PIN = "data4_pin"
CONF_DATA5_PIN = "data5_pin"
CONF_DATA6_PIN = "data6_pin"
CONF_DATA7_PIN = "data7_pin"
CONF_POWER_CTRL_PIN = "power_ctrl_pin"
CONF_CD_PIN = "cd_pin"
CONF_WP_PIN = "wp_pin"
CONF_INT_PIN = "int_pin"
CONF_MISO_PIN = "miso_pin"
CONF_MOSI_PIN = "mosi_pin"

sdfs_ns = cg.esphome_ns.namespace("sdfs")
BusWidth = sdfs_ns.enum("BusWidth")
BUS_WIDTH_OPTION = {
    "1bit": BusWidth.BUS_WIDTH_1BIT,
    "4bit": BusWidth.BUS_WIDTH_4BIT,
    "8bit": BusWidth.BUS_WIDTH_8BIT,
}

SdConnType = sdfs_ns.enum("SdConnType")
SD_CONN_TYPE = {
    "sdspi": BusWidth.SD_SPI,
    "sdmmc": BusWidth.SD_MMC,
}

# spi_ns = cg.esphome_ns.namespace("spi")
SdmmcHost = sdfs_ns.class_("SdmmcHost", cg.Component)
SpiDrv = sdfs_ns.class_("EsphomeSpiDrv", spi.SPIDevice)


def validate_raw_data(value):
    if isinstance(value, str):
        return value.encode("utf-8")
    if isinstance(value, list):
        return cv.Schema([cv.hex_uint8_t])(value)
    raise cv.Invalid(
        "data must either be a string wrapped in quotes or a list of bytes"
    )


def _validate(config):
    platform = CORE.target_platform
    # CORE.data[KEY_CORE][KEY_TARGET_PLATFORM]
    if platform == PLATFORM_ESP32:
        variant = CORE.data[KEY_ESP32][KEY_VARIANT]
    elif platform == PLATFORM_ESP8266:
        variant = PLATFORM_ESP8266

    if config[CONF_TYPE] == "sdspi":
        pass
    elif config[CONF_TYPE] == "sdmmc" and platform != PLATFORM_ESP32:
        raise cv.Invalid(
            "SDMMC host adapter available only on {PLATFORM_ESP32} platform with {VARIANT_ESP32} or {VARIANT_ESP32S3} chip"
        )
    else:
        if variant not in [VARIANT_ESP32, VARIANT_ESP32S3]:
            raise cv.Invalid(
                "SDMMC host adapter available only on {VARIANT_ESP32} or {VARIANT_ESP32S3} chips"
            )

        if config[CONF_BUS_WIDTH] == "8bit":
            if variant != VARIANT_ESP32:
                raise cv.Invalid(
                    "Useing 8bit bus available only in SLOT_0 on ESP32 chip."
                )
            elif config[CONF_BUS_SLOT] != 0:
                raise cv.Invalid("8bit bus with available only on SPI_0 ")

            if (
                config[CONF_DATA0_PIN] not in config
                or config[CONF_DATA1_PIN] not in config
                or config[CONF_DATA2_PIN] not in config
                or config[CONF_DATA3_PIN] not in config
                or config[CONF_DATA4_PIN] not in config
                or config[CONF_DATA5_PIN] not in config
                or config[CONF_DATA6_PIN] not in config
                or config[CONF_DATA7_PIN] not in config
            ):
                raise cv.Invalid(
                    f"With 8bit bus definition of {CONF_DATA4_PIN}, {CONF_DATA5_PIN}, {CONF_DATA6_PIN}, {CONF_DATA7_PIN} required."
                )

        elif config[CONF_BUS_WIDTH] == "4bit":
            if (
                config[CONF_DATA0_PIN] not in config
                or config[CONF_DATA1_PIN] not in config
                or config[CONF_DATA2_PIN] not in config
                or config[CONF_DATA3_PIN] not in config
            ):
                raise cv.Invalid(
                    f"With 8bit bus definition of {CONF_DATA0_PIN}, {CONF_DATA1_PIN}, {CONF_DATA2_PIN}, {CONF_DATA3_PIN} required."
                )
    return config


BASE_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SdmmcHost),
        cv.Optional(CONF_PATH, default="/sdcard"): cv.string,
        cv.Optional(CONF_CD_PIN): pins.internal_gpio_output_pin_number,
        cv.Optional(CONF_WP_PIN): pins.internal_gpio_output_pin_number,
        cv.Optional(CONF_BUS_WIDTH, default="1bit"): cv.enum(
            BUS_WIDTH_OPTION, lower=True
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

SDMMC_SCHEMA = BASE_SCHEMA.extend(
    cv.Schema(
        {
            cv.Optional(CONF_BUS_SLOT, default=1): cv.int_range(min=0, max=1),
            cv.Required(CONF_CMD_PIN): pins.internal_gpio_output_pin_number,
            cv.Required(CONF_SCLK_PIN): pins.internal_gpio_output_pin_number,
            cv.Required(CONF_DATA0_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_DATA1_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_DATA2_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_DATA3_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_DATA4_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_DATA5_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_DATA6_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_DATA7_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_POWER_CTRL_PIN): pins.internal_gpio_output_pin_number,
        }
    ),
)

SDSPI_SCHEMA = (
    cv.Schema(
        {
            cv.Optional(CONF_BUS_SLOT, default=2): cv.int_range(min=0, max=3),
        }
    )
    .extend(BASE_SCHEMA)
    .extend(spi.spi_device_schema(cs_pin_required=True, default_mode="MODE0"))
)

# cv.only_with_arduino,


# IDF_SPI_SCHEMA = BASE_SCHEMA.extend(
#     cv.Schema(
#         {
#             cv.Optional(CONF_BUS_SLOT, default=2): cv.int_range(
#                 min=0, max=3
#             ),  # TODO:  rename to CONF_SPI_MODE
#             cv.Required(CONF_SCLK_PIN): pins.internal_gpio_output_pin_number,
#             cv.Required(
#                 CONF_CS_PIN
#             ): pins.internal_gpio_output_pin_number,  # pins.gpio_output_pin_schema
#             cv.Required(CONF_MISO_PIN): pins.internal_gpio_output_pin_number,
#             cv.Required(CONF_MOSI_PIN): pins.internal_gpio_output_pin_number,
#             cv.Optional(CONF_INT_PIN): pins.internal_gpio_output_pin_number,
#         }
#     )
# )


# def select_spi():
#     if CORE.using_arduino:
#         return ARDUINO_SPI_SCHEMA
#     else:
#         # return IDF_SPI_SCHEMA
#         return ARDUINO_SPI_SCHEMA


# SDSPI_SCHEMA = cv.Schema(select_spi())

CONFIG_SCHEMA = cv.All(
    cv.typed_schema(
        {
            "sdspi": SDSPI_SCHEMA,
            "sdmmc": SDMMC_SCHEMA,
        },
    ),
    _validate,
)


async def to_code(config):
    if CORE.using_esp_idf and (config[CONF_TYPE] == "sdspi"):
        cg.add_define("USE_SDSPI_MODE")
        print("SDSPI ESP")
    elif CORE.using_esp_idf and (config[CONF_TYPE] == "sdmmc"):
        cg.add_define("USE_SDMMC_MODE")
        print("SDMMC ESP")
    elif CORE.using_arduino and (config[CONF_TYPE] == "sdspi"):
        cg.add_define("USE_SDSPI_MODE")
        if CORE.target_platform == PLATFORM_ESP8266:
            cg.add_library("ESP8266SdFat", None)
            # cg.add_library("SdFat", "2.3.50")
            # cg.add_library("FS", None)
            # cg.add_library("SDFS", None)
            # cg.add_library("SD", None)

            cg.add_build_flag("-DSPI_DRIVER_SELECT=3")
            cg.add_define("SPI_DRIVER_SELECT", 3)

            cg.add_build_flag("-DUSE_BLOCK_DEVICE_INTERFACE=1")
            cg.add_define("USE_BLOCK_DEVICE_INTERFACE", 1)

            cg.add_build_flag("-DSD_CHIP_SELECT_MODE=2")
            cg.add_define("SD_CHIP_SELECT_MODE", 2)

            # cg.add_build_flag("-DENABLE_DEDICATED_SPI=1")
            # cg.add_build_flag("-DSD_USE_CUSTOM_SPI")

            # cg.add_build_flag("-DFS_NO_GLOBALS")
            # cg.add_define("FS_NO_GLOBALS")
            # # SPI_DRIVER_SELECT
            # cg.add_define("ENABLE_DEDICATED_SPI",1)

        print("SDSPI ARDUINO")
    elif CORE.using_arduino and (config[CONF_TYPE] == "sdmmc"):
        cg.add_define("USE_SDMMC_MODE")
        cg.add_library("FS", None)
        cg.add_library("SD_MMC", None)
        print("SDMMC ARDUINO")
    else:
        raise cv.Invalid("Unsupported platform")

    # if CORE.using_arduino and (config[CONF_TYPE] == "sdspi"):
    #     cg.add_define("USE_ARDUINO_SPI_FS")
    # cg.add_platformio_option("extra_scripts", ["pre:build_pio.py"])
    # cg.add_platformio_option("lib_ldf_mode", "chain+")  #deep+  chain+
    # cg.add_platformio_option("lib_extra_dirs", "src/esphome/components/sdfs")
    # cg.add_library("FS", None)s
    # cg.add_library("SD", None)
    # cg.add_library("SPI", None)
    # cg.add_library("SdFat", None)
    #       lib_extra_di  rs = lib/MyLibFolder/ExternalLibFolder
    #       lib_ldf_mode = chain+

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_conn_type(cv.enum(SD_CONN_TYPE)(config[CONF_TYPE])))

    if CONF_CD_PIN in config:
        cg.add(var.set_cd_pin(config[CONF_CD_PIN]))
    if CONF_WP_PIN in config:
        cg.add(var.set_wp_pin(config[CONF_WP_PIN]))
    if CONF_PATH in config:
        cg.add(var.set_path(config[CONF_PATH]))
    if CONF_POWER_CTRL_PIN in config:
        cg.add(var.set_pw_ctrl_pin(config[CONF_POWER_CTRL_PIN]))

    if config[CONF_TYPE] == "sdspi":
        await spi.register_spi_device(var, config)
    elif config[CONF_TYPE] == "sdmmc":
        cg.add(var.set_bus_slot(config[CONF_BUS_SLOT]))
        if CONF_SCLK_PIN in config:
            cg.add(var.set_clk_pin(config[CONF_SCLK_PIN]))
        cg.add(var.set_path(config[CONF_PATH]))

        cg.add(var.set_cmd_pin(config[CONF_CMD_PIN]))
        cg.add(var.set_data0_pin(config[CONF_DATA0_PIN]))
        cg.add(var.set_bus_width(config[CONF_BUS_WIDTH]))

        if (config[CONF_BUS_WIDTH] == "4bit") or (config[CONF_BUS_WIDTH] == "8bit"):
            cg.add(var.set_data1_pin(config[CONF_DATA1_PIN]))
            cg.add(var.set_data2_pin(config[CONF_DATA2_PIN]))
            cg.add(var.set_data3_pin(config[CONF_DATA3_PIN]))

        elif config[CONF_BUS_WIDTH] == "8bit":
            cg.add(var.set_data4_pin(config[CONF_DATA4_PIN]))
            cg.add(var.set_data5_pin(config[CONF_DATA5_PIN]))
            cg.add(var.set_data6_pin(config[CONF_DATA6_PIN]))
            cg.add(var.set_data7_pin(config[CONF_DATA7_PIN]))
