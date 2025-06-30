import esphome.codegen as cg
from esphome.core import CORE, coroutine_with_priority

CODEOWNERS = ["@esphome/core"]
AUTO_LOAD = ["md5"]

ota_base_ns = cg.esphome_ns.namespace("ota_base")


@coroutine_with_priority(52.0)
async def to_code(config):
    if CORE.is_esp32 and CORE.using_arduino:
        cg.add_library("Update", None)

    if CORE.is_rp2040 and CORE.using_arduino:
        cg.add_library("Updater", None)
