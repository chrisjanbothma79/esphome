import esphome.codegen as cg
from esphome.components import i2c, display
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_LAMBDA,
    CONF_NUM_CHIPS,
    CONF_BUFFER_SIZE,
    CONF_BRIGHTNESS,
    CONF_DEVICE,
)

DEPENDENCIES = ["i2c"]

ht16k33_char_ns = cg.esphome_ns.namespace("ht16k33_char")

#------------------------------------------
#From ht16k33_alpha. TODO: Maybe implement these?
#TODO: Should I move these to const.py
CONF_CONTINUOUS = "continuous"
CONF_SCROLL = "scroll"
CONF_SCROLL_SPEED = "scroll_speed"
CONF_SCROLL_DWELL = "scroll_dwell"
CONF_SCROLL_DELAY = "scroll_delay"
CONF_SECONDARY_DISPLAYS = "secondary_displays"

CONFIG_SECONDARY = cv.Schema({
    cv.GenerateID(): cv.declare_id(i2c.I2CDevice)
}).extend(i2c.i2c_device_schema(None))
#------------------------------------------

#HT16K33Char_DeviceType = ht16k33_char_ns.enum("HT16K33Char_DeviceType")
#HT16K33_DEVICE_TYPES = {
#    "ADAFRUIT_7SEGMENT_1_2IN": HT16K33Char_DeviceType.ADAFRUIT_7SEGMENT_1_2IN,
#    "ADAFRUIT_14_SEG": HT16K33Char_DeviceType.ADAFRUIT_14_SEGMENT,
#}

HT16K33_DEVICE_TYPES = {
    "ADAFRUIT_7SEGMENT_1_2IN":  1,
    "ADAFRUIT_14_SEG":          2,
}


HT16k33CharComponent = ht16k33_char_ns.class_("HT16k33CharComponent", cg.PollingComponent, i2c.I2CDevice)
HT16k33ComponentRef = HT16k33CharComponent.operator("ref")

CONFIG_SCHEMA = ( display.BASIC_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(HT16k33CharComponent),
            cv.Optional(CONF_BUFFER_SIZE, default=8): cv.int_range(min=1, max=255),
            cv.Optional(CONF_BRIGHTNESS, default=15): cv.int_range(min=0, max=15),
            cv.Required(CONF_DEVICE): cv.enum(HT16K33_DEVICE_TYPES, upper=True),
            cv.Optional(CONF_SECONDARY_DISPLAYS): cv.ensure_list(CONFIG_SECONDARY),
            cv.Optional(CONF_CONTINUOUS, default=False): cv.boolean,
            cv.Optional(CONF_SCROLL, default=False): cv.boolean,
            cv.Optional(CONF_SCROLL_SPEED, default='250ms'): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_SCROLL_DWELL, default='2s'): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_SCROLL_DELAY, default='3'): cv.float_range(min=1),
        }
    )
    .extend(cv.polling_component_schema("10s"))
    .extend(i2c.i2c_device_schema(0x70))
)

async def to_code(config):
    
    for key, value in HT16K33_DEVICE_TYPES.items():
        cg.add_define("HT16K33_CHAR_TYPE_"+key, value)
    
    
    var = cg.new_Pvariable(config[CONF_ID])
    await i2c.register_i2c_device(var, config)
    await display.register_display(var, config)

    cg.add(var.set_buffer_size(config[CONF_BUFFER_SIZE]))   #TODO: I could use a compiler define to set this size. Is that a good idea?
    cg.add(var.set_brightness(config[CONF_BRIGHTNESS]))
    
    #TODO: I set this twice, I probably don't need to do that, but it should not hurt anything. 
    # I need the compiler define in order to remove char maps for devices that we are not using. 
    # However, I could use the compiler define to set the device type in the class. Also, do I 
    # even use that variable in the class?
    #cg.add(var.set_device_type(config[CONF_DEVICE]))
    cg.add_define("HT16K33_CHAR_DISPLAY_TYPE", config[CONF_DEVICE])

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(HT16k33ComponentRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
    
    #TODO: From ht16k33_alpha, not implemented. I don't have hardware to test any of this.
    if config[CONF_SCROLL]:
        cg.add(var.set_scroll(True))
        cg.add(var.set_continuous(config[CONF_CONTINUOUS]))
        cg.add(var.set_scroll_speed(config[CONF_SCROLL_SPEED]))
        cg.add(var.set_scroll_dwell(config[CONF_SCROLL_DWELL]))
        cg.add(var.set_scroll_delay(int(config[CONF_SCROLL_DELAY] * config[CONF_SCROLL_SPEED].total_milliseconds)))

    if CONF_SECONDARY_DISPLAYS in config:
        for conf in config[CONF_SECONDARY_DISPLAYS]:
            disp = cg.new_Pvariable(conf[CONF_ID])
            await i2c.register_i2c_device(disp, conf)
            cg.add(var.add_secondary_display(disp))
