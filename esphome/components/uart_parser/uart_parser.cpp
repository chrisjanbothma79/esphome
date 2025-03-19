#include "esphome/core/log.h"
#include "uart_parser.h"

namespace esphome {
namespace empty_component {

static const char *TAG = "empty_component.component";

uart::UARTComponent *uart_component = new uart::UARTComponent(115200, 0, GPIO25);

void UartParser::setup() { ESP_LOGI("custom_component", "My Custom Component Initialized"); }

void UartParser::loop() { ESP_LOGI("custom_component", "Component is running"); }

void UartParser::dump_config() { ESP_LOGCONFIG(TAG, "Empty component"); }

}  // namespace empty_component
}  // namespace esphome