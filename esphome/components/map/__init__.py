import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_FROM, CONF_ID, CONF_TO
from esphome.core import CORE
from esphome.cpp_generator import MockObj, VariableDeclarationExpression, add_global

CODEOWNERS = ["@clydebarrow"]
MULTI_CONF = True

map_ = cg.std_ns.class_("map")

CONF_ENTRIES = "entries"
CONF_CLASS = "class"


class IndexType:
    """
    Represents a type of index in a map.
    """

    def __init__(self, validator, data_type, conversion):
        self.validator = validator
        self.data_type = data_type
        self.conversion = conversion


INDEX_TYPES = {
    "int": IndexType(cv.int_, cg.int_, int),
    "string": IndexType(cv.string, cg.std_string, str),
}


def to_schema(value):
    """
    Generate a schema for the 'to' field of a map. This can be either one of the index types or a class name.
    :param value:
    :return:
    """
    return cv.Any(
        cv.one_of(*INDEX_TYPES, lower=True),
        cv.one_of(*CORE.id_classes.keys()),
    )(value)


BASE_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(map_),
        cv.Required(CONF_FROM): cv.one_of(*INDEX_TYPES, lower=True),
        cv.Required(CONF_TO): to_schema,
    },
    extra=cv.ALLOW_EXTRA,
)


def map_schema(config):
    config = BASE_SCHEMA(config)
    if CONF_ENTRIES not in config or not isinstance(config[CONF_ENTRIES], dict):
        raise cv.Invalid("an entries list is required for a map")
    entries = config[CONF_ENTRIES]
    to_ = config[CONF_TO]
    if len(entries) == 0:
        raise cv.Invalid("Map must have at least one entry")
    if to_ in INDEX_TYPES:
        config[CONF_ENTRIES] = {
            k: INDEX_TYPES[to_].validator(v) for k, v in entries.items()
        }
    else:
        config[CONF_ENTRIES] = {
            k: cv.use_id(CORE.id_classes[to_])(v) for k, v in entries.items()
        }
    return config


CONFIG_SCHEMA = map_schema


async def to_code(config):
    entries = config[CONF_ENTRIES]
    from_ = config[CONF_FROM]
    to_ = config[CONF_TO]
    index_conversion = INDEX_TYPES[from_].conversion
    index_type = INDEX_TYPES[from_].data_type
    if to_ in INDEX_TYPES:
        value_conversion = INDEX_TYPES[to_].conversion
        value_type = INDEX_TYPES[to_].data_type
        entries = {
            index_conversion(key): value_conversion(value)
            for key, value in entries.items()
        }
    else:
        entries = {
            index_conversion(key): await cg.get_variable(value)
            for key, value in entries.items()
        }
        value_type = CORE.id_classes[to_].operator("ptr")
    varid = config[CONF_ID]
    varid.type = map_.template(index_type, value_type)
    var = MockObj(varid, ".")
    decl = VariableDeclarationExpression(varid.type, "", varid)
    add_global(decl)
    CORE.register_variable(varid, var)

    for key, value in entries.items():
        cg.add(var.insert((key, value)))
    return var
