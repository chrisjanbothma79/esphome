#pragma once

#include "remote_base.h"

namespace esphome {
namespace remote_base {

/**
 * Raw NEC‐style IR protocol (NEC_Like) that captures low‐level bits.
 */
struct NECLikeData {
  std::vector<bool> bits_;

  bool operator==(const NECLikeData &rhs) const { return bits_ == rhs.bits_; }
};

class NECLikeProtocol : public RemoteProtocol<NECLikeData> {
 public:
  void encode(RemoteTransmitData *dst, const NECLikeData &data) override;
  optional<NECLikeData> decode(RemoteReceiveData src) override;
  void dump(const NECLikeData &data) override;
  void swap_nibbles(NECLikeData &data);
};

DECLARE_REMOTE_PROTOCOL(NECLike)

/**
 * Action to send raw NEC_Like bitstrings.
 */
template<typename... Ts> class NECLikeAction : public RemoteTransmitterActionBase<Ts...> {
 public:
  TEMPLATABLE_VALUE(std::string, bits)

  void encode(RemoteTransmitData *dst, Ts... x) override {
    NECLikeData data;
    data.bits_ = this->bits_.value(x...);
    NECLikeProtocol().encode(dst, data);
  }
};

}  // namespace remote_base
}  // namespace esphome
