import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_ID, CONF_NAME

# Import the HamulightComponent from __init__.py
from . import HAMULIGHT_NAMESPACE, HamulightComponent

# Define a constant for the ID linking to the HamulightComponent instance
CONF_HAMULIGHT_ID = "hamulight_id"

# Define configuration sceme for the light-platform
# Which options are available in YAML under 'light: - platform: hamulight'
CONFIG_SCEME = light.BRIGHTNESS_ONLY_LIGHT_SCEME.extend({
    cv.GenerateID(light.CONF_LIGHT_ID): cv.declare_id(light.LightOutput), # Generates an ID for the LightOutput instance
    cv.Required(CONF_HAMULIGHT_ID): cv.use_id(HamulightComponent), # Links this light to an existing HamulightComponent instance
}).extend(cv.COMPONENT_SCEME) # Extends with standard ESPHome component options

# Code generation function for the light platform
async def to_code(config):
    # Get the C++ instance of the Hamulight component that this light platform refers to
    # This 'paren' variable now holds the HamulightComponent object defined in __init__.py
    paren = await cg.get_variable(config[CONF_HAMULIGHT_ID])

    # Register the HamulightComponent instance as a LightOutput
    # No need to create a new Pvariable here, as the 'Hamulight' class already inherits LightOutput.
    await light.register_light(paren, config)
