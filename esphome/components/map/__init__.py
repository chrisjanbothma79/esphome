import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_FROM, CONF_ID, CONF_TO
from esphome.core import CORE
from esphome.cpp_generator import MockObj, VariableDeclarationExpression, add_global

CODEOWNERS = ["@clydebarrow"]

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
        cv.Schema({cv.Required(CONF_CLASS): cv.one_of(*MockObj.known_classes.keys())}),
    )(value)


BASE_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(map_),
        cv.Required(CONF_FROM): cv.one_of(*INDEX_TYPES, lower=True),
        cv.Required(CONF_TO): to_schema,
    }
)


def validate_mapping(config):
    entries = config[CONF_ENTRIES]
    from_ = config[CONF_FROM]
    to_ = config[CONF_TO]
    if len(entries) == 0:
        raise cv.Invalid("Map must have at least one entry")
    if isinstance(to_, dict):
        class_ = to_[CONF_CLASS]
        config[CONF_ENTRIES] = {k: cv.use_id(class_)(v) for k, v in entries.items()}
        for k, v in config[CONF_ENTRIES].items():
            print(k, v, v.type)
    else:
        config[CONF_ENTRIES] = {
            k: INDEX_TYPES[to_].validator(v) for k, v in entries.items()
        }
    return config


CONFIG_SCHEMA = cv.All(
    BASE_SCHEMA.extend(
        {
            cv.Required(CONF_ENTRIES): dict,
        }
    ),
    validate_mapping,
)


async def to_code(config):
    entries = config[CONF_ENTRIES]
    index = config[CONF_FROM]
    value_spec = config[CONF_TO]
    index_conversion = INDEX_TYPES[index].conversion
    index_type = INDEX_TYPES[index].data_type
    if isinstance(value_spec, dict):
        entries = {
            index_conversion(key): await cg.get_variable(value)
            for key, value in entries.items()
        }
        value_type = MockObj.known_classes[value_spec[CONF_CLASS]].operator("ptr")
    else:
        value_conversion = INDEX_TYPES[value_spec].conversion
        value_type = INDEX_TYPES[value_spec].data_type
        entries = {
            index_conversion(key): value_conversion(value)
            for key, value in entries.items()
        }
    varid = config[CONF_ID]
    varid.type = map_.template(index_type, value_type)
    var = MockObj(varid, ".")
    decl = VariableDeclarationExpression(varid.type, "", varid)
    add_global(decl)
    CORE.register_variable(varid, var)

    for key, value in entries.items():
        cg.add(var.insert((key, value)))
    return var
