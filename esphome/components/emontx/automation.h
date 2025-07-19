#pragma once

#include "esphome/core/automation.h"
#include "emontx.h"

namespace esphome {
namespace emontx {

class EmonTxJsonTrigger : public Trigger<JsonObjectConst> {
 public:
  explicit EmonTxJsonTrigger(EmonTx *parent) {
    parent->add_on_json_callback([this](JsonObject json) { this->trigger(json); });
  }
};

}  // namespace emontx
}  // namespace esphome
