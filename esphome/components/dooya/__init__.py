from esphome import automation
import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ADDRESS, CONF_ID

CODEOWNERS = ["@balika011"]
DEPENDENCIES = ["uart"]

MULTI_CONF = True

CONF_DOOYA_BRIDGE_ID = "dooya_bridge_id"

dooya_ns = cg.esphome_ns.namespace("dooya")
DooyaBridge = dooya_ns.class_("DooyaBridge", cg.Component)
DooyaComponent = dooya_ns.class_("DooyaComponent", cg.Component, cg.Parented)


def validate_address(value):
    if value is None:
        raise cv.Invalid("address value is None")
    value = str(value)
    if not value.isupper() or not value.isalnum() or len(value) != 3:
        raise cv.Invalid(f"{value} is not 3 uppercase alphanumeric characters")
    return value


DOOYA_CHILD_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_DOOYA_BRIDGE_ID): cv.use_id(DooyaBridge),
        cv.Required(CONF_ADDRESS): validate_address,
    }
)


async def register_component(var, config):
    paren = await cg.get_variable(config[CONF_DOOYA_BRIDGE_ID])
    await cg.register_parented(var, paren)
    cg.add(var.set_address(config[CONF_ADDRESS]))
    await cg.register_component(var, config)
    cg.add(paren.register_subcomponent(var))


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DooyaBridge),
    }
).extend(uart.UART_DEVICE_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await uart.register_uart_device(var, config)
    await cg.register_component(var, config)


DooyaBridgePairingAction = dooya_ns.class_(
    "DooyaBridgePairingAction", automation.Action
)


@automation.register_action(
    "dooya_bridge.pairing",
    DooyaBridgePairingAction,
    automation.maybe_simple_id(
        {
            cv.Required(CONF_ID): cv.use_id(DooyaBridge),
        }
    ),
)
async def dooya_bridge_pairing_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])

    return var
