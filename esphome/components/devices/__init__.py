from esphome import codegen as cg, config_validation as cv
from esphome.const import CONF_AREA, CONF_ID, CONF_NAME

devices_ns = cg.esphome_ns.namespace("devices")
SubDevice = devices_ns.class_("SubDevice")

MULTI_CONF = True

CODEOWNERS = ["@dala318"]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ID): cv.declare_id(SubDevice),
        cv.Required(CONF_NAME): cv.string,
        cv.Optional(CONF_AREA, default=""): cv.string,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    dev = cg.new_Pvariable(config[CONF_ID])
    cg.add(dev.set_uid(hash(str(config[CONF_ID])) % 0xFFFFFFFF))
    cg.add(dev.set_name(config[CONF_NAME]))
    cg.add(dev.set_area(config[CONF_AREA]))
    cg.add(cg.App.register_sub_device(dev))
    cg.add_define("USE_SUB_DEVICE")
