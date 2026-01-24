#include "include/packets/items/guild_warehouse.h"
#include "include/packets/items/inventory.h"
#include "include/packets/packet.h"
#include "include/utils/buffer_reader.h"
#include "include/utils/memory.h"
#include <cstring>

using namespace utils::buffer_reader;

namespace packets::items::guild_warehouse
{
	void send_items(CUser* user, uint8_t item_count)
	{
		CGuild* guild = user->guild;
		if (!guild) return;

		for (int i = 0; i < item_count; i++)
		{
			CItem* item = guild->deposit_item[i];
			if (!item) continue;

			GuildWarehouseFakeItemListPacket packet{};
			std::memset(&packet, 0, sizeof(GuildWarehouseAddRemoveItemPacket));

			packet.opcode = PacketType::GuildWarehouseItemList;
			packet.item_count = 1;
			packet.slot = i;
			packet.type = item->type;
			packet.type_id = item->typeId;
			packet.count = item->count;
			packet.quality = item->quality;

			for (int y = 0; y < 6; y++)
			{
				packet.gems[y] = item->gem[y];
			}

			std::memcpy(&packet.craftname, &item->craftname, 20);

			user->Send((void*)&packet, sizeof(GuildWarehouseFakeItemListPacket));
		}
	}

	void send_add_item(CUser* user, CItem* item, uint8_t slot)
	{
		GuildWarehouseAddRemoveItemPacket packet{};
		std::memset(&packet, 0, sizeof(GuildWarehouseAddRemoveItemPacket));

		packet.opcode = PacketType::GuildWarehouseAddItem;
		packet.slot = slot;
		packet.type = item->type;
		packet.type_id = item->typeId;
		packet.quality = item->quality;
		packet.count = item->count;

		for (int i = 0; i < 6; i++)
		{
			packet.gems[i] = item->gem[i];
		}

		std::memcpy(&packet.craftname, &item->craftname, 20);

		user->Send((void*)&packet, sizeof(GuildWarehouseAddRemoveItemPacket));
	}

	void send_remove_item(CUser* user, CItem* item, uint8_t slot)
	{
		GuildWarehouseAddRemoveItemPacket guild_packet{};
		std::memset(&guild_packet, 0, sizeof(GuildWarehouseAddRemoveItemPacket));

		guild_packet.opcode = PacketType::GuildWarehouseRemoveItem;
		guild_packet.slot = slot;
		guild_packet.type = item->type;
		guild_packet.type_id = item->typeId;
		guild_packet.quality = item->quality;

		std::memcpy(&guild_packet.craftname, &item->craftname, 20);

		user->Send((void*)&guild_packet, sizeof(GuildWarehouseAddRemoveItemPacket));

		inventory::MoveInventoryItemPacket move_packet{};
		std::memset(&move_packet.bag, 0, sizeof(inventory::MoveInventoryItemPacket) - 2);

		move_packet.bag = slot;
		move_packet.slot = slot;
		move_packet.type = item->type;
		move_packet.type_id = item->typeId;
		move_packet.count = item->count;
		move_packet.quality = item->quality;
		move_packet.gem_first_item[0] = item->gem[0];
		move_packet.gem_first_item[1] = item->gem[1];
		move_packet.gem_first_item[2] = item->gem[2];
		move_packet.gem_first_item[3] = item->gem[3];
		move_packet.gem_first_item[4] = item->gem[4];
		move_packet.gem_first_item[5] = item->gem[5];

		std::memcpy(&move_packet.craftname_first_item, &item->craftname, 20);

		move_packet.gold = user->gold;
		move_packet.bag--;

		user->Send((void*)&move_packet, sizeof(inventory::MoveInventoryItemPacket));

		UpdateUserInfoPacket user_info_packet{};
		user_info_packet.id = 2;
		user_info_packet.info = user->gold;
		user->Send((void*)&user_info_packet, sizeof(UpdateUserInfoPacket));
	}

	void send_add_item_to_all(CUser* user, CGuild* guild, CItem* item, uint8_t slot)
	{
		const int max_online_users = 1000;

		for (int i = 0; i < max_online_users; i++)
		{
			/*
			if (World::users.user[i] == nullptr) continue;

			CUser* user_receive = World::users.user[i];

			if (user_receive == user) continue;

			CGuild* user_receive_guild = user_receive->guild;

			if (user_receive_guild != nullptr && user_receive_guild == guild)
			{
				GuildWarehouseAddRemoveItemPacket add_item_packet{};
				std::memset(&add_item_packet, 0, sizeof(GuildWarehouseAddRemoveItemPacket));

				add_item_packet.opcode = PacketType::GuildWarehouseAddItem;
				add_item_packet.slot = slot;
				add_item_packet.type = item->type;
				add_item_packet.type_id = item->typeId;
				add_item_packet.quality = item->quality;
				add_item_packet.count = item->count;

				for (int y = 0; y < 6; y++)
				{
					add_item_packet.gems[y] = item->gem[y];
				}

				std::memcpy(&add_item_packet.craftname, &item->craftname, 20);

				user_receive->Send((void*)&add_item_packet, sizeof(GuildWarehouseAddRemoveItemPacket));
			}
			*/
		}
	}

	void send_move_item(CGuild* guild, CItem* src_item, uint8_t src_bag, uint8_t src_slot, CItem* dst_item, uint8_t dst_bag, uint8_t dst_slot)
	{
		inventory::MoveInventoryItemPacket move_packet{};
		std::memset(&move_packet.bag, 0, sizeof(inventory::MoveInventoryItemPacket) - 2);

		move_packet.bag = src_bag;
		move_packet.slot = src_slot;
		move_packet.type = src_item->type;
		move_packet.type_id = src_item->typeId;
		move_packet.count = src_item->count;
		move_packet.quality = src_item->quality;
		move_packet.gem_first_item[0] = src_item->gem[0];
		move_packet.gem_first_item[1] = src_item->gem[1];
		move_packet.gem_first_item[2] = src_item->gem[2];
		move_packet.gem_first_item[3] = src_item->gem[3];
		move_packet.gem_first_item[4] = src_item->gem[4];
		move_packet.gem_first_item[5] = src_item->gem[5];

		std::memcpy(&move_packet.craftname_first_item, &src_item->craftname, 20);

		move_packet.bag2 = dst_bag;
		move_packet.slot2 = dst_slot;
		move_packet.type2 = dst_item->type;
		move_packet.type_id2 = dst_item->typeId;
		move_packet.count2 = dst_item->count;
		move_packet.quality2 = dst_item->quality;

		move_packet.gem_second_item[0] = dst_item->gem[0];
		move_packet.gem_second_item[1] = dst_item->gem[1];
		move_packet.gem_second_item[2] = dst_item->gem[2];
		move_packet.gem_second_item[3] = dst_item->gem[3];
		move_packet.gem_second_item[4] = dst_item->gem[4];
		move_packet.gem_second_item[5] = dst_item->gem[5];

		std::memcpy(&move_packet.craftname_second_item, &dst_item->craftname, 20);

		/*
		World::SendPacketGuild(guild, (uint32_t)&move_packet, sizeof(inventory::MoveInventoryItemPacket));
		*/
	}

	void __fastcall send_items_from_old_packet(CUser* user, GuildWarehouseOldItemListPacket* packet)
	{
		uint8_t item_count = packet->item_count;

		for (int i = 0; i < item_count; i++)
		{
			GuildWarehouseFakeItemListPacket new_packet{};
			std::memset(&new_packet, 0, sizeof(GuildWarehouseAddRemoveItemPacket));

			new_packet.opcode = PacketType::GuildWarehouseItemList;
			new_packet.item_count = 1;

			new_packet.slot = packet->item_unit[i].slot;
			new_packet.type = packet->item_unit[i].type;
			new_packet.type_id = packet->item_unit[i].type_id;
			new_packet.count = packet->item_unit[i].count;
			new_packet.quality = packet->item_unit[i].quality;

			for (int y = 0; y < 6; y++)
			{
				new_packet.gems[y] = packet->item_unit[i].gems[y];
			}

			std::memcpy(&new_packet.craftname, &packet->item_unit[i].craftname, 20);

			user->Send((void*)&new_packet, sizeof(GuildWarehouseFakeItemListPacket));
		}
	}

	void __fastcall send_add_item_to_all_from_old_packet(CUser* user, CGuild* guild, GuildWarehouseOldAddItem* packet)
	{
		const int max_online_users = 1000;

		for (int i = 0; i < max_online_users; i++)
		{
			/*
			if (World::users.user[i] == nullptr) continue;

			CUser* user_receive = World::users.user[i];

			if (user_receive == user) continue;

			CGuild* user_receive_guild = user_receive->guild;

			if (user_receive_guild != nullptr && user_receive_guild == guild)
			{
				GuildWarehouseAddRemoveItemPacket add_item_packet{};
				std::memset(&add_item_packet, 0, sizeof(GuildWarehouseAddRemoveItemPacket));

				add_item_packet.opcode = PacketType::GuildWarehouseAddItem;
				add_item_packet.slot = packet->slot;
				add_item_packet.type = packet->type;
				add_item_packet.type_id = packet->type_id;
				add_item_packet.quality = packet->quality;
				add_item_packet.count = packet->count;

				for (int y = 0; y < 6; y++)
				{
					add_item_packet.gems[y] = packet->gems[y];
				}

				std::memcpy(&add_item_packet.craftname, &packet->craftname, 20);

				user_receive->Send((void*)&add_item_packet, sizeof(GuildWarehouseAddRemoveItemPacket));
			}
			*/
		}
	}

	void __fastcall send_move_item_from_old_packet(CGuild* guild, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);
		size_t offset = 0;

		inventory::MoveInventoryItemPacket move_packet{};
		std::memset(&move_packet.bag, 0, sizeof(inventory::MoveInventoryItemPacket) - 2);

		offset = 2;
		move_packet.bag = read_u8(data, offset);
		move_packet.slot = read_u8(data, offset);
		move_packet.type = read_u8(data, offset);
		move_packet.type_id = read_u8(data, offset);
		move_packet.count = read_u8(data, offset);
		move_packet.quality = read_u16(data, offset);
		offset = 9;
		move_packet.gem_first_item[0] = read_u8(data, offset);
		move_packet.gem_first_item[1] = read_u8(data, offset);
		move_packet.gem_first_item[2] = read_u8(data, offset);
		move_packet.gem_first_item[3] = read_u8(data, offset);
		move_packet.gem_first_item[4] = read_u8(data, offset);
		move_packet.gem_first_item[5] = read_u8(data, offset);

		read_bytes(data, offset, &move_packet.craftname_first_item, 20);

		offset = 36;
		move_packet.bag2 = read_u8(data, offset);
		move_packet.slot2 = read_u8(data, offset);
		move_packet.type2 = read_u8(data, offset);
		move_packet.type_id2 = read_u8(data, offset);
		move_packet.count2 = read_u8(data, offset);
		move_packet.quality2 = read_u16(data, offset);

		offset = 43;
		move_packet.gem_second_item[0] = read_u8(data, offset);
		move_packet.gem_second_item[1] = read_u8(data, offset);
		move_packet.gem_second_item[2] = read_u8(data, offset);
		move_packet.gem_second_item[3] = read_u8(data, offset);
		move_packet.gem_second_item[4] = read_u8(data, offset);
		move_packet.gem_second_item[5] = read_u8(data, offset);

		read_bytes(data, offset, &move_packet.craftname_second_item, 20);

		/*
		World::SendPacketGuild(guild, (uint32_t)&move_packet, sizeof(inventory::MoveInventoryItemPacket));
		*/
	}

	void __fastcall send_remove_item_from_old_packet(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);
		size_t offset = 0;

		GuildWarehouseAddRemoveItemPacket guild_packet{};
		std::memset(&guild_packet, 0, sizeof(GuildWarehouseAddRemoveItemPacket));

		guild_packet.opcode = PacketType::GuildWarehouseRemoveItem;
		offset = 3;
		guild_packet.slot = read_u8(data, offset);
		guild_packet.type = read_u8(data, offset);
		guild_packet.type_id = read_u8(data, offset);
		offset = 7;
		guild_packet.quality = read_u16(data, offset);

		offset = 15;
		read_bytes(data, offset, &guild_packet.craftname, 20);

		user->Send((void*)&guild_packet, sizeof(GuildWarehouseAddRemoveItemPacket));

		inventory::MoveInventoryItemPacket move_packet{};
		std::memset(&move_packet.bag, 0, sizeof(inventory::MoveInventoryItemPacket) - 2);

		offset = 2;
		move_packet.bag = read_u8(data, offset);
		move_packet.slot = read_u8(data, offset);
		move_packet.type = read_u8(data, offset);
		move_packet.type_id = read_u8(data, offset);
		move_packet.count = read_u8(data, offset);
		move_packet.quality = read_u16(data, offset);
		offset = 9;
		move_packet.gem_first_item[0] = read_u8(data, offset);
		move_packet.gem_first_item[1] = read_u8(data, offset);
		move_packet.gem_first_item[2] = read_u8(data, offset);
		move_packet.gem_first_item[3] = read_u8(data, offset);
		move_packet.gem_first_item[4] = read_u8(data, offset);
		move_packet.gem_first_item[5] = read_u8(data, offset);

		read_bytes(data, offset, &move_packet.craftname_first_item, 20);

		offset = 36;
		move_packet.bag2 = read_u8(data, offset);
		move_packet.slot2 = read_u8(data, offset);
		move_packet.type2 = read_u8(data, offset);
		move_packet.type_id2 = read_u8(data, offset);
		move_packet.count2 = read_u8(data, offset);
		move_packet.quality2 = read_u16(data, offset);

		offset = 43;
		move_packet.gem_second_item[0] = read_u8(data, offset);
		move_packet.gem_second_item[1] = read_u8(data, offset);
		move_packet.gem_second_item[2] = read_u8(data, offset);
		move_packet.gem_second_item[3] = read_u8(data, offset);
		move_packet.gem_second_item[4] = read_u8(data, offset);
		move_packet.gem_second_item[5] = read_u8(data, offset);

		read_bytes(data, offset, &move_packet.craftname_second_item, 20);

		move_packet.gold = user->gold;
		move_packet.bag--;

		user->Send((void*)&move_packet, sizeof(inventory::MoveInventoryItemPacket));

		UpdateUserInfoPacket user_info_packet{};
		user_info_packet.id = 2;
		user_info_packet.info = user->gold;
		user->Send((void*)&user_info_packet, sizeof(UpdateUserInfoPacket));
	}

	void __fastcall send_add_item_to_guild_from_old_packet(CUser* user, void* buffer)
	{
		inventory::send_move_item_from_buffer(user, buffer);
	}

	const uintptr_t add_item_to_guild_return = 0x004357D5;

	NAKED void add_item_to_guild_hook()
	{
		__asm {
			pushad
			call packets::items::guild_warehouse::send_add_item_to_guild_from_old_packet
			popad
			add esp, 0x08
			jmp add_item_to_guild_return
		}
	}

	const uintptr_t move_item_guild_return = 0x00435B95;

	NAKED void move_item_guild_hook()
	{
		__asm {
			pushad
			mov edx, ecx
			mov ecx, esi
			call packets::items::guild_warehouse::send_move_item_from_old_packet
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
			call packets::items::guild_warehouse::send_remove_item_from_old_packet
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
			call packets::items::guild_warehouse::send_items_from_old_packet
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
			call packets::items::guild_warehouse::send_items_from_old_packet
			popad
			add esp, 0x08
			jmp item_list_guild2_return
		}
	}

	const uintptr_t send_all_add_item_guild_return = 0x004357AB;

	NAKED void send_all_add_item_guild_hook()
	{
		__asm {
			pushad
			push eax
			mov edx, ebp
			mov ecx, edi
			call packets::items::guild_warehouse::send_add_item_to_all_from_old_packet
			popad
			add esp, 0x08
			jmp send_all_add_item_guild_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x004357D0, add_item_to_guild_hook, 5);
		utils::memory::hook((void*)0x00435B90, move_item_guild_hook, 5);
		utils::memory::hook((void*)0x00436332, remove_item_guild_hook, 5);
		utils::memory::hook((void*)0x0043508F, item_list_guild_hook, 5);
		utils::memory::hook((void*)0x00435050, item_list_guild2_hook, 5);
		utils::memory::hook((void*)0x004357A6, send_all_add_item_guild_hook, 5);
	}
}
