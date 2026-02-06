#include "include/packets/character/status.h"
#include "include/utils/memory.h"

namespace packets::character::status
{
	void __fastcall send(CUser* user)
	{
		StatusPacket status{};

		status.opcode = packets::PacketType::CharacterStatus;

		status.strength = (user->abilityStr - user->strength);
		status.dexterity = (user->abilityDex - user->dexterity);
		status.resistance = (user->abilityRec - user->resistance);
		status.intelligence = (user->abilityInt - user->intelligence);
		status.wisdom = (user->abilityWis - user->wisdom);
		status.luck = (user->abilityLuc - user->luck);
		status.min_attack = (user->job == 3) ? user->minRangeAttack : user->minPhysicalAttack;
		status.max_attack = (status.min_attack + user->attackPowerAdd);
		status.min_magic = user->minMagicAttack;
		status.max_magic = (status.min_magic + user->attackPowerAdd);
		status.defense = user->physicalDefence;
		status.magic_resistance = user->magicResist;

		user->Send((void*)&status, sizeof(StatusPacket));
	}

	uintptr_t send_character_status_return = 0x00461005;

	NAKED void send_character_status_hook()
	{
		__asm {
			mov [esi + 0x1434], ecx

			pushad
			mov ecx, esi
			call packets::character::status::send
			popad

			jmp send_character_status_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x00460FFF, send_character_status_hook, 6);
	}
}