//
// Created by Clyde Stubbs on 29/10/2023.
//
#pragma once

// only applicable on ESP32-S3
#ifdef USE_ESP32_VARIANT_ESP32P4
#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"
#include "esphome/components/display/display.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_io.h"

#include "esp_lcd_mipi_dsi.h"

namespace esphome {
namespace mipi_dsi {

constexpr static const char *const TAG = "display.mipi_dsi";
const uint8_t SW_RESET_CMD = 0x01;
const uint8_t SLEEP_OUT = 0x11;
const uint8_t SDIR_CMD = 0xC7;
const uint8_t MADCTL_CMD = 0x36;
const uint8_t INVERT_OFF = 0x20;
const uint8_t INVERT_ON = 0x21;
const uint8_t DISPLAY_ON = 0x29;
const uint8_t CMD2_BKSEL = 0xFF;
const uint8_t CMD2_BK0[5] = {0x77, 0x01, 0x00, 0x00, 0x10};
const uint8_t DELAY_FLAG = 0xFF;

enum PixelMode {
  PIXEL_MODE_8 = 1,
  PIXEL_MODE_16 = 2,
  PIXEL_MODE_18 = 3,
};

template<typename BUFFERTYPE, bool IS_BIG_ENDIAN, PixelMode DISPLAYPIXEL, int WIDTH, int HEIGHT>
class MIPI_DSI : public display::Display {
 public:
  display::ColorOrder get_color_mode() { return this->color_mode_; }
  void set_color_mode(display::ColorOrder color_mode) { this->color_mode_ = color_mode; }
  void set_invert_colors(bool invert_colors) { this->invert_colors_ = invert_colors; }

  void set_reset_pin(GPIOPin *reset_pin) { this->reset_pin_ = reset_pin; }
  void set_data_rate(uint32_t data_rate) { this->data_rate_ = data_rate; }
  int get_width_internal() override { return WIDTH; }
  int get_height_internal() override { return HEIGHT; }
  void set_hsync_back_porch(uint16_t hsync_back_porch) { this->hsync_back_porch_ = hsync_back_porch; }
  void set_hsync_front_porch(uint16_t hsync_front_porch) { this->hsync_front_porch_ = hsync_front_porch; }
  void set_hsync_pulse_width(uint16_t hsync_pulse_width) { this->hsync_pulse_width_ = hsync_pulse_width; }
  void set_vsync_pulse_width(uint16_t vsync_pulse_width) { this->vsync_pulse_width_ = vsync_pulse_width; }
  void set_vsync_back_porch(uint16_t vsync_back_porch) { this->vsync_back_porch_ = vsync_back_porch; }
  void set_vsync_front_porch(uint16_t vsync_front_porch) { this->vsync_front_porch_ = vsync_front_porch; }
  void set_init_sequence(const std::vector<uint8_t> &init_sequence) { this->init_sequence_ = init_sequence; }

  void smark_failed(const char *message, esp_err_t err) {
    auto str = str_sprintf("Setup failed: %s: %s", message, esp_err_to_name(err));
    this->mark_failed(str.c_str());
  }

  void setup() {
    esph_log_config(TAG, "Setting up MIPI_DSI");

    esp_lcd_dsi_bus_config_t config{};
    esp_lcd_dsi_bus_config_t bus_config = {
        .bus_id = 0,          // index from 0, specify the DSI host to use
        .num_data_lanes = 2,  // Number of data lanes to use, can't set a value that exceeds the chip's capability
        .phy_clk_src = MIPI_DSI_PHY_CLK_SRC_DEFAULT,  // Clock source for the DPHY
        .lane_bit_rate_mbps = this->data_rate_,       // Bit rate of the data lanes, in Mbps
    };
    auto err = esp_lcd_new_dsi_bus(&bus_config, &this->bus_handle_);
    if (err != ESP_OK) {
      this->smark_failed("lcd_new_dsi_bus failed", err);
      return;
    }
    esp_lcd_dbi_io_config_t dbi_config = {
        .virtual_channel = 0,
        .lcd_cmd_bits = 8,    // according to the LCD spec
        .lcd_param_bits = 8,  // according to the LCD spec
    };
    err = esp_lcd_new_panel_io_dbi(this->bus_handle_, &dbi_config, &this->io_handle_);
    if (err != ESP_OK) {
      this->smark_failed("new_panel_io_dbi failed", err);
      return;
    }
    /*for (auto *pin : this->enable_pins_) {
      pin->setup();
      pin->digital_write(true);
    } */
    if (this->reset_pin_ != nullptr) {
      this->reset_pin_->setup();
      this->reset_pin_->digital_write(true);
      delay(5);
      this->reset_pin_->digital_write(false);
      delay(5);
      this->reset_pin_->digital_write(true);
    }
    // need to know when the display is ready for SLPOUT command - will be 120ms after reset
    auto when = millis() + 120;
    delay(10);
    size_t index = 0;
    auto &vec = this->init_sequence_;
    while (index != vec.size()) {
      if (vec.size() - index < 2) {
        this->mark_failed("Malformed init sequence");
        return;
      }
      uint8_t cmd = vec[index++];
      uint8_t x = vec[index++];
      if (x == DELAY_FLAG) {
        ESP_LOGD(TAG, "Delay %dms", cmd);
        delay(cmd);
      } else {
        uint8_t num_args = x & 0x7F;
        if (vec.size() - index < num_args) {
          this->mark_failed("Malformed init sequence");
          return;
        }
        auto arg_byte = vec[index];
        switch (cmd) {
          case SLEEP_OUT: {
            // are we ready, boots?
            int duration = when - millis();
            if (duration > 0) {
              ESP_LOGD(TAG, "Sleep %dms", duration);
              delay(duration);
            }
          } break;

          case INVERT_ON:
            this->invert_colors_ = true;
            break;
          case MADCTL_CMD:
            this->madctl_ = arg_byte;
            break;

          default:
            break;
        }
        const auto *ptr = vec.data() + index;
        ESP_LOGD(TAG, "Command %02X, length %d, byte %02X", cmd, num_args, arg_byte);
        esp_lcd_panel_io_tx_param(this->io_handle_, cmd, ptr, num_args);
        index += num_args;
        if (cmd == SLEEP_OUT)
          delay(10);
      }
    }
    esp_lcd_dpi_panel_config_t dpi_config = {.virtual_channel = 0,
                                             .dpi_clk_src = MIPI_DSI_DPI_CLK_SRC_DEFAULT,
                                             .dpi_clock_freq_mhz = 1 * 1000,
                                             .in_color_format = LCD_COLOR_FMT_RGB888,
                                             .video_timing =
                                                 {
                                                     .h_size = HEIGHT,
                                                     .v_size = WIDTH,
                                                     .hsync_pulse_width = this->hsync_pulse_width_,
                                                     .hsync_back_porch = this->hsync_back_porch_,
                                                     .hsync_front_porch = this->hsync_front_porch_,
                                                     .vsync_pulse_width = this->vsync_pulse_width_,
                                                     .vsync_back_porch = this->vsync_back_porch_,
                                                     .vsync_front_porch = this->vsync_front_porch_,
                                                 },
                                             .flags = {
                                                 .use_dma2d = true,
                                             }};
    err = esp_lcd_new_panel_dpi(this->bus_handle_, &dpi_config, &this->handle_);
    if (err != ESP_OK) {
      this->smark_failed("esp_lcd_new_panel_dpi failed", err);
      return;
    }
    err = esp_lcd_panel_init(this->handle_);
    if (err != ESP_OK) {
      this->smark_failed("esp_lcd_init failed", err);
      return;
    }
    esph_log_config(TAG, "MIPI SPI setup complete");
  }

  void draw_pixels_at(int x_start, int y_start, int w, int h, const uint8_t *ptr, display::ColorOrder order,
                      display::ColorBitness bitness, bool big_endian, int x_offset, int y_offset, int x_pad) {
    if (w <= 0 || h <= 0)
      return;
    // if color mapping is required, pass the buck.
    // note that endianness is not considered here - it is assumed to match!
    if (bitness != display::COLOR_BITNESS_565) {
      return display::Display::draw_pixels_at(x_start, y_start, w, h, ptr, order, bitness, big_endian, x_offset,
                                              y_offset, x_pad);
    }
    esp_err_t err;
    // x_ and y_offset are offsets into the source buffer, unrelated to our own offsets into the display.
    if (x_offset == 0 && x_pad == 0 && y_offset == 0) {
      // we could deal here with a non-zero y_offset, but if x_offset is zero, y_offset probably will be so don't bother
      err = esp_lcd_panel_draw_bitmap(this->handle_, x_start, y_start, x_start + w, y_start + h, ptr);
    } else {
      // draw line by line
      auto stride = x_offset + w + x_pad;
      for (int y = 0; y != h; y++) {
        err = esp_lcd_panel_draw_bitmap(this->handle_, x_start, y + y_start, x_start + w, y + y_start + 1,
                                        ptr + ((y + y_offset) * stride + x_offset) * 2);
        if (err != ESP_OK)
          break;
      }
    }
    if (err != ESP_OK)
      esph_log_e(TAG, "lcd_lcd_panel_draw_bitmap failed: %s", esp_err_to_name(err));
  }

  void draw_pixel_at(int x, int y, Color color) {
    if (!this->get_clipping().inside(x, y))
      return;  // NOLINT

    switch (this->rotation_) {
      case display::DISPLAY_ROTATION_0_DEGREES:
        break;
      case display::DISPLAY_ROTATION_90_DEGREES:
        std::swap(x, y);
        x = WIDTH - x - 1;
        break;
      case display::DISPLAY_ROTATION_180_DEGREES:
        x = WIDTH - x - 1;
        y = HEIGHT - y - 1;
        break;
      case display::DISPLAY_ROTATION_270_DEGREES:
        std::swap(x, y);
        y = HEIGHT - y - 1;
        break;
    }
    auto pixel = convert_big_endian(display::ColorUtil::color_to_565(color));

    this->draw_pixels_at(x, y, 1, 1, (const uint8_t *) &pixel, display::COLOR_ORDER_RGB, display::COLOR_BITNESS_565,
                         true, 0, 0, 0);
    App.feed_wdt();
  }

  /**
   * this relies upon the init sequence being well-formed, which is guaranteed by the Python init code.
   */

  void dump_config() override {
    esph_log_config("",
                    "MIPI_DSI RGB LCD"
                    "\n  Height: %u"
                    "\n  Width: %u"
                    "\n  Data Rate: %dMHz",
                    HEIGHT, WIDTH, (unsigned) this->data_rate_ / 1000000);
    if (this->reset_pin_ != nullptr)
      esph_log_config(TAG, "  Reset Pin %s", this->reset_pin_->dump_summary().c_str());
  }

 protected:
  GPIOPin *reset_pin_{nullptr};
  uint8_t madctl_{};
  uint16_t hsync_pulse_width_ = 10;
  uint16_t hsync_back_porch_ = 10;
  uint16_t hsync_front_porch_ = 20;
  uint16_t vsync_pulse_width_ = 10;
  uint16_t vsync_back_porch_ = 10;
  uint16_t vsync_front_porch_ = 10;
  std::vector<uint8_t> init_sequence_;
  uint32_t data_rate_ = 16 * 1000 * 1000;

  bool invert_colors_{};
  display::ColorOrder color_mode_{display::COLOR_ORDER_BGR};

  esp_lcd_panel_handle_t handle_{};
  esp_lcd_dsi_bus_handle_t bus_handle_{};
  esp_lcd_panel_io_handle_t io_handle_{};
};

}  // namespace mipi_dsi
}  // namespace esphome
#endif
