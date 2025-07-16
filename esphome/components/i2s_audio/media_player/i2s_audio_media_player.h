#pragma once

#ifdef USE_ESP32

#include "../i2s_audio.h"
#include "esphome/components/media_player/media_player.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/helpers.h"

#include <driver/i2s.h>

// Forward declarations
class Audio;  // Arduino framework Audio class

#ifdef USE_ESP_IDF
/// @brief Audio format information for ESP-IDF implementation
struct AudioFormat;
#endif  // USE_ESP_IDF

namespace esphome {
namespace i2s_audio {

/// @brief I2S media player state enumeration
enum I2SState : uint8_t {
  I2S_STATE_STOPPED = 0,  ///< Media player is stopped
  I2S_STATE_STARTING,     ///< Media player is starting
  I2S_STATE_RUNNING,      ///< Media player is running
  I2S_STATE_STOPPING,     ///< Media player is stopping
};

/// @brief I2S Audio Media Player component supporting both Arduino and ESP-IDF frameworks
class I2SAudioMediaPlayer : public Component, public Parented<I2SAudioComponent>, public media_player::MediaPlayer {
 public:
  void setup() override;
  float get_setup_priority() const override { return esphome::setup_priority::LATE; }

  void loop() override;
  void dump_config() override;

  /// @brief Set the data out pin for I2S
  /// @param pin GPIO pin number for I2S data out
  void set_dout_pin(uint8_t pin) { this->dout_pin_ = pin; }

  /// @brief Set the mute pin (optional)
  /// @param mute_pin GPIO pin for muting audio output
  void set_mute_pin(GPIOPin *mute_pin) { this->mute_pin_ = mute_pin; }

#if SOC_I2S_SUPPORTS_DAC
  /// @brief Set internal DAC mode (legacy driver only)
  /// @param mode Internal DAC mode configuration
  void set_internal_dac_mode(i2s_dac_mode_t mode) { this->internal_dac_mode_ = mode; }
#endif  // SOC_I2S_SUPPORTS_DAC

  /// @brief Set number of external DAC channels
  /// @param channels Number of audio channels (1=mono, 2=stereo)
  void set_external_dac_channels(uint8_t channels) { this->external_dac_channels_ = channels; }

  /// @brief Set I2S communication format (LSB for Arduino compatibility)
  /// @param lsb True for LSB format, false for MSB
  void set_i2s_comm_fmt_lsb(bool lsb) { this->i2s_comm_fmt_lsb_ = lsb; }

  media_player::MediaPlayerTraits get_traits() override;
  bool is_muted() const override { return this->muted_; }

  /// @brief Start media playback
  void start();

  /// @brief Stop media playback
  void stop();

 protected:
  void control(const media_player::MediaPlayerCall &call) override;

  /// @brief Mute the audio output
  void mute_();

  /// @brief Unmute the audio output
  void unmute_();

  /// @brief Set volume level (0.0 to 1.0)
  /// @param volume Volume level between 0.0 and 1.0
  /// @param publish Whether to publish state change
  void set_volume_(float volume, bool publish = true);

  // Framework-specific protected methods
#ifdef USE_ESP32_FRAMEWORK_ARDUINO
  /// @brief Arduino-specific audio playback loop
  void play_();

  /// @brief Arduino-specific start implementation
  void start_();

  /// @brief Arduino-specific stop implementation
  void stop_();
#endif  // USE_ESP32_FRAMEWORK_ARDUINO

#ifdef USE_ESP_IDF
  /// @brief ESP-IDF specific task creation
  void start_task_();

  /// @brief ESP-IDF specific task cleanup
  void stop_task_();

  /// @brief ESP-IDF media player task function
  /// @param params Task parameters (I2SAudioMediaPlayer instance)
  static void media_player_task(void *params);

  /// @brief Start I2S driver with specified audio format
  /// @param format Audio format configuration
  /// @return ESP_OK on success, error code otherwise
  esp_err_t start_i2s_driver_(const struct AudioFormat &format);

  /// @brief Stop I2S driver
  void stop_i2s_driver_();

  /// @brief Start HTTP client for streaming
  /// @param url Audio stream URL
  /// @return ESP_OK on success, error code otherwise
  esp_err_t start_http_client_(const std::string &url);

  /// @brief Stop HTTP client
  void stop_http_client_();

  /// @brief Parse audio format from HTTP stream
  /// @return True if format was successfully parsed
  bool parse_audio_format_();

  /// @brief Apply volume control to audio data
  /// @param audio_data Audio data buffer
  /// @param len Length of audio data
  void apply_volume_control_(uint8_t *audio_data, size_t len);
#endif  // USE_ESP_IDF

  // Common member variables
  I2SState i2s_state_{I2S_STATE_STOPPED};          ///< Current I2S state
  uint8_t dout_pin_{0};                             ///< I2S data out pin
  GPIOPin *mute_pin_{nullptr};                      ///< Optional mute pin
  bool muted_{false};                               ///< Current mute state
  uint8_t external_dac_channels_{2};                ///< Number of external DAC channels
  bool i2s_comm_fmt_lsb_{false};                    ///< I2S communication format (LSB/MSB)
  HighFrequencyLoopRequester high_freq_;            ///< High frequency loop requester
  optional<std::string> current_url_{};             ///< Current media URL
  bool is_announcement_{false};                     ///< Whether current playback is an announcement

#if SOC_I2S_SUPPORTS_DAC
  i2s_dac_mode_t internal_dac_mode_{I2S_DAC_CHANNEL_DISABLE};  ///< Internal DAC mode
#endif  // SOC_I2S_SUPPORTS_DAC

#ifdef USE_ESP32_FRAMEWORK_ARDUINO
  std::unique_ptr<Audio> audio_;  ///< Arduino framework Audio instance
#endif  // USE_ESP32_FRAMEWORK_ARDUINO
};

}  // namespace i2s_audio
}  // namespace esphome

#endif  // USE_ESP32
