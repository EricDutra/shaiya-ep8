#pragma once
#include <cstdint>

namespace shaiya
{
#pragma pack(push, 1)
    struct BlockUser
    {
        uint32_t charId;        // 0x00
        char charname[21];      // 0x04
        char memo[51];          // 0x19
    };

    struct CFriend
    {
        uint32_t charId;        // 0x00
        uint8_t country;        // 0x04
        uint8_t grow;           // 0x05
        uint8_t job;            // 0x06
        char charname[21];      // 0x07
        char memo[51];          // 0x1C
        uint8_t _;              // 0x50
    };
#pragma pack(pop)
}