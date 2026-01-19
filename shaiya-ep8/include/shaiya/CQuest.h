#pragma once
#include <cstdint>
#include "include/shaiya/SNode.h"

namespace shaiya
{
#pragma pack(push, 1)
    struct CQuest
    {
        SNode node;           // 0x00
        uint32_t id;          // 0x08
        bool success;         // 0x0C
        uint8_t _0[3];        // 0x0D
        uint32_t addTick;     // 0x10
        uint32_t delay;       // 0x14
        uint32_t expireTick;  // 0x18
        uint8_t count1;       // 0x1C
        uint8_t count2;       // 0x1D
        uint8_t count3;       // 0x1E
        uint8_t _1;           // 0x1F
        uint32_t questInfo;   // 0x20 QuestInfo*
    };
#pragma pack(pop)
}