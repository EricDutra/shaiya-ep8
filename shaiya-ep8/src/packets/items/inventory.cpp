#include "include/packets/items/inventory.h"
#include "include/utils/memory.h"

namespace packets::items::inventory
{
	void __fastcall send_all(CUser* user)
	{
		for (uint8_t slot = 0; slot < 24; slot++)
		{
			CItem* item = user->equipment[slot];

			if (item)
			{
				user->SendItem(item, 0, slot);
			}
		}

		for (uint8_t bag = 0; bag < 5; bag++)
		{
			for (uint8_t slot = 0; slot < 24; slot++)
			{
				CItem* item = user->inventory[bag][slot];

				if (item)
				{
					user->SendItem(item, bag + 1, slot);
				}
			}
		}
	}

	const uintptr_t send_character_item_return = 0x0049263D;

	NAKED void send_character_item_hook()
	{
		__asm {
			pushad
			mov ecx, ebp
			call packets::items::inventory::send_all
			popad

			jmp send_character_item_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x0049251E, send_character_item_hook, 6);
	}
}