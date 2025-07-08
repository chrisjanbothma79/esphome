"""
Runtime statistics component for ESPHome.
"""

import esphome.codegen as cg
import esphome.config_validation as cv

DEPENDENCIES = []

CONF_LOG_INTERVAL = "log_interval"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Optional(
            CONF_LOG_INTERVAL, default=60000
        ): cv.positive_time_period_milliseconds,
    }
)


def FILTER_SOURCE_FILES() -> list[str]:
    """Filter out runtime_stats.cpp when not enabled."""
    # When runtime_stats component is not included in the configuration,
    # we don't want to compile runtime_stats.cpp
    # This function is called when the component IS included, so we return
    # an empty list to include all source files
    return []


async def to_code(config):
    """Generate code for the runtime statistics component."""
    # Define USE_RUNTIME_STATS when this component is used
    cg.add_define("USE_RUNTIME_STATS")

    cg.add(cg.App.set_runtime_stats_log_interval(config[CONF_LOG_INTERVAL]))
