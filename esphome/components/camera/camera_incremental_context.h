#pragma once

#include <string>
#include <unordered_map>

namespace esphome {
namespace camera {

/** CameraIncrementalContext is a presistent state object used across
 *  multiple stages camera processing (capture and overlay).
 *  The 'done' flag controls incremental flow. It is set to 'true' by default
 *  before user code is called. If the user wants to continue processing
 *  in the next cycle, they must explicitly set 'done = false' inside the automation.
 */
struct CameraIncrementalContext {
  enum ValueType { VALUE_TYPE_NONE = 0, VALUE_TYPE_INT, VALUE_TYPE_FLOAT, VALUE_TYPE_BOOL, VALUE_TYPE_STRING };
  struct Value {
    ValueType type = VALUE_TYPE_NONE;
    union {
      int i;
      float f;
      bool b;
    };
    std::string s;
    Value() : type(ValueType::VALUE_TYPE_NONE), i(0) {}
  };
  // Common coordinates
  int x = 0;
  int y = 0;
  int z = 0;
  // State of arbitrary state-machine
  int state = 0;
  // Indicates if incremental processing is finished.
  // Reset to false to leave capture or overlay states.
  bool done = true;
  // Sets user specific persisten data
  template<typename T> void set(const std::string &key, const T &value) {
    Value v;
    if (std::is_same<T, int>::value) {
      v.type = ValueType::VALUE_TYPE_INT;
      v.i = value;
    } else if (std::is_same<T, float>::value) {
      v.type = ValueType::VALUE_TYPE_FLOAT;
      v.f = value;
    } else if (std::is_same<T, bool>::value) {
      v.type = ValueType::VALUE_TYPE_BOOL;
      v.b = value;
    } else if (std::is_same<T, std::string>::value) {
      v.type = ValueType::VALUE_TYPE_STRING;
      v.s = value;
    } else {
      static_assert(!sizeof(T), "Unsupported type in CameraIncrementalContext::set");
    }

    values_[key] = std::move(v);
  }
  // Overload for const *char handling
  void set(const std::string &key, const char *value) {
    Value v;
    v.type = ValueType::VALUE_TYPE_STRING;
    v.s = value;
    values_[key] = std::move(v);
  }
  // Gets user specific persisten data
  template<typename T> bool get(const std::string &key, T *out) const {
    auto it = values_.find(key);
    if (it == values_.end())
      return false;

    const Value &v = it->second;
    if (std::is_same<T, int>::value) {
      if (v.type == ValueType::VALUE_TYPE_INT) {
        *out = v.i;
        return true;
      }
    } else if (std::is_same<T, float>::value) {
      if (v.type == ValueType::VALUE_TYPE_FLOAT) {
        *out = v.f;
        return true;
      }
    } else if (std::is_same<T, bool>::value) {
      if (v.type == ValueType::VALUE_TYPE_BOOL) {
        *out = v.b;
        return true;
      }
    } else if (std::is_same<T, std::string>::value) {
      if (v.type == ValueType::VALUE_TYPE_STRING) {
        *out = v.s;
        return true;
      }
    } else {
      static_assert(!sizeof(T), "Unsupported type in CameraIncrementalContext::get");
    }

    return false;
  }
  bool has_value(const std::string &key) const { return values_.count(key) > 0; }
  void reset() {
    x = 0;
    y = 0;
    z = 0;
    state = 0;
    done = true;
    values_.clear();
  }
  std::unordered_map<std::string, Value> values_;
};

}  // namespace camera
}  // namespace esphome
