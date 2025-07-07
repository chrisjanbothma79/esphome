#pragma once

namespace esphome {
namespace log {
  // 基本日志功能声明
  void log(const char* message) {}
  void debug(const char* message) {}
  void info(const char* message) {}
  void warn(const char* message) {}
  void error(const char* message) {}
}  // namespace log
}  // namespace esphome 