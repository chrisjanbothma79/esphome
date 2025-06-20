from esphome import automation, core
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_PAYLOAD, CONF_WIFI
import esphome.final_validate as fv

CODEOWNERS = ["@nielsnl68", "@jesserockz"]


espnow_ns = cg.esphome_ns.namespace("espnow")
ESPNowComponent = espnow_ns.class_("ESPNowComponent", cg.Component)
ESPNowInterface = espnow_ns.class_(
    "ESPNowInterface", cg.Parented.template(ESPNowComponent)
)

ESPNowDefaultTrigger = espnow_ns.class_(
    "ESPNowDefaultTrigger",
    automation.Trigger.template(),
)

SendAction = espnow_ns.class_("SendAction", automation.Action)
SetChannelAction = espnow_ns.class_("SetChannelAction", automation.Action)
NewPeerAction = espnow_ns.class_("NewPeerAction", automation.Action)
DelPeerAction = espnow_ns.class_("DelPeerAction", automation.Action)

CONF_AUTO_ADD_PEER = "auto_add_peer"
CONF_RESPONSE_TIMEOUT = "response_timeout"


CONF_ESPNOW = "espnow"
CONF_MAKE_DEFAULT = "make_default"
CONF_PEERS = "peers"
CONF_WIFI_CHANNEL = "wifi_channel"

CONF_ON_NEW_PEER = "on_new_peer"

CONF_ON_RECEIVED = "on_received"
CONF_ON_BROADCASTED = "on_broadcasted"

CONF_ON_SENT_SUCCEED = "on_sent_succeed"
CONF_ON_SENT_FAILED = "on_sent_failed"

CONF_PEER_ADDRESS = "peer_address"


ESPNowTriggers = espnow_ns.enum("ESPNowTriggers", is_class=True)
ALLOWED_TRIGGER_LIST = {
    CONF_ON_NEW_PEER: ESPNowTriggers.ON_NEW_PEER,
    CONF_ON_RECEIVED: ESPNowTriggers.ON_RECEIVED,
    CONF_ON_BROADCASTED: ESPNowTriggers.ON_BROADCASTED,
    CONF_ON_SENT_SUCCEED: ESPNowTriggers.ON_SUCCEED,
    CONF_ON_SENT_FAILED: ESPNowTriggers.ON_FAILED,
}


validate_channel = cv.int_range(1, 14)


def espnow_hex(peer_address):
    it = reversed(peer_address.parts)
    num = "".join(f"{part:02X}" for part in it)
    return cg.RawExpression(f"0x{num}ULL")


CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ESPNowComponent),
            cv.Optional(CONF_WIFI_CHANNEL): validate_channel,
            cv.Optional(CONF_AUTO_ADD_PEER): cv.boolean,
            cv.Optional(CONF_PEERS): cv.ensure_list(cv.mac_address),
            cv.Optional(CONF_ON_NEW_PEER): automation.validate_automation(single=True),
            cv.Optional(CONF_ON_RECEIVED): automation.validate_automation(single=True),
            cv.Optional(CONF_ON_BROADCASTED): automation.validate_automation(
                single=True
            ),
            cv.Optional(CONF_ON_SENT_SUCCEED): automation.validate_automation(
                single=True
            ),
            cv.Optional(CONF_ON_SENT_FAILED): automation.validate_automation(
                single=True
            ),
        },
    ).extend(cv.COMPONENT_SCHEMA),
    cv.only_on_esp32,
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if core.CORE.using_arduino:
        cg.add_library("WiFi", None)

    cg.add_define("USE_ESPNOW")
    if CONF_WIFI_CHANNEL in config:
        cg.add(var.set_wifi_channel(config[CONF_WIFI_CHANNEL]))

    if CONF_AUTO_ADD_PEER in config:
        cg.add(var.set_auto_add_peer(config[CONF_AUTO_ADD_PEER]))
    if CONF_RESPONSE_TIMEOUT in config:
        cg.add(var.set_confirmation_timeout(config[CONF_RESPONSE_TIMEOUT]))

    def_peer = 0
    for peer in config.get(CONF_PEERS, []):
        peer = espnow_hex(peer)
        cg.add(var.add_peer(peer))
        if def_peer == 0:
            def_peer = peer
    cg.add(var.set_default_peer_address(def_peer))

    for key, code in ALLOWED_TRIGGER_LIST.items():
        if conf := config.get(key):
            await automation.build_automation(
                var.get_trigger(code),
                [
                    (cg.uint64, "peer_address"),
                    (cg.std_vector.template(cg.uint8), "payload"),
                    (cg.int_, "errorcode"),
                ],
                conf,
            )


def _final_validate(config):
    full_config = fv.full_config.get()
    if CONF_WIFI_CHANNEL in config and CONF_WIFI in full_config:
        raise cv.Invalid(
            f"When you have {CONF_WIFI} configured, You can not set the {CONF_WIFI_CHANNEL} variable."
        )
    return config


FINAL_VALIDATE_SCHEMA = _final_validate


# ========================================== A C T I O N S ================================================


def validate_peer(value):
    if isinstance(value, cv.Lambda):
        return cv.returning_lambda(value)
    return cv.mac_address(value)


def validate_raw_data(value):
    if isinstance(value, str):
        return value.encode("utf-8")
    if isinstance(value, list):
        return cv.Schema([cv.hex_uint8_t])(value)
    raise cv.Invalid(
        f"'{CONF_PAYLOAD}' must either be a string wrapped in quotes or a list of bytes"
    )


async def register_peer(var, config, args):
    peer = config.get(CONF_PEER_ADDRESS, 0xFFFFFFFFFFFF)
    if isinstance(peer, core.MACAddress):
        peer = espnow_hex(peer)

    template_ = await cg.templatable(peer, args, cg.uint64)
    cg.add(var.set_peer_address(template_))


SEND_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(ESPNowComponent),
        cv.Optional(CONF_PEER_ADDRESS): validate_peer,
        cv.Required(CONF_PAYLOAD): cv.templatable(validate_raw_data),
    }
)


@automation.register_action(
    "espnow.send",
    SendAction,
    SEND_SCHEMA,
)
@automation.register_action(
    "espnow.broadcast",
    SendAction,
    cv.maybe_simple_value(
        SEND_SCHEMA.extend(
            {
                cv.Optional(CONF_PEER_ADDRESS, default=0xFFFFFFFFFFFF): cv.uint64_t,
            }
        ),
        key=CONF_PAYLOAD,
    ),
)
async def send_action(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])

    if CONF_PEER_ADDRESS in config:
        await register_peer(var, config, args)

    data = config.get(CONF_PAYLOAD, [])
    if isinstance(data, bytes):
        data = list(data)

    vec_ = cg.std_vector.template(cg.uint8)
    templ = await cg.templatable(data, args, vec_, vec_)
    cg.add(var.set_payload(templ))

    return var


@automation.register_action(
    "espnow.peer.add",
    NewPeerAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(ESPNowComponent),
            cv.Required(CONF_PEER_ADDRESS): validate_peer,
            cv.Optional(CONF_MAKE_DEFAULT): cv.boolean,
        },
        key=CONF_PEER_ADDRESS,
    ),
)
@automation.register_action(
    "espnow.peer.del",
    DelPeerAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(ESPNowComponent),
            cv.Required(CONF_PEER_ADDRESS): validate_peer,
        },
        key=CONF_PEER_ADDRESS,
    ),
)
async def peer_action(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    await register_peer(var, config, args)
    if config.get(CONF_MAKE_DEFAULT, False):
        cg.add(var.make_default())

    return var


@automation.register_action(
    "espnow.channel.set",
    SetChannelAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(ESPNowComponent),
            cv.Required(CONF_WIFI_CHANNEL): cv.templatable(validate_channel),
        },
        key=CONF_WIFI_CHANNEL,
    ),
)
async def channel_action(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])
    template_ = await cg.templatable(config[CONF_WIFI_CHANNEL], args, cg.uint8)
    cg.add(var.set_channel(template_))
    return var
