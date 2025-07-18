#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "sdfs_defines.h"
#include "sdfs.h"
#include "fs_interface.h"

namespace esphome {
namespace sdfs {

const char *TAG = "automation";

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
//    State changed
//
class ChangeSateteTrigger : public Trigger<SdDriverState> {
 public:
  explicit ChangeSateteTrigger(SdfsHost *parent) {
    parent->add_on_state_callback([this](SdDriverState state) { this->trigger(state); });
  }
};

//
//   Is State
//
template<typename... Ts> class SdIsStateCondition : public Condition<Ts...> {
 public:
  SdIsStateCondition(SdfsHost *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(int, state)
  bool check(Ts... x) override {
    int state_id = this->state_.value(x...);
    return this->parent_->get_state() == state_id;
  }
  // reinterpret_cast<SdDriverState>
 protected:
  SdfsHost *parent_;
};

//
// SdIsSizeGE
//
template<typename... Ts> class SdIsSizeGECondition : public Condition<Ts...> {
 public:
  SdIsSizeGECondition(SdfsHost *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(std::string, path)
  TEMPLATABLE_VALUE(size_t, size)
  bool check(Ts... x) override {
    auto path = this->path_.value(x...);
    auto input_size = this->size_.value(x...);
    FsInterface *fs = this->parent_->get_fs();
    if (fs == NULL) {
      ESP_LOGE(TAG, "FS not mounted");
      return false;
    }

    size_t obj_size = 0;
    if (path == "/") {
      obj_size = this->parent_->get_drv()->card_size();
    } else {
      if (!fs->is_dir(path)) {
        FileInterface *file = fs->open_file(path, 'r');
        obj_size = file->get_size();
      }
    }
    return obj_size >= input_size;
  }

 protected:
  SdfsHost *parent_;
};

//
// SdIsSizeGE
//
template<typename... Ts> class SdIsSizeLECondition : public Condition<Ts...> {
 public:
  SdIsSizeLECondition(SdfsHost *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(std::string, path)
  TEMPLATABLE_VALUE(size_t, size)
  bool check(Ts... x) override {
    auto path = this->path_.value(x...);
    auto input_size = this->size_.value(x...);
    FsInterface *fs = this->parent_->get_fs();
    size_t obj_size = 0;
    if (fs == NULL) {
      ESP_LOGE(TAG, "FS not mounted");
      return false;
    }

    if (path == "/") {
      obj_size = this->parent_->get_drv()->card_size();
    } else {
      if (!fs->is_dir(path)) {
        FileInterface *file = fs->open_file(path, 'r');
        obj_size = file->get_size();
      }
    }
    return obj_size <= input_size;
  }

 protected:
  SdfsHost *parent_;
};

//
// SdIsDir
//

template<typename... Ts> class SdIsDirCondition : public Condition<Ts...> {
 public:
  SdIsDirCondition(SdfsHost *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(std::string, path)
  bool check(Ts... x) override {
    auto path = this->path_.value(x...);
    FsInterface *fs = this->parent_->get_fs();
    if (fs == NULL) {
      ESP_LOGE(TAG, "FS not mounted");
      return false;
    }

    if (path == "/") {
      return true;
    } else {
      return fs->is_dir(path);
    }
  }

 protected:
  SdfsHost *parent_;
};

template<typename... Ts> class SdIsEsistCondition : public Condition<Ts...> {
 public:
  SdIsEsistCondition(SdfsHost *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(std::string, path)
  bool check(Ts... x) override {
    auto path = this->path_.value(x...);
    FsInterface *fs = this->parent_->get_fs();
    if (fs == NULL) {
      ESP_LOGE(TAG, "FS not mounted");
      return false;
    } else {
      return this->parent_->get_fs()->is_exist(path);
    }
  }

 protected:
  SdfsHost *parent_;
};

}  // namespace sdfs
}  // namespace esphome
