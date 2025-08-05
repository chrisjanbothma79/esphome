#pragma once
#ifdef USE_ESP_IDF

#include "driver/gptimer_types.h"

namespace esphome {
namespace ac_dimmer {

struct timer_struct_t;
typedef struct timer_struct_t hw_timer_t;

hw_timer_t *timerBegin(uint32_t frequency);

void timerAttachInterrupt(hw_timer_t *timer, void (*userFunc)(void));
void timerAlarm(hw_timer_t *timer, uint64_t alarm_value, bool autoreload, uint64_t reload_count);
void timerStart(hw_timer_t *timer);

}  // namespace ac_dimmer
}  // namespace esphome

#endif
