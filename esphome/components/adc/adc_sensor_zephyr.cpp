#ifdef USE_ZEPHYR

#include "adc_sensor.h"
#include "esphome/core/log.h"

#include "hal/nrf_saadc.h"

namespace esphome {
namespace adc {

static const char *const TAG = "adc.zephyr";

void AdcSensor::setup() {
  if (!adc_is_ready_dt(adc_channel_)) {
    ESP_LOGE(TAG, "ADC controller device %s not ready", adc_channel_->dev->name);
    return;
  }

  auto err = adc_channel_setup_dt(adc_channel_);
  if (err < 0) {
    ESP_LOGE(TAG, "Could not setup channel %s (%d)", adc_channel_->dev->name, err);
    return;
  }
}

static LogString *gain_to_str(enum adc_gain gain) {
  switch (gain) {
    case ADC_GAIN_1_6:
      return LOG_STR("1/6");
    case ADC_GAIN_1_5:
      return LOG_STR("1/5");
    case ADC_GAIN_1_4:
      return LOG_STR("1/4");
    case ADC_GAIN_1_3:
      return LOG_STR("1/3");
    case ADC_GAIN_2_5:
      return LOG_STR("2/5");
    case ADC_GAIN_1_2:
      return LOG_STR("1/2");
    case ADC_GAIN_2_3:
      return LOG_STR("2/3");
    case ADC_GAIN_4_5:
      return LOG_STR("4/5");
    case ADC_GAIN_1:
      return LOG_STR("1");
    case ADC_GAIN_2:
      return LOG_STR("2");
    case ADC_GAIN_3:
      return LOG_STR("3");
    case ADC_GAIN_4:
      return LOG_STR("4");
    case ADC_GAIN_6:
      return LOG_STR("6");
    case ADC_GAIN_8:
      return LOG_STR("8");
    case ADC_GAIN_12:
      return LOG_STR("12");
    case ADC_GAIN_16:
      return LOG_STR("16");
    case ADC_GAIN_24:
      return LOG_STR("24");
    case ADC_GAIN_32:
      return LOG_STR("32");
    case ADC_GAIN_64:
      return LOG_STR("64");
    case ADC_GAIN_128:
      return LOG_STR("128");
  }
  return LOG_STR("undefined gain");
}

static LogString *reference_to_str(enum adc_reference reference) {
  switch (reference) {
    case ADC_REF_VDD_1:
      return LOG_STR("VDD");
    case ADC_REF_VDD_1_2:
      return LOG_STR("VDD/2");
    case ADC_REF_VDD_1_3:
      return LOG_STR("VDD/3");
    case ADC_REF_VDD_1_4:
      return LOG_STR("VDD/4");
    case ADC_REF_INTERNAL:
      return LOG_STR("INTERNAL");
    case ADC_REF_EXTERNAL0:
      return LOG_STR("External, input 0");
    case ADC_REF_EXTERNAL1:
      return LOG_STR("External, input 1");
  }
  return LOG_STR("undefined reference");
}

static LogString *input_to_str(uint8_t input) {
  switch (input) {
    case NRF_SAADC_INPUT_AIN0:
      return LOG_STR("AIN0");
    case NRF_SAADC_INPUT_AIN1:
      return LOG_STR("AIN1");
    case NRF_SAADC_INPUT_AIN2:
      return LOG_STR("AIN2");
    case NRF_SAADC_INPUT_AIN3:
      return LOG_STR("AIN3");
    case NRF_SAADC_INPUT_AIN4:
      return LOG_STR("AIN4");
    case NRF_SAADC_INPUT_AIN5:
      return LOG_STR("AIN5");
    case NRF_SAADC_INPUT_AIN6:
      return LOG_STR("AIN6");
    case NRF_SAADC_INPUT_AIN7:
      return LOG_STR("AIN7");
    case NRF_SAADC_INPUT_VDD:
      return LOG_STR("VDD");
    case NRF_SAADC_INPUT_VDDHDIV5:
      return LOG_STR("VDDHDIV5");
  }
  return LOG_STR("undefined input");
}

void AdcSensor::dump_config() {
  LOG_SENSOR("", "ADC Sensor", this);
  LOG_PIN("  Pin: ", this->pin_);
  ESP_LOGCONFIG(TAG,
                "  Name: %s\n"
                "  Channel: %d\n"
                "  vref_mv: %d\n"
                "  Resolution %d\n"
                "  Oversampling %d",
                adc_channel_->dev->name, adc_channel_->channel_id, adc_channel_->vref_mv, adc_channel_->resolution,
                adc_channel_->oversampling);

  ESP_LOGCONFIG(TAG,
                "  Gain: %s\n"
                "  reference: %s\n"
                "  acquisition_time: %d\n"
                "  differential %s",
                gain_to_str(adc_channel_->channel_cfg.gain), reference_to_str(adc_channel_->channel_cfg.reference),
                adc_channel_->channel_cfg.acquisition_time, YESNO(adc_channel_->channel_cfg.differential));
  if (adc_channel_->channel_cfg.differential) {
    ESP_LOGCONFIG(TAG,
                  "  Positive: %s\n"
                  "  Negative: %s",
                  input_to_str(adc_channel_->channel_cfg.input_positive),
                  input_to_str(adc_channel_->channel_cfg.input_negative));
  } else {
    ESP_LOGCONFIG(TAG, "  Positive: %s", input_to_str(adc_channel_->channel_cfg.input_positive));
  }

  LOG_UPDATE_INTERVAL(this);
}

float ADCSensor::sample() {
  int16_t buf = 0;
  struct adc_sequence sequence = {
      .buffer = &buf,
      /* buffer size in bytes, not number of samples */
      .buffer_size = sizeof(buf),
  };
  int32_t val_mv;

  auto err = adc_sequence_init_dt(adc_channel_, &sequence);
  if (err < 0) {
    ESP_LOGE(TAG, "Could sequence init %s (%d)", adc_channel_->dev->name, err);
    return 0.0;
  }

  err = adc_read(adc_channel_->dev, &sequence);
  if (err < 0) {
    ESP_LOGE(TAG, "Could not read %s (%d)", adc_channel_->dev->name, err);
    return 0.0;
  }

  /*
   * If using differential mode, the 16 bit value
   * in the ADC sample buffer should be a signed 2's
   * complement value.
   */
  if (adc_channel_->channel_cfg.differential) {
    val_mv = (int32_t) ((int16_t) buf);
  } else {
    val_mv = (int32_t) buf;
    // https://github.com/adafruit/Adafruit_nRF52_Arduino/blob/0ed4d9ffc674ae407be7cacf5696a02f5e789861/cores/nRF5/wiring_analog_nRF52.c#L222
    if (val_mv < 0) {
      val_mv = 0;
    }
  }

  if (output_raw_) {
    return val_mv;
  }

  err = adc_raw_to_millivolts_dt(adc_channel_, &val_mv);
  /* conversion to mV may not be supported, skip if not */
  if (err < 0) {
    ESP_LOGE(TAG, "Value in mV not available %s (%d)", adc_channel_->dev->name, err);
    return 0.0;
  }

  return val_mv / 1000.0f;
}

}  // namespace adc
}  // namespace esphome
