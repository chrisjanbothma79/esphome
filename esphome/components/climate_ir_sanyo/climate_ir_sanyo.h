// climate_ir_sanyo.h
#pragma once

#include "esphome/components/climate_ir/climate_ir.h"
#include "esphome/components/remote_base/nec_like_protocol.h"

/* Set to 1 to mimic simulating sending codes based on the current configuration.
 * Used to verify that we will generate the same IR code that the remote does.
 */
#define VERIFY_GENERATION 0

namespace esphome {
namespace climate_ir_sanyo {

class Frame {
 public:
  Frame();
  void clear();

#if VERIFY_GENERATION
  void compare(const Frame &other);
#endif

  void set_target_temperature(float temp);
  float get_target_temperature();

  void set_room_temperature(float temp);
  float get_room_temperature();

  void set_mode(climate::ClimateMode mode);
  climate::ClimateMode get_mode();

  void set_fan_mode(climate::ClimateFanMode fan);
  climate::ClimateFanMode get_fan_mode();

  void set_swing_mode(climate::ClimateSwingMode swing);
  climate::ClimateSwingMode get_swing_mode();

  void set_room_sensing(bool on);
  bool get_room_sensing();

  void set_power(bool on);
  bool get_power();

  void set_night_setback(bool on);
  bool get_night_setback();

  remote_base::NECLikeData to_bits();
  bool from_bits(const remote_base::NECLikeData &data_bits);

 private:
  uint8_t nibbles[12];
  uint8_t calculate_checksum();
  void update_checksum();
};

class SanyoIrClimate : public climate_ir::ClimateIR {
 public:
  SanyoIrClimate();
  void set_room_sensing(bool on);
  bool get_room_sensing();
  void set_night_setback(bool on);
  bool get_night_setback();

 protected:
  void transmit_state() override;
  bool on_receive(remote_base::RemoteReceiveData src) override;
  void dump_state_();

 private:
  Frame frame;
};

}  // namespace climate_ir_sanyo
}  // namespace esphome
