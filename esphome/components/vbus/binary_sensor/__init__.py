import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_BINARY_SENSORS,
    CONF_COMMAND,
    CONF_CUSTOM,
    CONF_DEST,
    CONF_ID,
    CONF_LAMBDA,
    CONF_MODEL,
    CONF_SOURCE,
    DEVICE_CLASS_PROBLEM,
    ENTITY_CATEGORY_DIAGNOSTIC,
)

from .. import (
    CONF_DELTASOL_BS_2009,
    CONF_DELTASOL_BS_PLUS,
    CONF_DELTASOL_BX,
    CONF_DELTASOL_C,
    CONF_DELTASOL_CS2,
    CONF_DELTASOL_CS_PLUS,
    CONF_VBUS_ID,
    VBus,
    vbus_ns,
)

DeltaSol_BS_Plus = vbus_ns.class_("DeltaSolBSPlusBSensor", cg.Component)
DeltaSol_BS_2009 = vbus_ns.class_("DeltaSolBS2009BSensor", cg.Component)
DeltaSol_BX = vbus_ns.class_("DeltaSolBXBSensor", cg.Component)
DeltaSol_C = vbus_ns.class_("DeltaSolCBSensor", cg.Component)
DeltaSol_CS2 = vbus_ns.class_("DeltaSolCS2BSensor", cg.Component)
DeltaSol_CS_Plus = vbus_ns.class_("DeltaSolCSPlusBSensor", cg.Component)
VBusCustom = vbus_ns.class_("VBusCustomBSensor", cg.Component)
VBusCustomSub = vbus_ns.class_("VBusCustomSubBSensor", cg.Component)

CONF_RELAY1 = "relay1"
CONF_RELAY2 = "relay2"
CONF_SENSOR1_ERROR = "sensor1_error"
CONF_SENSOR2_ERROR = "sensor2_error"
CONF_SENSOR3_ERROR = "sensor3_error"
CONF_SENSOR4_ERROR = "sensor4_error"
CONF_SENSOR5_ERROR = "sensor5_error"
CONF_SENSOR6_ERROR = "sensor6_error"
CONF_SENSOR7_ERROR = "sensor7_error"
CONF_SENSOR8_ERROR = "sensor8_error"
CONF_SENSOR9_ERROR = "sensor9_error"
CONF_V40_ERROR = "v40_error"
CONF_LEAKAGE = "leakage"
CONF_OVERPRESSURE = "overpressure"
CONF_FLOW_RATE_ERROR = "flow_rate_error"
CONF_BLOCKING_PROTECTION1 = "blocking_protection1"
CONF_BLOCKING_PROTECTION2 = "blocking_protection2"
CONF_BLOCKING_PROTECTION3 = "blocking_protection3"
CONF_BLOCKING_PROTECTION4 = "blocking_protection4"
CONF_INITIALISATION = "initialisation"
CONF_FILLING = "filling"
CONF_STABILISATION = "stabilisation"
CONF_PUMP_DELAY = "pump_delay"
CONF_HEAT_DUMP = "heat_dump"
CONF_OVERRUN = "overrun"
CONF_THERMAL_DISINFECTION = "thermal_disinfection"
CONF_SYSTEM_COOLING = "system_cooling"
CONF_STORE_COOLING = "store_cooling"
CONF_SPREADING = "spreading"
CONF_ANTIFREEZE = "antifreeze"
CONF_COLLECTOR_COOLING = "collector_cooling"
CONF_COLLECTOR_MAX = "collector_max"
CONF_COLLECTOR_MIN = "collector_min"
CONF_COLLECTOR_FROST = "collector_frost"
CONF_TUBE_COLLECTOR = "tube_collector"
CONF_RECOOLING = "recooling"
CONF_HQM = "hqm"
CONF_FROST_PROTECTION_ACTIVE = "frost_protection_active"

CONFIG_SCHEMA = cv.typed_schema(
    {
        CONF_DELTASOL_BS_PLUS: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(DeltaSol_BS_Plus),
                cv.GenerateID(CONF_VBUS_ID): cv.use_id(VBus),
                cv.Optional(CONF_RELAY1): binary_sensor.binary_sensor_schema(),
                cv.Optional(CONF_RELAY2): binary_sensor.binary_sensor_schema(),
                cv.Optional(CONF_SENSOR1_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR2_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR3_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR4_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_COLLECTOR_MAX): binary_sensor.binary_sensor_schema(
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_COLLECTOR_MIN): binary_sensor.binary_sensor_schema(
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_COLLECTOR_FROST): binary_sensor.binary_sensor_schema(
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_TUBE_COLLECTOR): binary_sensor.binary_sensor_schema(
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_RECOOLING): binary_sensor.binary_sensor_schema(
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_HQM): binary_sensor.binary_sensor_schema(
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
            }
        ),
        CONF_DELTASOL_BS_2009: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(DeltaSol_BS_2009),
                cv.GenerateID(CONF_VBUS_ID): cv.use_id(VBus),
                cv.Optional(CONF_SENSOR1_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR2_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR3_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR4_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(
                    CONF_FROST_PROTECTION_ACTIVE
                ): binary_sensor.binary_sensor_schema(
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
            }
        ),
        CONF_DELTASOL_BX: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(DeltaSol_BX),
                cv.GenerateID(CONF_VBUS_ID): cv.use_id(VBus),
                cv.Optional(CONF_SENSOR1_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR2_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR3_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR4_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR5_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR6_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR7_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR8_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR9_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_V40_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_LEAKAGE): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_OVERPRESSURE): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_FLOW_RATE_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(
                    CONF_BLOCKING_PROTECTION1
                ): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(
                    CONF_BLOCKING_PROTECTION2
                ): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(
                    CONF_BLOCKING_PROTECTION3
                ): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(
                    CONF_BLOCKING_PROTECTION4
                ): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_INITIALISATION): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_FILLING): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_STABILISATION): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_PUMP_DELAY): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_HEAT_DUMP): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_OVERRUN): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(
                    CONF_THERMAL_DISINFECTION
                ): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SYSTEM_COOLING): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_STORE_COOLING): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SPREADING): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_ANTIFREEZE): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_COLLECTOR_COOLING): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
            }
        ),
        CONF_DELTASOL_C: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(DeltaSol_C),
                cv.GenerateID(CONF_VBUS_ID): cv.use_id(VBus),
                cv.Optional(CONF_SENSOR1_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR2_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR3_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR4_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
            }
        ),
        CONF_DELTASOL_CS2: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(DeltaSol_CS2),
                cv.GenerateID(CONF_VBUS_ID): cv.use_id(VBus),
                cv.Optional(CONF_SENSOR1_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR2_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR3_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR4_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
            }
        ),
        CONF_DELTASOL_CS_PLUS: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(DeltaSol_CS_Plus),
                cv.GenerateID(CONF_VBUS_ID): cv.use_id(VBus),
                cv.Optional(CONF_SENSOR1_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR2_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR3_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
                cv.Optional(CONF_SENSOR4_ERROR): binary_sensor.binary_sensor_schema(
                    device_class=DEVICE_CLASS_PROBLEM,
                    entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                ),
            }
        ),
        CONF_CUSTOM: cv.COMPONENT_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(VBusCustom),
                cv.GenerateID(CONF_VBUS_ID): cv.use_id(VBus),
                cv.Optional(CONF_COMMAND): cv.uint16_t,
                cv.Optional(CONF_SOURCE): cv.uint16_t,
                cv.Optional(CONF_DEST): cv.uint16_t,
                cv.Optional(CONF_BINARY_SENSORS): cv.ensure_list(
                    binary_sensor.binary_sensor_schema().extend(
                        {
                            cv.GenerateID(): cv.declare_id(VBusCustomSub),
                            cv.Required(CONF_LAMBDA): cv.lambda_,
                        }
                    )
                ),
            }
        ),
    },
    key=CONF_MODEL,
    lower=True,
    space="_",
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if config[CONF_MODEL] == CONF_DELTASOL_BS_PLUS:
        cg.add(var.set_command(0x0100))
        cg.add(var.set_source(0x4221))
        cg.add(var.set_dest(0x0010))
        if CONF_RELAY1 in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_RELAY1])
            cg.add(var.set_relay1_bsensor(sens))
        if CONF_RELAY2 in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_RELAY2])
            cg.add(var.set_relay2_bsensor(sens))
        if CONF_SENSOR1_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR1_ERROR])
            cg.add(var.set_s1_error_bsensor(sens))
        if CONF_SENSOR2_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR2_ERROR])
            cg.add(var.set_s2_error_bsensor(sens))
        if CONF_SENSOR3_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR3_ERROR])
            cg.add(var.set_s3_error_bsensor(sens))
        if CONF_SENSOR4_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR4_ERROR])
            cg.add(var.set_s4_error_bsensor(sens))
        if CONF_COLLECTOR_MAX in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_COLLECTOR_MAX])
            cg.add(var.set_collector_max_bsensor(sens))
        if CONF_COLLECTOR_MIN in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_COLLECTOR_MIN])
            cg.add(var.set_collector_min_bsensor(sens))
        if CONF_COLLECTOR_FROST in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_COLLECTOR_FROST])
            cg.add(var.set_collector_frost_bsensor(sens))
        if CONF_TUBE_COLLECTOR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_TUBE_COLLECTOR])
            cg.add(var.set_tube_collector_bsensor(sens))
        if CONF_RECOOLING in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_RECOOLING])
            cg.add(var.set_recooling_bsensor(sens))
        if CONF_HQM in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_HQM])
            cg.add(var.set_hqm_bsensor(sens))

    elif config[CONF_MODEL] == CONF_DELTASOL_BS_2009:
        cg.add(var.set_command(0x0100))
        cg.add(var.set_source(0x427B))
        cg.add(var.set_dest(0x0010))
        if CONF_SENSOR1_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR1_ERROR])
            cg.add(var.set_s1_error_bsensor(sens))
        if CONF_SENSOR2_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR2_ERROR])
            cg.add(var.set_s2_error_bsensor(sens))
        if CONF_SENSOR3_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR3_ERROR])
            cg.add(var.set_s3_error_bsensor(sens))
        if CONF_SENSOR4_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR4_ERROR])
            cg.add(var.set_s4_error_bsensor(sens))
        if CONF_FROST_PROTECTION_ACTIVE in config:
            sens = await binary_sensor.new_binary_sensor(
                config[CONF_FROST_PROTECTION_ACTIVE]
            )
            cg.add(var.set_frost_protection_active_bsensor(sens))

    elif config[CONF_MODEL] == CONF_DELTASOL_BX:
        cg.add(var.set_command(0x0100))
        cg.add(var.set_source(0x7421))
        cg.add(var.set_dest(0x0010))
        if CONF_SENSOR1_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR1_ERROR])
            cg.add(var.set_s1_error_bsensor(sens))
        if CONF_SENSOR2_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR2_ERROR])
            cg.add(var.set_s2_error_bsensor(sens))
        if CONF_SENSOR3_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR3_ERROR])
            cg.add(var.set_s3_error_bsensor(sens))
        if CONF_SENSOR4_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR4_ERROR])
            cg.add(var.set_s4_error_bsensor(sens))
        if CONF_SENSOR5_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR5_ERROR])
            cg.add(var.set_s5_error_bsensor(sens))
        if CONF_SENSOR6_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR6_ERROR])
            cg.add(var.set_s6_error_bsensor(sens))
        if CONF_SENSOR7_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR7_ERROR])
            cg.add(var.set_s7_error_bsensor(sens))
        if CONF_SENSOR8_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR8_ERROR])
            cg.add(var.set_s8_error_bsensor(sens))
        if CONF_SENSOR9_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR9_ERROR])
            cg.add(var.set_s9_error_bsensor(sens))
        if CONF_V40_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_V40_ERROR])
            cg.add(var.set_v40_error_bsensor(sens))
        if CONF_LEAKAGE in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_LEAKAGE])
            cg.add(var.set_leakage_bsensor(sens))
        if CONF_OVERPRESSURE in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_OVERPRESSURE])
            cg.add(var.set_overpressure_bsensor(sens))
        if CONF_FLOW_RATE_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_FLOW_RATE_ERROR])
            cg.add(var.set_flow_rate_error_bsensor(sens))
        if CONF_BLOCKING_PROTECTION1 in config:
            sens = await binary_sensor.new_binary_sensor(
                config[CONF_BLOCKING_PROTECTION1]
            )
            cg.add(var.set_blocking_protection1_bsensor(sens))
        if CONF_BLOCKING_PROTECTION2 in config:
            sens = await binary_sensor.new_binary_sensor(
                config[CONF_BLOCKING_PROTECTION2]
            )
            cg.add(var.set_blocking_protection2_bsensor(sens))
        if CONF_BLOCKING_PROTECTION3 in config:
            sens = await binary_sensor.new_binary_sensor(
                config[CONF_BLOCKING_PROTECTION3]
            )
            cg.add(var.set_blocking_protection3_bsensor(sens))
        if CONF_BLOCKING_PROTECTION4 in config:
            sens = await binary_sensor.new_binary_sensor(
                config[CONF_BLOCKING_PROTECTION4]
            )
            cg.add(var.set_blocking_protection4_bsensor(sens))
        if CONF_INITIALISATION in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_INITIALISATION])
            cg.add(var.set_initialisation_bsensor(sens))
        if CONF_FILLING in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_FILLING])
            cg.add(var.set_filling_bsensor(sens))
        if CONF_STABILISATION in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_STABILISATION])
            cg.add(var.set_stabilisation_bsensor(sens))
        if CONF_PUMP_DELAY in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_PUMP_DELAY])
            cg.add(var.set_pump_delay_bsensor(sens))
        if CONF_HEAT_DUMP in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_HEAT_DUMP])
            cg.add(var.set_heat_dump_bsensor(sens))
        if CONF_OVERRUN in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_OVERRUN])
            cg.add(var.set_overrun_bsensor(sens))
        if CONF_THERMAL_DISINFECTION in config:
            sens = await binary_sensor.new_binary_sensor(
                config[CONF_THERMAL_DISINFECTION]
            )
            cg.add(var.set_thermal_disinfection_bsensor(sens))
        if CONF_SYSTEM_COOLING in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SYSTEM_COOLING])
            cg.add(var.set_system_cooling_bsensor(sens))
        if CONF_STORE_COOLING in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_STORE_COOLING])
            cg.add(var.set_store_cooling_bsensor(sens))
        if CONF_SPREADING in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SPREADING])
            cg.add(var.set_spreading_bsensor(sens))
        if CONF_ANTIFREEZE in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_ANTIFREEZE])
            cg.add(var.set_antifreeze_bsensor(sens))
        if CONF_COLLECTOR_COOLING in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_COLLECTOR_COOLING])
            cg.add(var.set_collector_cooling_bsensor(sens))

    elif config[CONF_MODEL] == CONF_DELTASOL_C:
        cg.add(var.set_command(0x0100))
        cg.add(var.set_source(0x4212))
        cg.add(var.set_dest(0x0010))
        if CONF_SENSOR1_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR1_ERROR])
            cg.add(var.set_s1_error_bsensor(sens))
        if CONF_SENSOR2_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR2_ERROR])
            cg.add(var.set_s2_error_bsensor(sens))
        if CONF_SENSOR3_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR3_ERROR])
            cg.add(var.set_s3_error_bsensor(sens))
        if CONF_SENSOR4_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR4_ERROR])
            cg.add(var.set_s4_error_bsensor(sens))

    elif config[CONF_MODEL] == CONF_DELTASOL_CS2:
        cg.add(var.set_command(0x0100))
        cg.add(var.set_source(0x1121))
        cg.add(var.set_dest(0x0010))
        if CONF_SENSOR1_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR1_ERROR])
            cg.add(var.set_s1_error_bsensor(sens))
        if CONF_SENSOR2_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR2_ERROR])
            cg.add(var.set_s2_error_bsensor(sens))
        if CONF_SENSOR3_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR3_ERROR])
            cg.add(var.set_s3_error_bsensor(sens))
        if CONF_SENSOR4_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR4_ERROR])
            cg.add(var.set_s4_error_bsensor(sens))

    elif config[CONF_MODEL] == CONF_DELTASOL_CS_PLUS:
        cg.add(var.set_command(0x0100))
        cg.add(var.set_source(0x2211))
        cg.add(var.set_dest(0x0010))
        if CONF_SENSOR1_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR1_ERROR])
            cg.add(var.set_s1_error_bsensor(sens))
        if CONF_SENSOR2_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR2_ERROR])
            cg.add(var.set_s2_error_bsensor(sens))
        if CONF_SENSOR3_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR3_ERROR])
            cg.add(var.set_s3_error_bsensor(sens))
        if CONF_SENSOR4_ERROR in config:
            sens = await binary_sensor.new_binary_sensor(config[CONF_SENSOR4_ERROR])
            cg.add(var.set_s4_error_bsensor(sens))

    elif config[CONF_MODEL] == CONF_CUSTOM:
        if CONF_COMMAND in config:
            cg.add(var.set_command(config[CONF_COMMAND]))
        if CONF_SOURCE in config:
            cg.add(var.set_source(config[CONF_SOURCE]))
        if CONF_DEST in config:
            cg.add(var.set_dest(config[CONF_DEST]))
        bsensors = []
        for conf in config[CONF_BINARY_SENSORS]:
            bsens = await binary_sensor.new_binary_sensor(conf)
            lambda_ = await cg.process_lambda(
                conf[CONF_LAMBDA],
                [(cg.std_vector.template(cg.uint8), "x")],
                return_type=cg.bool_,
            )
            cg.add(bsens.set_message_parser(lambda_))
            bsensors.append(bsens)
        cg.add(var.set_bsensors(bsensors))

    vbus = await cg.get_variable(config[CONF_VBUS_ID])
    cg.add(vbus.register_listener(var))
