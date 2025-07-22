import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

CODEOWNERS = ["@mikelawrence"]
MULTI_CONF = True

CONF_DFROBOT_C4001_ID = "dfrobot_c4001_id"

dfrobot_c4001_ns = cg.esphome_ns.namespace("dfrobot_c4001")
DFRobotC4001Hub = dfrobot_c4001_ns.class_(
    "DFRobotC4001Hub", cg.Component, uart.UARTDevice
)

HUB_CHILD_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_DFROBOT_C4001_ID): cv.use_id(DFRobotC4001Hub),
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(DFRobotC4001Hub),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "dfrobot_c4001",
    require_tx=True,
    require_rx=True,
    parity="NONE",
    stop_bits=1,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
