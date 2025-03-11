import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import socket
from esphome.const import (
    CONF_ID,
    CONF_PASSWORD,
    CONF_PORT,
    CONF_USERNAME,
    CONF_BROKER,
    CONF_CLIENT_ID,
)
from esphome.core import CORE
from esphome import automation
from esphome.automation import Action, Trigger

# Define our own constants
CONF_KEEP_ALIVE = "keep_alive"
CONF_AUTO_RECONNECT = "auto_reconnect"
CONF_ON_MESSAGE = "on_message"
CONF_TOPIC = "topic"
CONF_QOS = "qos"
CONF_PAYLOAD = "payload"
CONF_RETAIN = "retain"
CONF_SIMPLE_MQTT_ID = "simple_mqtt_id"
CONF_TRIGGER_ID = "trigger_id"

DEPENDENCIES = ["socket"]
AUTO_LOAD = ["socket"]

# If we're on nRF52, we need OpenThread for IPv6 support
if CORE.is_esp32:
    # ESP32 has IPv6 support built-in
    pass
elif CORE.is_esp8266:
    # ESP8266 doesn't support IPv6
    pass
elif CORE.is_nrf52:
    # For nRF52, use openthread_zephyr
    DEPENDENCIES.append("openthread_zephyr")
    AUTO_LOAD.append("openthread_zephyr")

simple_mqtt_ns = cg.esphome_ns.namespace("simple_mqtt")
SimpleMQTTClient = simple_mqtt_ns.class_("SimpleMQTTClient", cg.Component)
MQTTMessageTrigger = simple_mqtt_ns.class_(
    "MQTTMessageTrigger", automation.Trigger.template(cg.std_string, cg.std_string)
)
MQTTPublishAction = simple_mqtt_ns.class_("MQTTPublishAction", automation.Action)

# Config schemas
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SimpleMQTTClient),
        cv.Required(CONF_BROKER): cv.string,
        cv.Optional(CONF_PORT, default=1883): cv.port,
        cv.Optional(CONF_USERNAME): cv.string,
        cv.Optional(CONF_PASSWORD): cv.string,
        cv.Optional(CONF_CLIENT_ID): cv.string,
        cv.Optional(CONF_KEEP_ALIVE, default=60): cv.positive_int,
        cv.Optional(CONF_AUTO_RECONNECT, default=True): cv.boolean,
        cv.Optional(CONF_ON_MESSAGE): automation.validate_automation(
            {
                cv.Required(CONF_TOPIC): cv.string,
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(MQTTMessageTrigger),
            }
        ),
    }
).extend(cv.COMPONENT_SCHEMA)

MQTT_PUBLISH_ACTION_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(SimpleMQTTClient),
        cv.Required(CONF_TOPIC): cv.templatable(cv.string),
        cv.Required(CONF_PAYLOAD): cv.templatable(cv.string),
        cv.Optional(CONF_QOS, default=0): cv.templatable(cv.int_range(0, 2)),
        cv.Optional(CONF_RETAIN, default=False): cv.templatable(cv.boolean),
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    # Set up the MQTT client
    cg.add(var.set_broker_address(config[CONF_BROKER]))
    cg.add(var.set_broker_port(config[CONF_PORT]))
    
    if CONF_USERNAME in config:
        cg.add(var.set_username(config[CONF_USERNAME]))
    
    if CONF_PASSWORD in config:
        cg.add(var.set_password(config[CONF_PASSWORD]))
    
    if CONF_CLIENT_ID in config:
        cg.add(var.set_client_id(config[CONF_CLIENT_ID]))
    
    cg.add(var.set_keep_alive(config[CONF_KEEP_ALIVE]))
    cg.add(var.set_auto_reconnect(config[CONF_AUTO_RECONNECT]))
    
    # Set up message triggers
    if CONF_ON_MESSAGE in config:
        for conf in config[CONF_ON_MESSAGE]:
            trigger = cg.new_Pvariable(
                conf[CONF_TRIGGER_ID], 
                var
            )
            cg.add(var.subscribe(conf[CONF_TOPIC]))
            await automation.build_automation(
                trigger, [(cg.std_string, "topic"), (cg.std_string, "payload")], conf
            )

@automation.register_action("simple_mqtt.publish", MQTTPublishAction, MQTT_PUBLISH_ACTION_SCHEMA)
async def mqtt_publish_action_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    
    template_ = await cg.templatable(config[CONF_TOPIC], args, cg.std_string)
    cg.add(var.set_topic(template_))
    
    template_ = await cg.templatable(config[CONF_PAYLOAD], args, cg.std_string)
    cg.add(var.set_payload(template_))
    
    template_ = await cg.templatable(config[CONF_QOS], args, cg.uint8)
    cg.add(var.set_qos(template_))
    
    template_ = await cg.templatable(config[CONF_RETAIN], args, cg.bool_)
    cg.add(var.set_retain(template_))
    
    return var 