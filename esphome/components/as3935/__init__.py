from esphome import pins
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import (
    CONF_CALIBRATION,
    CONF_CAPACITANCE,
    CONF_DIV_RATIO,
    CONF_INDOOR,
    CONF_IRQ_PIN,
    CONF_LIGHTNING_THRESHOLD,
    CONF_MASK_DISTURBER,
    CONF_NOISE_LEVEL,
    CONF_SPIKE_REJECTION,
    CONF_TUNE_ANTENNA,
    CONF_WATCHDOG_THRESHOLD,
    CONF_ID,
    CONF_ENTITY_CATEGORY,
    CONF_ICON,
)
from esphome.core.entity_helpers import entity_duplicate_validator
from esphome.cpp_generator import MockObjClass

MULTI_CONF = True

CONF_AS3935_ID = "as3935_id"

as3935_ns = cg.esphome_ns.namespace("as3935")
AS3935 = as3935_ns.class_("AS3935Component", cg.Component)

_AS3935_SCHEMA = cv.ENTITY_BASE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(AS3935),
        cv.Required(CONF_IRQ_PIN): pins.gpio_input_pin_schema,
        cv.Optional(CONF_INDOOR, default=True): cv.boolean,
        cv.Optional(CONF_NOISE_LEVEL, default=2): cv.int_range(min=1, max=7),
        cv.Optional(CONF_WATCHDOG_THRESHOLD, default=2): cv.int_range(min=1, max=10),
        cv.Optional(CONF_SPIKE_REJECTION, default=2): cv.int_range(min=1, max=11),
        cv.Optional(CONF_LIGHTNING_THRESHOLD, default=1): cv.one_of(
            1, 5, 9, 16, int=True
        ),
        cv.Optional(CONF_MASK_DISTURBER, default=False): cv.boolean,
        cv.Optional(CONF_DIV_RATIO, default=0): cv.one_of(0, 16, 32, 64, 128, int=True),
        cv.Optional(CONF_CAPACITANCE, default=0): cv.int_range(min=0, max=15),
        cv.Optional(CONF_TUNE_ANTENNA, default=False): cv.boolean,
        cv.Optional(CONF_CALIBRATION, default=True): cv.boolean,
    }
)

_AS3935_SCHEMA.add_extra(entity_duplicate_validator("as3935"))


def as3935_schema(
    class_: MockObjClass,
    *,
    entity_category: str = cv.UNDEFINED,
    icon: str = cv.UNDEFINED,
) -> cv.Schema:
    schema = {cv.GenerateID(CONF_ID): cv.declare_id(class_)}

    for key, default, validator in [
        (CONF_ENTITY_CATEGORY, entity_category, cv.entity_category),
        (CONF_ICON, icon, cv.icon),
    ]:
        if default is not cv.UNDEFINED:
            schema[cv.Optional(key, default=default)] = validator

    return _AS3935_SCHEMA.extend(schema)


# Remove before 2025.11.0
AS3935_SCHEMA = as3935_schema(AS3935)
AS3935_SCHEMA.add_extra(cv.deprecated_schema_constant("as3935"))


async def setup_as3935(var, config):
    await cg.register_component(var, config)

    irq_pin = await cg.gpio_pin_expression(config[CONF_IRQ_PIN])
    cg.add(var.set_irq_pin(irq_pin))
    cg.add(var.set_indoor(config[CONF_INDOOR]))
    cg.add(var.set_noise_level(config[CONF_NOISE_LEVEL]))
    cg.add(var.set_watchdog_threshold(config[CONF_WATCHDOG_THRESHOLD]))
    cg.add(var.set_spike_rejection(config[CONF_SPIKE_REJECTION]))
    cg.add(var.set_lightning_threshold(config[CONF_LIGHTNING_THRESHOLD]))
    cg.add(var.set_mask_disturber(config[CONF_MASK_DISTURBER]))
    cg.add(var.set_div_ratio(config[CONF_DIV_RATIO]))
    cg.add(var.set_capacitance(config[CONF_CAPACITANCE]))
    cg.add(var.set_tune_antenna(config[CONF_TUNE_ANTENNA]))
    cg.add(var.set_calibration(config[CONF_CALIBRATION]))
