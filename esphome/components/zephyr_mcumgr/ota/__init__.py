import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.ota import BASE_OTA_SCHEMA, ota_to_code
from esphome.const import (
    CONF_ID,
    CONF_NUM_ATTEMPTS,
    CONF_OTA,
    CONF_REBOOT_TIMEOUT,
    CONF_HARDWARE_UART,
    CONF_BLE,
    CONF_UDP,
    CONF_TRANSPORT,
)
from esphome.core import CORE, coroutine_with_priority
import esphome.final_validate as fv
from esphome.components.zephyr.const import BOOTLOADER_MCUBOOT, KEY_BOOTLOADER
from esphome.components.zephyr import (
    zephyr_add_prj_conf,
    zephyr_add_cdc_acm,
    zephyr_add_overlay,
    zephyr_add_mcuboot_conf,
)

AUTO_LOAD = ["zephyr_mcumgr"]

esphome = cg.esphome_ns.namespace("esphome")
ZephyrMcumgrOTAComponent = cg.esphome_ns.namespace("zephyr_mcumgr").class_(
    "OTAComponent", cg.Component
)

def _validate_transport(conf):
    if conf[CONF_TRANSPORT] in [CONF_BLE, CONF_UDP, CONF_HARDWARE_UART]:
        return conf
    raise cv.Invalid(
        f"At least one trasnport protocol has to be enabled. Set '{CONF_BLE}', '{CONF_UDP}' or '{CONF_HARDWARE_UART}'"
    )


UARTS = {
    "cdc": ("cdc_acm_uart0", 0),
    "cdc1": ("cdc_acm_uart1", 1),
    "uart0": ("uart0", -1),
    "uart1": ("uart1", -1),
}

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ZephyrMcumgrOTAComponent),
            cv.Optional(
                CONF_REBOOT_TIMEOUT, default="5min"
            ): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_NUM_ATTEMPTS, default="10"): cv.positive_not_null_int,
            cv.Optional(CONF_TRANSPORT, default=CONF_BLE): cv.one_of(CONF_BLE, CONF_UDP, CONF_HARDWARE_UART, lower=True),
            cv.Optional(CONF_HARDWARE_UART): cv.one_of(*UARTS, lower=True),
        }
    )
    .extend(BASE_OTA_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA),
    _validate_transport,
)


def _validate_mcumgr(config):
    fconf = fv.full_config.get()
    try:
        bootloader = fconf.get_config_for_path(["nrf52", KEY_BOOTLOADER])
        if bootloader != BOOTLOADER_MCUBOOT:
            raise cv.Invalid(f"'{bootloader}' bootloader does not support OTA")
    except KeyError:
        pass


KEY_ZEPHYR_BLE_SERVER = "zephyr_ble_server"
from esphome.components.zephyr_openthread.const import CONF_OPENTHREAD

def _validate_ble_server(config):
    if config[CONF_TRANSPORT] == CONF_BLE:
        has_ble_server = KEY_ZEPHYR_BLE_SERVER in fv.full_config.get()
        if not has_ble_server:
            raise cv.Invalid(
                f"'{KEY_ZEPHYR_BLE_SERVER}' component is required for BLE OTA"
            )

def _validate_udp_server(config):
    if config[CONF_TRANSPORT] == CONF_UDP:
        has_openthread = CONF_OPENTHREAD in fv.full_config.get()
        if not has_openthread:
            raise cv.Invalid(
                f"'{CONF_OPENTHREAD}' component is required for UDP OTA"
            )


def _final_validate(config):
    _validate_mcumgr(config)
    _validate_ble_server(config)
    _validate_udp_server(config)

FINAL_VALIDATE_SCHEMA = _final_validate


@coroutine_with_priority(50.0)
async def to_code(config):
    CORE.data[CONF_OTA] = {}

    var = cg.new_Pvariable(config[CONF_ID])
    await ota_to_code(var, config)
    cg.add_define("USE_OTA")

    await cg.register_component(var, config)

    # Set transport flags based on config
    if config[CONF_TRANSPORT] == CONF_UDP:
        cg.add(var.set_udp_transport(True))
    elif config[CONF_TRANSPORT] == CONF_HARDWARE_UART:
        cdc_id = UARTS[config[CONF_HARDWARE_UART]][1]
        if cdc_id >= 0: # Only set flag if using CDC ACM UART
             cg.add(var.set_cdc_transport(True))
        # else: No specific flag needed for non-CDC hardware UARTs yet
    # elif config[CONF_TRANSPORT] == CONF_BLE:
    #     # No specific flag needed for BLE transport management in C++ yet
    #     pass

    # mcumgr Kconfig settings based on transport
    if config[CONF_TRANSPORT] == CONF_BLE:
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_BT", True)
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_BT_REASSEMBLY", True)
        zephyr_add_prj_conf("NCS_SAMPLE_MCUMGR_BT_OTA_DFU_SPEEDUP", True)
    if config[CONF_TRANSPORT] == CONF_UDP:
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_UDP", True)
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_UDP_IPV6", True)
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_UDP_STACK_SIZE", 2048)
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_UDP_MTU", 1232)
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_UDP_AUTOMATIC_INIT", False)
    if config[CONF_TRANSPORT] == CONF_HARDWARE_UART:
        cdc_id = UARTS[config[CONF_HARDWARE_UART]][1]
        if cdc_id >= 0:
            zephyr_add_cdc_acm(config, cdc_id)
        zephyr_add_prj_conf("MCUMGR_TRANSPORT_UART", True)
        zephyr_add_prj_conf("BASE64", True)
        zephyr_add_prj_conf("CONSOLE", True)
        zephyr_add_overlay(
            f"""
/ {{
    chosen {{
        zephyr,uart-mcumgr = &{UARTS[config[CONF_HARDWARE_UART]][0]};
    }};
}};
"""
        )

    # mcumgr begin
    zephyr_add_prj_conf("NET_BUF", True)
    zephyr_add_prj_conf("ZCBOR", True)
    zephyr_add_prj_conf("MCUMGR", True)

    zephyr_add_prj_conf("MCUMGR_GRP_IMG", True)
    zephyr_add_prj_conf("MCUMGR_GRP_OS", True)
    zephyr_add_prj_conf("MCUMGR_GRP_OS_MCUMGR_PARAMS", True)

    zephyr_add_prj_conf("IMG_MANAGER", True)
    zephyr_add_prj_conf("STREAM_FLASH", True)
    zephyr_add_prj_conf("FLASH_MAP", True)
    zephyr_add_prj_conf("FLASH", True)

    zephyr_add_prj_conf("IMG_ERASE_PROGRESSIVELY", True)

    zephyr_add_prj_conf("BOOTLOADER_MCUBOOT", True)

    zephyr_add_prj_conf("MCUMGR_MGMT_NOTIFICATION_HOOKS", True)
    zephyr_add_prj_conf("MCUMGR_GRP_IMG_STATUS_HOOKS", True)
    zephyr_add_prj_conf("MCUMGR_GRP_IMG_UPLOAD_CHECK_HOOK", True)
    # MCUBoot config
    zephyr_add_mcuboot_conf("MAIN_STACK_SIZE", 20480)
    zephyr_add_mcuboot_conf("SYSTEM_WORKQUEUE_STACK_SIZE", 20480)
    zephyr_add_mcuboot_conf("PM_PARTITION_SIZE_MCUBOOT", "0x12000")
    zephyr_add_mcuboot_conf("SECURE_BOOT", False)

     ## MCUBoot configuration
    zephyr_add_mcuboot_conf("MULTITHREADING", True)
    zephyr_add_mcuboot_conf("FLASH", True)
