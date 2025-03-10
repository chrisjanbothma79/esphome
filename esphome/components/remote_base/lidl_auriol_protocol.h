#pragma once

#include "remote_base.h"

namespace esphome {
namespace remote_base {

struct LidlAuriolData {
  std::string model;
  uint64_t code{};
  uint16_t id{};
  float battery_level{};
  uint8_t channel{};
  float temperature{};
  uint8_t humidity{};
  float rain{};
  uint16_t wind_direction_degrees{};
  float wind_speed{};
  float wind_gust{};
};

class LidlAuriolProtocol : public RemoteProtocol<LidlAuriolData> {
 public:
  void encode(RemoteTransmitData *dst, const LidlAuriolData &data) override;
  optional<LidlAuriolData> decode(RemoteReceiveData src) override;
  void dump(const LidlAuriolData &data) override;
};

DECLARE_REMOTE_PROTOCOL(LidlAuriol)

template<typename... Ts> class LidlAuriolAction : public RemoteTransmitterActionBase<Ts...> {
 public:
  TEMPLATABLE_VALUE(std::string, model)
  TEMPLATABLE_VALUE(uint16_t, id)
  TEMPLATABLE_VALUE(float, battery_level)
  TEMPLATABLE_VALUE(uint8_t, channel)
  TEMPLATABLE_VALUE(float, temperature)
  TEMPLATABLE_VALUE(uint8_t, humidity)
  TEMPLATABLE_VALUE(float, rain)
  TEMPLATABLE_VALUE(float, wind_direction_degrees)
  TEMPLATABLE_VALUE(float, wind_speed)
  TEMPLATABLE_VALUE(float, wind_gust)
  void encode(RemoteTransmitData *dst, Ts... x) override {
    LidlAuriolData data{};
    data.model = this->model_.value(x...);
    data.id = this->id_.value(x...);
    data.battery_level = this->battery_level_.value(x...);
    data.channel = this->channel_.value(x...);
    data.temperature = this->temperature_.value(x...);
    data.humidity = this->humidity_.value(x...);
    data.rain = this->rain_.value(x...);
    data.wind_direction_degrees = this->wind_direction_degrees_.value(x...);
    data.wind_speed = this->wind_speed_.value(x...);
    data.wind_gust = this->wind_gust_.value(x...);
    LidlAuriolProtocol().encode(dst, data);
  }
};

}  // namespace remote_base
}  // namespace esphome
