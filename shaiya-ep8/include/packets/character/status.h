#pragma once
#include <cstdint>
#include "include/packets/packet.h"
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace packets::character::status
{
#pragma pack(push, 1)
    struct StatusPacket
    {
        PacketType opcode;

        uint32_t strength;
        uint32_t resistance;
        uint32_t intelligence;
        uint32_t wisdom;
        uint32_t dexterity;
        uint32_t luck;

        uint32_t min_attack;
        uint32_t max_attack;
        uint32_t min_magic;
        uint32_t max_magic;

        uint32_t defense;
        uint32_t magic_resistance;
    };
#pragma pack(pop)

    void __fastcall send(CUser* user);
    void hook();
}