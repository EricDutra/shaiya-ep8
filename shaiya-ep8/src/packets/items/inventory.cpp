#include "include/packets/items/inventory.h"
#include "include/utils/memory.h"
#include "include/utils/buffer_reader.h"
#include <cstring>

using namespace utils::buffer_reader;

namespace packets::items::inventory
{
	void send_add_item(CUser* user, uint8_t bag, uint8_t slot, CItem* item)
	{
		AddInventoryItemPacket packet{};
		std::memset(&packet.bag, 0, sizeof(AddInventoryItemPacket) - 2);

		packet.bag = bag;
		packet.slot = slot;
		packet.type = item->type;
		packet.type_id = item->typeId;
		packet.count = item->count;
		packet.quality = item->quality;
		packet.gem[0] = item->gem[0];
		packet.gem[1] = item->gem[1];
		packet.gem[2] = item->gem[2];
		packet.gem[3] = item->gem[3];
		packet.gem[4] = item->gem[4];
		packet.gem[5] = item->gem[5];

		std::memcpy(&packet.craftname, &item->craftname, 20);

		user->Send((void*)&packet, sizeof(AddInventoryItemPacket));
	}

	void send_move_item(CUser* user, uint8_t src_bag, uint8_t src_slot, CItem* src_item, uint8_t dst_bag, uint8_t dst_slot, CItem* dst_item, uint32_t gold)
	{
		MoveInventoryItemPacket packet{};
		std::memset(&packet.bag, 0, sizeof(MoveInventoryItemPacket) - 2);

		packet.bag = src_bag;
		packet.slot = src_slot;

		if (dst_item != nullptr)
		{
			packet.type = dst_item->type;
			packet.type_id = dst_item->typeId;
			packet.count = dst_item->count;
			packet.quality = dst_item->quality;
			packet.gem_first_item[0] = dst_item->gem[0];
			packet.gem_first_item[1] = dst_item->gem[1];
			packet.gem_first_item[2] = dst_item->gem[2];
			packet.gem_first_item[3] = dst_item->gem[3];
			packet.gem_first_item[4] = dst_item->gem[4];
			packet.gem_first_item[5] = dst_item->gem[5];

			std::memcpy(&packet.craftname_first_item, &dst_item->craftname, 20);
		}

		packet.bag2 = dst_bag;
		packet.slot2 = dst_slot;
		packet.type2 = src_item->type;
		packet.type_id2 = src_item->typeId;
		packet.count2 = src_item->count;
		packet.quality2 = src_item->quality;
		packet.gem_second_item[0] = src_item->gem[0];
		packet.gem_second_item[1] = src_item->gem[1];
		packet.gem_second_item[2] = src_item->gem[2];
		packet.gem_second_item[3] = src_item->gem[3];
		packet.gem_second_item[4] = src_item->gem[4];
		packet.gem_second_item[5] = src_item->gem[5];

		std::memcpy(&packet.craftname_second_item, &src_item->craftname, 20);

		packet.gold = gold;

		user->Send((void*)&packet, sizeof(MoveInventoryItemPacket));
	}

	void move_item(CUser* user, uint8_t current_bag, uint8_t current_slot, uint8_t destination_bag, uint8_t destination_slot)
	{
		CItem* item_at_current_slot = user->inventory[current_bag][current_slot];
		CItem* item_at_destination_slot = user->inventory[destination_bag][destination_slot];

		if (item_at_current_slot == nullptr) return;

		user->inventory[destination_bag][destination_slot] = item_at_current_slot;
		user->inventory[current_bag][current_slot] = nullptr;

		if (item_at_destination_slot != nullptr)
		{
			user->inventory[current_bag][current_slot] = item_at_destination_slot;
		}

		send_move_item(user, current_bag + 1, current_slot, item_at_current_slot, destination_bag + 1, destination_slot, item_at_destination_slot, user->gold);

		/*
		struct db_agent_move_item_inventory
		{
			uint32_t user_id;
			uint8_t destination_bag;
			uint8_t destination_slot;
			uint8_t current_bag;
			uint8_t current_slot;
			uint8_t current_count;
			uint8_t destination_count;
		};

		db_agent_move_item_inventory db_packet;
		db_packet.user_id = user->userId;
		db_packet.destination_bag = destination_bag + 1;
		db_packet.destination_slot = destination_slot;
		db_packet.current_bag = current_bag + 1;
		db_packet.current_slot = current_slot;
		db_packet.current_count = item_at_current_slot->count;
		db_packet.destination_count = item_at_destination_slot ? item_at_destination_slot->count : 0;
		DBAgent::Send((uint32_t)&db_packet, sizeof(db_agent_move_item_inventory));
		*/
	}

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

		for (uint8_t bag = 0; bag < 5; bag++)
		{
			for (uint8_t slot = 0; slot < 24; slot++)
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
				move_item(user, items[i].bag, items[i].slot, target_bag, target_slot);

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
			if (target_slot >= 24)
			{
				target_slot = 0;
				target_bag++;
			}
		}
	}

	void send_all(CUser* user)
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

	void __fastcall send_add_item_from_buffer(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);

		AddInventoryItemPacket packet{};
		std::memset(&packet.bag, 0, sizeof(AddInventoryItemPacket) - 2);

		packet.bag = read_u8(data, 2);
		packet.slot = read_u8(data, 3);
		packet.type = read_u8(data, 4);
		packet.type_id = read_u8(data, 5);
		packet.count = read_u8(data, 6);
		packet.quality = read_u16(data, 7);
		packet.gem[0] = read_u8(data, 9);
		packet.gem[1] = read_u8(data, 10);
		packet.gem[2] = read_u8(data, 11);
		packet.gem[3] = read_u8(data, 12);
		packet.gem[4] = read_u8(data, 13);
		packet.gem[5] = read_u8(data, 14);

		read_bytes(data, 15, &packet.craftname, 20);

		user->Send((void*)&packet, sizeof(AddInventoryItemPacket));
	}

	void __fastcall send_move_item_from_buffer(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);

		MoveInventoryItemPacket packet{};
		std::memset(&packet.bag, 0, sizeof(MoveInventoryItemPacket) - 2);

		packet.bag = read_u8(data, 2);
		packet.slot = read_u8(data, 3);
		packet.type = read_u8(data, 4);
		packet.type_id = read_u8(data, 5);
		packet.count = read_u8(data, 6);
		packet.quality = read_u16(data, 7);
		packet.gem_first_item[0] = read_u8(data, 9);
		packet.gem_first_item[1] = read_u8(data, 10);
		packet.gem_first_item[2] = read_u8(data, 11);
		packet.gem_first_item[3] = read_u8(data, 12);
		packet.gem_first_item[4] = read_u8(data, 13);
		packet.gem_first_item[5] = read_u8(data, 14);

		read_bytes(data, 15, &packet.craftname_first_item, 20);

		packet.bag2 = read_u8(data, 36);
		packet.slot2 = read_u8(data, 37);
		packet.type2 = read_u8(data, 38);
		packet.type_id2 = read_u8(data, 39);
		packet.count2 = read_u8(data, 40);
		packet.quality2 = read_u16(data, 41);

		packet.gem_second_item[0] = read_u8(data, 43);
		packet.gem_second_item[1] = read_u8(data, 44);
		packet.gem_second_item[2] = read_u8(data, 45);
		packet.gem_second_item[3] = read_u8(data, 46);
		packet.gem_second_item[4] = read_u8(data, 47);
		packet.gem_second_item[5] = read_u8(data, 48);

		read_bytes(data, 49, &packet.craftname_second_item, 20);

		packet.gold = user->gold;

		user->Send((void*)&packet, sizeof(MoveInventoryItemPacket));
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

	const uintptr_t add_item_drop_return = 0x0046A869;

	NAKED void add_item_drop_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x60]
			mov ecx, edi
			call packets::items::inventory::send_add_item_from_buffer
			popad
			jmp add_item_drop_return
		}
	}

	const uintptr_t add_item_gm_return = 0x0046C22F;

	NAKED void add_item_gm_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0xB4]
			mov ecx, [esp + 0x38]
			call packets::items::inventory::send_add_item_from_buffer
			popad
			jmp add_item_gm_return
		}
	}

	const uintptr_t move_item_inventory_return = 0x00468E64;

	NAKED void move_item_inventory_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x54]
			mov ecx, esi
			call packets::items::inventory::send_move_item_from_buffer
			popad
			jmp move_item_inventory_return
		}
	}

	void __fastcall drop_gold_fix(void* buffer)
	{
		uint8_t* data = static_cast<uint8_t*>(buffer);
		uint32_t gold = read_u32(data, 5);
		std::memset(data + 5, 0, 4);
		std::memcpy(data + 7, &gold, 4);
	}

	const uintptr_t original_user_send = 0x004ED0E0;
	const uintptr_t drop_gold_return = 0x0046A372;

	NAKED void drop_gold_hook()
	{
		__asm {
			pushad
			lea ecx, [esp + 0x68]
			call packets::items::inventory::drop_gold_fix
			popad

			call original_user_send
			jmp drop_gold_return
		}
	}

	const uintptr_t drop_gold_b_return = 0x0046BC65;

	NAKED void drop_gold_b_hook()
	{
		__asm {
			pushad
			lea ecx, [esp + 0x40]
			call packets::items::inventory::drop_gold_fix
			popad

			call original_user_send
			jmp drop_gold_b_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x0049251E, send_character_item_hook, 6);
		utils::memory::hook((void*)0x0046A857, add_item_drop_hook, 6);
		utils::memory::hook((void*)0x0046C218, add_item_gm_hook, 6);
		utils::memory::hook((void*)0x00468E56, move_item_inventory_hook, 6);
		utils::memory::hook((void*)0x0046A36D, drop_gold_hook, 5);
		utils::memory::hook((void*)0x0046BC60, drop_gold_b_hook, 5);
	}
}
