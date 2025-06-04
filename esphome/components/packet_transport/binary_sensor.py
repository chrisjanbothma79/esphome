import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_DATA,
    CONF_ID,
    CONF_STATUS,
    CONF_TYPE,
    DEVICE_CLASS_CONNECTIVITY,
    ENTITY_CATEGORY_DIAGNOSTIC,
)

from . import (
    CONF_PROVIDER,
    CONF_REMOTE_ID,
    CONF_TRANSPORT_ID,
    PacketTransport,
    packet_transport_sensor_schema,
    provider_name_validate,
)

STATUS_SENSOR_SCHEMA = binary_sensor.binary_sensor_schema(
    device_class=DEVICE_CLASS_CONNECTIVITY,
    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
).extend(
    {
        cv.GenerateID(CONF_TRANSPORT_ID): cv.use_id(PacketTransport),
        cv.Required(CONF_PROVIDER): provider_name_validate,
    }
)

CONFIG_SCHEMA = cv.typed_schema(
    {
        CONF_DATA: packet_transport_sensor_schema(binary_sensor.binary_sensor_schema()),
        CONF_STATUS: STATUS_SENSOR_SCHEMA,
    },
    key=CONF_TYPE,
    default_type=CONF_DATA,
)


async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    comp = await cg.get_variable(config[CONF_TRANSPORT_ID])
    if config[CONF_TYPE] == CONF_DATA:
        remote_id = str(config.get(CONF_REMOTE_ID) or config.get(CONF_ID))
        cg.add(comp.add_remote_binary_sensor(config[CONF_PROVIDER], remote_id, var))
    elif config[CONF_TYPE] == CONF_STATUS:
        cg.add(comp.set_provider_status_sensor(config[CONF_PROVIDER], var))
        cg.add_define("USE_STATUS_SENSOR")
