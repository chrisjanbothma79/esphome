#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

#include <vector>
#include <array>

namespace esphome {
namespace emontx {
/*
 * 198 bytes should be enough to contain a full session in historical mode with
 * three phases. But go with 1024 just to be sure.
 */
constexpr uint8_t MAX_TAG_SIZE = 16;
constexpr uint16_t MAX_VAL_SIZE = 16;
constexpr uint16_t MAX_BUF_SIZE = 1048;

/**
 * @class emonTxListener
 * @brief Listener interface for receiving updates from the emonTx.
 *
 * This class allows other components to register as listeners to receive updates
 * for specific tags published by the emonTx.
 */
class emonTxListener {
 public:
  std::string tag;
  virtual void publish_val(const std::string &val){};
};

/**
 * @class emonTx
 * @brief Main class for the emonTx component.
 *
 * The emonTx processes incoming data frames via UART, validates their CRC,
 * extracts tags and values, and publishes them to registered listeners.
 */
class emonTx : public PollingComponent, public uart::UARTDevice {
 public:
  emonTx();
  void register_emontx_listener(emonTxListener *listener);
  void loop() override;
  void setup() override;
  void update() override;
  void dump_config() override;
  std::vector<emonTxListener *> emontx_listeners_{};

 protected:
  uint32_t baud_rate_;
  size_t checksum_area_end_;
  std::array<char, MAX_BUF_SIZE> buf_;
  size_t buf_index_{0};
  std::string tag_;
  std::string val_;

  enum class State {
    OFF,
    ON,
    START_FRAME_RECEIVED,
    END_FRAME_RECEIVED,
  };

  State state_{State::OFF};

  bool read_chars_until_(bool drop, uint8_t c);
  uint8_t calculate_crc_(const char *grp, size_t grp_len);
  bool check_crc_(const char *grp, const char *grp_end);
  void publish_value_(const std::string &tag, const std::string &val);
};
}  // namespace emontx
}  // namespace esphome
