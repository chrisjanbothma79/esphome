#pragma once

namespace esphome {
namespace dlms_meter {

/*
 * Data structure
 */

/*
+----------------------------------------------------+ -
|               Start Character [0x68]               |  \
+----------------------------------------------------+   |
|                   Data Length (L)                  |   |
+----------------------------------------------------+   |
|               Data Length Repeat (L)               |   |
+----------------------------------------------------+    > M-Bus Data link layer
|            Start Character Repeat [0x68]           |   |
+----------------------------------------------------+   |
|             Control/Function Field (C)             |   |
+----------------------------------------------------+   |
|                  Address Field (A)                 |  /
+----------------------------------------------------+ -
|           Control Information Field (CI)           |  \
+----------------------------------------------------+   |
|    Source Transport Service Access Point (STSAP)   |    > DLMS/COSEM M-Bus transport layer
+----------------------------------------------------+   |
| Destination Transport Service Access Point (DTSAP) |  /
+----------------------------------------------------+ -
|                                                    |  \
~                                                    ~   |
                         Data                             > DLMS/COSEM Application Layer
~                                                    ~   |
|                                                    |  /
+----------------------------------------------------+ -
|                      Checksum                      |  \
+----------------------------------------------------+    > M-Bus Data link layer
|                Stop Character [0x16]               |  /
+----------------------------------------------------+ -

Data_Length = L - C - A - CI
Each line (except Data) is one Byte

Possible Values found in publicly available docs:
- C: 0x53/0x73 (SND_UD)
- A: FF (Broadcast)
- CI: 0x00-0x1F/0x60/0x61/0x7C/0x7D
- STSAP: 0x01 (Management Logical Device ID 1 of the meter)
- DTSAP: 0x67 (Consumer Information Push Client ID 103)
 */

static const int MBUS_HEADER_INTRO_LENGTH = 4;  // Header length for the intro (0x68, length, length, 0x68)
static const int MBUS_FULL_HEADER_LENGTH = 9;   // Total header length
static const int MBUS_FOOTER_LENGTH = 2;        // Footer after frame

static const int MBUS_MAX_FRAME_LENGTH = 250;  // Maximum size of frame

static const int MBUS_START1_OFFSET = 0;   // Offset of first start byte
static const int MBUS_LENGTH1_OFFSET = 1;  // Offset of first length byte
static const int MBUS_LENGTH2_OFFSET = 2;  // Offset of (duplicated) second length byte
static const int MBUS_START2_OFFSET = 3;   // Offset of (duplicated) second start byte

}  // namespace dlms_meter
}  // namespace esphome
