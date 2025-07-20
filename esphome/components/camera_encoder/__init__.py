import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_TYPE

CODEOWNERS = ["@DT-art1"]

AUTO_LOAD = ["camera"]

CONF_MCU_COUNT = "mcu_count"
CONF_QUALITY = "quality"
CONF_SUBSAMPLING = "subsampling"

DEFAULT_ENCODER = "default"

camera_ns = cg.esphome_ns.namespace("camera")
camera_encoder_ns = cg.esphome_ns.namespace("camera_encoder")

Encoder = camera_ns.class_("Encoder")
DefaultEncoder = camera_encoder_ns.class_("DefaultJPEGEncoder", Encoder)

DefaultQuality = camera_encoder_ns.enum("DefaultQuality")
DefaultSubsampling = camera_encoder_ns.enum("DefaultSubsampling")

CONF_DEFAULT_SUBSAMPLING_SELECTS = {
    "444": DefaultSubsampling.SUBSAMPLING_444,
    "420": DefaultSubsampling.SUBSAMPLING_420,
}
CONF_DEFAULT_QUALITY_SELECTS = {
    "BEST": DefaultQuality.QUALITY_BEST,
    "HIGH": DefaultQuality.QUALITY_HIGH,
    "MED": DefaultQuality.QUALITY_MED,
    "LOW": DefaultQuality.QUALITY_LOW,
}

DEFAULT_ENCODER_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(DefaultEncoder),
        cv.Optional(CONF_QUALITY, default="HIGH"): cv.enum(
            CONF_DEFAULT_QUALITY_SELECTS, upper=True
        ),
        cv.Optional(CONF_SUBSAMPLING, default="444"): cv.enum(
            CONF_DEFAULT_SUBSAMPLING_SELECTS, upper=True
        ),
        cv.Optional(CONF_MCU_COUNT, default=0): cv.int_range(0),
    }
)


CONFIG_SCHEMA = cv.typed_schema(
    {
        DEFAULT_ENCODER: DEFAULT_ENCODER_SCHEMA,
    },
    default_type=DEFAULT_ENCODER,
)


async def to_code(config):
    cg.add_build_flag("-DUSE_CAMERA_SW_JPEG_ENCODER")
    cg.add_library("dt-art1/jpegenc-pio", "1.0.0")

    if config[CONF_TYPE] == DEFAULT_ENCODER:
        cg.new_Pvariable(
            config[CONF_ID],
            config[CONF_QUALITY],
            config[CONF_SUBSAMPLING],
            config[CONF_MCU_COUNT],
        )
