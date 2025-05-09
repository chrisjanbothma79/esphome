#pragma once
#include "as734xbase.h"

namespace esphome {
namespace as734x {

class AS7343 : public AS734xBase {
 public:
  static constexpr uint8_t NUM_CHANNELS = 13;

  // datasheet values
  static const CalibrationParams DEFAULT_CORRECTION;
  static const float GAIN_CORRECTION[Gain::AS734X_MAX_GAIN][NUM_CHANNELS];
  static const float XYZ_PER_COUNT[3][NUM_CHANNELS];

  // precalculated values
  static const float IRRAD_MW_PER_COUNT[NUM_CHANNELS];
  static const float IRRAD_PAR_E_MW_PER_COUNT[NUM_CHANNELS];
  static const float IRRAD_PHOTOPIC_MW_PER_COUNT[NUM_CHANNELS];
  static const float PPFD_UMOL_PER_COUNT[NUM_CHANNELS];

 public:
  AS7343(i2c::I2CDevice *i2c_device);

  const RegisterMap &registers() const override { return AS7343::REG_MAP; }

  const CalibrationParams &get_default_correction() const override { return DEFAULT_CORRECTION; }

  virtual bool verify_device_id() override;
  virtual void write_default_config() override;

  virtual uint8_t get_number_of_smux_steps() const override { return 1; }
  virtual bool prepare_for_smux_step(uint8_t step) override { return true; };
  virtual bool is_smux_ready() override { return true; };

  virtual bool read_and_discard_channels() override;
  virtual bool read_channels(uint8_t step, ChannelValuesUint16 &values, Gain &gain, bool &saturated) override;

  virtual float get_gain_correction(const uint8_t channel, const Gain gain) override;
  virtual void get_bc_conversion(const uint8_t channel, float &mw, float &mw_photopic, float &mw_par,
                                 float &umol_ppdf) override;
  virtual void get_xyz_conversion(const uint8_t channel, float &tri_x, float &tri_y, float &tri_z) override;

 protected:
  static const RegisterMap REG_MAP;
  void direct_config_3_chain_();
};

}  // namespace as734x
}  // namespace esphome
