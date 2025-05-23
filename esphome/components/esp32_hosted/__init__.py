import os

from esphome.components import esp32
import esphome.config_validation as cv
from esphome.const import CONF_VARIANT, KEY_CORE, KEY_FRAMEWORK_VERSION
from esphome.core import CORE

CODEOWNERS = ["@swoboda1337"]

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.Optional(CONF_VARIANT): cv.one_of(*esp32.VARIANTS, upper=True),
        }
    ),
)


async def to_code(config):
    framework_ver: cv.Version = CORE.data[KEY_CORE][KEY_FRAMEWORK_VERSION]

    os.environ["ESP_IDF_VERSION"] = f"{framework_ver.major}.{framework_ver.minor}"

    esp32.add_idf_sdkconfig_option(
        f"CONFIG_SLAVE_IDF_TARGET_{config[CONF_VARIANT]}",  # NOLINT
        True,
    )

    esp32.add_idf_component(
        name="esp_wifi_remote",
        repo="https://github.com/espressif/esp-wifi-remote.git",
        path="components/esp_wifi_remote",
    )

    esp32.add_extra_script(
        "post",
        "esp32_hosted.py",
        os.path.join(os.path.dirname(__file__), "esp32_hosted.py.script"),
    )
