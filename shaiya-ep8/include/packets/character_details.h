#pragma once
#include <cstdint>
#include "include/packets/packet.h"
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace packets
{
	namespace character_details
	{
#pragma pack(push, 1)
		struct Details
		{
			PacketType opcode;

			uint16_t strength;
			uint16_t dexterity;
			uint16_t intelligence;
			uint16_t wisdom;
			uint16_t resistance;
			uint16_t luck;

			uint16_t stat_points;
			uint16_t skill_points;

			uint32_t max_hp;
			uint32_t max_mp;
			uint32_t max_sp;

			uint16_t angle;

			uint32_t start_exp;
			uint32_t end_exp;
			uint32_t current_exp;

			uint32_t gold;

			float pos_x;
			float pos_y;
			float pos_z;

			uint32_t kills;
			uint32_t deaths;
			uint32_t victories;
			uint32_t defeats;

			char guild_name[25];
		};
#pragma pack(pop)

		void __fastcall send(CUser* user);
		void hook();
	}
}