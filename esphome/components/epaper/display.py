from esphome import core, pins
import esphome.codegen as cg
from esphome.components import display, spi
import esphome.config_validation as cv
from esphome.const import (
    CONF_BUSY_PIN,
    CONF_DC_PIN,
    CONF_FULL_UPDATE_EVERY,
    CONF_ID,
    CONF_LAMBDA,
    CONF_MODEL,
    CONF_PAGES,
    CONF_RESET_DURATION,
    CONF_RESET_PIN,
)

DEPENDENCIES = ["spi"]

_epaper_ns = cg.esphome_ns.namespace("_epaper")
EPaperBase = _epaper_ns.class_(
    "EPaperBase", cg.PollingComponent, spi.SPIDevice, display.DisplayBuffer
)
EPaper = _epaper_ns.class_("EPaper", EPaperBase)
EPaperBWR = _epaper_ns.class_(
    "EPaperBWR", EPaperBase
)
EPaper7C = _epaper_ns.class_("EPaper7C", EPaperBase)
EPaperTypeA = _epaper_ns.class_(
    "EPaperTypeA", EPaper
)
Epaper1P54INBV2 = _epaper_ns.class_(
    "EPaper1P54InBV2", EPaperBWR
)
EPaper2P7In = _epaper_ns.class_(
    "EPaper2P7In", EPaper
)
EPaper2P7InB = _epaper_ns.class_(
    "EPaper2P7InB", EPaperBWR
)
EPaper2P7InBV2 = _epaper_ns.class_(
    "EPaper2P7InBV2", EPaperBWR
)
EPaper2P7InV2 = _epaper_ns.class_(
    "EPaper2P7InV2", EPaper
)
EPaper2P9InB = _epaper_ns.class_(
    "EPaper2P9InB", EPaper
)
EPaper2P9InBV3 = _epaper_ns.class_(
    "EPaper2P9InBV3", EPaper
)
EPaper2P9InV2R2 = _epaper_ns.class_(
    "EPaper2P9InV2R2", EPaper
)
GDEW029T5 = _epaper_ns.class_("GDEW029T5", EPaper)
GDEY029T94 = _epaper_ns.class_("GDEY029T94", EPaper)
EPaper2P9InDKE = _epaper_ns.class_(
    "EPaper2P9InDKE", EPaper
)
GDEY042T81 = _epaper_ns.class_("GDEY042T81", EPaper)
EPaper2P9InD = _epaper_ns.class_(
    "EPaper2P9InD", EPaper
)
EPaper4P2In = _epaper_ns.class_(
    "EPaper4P2In", EPaper
)
EPaper4P2InBV2 = _epaper_ns.class_(
    "EPaper4P2InBV2", EPaper
)
EPaper4P2InBV2BWR = _epaper_ns.class_(
    "EPaper4P2InBV2BWR", EPaperBWR
)
EPaper5P8In = _epaper_ns.class_(
    "EPaper5P8In", EPaper
)
EPaper5P8InV2 = _epaper_ns.class_(
    "EPaper5P8InV2", EPaper
)
EPaper7P3InF = _epaper_ns.class_(
    "EPaper7P3InF", EPaper7C
)
EPaper7P5In = _epaper_ns.class_(
    "EPaper7P5In", EPaper
)
EPaper7P5InBC = _epaper_ns.class_(
    "EPaper7P5InBC", EPaper
)
EPaper7P5InBV2 = _epaper_ns.class_(
    "EPaper7P5InBV2", EPaper
)
EPaper7P5InBV3 = _epaper_ns.class_(
    "EPaper7P5InBV3", EPaper
)
EPaper7P5InBV3BWR = _epaper_ns.class_(
    "EPaper7P5InBV3BWR", EPaperBWR
)
EPaper7P5InV2 = _epaper_ns.class_(
    "EPaper7P5InV2", EPaper
)
EPaper7P5InV2alt = _epaper_ns.class_(
    "EPaper7P5InV2alt", EPaper
)
EPaper7P5InV2P = _epaper_ns.class_(
    "EPaper7P5InV2P", EPaper
)
EPaper7P5InHDB = _epaper_ns.class_(
    "EPaper7P5InHDB", EPaper
)
EPaper2P13InDKE = _epaper_ns.class_(
    "EPaper2P13InDKE", EPaper
)
EPaper2P13InV2 = _epaper_ns.class_(
    "EPaper2P13InV2", EPaper
)
EPaper2P13InV3 = _epaper_ns.class_(
    "EPaper2P13InV3", EPaper
)
EPaper13P3InK = _epaper_ns.class_(
    "EPaper13P3InK", EPaper
)
GDEW0154M09 = _epaper_ns.class_("GDEW0154M09", EPaper)

EPaperTypeAModel = _epaper_ns.enum("EPaperTypeAModel")
EPaperTypeBModel = _epaper_ns.enum("EPaperTypeBModel")

MODELS = {
    "1.54in": ("a", EPaperTypeAModel._EPAPER_1_54_IN),
    "1.54inv2": ("a", EPaperTypeAModel._EPAPER_1_54_IN_V2),
    "1.54inv2-b": ("b", Epaper1P54INBV2),
    "2.13in": ("a", EPaperTypeAModel._EPAPER_2_13_IN),
    "2.13inv2": ("a", EPaperTypeAModel._EPAPER_2_13_IN_V2),
    "2.13in-ttgo": ("a", EPaperTypeAModel.TTGO_EPAPER_2_13_IN),
    "2.13in-ttgo-b1": ("a", EPaperTypeAModel.TTGO_EPAPER_2_13_IN_B1),
    "2.13in-ttgo-b73": ("a", EPaperTypeAModel.TTGO_EPAPER_2_13_IN_B73),
    "2.13in-ttgo-b74": ("a", EPaperTypeAModel.TTGO_EPAPER_2_13_IN_B74),
    "2.90in": ("a", EPaperTypeAModel._EPAPER_2_9_IN),
    "2.90inv2": ("a", EPaperTypeAModel._EPAPER_2_9_IN_V2),
    "gdew029t5": ("c", GDEW029T5),
    "2.70in": ("b", EPaper2P7In),
    "2.70in-b": ("b", EPaper2P7InB),
    "2.70in-bv2": ("b", EPaper2P7InBV2),
    "2.70inv2": ("b", EPaper2P7InV2),
    "2.90in-b": ("b", EPaper2P9InB),
    "2.90in-bv3": ("b", EPaper2P9InBV3),
    "gdey029t94": ("c", GDEY029T94),
    "2.90inv2-r2": ("c", EPaper2P9InV2R2),
    "2.90in-d": ("b", EPaper2P9InD),
    "2.90in-dke": ("c", EPaper2P9InDKE),
    "gdey042t81": ("c", GDEY042T81),
    "4.20in": ("b", EPaper4P2In),
    "4.20in-bv2": ("b", EPaper4P2InBV2),
    "4.20in-bv2-bwr": ("b", EPaper4P2InBV2BWR),
    "5.83in": ("b", EPaper5P8In),
    "5.83inv2": ("b", EPaper5P8InV2),
    "7.30in-f": ("b", EPaper7P3InF),
    "7.50in": ("b", EPaper7P5In),
    "7.50in-bv2": ("b", EPaper7P5InBV2),
    "7.50in-bv3": ("b", EPaper7P5InBV3),
    "7.50in-bv3-bwr": ("b", EPaper7P5InBV3BWR),
    "7.50in-bc": ("b", EPaper7P5InBC),
    "7.50inv2": ("b", EPaper7P5InV2),
    "7.50inv2alt": ("b", EPaper7P5InV2alt),
    "7.50inv2p": ("c", EPaper7P5InV2P),
    "7.50in-hd-b": ("b", EPaper7P5InHDB),
    "2.13in-ttgo-dke": ("c", EPaper2P13InDKE),
    "2.13inv3": ("c", EPaper2P13InV3),
    "1.54in-m5coreink-m09": ("b", GDEW0154M09),
    "13.3in-k": ("b", EPaper13P3InK),
}

RESET_PIN_REQUIRED_MODELS = ("2.13inv2", "2.13in-ttgo-b74")


def validate_full_update_every_only_types_ac(value):
    if CONF_FULL_UPDATE_EVERY not in value:
        return value
    if MODELS[value[CONF_MODEL]][0] == "b":
        full_models = []
        for key, val in sorted(MODELS.items()):
            if val[0] != "b":
                full_models.append(key)
        raise cv.Invalid(
            "The 'full_update_every' option is only available for models "
            + ", ".join(full_models)
        )
    return value


def validate_reset_pin_required(config):
    if config[CONF_MODEL] in RESET_PIN_REQUIRED_MODELS and CONF_RESET_PIN not in config:
        raise cv.Invalid(
            f"'{CONF_RESET_PIN}' is required for model {config[CONF_MODEL]}"
        )
    return config


CONFIG_SCHEMA = cv.All(
    display.FULL_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(EPaperBase),
            cv.Required(CONF_DC_PIN): pins.gpio_output_pin_schema,
            cv.Required(CONF_MODEL): cv.one_of(*MODELS, lower=True),
            cv.Optional(CONF_RESET_PIN): pins.gpio_output_pin_schema,
            cv.Optional(CONF_BUSY_PIN): pins.gpio_input_pin_schema,
            cv.Optional(CONF_FULL_UPDATE_EVERY): cv.int_range(min=1, max=4294967295),
            cv.Optional(CONF_RESET_DURATION): cv.All(
                cv.positive_time_period_milliseconds,
                cv.Range(max=core.TimePeriod(milliseconds=500)),
            ),
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(spi.spi_device_schema()),
    validate_full_update_every_only_types_ac,
    validate_reset_pin_required,
    cv.has_at_most_one_key(CONF_PAGES, CONF_LAMBDA),
)

FINAL_VALIDATE_SCHEMA = spi.final_validate_device_schema(
    "_epaper", require_miso=False, require_mosi=True
)


async def to_code(config):
    model_type, model = MODELS[config[CONF_MODEL]]
    if model_type == "a":
        rhs = EPaperTypeA.new(model)
        var = cg.Pvariable(config[CONF_ID], rhs, EPaperTypeA)
    elif model_type in ("b", "c"):
        rhs = model.new()
        var = cg.Pvariable(config[CONF_ID], rhs, model)
    else:
        raise NotImplementedError()

    await display.register_display(var, config)
    await spi.register_spi_device(var, config)

    dc = await cg.gpio_pin_expression(config[CONF_DC_PIN])
    cg.add(var.set_dc_pin(dc))

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(display.DisplayRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
    if CONF_RESET_PIN in config:
        reset = await cg.gpio_pin_expression(config[CONF_RESET_PIN])
        cg.add(var.set_reset_pin(reset))
    if CONF_BUSY_PIN in config:
        reset = await cg.gpio_pin_expression(config[CONF_BUSY_PIN])
        cg.add(var.set_busy_pin(reset))
    if CONF_FULL_UPDATE_EVERY in config:
        cg.add(var.set_full_update_every(config[CONF_FULL_UPDATE_EVERY]))
    if CONF_RESET_DURATION in config:
        cg.add(var.set_reset_duration(config[CONF_RESET_DURATION]))
