import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PORT

CODEOWNERS = ["@clydebarrow"]
DEPENDENCIES = ["network"]
AUTO_LOAD = ["socket"]

MULTI_CONF = True
udp_ns = cg.esphome_ns.namespace("udp")
UDPComponent = udp_ns.class_("UDPComponent", cg.Component)

CONF_ADDRESSES = "addresses"
CONF_LISTEN_ADDRESS = "listen_address"
CONF_UDP_ID = "udp_id"

UDP_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_UDP_ID): cv.use_id(UDPComponent),
    }
)

CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(UDPComponent),
        cv.Optional(CONF_PORT, default=18511): cv.port,
        cv.Optional(
            CONF_LISTEN_ADDRESS, default="255.255.255.255"
        ): cv.ipv4address_multi_broadcast,
        cv.Optional(CONF_ADDRESSES, default=["255.255.255.255"]): cv.ensure_list(
            cv.ipv4address,
        ),
    }
)


async def register_udp_client(var, config):
    udp_var = await cg.get_variable(config[CONF_UDP_ID])
    cg.add(var.set_parent(udp_var))
    return udp_var


async def to_code(config):
    cg.add_define("USE_UDP")
    cg.add_global(udp_ns.using)
    var = cg.new_Pvariable(config[CONF_ID])
    var = await cg.register_component(var, config)
    cg.add(var.set_port(config[CONF_PORT]))
    if (listen_address := str(config[CONF_LISTEN_ADDRESS])) != "255.255.255.255":
        cg.add(var.set_listen_address(listen_address))
    for address in config[CONF_ADDRESSES]:
        cg.add(var.add_address(str(address)))
