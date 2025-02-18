#include "sensor_mlx90393.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mlx90393 {

static const char *const TAG = "mlx90393";

bool MLX90393Cls::transceive(const uint8_t *request, size_t request_size, uint8_t *response, size_t response_size) {
  i2c::ErrorCode e = this->write(request, request_size);
  if (e != i2c::ErrorCode::ERROR_OK) {
    ESP_LOGV(TAG, "i2c failed to write %u", e);
    return false;
  }
  e = this->read(response, response_size);
  if (e != i2c::ErrorCode::ERROR_OK) {
    ESP_LOGV(TAG, "i2c failed to read %u", e);
    return false;
  }
  return true;
}

bool MLX90393Cls::has_drdy_pin() { return this->drdy_pin_ != nullptr; }

bool MLX90393Cls::read_drdy_pin() {
  if (this->drdy_pin_ == nullptr) {
    return false;
  } else {
    return this->drdy_pin_->digital_read();
  }
}
void MLX90393Cls::sleep_millis(uint32_t millis) { delay(millis); }
void MLX90393Cls::sleep_micros(uint32_t micros) { delayMicroseconds(micros); }

bool MLX90393Cls::apply_settings_() {
  // perform dummy read after reset
  // first one always gets NAK even tough everything is fine
  uint8_t ignore = 0;
  this->mlx_.getGainSel(ignore);

  if (this->mlx_.setGainSel(this->gain_) != MLX90393::STATUS_OK) {
    ESP_LOGW(TAG, "failed to apply gain");
    return false;
  }

  if (this->mlx_.setResolution(this->resolutions_[0], this->resolutions_[1], this->resolutions_[2]) !=
      MLX90393::STATUS_OK) {
    ESP_LOGE(TAG, "failed to apply resolutions");
    return false;
  }

  if (this->mlx_.setOverSampling(this->oversampling_) != MLX90393::STATUS_OK) {
    ESP_LOGE(TAG, "failed to apply over sampling");
    return false;
  }

  if (this->mlx_.setDigitalFiltering(this->filter_) != MLX90393::STATUS_OK) {
    ESP_LOGE(TAG, "failed to apply digital filtering");
    return false;
  }

  if (this->mlx_.setTemperatureOverSampling(this->temperature_oversampling_) != MLX90393::STATUS_OK) {
    ESP_LOGE(TAG, "failed to apply temperature over sampling");
    return false;
  }

  if (this->mlx_.setTemperatureCompensation(this->temperature_compensation_) != MLX90393::STATUS_OK) {
    ESP_LOGE(TAG, "failed to apply temperature compensation");
    return false;
  }

  if (this->mlx_.setHallConf(this->hallconf_) != MLX90393::STATUS_OK) {
    ESP_LOGE(TAG, "failed to apply hallconf");
    return false;
  }

  return true;
}

void MLX90393Cls::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MLX90393...");
  // note the two arguments A0 and A1 which are used to construct an i2c address
  // we can hard-code these because we never actually use the constructed address
  // see the transceive function above, which uses the address from I2CComponent
  this->mlx_.begin_with_hal(this, 0, 0);

  this->apply_settings_();
}

void MLX90393Cls::dump_config() {
  ESP_LOGCONFIG(TAG, "MLX90393:");
  LOG_I2C_DEVICE(this);

  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with MLX90393 failed!");
    return;
  }
  LOG_UPDATE_INTERVAL(this);

  LOG_SENSOR("  ", "X Axis", this->x_sensor_);
  LOG_SENSOR("  ", "Y Axis", this->y_sensor_);
  LOG_SENSOR("  ", "Z Axis", this->z_sensor_);
  LOG_SENSOR("  ", "Temperature", this->t_sensor_);
}

float MLX90393Cls::get_setup_priority() const { return setup_priority::DATA; }

void MLX90393Cls::update() {
  MLX90393::txyz data;

  if (this->mlx_.readData(data) == MLX90393::STATUS_OK) {
    ESP_LOGD(TAG, "received %f %f %f", data.x, data.y, data.z);
    if (this->x_sensor_ != nullptr) {
      this->x_sensor_->publish_state(data.x);
    }
    if (this->y_sensor_ != nullptr) {
      this->y_sensor_->publish_state(data.y);
    }
    if (this->z_sensor_ != nullptr) {
      this->z_sensor_->publish_state(data.z);
    }
    if (this->t_sensor_ != nullptr) {
      this->t_sensor_->publish_state(data.t);
    }
    this->status_clear_warning();
  } else {
    ESP_LOGE(TAG, "failed to read data");
    this->status_set_warning();
  }

  // perform verifications. if a register has an unexpected value, reset chip and set everything again
  if (!this->verify_settings_()) {
    if (this->mlx_.checkStatus(this->mlx_.reset()) != MLX90393::STATUS_OK) {
      ESP_LOGE(TAG, "failed to reset device");
      this->status_set_error();
      this->mark_failed();
      return;
    }

    if (!this->apply_settings_()) {
      ESP_LOGE(TAG, "failed to re-apply settings");
      this->status_set_error();
      this->mark_failed();
    } else {
      ESP_LOGI(TAG, "reset and re-apply settings completed");
    }
  }
}

enum VerifySettingsStage {
  VERIFY_SETTINGS_GAIN_SEL = 0,
  VERIFY_SETTINGS_RESOLUTION,
  VERIFY_SETTINGS_OVER_SAMPLING,
  VERIFY_SETTINGS_DIGITAL_FILTERING,
  VERIFY_SETTINGS_TEMPERATURE_OVER_SAMPLING,
  VERIFY_SETTINGS_TEMPERATURE_COMPENSATION,
  VERIFY_SETTINGS_HALLCONF,
  VERIFY_SETTINGS_LAST,
};

/**
 * Regularly checks that our settings are still applied.
 * Used to catch spurious chip resets.
 *
 * returns true if everything is fine.
 * false if not
 */
bool MLX90393Cls::verify_settings_() {
  static enum VerifySettingsStage stage = VERIFY_SETTINGS_GAIN_SEL;
  static uint32_t last_verify = 0;

  // verify at most once every 3s
  if (millis() - last_verify > 3000) {
    last_verify = millis();

    switch (stage) {
      case VERIFY_SETTINGS_GAIN_SEL: {
        uint8_t read_gain_sel = -1;
        if (this->mlx_.getGainSel(read_gain_sel) != MLX90393::STATUS_OK) {
          ESP_LOGE(TAG, "verify error: failed to read gain sel");
          return false;
        }
        if (read_gain_sel != this->gain_) {
          ESP_LOGW(TAG, "verify failed: read back wrong gain. got %u expected %u", read_gain_sel, this->gain_);
          return false;
        } else {
          ESP_LOGD(TAG, "verify succeeded for gain. got %u", read_gain_sel);
        }
        break;
      }
      case VERIFY_SETTINGS_RESOLUTION: {
        uint8_t x = -1;
        uint8_t y = -1;
        uint8_t z = -1;
        if (this->mlx_.getResolution(x, y, z) != MLX90393::STATUS_OK) {
          ESP_LOGE(TAG, "verify error: failed to read resolution");
          return false;
        }
        if (x != this->resolutions_[0] || y != this->resolutions_[1] || z != this->resolutions_[2]) {
          ESP_LOGW(TAG, "verify failed: read back wrong resolutions: got x=%u y=%u z=%u expected x=%u y=%u z=%u", y, x,
                   z, this->resolutions_[0], this->resolutions_[1], this->resolutions_[2]);
          return false;
        } else {
          ESP_LOGD(TAG, "verify succeeded for resolutions. got %u %u %u", x, y, z);
        }
        break;
      }
      case VERIFY_SETTINGS_OVER_SAMPLING: {
        uint8_t osr = -1;
        if (this->mlx_.getOverSampling(osr) != MLX90393::STATUS_OK) {
          ESP_LOGE(TAG, "verify error: failed to read over sampling");
          return false;
        }
        if (osr != this->oversampling_) {
          ESP_LOGW(TAG, "verify failed: read back wrong over sampling: got %u expected %u", osr, this->oversampling_);
          return false;
        } else {
          ESP_LOGD(TAG, "verify succeeded for over sampling. got %u", osr);
        }
        break;
      }
      case VERIFY_SETTINGS_DIGITAL_FILTERING: {
        uint8_t dig_filt = -1;
        if (this->mlx_.getDigitalFiltering(dig_filt) != MLX90393::STATUS_OK) {
          ESP_LOGE(TAG, "verify error: failed to read digital filtering");
          return false;
        }
        if (dig_filt != this->filter_) {
          ESP_LOGW(TAG, "verify failed: read back wrong digital filtering: got %u expected %u", dig_filt,
                   this->filter_);
          return false;
        } else {
          ESP_LOGD(TAG, "verify succeeded for digital filtering. got %u", dig_filt);
        }
        break;
      }
      case VERIFY_SETTINGS_TEMPERATURE_OVER_SAMPLING: {
        uint8_t osr2 = -1;
        if (this->mlx_.getTemperatureOverSampling(osr2) != MLX90393::STATUS_OK) {
          ESP_LOGE(TAG, "verify error: failed to read temperature over sampling");
          return false;
        }
        if (osr2 != this->temperature_oversampling_) {
          ESP_LOGW(TAG, "verify failed: read back wrong temperature over sampling: got %u expected %u", osr2,
                   this->temperature_oversampling_);
          return false;
        } else {
          ESP_LOGD(TAG, "verify succeeded for temperature over sampling. got %u", osr2);
        }
        break;
      }
      case VERIFY_SETTINGS_TEMPERATURE_COMPENSATION: {
        uint8_t enabled = 0;
        if (this->mlx_.getTemperatureCompensation(enabled) != MLX90393::STATUS_OK) {
          ESP_LOGE(TAG, "verify error: failed to read temperature compensation");
          return false;
        }
        if (enabled != this->temperature_compensation_) {
          ESP_LOGW(TAG, "verify failed: read back wrong temperature compensation: got %u expected %u", enabled,
                   this->temperature_compensation_);
          return false;
        } else {
          ESP_LOGD(TAG, "verify succeeded for temperature compensation. got %u", enabled);
        }
        break;
      }
      case VERIFY_SETTINGS_HALLCONF: {
        uint8_t hallconf = 0;
        if (this->mlx_.getHallConf(hallconf) != MLX90393::STATUS_OK) {
          ESP_LOGE(TAG, "verify error: failed to read hallconf");
          return false;
        }
        if (hallconf != this->hallconf_) {
          ESP_LOGW(TAG, "verify failed: read back wrong hallconf: got %u expected %u", hallconf, this->hallconf_);
          return false;
        } else {
          ESP_LOGD(TAG, "verify succeeded for hallconf. got %u", hallconf);
        }
        break;
      }
      default:
        break;
    }

    // advance to next verify stage
    stage = static_cast<VerifySettingsStage>(static_cast<int>(stage) + 1);
    if (stage == VERIFY_SETTINGS_LAST) {
      stage = static_cast<VerifySettingsStage>(0);
    }
  }
  return true;
}

}  // namespace mlx90393
}  // namespace esphome
