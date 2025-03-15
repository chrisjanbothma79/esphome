#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

// CRC16 implementation based on the provided configuration
uint16_t calculateCRC16(const std::vector<uint8_t>& data) {
    uint16_t crc = 0xFFFE;
    uint16_t polynomial = 0x1021;

    for (uint8_t byte : data) {
        crc ^= (static_cast<uint16_t>(byte) << 8);
        for (int i = 0; i < 8; ++i) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

std::vector<uint8_t> packet(uint32_t id, uint16_t command, uint8_t counter) {
    std::vector<uint8_t> data;

    // preamble (8 bytes)
    uint64_t preamble = 0x533914DD1C493412;
    for (int i = 7; i >= 0; --i) {
        data.push_back(static_cast<uint8_t>((preamble >> (i * 8)) & 0xFF));
    }

    // remote id (3 bytes)
    for (int i = 2; i >= 0; --i) {
        data.push_back(static_cast<uint8_t>((id >> (i * 8)) & 0xFF));
    }

    // separator (1 byte)
    uint8_t separator = 0xFF;
    data.push_back(separator);

    // sequence counter (1 byte)
    data.push_back(counter);

    // command id (2 bytes)
    for (int i = 1; i >= 0; --i) {
        data.push_back(static_cast<uint8_t>((command >> (i * 8)) & 0xFF));
    }

    // CRC16 (2 bytes)
    uint16_t crc = calculateCRC16(data);
    for (int i = 1; i >= 0; --i) {
        data.push_back(static_cast<uint8_t>((crc >> (i * 8)) & 0xFF));
    }

    return data;
}

// int main() {
//     uint32_t remoteId = 0x01B960; // Example remote ID
//     uint16_t command = 0x0100;    // Example command (on/off)
//     uint8_t counter = 0x79;       // Example counter

//     std::vector<uint8_t> packetData = packet(remoteId, command, counter);

//     std::cout << "Packet: ";
//     for (uint8_t byte : packetData) {
//         std::cout << std::hex << static_cast<int>(byte) << " ";
//     }
//     std::cout << std::dec << std::endl;

//     return 0;
// }