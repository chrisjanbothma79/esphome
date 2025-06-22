import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome import pins
from esphome.components import number, sensor

# Define the C++ namespace and component
hamulight_ns = cg.esphome_ns.namespace("hamulight")
HamulightComponent = hamulight_ns.class_("HamulightComponent", cg.Component)

CONF_RF_TRANSMIT_PIN = "rf_transmit_pin"
CONF_RF_ADDRESS = "rf_address"
CONF_LED_PIN = "led_pin"

# Command scanner optional fields
CONF_CMDSCAN_START = "cmdscan_start"
CONF_CMDSCAN_END = "cmdscan_end"
CONF_CMDSCAN_PAUSE = "cmdscan_pause"
CONF_LAST_SCANNED_SENSOR = "last_scanned_sensor"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(HamulightComponent),
        cv.Required(CONF_RF_TRANSMIT_PIN): pins.gpio_output_pin_schema,
        cv.Required(CONF_RF_ADDRESS): cv.hex_uint16_t,
        cv.Optional(CONF_LED_PIN): pins.gpio_output_pin_schema,
        # Optional command scanner entity references (numbers and sensor)
        cv.Optional(CONF_CMDSCAN_START): cv.use_id(number.Number),
        cv.Optional(CONF_CMDSCAN_END): cv.use_id(number.Number),
        cv.Optional(CONF_CMDSCAN_PAUSE): cv.use_id(number.Number),
        cv.Optional(CONF_LAST_SCANNED_SENSOR): cv.use_id(sensor.Sensor),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # Set pin numbers for logging and hardware
    rf_pin_num = config[CONF_RF_TRANSMIT_PIN]["number"]
    cg.add(var.set_rf_pin_num(rf_pin_num))
    rf_transmit_pin_code = await cg.gpio_pin_expression(config[CONF_RF_TRANSMIT_PIN])
    cg.add(var.set_rf_transmit_pin(rf_transmit_pin_code))
    cg.add(var.set_rf_address(config[CONF_RF_ADDRESS]))

    # Optional feedback LED
    if CONF_LED_PIN in config:
        led_pin_code = await cg.gpio_pin_expression(config[CONF_LED_PIN])
        cg.add(var.set_led_pin(led_pin_code))
        cg.add(var.set_led_pin_num(config[CONF_LED_PIN]["number"]))

    # Optional command scanner number entities (linked for use in C++)
    if CONF_CMDSCAN_START in config:
        num = await cg.get_variable(config[CONF_CMDSCAN_START])
        cg.add(var.set_cmdscan_start_number(num))
    if CONF_CMDSCAN_END in config:
        num = await cg.get_variable(config[CONF_CMDSCAN_END])
        cg.add(var.set_cmdscan_end_number(num))
    if CONF_CMDSCAN_PAUSE in config:
        num = await cg.get_variable(config[CONF_CMDSCAN_PAUSE])
        cg.add(var.set_cmdscan_pause_number(num))

    # Optional last scanned sensor (template sensor)
    if CONF_LAST_SCANNED_SENSOR in config:
        s = await cg.get_variable(config[CONF_LAST_SCANNED_SENSOR])
        cg.add(var.set_last_scanned_sensor(s))
