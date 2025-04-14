import esphome.codegen as cg
from esphome.components import esp32, microphone
from esphome.components.adc import ESP32_VARIANT_ADC1_PIN_TO_CHANNEL, validate_adc_pin
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_NUMBER, CONF_SAMPLE_RATE

CODEOWNERS = ["@calumapplepie"]

DEPENDENCIES = ["esp32"]


CONF_ADC_PIN = "adc_pin"
CONF_ADC_TYPE = "adc_type"
adc_microphone_ns = cg.esphome_ns.namespace("adc_microphone")

ADCAudioMicrophone = adc_microphone_ns.class_(
    "ADCAudioMicrophone", microphone.Microphone, cg.Component
)

BASE_SCHEMA = microphone.MICROPHONE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ADCAudioMicrophone),
        cv.Optional(CONF_SAMPLE_RATE, default=20000): cv.int_range(min=1),
        cv.Required(CONF_ADC_PIN): validate_adc_pin,
    }
).extend(cv.COMPONENT_SCHEMA)


CONFIG_SCHEMA = BASE_SCHEMA


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await microphone.register_microphone(var, config)

    variant = esp32.get_esp32_variant()
    pin_num = config[CONF_ADC_PIN][CONF_NUMBER]
    channel = ESP32_VARIANT_ADC1_PIN_TO_CHANNEL[variant][pin_num]
    cg.add(var.set_adc_channel(channel))
