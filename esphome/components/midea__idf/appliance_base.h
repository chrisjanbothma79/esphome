// esphome/components/midea/appliance_base.h
#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/uart/uart.h"

// Incluimos nuestra capa de compatibilidad y la librería vendida
#include "midea_compat.h"
#include "lib/Appliance/ApplianceBase.h"
#include "ir_transmitter.h"

namespace esphome {
namespace midea {

template<typename T> class ApplianceBase : public Component, public uart::UARTDevice {
  static_assert(std::is_base_of<dudanov::midea::ApplianceBase, T>::value,
                "T must derive from dudanov::midea::ApplianceBase class");

 public:
  ApplianceBase() {
    // La librería espera un puntero a un Stream. `uart::UARTDevice` hereda de `Stream`,
    // así que podemos pasar 'this' directamente.
    this->base_.setStream(this);
    this->base_.addOnStateCallback([this]() { this->on_status_change(); });

    // El logger de la librería se redirige al logger de ESPHome
    dudanov::midea::ApplianceBase::setLogger(
        [](int level, const char *tag, int line, const String &format, va_list args) {
          esp_log_vprintf_(level, tag, line, format.c_str(), args);
        });
  }

#ifdef USE_REMOTE_TRANSMITTER
  void set_transmitter(RemoteTransmitterBase *transmitter) { this->transmitter_.set_transmitter(transmitter); }
#endif

  // Las funciones de configuración de UART ahora son manejadas por uart::UARTDevice
  void set_period(uint32_t ms) { this->base_.setPeriod(ms); }
  void set_response_timeout(uint32_t ms) { this->base_.setTimeout(ms); }
  void set_request_attempts(uint32_t attempts) { this->base_.setNumAttempts(attempts); }

  // Métodos de Component
  void setup() override { this->base_.setup(); }
  void loop() override { this->base_.loop(); }
  float get_setup_priority() const override { return setup_priority::BEFORE_CONNECTION; }
  bool can_proceed() override {
    return this->base_.getAutoconfStatus() != dudanov::midea::AutoconfStatus::AUTOCONF_PROGRESS;
  }

  void set_beeper_feedback(bool state) { this->base_.setBeeper(state); }
  void set_autoconf(bool value) { this->base_.setAutoconf(value); }
  virtual void on_status_change() = 0;

 protected:
  T base_;
#ifdef USE_REMOTE_TRANSMITTER
  IrTransmitter transmitter_;
#endif
};

}  // namespace midea
}  // namespace esphome
