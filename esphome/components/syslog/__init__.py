import esphome.codegen as cg
from esphome.components import udp
from esphome.components.udp import CONF_UDP_ID
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.cpp_types import Component, Parented

CODEOWNERS = ["@clydebarrow"]

syslog_ns = cg.esphome_ns.namespace("syslog")
Syslog = syslog_ns.class_("Syslog", Component, Parented.template(udp.UDPComponent))
CONFIG_SCHEMA = udp.UDP_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(Syslog),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_UDP_ID])
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await cg.register_parented(var, parent)
