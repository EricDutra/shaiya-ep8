#pragma once
#include <cstdint>

namespace packets
{
    enum struct PacketType : uint16_t
    {
		CharacterList = 0x0101,
		CheckCharnameAvailable = 0x0119,
        AutoStatsList = 0x0120
    };

	struct Packet
	{
		PacketType opcode;
		uint8_t data[512];
	};
}