from esphome import automation
import esphome.codegen as cg
from esphome.components.espnow import (
    CONF_DEFAULT,
    ESPNOW_APP_SCHEMA,
    ESPNowApp,
    espnow_ns,
    register_app,
    register_peer,
    validate_peer,
)
import esphome.config_validation as cv
from esphome.const import CONF_ELSE, CONF_ID, CONF_MAC_ADDRESS, CONF_THEN, CONF_WIFI
import esphome.final_validate as fv

CODEOWNERS = ["@nielsnl68"]

DEPENDENCIES = ["espnow"]


ESPNowFindPeer = espnow_ns.class_("ESPNowFindPeer", ESPNowApp)
FindPeerAction = espnow_ns.class_("FindPeerAction", automation.Action, cg.Component)


CONF_SUCCESS = "success"
CONF_FAILED = "failed"


CONFIG_SCHEMA = ESPNOW_APP_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(ESPNowFindPeer),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await register_app(var, config)


def _final_validate(config):
    full_config = fv.full_config.get()
    if CONF_WIFI in full_config:
        raise cv.Invalid(
            f"When you have {CONF_WIFI} configured, You can not add the 'espnow_find' component."
        )
    return config


FINAL_VALIDATE_SCHEMA = _final_validate


@automation.register_action(
    "espnow.peer.find",
    FindPeerAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(ESPNowFindPeer),
            cv.Optional(CONF_MAC_ADDRESS, default=CONF_DEFAULT): validate_peer,
            cv.Optional(CONF_SUCCESS): automation.validate_action_list,
            cv.Optional(CONF_FAILED): automation.validate_action_list,
        },
        key=CONF_MAC_ADDRESS,
    ),
)
async def channel_action(config, action_id, template_arg, args):
    print(template_arg)
    print(args)
    var = cg.new_Pvariable(action_id, template_arg)
    await cg.register_parented(var, config[CONF_ID])

    await register_peer(var, config, args)

    if CONF_SUCCESS in config:
        actions = await automation.build_action_list(
            config[CONF_THEN], template_arg, args
        )
        cg.add(var.add_success(actions))
    if CONF_FAILED in config:
        actions = await automation.build_action_list(
            config[CONF_ELSE], template_arg, args
        )
        cg.add(var.add_failed(actions))
    return var
