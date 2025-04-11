"""OpenThread information components for ESPHome."""

import esphome.codegen as cg
import esphome.config_validation as cv

DEPENDENCIES = ["zephyr_openthread"]
AUTO_LOAD = ["text_sensor"]

MULTI_CONF = True

# Create the namespace for our component
openthread_info_ns = cg.esphome_ns.namespace("openthread_info")

# Empty top-level schema
CONFIG_SCHEMA = cv.Schema({})

async def to_code(config):
    # This component uses std::optional etc, requiring C++17
    cg.add_build_flag("-std=gnu++17")
