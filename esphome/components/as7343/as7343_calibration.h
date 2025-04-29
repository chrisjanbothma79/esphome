#pragma once

#include "as7343_registers.h"

namespace esphome {
namespace as7343 {

extern const float AS7343_GAIN_CORRECTION[13][12 + 1];
extern const float AS7343_XYZ_PER_COUNT[3][AS7343_NUM_CHANNELS];
extern const float AS7343_XYZ_PER_COUNT_2[3][AS7343_NUM_CHANNELS];

extern const float AS7343_IRRAD_MW_PER_COUNT[AS7343_NUM_CHANNELS];
extern const float AS7343_IRRAD_PHOTOPIC_MW_PER_COUNT[AS7343_NUM_CHANNELS];
extern const float AS7343_IRRAD_PAR_E_MW_PER_COUNT[AS7343_NUM_CHANNELS];
extern const float AS7343_PPFD_UMOL_PER_COUNT[AS7343_NUM_CHANNELS];

extern const float AS7343_CORR_MATRIX_380_780_NM[401][AS7343_NUM_CHANNELS - 1];

}  // namespace as7343
}  // namespace esphome
