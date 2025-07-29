from esphome import automation
import esphome.codegen as cg
from esphome.components import i2c, sensor, text_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_HUMIDITY,
    CONF_ID,
    CONF_TEMPERATURE,
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_TEMPERATURE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_PERCENT,
)
CONF_LAST_ERROR = 'last_error'

DEPENDENCIES = ["i2c"]

hdc302x_ns = cg.esphome_ns.namespace("hdc302x")
HDC302XComponent = hdc302x_ns.class_(
    "HDC302XComponent", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(HDC302XComponent),
            cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_HUMIDITY): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_HUMIDITY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_LAST_ERROR): text_sensor.text_sensor_schema(
            ),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x44))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature(sens))

    if CONF_HUMIDITY in config:
        sens = await sensor.new_sensor(config[CONF_HUMIDITY])
        cg.add(var.set_humidity(sens))
        
    if CONF_LAST_ERROR in config:
        sens = await text_sensor.new_text_sensor(config[CONF_LAST_ERROR])
        cg.add(var.set_last_error(sens))


if False:
    # Actions
    HDC302XAirCalibrationAction = hdc302x_ns.class_(
        "HDC302XAirCalibrationAction", automation.Action
    )
    HDC302X_CALIBRATION_SCHEMA = cv.Schema(
        {
            cv.GenerateID(): cv.use_id(HDC302XComponent),
        }
    )
    @automation.register_action(
        "hdc302x.air_calibration",
        HDC302XAirCalibrationAction,
        HDC302X_CALIBRATION_SCHEMA,
    )
    async def hdc302x_calibration_to_code(config, action_id, template_arg, args):
        parent = await cg.get_variable(config[CONF_ID])
        var = cg.new_Pvariable(action_id, template_arg, parent)
        return var
    HDC302X_NEW_I2C_ADDRESS_SCHEMA = cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(HDC302XComponent),
            cv.Required(CONF_ADDRESS): cv.templatable(cv.i2c_address),
        },
        key=CONF_ADDRESS,
    )
    @automation.register_action(
        "hdc302x.new_i2c_address",
        HDC302XNewI2cAddressAction,
        HDC302X_NEW_I2C_ADDRESS_SCHEMA,
    )
    async def hdc302xnewi2caddress_to_code(config, action_id, template_arg, args):
        parent = await cg.get_variable(config[CONF_ID])
        var = cg.new_Pvariable(action_id, template_arg, parent)
        address = await cg.templatable(config[CONF_ADDRESS], args, int)
        cg.add(var.set_new_address(address))
        return var
