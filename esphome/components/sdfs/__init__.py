from esphome import automation, pins
import esphome.codegen as cg
from esphome.components import spi
from esphome.components.esp32.const import KEY_ESP32, VARIANT_ESP32, VARIANT_ESP32S3
import esphome.config_validation as cv
from esphome.const import (
    # CONF_CLK_PIN,
    # CONF_CS_PIN,
    CONF_ID,
    CONF_PATH,
    # PLATFORM_ESP8266,
    CONF_TRIGGER_ID,
    CONF_TYPE,
    # KEY_CORE,
    # KEY_TARGET_FRAMEWORK,
    KEY_VARIANT,
    PLATFORM_ESP32,
    PLATFORM_ESP8266,
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
# CONF_INT_PIN = "int_pin"
CONF_MISO_PIN = "miso_pin"
CONF_MOSI_PIN = "mosi_pin"
CONF_MODE = "mode"
CONF_DATA = "data"
CONF_ON_STATE = "on_state"
CONF_STATE_NUM = "state"


sdfs_ns = cg.esphome_ns.namespace("sdfs")
BusWidth = sdfs_ns.enum("BusWidth")
BUS_WIDTH_OPTION = {
    "1bit": BusWidth.BUS_WIDTH_1BIT,
    "4bit": BusWidth.BUS_WIDTH_4BIT,
    "8bit": BusWidth.BUS_WIDTH_8BIT,
}

SdConnType = sdfs_ns.enum("SdConnType")
SD_CONN_TYPE = {
    "sdspi": SdConnType.SD_SPI,
    "sdmmc": SdConnType.SD_MMC,
}

SdDriverState = sdfs_ns.enum("SdDriverState")
SD_DRIVER_STATUS = {
    "no_init": SdDriverState.SD_SLOT_ST_NOTINIT,
    "init": SdDriverState.SD_SLOT_ST_INIT,
    "empty": SdDriverState.SD_SLOT_ST_EMPTY,
    "card": SdDriverState.SD_SLOT_ST_CARD,
    "mount": SdDriverState.SD_SLOT_ST_MOUNT,
}

# spi_ns = cg.esphome_ns.namespace("spi")
SdfsHost = sdfs_ns.class_("SdfsHost", cg.PollingComponent)
SpiDrv = sdfs_ns.class_("EsphomeSpiDrv", spi.SPIDevice)

SdfsWriteFile = sdfs_ns.class_("SdfsWriteFile", automation.Action)
# SdfsStatus = sdfs_ns.class_("SdfsStatus", automation.Condition)

SdIsStateCondition = sdfs_ns.class_(
    "SdIsStateCondition", automation.Condition.template()
)

ChangeSateteTrigger = sdfs_ns.class_(
    "ChangeSateteTrigger", automation.Trigger.template()
)


# -------------------------------------------------------------------------------------------
#
#  VALUDATION
#
def validate_inlist(value, array):
    if value not in array:
        options = ",".joun(array)
        raise cv.Invalid(f"Must me one of the  {options}  options")


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


# -------------------------------------------------------------------------------------------
#
#  SCHEMAS
#
BASE_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(SdfsHost),
            cv.Optional(CONF_PATH, default="/sdcard"): cv.string,
            cv.Optional(CONF_POWER_CTRL_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_CD_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_WP_PIN): pins.internal_gpio_output_pin_number,
            cv.Optional(CONF_ON_STATE): automation.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(ChangeSateteTrigger),
                },
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(cv.polling_component_schema("10s"))
)

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
            cv.Optional(CONF_BUS_WIDTH, default="1bit"): cv.enum(
                BUS_WIDTH_OPTION, lower=True
            ),
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

CONFIG_SCHEMA = cv.All(
    cv.typed_schema(
        {
            "sdspi": SDSPI_SCHEMA,
            "sdmmc": SDMMC_SCHEMA,
        },
    ),
    _validate,
)

WRITE_ACTION_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(SdfsHost),
        cv.Required(CONF_PATH): cv.templatable(cv.string_strict),
        # cv.Required(CONF_MODE): cv.templatable(validate_raw_data),
        cv.Optional(CONF_MODE, default="a"): cv.templatable(cv.one_of("a", "w", "t")),
        cv.Required(CONF_DATA): cv.templatable(validate_raw_data),
    }
)


# -------------------------------------------------------------------------------------------
#
#  CODE GENERATION
#
async def to_code(config):
    #
    #   Create required defines and add library
    #
    if CORE.using_esp_idf:
        cg.add_build_flag("-DCONFIG_FATFS_API_ENCODING_UTF_8")
        cg.add_build_flag("-DCONFIG_FATFS_MAX_LFN=254")
        # cg.add_build_flag("-DCONFIG_FATFS_LFN_STACK")
        cg.add_build_flag("-DCONFIG_FATFS_LFN_HEAP")

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
            cg.add_build_flag("-DSPI_DRIVER_SELECT=3")
            cg.add_define("SPI_DRIVER_SELECT", 3)
            cg.add_build_flag("-DUSE_BLOCK_DEVICE_INTERFACE=1")
            cg.add_define("USE_BLOCK_DEVICE_INTERFACE", 1)
            cg.add_build_flag("-DSD_CHIP_SELECT_MODE=2")
            cg.add_define("SD_CHIP_SELECT_MODE", 2)
            cg.add_build_flag("-DUSE_SD_CRC=1")
            cg.add_define("USE_SD_CRC", 1)
            cg.add_build_flag("-DFS_NO_GLOBALS")
        print("SDSPI ARDUINO")
    elif CORE.using_arduino and (config[CONF_TYPE] == "sdmmc"):
        cg.add_define("USE_SDMMC_MODE")
        cg.add_library("FS", None)
        cg.add_library("SD_MMC", None)
        print("SDMMC ARDUINO")
    else:
        raise cv.Invalid("Unsupported platform")

    #
    #   Create class and add values
    #
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_conn_type(cv.enum(SD_CONN_TYPE)(config[CONF_TYPE])))
    if CONF_PATH in config:
        cg.add(var.set_path(config[CONF_PATH]))

    if CONF_POWER_CTRL_PIN in config:
        # cg.add(var.set_pw_ctrl_pin(config[CONF_POWER_CTRL_PIN]))
        pin = await cg.gpio_pin_expression(config[CONF_POWER_CTRL_PIN])
        cg.add(var.load_pw_ctrl_pin(pin))
    if CONF_CD_PIN in config:
        # cg.add(var.set_cd_pin(config[CONF_CD_PIN]))
        pin = await cg.gpio_pin_expression(config[CONF_CD_PIN])
        cg.add(var.load_cd_pin(pin))
    if CONF_WP_PIN in config:
        # cg.add(var.set_wp_pin(config[CONF_WP_PIN]))
        pin = await cg.gpio_pin_expression(config[CONF_WP_PIN])
        cg.add(var.load_wp_pin(pin))

    if config[CONF_TYPE] == "sdspi":
        await spi.register_spi_device(var, config)

    elif config[CONF_TYPE] == "sdmmc":
        if CONF_WP_PIN in config:
            cg.add(var.set_bus_slot(config[CONF_BUS_SLOT]))
        if CONF_SCLK_PIN in config:
            cg.add(var.set_clk_pin(config[CONF_SCLK_PIN]))

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

    #
    #   Register Triggers
    #
    for conf in config.get(CONF_ON_STATE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [(SdDriverState, "x")], conf)


# -------------------------------------------------------------------------------------------
#
#    AUTOMATION
#
@automation.register_action("sdfs.write_file", SdfsWriteFile, WRITE_ACTION_SCHEMA)
async def sdfs_write_file_to_code(config, action_id, template_arg, args):
    parent = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, parent)
    path_ = await cg.templatable(config[CONF_PATH], args, cg.std_string)
    # mode_  = await cg.get_variable(config[CONF_MODE])
    mode_ = await cg.templatable(config[CONF_MODE], args, cg.uint8)
    data_ = await cg.templatable(
        config[CONF_DATA], args, cg.std_vector.template(cg.uint8)
    )
    cg.add(var.set_path(path_))
    cg.add(var.set_mode(mode_))
    cg.add(var.set_data(data_))
    return var


# -------------------------------------------------------------------------------------------
#
#   CONDITION
#
@automation.register_condition(
    "sdfs.is_state",
    SdIsStateCondition,
    automation.maybe_simple_id(
        {
            cv.Required(CONF_ID): cv.use_id(SdfsHost),
            cv.Optional(CONF_STATE_NUM, default=4): cv.templatable(
                cv.int_range(min=0, max=4)
            ),
        }
    ),
)
async def sd_is_state_to_code(config, condition_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(condition_id, template_arg, paren)
    templ = await cg.templatable(config[CONF_STATE_NUM], args, cg.int_)
    cg.add(var.set_state(templ))
    return var
