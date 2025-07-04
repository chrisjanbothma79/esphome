#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "sdfs_defines.h"
#include "sdfs.h"

namespace esphome {
namespace sdfs {

/***************************************************************************
 *
 * @brief   Write to file action processing
 *
 * @tparam Ts
 */
template<typename... Ts> class SdfsWriteFile : public Action<Ts...> {
 public:
  SdfsWriteFile(SdfsHost *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(std::string, path)
  TEMPLATABLE_VALUE(std::string, mode)
  TEMPLATABLE_VALUE(std::vector<uint8_t>, data)

  void play(Ts... x) {
    auto path = this->path_.value(x...);
    auto mode = this->mode_.value(x...);
    auto buffer = this->data_.value(x...);
    this->parent_->write_to_file(path, mode, buffer.data(), buffer.size());
  }

 protected:
  SdfsHost *parent_;
};

//
//   Is State
//
template<typename... Ts> class SdIsStateCondition : public Condition<Ts...> {
 public:
  SdIsStateCondition(SdfsHost *parent) : parent_(parent) {
    state_id = reinterpret_cast<SdDriverState>(SD_SLOT_ST_MOUNT);
  }
  TEMPLATABLE_VALUE(int, state_id)
  bool check(Ts... x) override { return this->parent_->get_state() == state_id; }

 protected:
  SdfsHost *parent_;
  SdDriverState state_id;
};

//
//    State changed
//
class ChangeSateteTrigger : public Trigger<SdDriverState> {
 public:
  explicit ChangeSateteTrigger(SdfsHost *parent) {
    parent->add_on_state_callback([this](SdDriverState state) { this->trigger(state); });
  }
};

}  // namespace sdfs
}  // namespace esphome