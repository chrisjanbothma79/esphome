import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import (
    CONF_MAX_RANGE,
    CONF_MIN_RANGE,
    DEVICE_CLASS_DISTANCE,
    DEVICE_CLASS_DURATION,
    ENTITY_CATEGORY_CONFIG,
    ICON_ARROW_EXPAND_VERTICAL,
    ICON_SCALE,
    ICON_TIMER,
    UNIT_METER,
    UNIT_SECOND,
)

from .. import CONF_DFROBOT_C4001_ID, HUB_CHILD_SCHEMA, dfrobot_c4001_ns

DEPENDENCIES = ["dfrobot_c4001"]

CONF_TRIGGER_RANGE = "trigger_range"
CONF_HOLD_SENSITIVITY = "hold_sensitivity"
CONF_TRIGGER_SENSITIVITY = "trigger_sensitivity"
CONF_ON_LATENCY = "on_latency"
CONF_OFF_LATENCY = "off_latency"
CONF_INHIBIT_TIME = "inhibit_time"

MaxRangeNumber = dfrobot_c4001_ns.class_("MaxRangeNumber", number.Number)
MinRangeNumber = dfrobot_c4001_ns.class_("MinRangeNumber", number.Number)
TriggerRangeNumber = dfrobot_c4001_ns.class_("TriggerRangeNumber", number.Number)
HoldSensitivityNumber = dfrobot_c4001_ns.class_("HoldSensitivityNumber", number.Number)
TriggerSensitivityNumber = dfrobot_c4001_ns.class_(
    "TriggerSensitivityNumber", number.Number
)
OnLatencyNumber = dfrobot_c4001_ns.class_("OnLatencyNumber", number.Number)
OffLatencyNumber = dfrobot_c4001_ns.class_("OffLatencyNumber", number.Number)
OffLatencyNumber = dfrobot_c4001_ns.class_("OffLatencyNumber", number.Number)
InhibitTimeNumber = dfrobot_c4001_ns.class_("InhibitTimeNumber", number.Number)

RANGE_GROUP = "Range Group: min_range and max_range"
SENSITIVITY_GROUP = "Sensitivity Group: hold_sensitivity and trigger_sensitivity"
LATENCY_GROUP = "Latency Group: on_latency and off_latency"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.Inclusive(CONF_MAX_RANGE, RANGE_GROUP): number.number_schema(
                MaxRangeNumber,
                unit_of_measurement=UNIT_METER,
                device_class=DEVICE_CLASS_DISTANCE,
                entity_category=ENTITY_CATEGORY_CONFIG,
                icon=ICON_ARROW_EXPAND_VERTICAL,
            ),
            cv.Inclusive(CONF_MIN_RANGE, RANGE_GROUP): number.number_schema(
                MinRangeNumber,
                unit_of_measurement=UNIT_METER,
                device_class=DEVICE_CLASS_DISTANCE,
                entity_category=ENTITY_CATEGORY_CONFIG,
                icon=ICON_ARROW_EXPAND_VERTICAL,
            ),
            cv.Optional(CONF_TRIGGER_RANGE): number.number_schema(
                TriggerRangeNumber,
                unit_of_measurement=UNIT_METER,
                device_class=DEVICE_CLASS_DISTANCE,
                entity_category=ENTITY_CATEGORY_CONFIG,
                icon=ICON_ARROW_EXPAND_VERTICAL,
            ),
            cv.Inclusive(
                CONF_HOLD_SENSITIVITY, SENSITIVITY_GROUP
            ): number.number_schema(
                HoldSensitivityNumber,
                entity_category=ENTITY_CATEGORY_CONFIG,
                icon=ICON_SCALE,
            ),
            cv.Inclusive(
                CONF_TRIGGER_SENSITIVITY, SENSITIVITY_GROUP
            ): number.number_schema(
                TriggerSensitivityNumber,
                entity_category=ENTITY_CATEGORY_CONFIG,
                icon=ICON_SCALE,
            ),
            cv.Inclusive(CONF_ON_LATENCY, LATENCY_GROUP): number.number_schema(
                OnLatencyNumber,
                unit_of_measurement=UNIT_SECOND,
                entity_category=ENTITY_CATEGORY_CONFIG,
                device_class=DEVICE_CLASS_DURATION,
                icon=ICON_TIMER,
            ),
            cv.Inclusive(CONF_OFF_LATENCY, LATENCY_GROUP): number.number_schema(
                OffLatencyNumber,
                unit_of_measurement=UNIT_SECOND,
                entity_category=ENTITY_CATEGORY_CONFIG,
                device_class=DEVICE_CLASS_DURATION,
                icon=ICON_TIMER,
            ),
            cv.Optional(CONF_INHIBIT_TIME): number.number_schema(
                InhibitTimeNumber,
                unit_of_measurement=UNIT_SECOND,
                entity_category=ENTITY_CATEGORY_CONFIG,
                device_class=DEVICE_CLASS_DURATION,
                icon=ICON_TIMER,
            ),
        }
    )
    .extend(HUB_CHILD_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    sens0609_hub = await cg.get_variable(config[CONF_DFROBOT_C4001_ID])

    if max_range := config.get(CONF_MAX_RANGE):
        n = await number.new_number(max_range, min_value=0.6, max_value=25.0, step=0.1)
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_max_range_number(n))
    if min_range := config.get(CONF_MIN_RANGE):
        n = await number.new_number(min_range, min_value=0.6, max_value=25.0, step=0.1)
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_min_range_number(n))
    if trigger_range := config.get(CONF_TRIGGER_RANGE):
        n = await number.new_number(
            trigger_range, min_value=0.6, max_value=25.0, step=0.1
        )
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_trigger_range_number(n))
    if hold_sensitivity := config.get(CONF_HOLD_SENSITIVITY):
        n = await number.new_number(hold_sensitivity, min_value=0, max_value=9, step=1)
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_hold_sensitivity_number(n))
    if trigger_sensitivity := config.get(CONF_TRIGGER_SENSITIVITY):
        n = await number.new_number(
            trigger_sensitivity, min_value=0, max_value=9, step=1
        )
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_trigger_sensitivity_number(n))
    if on_latency := config.get(CONF_ON_LATENCY):
        n = await number.new_number(
            on_latency, min_value=0.0, max_value=100.0, step=0.01
        )
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_on_latency_number(n))
    if off_latency := config.get(CONF_OFF_LATENCY):
        n = await number.new_number(
            off_latency, min_value=2.0, max_value=1500.0, step=0.5
        )
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_off_latency_number(n))
    if inhibit_time := config.get(CONF_INHIBIT_TIME):
        n = await number.new_number(
            inhibit_time, min_value=0.1, max_value=255.0, step=0.01
        )
        await cg.register_parented(n, config[CONF_DFROBOT_C4001_ID])
        cg.add(sens0609_hub.set_inhibit_time_number(n))
