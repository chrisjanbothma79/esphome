import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components.zephyr import (
    zephyr_add_prj_conf,
    zephyr_add_overlay,
    zephyr_add_mcuboot_conf,
    zephyr_add_mcuboot_overlay,
)
from esphome.const import CONF_ID, CONF_ENABLE_IPV6
from esphome.core import CORE, coroutine_with_priority

from .const import (
    CONF_CHANNEL,
    CONF_NETWORK_KEY,
    CONF_NETWORK_NAME,
    CONF_PANID,
    CONF_RADIO_TX_POWER,
    CONF_XPANID,
    CONF_PSKC,
    CONF_FORCE_DATASET,
    CONF_SHELL,
    DEFAULT_CHANNEL,
    DEFAULT_NETWORK_KEY,
    DEFAULT_NETWORK_NAME,
    DEFAULT_PANID,
    DEFAULT_RADIO_TX_POWER,
    DEFAULT_XPANID,
    DEFAULT_PSKC,
    DEFAULT_FORCE_DATASET,
    DEFAULT_SHELL,
    zephyr_openthread_ns,
)

from . import config_validation as ot_cv

CODEOWNERS = ["@felipejfc"]
DEPENDENCIES = ["zephyr", "nrf52"]
AUTO_LOAD = ["mdns", "network"]

OpenThreadZephyr = zephyr_openthread_ns.class_("OpenThreadZephyr", cg.Component)
OpenThreadDNSComponent = zephyr_openthread_ns.class_(
    "OpenThreadDNSComponent", cg.Component
)


# Create a custom validator for hex strings with a specific length
def hex_string_length(length):
    def validator(value):
        value = cv.string_strict(value)
        if not all(c in "0123456789ABCDEFabcdef" for c in value):
            raise cv.Invalid(f"Invalid hex string: {value}")
        if len(value) != length:
            raise cv.Invalid(f"Hex string must be exactly {length} characters long")
        return value

    return validator


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(OpenThreadZephyr),
        cv.Optional(CONF_CHANNEL, default=DEFAULT_CHANNEL): cv.int_range(
            min=11, max=26
        ),
        cv.Optional(CONF_PANID, default=DEFAULT_PANID): cv.hex_uint16_t,
        cv.Optional(CONF_NETWORK_NAME, default=DEFAULT_NETWORK_NAME): cv.string,
        cv.Optional(CONF_XPANID, default=DEFAULT_XPANID): hex_string_length(16),
        cv.Optional(CONF_NETWORK_KEY, default=DEFAULT_NETWORK_KEY): hex_string_length(
            32
        ),
        cv.Optional(CONF_PSKC, default=DEFAULT_PSKC): hex_string_length(32),
        cv.Optional(CONF_RADIO_TX_POWER, default=DEFAULT_RADIO_TX_POWER): cv.int_range(
            min=-20, max=20
        ),
        cv.Optional(CONF_FORCE_DATASET, default=DEFAULT_FORCE_DATASET): cv.boolean,
        cv.Optional(CONF_SHELL, default=DEFAULT_SHELL): cv.boolean,
        cv.Optional(CONF_ENABLE_IPV6, default=True): ot_cv.require_framework_version(
            cv.Version(1, 0, 0)
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


@coroutine_with_priority(1000)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # Configure OpenThread parameters
    cg.add(var.set_channel(config[CONF_CHANNEL]))
    cg.add(var.set_panid(config[CONF_PANID]))
    cg.add(var.set_network_name(config[CONF_NETWORK_NAME]))
    cg.add(var.set_xpanid(config[CONF_XPANID]))
    cg.add(var.set_network_key(config[CONF_NETWORK_KEY]))
    cg.add(var.set_pskc(config[CONF_PSKC]))
    cg.add(var.set_radio_tx_power(config[CONF_RADIO_TX_POWER]))
    cg.add(var.set_force_dataset(config[CONF_FORCE_DATASET]))

    # Get mDNS component reference if available
    if "mdns" in CORE.config:
        mdns = await cg.get_variable(CORE.config["mdns"]["id"])
        cg.add(var.set_mdns(mdns))

    # Configure Zephyr for OpenThread
    # Enable OpenThread
    zephyr_add_prj_conf("NET_L2_OPENTHREAD", True)
    zephyr_add_prj_conf("INIT_STACKS", True)
    zephyr_add_prj_conf("OPENTHREAD_MTD", True)

    # Nordic library configuration
    zephyr_add_prj_conf("OPENTHREAD_NORDIC_LIBRARY", True)
    zephyr_add_prj_conf("OPENTHREAD_NORDIC_LIBRARY_MTD", True)

    # Shell configuration - make it configurable
    shell_enabled = config[CONF_SHELL]
    zephyr_add_prj_conf("OPENTHREAD_NORDIC_LIBRARY_FTD", shell_enabled)
    zephyr_add_prj_conf("OPENTHREAD_SHELL", shell_enabled)
    zephyr_add_prj_conf("OPENTHREAD_PING_SENDER", shell_enabled)
    zephyr_add_prj_conf("SHELL", shell_enabled)
    zephyr_add_prj_conf("SHELL_BACKEND_SERIAL", shell_enabled)

    # CLI settings - ensure CLI libraries are properly included
    if shell_enabled:
        zephyr_add_prj_conf("OPENTHREAD_CLI_MAX_LINE_LENGTH", 128)

    # Network stack with IPv6 support
    zephyr_add_prj_conf("NETWORKING", True)
    zephyr_add_prj_conf("NET_IPV6", True)
    zephyr_add_prj_conf("NET_IPV4", True)
    zephyr_add_prj_conf("NET_TCP", True)
    zephyr_add_prj_conf("NET_UDP", True)

    zephyr_add_prj_conf("OPENTHREAD_SLAAC", True)
    zephyr_add_prj_conf("NET_IF_UNICAST_IPV6_ADDR_COUNT", 6)
    zephyr_add_prj_conf("NET_SOCKETS", True)
    zephyr_add_prj_conf("NET_SOCKETS_POSIX_NAMES", True)

    # TCP configuration - disable RFC6528 ISN generation to avoid mbedtls_md5 dependency
    zephyr_add_prj_conf("NET_TCP_ISN_RFC6528", False)

    # SRP (Service Registration Protocol) support
    zephyr_add_prj_conf("OPENTHREAD_SRP_CLIENT", True)

    # Enable OpenThread DNS client and upstream query
    zephyr_add_prj_conf("CONFIG_OPENTHREAD_DNS_CLIENT", True)
    zephyr_add_prj_conf("CONFIG_OPENTHREAD_DNS_UPSTREAM_QUERY", True)

    # Enable hostname
    zephyr_add_prj_conf("NET_HOSTNAME_ENABLE", True)

    # Configure DNS resolver settings for Zephyr
    zephyr_add_prj_conf("DNS_RESOLVER", True)
    zephyr_add_prj_conf("DNS_SD", True)
    zephyr_add_prj_conf("DNS_SERVER_IP_ADDRESSES", False)
    zephyr_add_prj_conf("DNS_RESOLVER_MAX_SERVERS", 2)
    zephyr_add_prj_conf("DNS_RESOLVER_ADDITIONAL_BUF_CTR", 2)
    zephyr_add_prj_conf("DNS_RESOLVER_ADDITIONAL_QUERIES", 2)

    # IEEE 802.15.4 driver
    zephyr_add_prj_conf("IEEE802154", True)
    zephyr_add_prj_conf("IEEE802154_NRF5", True)
    zephyr_add_prj_conf("IEEE802154_NRF5_RX_STACK_SIZE", 800)

    # Stack sizes
    zephyr_add_prj_conf("MAIN_STACK_SIZE", 10240)
    
    # OpenThread settings
    zephyr_add_prj_conf("OPENTHREAD_THREAD_STACK_SIZE", 8192)
    zephyr_add_prj_conf("OPENTHREAD_CHANNEL", config[CONF_CHANNEL])
    panid_int = int(config[CONF_PANID])  # Already an integer from cv.hex_uint16_t
    zephyr_add_prj_conf("OPENTHREAD_PANID", panid_int)
    zephyr_add_prj_conf("OPENTHREAD_NETWORK_NAME", config[CONF_NETWORK_NAME])
    zephyr_add_prj_conf("OPENTHREAD_XPANID", config[CONF_XPANID])
    zephyr_add_prj_conf("OPENTHREAD_NETWORKKEY", config[CONF_NETWORK_KEY])
    zephyr_add_prj_conf("OPENTHREAD_MANUAL_START", True)
    zephyr_add_prj_conf("OPENTHREAD_DEFAULT_TX_POWER", config[CONF_RADIO_TX_POWER])

    # Radio settings
    zephyr_add_prj_conf("OPENTHREAD_RADIO_WORKQUEUE_STACK_SIZE", 2048)

    # Add build flags - ensure proper spacing between flags
    cg.add_build_flag("-DUSE_OPENTHREAD")
    cg.add_build_flag("-DUSE_ZEPHYR_OPENTHREAD")
    cg.add_build_flag("-DUSE_IPV6")
    cg.add_build_flag("-DUSE_ZEPHYR")
    cg.add_build_flag("-DUSE_ZEPHYR_NETWORKING")

    # Add device tree overlay for OpenThread
    zephyr_add_overlay("""
&ieee802154 {
    status = "okay";
};

&p25q16h {
	status = "okay";
};

/ {
    chosen {
        nordic,pm-ext-flash = &p25q16h;
    };
};
    """)
    
    zephyr_add_mcuboot_overlay("""
&p25q16h {
	status = "okay";
};

/ {
    chosen {
        nordic,pm-ext-flash = &p25q16h;
    };
    
    aliases {
        mcuboot-button0 = &button0;
    };
};

&gpio0 {
    status = "okay";
};

/ {
    buttons {
        compatible = "gpio-keys";
        button0: button_0 {
            gpios = <&gpio0 28 (GPIO_PULL_UP | GPIO_ACTIVE_LOW)>;
            label = "MCUboot recovery button";
        };
    };
};
    """)

