import esphome.codegen as cg
from esphome.components import microphone
from esphome.components.adc import validate_adc_pin
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


CONFIG_SCHEMA = cv.All(
    BASE_SCHEMA, cv.require_framework_version(esp_idf=cv.Version(5, 0, 0))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await microphone.register_microphone(var, config)

    pin_num = config[CONF_ADC_PIN][CONF_NUMBER]
    cg.add(var.set_adc_channel(pin_num))
    cg.add(var.set_sample_rate(config[CONF_SAMPLE_RATE]))
