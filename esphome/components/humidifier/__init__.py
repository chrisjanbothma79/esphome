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


# Remove before 2025.11.0
HUMIDIFER_SCHEMA = humidifer_schema(Humidifer)
HUMIDIFER_SCHEMA.add_extra(cv.deprecated_schema_constant("humidifer"))


async def setup_humidifer_core_(var, config):
    await setup_entity(var, config, "humidifer")

    visual = config[CONF_VISUAL]
    if (min_temp := visual.get(CONF_MIN_TEMPERATURE)) is not None:
        cg.add(var.set_visual_min_temperature_override(min_temp))
    if (max_temp := visual.get(CONF_MAX_TEMPERATURE)) is not None:
        cg.add(var.set_visual_max_temperature_override(max_temp))
    if (temp_step := visual.get(CONF_TEMPERATURE_STEP)) is not None:
        cg.add(
            var.set_visual_temperature_step_override(
                temp_step[CONF_TARGET_TEMPERATURE],
                temp_step[CONF_CURRENT_TEMPERATURE],
            )
        )
    if (min_humidity := visual.get(CONF_MIN_HUMIDITY)) is not None:
        cg.add(var.set_visual_min_humidity_override(min_humidity))
    if (max_humidity := visual.get(CONF_MAX_HUMIDITY)) is not None:
        cg.add(var.set_visual_max_humidity_override(max_humidity))

    if (mqtt_id := config.get(CONF_MQTT_ID)) is not None:
        mqtt_ = cg.new_Pvariable(mqtt_id, var)
        await mqtt.register_mqtt_component(mqtt_, config)

        if (action_state_topic := config.get(CONF_ACTION_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_action_state_topic(action_state_topic))
        if (away_command_topic := config.get(CONF_AWAY_COMMAND_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_away_command_topic(away_command_topic))
        if (away_state_topic := config.get(CONF_AWAY_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_away_state_topic(away_state_topic))
        if (
            current_temperature_state_topic := config.get(
                CONF_CURRENT_TEMPERATURE_STATE_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_current_temperature_state_topic(
                    current_temperature_state_topic
                )
            )
        if (
            current_humidity_state_topic := config.get(
                CONF_CURRENT_HUMIDITY_STATE_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_current_humidity_state_topic(
                    current_humidity_state_topic
                )
            )
        if (
            fan_mode_command_topic := config.get(CONF_FAN_MODE_COMMAND_TOPIC)
        ) is not None:
            cg.add(mqtt_.set_custom_fan_mode_command_topic(fan_mode_command_topic))
        if (fan_mode_state_topic := config.get(CONF_FAN_MODE_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_fan_mode_state_topic(fan_mode_state_topic))
        if (mode_command_topic := config.get(CONF_MODE_COMMAND_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_mode_command_topic(mode_command_topic))
        if (mode_state_topic := config.get(CONF_MODE_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_mode_state_topic(mode_state_topic))
        if (preset_command_topic := config.get(CONF_PRESET_COMMAND_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_preset_command_topic(preset_command_topic))
        if (preset_state_topic := config.get(CONF_PRESET_STATE_TOPIC)) is not None:
            cg.add(mqtt_.set_custom_preset_state_topic(preset_state_topic))
        if (
            swing_mode_command_topic := config.get(CONF_SWING_MODE_COMMAND_TOPIC)
        ) is not None:
            cg.add(mqtt_.set_custom_swing_mode_command_topic(swing_mode_command_topic))
        if (
            swing_mode_state_topic := config.get(CONF_SWING_MODE_STATE_TOPIC)
        ) is not None:
            cg.add(mqtt_.set_custom_swing_mode_state_topic(swing_mode_state_topic))
        if (
            target_temperature_command_topic := config.get(
                CONF_TARGET_TEMPERATURE_COMMAND_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_temperature_command_topic(
                    target_temperature_command_topic
                )
            )
        if (
            target_temperature_state_topic := config.get(
                CONF_TARGET_TEMPERATURE_STATE_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_temperature_state_topic(
                    target_temperature_state_topic
                )
            )
        if (
            target_temperature_high_command_topic := config.get(
                CONF_TARGET_TEMPERATURE_HIGH_COMMAND_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_temperature_high_command_topic(
                    target_temperature_high_command_topic
                )
            )
        if (
            target_temperature_high_state_topic := config.get(
                CONF_TARGET_TEMPERATURE_HIGH_STATE_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_temperature_high_state_topic(
                    target_temperature_high_state_topic
                )
            )
        if (
            target_temperature_low_command_topic := config.get(
                CONF_TARGET_TEMPERATURE_LOW_COMMAND_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_temperature_low_command_topic(
                    target_temperature_low_command_topic
                )
            )
        if (
            target_temperature_low_state_topic := config.get(
                CONF_TARGET_TEMPERATURE_LOW_STATE_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_temperature_state_topic(
                    target_temperature_low_state_topic
                )
            )
        if (
            target_humidity_command_topic := config.get(
                CONF_TARGET_HUMIDITY_COMMAND_TOPIC
            )
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_humidity_command_topic(
                    target_humidity_command_topic
                )
            )
        if (
            target_humidity_state_topic := config.get(CONF_TARGET_HUMIDITY_STATE_TOPIC)
        ) is not None:
            cg.add(
                mqtt_.set_custom_target_humidity_state_topic(
                    target_humidity_state_topic
                )
            )

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
        cv.Optional(CONF_MODE): cv.templatable(validate_humidifer_mode),
        cv.Optional(CONF_TARGET_TEMPERATURE): cv.templatable(cv.temperature),
        cv.Optional(CONF_TARGET_TEMPERATURE_LOW): cv.templatable(cv.temperature),
        cv.Optional(CONF_TARGET_TEMPERATURE_HIGH): cv.templatable(cv.temperature),
        cv.Optional(CONF_TARGET_HUMIDITY): cv.templatable(cv.percentage_int),
        cv.Optional(CONF_AWAY): cv.invalid("Use preset instead"),
        cv.Exclusive(CONF_FAN_MODE, "fan_mode"): cv.templatable(
            validate_humidifer_fan_mode
        ),
        cv.Exclusive(CONF_CUSTOM_FAN_MODE, "fan_mode"): cv.templatable(
            cv.string_strict
        ),
        cv.Exclusive(CONF_PRESET, "preset"): cv.templatable(validate_humidifer_preset),
        cv.Exclusive(CONF_CUSTOM_PRESET, "preset"): cv.templatable(cv.string_strict),
        cv.Optional(CONF_SWING_MODE): cv.templatable(validate_humidifer_swing_mode),
    }
)


@automation.register_action(
    "humidifer.control", ControlAction, HUMIDIFER_CONTROL_ACTION_SCHEMA
)
async def humidifer_control_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    if (mode := config.get(CONF_MODE)) is not None:
        template_ = await cg.templatable(mode, args, HumidiferMode)
        cg.add(var.set_mode(template_))
    if (target_temp := config.get(CONF_TARGET_TEMPERATURE)) is not None:
        template_ = await cg.templatable(target_temp, args, float)
        cg.add(var.set_target_temperature(template_))
    if (target_temp_low := config.get(CONF_TARGET_TEMPERATURE_LOW)) is not None:
        template_ = await cg.templatable(target_temp_low, args, float)
        cg.add(var.set_target_temperature_low(template_))
    if (target_temp_high := config.get(CONF_TARGET_TEMPERATURE_HIGH)) is not None:
        template_ = await cg.templatable(target_temp_high, args, float)
        cg.add(var.set_target_temperature_high(template_))
    if (target_humidity := config.get(CONF_TARGET_HUMIDITY)) is not None:
        template_ = await cg.templatable(target_humidity, args, float)
        cg.add(var.set_target_humidity(template_))
    if (fan_mode := config.get(CONF_FAN_MODE)) is not None:
        template_ = await cg.templatable(fan_mode, args, HumidiferFanMode)
        cg.add(var.set_fan_mode(template_))
    if (custom_fan_mode := config.get(CONF_CUSTOM_FAN_MODE)) is not None:
        template_ = await cg.templatable(custom_fan_mode, args, cg.std_string)
        cg.add(var.set_custom_fan_mode(template_))
    if (preset := config.get(CONF_PRESET)) is not None:
        template_ = await cg.templatable(preset, args, HumidiferPreset)
        cg.add(var.set_preset(template_))
    if (custom_preset := config.get(CONF_CUSTOM_PRESET)) is not None:
        template_ = await cg.templatable(custom_preset, args, cg.std_string)
        cg.add(var.set_custom_preset(template_))
    if (swing_mode := config.get(CONF_SWING_MODE)) is not None:
        template_ = await cg.templatable(swing_mode, args, HumidiferSwingMode)
        cg.add(var.set_swing_mode(template_))
    return var


@coroutine_with_priority(100.0)
async def to_code(config):
    cg.add_define("USE_HUMIDIFER")
    cg.add_global(humidifer_ns.using)
