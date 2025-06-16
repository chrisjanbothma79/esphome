import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, ENTITY_CATEGORY_DIAGNOSTIC, STATE_CLASS_MEASUREMENT

from . import LoopTestComponent

DEPENDENCIES = ["loop_test_component"]

CONF_LOOP_COUNT = "loop_count"
CONF_SETUP_DISABLE_COUNT = "setup_disable_count"
CONF_SETUP_ENABLE_COUNT = "setup_enable_count"
CONF_LOOP_DISABLE_COUNT = "loop_disable_count"
CONF_EXTERNAL_ENABLE_COUNT = "external_enable_count"
CONF_EXTERNAL_DISABLE_COUNT = "external_disable_count"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ID): cv.use_id(LoopTestComponent),
        cv.Optional(CONF_LOOP_COUNT): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_SETUP_DISABLE_COUNT): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_SETUP_ENABLE_COUNT): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_LOOP_DISABLE_COUNT): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_EXTERNAL_ENABLE_COUNT): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_EXTERNAL_DISABLE_COUNT): sensor.sensor_schema(
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_ID])

    if CONF_LOOP_COUNT in config:
        sens = await sensor.new_sensor(config[CONF_LOOP_COUNT])
        cg.add(
            parent.set_loop_count_sensor(sens)
        )  # We'll implement this in the component

    # For simplicity, let's just expose loop_count for now in the test
