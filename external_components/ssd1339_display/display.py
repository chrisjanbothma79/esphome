AUTO_LOAD = ["display"]

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display
from esphome import pins
from esphome.const import CONF_ID

ssd1339_display_ns = cg.esphome_ns.namespace('ssd1339_display')
SSD1339Display = ssd1339_display_ns.class_('SSD1339Display', display.DisplayBuffer, cg.Component)

CONFIG_SCHEMA = display.BASIC_DISPLAY_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(SSD1339Display),
    cv.Required("rst_pin"): pins.gpio_output_pin_schema,
    cv.Required("cs_pin"): pins.gpio_output_pin_schema,
    cv.Required("dc_pin"): pins.gpio_output_pin_schema,
    cv.Required("din_pin"): pins.gpio_output_pin_schema,
    cv.Required("clk_pin"): pins.gpio_output_pin_schema,
    cv.Required("hven_pin"): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await display.register_display(var, config)
    cg.add(var.set_rst_pin(await cg.gpio_pin_expression(config["rst_pin"])))
    cg.add(var.set_cs_pin(await cg.gpio_pin_expression(config["cs_pin"])))
    cg.add(var.set_dc_pin(await cg.gpio_pin_expression(config["dc_pin"])))
    cg.add(var.set_din_pin(await cg.gpio_pin_expression(config["din_pin"])))
    cg.add(var.set_clk_pin(await cg.gpio_pin_expression(config["clk_pin"])))
    cg.add(var.set_hven_pin(await cg.gpio_pin_expression(config["hven_pin"]))) 