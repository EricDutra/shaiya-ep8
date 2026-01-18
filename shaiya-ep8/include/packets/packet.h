#pragma once
#include <cstdint>

namespace packets
{
    enum struct PacketType : uint16_t
    {
        AutoStatsList = 0x0120
    };

	struct Packet
	{
		PacketType opcode;
		uint8_t data[512];
	};
}