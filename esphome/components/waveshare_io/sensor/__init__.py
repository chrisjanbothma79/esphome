import esphome.codegen as cg
from esphome.components import sensor, voltage_sampler
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_REFERENCE_VOLTAGE,
    DEVICE_CLASS_VOLTAGE,
    STATE_CLASS_MEASUREMENT,
    UNIT_VOLT,
)

from .. import CONF_WAVESHARE_IO_ID, WaveshareIOComponent, waveshare_io_ns

AUTO_LOAD = ["voltage_sampler"]

DEPENDENCIES = ["waveshare_io"]

WaveshareIOSensor = waveshare_io_ns.class_(
    "WaveshareIOSensor",
    sensor.Sensor,
    cg.PollingComponent,
    voltage_sampler.VoltageSampler,
    cg.Parented.template(WaveshareIOComponent),
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        WaveshareIOSensor,
        unit_of_measurement=UNIT_VOLT,
        accuracy_decimals=3,
        device_class=DEVICE_CLASS_VOLTAGE,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.GenerateID(CONF_WAVESHARE_IO_ID): cv.use_id(WaveshareIOComponent),
            cv.Optional(CONF_REFERENCE_VOLTAGE, default="9.9V"): cv.voltage,
        }
    )
    .extend(cv.polling_component_schema("60s"))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_parented(var, config[CONF_WAVESHARE_IO_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    cg.add(var.set_reference_voltage(config[CONF_REFERENCE_VOLTAGE]))
