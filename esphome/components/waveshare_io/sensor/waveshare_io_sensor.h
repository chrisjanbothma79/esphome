#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"

#include "esphome/components/sensor/sensor.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"

#include "../waveshare_io.h"

namespace esphome {
namespace waveshare_io {

class WaveshareIOSensor : public sensor::Sensor,
                          public PollingComponent,
                          public voltage_sampler::VoltageSampler,
                          public Parented<WaveshareIOComponent> {
 public:
  void set_reference_voltage(float reference_voltage) { this->reference_voltage_ = reference_voltage; }

  void update() override;
  void dump_config() override;
  float get_setup_priority() const override;
  float sample() override;

 protected:
  float reference_voltage_;
};

}  // namespace waveshare_io
}  // namespace esphome
