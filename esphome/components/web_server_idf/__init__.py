from esphome.components.esp32 import add_idf_component, add_idf_sdkconfig_option
import esphome.config_validation as cv
from esphome.const import CONF_OTA
from esphome.core import CORE

CODEOWNERS = ["@dentra"]

CONFIG_SCHEMA = cv.All(
    cv.Schema({}),
    cv.only_with_esp_idf,
)


async def to_code(config):
    # Increase the maximum supported size of headers section in HTTP request packet to be processed by the server
    add_idf_sdkconfig_option("CONFIG_HTTPD_MAX_REQ_HDR_LEN", 1024)

    # Check if web_server OTA platform is configured
    ota_config = CORE.config.get(CONF_OTA, [])
    has_web_server_ota = any(
        platform.get("platform") == "web_server" for platform in ota_config
    )
    if has_web_server_ota:
        # Add multipart parser dependency for web server OTA
        add_idf_component(name="zorxx/multipart-parser", ref="1.0.1")
