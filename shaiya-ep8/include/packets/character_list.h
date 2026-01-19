#pragma once
#include <cstdint>
#include "include/packets/packet.h"
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace packets
{
	namespace character_list
	{
#pragma pack(push, 1)
        struct Character
        {
			PacketType opcode;

			uint8_t  slot;
			uint32_t char_id;
			uint32_t creation_time;

			uint16_t level;
			uint8_t  family;
			uint8_t  mode;
			uint8_t  hair;
			uint8_t  face;
			uint8_t  height;
			uint8_t  job;
			uint8_t  gender;

			uint16_t map;

			uint16_t strength;
			uint16_t dexterity;
			uint16_t resistance;
			uint16_t intelligence;
			uint16_t wisdom;
			uint16_t luck;

			uint8_t  unk_1[6];

			// equipment types
			uint8_t  helmet_type;
			uint8_t  armor_type;
			uint8_t  pants_type;
			uint8_t  glove_type;
			uint8_t  boot_type;
			uint8_t  weapon_type;
			uint8_t  shield_type;
			uint8_t  cape_type;

			uint8_t  unk_2[6];

			uint8_t  pet_type;
			uint8_t  costume_type;
			uint8_t  wing_type;

			// equipment type IDs
			uint8_t  helmet_type_id;
			uint8_t  armor_type_id;
			uint8_t  pants_type_id;
			uint8_t  glove_type_id;
			uint8_t  boot_type_id;
			uint8_t  weapon_type_id;
			uint8_t  shield_type_id;
			uint8_t  cape_type_id;

			uint8_t  unk_3[6];

			uint8_t  pet_type_id;
			uint8_t  costume_type_id;
			uint8_t  wing_type_id;

			uint8_t  unk_4[540];

			char     name[19];

			uint8_t  delete_flag;
			uint8_t  rename_flag;
        };
#pragma pack(pop)

        void __fastcall send(CUser* user, void* old_packet);
        void hook();
	}
}