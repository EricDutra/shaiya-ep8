#include "include/packets/character/details.h"
#include "include/shaiya/CGuild.h"
#include "include/utils/memory.h"

namespace packets::character::details
{
	uint32_t end_exp_by_level(uint16_t level, uint8_t mode)
	{
		constexpr uintptr_t base_address = 0x00589204;
		constexpr uint32_t mode_stride = 0x47;
		constexpr uint32_t entry_size = sizeof(uint32_t);

		uintptr_t address = base_address + entry_size * (static_cast<uint32_t>(mode) * mode_stride + level);

		return *reinterpret_cast<const uint32_t*>(address);
	}

	void __fastcall send(CUser* user)
	{
		DetailsPacket details{};

		details.opcode = packets::PacketType::CharacterDetails;

		details.strength = user->strength;
		details.dexterity = user->dexterity;
		details.intelligence = user->intelligence;
		details.wisdom = user->wisdom;
		details.resistance = user->resistance;
		details.luck = user->luck;

		details.stat_points = user->statPoints;
		details.skill_points = user->skillPoints;

		details.max_hp = user->maxHP;
		details.max_mp = user->maxMP;
		details.max_sp = user->maxSP;

		details.angle = user->direction;

		details.current_exp = user->exp;
		details.start_exp = end_exp_by_level(user->level - 1, user->grow);
		details.end_exp = end_exp_by_level(user->level, user->grow);

		details.gold = user->gold;

		details.pos_x = user->posX;
		details.pos_y = user->posY;
		details.pos_z = user->posZ;

		details.kills = user->kills;
		details.deaths = user->deaths;
		details.victories = user->victories;
		details.defeats = user->defeats;

		if (user->guild)
		{
			std::memcpy(details.guild_name, user->guild->name, sizeof(details.guild_name));
		}

		user->Send((void*)&details, sizeof(DetailsPacket));
	}

	uintptr_t send_character_details_return = 0x004924DA;

	NAKED void send_character_details_hook()
	{
		__asm {
			lea edx, [esp + 0x10]
			push edx
			mov ecx, esi

			pushad
			call packets::character::details::send
			popad

			add esp, 0x08

			jmp send_character_details_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x004924CE, send_character_details_hook, 7);
	}
}