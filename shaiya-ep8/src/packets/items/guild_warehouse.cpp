#include "include/packets/items/guild_warehouse.h"
#include "include/packets/items/inventory.h"
#include "include/packets/packet.h"
#include "include/utils/buffer_reader.h"
#include "include/utils/memory.h"
#include <cstring>

using namespace utils::buffer_reader;

namespace packets::items::guild_warehouse
{
	

	

	const uintptr_t move_item_guild_return = 0x00435B95;

	NAKED void move_item_guild_hook()
	{
		__asm {
			pushad
			mov edx, ecx
			mov ecx, esi
			//call packets::items::guild_warehouse::send_move_item_from_old_packet
			popad
			add esp, 0x04
			jmp move_item_guild_return
		}
	}

	const uintptr_t remove_item_guild_return = 0x00436337;

	NAKED void remove_item_guild_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x5C]
			//call packets::items::guild_warehouse::send_remove_item_from_old_packet
			popad
			add esp, 0x08
			jmp remove_item_guild_return
		}
	}

	const uintptr_t item_list_guild_return = 0x00435094;

	NAKED void item_list_guild_hook()
	{
		__asm {
			pushad
			mov edx, eax
			//call packets::items::guild_warehouse::send_items_from_old_packet
			popad
			add esp, 0x08
			jmp item_list_guild_return
		}
	}

	const uintptr_t item_list_guild2_return = 0x00435055;

	NAKED void item_list_guild2_hook()
	{
		__asm {
			pushad
			mov edx, eax
			//call packets::items::guild_warehouse::send_items_from_old_packet
			popad
			add esp, 0x08
			jmp item_list_guild2_return
		}
	}

	const uintptr_t item_bag_to_guild2_return = 0x004357AB;

	NAKED void item_bag_to_guild_hook2()
	{
		__asm {
			pushad
			push eax
			mov edx, ebp
			mov ecx, edi
			//call packets::items::guild_warehouse::send_add_item_to_all_from_old_packet
			popad

			add esp, 0x08

			jmp item_bag_to_guild2_return
		}
	}

	const uintptr_t item_bag_to_guild_hook_return = 0x004357D5;

	NAKED void item_bag_to_guild_hook()
	{
		__asm {
			pushad
			call packets::items::inventory::send_move_item_from_old_packet
			popad

			add esp, 0x08

			jmp item_bag_to_guild_hook_return
		}
	}

	void hook()
	{
		// 004350B0 - CGuild::ItemBagToGuildBank
		utils::memory::hook((void*)0x004357D0, item_bag_to_guild_hook, 5);
		utils::memory::hook((void*)0x004357A6, item_bag_to_guild_hook2, 5);

		// 00435840 - CGuild::ItemGuildBankToGuildBank
		utils::memory::hook((void*)0x00435B90, move_item_guild_hook, 5);

		// 00435BC0 - CGuild::ItemGuildBankToBag
		utils::memory::hook((void*)0x00436332, remove_item_guild_hook, 5);

		// 00434F80 - CGuild::SendBankItemList
		utils::memory::hook((void*)0x00435050, item_list_guild2_hook, 5);
		utils::memory::hook((void*)0x0043508F, item_list_guild_hook, 5);
	}
}