#include "adc_audio_microphone.h"

#ifdef USE_ESP32_FRAMEWORK_ESP_IDF

#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace adc_microphone {

static const size_t BUFFER_SIZE = 512;

static const char *const TAG = "adc_microphone";

void ADCAudioMicrophone::setup() {
  ESP_LOGCONFIG(TAG, "Setting up ADC Audio Microphone...");

  adc_continuous_handle_cfg_t adc_config = {
      .max_store_buf_size = SOC_ADC_DIGI_DATA_BYTES_PER_CONV * 8 *
                            100,  // ensure buffer is large enough to work even when running at slower speed
      .conv_frame_size = SOC_ADC_DIGI_DATA_BYTES_PER_CONV * 8,
  };

  ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &adc_handle));

#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2
  adc_digi_output_format_t format = ADC_DIGI_OUTPUT_FORMAT_TYPE1;
#else
  adc_digi_output_format_t format = ADC_DIGI_OUTPUT_FORMAT_TYPE2;
#endif

  adc_digi_convert_mode_t adc_conv_mode = (adc_unit_ == ADC_UNIT_1) ? ADC_CONV_SINGLE_UNIT_1 : ADC_CONV_SINGLE_UNIT_2;

  adc_continuous_config_t dig_cfg = {
      .pattern_num = 1,
      .sample_freq_hz = 20 * 1000,
      .conv_mode = adc_conv_mode,
      .format = format,
  };

  adc_digi_pattern_config_t adc_pattern = {
      .atten = attenuation_,
      .channel = adc_channel_,
      .unit = adc_unit_,
      .bit_width = ADC_BITWIDTH_DEFAULT,
  };
  dig_cfg.adc_pattern = &adc_pattern;
  ESP_ERROR_CHECK(adc_continuous_config(adc_handle, &dig_cfg))
}

void ADCAudioMicrophone::set_adc_channel(int gpio_pin) {
  ESP_ERROR_CHECK(adc_continuous_io_to_channel(gpio_pin, &adc_unit_, &adc_channel_));
}

void ADCAudioMicrophone::start() {
  if (this->is_failed())
    return;
  if (this->state_ == microphone::STATE_RUNNING)
    return;  // Already running
  this->state_ = microphone::STATE_STARTING;
}
void ADCAudioMicrophone::start_() {
  if (!this->parent_->try_lock()) {
    return;  // Waiting for another i2s to return lock
  }
  i2s_driver_config_t config = {
      .mode = (i2s_mode_t) (this->i2s_mode_ | I2S_MODE_RX),
      .sample_rate = this->sample_rate_,
      .bits_per_sample = this->bits_per_sample_,
      .channel_format = this->channel_,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = this->use_apll_,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0,
      .mclk_multiple = I2S_MCLK_MULTIPLE_256,
      .bits_per_chan = this->bits_per_channel_,
  };

  esp_err_t err;

#if SOC_I2S_SUPPORTS_ADC
  if (this->adc_) {
    config.mode = (i2s_mode_t) (config.mode | I2S_MODE_ADC_BUILT_IN);
    err = i2s_driver_install(this->parent_->get_port(), &config, 0, nullptr);
    if (err != ESP_OK) {
      ESP_LOGW(TAG, "Error installing I2S driver: %s", esp_err_to_name(err));
      this->status_set_error();
      return;
    }

    err = i2s_set_adc_mode(ADC_UNIT_1, this->adc_channel_);
    if (err != ESP_OK) {
      ESP_LOGW(TAG, "Error setting ADC mode: %s", esp_err_to_name(err));
      this->status_set_error();
      return;
    }
    err = i2s_adc_enable(this->parent_->get_port());
    if (err != ESP_OK) {
      ESP_LOGW(TAG, "Error enabling ADC: %s", esp_err_to_name(err));
      this->status_set_error();
      return;
    }

  } else
#endif
  {
    if (this->pdm_)
      config.mode = (i2s_mode_t) (config.mode | I2S_MODE_PDM);

    err = i2s_driver_install(this->parent_->get_port(), &config, 0, nullptr);
    if (err != ESP_OK) {
      ESP_LOGW(TAG, "Error installing I2S driver: %s", esp_err_to_name(err));
      this->status_set_error();
      return;
    }

    i2s_pin_config_t pin_config = this->parent_->get_pin_config();
    pin_config.data_in_num = this->din_pin_;

    err = i2s_set_pin(this->parent_->get_port(), &pin_config);
    if (err != ESP_OK) {
      ESP_LOGW(TAG, "Error setting I2S pin: %s", esp_err_to_name(err));
      this->status_set_error();
      return;
    }
  }
  this->state_ = microphone::STATE_RUNNING;
  this->high_freq_.start();
  this->status_clear_error();
}

void ADCAudioMicrophone::stop() {
  if (this->state_ == microphone::STATE_STOPPED || this->is_failed())
    return;
  if (this->state_ == microphone::STATE_STARTING) {
    this->state_ = microphone::STATE_STOPPED;
    return;
  }
  this->state_ = microphone::STATE_STOPPING;
}

void ADCAudioMicrophone::stop_() {
  esp_err_t err;
#if SOC_I2S_SUPPORTS_ADC
  if (this->adc_) {
    err = i2s_adc_disable(this->parent_->get_port());
    if (err != ESP_OK) {
      ESP_LOGW(TAG, "Error disabling ADC: %s", esp_err_to_name(err));
      this->status_set_error();
      return;
    }
  }
#endif
  err = i2s_stop(this->parent_->get_port());
  if (err != ESP_OK) {
    ESP_LOGW(TAG, "Error stopping I2S microphone: %s", esp_err_to_name(err));
    this->status_set_error();
    return;
  }
  err = i2s_driver_uninstall(this->parent_->get_port());
  if (err != ESP_OK) {
    ESP_LOGW(TAG, "Error uninstalling I2S driver: %s", esp_err_to_name(err));
    this->status_set_error();
    return;
  }
  this->parent_->unlock();
  this->state_ = microphone::STATE_STOPPED;
  this->high_freq_.stop();
  this->status_clear_error();
}

size_t ADCAudioMicrophone::read(int16_t *buf, size_t len) {
  size_t bytes_read = 0;
  esp_err_t err = i2s_read(this->parent_->get_port(), buf, len, &bytes_read, (100 / portTICK_PERIOD_MS));
  if (err != ESP_OK) {
    ESP_LOGW(TAG, "Error reading from I2S microphone: %s", esp_err_to_name(err));
    this->status_set_warning();
    return 0;
  }
  if (bytes_read == 0) {
    this->status_set_warning();
    return 0;
  }
  this->status_clear_warning();
  // ESP-IDF I2S implementation right-extends 8-bit data to 16 bits,
  // and 24-bit data to 32 bits.
  switch (this->bits_per_sample_) {
    case I2S_BITS_PER_SAMPLE_8BIT:
    case I2S_BITS_PER_SAMPLE_16BIT:
      return bytes_read;
    case I2S_BITS_PER_SAMPLE_24BIT:
    case I2S_BITS_PER_SAMPLE_32BIT: {
      size_t samples_read = bytes_read / sizeof(int32_t);
      for (size_t i = 0; i < samples_read; i++) {
        int32_t temp = reinterpret_cast<int32_t *>(buf)[i] >> 14;
        buf[i] = clamp<int16_t>(temp, INT16_MIN, INT16_MAX);
      }
      return samples_read * sizeof(int16_t);
    }
    default:
      ESP_LOGE(TAG, "Unsupported bits per sample: %d", this->bits_per_sample_);
      return 0;
  }
}

void ADCAudioMicrophone::read_() {
  std::vector<int16_t> samples;
  samples.resize(BUFFER_SIZE);
  size_t bytes_read = this->read(samples.data(), BUFFER_SIZE / sizeof(int16_t));
  samples.resize(bytes_read / sizeof(int16_t));
  this->data_callbacks_.call(samples);
}

void ADCAudioMicrophone::loop() {
  switch (this->state_) {
    case microphone::STATE_STOPPED:
      break;
    case microphone::STATE_STARTING:
      this->start_();
      break;
    case microphone::STATE_RUNNING:
      if (this->data_callbacks_.size() > 0) {
        this->read_();
      }
      break;
    case microphone::STATE_STOPPING:
      this->stop_();
      break;
  }
}

}  // namespace adc_microphone
}  // namespace esphome

#endif  // USE_ESP32_FRAMEWORK_ESP_IDF
