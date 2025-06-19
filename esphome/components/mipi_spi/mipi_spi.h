#pragma once

#include <utility>

#include "esphome/components/spi/spi.h"
#include "esphome/components/display/display.h"
#include "esphome/components/display/display_buffer.h"
#include "esphome/components/display/display_color_utils.h"

namespace esphome {
namespace mipi_spi {

constexpr static const char *const TAG = "display.mipi_spi";
static const uint8_t SW_RESET_CMD = 0x01;
static const uint8_t SLEEP_OUT = 0x11;
static const uint8_t NORON = 0x13;
static const uint8_t INVERT_OFF = 0x20;
static const uint8_t INVERT_ON = 0x21;
static const uint8_t ALL_ON = 0x23;
static const uint8_t WRAM = 0x24;
static const uint8_t MIPI = 0x26;
static const uint8_t DISPLAY_ON = 0x29;
static const uint8_t RASET = 0x2B;
static const uint8_t CASET = 0x2A;
static const uint8_t WDATA = 0x2C;
static const uint8_t TEON = 0x35;
static const uint8_t MADCTL_CMD = 0x36;
static const uint8_t PIXFMT = 0x3A;
static const uint8_t BRIGHTNESS = 0x51;
static const uint8_t SWIRE1 = 0x5A;
static const uint8_t SWIRE2 = 0x5B;
static const uint8_t PAGESEL = 0xFE;

static const uint8_t MADCTL_MY = 0x80;     // Bit 7 Bottom to top
static const uint8_t MADCTL_MX = 0x40;     // Bit 6 Right to left
static const uint8_t MADCTL_MV = 0x20;     // Bit 5 Swap axes
static const uint8_t MADCTL_RGB = 0x00;    // Bit 3 Red-Green-Blue pixel order
static const uint8_t MADCTL_BGR = 0x08;    // Bit 3 Blue-Green-Red pixel order
static const uint8_t MADCTL_XFLIP = 0x02;  // Mirror the display horizontally
static const uint8_t MADCTL_YFLIP = 0x01;  // Mirror the display vertically

static const uint8_t DELAY_FLAG = 0xFF;
// store a 16 bit value in a buffer, big endian.
static inline void put16_be(uint8_t *buf, uint16_t value) {
  buf[0] = value >> 8;
  buf[1] = value;
}

// Buffer mode, conveniently also the number of bytes in a pixel
enum PixelMode {
  PIXEL_MODE_8 = 1,
  PIXEL_MODE_16 = 2,
  PIXEL_MODE_18 = 3,
};

enum BusType {
  BUS_TYPE_SINGLE = 1,
  BUS_TYPE_QUAD = 4,
  BUS_TYPE_OCTAL = 8,
  BUS_TYPE_SINGLE_16 = 16,  // Single bit bus, but 16 bits per transfer
};

/**
 * Un-templated base class for MIPI SPI displays.
 * This defines methods and properties that don't depend on the pixel mode or bus type.
 */

class MipiSpi : public display::DisplayBuffer,
                public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING,
                                      spi::DATA_RATE_1MHZ> {
 public:
  MipiSpi(size_t width, size_t height, int16_t offset_width, int16_t offset_height)
      : width_(width), height_(height), offset_width_(offset_width), offset_height_(offset_height) {}
  void set_model(const char *model) { this->model_ = model; }
  void update() override;
  void setup() override;

  void set_reset_pin(GPIOPin *reset_pin) { this->reset_pin_ = reset_pin; }
  void set_enable_pins(std::vector<GPIOPin *> enable_pins) { this->enable_pins_ = std::move(enable_pins); }
  void set_dc_pin(GPIOPin *dc_pin) { this->dc_pin_ = dc_pin; }
  void set_invert_colors(bool invert_colors) {
    this->invert_colors_ = invert_colors;
    this->reset_params_();
  }
  void set_brightness(uint8_t brightness) {
    this->brightness_ = brightness;
    this->reset_params_();
  }

  void set_draw_from_origin(bool draw_from_origin) { this->draw_from_origin_ = draw_from_origin; }
  display::DisplayType get_display_type() override { return display::DisplayType::DISPLAY_TYPE_COLOR; }
  void dump_config() override;

  int get_width_internal() override { return this->width_; }
  int get_height_internal() override { return this->height_; }
  bool can_proceed() override { return this->setup_complete_; }
  void set_init_sequence(const std::vector<uint8_t> &sequence) { this->init_sequence_ = sequence; }
  void set_draw_rounding(unsigned rounding) { this->draw_rounding_ = rounding; }
  void set_spi_16(bool spi_16) { this->spi_16_ = spi_16; }

 protected:
  void draw_pixels_at(int x_start, int y_start, int w, int h, const uint8_t *ptr, display::ColorOrder order,
                      display::ColorBitness bitness, bool big_endian, int x_offset, int y_offset, int x_pad) override;
  virtual void write_to_display_(int x_start, int y_start, int w, int h, const uint8_t *ptr, int x_offset, int y_offset,
                                 int x_pad) = 0;

  void write_command_(uint8_t cmd, const uint8_t *bytes, size_t len);
  void write_command_(uint8_t cmd, uint8_t data) { this->write_command_(cmd, &data, 1); }
  void write_command_(uint8_t cmd) { this->write_command_(cmd, &cmd, 0); }
  void reset_params_();
  void write_init_sequence_();
  void set_addr_window_(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

  GPIOPin *reset_pin_{nullptr};
  std::vector<GPIOPin *> enable_pins_{};
  GPIOPin *dc_pin_{nullptr};
  uint16_t x_low_{1};
  uint16_t y_low_{1};
  uint16_t x_high_{0};
  uint16_t y_high_{0};
  bool setup_complete_{};

  bool invert_colors_{};
  size_t width_;
  size_t height_;
  int16_t offset_width_;
  int16_t offset_height_;
  size_t buffer_bytes_{0};
  display::ColorBitness color_depth_{};
  uint8_t bus_width_{};
  bool spi_16_{};
  uint8_t madctl_{};
  bool draw_from_origin_{false};
  unsigned draw_rounding_{2};
  optional<uint8_t> brightness_{};
  const char *model_{"Unknown"};
  std::vector<uint8_t> init_sequence_{};
};

}  // namespace mipi_spi
}  // namespace esphome
