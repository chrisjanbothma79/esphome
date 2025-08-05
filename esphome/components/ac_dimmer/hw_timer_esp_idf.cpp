#ifdef USE_ESP32

#include "hw_timer_esp_idf.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esphome/core/log.h"

#include "driver/gptimer.h"
#include "esp_clk_tree.h"

static const char *const TAG = "hw_timer_esp_idf";

namespace esphome {
namespace ac_dimmer {

using voidFuncPtr = void (*)(void);
using voidFuncPtrArg = void (*)(void *);

struct interrupt_config_t {
  voidFuncPtr fn;
  void *arg;
};

struct timer_struct_t {
  gptimer_handle_t timer_handle;
  interrupt_config_t interrupt_handle;
  bool timer_started;
};

interrupt_config_t *timer_intr_config = NULL;

hw_timer_t *timer_begin(uint32_t frequency) {
  esp_err_t err = ESP_OK;
  uint32_t counter_src_hz = 0;
  uint32_t divider = 0;
  int /*soc_periph_gptimer_clk_src_t*/ clk;
  int /*soc_periph_gptimer_clk_src_t*/ gptimer_clks[] = SOC_GPTIMER_CLKS;
  for (size_t i = 0; i < sizeof(gptimer_clks) / sizeof(gptimer_clks[0]); i++) {
    clk = gptimer_clks[i];
    esp_clk_tree_src_get_freq_hz((soc_module_clk_t) clk, ESP_CLK_TREE_SRC_FREQ_PRECISION_CACHED, &counter_src_hz);
    divider = counter_src_hz / frequency;
    if ((divider >= 2) && (divider <= 65536)) {
      break;
    } else {
      divider = 0;
    }
  }

  if (divider == 0) {
    ESP_LOGE(TAG, "Resolution cannot be reached with any clock source, aborting!");
    return NULL;
  }

  gptimer_config_t config = {
      .clk_src = (gptimer_clock_source_t) clk,
      .direction = GPTIMER_COUNT_UP,
      .resolution_hz = frequency,
      .flags = {.intr_shared = true},
  };

  hw_timer_t *timer = (hw_timer_t *) malloc(sizeof(hw_timer_t));

  err = gptimer_new_timer(&config, &timer->timer_handle);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Failed to create a new GPTimer, error num=%d", err);
    free(timer);
    return NULL;
  }
  gptimer_enable(timer->timer_handle);
  gptimer_start(timer->timer_handle);
  timer->timer_started = true;
  return timer;
}

bool IRAM_ATTR timer_fn_wrapper(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *args) {
  interrupt_config_t *isr = (interrupt_config_t *) args;
  if (isr->fn) {
    if (isr->arg) {
      ((voidFuncPtrArg) isr->fn)(isr->arg);
    } else {
      isr->fn();
    }
  }
  // some additional logic or handling may be required here to appropriately yield or not
  return false;
}

void timer_attach_interrupt_functional_arg(hw_timer_t *timer, void (*userFunc)(void *), void *arg) {
  if (timer == NULL) {
    ESP_LOGE(TAG, "Timer handle is NULL");
    return;
  }
  esp_err_t err = ESP_OK;
  gptimer_event_callbacks_t cbs = {
      .on_alarm = timer_fn_wrapper,
  };

  timer->interrupt_handle.fn = (voidFuncPtr) userFunc;
  timer->interrupt_handle.arg = arg;

  if (timer->timer_started == true) {
    gptimer_stop(timer->timer_handle);
  }
  gptimer_disable(timer->timer_handle);
  err = gptimer_register_event_callbacks(timer->timer_handle, &cbs, &timer->interrupt_handle);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Timer Attach Interrupt failed, error num=%d", err);
  }
  gptimer_enable(timer->timer_handle);
  if (timer->timer_started == true) {
    gptimer_start(timer->timer_handle);
  }
}

void timer_attach_interrupt_arg(hw_timer_t *timer, void (*userFunc)(void *), void *arg) {
  timer_attach_interrupt_functional_arg(timer, userFunc, arg);
}

void timer_attach_interrupt(hw_timer_t *timer, voidFuncPtr userFunc) {
  timer_attach_interrupt_functional_arg(timer, (voidFuncPtrArg) userFunc, NULL);
}

void timer_detach_interrupt(hw_timer_t *timer) {
  if (timer == NULL) {
    ESP_LOGE(TAG, "Timer handle is NULL");
    return;
  }
  esp_err_t err = ESP_OK;
  err = gptimer_set_alarm_action(timer->timer_handle, NULL);
  timer->interrupt_handle.fn = NULL;
  timer->interrupt_handle.arg = NULL;
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Timer Detach Interrupt failed, error num=%d", err);
  }
}

void timer_alarm(hw_timer_t *timer, uint64_t alarm_value, bool autoreload, uint64_t reload_count) {
  if (timer == NULL) {
    ESP_LOGE(TAG, "Timer handle is NULL");
    return;
  }
  esp_err_t err = ESP_OK;
  gptimer_alarm_config_t alarm_cfg = {
      .alarm_count = alarm_value,
      .reload_count = reload_count,
      .flags = {.auto_reload_on_alarm = autoreload},
  };
  err = gptimer_set_alarm_action(timer->timer_handle, &alarm_cfg);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Timer Alarm Write failed, error num=%d", err);
  }
}

void timer_start(hw_timer_t *timer) {
  if (timer == NULL) {
    ESP_LOGE(TAG, "Timer handle is NULL");
    return;
  }
  gptimer_start(timer->timer_handle);
  timer->timer_started = true;
}

}  // namespace ac_dimmer
}  // namespace esphome
#endif
