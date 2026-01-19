#pragma once
#include <cstdint>
#include "include/shaiya/SNode.h"
#include "include/shaiya/SkillInfo.h"

namespace shaiya
{
#pragma pack(push, 1)
    struct CSkill
    {
        SNode node;             // 0x00
        uint32_t id;            // 0x08
        uint32_t skillId;       // 0x0C
        uint32_t skillLv;       // 0x10
        uint32_t skillListIndex; // 0x14

        uint32_t tick1;         // 0x18
        uint32_t resetTick;     // 0x1C
        uint32_t tick2;         // 0x20
        uint32_t tick3;         // 0x24
        uint32_t tick4;         // 0x28
        uint32_t tick5;         // 0x2C

        uint32_t debuffCasterId; // 0x30
        SkillInfo* skillInfo;   // 0x34
    };
#pragma pack(pop)
}