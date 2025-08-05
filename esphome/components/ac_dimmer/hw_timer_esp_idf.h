#pragma once
#ifdef USE_ESP32

#include "driver/gptimer_types.h"

namespace esphome {
namespace ac_dimmer {

struct TimerStructT;
using hw_timer_t = struct TimerStructT;

hw_timer_t *timer_begin(uint32_t frequency);

void timer_attach_interrupt(hw_timer_t *timer, void (*user_func)());
void timer_alarm(hw_timer_t *timer, uint64_t alarm_value, bool autoreload, uint64_t reload_count);
void timer_start(hw_timer_t *timer);

}  // namespace ac_dimmer
}  // namespace esphome

#endif
