#pragma once
#include "as734xbase.h"

namespace esphome {
namespace as734x {

class AS7341 : public AS734xBase {
 public:
  static constexpr uint8_t NUM_CHANNELS = 10;

  // datasheet values
  static const CalibrationParams DEFAULT_CORRECTION;
  static const float GAIN_CORRECTION[Gain::AS734X_MAX_GAIN];
  static const float XYZ_PER_COUNT[3][NUM_CHANNELS];

  // precalculated values
  static const float IRRAD_MW_PER_COUNT[NUM_CHANNELS];
  static const float IRRAD_PAR_E_MW_PER_COUNT[NUM_CHANNELS];
  static const float IRRAD_PHOTOPIC_MW_PER_COUNT[NUM_CHANNELS];
  static const float PPFD_UMOL_PER_COUNT[NUM_CHANNELS];

 public:
  AS7341(i2c::I2CDevice *i2c_device);
  const RegisterMap &registers() const override { return AS7341::REG_MAP; }

  const CalibrationParams &get_default_correction() const override { return DEFAULT_CORRECTION; }

  virtual bool verify_device_id() override;
  virtual void write_default_config() override;

  virtual uint8_t get_number_of_smux_steps() const override { return 2; }
  virtual bool prepare_for_smux_step(uint8_t step) override;

  virtual bool read_and_discard_channels() override;
  virtual bool read_channels(uint8_t step, ChannelValuesUint16 &values, Gain &gain, bool &saturated) override;

  virtual float get_gain_correction(uint8_t channel, Gain gain) override;
  virtual void get_bc_conversion(uint8_t channel, float &mw, float &mw_photopic, float &mw_par,
                                 float &umol_ppdf) override;
  virtual void get_xyz_conversion(uint8_t channel, float &tri_x, float &tri_y, float &tri_z) override;

 protected:
  static const RegisterMap REG_MAP;

  bool read_low_channels_();
  bool read_high_channels_();
  bool set_smux_command_(uint8_t command);

  void configure_smux_low_channels_();
  void configure_smux_high_channels_();
  bool enable_smux_();
};

}  // namespace as734x
}  // namespace esphome
