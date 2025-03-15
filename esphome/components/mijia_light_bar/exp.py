
# 0xc97e40
import crc
import crc
from struct import unpack

crc16_config = crc.Configuration(
    width=16,
    polynomial=0x1021,
    init_value=0xFFFE,
    final_xor_value=0x0000,
    reverse_input=False,
    reverse_output=False,
)
crc16 = crc.Calculator(crc16_config)

def print_binary(data: int):
    print(' > '  + ' '.join(F"{byte:08b}" for byte in data.to_bytes((data.bit_length() + 7) // 8, 'big')))

def strip_bits(num: int, msb: int, lsb: int):
    """Strip msb and lsb bits of an int"""

    print("original")
    print_binary(num)
    mask = (1 << num.bit_length()-msb + 1)-1
    print("mask")
    print_binary(mask)
    return (num & mask) >> lsb
preamble = 0x533914DD1C493412  # 8 bytes


# byte_data = b'\x49\x34\x12\xc9\x7e\x40\xff\x01\x01\x00\xd2\xa4'
byte_data = b'\x49\x34\x12\xc9\x7e\x40\xff\x02\x01\x00\x8b\xf4'
raw = int.from_bytes(byte_data, 'big')
print_binary(raw)

# for bits_to_strip in range(24):
#     stripped = strip_bits(raw, bits_to_strip, 24 - bits_to_strip)
#     print(f"Stripped {bits_to_strip}")
#     print_binary(stripped)

def strip_bits(num: int, msb: int, lsb: int):
    """Strip msb and lsb bits of an int"""

    mask = (1 << 96-msb)-1
    return (num & mask) >> lsb


def decode_packet(raw: bytes):
    """Decode a received packet

    I captured 12 bytes = 96 bits, but:
    - The first 15 bits (MSB) are the preamble trailing ones.
      Remember that the 24 LSB from the preamble were included in the captured packet.
      Where the other 9 bits are gone, I do not know. Maybe the ether monster ate them.
    - 9 bytes = 72 bits are the good ones, the payload.
    - The remaining 9 bits (LSB) are junk.
    """

    # Strip the preamble and junk bits
    raw_int = int.from_bytes(raw, "big")
    data = strip_bits(raw_int, 24, 0)

    # Now, the payload is clean and ready to be decoded
    keys = ["id", "separator", "counter", "command", "crc"]
    values = unpack('>3s s s 2s 2s', data.to_bytes(9, 'big'))
    values = (int.from_bytes(x, "big") for x in values)
    packet = dict(zip(keys, values))
    return packet


def good_packet(packet: int):
    """Check the CRC of a packet"""

    x = preamble.to_bytes(8, 'big')
    x += packet["id"].to_bytes(3, 'big')
    x += packet["separator"].to_bytes(1, 'big')
    x += packet["counter"].to_bytes(1, 'big')
    x += packet["command"].to_bytes(2, 'big')
    return packet["crc"] == crc16.checksum(x)

def print_packet(packet: int):
    if good_packet(packet):
        print("Decoded packet, CRC ok")
    else:
        print("Decoded packet, wrong CRC")
    for k, v in packet.items():
        print(f"• {k}: {hex(v)}")


packet = decode_packet(byte_data)
print()
print_packet(packet)