import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID, CONF_NAME

# Import the HamulightComponent from __init__.py
from . import HAMULIGHT_NAMESPACE, HamulightComponent

# Define configuration sceme for the light-platform
# Which options are available in YAML under 'light: - platform: hamulight'
CONFIG_SCEME = light.BRIGHTNESS_ONLY_LIGHT_SCEME.extend({
    cv.GenerateID(): cv.declare_id(light.LightOutput),           # Generates an ID for the LightOutput instance
    cv.Required(CONF_ID): cv.use_id(HamulightComponent),         # Links the light-platform to the hamulight-component
}).extend(cv.COMPONENT_SCEME)

# Generate the C++ code for the light-platform
async def to_code(config):
    # Get the hamulight-component C++ instance, to which the light-platform refers
    paren = await cg.get_variable(config[CONF_ID])

    # Create a new C++ instance of the LightOutput class (from hamulight_component.h)
    var = cg.new_Pvariable(config[light.CONF_LIGHT_ID], paren)
    await light.register_light(var, config)
