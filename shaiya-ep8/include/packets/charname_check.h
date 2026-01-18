#pragma once
#include <cstdint>
#include "include/shaiya/CUser.h"
#include "include/packets/packet.h"

using namespace shaiya;

namespace packets
{
	namespace charname_check
	{

#pragma pack(push, 1)

		struct Response
		{
			PacketType opcode;
			bool available;
		};

#pragma pack(pop)

		void check(CUser* user, Packet* packet);
	}
}