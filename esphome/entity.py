"""Entity-related helper functions."""

from esphome.core import CORE
from esphome.helpers import sanitize, snake_case


def get_base_entity_object_id(name: str, friendly_name: str | None) -> str:
    """Calculate the base object ID for an entity that will be set via set_object_id().

    This function calculates what object_id_c_str_ should be set to in C++.

    The C++ EntityBase::get_object_id() (entity_base.cpp lines 38-49) works as:
    - If !has_own_name && is_name_add_mac_suffix_enabled():
        return str_sanitize(str_snake_case(App.get_friendly_name()))  // Dynamic
    - Else:
        return object_id_c_str_ ?? ""  // What we set via set_object_id()

    Since we're calculating what to pass to set_object_id(), we always need to
    generate the object_id the same way, regardless of name_add_mac_suffix setting.

    Args:
        name: The entity name (empty string if no name)
        friendly_name: The friendly name from CORE.friendly_name

    Returns:
        The base object ID to use for duplicate checking and to pass to set_object_id()
    """

    if name:
        # Entity has its own name (has_own_name will be true)
        base_str = name
    elif friendly_name:
        # Entity has empty name (has_own_name will be false)
        # Calculate what the object_id should be
        # C++ uses App.get_friendly_name() which returns friendly_name or device name
        base_str = friendly_name
    else:
        # Fallback to device name
        base_str = CORE.name

    return sanitize(snake_case(base_str))
