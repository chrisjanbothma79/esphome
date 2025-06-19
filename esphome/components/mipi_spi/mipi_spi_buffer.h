#pragma once

#include "mipi_spi.h"

namespace esphome {
namespace mipi_spi {

/**
 * Templated MipiSpiBuffer class for MIPI SPI displays.
 *
 * @tparam BUFFERPIXEL Color depth of the buffer
 * @tparam DISPLAYPIXEL Color depth of the display
 * @tparam ROTATION Display rotation
 * @tparam BUS_TYPE The type of the interface bus (single, quad, octal)
 */
template<PixelMode BUFFERPIXEL, PixelMode DISPLAYPIXEL, display::DisplayRotation ROTATION, BusType BUS_TYPE>
class MipiSpiBuffer : public MipiSpi {
 public:
  MipiSpiBuffer(size_t width, size_t height, int16_t offset_width, int16_t offset_height)
      : MipiSpi(width, height, offset_width, offset_height) {
    this->set_rotation(ROTATION);
    switch (BUFFERPIXEL) {
      case PIXEL_MODE_8:
        this->color_depth_ = display::COLOR_BITNESS_332;
        break;
      case PIXEL_MODE_16:
        this->color_depth_ = display::COLOR_BITNESS_565;
        break;
      case PIXEL_MODE_18:  // not currently implemented
      default:
        this->Component::mark_failed();
        return;
    }
  }

 protected:
  bool check_buffer_() {
    if (this->is_failed())
      return false;
    if (this->buffer_ != nullptr)
      return true;
    this->init_internal_(this->width_ * this->height_ * BUFFERPIXEL);
    if (this->buffer_ == nullptr) {
      this->mark_failed();
      return false;
    }
    this->buffer_bytes_ = this->width_ * this->height_ * BUFFERPIXEL;
    return true;
  }

  // functions to convert from one pixel format to another

  template<PixelMode B = BUFFERPIXEL, PixelMode D = DISPLAYPIXEL>
  std::enable_if_t<(B == PIXEL_MODE_8 && D == PIXEL_MODE_16), void> convert_pixel_(const uint8_t *&from, uint8_t *&to) {
    auto color_val = *from++;
    *to++ = (color_val & 0xE0) | ((color_val & 0x1C) >> 2);
    *to++ = (color_val & 0x3) << 3;
  }

  template<PixelMode B = BUFFERPIXEL, PixelMode D = DISPLAYPIXEL>
  std::enable_if_t<(B == PIXEL_MODE_16 && D == PIXEL_MODE_18), void> convert_pixel_(const uint8_t *&from,
                                                                                    uint8_t *&to) {
    uint16_t color_val = *from++ << 8;  // Read the high byte
    color_val |= *from++;
    // deal with byte swapping
    *to++ = (color_val & 0xF8);                                       // Blue
    *to++ = ((color_val & 0x7) << 5) | ((color_val & 0xE000) >> 11);  // Green
    *to++ = (color_val >> 5) & 0xF8;                                  // Red
  }

  template<PixelMode B = BUFFERPIXEL, PixelMode D = DISPLAYPIXEL>
  std::enable_if_t<(B == PIXEL_MODE_8 && D == PIXEL_MODE_18), void> convert_pixel_(const uint8_t *&from, uint8_t *&to) {
    auto color_val = *from++;
    *to++ = (color_val & 0xE0);       // Blue
    *to++ = (color_val & 0x1C) << 3;  // Green
    *to++ = color_val << 5;           // Red
  }

  // methods to write display data, given start ptr, width, height and padding
  // the pointer already has the x-offset and y-offset applied, so it points to the first pixel
  // width and pad are in bytes, height in rows

  template<BusType M = BUS_TYPE>
  std::enable_if_t<M == BUS_TYPE_QUAD, void> write_display_data_(const uint8_t *ptr, size_t w, size_t h, size_t pad) {
    this->enable();
    if (pad == 0) {
      this->write_cmd_addr_data(8, 0x32, 24, WDATA << 8, ptr, w * h, 4);
    } else {
      this->write_cmd_addr_data(8, 0x32, 24, WDATA << 8, nullptr, 0, 4);
      for (int y = 0; y != h; y++) {
        this->write_cmd_addr_data(0, 0, 0, 0, ptr, w, 4);
        ptr += w + pad;
      }
    }
    this->disable();
  }

  template<BusType M = BUS_TYPE>
  std::enable_if_t<M == BUS_TYPE_OCTAL, void> write_display_data_(const uint8_t *ptr, size_t w, size_t h, size_t pad) {
    this->write_command_(WDATA);
    this->enable();
    if (pad == 0) {
      this->write_cmd_addr_data(0, 0, 0, 0, ptr, w * h, 8);
    } else {
      for (int y = 0; y != h; y++) {
        this->write_cmd_addr_data(0, 0, 0, 0, ptr, w, 8);
        ptr += w + pad;
      }
    }
    this->disable();
  }

  template<BusType M = BUS_TYPE>
  std::enable_if_t<M == BUS_TYPE_SINGLE || M == BUS_TYPE_SINGLE_16, void> write_display_data_(const uint8_t *ptr,
                                                                                              size_t w, size_t h,
                                                                                              size_t pad) {
    this->write_command_(WDATA);
    this->enable();
    if (pad == 0) {
      this->write_array(ptr, w * h);
    } else {
      for (int y = 0; y != h; y++) {
        this->write_array(ptr, w);
        ptr += w + pad;
      }
    }
    this->disable();
  }

  // Write to display, with the same pixel mode for buffer and display
  template<PixelMode B = BUFFERPIXEL, PixelMode D = DISPLAYPIXEL>
  std::enable_if_t<(B == D), void> write_to_display_(int x_start, int y_start, int w, int h, const uint8_t *ptr,
                                                     int x_offset, int y_offset, int x_pad) {
    this->set_addr_window_(x_start, y_start, x_start + w - 1, y_start + h - 1);
    ptr += y_offset * (x_offset + w + x_pad) * BUFFERPIXEL + x_offset * BUFFERPIXEL;
    this->write_display_data_(ptr, w * BUFFERPIXEL, h, x_pad * BUFFERPIXEL);
  }

  // write a command for various bus types
  template<BusType M = BUS_TYPE>
  std::enable_if_t<M == BUS_TYPE_QUAD, void> write_command_(uint8_t cmd, const uint8_t *bytes, size_t len) {
    ESP_LOGV(TAG, "Command %02X, length %d, bytes %s", cmd, len, format_hex_pretty(bytes, len).c_str());
    this->enable();
    this->write_cmd_addr_data(8, 0x02, 24, cmd << 8, bytes, len);
    this->disable();
  }

  template<BusType M = BUS_TYPE>
  std::enable_if_t<M == BUS_TYPE_OCTAL, void> write_command_(uint8_t cmd, const uint8_t *bytes, size_t len) {
    ESP_LOGV(TAG, "Command %02X, length %d, bytes %s", cmd, len, format_hex_pretty(bytes, len).c_str());
    this->dc_pin_->digital_write(false);
    this->enable();
    this->write_cmd_addr_data(0, 0, 0, 0, &cmd, 1, 8);
    this->disable();
    this->dc_pin_->digital_write(true);
    if (len != 0) {
      this->enable();
      this->write_cmd_addr_data(0, 0, 0, 0, bytes, len, 8);
      this->disable();
    }
  }
  template<BusType M = BUS_TYPE>
  std::enable_if_t<M == BUS_TYPE_SINGLE, void> write_command_(uint8_t cmd, const uint8_t *bytes, size_t len) {
    ESP_LOGV(TAG, "Command %02X, length %d, bytes %s", cmd, len, format_hex_pretty(bytes, len).c_str());
    this->dc_pin_->digital_write(false);
    this->enable();
    this->write_byte(cmd);
    this->disable();
    this->dc_pin_->digital_write(true);
    if (len != 0) {
      this->enable();
      this->write_array(bytes, len);
      this->disable();
    }
  }

  template<BusType M = BUS_TYPE>
  std::enable_if_t<M == BUS_TYPE_SINGLE_16, void> write_command_(uint8_t cmd, const uint8_t *bytes, size_t len) {
    ESP_LOGV(TAG, "Command %02X, length %d, bytes %s", cmd, len, format_hex_pretty(bytes, len).c_str());
    this->dc_pin_->digital_write(false);
    this->enable();
    this->write_byte(cmd);
    this->disable();
    this->dc_pin_->digital_write(true);
    for (size_t i = 0; i != len; i++) {
      this->enable();
      this->write_byte(0);
      this->write_byte(bytes[i]);
      this->disable();
    }
  }
};

}  // namespace mipi_spi
}  // namespace esphome
