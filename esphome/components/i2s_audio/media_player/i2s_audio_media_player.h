#pragma once

#ifdef USE_ESP32

#include "../i2s_audio.h"
#include "esphome/components/media_player/media_player.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/helpers.h"

// Framework-specific includes are handled in the respective implementation files

namespace esphome {
namespace i2s_audio {

// Forward declarations for framework-specific types
class Audio;  // Arduino framework Audio class

enum I2SState : uint8_t {
  I2S_STATE_STOPPED = 0,
  I2S_STATE_STARTING,
  I2S_STATE_RUNNING,
  I2S_STATE_STOPPING,
};

class I2SAudioMediaPlayer : public Component, public Parented<I2SAudioComponent>, public media_player::MediaPlayer {
 public:
  void setup() override;
  float get_setup_priority() const override { return esphome::setup_priority::LATE; }

  void loop() override;
  void dump_config() override;

  /// @brief Set the data out pin for I2S
  void set_dout_pin(uint8_t pin) { this->dout_pin_ = pin; }

  /// @brief Set the mute pin (optional)
  void set_mute_pin(GPIOPin *mute_pin) { this->mute_pin_ = mute_pin; }

#if SOC_I2S_SUPPORTS_DAC
  /// @brief Set internal DAC mode (legacy driver only)
  void set_internal_dac_mode(i2s_dac_mode_t mode) { this->internal_dac_mode_ = mode; }
#endif  // SOC_I2S_SUPPORTS_DAC

  /// @brief Set number of external DAC channels
  void set_external_dac_channels(uint8_t channels) { this->external_dac_channels_ = channels; }

  /// @brief Set I2S communication format (LSB for Arduino compatibility)
  void set_i2s_comm_fmt_lsb(bool lsb) { this->i2s_comm_fmt_lsb_ = lsb; }

  media_player::MediaPlayerTraits get_traits() override;
  bool is_muted() const override { return this->muted_; }

  void start();
  void stop();

 protected:
  void control(const media_player::MediaPlayerCall &call) override;

  /// @brief Mute the audio output
  void mute_();

  /// @brief Unmute the audio output
  void unmute_();

  /// @brief Set volume level (0.0 to 1.0)
  /// @param volume Volume level
  /// @param publish Whether to publish state change
  void set_volume_(float volume, bool publish = true);

  // Framework-specific protected methods are declared in the implementation files

  // Common member variables
  I2SState i2s_state_{I2S_STATE_STOPPED};
  uint8_t dout_pin_{0};
  GPIOPin *mute_pin_{nullptr};
  bool muted_{false};
  uint8_t external_dac_channels_{2};
  bool i2s_comm_fmt_lsb_{false};
  HighFrequencyLoopRequester high_freq_;
  optional<std::string> current_url_{};
  bool is_announcement_{false};

#if SOC_I2S_SUPPORTS_DAC
  i2s_dac_mode_t internal_dac_mode_{I2S_DAC_CHANNEL_DISABLE};
#endif  // SOC_I2S_SUPPORTS_DAC

  // Arduino framework member variable
  std::unique_ptr<Audio> audio_;
};

}  // namespace i2s_audio
}  // namespace esphome

#endif  // USE_ESP32
