#pragma once
#include <cstdint>

namespace packets
{
    enum struct PacketType : uint16_t
    {
		CharacterList = 0x0101,
		CharacterDetails = 0x0105,
		CheckCharnameAvailable = 0x0119,
        AutoStatsList = 0x0120,
		CharacterStatus = 0x0526,
		Ping = 0xA303
    };

	struct Packet
	{
		PacketType opcode;
		uint8_t data[512];
	};
}