#include <cstring>
#include "include/packets/items/inventory.h"
#include "include/utils/memory.h"
#include "include/utils/buffer_reader.h"

using namespace utils::buffer_reader;

namespace packets::items::inventory
{
	void sort_items(CUser* user)
	{
		struct ItemSlot
		{
			CItem* item;
			uint8_t bag;
			uint8_t slot;
		};

		ItemSlot items[120];
		int item_count = 0;

		for (uint8_t bag = 0; bag < max_bag; bag++)
		{
			for (uint8_t slot = 0; slot < max_slot; slot++)
			{
				if (user->inventory[bag][slot] != nullptr)
				{
					items[item_count].item = user->inventory[bag][slot];
					items[item_count].bag = bag;
					items[item_count].slot = slot;
					item_count++;
				}
			}
		}

		for (int i = 0; i < item_count - 1; i++)
		{
			for (int j = i + 1; j < item_count; j++)
			{
				bool should_swap = false;

				if (items[i].item->type > items[j].item->type)
				{
					should_swap = true;
				}
				else if (items[i].item->type == items[j].item->type && items[i].item->typeId > items[j].item->typeId)
				{
					should_swap = true;
				}

				if (should_swap)
				{
					ItemSlot temp = items[i];
					items[i] = items[j];
					items[j] = temp;
				}
			}
		}

		uint8_t target_bag = 0;
		uint8_t target_slot = 0;

		for (int i = 0; i < item_count; i++)
		{
			if (items[i].bag != target_bag || items[i].slot != target_slot)
			{
				user->MoveItem(items[i].bag, items[i].slot, target_bag, target_slot);

				for (int j = i + 1; j < item_count; j++)
				{
					if (items[j].bag == target_bag && items[j].slot == target_slot)
					{
						items[j].bag = items[i].bag;
						items[j].slot = items[i].slot;
						break;
					}
				}

				items[i].bag = target_bag;
				items[i].slot = target_slot;
			}

			target_slot++;
			if (target_slot >= max_slot)
			{
				target_slot = 0;
				target_bag++;
			}
		}
	}

	void send_all(CUser* user)
	{
		for (uint8_t slot = 0; slot < max_slot; slot++)
		{
			CItem* item = user->equipment[slot];

			if (item)
			{
				user->SendItem(item, 0, slot);
			}
		}

		for (uint8_t bag = 0; bag < max_bag; bag++)
		{
			for (uint8_t slot = 0; slot < max_slot; slot++)
			{
				CItem* item = user->inventory[bag][slot];

				if (item)
				{
					user->SendItem(item, bag + 1, slot);
				}
			}
		}
	}

	void __fastcall send_add_item_from_packet(CUser* user, void* packet)
	{
		const uint8_t* data = static_cast<const uint8_t*>(packet);

		AddItemPacket response_packet{};
		std::memset(&response_packet.bag, 0, sizeof(AddItemPacket) - 2);

		response_packet.bag = read_u8(data, 2);
		response_packet.slot = read_u8(data, 3);
		response_packet.type = read_u8(data, 4);
		response_packet.type_id = read_u8(data, 5);
		response_packet.count = read_u8(data, 6);
		response_packet.quality = read_u16(data, 7);
		response_packet.gem[0] = read_u8(data, 9);
		response_packet.gem[1] = read_u8(data, 10);
		response_packet.gem[2] = read_u8(data, 11);
		response_packet.gem[3] = read_u8(data, 12);
		response_packet.gem[4] = read_u8(data, 13);
		response_packet.gem[5] = read_u8(data, 14);

		read_bytes(data, 15, &response_packet.craftname, 20);

		user->Send((void*)&response_packet, sizeof(AddItemPacket));
	}

	void __fastcall send_move_item_from_packet(CUser* user, void* packet)
	{
		const uint8_t* data = static_cast<const uint8_t*>(packet);

		MoveItemPacket response_packet{};
		std::memset(&response_packet.bag, 0, sizeof(MoveItemPacket) - 2);

		response_packet.bag = read_u8(data, 2);
		response_packet.slot = read_u8(data, 3);
		response_packet.type = read_u8(data, 4);
		response_packet.type_id = read_u8(data, 5);
		response_packet.count = read_u8(data, 6);
		response_packet.quality = read_u16(data, 7);
		response_packet.gem_first_item[0] = read_u8(data, 9);
		response_packet.gem_first_item[1] = read_u8(data, 10);
		response_packet.gem_first_item[2] = read_u8(data, 11);
		response_packet.gem_first_item[3] = read_u8(data, 12);
		response_packet.gem_first_item[4] = read_u8(data, 13);
		response_packet.gem_first_item[5] = read_u8(data, 14);

		read_bytes(data, 15, &response_packet.craftname_first_item, 20);

		response_packet.bag2 = read_u8(data, 36);
		response_packet.slot2 = read_u8(data, 37);
		response_packet.type2 = read_u8(data, 38);
		response_packet.type_id2 = read_u8(data, 39);
		response_packet.count2 = read_u8(data, 40);
		response_packet.quality2 = read_u16(data, 41);

		response_packet.gem_second_item[0] = read_u8(data, 43);
		response_packet.gem_second_item[1] = read_u8(data, 44);
		response_packet.gem_second_item[2] = read_u8(data, 45);
		response_packet.gem_second_item[3] = read_u8(data, 46);
		response_packet.gem_second_item[4] = read_u8(data, 47);
		response_packet.gem_second_item[5] = read_u8(data, 48);

		read_bytes(data, 49, &response_packet.craftname_second_item, 20);

		response_packet.gold = user->gold;

		user->Send((void*)&response_packet, sizeof(MoveItemPacket));
	}

	const uintptr_t send_character_item_return = 0x0049263D;

	// 00492500 - CUser::SendCharacterItem
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

	const uintptr_t item_get_return = 0x0046A869;

	// 0046A1E0 - CUser::ItemGet
	NAKED void item_get_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x60]
			mov ecx, edi
			call packets::items::inventory::send_add_item_from_packet
			popad
			jmp item_get_return
		}
	}

	const uintptr_t item_create_return = 0x0046C22F;

	// CUser::ItemCreate
	NAKED void item_create_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0xB4]
			mov ecx, [esp + 0x38]
			call packets::items::inventory::send_add_item_from_packet
			popad
			jmp item_create_return
		}
	}

	const uintptr_t item_bag_to_bag_return = 0x00468E64;

	// CUser::ItemBagToBag
	NAKED void item_bag_to_bag_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x54]
			mov ecx, esi
			call packets::items::inventory::send_move_item_from_packet
			popad
			jmp item_bag_to_bag_return
		}
	}

	void __fastcall drop_gold_fix(void* packet)
	{
		uint8_t* data = static_cast<uint8_t*>(packet);
		uint32_t gold = read_u32(data, 5);
		std::memset(data + 5, 0, 4);
		std::memcpy(data + 7, &gold, 4);
	}

	const uintptr_t item_get2_return = 0x0046A372;

	// 0046A1E0 - CUser::ItemGet
	NAKED void item_get2_hook()
	{
		__asm {
			pushad
			lea ecx, [esp + 0x68]
			call packets::items::inventory::drop_gold_fix
			popad

			call SConnectionSend
			jmp item_get2_return
		}
	}

	const uintptr_t item_get_money_return = 0x0046BC65;

	// 0046BBA0 - CUser::ItemGetMoney
	NAKED void item_get_money_hook()
	{
		__asm {
			pushad
			lea ecx, [esp + 0x40]
			call packets::items::inventory::drop_gold_fix
			popad

			call SConnectionSend
			jmp item_get_money_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x0049251E, send_character_item_hook, 6);
		utils::memory::hook((void*)0x0046C218, item_create_hook, 6);
		utils::memory::hook((void*)0x00468E56, item_bag_to_bag_hook, 6);
		utils::memory::hook((void*)0x0046A857, item_get_hook, 6);
		utils::memory::hook((void*)0x0046A36D, item_get2_hook, 5);
		utils::memory::hook((void*)0x0046BC60, item_get_money_hook, 5);
	}
}