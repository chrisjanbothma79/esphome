from esphome import pins
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PIN
from esphome.core import coroutine_with_priority

activity_led_ns = cg.esphome_ns.namespace("activity_led")
ActivityLED = activity_led_ns.class_("ActivityLED", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(ActivityLED),
        cv.Required(CONF_PIN): pins.gpio_output_pin_schema,
    }
).extend(cv.COMPONENT_SCHEMA)


@coroutine_with_priority(80.0)
async def to_code(config):
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    rhs = ActivityLED.new(pin)
    var = cg.Pvariable(config[CONF_ID], rhs)
    await cg.register_component(var, config)
    cg.add(var.pre_setup())
    cg.add_define("USE_ACTIVITY_LED")
