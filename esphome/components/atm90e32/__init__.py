import esphome.codegen as cg

CODEOWNERS = ["@circuitsetup", "@descipher"]

atm90e32_ns = cg.esphome_ns.namespace("atm90e32")
ATM90E32Component = atm90e32_ns.class_("ATM90E32Component", cg.Component)

CONF_ATM90E32_ID = "atm90e32_id"

# Import button submodule to expose classes
from .button import (
    ATM90E32GainCalibrationButton,
    ATM90E32ClearGainCalibrationButton,
    ATM90E32OffsetCalibrationButton,
    ATM90E32ClearOffsetCalibrationButton,
    ATM90E32PowerOffsetCalibrationButton,
    ATM90E32ClearPowerOffsetCalibrationButton,
)
