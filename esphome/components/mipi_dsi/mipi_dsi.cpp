#ifdef USE_ESP32_VARIANT_ESP32P4
#include "mipi_dsi.h"

namespace esphome {
namespace mipi_dsi {

static bool notify_refresh_ready(esp_lcd_panel_handle_t panel, esp_lcd_dpi_panel_event_data_t *edata, void *user_ctx) {
  auto *sem = static_cast<SemaphoreHandle_t *>(user_ctx);
  BaseType_t need_yield = pdFALSE;
  xSemaphoreGiveFromISR(sem, &need_yield);
  return (need_yield == pdTRUE);
}
void MIPI_DSI::setup() {
  ESP_LOGCONFIG(TAG, "Running Setup");

  /*for (auto *pin : this->enable_pins_) {
    pin->setup();
    pin->digital_write(true);
  }
  delay(10);
*/

  esp_lcd_dsi_bus_config_t bus_config = {
      .bus_id = 0,  // index from 0, specify the DSI host to use
      .num_data_lanes =
          this->lanes_,  // Number of data lanes to use, can't set a value that exceeds the chip's capability
      .phy_clk_src = MIPI_DSI_PHY_CLK_SRC_DEFAULT,  // Clock source for the DPHY
      .lane_bit_rate_mbps = this->lane_bit_rate_,   // Bit rate of the data lanes, in Mbps
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
  esp_lcd_dpi_panel_config_t dpi_config = {.virtual_channel = 0,
                                           .dpi_clk_src = MIPI_DSI_DPI_CLK_SRC_DEFAULT,
                                           .dpi_clock_freq_mhz = this->pclk_frequency_,
                                           .pixel_format = LCD_COLOR_PIXEL_FORMAT_RGB565,
                                           .num_fbs = 1,  // number of frame buffers to allocate
                                           .video_timing =
                                               {
                                                   .h_size = this->width_,
                                                   .v_size = this->height_,
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
  if (this->reset_pin_ != nullptr) {
    this->reset_pin_->setup();
    this->reset_pin_->digital_write(true);
    delay(5);
    this->reset_pin_->digital_write(false);
    delay(5);
    this->reset_pin_->digital_write(true);
  } else {
    esp_lcd_panel_io_tx_param(this->io_handle_, SW_RESET_CMD, nullptr, 0);
  }
  // need to know when the display is ready for SLPOUT command - will be 120ms after reset
  auto when = millis() + 120;
  err = esp_lcd_panel_init(this->handle_);
  if (err != ESP_OK) {
    this->smark_failed("esp_lcd_init failed", err);
    return;
  }
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

        default:
          break;
      }
      const auto *ptr = vec.data() + index;
      ESP_LOGVV(TAG, "Command %02X, length %d, byte(s) %s", cmd, num_args,
                format_hex_pretty(ptr, num_args, '.', false).c_str());
      err = esp_lcd_panel_io_tx_param(this->io_handle_, cmd, ptr, num_args);
      if (err != ESP_OK) {
        this->smark_failed("lcd_panel_io_tx_param failed", err);
        return;
      }
      index += num_args;
      if (cmd == SLEEP_OUT)
        delay(10);
    }
  }
  this->io_lock_ = xSemaphoreCreateBinary();
  esp_lcd_dpi_panel_event_callbacks_t cbs = {
      .on_color_trans_done = notify_refresh_ready,
  };

  err = (esp_lcd_dpi_panel_register_event_callbacks(this->handle_, &cbs, this->io_lock_));
  if (err != ESP_OK) {
    this->smark_failed("Failed to register callbacks", err);
    return;
  }

  ESP_LOGCONFIG(TAG, "MIPI SPI setup complete");
}

void MIPI_DSI::draw_pixels_at(int x_start, int y_start, int w, int h, const uint8_t *ptr, display::ColorOrder order,
                              display::ColorBitness bitness, bool big_endian, int x_offset, int y_offset, int x_pad) {
  if (w <= 0 || h <= 0)
    return;
  // if color mapping is required, pass the buck.
  // note that endianness is not considered here - it is assumed to match!
  if (bitness != display::COLOR_BITNESS_565) {
    display::Display::draw_pixels_at(x_start, y_start, w, h, ptr, order, bitness, big_endian, x_offset, y_offset,
                                     x_pad);
  }
  esp_err_t err;
  auto stride = (x_offset + w + x_pad) * 2;
  ptr += y_offset * stride + x_offset * 2;  // skip to the first pixel
  // x_ and y_offset are offsets into the source buffer, unrelated to our own offsets into the display.
  if (x_offset == 0 && x_pad == 0) {
    err = esp_lcd_panel_draw_bitmap(this->handle_, x_start, y_start, x_start + w, y_start + h, ptr);
    xSemaphoreTake(this->io_lock_, portMAX_DELAY);

  } else {
    // draw line by line
    for (int y = 0; y != h; y++) {
      err = esp_lcd_panel_draw_bitmap(this->handle_, x_start, y + y_start, x_start + w, y + y_start + 1, ptr);
      if (err != ESP_OK)
        break;
      ptr += stride;  // next line
      xSemaphoreTake(this->io_lock_, portMAX_DELAY);
    }
  }
  if (err != ESP_OK)
    ESP_LOGE(TAG, "lcd_lcd_panel_draw_bitmap failed: %s", esp_err_to_name(err));
}

void MIPI_DSI::draw_pixel_at(int x, int y, Color color) {
  if (!this->get_clipping().inside(x, y))
    return;  // NOLINT

  switch (this->rotation_) {
    case display::DISPLAY_ROTATION_0_DEGREES:
      break;
    case display::DISPLAY_ROTATION_90_DEGREES:
      std::swap(x, y);
      x = this->width_ - x - 1;
      break;
    case display::DISPLAY_ROTATION_180_DEGREES:
      x = this->width_ - x - 1;
      y = this->height_ - y - 1;
      break;
    case display::DISPLAY_ROTATION_270_DEGREES:
      std::swap(x, y);
      y = this->height_ - y - 1;
      break;
  }
  auto pixel = convert_big_endian(display::ColorUtil::color_to_565(color));

  this->draw_pixels_at(x, y, 1, 1, (const uint8_t *) &pixel, display::COLOR_ORDER_RGB, display::COLOR_BITNESS_565, true,
                       0, 0, 0);
  App.feed_wdt();
}

int MIPI_DSI::get_width() {
  switch (this->rotation_) {
    case display::DISPLAY_ROTATION_90_DEGREES:
    case display::DISPLAY_ROTATION_270_DEGREES:
      return this->get_height_internal();
    case display::DISPLAY_ROTATION_0_DEGREES:
    case display::DISPLAY_ROTATION_180_DEGREES:
    default:
      return this->get_width_internal();
  }
}

int MIPI_DSI::get_height() {
  switch (this->rotation_) {
    case display::DISPLAY_ROTATION_0_DEGREES:
    case display::DISPLAY_ROTATION_180_DEGREES:
      return this->get_height_internal();
    case display::DISPLAY_ROTATION_90_DEGREES:
    case display::DISPLAY_ROTATION_270_DEGREES:
    default:
      return this->get_width_internal();
  }
}

static const uint8_t PIXEL_MODES[] = {0, 16, 18, 24};

void MIPI_DSI::dump_config() {
  ESP_LOGCONFIG(TAG,
                "MIPI_DSI RGB LCD"
                "\n  Model: %s"
                "\n  Width: %u"
                "\n  Height: %u"
                "\n  Mirror X: %s"
                "\n  Mirror Y: %s"
                "\n  Swap X/Y: %s"
                "\n  Rotation: %d degrees"
                "\n  DSI Lanes: %u"
                "\n  Lane Bit Rate: %uMbps"
                "\n  HSync Pulse Width: %u"
                "\n  HSync Back Porch: %u"
                "\n  HSync Front Porch: %u"
                "\n  VSync Pulse Width: %u"
                "\n  VSync Back Porch: %u"
                "\n  VSync Front Porch: %u"
                "\n  Pixel Mode: %d bit"
                "\n  Color Order: %s"
                "\n  Invert Colors: %s"
                "\n  Pixel Clock: %dMHz",
                this->model_, this->width_, this->height_, YESNO(this->madctl_ & MADCTL_MX),
                YESNO(this->madctl_ & MADCTL_MY), YESNO(this->madctl_ & MADCTL_MV), this->rotation_, this->lanes_,
                this->lane_bit_rate_, this->hsync_pulse_width_, this->hsync_back_porch_, this->hsync_front_porch_,
                this->vsync_pulse_width_, this->vsync_back_porch_, this->vsync_front_porch_,
                PIXEL_MODES[this->madctl_ & 0x03], this->madctl_ & MADCTL_BGR ? "BGR" : "RGB",
                YESNO(this->invert_colors_), this->pclk_frequency_);
  LOG_PIN("  Reset Pin ", this->reset_pin_);
}
}  // namespace mipi_dsi
}  // namespace esphome
#endif  // USE_ESP32_VARIANT_ESP32P4
