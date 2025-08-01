#pragma once

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include <map>
#include <string>

namespace esphome::mapping {

using alloc_string_t = std::basic_string<char, std::char_traits<char>, RAMAllocator<char>>;

/**
 *
 * Mapping class with custom allocator.
 * Additionally, when std::string is used as key or value, it will be replaced with a custom string type
 * that uses RAMAllocator.
 * @tparam K The type of the key in the mapping.
 * @tparam V The type of the value in the mapping. Should be a basic type or pointer.
 */

static const char *const TAG = "mapping";

template<typename K, typename V> class Mapping {
 public:
  // Constructor
  Mapping() = default;

  using key_t = const std::conditional_t<std::is_same_v<K, std::string>,
                                         alloc_string_t,  // if K is std::string, custom string type
                                         K>;
  using value_t = std::conditional_t<std::is_same_v<V, std::string>,
                                     alloc_string_t,  // if V is std::string, custom string type
                                     V>;

  class Proxy {
   public:
    Proxy(Mapping &map, const K &key) : map_(map), key_(key) {}

    // assignment operator that handles the assignment
    Proxy &operator=(const V &v) {
      this->map_.set(key_t{this->key_}, v);
      return *this;
    }

    // conversion operator to support reading
    operator V() const { return this->map_.get(key_); }

   private:
    Mapping &map_;
    const K &key_;
  };

  Proxy operator[](const K &key) { return Proxy(*this, key); }

  V get(const key_t &key) const {
    auto it = this->map_.find(key);
    if (it != this->map_.end()) {
      return V{it->second};
    }
    esph_log_e(TAG, "Key '%s' not found in mapping", to_string(key).c_str());
    return V{};
  }

  void set(const key_t &key, const V &value) { this->map_[key] = value; }

 private:
  std::map<key_t, value_t, std::less<key_t>, RAMAllocator<std::pair<key_t, value_t>>> map_;
};

}  // namespace esphome::mapping
