#include "include/packets/handler.h"
#include "include/packets/character/charname_check.h"
#include "include/packets/items/inventory.h"
#include "include/utils/memory.h"

namespace packets::handler
{
	bool __fastcall process(CUser* user, Packet* packet)
	{
		switch (packet->opcode)
		{
			case PacketType::AutoStatsList:
				return true;

			case PacketType::CheckCharnameAvailable:
				packets::character::charname_check::check(user, packet);
				return true;

			case PacketType::SortInventoryItems:
				packets::items::inventory::sort_items(user);
				return true;

			case PacketType::Ping:
				return true;

			case (PacketType)0x0234: // unknown
				return true;
		}

		return false;
	}

	uintptr_t packet_processing_return = 0x00474963;
	uintptr_t packet_processing_ignore = 0x00474D75;

	NAKED void packet_processing_hook()
	{
		__asm {
			mov eax, [ebx + 0x57F4]
			xor esi, esi
			push edi
			mov edi, edx

			pushad
			mov edx, edi
			mov ecx, ebx
			call packets::handler::process
			test al, al
			popad
			jne _ignore

			jmp packet_processing_return

		_ignore:
			jmp packet_processing_ignore
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x00474958, packet_processing_hook, 6);
	}
}