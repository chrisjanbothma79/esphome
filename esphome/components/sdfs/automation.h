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
//   Is Mount
//
template<typename... Ts> class SdIsMountCondition : public Condition<Ts...> {
 public:
  SdIsMountCondition(SdfsHost *parent) : parent_(parent) {}
  bool check(Ts... x) override { return this->parent_->get_state() == SD_SLOT_ST_MOUNT; }

 protected:
  SdfsHost *parent_;
};

//
//   Is Empty
//
template<typename... Ts> class SdIsEmptyCondition : public Condition<Ts...> {
 public:
  SdIsEmptyCondition(SdfsHost *parent) : parent_(parent) {}
  bool check(Ts... x) override { return this->parent_->get_state() == SD_SLOT_ST_EMPTY; }

 protected:
  SdfsHost *parent_;
};

//
//   Is Card
//
template<typename... Ts> class SdIsCardCondition : public Condition<Ts...> {
 public:
  SdIsCardCondition(SdfsHost *parent) : parent_(parent) {}
  bool check(Ts... x) override { return this->parent_->get_state() == SD_SLOT_ST_CARD; }

 protected:
  SdfsHost *parent_;
};

//
//   Is Init
//
template<typename... Ts> class SdIsInitCondition : public Condition<Ts...> {
 public:
  SdIsInitCondition(SdfsHost *parent) : parent_(parent) {}
  bool check(Ts... x) override { return this->parent_->get_state() == SD_SLOT_ST_INIT; }

 protected:
  SdfsHost *parent_;
};

//
//    State changed
//
class ChangeSateteTrigger : public Trigger<SdDriverStatus> {
 public:
  explicit ChangeSateteTrigger(SdfsHost *parent) {
    parent->add_on_state_callback([this](SdDriverStatus state) { this->trigger(state); });
  }
};

}  // namespace sdfs
}  // namespace esphome