#include "es8388_hub.h"
#include "esphome/core/log.h"

namespace esphome {
namespace es8388 {

static const char *const TAG = "ES8388Hub";

ES8388Hub::ES8388Hub() {}

void ES8388Hub::setup() {
#ifdef USE_SELECT

  static uint8_t dac_power = this->audio_dac_->get_dac_power();
  static uint8_t dac_output = 0;

  switch (dac_power) {
    case ES8388_DAC_OUTPUT_LOUT1_ROUT1:
      dac_output = DAC_OUTPUT_LINE1;
      break;
    case ES8388_DAC_OUTPUT_LOUT2_ROUT2:
      dac_output = DAC_OUTPUT_LINE2;
      break;
    case ES8388_DAC_OUTPUT_BOTH:
      dac_output = DAC_OUTPUT_BOTH;
      break;
    default:
      break;
  };

  std::string dac_output_string = DAC_OUTPUT_INT_TO_ENUM.at(static_cast<DacOutputLineStructure>(dac_output));

  if (this->dac_output_select_ != nullptr) {
    this->dac_output_select_->publish_state(dac_output_string);
  }

  // ADC input MIC

  static uint8_t mic_input_raw = this->audio_dac_->get_mic_input();
  static uint8_t mic_input = 0;

  switch (mic_input_raw) {
    case ES8388_ADC_INPUT_LINPUT1_RINPUT1:
      mic_input = ADC_INPUT_MIC_LINE1;
      break;
    case ES8388_ADC_INPUT_LINPUT2_RINPUT2:
      mic_input = ADC_INPUT_MIC_LINE2;
      break;
    case ES8388_ADC_INPUT_DIFFERENCE:
      mic_input = ADC_INPUT_MIC_DIFFERENCE;
      break;
    default:
      break;
  };

  std::string adc_mic_line_string = ADC_INPUT_MIC_INT_TO_ENUM.at(static_cast<AdcInputMicLineStructure>(mic_input));

  if (this->adc_input_mic_select_ != nullptr) {
    this->adc_input_mic_select_->publish_state(adc_mic_line_string);
  }

#endif
}

void ES8388Hub::set_dac_output(const std::string &state) {
  this->dac_output_ = DAC_OUTPUT_ENUM_TO_INT.at(state);
  static uint8_t dac_power = 0;

  switch (this->dac_output_) {
    case DAC_OUTPUT_LINE1:
      dac_power = ES8388_DAC_OUTPUT_LOUT1_ROUT1;
      break;
    case DAC_OUTPUT_LINE2:
      dac_power = ES8388_DAC_OUTPUT_LOUT2_ROUT2;
      break;
    case DAC_OUTPUT_BOTH:
      dac_power = ES8388_DAC_OUTPUT_BOTH;
      break;
    default:
      break;
  };

  // Set es8388 dac power
  this->audio_dac_->set_dac_power(dac_power);
}

void ES8388Hub::set_adc_input_mic(const std::string &state) {
  this->adc_input_mic_ = ADC_INPUT_MIC_ENUM_TO_INT.at(state);

  static uint8_t input_mic = 0;

  switch (this->adc_input_mic_) {
    case ADC_INPUT_MIC_LINE1:
      input_mic = ES8388_ADC_INPUT_LINPUT1_RINPUT1;
      break;
    case ADC_INPUT_MIC_LINE2:
      input_mic = ES8388_ADC_INPUT_LINPUT2_RINPUT2;
      break;
    case ADC_INPUT_MIC_DIFFERENCE:
      input_mic = ES8388_ADC_INPUT_DIFFERENCE;
      break;
    default:
      break;
  };

  // Set es8388 mic input
  this->audio_dac_->set_mic_input(input_mic);
}

void ES8388Hub::dump_config() {
#ifdef USE_SELECT
  LOG_SELECT("  ", "DacOutputSelect", this->dac_output_select_);
  LOG_SELECT("  ", "ADCInputMicSelect", this->adc_input_mic_select_);

#endif
}

}  // namespace es8388
}  // namespace esphome
