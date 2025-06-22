import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome import pins
from esphome.components import button, number, sensor

HAMULIGHT_NAMESPACE = cg.esphome_ns.namespace('hamulight')
HamulightComponent = HAMULIGHT_NAMESPACE.class_('HamulightComponent', cg.Component)

CONF_RF_TRANSMIT_PIN = "rf_transmit_pin"
CONF_RF_ADDRESS = "rf_address"
CONF_LED_PIN = "led_pin"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HamulightComponent),
    cv.Required(CONF_RF_TRANSMIT_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_LED_PIN): pins.gpio_output_pin_schema,
    cv.Required(CONF_RF_ADDRESS): cv.hex_uint16_t,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    rf_pin_num = config[CONF_RF_TRANSMIT_PIN]["number"]
    cg.add(var.set_rf_pin_num(rf_pin_num))

    rf_transmit_pin_code = await cg.gpio_pin_expression(config[CONF_RF_TRANSMIT_PIN])
    cg.add(var.set_rf_transmit_pin(rf_transmit_pin_code))

    if CONF_LED_PIN in config:
        led_pin_code = await cg.gpio_pin_expression(config[CONF_LED_PIN])
        cg.add(var.set_led_pin(led_pin_code))

    cg.add(var.set_rf_address(config[CONF_RF_ADDRESS]))

    # Button: Toggle
    b_toggle = await cg.get_variable("hamulight_toggle_btn")
    cg.add(b_toggle.set_on_press(cg.Lambda("id({}).toggle();".format(config[CONF_ID]))))

    # Button: Pair with LED driver (maximum Brightness)
    b_pair = await cg.get_variable("hamulight_pair_btn")
    cg.add(b_pair.set_on_press(cg.Lambda("id({}).pair_with_driver();".format(config[CONF_ID]))))

    # Button: Start Command Scan
    b_cmdscan = await cg.get_variable("hamulight_cmdscan_btn")
    cg.add(b_cmdscan.set_on_press(cg.Lambda("id({}).start_command_scan();".format(config[CONF_ID]))))

    # Number: Brightness
    n_brightness = await cg.get_variable("hamulight_brightness")
    cg.add(n_brightness.set_min_value(0))
    cg.add(n_brightness.set_max_value(100))
    cg.add(n_brightness.set_step(1))
    cg.add(n_brightness.set_set_action(cg.Lambda("id({}).set_brightness(x);".format(config[CONF_ID]))))


    
    # --- THE FOLLOWING CODE IS FOR THE OPTIONAL COMMAND SCANNER ---
    
    # Button: Stop Command Scan
    b_cmdscan_stop = await cg.get_variable("hamulight_cmdscan_stop_btn")
    cg.add(b_cmdscan_stop.set_on_press(cg.Lambda("id({}).stop_command_scan();".format(config[CONF_ID]))))


    # Command Scan Numbers - start of the range
    n_cmdscan_start = await cg.get_variable("hamulight_cmdscan_start")
    cg.add(n_cmdscan_start.set_min_value(0))
    cg.add(n_cmdscan_start.set_max_value(255))
    cg.add(n_cmdscan_start.set_step(1))
    cg.add(var.set_cmdscan_start_number(n_cmdscan_start))

    # Command Scan Numbers - end of the range
    n_cmdscan_end = await cg.get_variable("hamulight_cmdscan_end")
    cg.add(n_cmdscan_end.set_min_value(0))
    cg.add(n_cmdscan_end.set_max_value(255))
    cg.add(n_cmdscan_end.set_step(1))
    cg.add(var.set_cmdscan_end_number(n_cmdscan_end))

    # Command Scan Numbers - pause (in ms) between each scan command sent
    n_cmdscan_pause = await cg.get_variable("hamulight_cmdscan_pause")
    cg.add(n_cmdscan_pause.set_min_value(0))
    cg.add(n_cmdscan_pause.set_max_value(5000))
    cg.add(n_cmdscan_pause.set_step(10))
    cg.add(var.set_cmdscan_pause_number(n_cmdscan_pause))

    # Sensor: Last Scanned Command
    s_last_scanned = await cg.get_variable("hamulight_last_scanned_command")
    cg.add(var.set_last_scanned_sensor(s_last_scanned))
