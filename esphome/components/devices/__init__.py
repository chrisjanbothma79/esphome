from esphome import codegen as cg, config_validation as cv
from esphome.const import CONF_AREA, CONF_ID, CONF_NAME

ns = cg.esphome_ns.namespace("devices")
DeviceClass = ns.Class("SubDevice")
StringRef = cg.esphome_ns.struct("StringRef")

MULTI_CONF = True

CODEOWNERS = ["@dala318"]

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ID): cv.declare_id(DeviceClass),
        # cv.Required(CONF_NAME): cv.declare_id(StringRef),
        # cv.Optional(CONF_AREA, ""): cv.declare_id(StringRef),
        cv.Required(CONF_NAME): cv.string,
        cv.Optional(CONF_AREA, ""): cv.string,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    dev = cg.new_Pvariable(config[CONF_ID])
    cg.add(dev.set_name(config[CONF_NAME]))
    if CONF_AREA in config:
        cg.add(dev.set_area(config[CONF_AREA]))
    cg.add(cg.App.register_sub_device(dev))
    # cg.add(
    #     cg.App.register_sub_device(
    #         config[CONF_ID],
    #         config[CONF_NAME],
    #         config[CONF_AREA],
    #         # config.get(CONF_COMMENT, ""),
    #     )
    # )
    cg.add_define("USE_SUB_DEVICE")
