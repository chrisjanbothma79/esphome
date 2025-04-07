import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PHASE_A, CONF_PHASE_B, CONF_PHASE_C

from .. import atm90e32_ns
from ..sensor import ATM90E32Component

ATM90E32PhaseStatusSensor = atm90e32_ns.class_(
    "ATM90E32PhaseStatusSensor",
    text_sensor.TextSensor,
    cg.Parented.template(ATM90E32Component),
)

ATM90E32FreqStatusSensor = atm90e32_ns.class_(
    "ATM90E32FreqStatusSensor",
    text_sensor.TextSensor,
    cg.Parented.template(ATM90E32Component),
)

CONF_PHASE_STATUS = "phase_status"
CONF_FREQ_STATUS = "freq_status"
PHASE_KEYS = [CONF_PHASE_A, CONF_PHASE_B, CONF_PHASE_C]

PHASE_STATUS_SCHEMA = cv.Schema(
    {
        cv.Optional(CONF_PHASE_A): text_sensor.text_sensor_schema(
            ATM90E32PhaseStatusSensor, icon="mdi:flash-alert"
        ),
        cv.Optional(CONF_PHASE_B): text_sensor.text_sensor_schema(
            ATM90E32PhaseStatusSensor, icon="mdi:flash-alert"
        ),
        cv.Optional(CONF_PHASE_C): text_sensor.text_sensor_schema(
            ATM90E32PhaseStatusSensor, icon="mdi:flash-alert"
        ),
    }
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.use_id(ATM90E32Component),
        cv.Optional(CONF_PHASE_STATUS): PHASE_STATUS_SCHEMA,
        cv.Optional(CONF_FREQ_STATUS): text_sensor.text_sensor_schema(
            ATM90E32FreqStatusSensor, icon="mdi:lightbulb-alert"
        ),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_ID])

    if CONF_PHASE_STATUS in config:
        phase_cfg = config[CONF_PHASE_STATUS]
        for i, key in enumerate(PHASE_KEYS):
            if key in phase_cfg:
                sens = await text_sensor.new_text_sensor(phase_cfg[key])
                await cg.register_parented(sens, parent)
                cg.add(parent.set_phase_status_text_sensor(i, sens))

    if CONF_FREQ_STATUS in config:
        sens = await text_sensor.new_text_sensor(config[CONF_FREQ_STATUS])
        await cg.register_parented(sens, parent)
        cg.add(parent.set_freq_status_text_sensor(sens))
