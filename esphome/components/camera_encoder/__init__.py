import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_TYPE

CODEOWNERS = ["@DT-art1"]

CONF_DEFAULT_MCU_COUNT = "mcu_count"
CONF_DEFAULT_QUALITY = "quality"
CONF_DEFAULT_SUBSAMPLING = "subsampling"

DEFAULT_ENCODER = "default"

camera_ns = cg.esphome_ns.namespace("camera")
camera_encoder_ns = cg.esphome_ns.namespace("camera_encoder")

Encoder = camera_ns.class_("Encoder")
DefaultEncoder = camera_encoder_ns.class_("DefaultJPEGEncoder")

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

BASE_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Encoder),
    }
)

DEFAULT_ENCODER_SCHEMA = cv.Schema(
    {
        cv.Optional(CONF_DEFAULT_QUALITY, default="HIGH"): cv.enum(
            CONF_DEFAULT_QUALITY_SELECTS, upper=True
        ),
        cv.Optional(CONF_DEFAULT_SUBSAMPLING, default="444"): cv.enum(
            CONF_DEFAULT_SUBSAMPLING_SELECTS, upper=True
        ),
        cv.Optional(CONF_DEFAULT_MCU_COUNT, default=0): cv.int_range(0),
    }
)


CONFIG_SCHEMA = cv.typed_schema(
    {
        DEFAULT_ENCODER: BASE_SCHEMA.extend(DEFAULT_ENCODER_SCHEMA),
    },
    default_type=DEFAULT_ENCODER,
)


async def to_code(config):
    cg.add_build_flag("-DUSE_CAMERA_SW_JPEG_ENCODER")
    cg.add_library("dt-art1/jpegenc-pio", "1.0.0")

    if config[CONF_TYPE] == DEFAULT_ENCODER:
        cg.Pvariable(
            config[CONF_ID],
            DefaultEncoder.new(
                config[CONF_DEFAULT_QUALITY],
                config[CONF_DEFAULT_SUBSAMPLING],
                config[CONF_DEFAULT_MCU_COUNT],
            ),
        )
