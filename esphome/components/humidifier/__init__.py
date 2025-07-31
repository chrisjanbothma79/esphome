from esphome import automation
import esphome.codegen as cg
from esphome.components import mqtt, web_server
import esphome.config_validation as cv
from esphome.const import (
    CONF_ENTITY_CATEGORY,
    CONF_ICON,
    CONF_ID,
    CONF_MODE,
    CONF_MODE_COMMAND_TOPIC,
    CONF_MODE_STATE_TOPIC,
    CONF_MQTT_ID,
    CONF_ON_CONTROL,
    CONF_ON_STATE,
    CONF_TARGET_HUMIDITY_COMMAND_TOPIC,
    CONF_TARGET_HUMIDITY_STATE_TOPIC,
    CONF_TRIGGER_ID,
    CONF_VISUAL,
    CONF_WEB_SERVER,
)
from esphome.core import CORE, coroutine_with_priority
from esphome.core.entity_helpers import entity_duplicate_validator, setup_entity
from esphome.cpp_generator import MockObjClass

TOPICS = [
    CONF_ACTION_TOPIC,
    CONF_STATE_TOPIC,
    CONF_COMMAND_TOPIC,
    CONF_CURRENT_HUMIDITY_TOPIC,
    CONF_TARGET_HUMIDITY_STATE_TOPIC,
    CONF_TARGET_HUMIDITY_COMMAND_TOPIC,
    CONF_MODE_STATE_TOPIC,
    CONF_MODE_COMMAND_TOPIC,
]


IS_PLATFORM_COMPONENT = True

CODEOWNERS = ["@redstone99"]
humidifer_ns = cg.esphome_ns.namespace("humidifer")
Humidifer = humidifer_ns.class_("Humidifer", cg.EntityBase)

DeviceClass = humidifer_ns.enum("DeviceClass")
DEVICE_CLASSES = {
    "HUMIDIFIER": DeviceClass.HUMIDIFER,
    "DEHUMIDIFIER": DeviceClass.DEHUMIDIFIER,
}
validate_device_class = cv.enum(DEVICE_CLASSES, upper=True)

#HumidifierMode = humidifier_ns.enum("HumidifierMode")
#HUMIDIFIER_MODES = {
#    "OFF": HumidifierMode.HUMIDIFIER_MODE_OFF,
#    "HEAT_COOL": HumidifierMode.HUMIDIFIER_MODE_HEAT_COOL,
#    "COOL": HumidifierMode.HUMIDIFIER_MODE_COOL,
#}
#validate_humidifier_mode = cv.enum(HUMIDIFIER_MODES, upper=True)




# Actions
ControlAction = humidifer_ns.class_("HumidifierAction", automation.Action)
TurnOnAction = humidifier_ns.class_("TurnOnAction", automation.Action)
TurnOffAction = humidifier_ns.class_("TurnOffAction", automation.Action)

_HUMIDIFER_SCHEMA = (
    cv.ENTITY_BASE_SCHEMA.extend(web_server.WEBSERVER_SORTING_SCHEMA)
    .extend(cv.MQTT_COMMAND_COMPONENT_SCHEMA)
    .extend(
        {
            cv.OnlyWith(CONF_MQTT_ID, "mqtt"): cv.declare_id(
                mqtt.MQTTHumidiferComponent
            ),
            cv.Optional(CONF_VISUAL, default={}): cv.Schema(
                {
                    cv.Optional(CONF_MIN_HUMIDITY): cv.percentage_int,
                    cv.Optional(CONF_MAX_HUMIDITY): cv.percentage_int,
                }
            ),
            cv.Optional(CONF_ACTION_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_STATE_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_COMMAND_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_CURRENT_HUMIDITY_STATE_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_TARGET_HUMIDITY_STATE_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_TARGET_HUMIDITY_COMMAND_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_MODE_STATE_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_MODE_COMMAND_TOPIC): cv.All(
                cv.requires_component("mqtt"), cv.publish_topic
            ),
            cv.Optional(CONF_ON_CONTROL): automation.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(ControlTrigger),
                }
            ),
            cv.Optional(CONF_ON_STATE): automation.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(StateTrigger),
                }
            ),
        }
    )
)
_HUMIDIFER_SCHEMA.add_extra(entity_duplicate_validator("humidifer"))


def humidifer_schema(
    class_: MockObjClass,
    *,
    entity_category: str = cv.UNDEFINED,
    icon: str = cv.UNDEFINED,
) -> cv.Schema:
    schema = {
        cv.GenerateID(): cv.declare_id(class_),
    }

    for key, default, validator in [
        (CONF_ENTITY_CATEGORY, entity_category, cv.entity_category),
        (CONF_ICON, icon, cv.icon),
    ]:
        if default is not cv.UNDEFINED:
            schema[cv.Optional(key, default=default)] = validator

    return _HUMIDIFER_SCHEMA.extend(schema)


HUMIDIFER_SCHEMA = humidifer_schema(Humidifer)


async def setup_humidifer_core_(var, config):
    await setup_entity(var, config, "humidifer")

    visual = config[CONF_VISUAL]
    if (min_humidity := visual.get(CONF_MIN_HUMIDITY)) is not None:
        cg.add(var.set_visual_min_humidity_override(min_humidity))
    if (max_humidity := visual.get(CONF_MAX_HUMIDITY)) is not None:
        cg.add(var.set_visual_max_humidity_override(max_humidity))

    if (mqtt_id := config.get(CONF_MQTT_ID)) is not None:
        mqtt_ = cg.new_Pvariable(mqtt_id, var)
        await mqtt.register_mqtt_component(mqtt_, config)

        if (action_topic := config.get(CONF_ACTION_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_action_topic(action_topic))
        if (state_topic := config.get(CONF_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_state_topic(state_topic))
        if (command_topic := config.get(CONF_COMMAND_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_command_topic(command_topic))
        if (current_humidity_state_topic := config.get(CONF_CURRENT_HUMIDITY_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_current_humidity_state_topic(current_humidity_state_topic))
        if (target_humidity_state_topic := config.get(CONF_TARGET_HUMIDITY_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_target_humidity_state_topic(target_humidity_state_topic))
        if (target_humidity_command_topic := config.get(CONF_TARGET_HUMIDITY_COMMAND_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_target_humidity_command_topic(target_humidity_command_topic))
        if (mode_state_topic := config.get(CONF_MODE_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_mode_state_topic(mode_state_topic))
        if (mode_command_topic := config.get(CONF_MODE_COMMAND_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_mode_command_topic(mode_command_topic))
            
    for conf in config.get(CONF_ON_STATE, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(
            trigger, [(Humidifer.operator("ref"), "x")], conf
        )

    for conf in config.get(CONF_ON_CONTROL, []):
        trigger = cg.new_Pvariable(conf[CONF_TRIGGER_ID], var)
        await automation.build_automation(
            trigger, [(HumidiferCall.operator("ref"), "x")], conf
        )

    if web_server_config := config.get(CONF_WEB_SERVER):
        await web_server.add_entity_config(var, web_server_config)

async def register_humidifer(var, config):
    if not CORE.has_id(config[CONF_ID]):
        var = cg.Pvariable(config[CONF_ID], var)
    cg.add(cg.App.register_humidifer(var))
    CORE.register_platform_component("humidifer", var)
    await setup_humidifer_core_(var, config)

async def new_humidifer(config, *args):
    var = cg.new_Pvariable(config[CONF_ID], *args)
    await register_humidifer(var, config)
    return var

HUMIDIFER_CONTROL_ACTION_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.use_id(Humidifer),
        #cv.Optional(CONF_MODE): cv.templatable(validate_humidifer_mode),
        cv.Optional(CONF_TARGET_HUMIDITY_LOW): cv.templatable(cv.humidity),
        cv.Optional(CONF_TARGET_HUMIDITY_HIGH): cv.templatable(cv.humidity),
    }
)
@automation.register_action(
    "humidifer.control", ControlAction, HUMIDIFER_CONTROL_ACTION_SCHEMA
)
async def humidifer_control_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    #if (mode := config.get(CONF_MODE)) is not None:
    #    template_ = await cg.templatable(mode, args, HumidiferMode)
    #    cg.add(var.set_mode(template_))
    if (target_temp_low := config.get(CONF_TARGET_HUMIDITY_LOW)) is not None:
        template_ = await cg.templatable(target_temp_low, args, float)
        cg.add(var.set_target_humidity_low(template_))
    if (target_temp_high := config.get(CONF_TARGET_HUMIDITY_HIGH)) is not None:
        template_ = await cg.templatable(target_temp_high, args, float)
        cg.add(var.set_target_humidity_high(template_))
    return var

@coroutine_with_priority(100.0)
async def to_code(config):
    cg.add_define("USE_HUMIDIFER")
    cg.add_global(humidifer_ns.using)
