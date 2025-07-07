#pragma once
#include <vector>
#include <string>
#include <functional>
#include <cstdint>

namespace esphome {

class Component {
 public:
  Component();
  virtual ~Component();
  virtual void setup();
  virtual void dump_config();
  virtual void loop();
  virtual void update();
  virtual float get_setup_priority() const;
  virtual void set_restore_mode(bool restore);
  virtual bool is_failed() const;
  virtual void mark_failed();
  virtual void call_setup();
  virtual void call_loop();
  virtual void call_update();
  virtual void call_dump_config();
  virtual void set_interval(const std::string &name, uint32_t interval, std::function<void()> &&f);
  virtual void cancel_interval(const std::string &name);
  virtual void set_timeout(const std::string &name, uint32_t timeout, std::function<void()> &&f);
  virtual void cancel_timeout(const std::string &name);
};

}  // namespace esphome 