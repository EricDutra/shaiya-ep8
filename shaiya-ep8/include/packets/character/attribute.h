#pragma once
#include <cstdint>
#include "include/packets/packet.h"
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace packets::character::attribute
{
#pragma pack(push, 1)
    struct AttributePacket
    {
        PacketType opcode = PacketType::AttributeSet;
        uint8_t id = 0;
        uint32_t attribute = 0;
    };
#pragma pack(pop)

    void send(CUser* user, uint8_t attribute_id, uint32_t attribute);
}