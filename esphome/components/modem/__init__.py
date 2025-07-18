import logging

from esphome import automation, pins
import esphome.codegen as cg
from esphome.components.esp32 import add_idf_component, add_idf_sdkconfig_option

# from esphome.components.wifi import wifi_has_sta  # uncomment after PR #4091 is merged
import esphome.config_validation as cv
from esphome.const import (
    CONF_BAUD_RATE,
    CONF_DEBUG,
    CONF_DISABLED,
    CONF_ENABLE_ON_BOOT,
    CONF_ID,
    CONF_MODEL,
    CONF_ON_CONNECT,
    CONF_ON_DISCONNECT,
    CONF_PASSWORD,
    CONF_REBOOT_TIMEOUT,
    CONF_RX_PIN,
    CONF_SAFE_MODE,
    CONF_TRIGGER_ID,
    CONF_TX_PIN,
    CONF_USE_ADDRESS,
    CONF_USERNAME,
)
from esphome.core import coroutine_with_priority
import esphome.final_validate as fv

_LOGGER = logging.getLogger(__name__)

CODEOWNERS = ["@oarcher"]
DEPENDENCIES = ["esp32"]
AUTO_LOAD = ["network", "watchdog"]
CONFLICTS_WITH = ["captive_portal", "ethernet"]

CONF_MODEM = "modem"
CONF_MODEM_ID = "modem_id"
CONF_PIN_CODE = "pin_code"
CONF_APN = "apn"
CONF_DTR_PIN = "dtr_pin"
CONF_STATUS_PIN = "status_pin"
CONF_POWER_PIN = "power_pin"
CONF_TON_PULSE_DELAY = "ton_pulse_delay"
CONF_TON_DELAY = "ton_delay"
CONF_TOFF_PULSE_DELAY = "toff_pulse_delay"
CONF_TOFF_DELAY = "toff_delay"
CONF_INIT_AT = "init_at"
CONF_ON_NOT_RESPONDING = "on_not_responding"
CONF_ENABLE_CMUX = "enable_cmux"

MODEM_MODELS = ["BG96", "SIM800", "SIM7000", "SIM7600", "SIM7670", "GENERIC"]
MODEM_MODELS_POWER = {
    "BG96": {
        CONF_TON_PULSE_DELAY: 600,
        CONF_TON_DELAY: 4900,
        CONF_TOFF_PULSE_DELAY: 650,
        CONF_TOFF_DELAY: 2000,
    },
    "SIM800": {
        CONF_TON_PULSE_DELAY: 1300,
        CONF_TON_DELAY: 3000,
        CONF_TOFF_PULSE_DELAY: 200,
        CONF_TOFF_DELAY: 3000,
    },
    "SIM7000": {
        CONF_TON_PULSE_DELAY: 1100,
        CONF_TON_DELAY: 4500,
        CONF_TOFF_PULSE_DELAY: 1300,
        CONF_TOFF_DELAY: 1800,
    },
    "SIM7600": {
        CONF_TON_PULSE_DELAY: 500,
        CONF_TON_DELAY: 14000,
        CONF_TOFF_PULSE_DELAY: 2800,
        CONF_TOFF_DELAY: 25000,
    },
    "GENERIC": {
        CONF_TON_PULSE_DELAY: None,
        CONF_TON_DELAY: None,
        CONF_TOFF_PULSE_DELAY: None,
        CONF_TOFF_DELAY: None,
    },
}

MODEM_MODELS_POWER["SIM7670"] = MODEM_MODELS_POWER["SIM7600"]

KEY_MODEM_MODEL = "modem_model"
KEY_MODEM_CMUX = "modem_cmux"

modem_ns = cg.esphome_ns.namespace("modem")
ModemComponent = modem_ns.class_("ModemComponent", cg.Component)
ModemComponentState = modem_ns.enum("ModemComponentState")
ModemOnNotRespondingTrigger = modem_ns.class_(
    "ModemOnNotRespondingTrigger", automation.Trigger.template()
)
ModemOnConnectTrigger = modem_ns.class_(
    "ModemOnConnectTrigger", automation.Trigger.template()
)
ModemOnDisconnectTrigger = modem_ns.class_(
    "ModemOnDisconnectTrigger", automation.Trigger.template()
)

MODEM_COMPONENT_SCHEMA = cv.Schema(
    {cv.GenerateID(CONF_MODEM_ID): cv.use_id(ModemComponent)}
)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_ID): cv.declare_id(ModemComponent),
            cv.Required(CONF_TX_PIN): pins.internal_gpio_output_pin_schema,
            cv.Required(CONF_RX_PIN): pins.internal_gpio_output_pin_schema,
            cv.Optional(CONF_BAUD_RATE): cv.positive_int,
            cv.Required(CONF_MODEL): cv.one_of(*MODEM_MODELS, upper=True),
            cv.Required(CONF_APN): cv.string,
            cv.Optional(CONF_STATUS_PIN): pins.gpio_input_pin_schema,
            cv.Optional(CONF_POWER_PIN): pins.gpio_output_pin_schema,
            cv.Optional(CONF_TON_PULSE_DELAY): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_TON_DELAY): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_TOFF_PULSE_DELAY): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_TOFF_DELAY): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_PIN_CODE): cv.string_strict,
            cv.Optional(CONF_USE_ADDRESS): cv.string,
            cv.Optional(CONF_INIT_AT): cv.All(cv.ensure_list(cv.string)),
            cv.Optional(CONF_ENABLE_ON_BOOT, default=True): cv.boolean,
            cv.Optional(CONF_ENABLE_CMUX, default=False): cv.boolean,
            cv.Optional(CONF_DEBUG, default=False): cv.boolean,
            cv.Optional(
                CONF_REBOOT_TIMEOUT, default="10min"
            ): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_ON_NOT_RESPONDING): automation.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                        ModemOnNotRespondingTrigger
                    )
                }
            ),
            cv.Optional(CONF_ON_CONNECT): automation.validate_automation(
                {cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(ModemOnConnectTrigger)}
            ),
            cv.Optional(CONF_ON_DISCONNECT): automation.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(
                        ModemOnDisconnectTrigger
                    )
                }
            ),
        }
    )
    .extend(MODEM_COMPONENT_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA),
    cv.require_framework_version(
        esp_idf=cv.Version(4, 0, 0),  # 5.2.0 OK
    ),
)


def final_validate_platform(config):
    # To be called by platform components
    if modem_config := fv.full_config.get().get(CONF_MODEM, None):
        if not modem_config.get(CONF_ENABLE_CMUX, None):
            raise cv.Invalid(
                f"'{CONF_MODEM}' platform require '{CONF_ENABLE_CMUX}' to be 'true'."
            )
    else:
        raise cv.Invalid("'{CONF_MODEM}' component required.")
    return config


def _final_validate(config):
    full_config = fv.full_config.get()
    # Uncomment after PR #4091 is merged
    # if wifi_config := full_config.get(CONF_WIFI, None):
    #     if wifi_has_sta(wifi_config):
    #         raise cv.Invalid("Wi-Fi must be in AP-only mode when using a modem")
    if config.get(CONF_POWER_PIN, None):
        # if ton/off pulse delay options are defined, they overrides MODEM_MODELS_POWER
        if ton_pulse_delay := config.get(CONF_TON_PULSE_DELAY, None):
            MODEM_MODELS_POWER[config[CONF_MODEL]][CONF_TON_PULSE_DELAY] = (
                ton_pulse_delay
            )
        if ton_delay := config.get(CONF_TON_DELAY, None):
            MODEM_MODELS_POWER[config[CONF_MODEL]][CONF_TON_DELAY] = ton_delay
        if toff_pulse_delay := config.get(CONF_TOFF_PULSE_DELAY, None):
            MODEM_MODELS_POWER[config[CONF_MODEL]][CONF_TOFF_PULSE_DELAY] = (
                toff_pulse_delay
            )
        if toff_delay := config.get(CONF_TOFF_DELAY, None):
            MODEM_MODELS_POWER[config[CONF_MODEL]][CONF_TOFF_DELAY] = toff_delay

        if config[CONF_MODEL] not in MODEM_MODELS_POWER:
            # no defaults for ton/toff delay, so manual config is required
            if not (
                config.get(CONF_TON_PULSE_DELAY, None)
                and config.get(CONF_TON_DELAY, None)
                and config.get(CONF_TOFF_PULSE_DELAY, None)
                and config.get(CONF_TOFF_DELAY, None)
            ):
                raise cv.Invalid(
                    f"Modem model '{config[CONF_MODEL]}' has no known power specs. If using a power pin, '{CONF_TON_PULSE_DELAY}', '{CONF_TON_DELAY}', '{CONF_TOFF_PULSE_DELAY}', '{CONF_TOFF_DELAY}' options a required"
                )
        power_undef = [
            k for k, v in MODEM_MODELS_POWER[config[CONF_MODEL]].items() if not v
        ]
        if power_undef:
            raise cv.Invalid(
                f"Options {power_undef} must be defined for model {config[CONF_MODEL]}"
            )

    if conf_safe_mode := full_config.get(CONF_SAFE_MODE, None):
        if not conf_safe_mode.get(CONF_DISABLED, None):
            _LOGGER.warning(
                "%s may be explicitly disabled, since triggering it would prevent the %s component from being activated.",
                CONF_SAFE_MODE,
                CONF_MODEM,
            )


FINAL_VALIDATE_SCHEMA = _final_validate


@coroutine_with_priority(60.0)
async def to_code(config):
    add_idf_component(
        name="esp_modem",
        repo="https://github.com/espressif/esp-protocols.git",
        ref="modem-v1.4.0",
        path="components/esp_modem",
    )

    add_idf_sdkconfig_option("CONFIG_PPP", True)
    add_idf_sdkconfig_option("CONFIG_LWIP_PPP_SUPPORT", True)
    add_idf_sdkconfig_option("CONFIG_ESP_MODEM_CMUX_DELAY_AFTER_DLCI_SETUP", 500)
    add_idf_sdkconfig_option("CONFIG_PPP_SUPPORT", True)
    add_idf_sdkconfig_option(
        "CONFIG_ESP_MODEM_CMUX_USE_SHORT_PAYLOADS_ONLY", True
    )  # Slower but more reliable

    # If "Uart queue full" messages appear (e.g., with A7672), these config options might need adjustment
    # See: https://github.com/espressif/esp-protocols/issues/272#issuecomment-1558682967
    # add_idf_sdkconfig_option("CONFIG_ESP_MODEM_CMUX_DEFRAGMENT_PAYLOAD", True)
    # add_idf_sdkconfig_option("CONFIG_ESP_MODEM_USE_INFLATABLE_BUFFER_IF_NEEDED", True)
    # add_idf_sdkconfig_option("CONFIG_ESP_MODEM_CMUX_USE_SHORT_PAYLOADS_ONLY", False)

    cg.add_define("USE_MODEM")

    var = cg.new_Pvariable(config[CONF_ID])

    cg.add(var.set_reboot_timeout(config[CONF_REBOOT_TIMEOUT]))

    if use_address := config.get(CONF_USE_ADDRESS, None):
        cg.add(var.set_use_address(use_address))

    if username := config.get(CONF_USERNAME, None):
        cg.add(var.set_username(username))

    if password := config.get(CONF_PASSWORD, None):
        cg.add(var.set_password(password))

    if pin_code := config.get(CONF_PIN_CODE, None):
        cg.add(var.set_pin_code(pin_code))

    if config[CONF_ENABLE_ON_BOOT]:
        cg.add(var.enable())

    if config[CONF_ENABLE_CMUX]:
        cg.add(var.enable_cmux())

    if config[CONF_DEBUG]:
        add_idf_sdkconfig_option("CONFIG_LOG_MAXIMUM_LEVEL_VERBOSE", True)
        cg.add(var.enable_debug())

    if init_at := config.get(CONF_INIT_AT, None):
        for cmd in init_at:
            cg.add(var.add_init_at_command(cmd))

    modem_model = config[CONF_MODEL]
    cg.add(var.set_model(modem_model))

    if power_spec := MODEM_MODELS_POWER.get(modem_model, None):
        cg.add(var.set_power_ton_pulse_delay(power_spec[CONF_TON_PULSE_DELAY]))
        cg.add(var.set_power_ton_delay(power_spec[CONF_TON_DELAY]))
        cg.add(var.set_power_toff_pulse_delay(power_spec[CONF_TOFF_PULSE_DELAY]))
        cg.add(var.set_power_toff_delay(power_spec[CONF_TOFF_DELAY]))

    cg.add(var.set_apn(config[CONF_APN]))

    tx_pin = await cg.gpio_pin_expression(config[CONF_TX_PIN])
    cg.add(var.set_tx_pin(tx_pin))

    rx_pin = await cg.gpio_pin_expression(config[CONF_RX_PIN])
    cg.add(var.set_rx_pin(rx_pin))

    if baud_rate := config.get(CONF_BAUD_RATE, None):
        cg.add(var.set_baud_rate(baud_rate))

    if status_pin := config.get(CONF_STATUS_PIN, None):
        pin = await cg.gpio_pin_expression(status_pin)
        cg.add(var.set_status_pin(pin))

    if power_pin := config.get(CONF_POWER_PIN, None):
        pin = await cg.gpio_pin_expression(power_pin)
        cg.add(var.set_power_pin(pin))

    for conf in config.get(CONF_ON_NOT_RESPONDING, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [], conf)

    for conf in config.get(CONF_ON_CONNECT, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [], conf)

    for conf in config.get(CONF_ON_DISCONNECT, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(trigger, [], conf)

    await cg.register_component(var, config)
