#include "component.h"
namespace esphome {
Component::Component() {}
Component::~Component() {}
void Component::setup() {}
void Component::dump_config() {}
void Component::loop() {}
void Component::update() {}
float Component::get_setup_priority() const { return 0.0f; }
void Component::set_restore_mode(bool) {}
bool Component::is_failed() const { return false; }
void Component::mark_failed() {}
void Component::call_setup() {}
void Component::call_loop() {}
void Component::call_update() {}
void Component::call_dump_config() {}
void Component::set_interval(const std::string &, uint32_t, std::function<void()> &&) {}
void Component::cancel_interval(const std::string &) {}
void Component::set_timeout(const std::string &, uint32_t, std::function<void()> &&) {}
void Component::cancel_timeout(const std::string &) {}
}  // namespace esphome 