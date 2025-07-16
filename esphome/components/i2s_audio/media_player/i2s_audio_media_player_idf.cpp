#include "i2s_audio_media_player.h"

#if defined(USE_ESP32) && defined(USE_ESP_IDF)

#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include <esp_log.h>
#include <esp_timer.h>
#include <esp_http_client.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <string.h>

#ifdef USE_I2S_LEGACY
#include <driver/i2s.h>
#else  // !USE_I2S_LEGACY
#include <driver/i2s_std.h>
#endif  // USE_I2S_LEGACY

namespace esphome {
namespace i2s_audio {

static const char *const TAG = "i2s_audio.media_player";

static const uint32_t TASK_STACK_SIZE = 8192;
static const UBaseType_t TASK_PRIORITY = 5;
static const uint32_t HTTP_BUFFER_SIZE = 4096;
static const uint32_t I2S_DMA_BUFFER_COUNT = 8;
static const uint32_t I2S_DMA_BUFFER_LEN = 512;
static const TickType_t TASK_DELAY_MS = pdMS_TO_TICKS(10);
static const uint32_t HTTP_TIMEOUT_MS = 5000;

/// @brief Event group bits for media player task communication
enum MediaPlayerEventGroupBits : uint32_t {
  COMMAND_START = (1 << 0),       ///< Start playback command
  COMMAND_STOP = (1 << 1),        ///< Stop playback command
  COMMAND_PAUSE = (1 << 2),       ///< Pause playback command
  COMMAND_RESUME = (1 << 3),      ///< Resume playback command
  COMMAND_SET_VOLUME = (1 << 4),  ///< Set volume command

  STATE_STARTING = (1 << 10),  ///< Task starting state
  STATE_RUNNING = (1 << 11),   ///< Task running state
  STATE_PAUSED = (1 << 12),    ///< Task paused state
  STATE_STOPPING = (1 << 13),  ///< Task stopping state
  STATE_STOPPED = (1 << 14),   ///< Task stopped state

  ERR_HTTP_FAILED = (1 << 20),  ///< HTTP connection failed
  ERR_I2S_FAILED = (1 << 21),   ///< I2S operation failed
  ERR_TASK_FAILED = (1 << 22),  ///< Task creation failed
  ERR_NO_MEMORY = (1 << 23),    ///< Memory allocation failed

  ALL_ERR_BITS = ERR_HTTP_FAILED | ERR_I2S_FAILED | ERR_TASK_FAILED | ERR_NO_MEMORY,
  ALL_BITS = 0x00FFFFFF,  ///< All valid FreeRTOS event group bits
};

/// @brief Audio format information for ESP-IDF implementation
struct AudioFormat {
  uint32_t sample_rate{44100};  ///< Sample rate in Hz
  uint8_t channels{2};          ///< Number of channels (1=mono, 2=stereo)
  uint8_t bits_per_sample{16};  ///< Bits per sample (8, 16, 24, 32)
};

/// @brief ESP-IDF specific data for each media player instance
struct ESPIDFData {
  TaskHandle_t task_handle_{nullptr};
  EventGroupHandle_t event_group_{nullptr};
  esp_http_client_handle_t http_client_{nullptr};

#ifdef USE_I2S_LEGACY
  // Legacy I2S driver state - no additional members needed
#else   // !USE_I2S_LEGACY
  i2s_chan_handle_t tx_handle_{nullptr};
#endif  // USE_I2S_LEGACY

  AudioFormat audio_format_;
  uint8_t *audio_buffer_{nullptr};
  size_t audio_buffer_size_{4096};
  bool task_running_{false};
  bool i2s_driver_installed_{false};
  uint8_t volume_level_{21};  ///< Volume level (0-21, matching Arduino library)
};

// Static map to store ESP-IDF specific data for each media player instance
static std::map<I2SAudioMediaPlayer *, ESPIDFData> esp_idf_data;

/// @brief HTTP event handler for audio streaming
static esp_err_t http_event_handler(esp_http_client_event_t *evt) {
  switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
      ESP_LOGE(TAG, "HTTP error occurred");
      break;
    case HTTP_EVENT_ON_CONNECTED:
      ESP_LOGD(TAG, "HTTP connected");
      break;
    case HTTP_EVENT_ON_DATA:
      // Data is handled in the task loop
      break;
    case HTTP_EVENT_ON_FINISH:
      ESP_LOGD(TAG, "HTTP finished");
      break;
    case HTTP_EVENT_DISCONNECTED:
      ESP_LOGD(TAG, "HTTP disconnected");
      break;
    default:
      break;
  }
  return ESP_OK;
}

void I2SAudioMediaPlayer::setup() {
  ESP_LOGCONFIG(TAG, "Running setup");
  this->state = media_player::MEDIA_PLAYER_STATE_IDLE;

  auto &data = esp_idf_data[this];

  // Create event group for task communication
  data.event_group_ = xEventGroupCreate();
  if (data.event_group_ == nullptr) {
    ESP_LOGE(TAG, "Failed to create event group");
    this->mark_failed();
    return;
  }

  // Allocate audio buffer
  data.audio_buffer_ = static_cast<uint8_t *>(heap_caps_malloc(data.audio_buffer_size_, MALLOC_CAP_DMA));
  if (data.audio_buffer_ == nullptr) {
    ESP_LOGE(TAG, "Failed to allocate audio buffer");
    this->mark_failed();
    return;
  }

  // Set default audio format
  data.audio_format_.sample_rate = 44100;
  data.audio_format_.channels = 2;
  data.audio_format_.bits_per_sample = 16;
}

void I2SAudioMediaPlayer::loop() {
  auto &data = esp_idf_data[this];
  if (data.event_group_ == nullptr) {
    return;
  }

  uint32_t event_bits = xEventGroupGetBits(data.event_group_);

  // Handle state changes
  if (event_bits & MediaPlayerEventGroupBits::STATE_STARTING) {
    ESP_LOGD(TAG, "Media player starting");
    this->state = media_player::MEDIA_PLAYER_STATE_PLAYING;
    if (this->is_announcement_) {
      this->state = media_player::MEDIA_PLAYER_STATE_ANNOUNCING;
    }
    this->publish_state();
    xEventGroupClearBits(data.event_group_, MediaPlayerEventGroupBits::STATE_STARTING);
  }

  if (event_bits & MediaPlayerEventGroupBits::STATE_RUNNING) {
    ESP_LOGD(TAG, "Media player running");
    xEventGroupClearBits(data.event_group_, MediaPlayerEventGroupBits::STATE_RUNNING);
  }

  if (event_bits & MediaPlayerEventGroupBits::STATE_PAUSED) {
    ESP_LOGD(TAG, "Media player paused");
    this->state = media_player::MEDIA_PLAYER_STATE_PAUSED;
    this->publish_state();
    xEventGroupClearBits(data.event_group_, MediaPlayerEventGroupBits::STATE_PAUSED);
  }

  if (event_bits & MediaPlayerEventGroupBits::STATE_STOPPED) {
    ESP_LOGD(TAG, "Media player stopped");
    this->state = media_player::MEDIA_PLAYER_STATE_IDLE;
    this->i2s_state_ = I2S_STATE_STOPPED;
    this->is_announcement_ = false;
    this->high_freq_.stop();
    this->publish_state();
    xEventGroupClearBits(data.event_group_, MediaPlayerEventGroupBits::STATE_STOPPED);
  }

  // Handle errors
  if (event_bits & MediaPlayerEventGroupBits::ALL_ERR_BITS) {
    if (event_bits & MediaPlayerEventGroupBits::ERR_HTTP_FAILED) {
      ESP_LOGE(TAG, "HTTP connection failed");
    }
    if (event_bits & MediaPlayerEventGroupBits::ERR_I2S_FAILED) {
      ESP_LOGE(TAG, "I2S operation failed");
    }
    if (event_bits & MediaPlayerEventGroupBits::ERR_TASK_FAILED) {
      ESP_LOGE(TAG, "Task creation failed");
    }
    if (event_bits & MediaPlayerEventGroupBits::ERR_NO_MEMORY) {
      ESP_LOGE(TAG, "Memory allocation failed");
    }

    this->state = media_player::MEDIA_PLAYER_STATE_IDLE;
    this->i2s_state_ = I2S_STATE_STOPPED;
    this->publish_state();
    xEventGroupClearBits(data.event_group_, MediaPlayerEventGroupBits::ALL_ERR_BITS);
  }
}

void I2SAudioMediaPlayer::control(const media_player::MediaPlayerCall &call) {
  auto &data = esp_idf_data[this];

  media_player::MediaPlayerState play_state = media_player::MEDIA_PLAYER_STATE_PLAYING;
  if (call.get_announcement().has_value()) {
    play_state = call.get_announcement().value() ? media_player::MEDIA_PLAYER_STATE_ANNOUNCING
                                                 : media_player::MEDIA_PLAYER_STATE_PLAYING;
  }

  if (call.get_media_url().has_value()) {
    this->current_url_ = call.get_media_url();
    if (this->i2s_state_ != I2S_STATE_STOPPED) {
      this->stop();
    }
    this->start();
  }

  if (play_state == media_player::MEDIA_PLAYER_STATE_ANNOUNCING) {
    this->is_announcement_ = true;
  }

  if (call.get_volume().has_value()) {
    this->volume = call.get_volume().value();
    this->set_volume_(volume);
    this->unmute_();
  }

  if (call.get_command().has_value()) {
    switch (call.get_command().value()) {
      case media_player::MEDIA_PLAYER_COMMAND_MUTE:
        this->mute_();
        break;
      case media_player::MEDIA_PLAYER_COMMAND_UNMUTE:
        this->unmute_();
        break;
      case media_player::MEDIA_PLAYER_COMMAND_VOLUME_UP: {
        float new_volume = this->volume + 0.1f;
        if (new_volume > 1.0f)
          new_volume = 1.0f;
        this->set_volume_(new_volume);
        this->unmute_();
        break;
      }
      case media_player::MEDIA_PLAYER_COMMAND_VOLUME_DOWN: {
        float new_volume = this->volume - 0.1f;
        if (new_volume < 0.0f)
          new_volume = 0.0f;
        this->set_volume_(new_volume);
        this->unmute_();
        break;
      }
      default:
        break;
    }

    // ESP-IDF specific command handling
    if (data.event_group_ != nullptr) {
      switch (call.get_command().value()) {
        case media_player::MEDIA_PLAYER_COMMAND_PLAY:
          xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_RESUME);
          this->state = play_state;
          break;
        case media_player::MEDIA_PLAYER_COMMAND_PAUSE:
          xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_PAUSE);
          break;
        case media_player::MEDIA_PLAYER_COMMAND_STOP:
          this->stop();
          break;
        case media_player::MEDIA_PLAYER_COMMAND_TOGGLE:
          if (this->state == media_player::MEDIA_PLAYER_STATE_PAUSED) {
            xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_RESUME);
          } else {
            xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_PAUSE);
          }
          break;
        default:
          break;
      }
    }
  }
  this->publish_state();
}

void I2SAudioMediaPlayer::mute_() {
  if (this->mute_pin_ != nullptr) {
    this->mute_pin_->digital_write(true);
  } else {
    this->set_volume_(0.0f, false);
  }
  this->muted_ = true;
}

void I2SAudioMediaPlayer::unmute_() {
  if (this->mute_pin_ != nullptr) {
    this->mute_pin_->digital_write(false);
  } else {
    this->set_volume_(this->volume, false);
  }
  this->muted_ = false;
}

void I2SAudioMediaPlayer::set_volume_(float volume, bool publish) {
  auto &data = esp_idf_data[this];
  data.volume_level_ = remap<uint8_t, float>(volume, 0.0f, 1.0f, 0, 21);
  if (data.event_group_ != nullptr) {
    xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_SET_VOLUME);
  }

  if (publish)
    this->volume = volume;
}

media_player::MediaPlayerTraits I2SAudioMediaPlayer::get_traits() {
  auto traits = media_player::MediaPlayerTraits();
  traits.set_supports_pause(true);
  return traits;
}

void I2SAudioMediaPlayer::start() {
  this->i2s_state_ = I2S_STATE_STARTING;
  this->start_task_();
}

void I2SAudioMediaPlayer::stop() {
  if (this->i2s_state_ == I2S_STATE_STOPPED) {
    return;
  }
  if (this->i2s_state_ == I2S_STATE_STARTING) {
    this->i2s_state_ = I2S_STATE_STOPPED;
    return;
  }
  this->i2s_state_ = I2S_STATE_STOPPING;
  this->stop_task_();
}

void I2SAudioMediaPlayer::dump_config() {
  ESP_LOGCONFIG(TAG, "I2S Audio Media Player:");
  if (this->is_failed()) {
    ESP_LOGCONFIG(TAG, "  Setup failed!");
    return;
  }

#if SOC_I2S_SUPPORTS_DAC
  if (this->internal_dac_mode_ != I2S_DAC_CHANNEL_DISABLE) {
    switch (this->internal_dac_mode_) {
      case I2S_DAC_CHANNEL_LEFT_EN:
        ESP_LOGCONFIG(TAG, "  Internal DAC mode: Left");
        break;
      case I2S_DAC_CHANNEL_RIGHT_EN:
        ESP_LOGCONFIG(TAG, "  Internal DAC mode: Right");
        break;
      case I2S_DAC_CHANNEL_BOTH_EN:
        ESP_LOGCONFIG(TAG, "  Internal DAC mode: Left & Right");
        break;
      default:
        break;
    }
  } else {
#endif  // SOC_I2S_SUPPORTS_DAC
    ESP_LOGCONFIG(TAG, "  External DAC channels: %d", this->external_dac_channels_);
    ESP_LOGCONFIG(TAG, "  I2S DOUT Pin: %d", this->dout_pin_);
    LOG_PIN("  Mute Pin: ", this->mute_pin_);
#if SOC_I2S_SUPPORTS_DAC
  }
#endif  // SOC_I2S_SUPPORTS_DAC

  ESP_LOGCONFIG(TAG, "  Framework: ESP-IDF");
  ESP_LOGCONFIG(TAG, "  Audio buffer size: %d bytes", esp_idf_data[this].audio_buffer_size_);
}

// Private ESP-IDF specific methods
void I2SAudioMediaPlayer::start_task_() {
  auto &data = esp_idf_data[this];
  if (data.task_running_ || data.task_handle_ != nullptr) {
    return;
  }

  BaseType_t result =
      xTaskCreate(media_player_task, "media_player_task", TASK_STACK_SIZE, this, TASK_PRIORITY, &data.task_handle_);

  if (result != pdPASS || data.task_handle_ == nullptr) {
    ESP_LOGE(TAG, "Failed to create media player task");
    xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::ERR_TASK_FAILED);
    return;
  }

  data.task_running_ = true;
  this->high_freq_.start();
  xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_START);
}

void I2SAudioMediaPlayer::stop_task_() {
  auto &data = esp_idf_data[this];
  if (!data.task_running_ || data.task_handle_ == nullptr) {
    return;
  }

  xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_STOP);

  // Wait for task to finish (with timeout)
  uint32_t timeout_count = 0;
  while (data.task_running_ && timeout_count < 100) {
    vTaskDelay(pdMS_TO_TICKS(50));
    timeout_count++;
  }

  if (data.task_running_) {
    ESP_LOGW(TAG, "Task did not stop gracefully, forcing deletion");
    if (data.task_handle_ != nullptr) {
      vTaskDelete(data.task_handle_);
      data.task_handle_ = nullptr;
    }
    data.task_running_ = false;
  }
}

void I2SAudioMediaPlayer::media_player_task(void *params) {
  I2SAudioMediaPlayer *player = static_cast<I2SAudioMediaPlayer *>(params);
  auto &data = esp_idf_data[player];
  bool paused = false;

  ESP_LOGD(TAG, "Media player task started");

  // Wait for start command
  xEventGroupWaitBits(data.event_group_, MediaPlayerEventGroupBits::COMMAND_START,
                      pdTRUE,   // Clear on exit
                      pdFALSE,  // Don't wait for all bits
                      portMAX_DELAY);

  xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::STATE_STARTING);

  // Start HTTP client
  if (player->current_url_.has_value()) {
    esp_err_t err = player->start_http_client_(player->current_url_.value());
    if (err != ESP_OK) {
      ESP_LOGE(TAG, "Failed to start HTTP client: %s", esp_err_to_name(err));
      xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::ERR_HTTP_FAILED);
      goto task_cleanup;
    }
  } else {
    ESP_LOGE(TAG, "No URL provided for playback");
    xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::ERR_HTTP_FAILED);
    goto task_cleanup;
  }

  // Parse audio format from stream
  if (!player->parse_audio_format_()) {
    ESP_LOGW(TAG, "Could not parse audio format, using defaults");
  }

  // Start I2S driver
  esp_err_t err = player->start_i2s_driver_(data.audio_format_);
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "Failed to start I2S driver: %s", esp_err_to_name(err));
    xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::ERR_I2S_FAILED);
    goto task_cleanup;
  }

  xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::STATE_RUNNING);

  // Main playback loop
  while (true) {
    uint32_t event_bits = xEventGroupWaitBits(
        data.event_group_,
        MediaPlayerEventGroupBits::COMMAND_STOP | MediaPlayerEventGroupBits::COMMAND_PAUSE |
            MediaPlayerEventGroupBits::COMMAND_RESUME | MediaPlayerEventGroupBits::COMMAND_SET_VOLUME,
        pdTRUE,   // Clear on exit
        pdFALSE,  // Don't wait for all bits
        TASK_DELAY_MS);

    // Handle stop command
    if (event_bits & MediaPlayerEventGroupBits::COMMAND_STOP) {
      break;
    }

    // Handle pause command
    if (event_bits & MediaPlayerEventGroupBits::COMMAND_PAUSE) {
      paused = true;
      xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::STATE_PAUSED);
    }

    // Handle resume command
    if (event_bits & MediaPlayerEventGroupBits::COMMAND_RESUME) {
      paused = false;
      xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::STATE_RUNNING);
    }

    // Handle volume change
    if (event_bits & MediaPlayerEventGroupBits::COMMAND_SET_VOLUME) {
      ESP_LOGD(TAG, "Volume changed to level %d", data.volume_level_);
    }

    if (paused) {
      vTaskDelay(pdMS_TO_TICKS(100));
      continue;
    }

    // Read audio data from HTTP stream
    size_t bytes_read =
        esp_http_client_read(data.http_client_, reinterpret_cast<char *>(data.audio_buffer_), data.audio_buffer_size_);

    if (bytes_read <= 0) {
      ESP_LOGD(TAG, "End of stream or read error, stopping playback");
      break;
    }

    // Apply volume control
    player->apply_volume_control_(data.audio_buffer_, bytes_read);

    // Write to I2S
    size_t bytes_written = 0;
#ifdef USE_I2S_LEGACY
    esp_err_t write_err =
        i2s_write(player->parent_->get_port(), data.audio_buffer_, bytes_read, &bytes_written, pdMS_TO_TICKS(100));
#else   // !USE_I2S_LEGACY
    esp_err_t write_err =
        i2s_channel_write(data.tx_handle_, data.audio_buffer_, bytes_read, &bytes_written, pdMS_TO_TICKS(100));
#endif  // USE_I2S_LEGACY

    if (write_err != ESP_OK) {
      ESP_LOGW(TAG, "I2S write error: %s", esp_err_to_name(write_err));
      if (write_err != ESP_ERR_TIMEOUT) {
        xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::ERR_I2S_FAILED);
        break;
      }
    }
  }

task_cleanup:
  // Cleanup
  player->stop_i2s_driver_();
  player->stop_http_client_();

  xEventGroupSetBits(data.event_group_, MediaPlayerEventGroupBits::STATE_STOPPED);
  data.task_running_ = false;
  data.task_handle_ = nullptr;

  ESP_LOGD(TAG, "Media player task ended");
  vTaskDelete(nullptr);
}

esp_err_t I2SAudioMediaPlayer::start_i2s_driver_(const AudioFormat &format) {
  auto &data = esp_idf_data[this];

  if (!this->parent_->try_lock()) {
    return ESP_ERR_INVALID_STATE;
  }

  esp_err_t err;

#ifdef USE_I2S_LEGACY
  i2s_config_t i2s_config = {
      .mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = format.sample_rate,
      .bits_per_sample = static_cast<i2s_bits_per_sample_t>(format.bits_per_sample),
      .channel_format = format.channels == 1 ? I2S_CHANNEL_FMT_ONLY_LEFT : I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = I2S_DMA_BUFFER_COUNT,
      .dma_buf_len = I2S_DMA_BUFFER_LEN,
      .use_apll = false,
      .tx_desc_auto_clear = true,
      .fixed_mclk = 0,
      .mclk_multiple = I2S_MCLK_MULTIPLE_256,
      .bits_per_chan = I2S_BITS_PER_CHAN_DEFAULT,
  };

#if SOC_I2S_SUPPORTS_DAC
  if (this->internal_dac_mode_ != I2S_DAC_CHANNEL_DISABLE) {
    i2s_config.mode = static_cast<i2s_mode_t>(i2s_config.mode | I2S_MODE_DAC_BUILT_IN);
  }
#endif  // SOC_I2S_SUPPORTS_DAC

  err = i2s_driver_install(this->parent_->get_port(), &i2s_config, 0, nullptr);
  if (err != ESP_OK) {
    this->parent_->unlock();
    return err;
  }

#if SOC_I2S_SUPPORTS_DAC
  if (this->internal_dac_mode_ == I2S_DAC_CHANNEL_DISABLE) {
#endif  // SOC_I2S_SUPPORTS_DAC
    i2s_pin_config_t pin_config = this->parent_->get_pin_config();
    pin_config.data_out_num = this->dout_pin_;
    err = i2s_set_pin(this->parent_->get_port(), &pin_config);
#if SOC_I2S_SUPPORTS_DAC
  } else {
    err = i2s_set_dac_mode(this->internal_dac_mode_);
  }
#endif  // SOC_I2S_SUPPORTS_DAC

#else   // !USE_I2S_LEGACY
  i2s_chan_config_t chan_cfg = {
      .id = this->parent_->get_port(),
      .role = I2S_ROLE_MASTER,
      .dma_desc_num = I2S_DMA_BUFFER_COUNT,
      .dma_frame_num = I2S_DMA_BUFFER_LEN,
      .auto_clear = true,
  };

  err = i2s_new_channel(&chan_cfg, &data.tx_handle_, nullptr);
  if (err != ESP_OK) {
    this->parent_->unlock();
    return err;
  }

  i2s_std_clk_config_t clk_cfg = {
      .sample_rate_hz = format.sample_rate,
      .clk_src = I2S_CLK_SRC_DEFAULT,
      .mclk_multiple = I2S_MCLK_MULTIPLE_256,
  };

  i2s_slot_mode_t slot_mode = format.channels == 1 ? I2S_SLOT_MODE_MONO : I2S_SLOT_MODE_STEREO;
  i2s_std_slot_config_t slot_cfg =
      I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(static_cast<i2s_data_bit_width_t>(format.bits_per_sample), slot_mode);
  slot_cfg.slot_mask = format.channels == 1 ? I2S_STD_SLOT_LEFT : I2S_STD_SLOT_BOTH;

  i2s_std_gpio_config_t gpio_cfg = this->parent_->get_pin_config();
  gpio_cfg.dout = static_cast<gpio_num_t>(this->dout_pin_);

  i2s_std_config_t std_cfg = {
      .clk_cfg = clk_cfg,
      .slot_cfg = slot_cfg,
      .gpio_cfg = gpio_cfg,
  };

  err = i2s_channel_init_std_mode(data.tx_handle_, &std_cfg);
  if (err != ESP_OK) {
    i2s_del_channel(data.tx_handle_);
    this->parent_->unlock();
    return err;
  }

  err = i2s_channel_enable(data.tx_handle_);
#endif  // USE_I2S_LEGACY

  if (err != ESP_OK) {
#ifdef USE_I2S_LEGACY
    i2s_driver_uninstall(this->parent_->get_port());
#else   // !USE_I2S_LEGACY
    i2s_del_channel(data.tx_handle_);
    data.tx_handle_ = nullptr;
#endif  // USE_I2S_LEGACY
    this->parent_->unlock();
    return err;
  }

  data.i2s_driver_installed_ = true;
  return ESP_OK;
}

void I2SAudioMediaPlayer::stop_i2s_driver_() {
  auto &data = esp_idf_data[this];
  if (!data.i2s_driver_installed_) {
    return;
  }

#ifdef USE_I2S_LEGACY
  i2s_stop(this->parent_->get_port());
  i2s_driver_uninstall(this->parent_->get_port());
#else   // !USE_I2S_LEGACY
  if (data.tx_handle_ != nullptr) {
    i2s_channel_disable(data.tx_handle_);
    i2s_del_channel(data.tx_handle_);
    data.tx_handle_ = nullptr;
  }
#endif  // USE_I2S_LEGACY

  this->parent_->unlock();
  data.i2s_driver_installed_ = false;
}

esp_err_t I2SAudioMediaPlayer::start_http_client_(const std::string &url) {
  auto &data = esp_idf_data[this];

  esp_http_client_config_t config = {};
  config.url = url.c_str();
  config.event_handler = http_event_handler;
  config.user_data = this;
  config.timeout_ms = HTTP_TIMEOUT_MS;
  config.buffer_size = HTTP_BUFFER_SIZE;
  config.buffer_size_tx = 1024;

  data.http_client_ = esp_http_client_init(&config);
  if (data.http_client_ == nullptr) {
    return ESP_ERR_NO_MEM;
  }

  esp_err_t err = esp_http_client_open(data.http_client_, 0);
  if (err != ESP_OK) {
    esp_http_client_cleanup(data.http_client_);
    data.http_client_ = nullptr;
    return err;
  }

  int status_code = esp_http_client_get_status_code(data.http_client_);
  if (status_code != 200) {
    ESP_LOGE(TAG, "HTTP request failed with status code: %d", status_code);
    this->stop_http_client_();
    return ESP_FAIL;
  }

  return ESP_OK;
}

void I2SAudioMediaPlayer::stop_http_client_() {
  auto &data = esp_idf_data[this];
  if (data.http_client_ != nullptr) {
    esp_http_client_close(data.http_client_);
    esp_http_client_cleanup(data.http_client_);
    data.http_client_ = nullptr;
  }
}

bool I2SAudioMediaPlayer::parse_audio_format_() {
  auto &data = esp_idf_data[this];
  if (data.http_client_ == nullptr) {
    return false;
  }

  // Try to get content type
  char *content_type = nullptr;

  esp_err_t err = esp_http_client_get_header(data.http_client_, "Content-Type", &content_type);
  if (err == ESP_OK && content_type != nullptr) {
    ESP_LOGD(TAG, "Content-Type: %s", content_type);

    // Simple format detection based on content type
    if (strstr(content_type, "audio/wav") != nullptr) {
      // Default WAV format
      data.audio_format_.sample_rate = 44100;
      data.audio_format_.channels = 2;
      data.audio_format_.bits_per_sample = 16;
    } else if (strstr(content_type, "audio/mpeg") != nullptr) {
      // MP3 format - we'll decode this as PCM
      data.audio_format_.sample_rate = 44100;
      data.audio_format_.channels = 2;
      data.audio_format_.bits_per_sample = 16;
    }
    free(content_type);
  }

  ESP_LOGD(TAG, "Audio format: %lu Hz, %d channels, %d bits", data.audio_format_.sample_rate,
           data.audio_format_.channels, data.audio_format_.bits_per_sample);

  return true;
}

void I2SAudioMediaPlayer::apply_volume_control_(uint8_t *audio_data, size_t len) {
  auto &data = esp_idf_data[this];
  if (data.volume_level_ == 21) {
    return;  // Max volume, no adjustment needed
  }

  if (data.volume_level_ == 0) {
    memset(audio_data, 0, len);  // Muted
    return;
  }

  // Simple volume scaling for 16-bit samples
  if (data.audio_format_.bits_per_sample == 16) {
    int16_t *samples = reinterpret_cast<int16_t *>(audio_data);
    size_t sample_count = len / sizeof(int16_t);

    // Volume scaling: 21 = 100%, 0 = 0%
    float volume_factor = static_cast<float>(data.volume_level_) / 21.0f;

    for (size_t i = 0; i < sample_count; i++) {
      int32_t scaled = static_cast<int32_t>(samples[i]) * volume_factor;
      samples[i] =
          static_cast<int16_t>(std::clamp(scaled, static_cast<int32_t>(INT16_MIN), static_cast<int32_t>(INT16_MAX)));
    }
  }
}

}  // namespace i2s_audio
}  // namespace esphome

#endif  // USE_ESP32 && USE_ESP_IDF
