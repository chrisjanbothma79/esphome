import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@test"]
AUTO_LOAD = ["api"]

api_buffer_test_component_ns = cg.esphome_ns.namespace("api_buffer_test_component")
APIBufferTestComponent = api_buffer_test_component_ns.class_(
    "APIBufferTestComponent", cg.Component
)

CONF_FILL_SIZE = "fill_size"
CONF_FILL_COUNT = "fill_count"
CONF_AUTO_FILL_DELAY = "auto_fill_delay"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(APIBufferTestComponent),
        cv.Optional(CONF_FILL_SIZE, default=2048): cv.int_range(min=1, max=16384),
        cv.Optional(CONF_FILL_COUNT, default=200): cv.int_range(min=1, max=1000),
        cv.Optional(
            CONF_AUTO_FILL_DELAY, default="2s"
        ): cv.positive_time_period_milliseconds,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_fill_size(config[CONF_FILL_SIZE]))
    cg.add(var.set_fill_count(config[CONF_FILL_COUNT]))
    cg.add(var.set_auto_fill_delay(config[CONF_AUTO_FILL_DELAY]))
