// This file is just a minimal stub for the ModemComponent class.
// It will be overridden by future merge of #9807

#ifdef USE_ESP_IDF

#include "modem_component.h"
#include "esphome/core/log.h"

namespace esphome {
namespace modem {

static const char *const TAG = "modem";

ModemComponent *global_modem_component = nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

}  // namespace modem
}  // namespace esphome

#endif
