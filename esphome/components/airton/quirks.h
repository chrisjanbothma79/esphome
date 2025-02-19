#pragma once

#ifndef AIRTON_QUIRKS_H
#define AIRTON_QUIRKS_H

#include <cstdint>
#include <string>
#include "esphome/core/log.h"

namespace esphome {
namespace airton {

// Vertical direction for air outlet flap
class VerticalDirection {
 public:
  enum Direction {
    VERTICAL_DIRECTION_OFF = 0x00,
    VERTICAL_DIRECTION_SWING = 0x01,
    VERTICAL_DIRECTION_UP = 0x02,
    VERTICAL_DIRECTION_MIDDLE_UP = 0x03,
    VERTICAL_DIRECTION_MIDDLE = 0x04,
    VERTICAL_DIRECTION_MIDDLE_DOWN = 0x05,
    VERTICAL_DIRECTION_DOWN = 0x06,
  };

  VerticalDirection(Direction direction = Direction::VERTICAL_DIRECTION_OFF) : _direction(direction) {}

  std::string toString() const {
    switch (_direction) {
      case Direction::VERTICAL_DIRECTION_SWING:
        return "swing";
      case Direction::VERTICAL_DIRECTION_UP:
        return "up";
      case Direction::VERTICAL_DIRECTION_MIDDLE_UP:
        return "middle-up";
      case Direction::VERTICAL_DIRECTION_MIDDLE:
        return "middle";
      case Direction::VERTICAL_DIRECTION_MIDDLE_DOWN:
        return "middle-down";
      case Direction::VERTICAL_DIRECTION_DOWN:
        return "down";
      case Direction::VERTICAL_DIRECTION_OFF:
      default:
        return "off";
    }
  }

  uint8_t toUint8() const { return static_cast<uint8_t>(_direction); }

  void setDirection(Direction direction) { _direction = direction; }
  void setDirection(std::string direction) {
    if (direction == "swing") {
      _direction = Direction::VERTICAL_DIRECTION_SWING;
    } else if (direction == "up") {
      _direction = Direction::VERTICAL_DIRECTION_UP;
    } else if (direction == "middle-up") {
      _direction = Direction::VERTICAL_DIRECTION_MIDDLE_UP;
    } else if (direction == "middle") {
      _direction = Direction::VERTICAL_DIRECTION_MIDDLE;
    } else if (direction == "middle-down") {
      _direction = Direction::VERTICAL_DIRECTION_MIDDLE_DOWN;
    } else if (direction == "down") {
      _direction = Direction::VERTICAL_DIRECTION_DOWN;
    } else {
      _direction = Direction::VERTICAL_DIRECTION_OFF;
    }
  }

  Direction getDirection() const { return _direction; }

 private:
  Direction _direction;
};

}  // namespace airton
}  // namespace esphome

#endif  // AIRTON_QUIRKS_H
