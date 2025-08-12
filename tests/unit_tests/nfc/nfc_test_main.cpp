#include "esphome/components/nfc/nfc.h"
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace esphome {
static char format_hex_pretty_char(uint8_t v) { return v >= 10 ? 'A' + (v - 10) : '0' + v; }
std::string format_hex_pretty(const std::vector<uint8_t> &data, char separator, bool show_length) {
  if (data.empty())
    return "";
  std::string ret;
  uint8_t multiple = separator ? 3 : 2;
  ret.resize(multiple * data.size() - (separator ? 1 : 0));
  for (size_t i = 0; i < data.size(); i++) {
    ret[multiple * i] = format_hex_pretty_char((data[i] & 0xF0) >> 4);
    ret[multiple * i + 1] = format_hex_pretty_char(data[i] & 0x0F);
    if (separator && i != data.size() - 1)
      ret[multiple * i + 2] = separator;
  }
  if (show_length && data.size() > 4)
    return ret + " (" + std::to_string(data.size()) + ")";
  return ret;
}
}  // namespace esphome

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;
  std::string cmd = argv[1];
  if (cmd == "guess") {
    int len = std::atoi(argv[2]);
    printf("%u\n", esphome::nfc::guess_tag_type(len));
  } else if (cmd == "start_index") {
    std::vector<uint8_t> data;
    for (int i = 2; i < argc; i++) {
      unsigned int val;
      std::sscanf(argv[i], "%x", &val);
      data.push_back(val);
    }
    int res = esphome::nfc::get_mifare_classic_ndef_start_index(data);
    printf("%d\n", res);
  } else if (cmd == "decode") {
    std::vector<uint8_t> data;
    for (int i = 2; i < argc; i++) {
      unsigned int val;
      std::sscanf(argv[i], "%x", &val);
      data.push_back(val);
    }
    uint32_t length = 0;
    uint16_t start = 0;
    bool ok = esphome::nfc::decode_mifare_classic_tlv(data, length, start);
    if (ok)
      printf("ok %u %u\n", length, start);
    else
      printf("fail\n");
  } else if (cmd == "size") {
    int len = std::atoi(argv[2]);
    uint32_t res = esphome::nfc::get_mifare_classic_buffer_size(len);
    printf("%u\n", res);
  } else {
    return 1;
  }
  return 0;
}
