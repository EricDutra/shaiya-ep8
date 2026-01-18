#pragma once
#include "include/packets/packet.h"
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace packets
{
	namespace handler
	{
		bool __fastcall process(CUser* user, Packet* packet);
		void hook();
	}
}