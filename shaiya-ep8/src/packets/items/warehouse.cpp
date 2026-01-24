#include "include/packets/items/warehouse.h"
#include "include/utils/memory.h"
#include "include/utils/buffer_reader.h"
#include <cstring>

using namespace utils::buffer_reader;

namespace packets::items::warehouse
{
	void send_all_items(CUser* user, uint32_t unk_value, uint8_t item_count)
	{
		WarehouseAllItemsPacket packet{};
		std::memset(&packet.unk, 0, sizeof(WarehouseAllItemsPacket) - 2);

		packet.unk = unk_value;
		packet.item_count = item_count;

		for (int i = 0; i < item_count; i++)
		{
			CItem* item = user->warehouse[i];

			if (item)
			{
				packet.item[i].slot = i;
				packet.item[i].type = item->type;
				packet.item[i].type_id = item->typeId;
				packet.item[i].quality = item->quality;
				packet.item[i].gem[0] = item->gem[0];
				packet.item[i].gem[1] = item->gem[1];
				packet.item[i].gem[2] = item->gem[2];
				packet.item[i].gem[3] = item->gem[3];
				packet.item[i].gem[4] = item->gem[4];
				packet.item[i].gem[5] = item->gem[5];
				packet.item[i].count = item->count;

				std::memcpy(&packet.item[i].craftname, &item->craftname, 20);
			}
		}

		user->Send((void*)&packet, sizeof(WarehouseItem) * item_count + 7);
	}

	void send_item(CUser* user, uint32_t unk_value, CItem* item, uint8_t slot)
	{
		WarehouseItemPacket packet{};
		std::memset(&packet.unk, 0, sizeof(WarehouseItemPacket) - 2);

		packet.unk = unk_value;
		packet.slot = slot;
		packet.type = item->type;
		packet.type_id = item->typeId;
		packet.quality = item->quality;
		packet.gem[0] = item->gem[0];
		packet.gem[1] = item->gem[1];
		packet.gem[2] = item->gem[2];
		packet.gem[3] = item->gem[3];
		packet.gem[4] = item->gem[4];
		packet.gem[5] = item->gem[5];
		packet.count = item->count;

		std::memcpy(&packet.craftname, &item->craftname, 20);

		user->Send((void*)&packet, sizeof(WarehouseItemPacket));
	}

	void __fastcall send_all_items_from_buffer(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);
		size_t offset = 0;

		WarehouseAllItemsPacket warehouse_packet{};
		std::memset(&warehouse_packet.unk, 0, sizeof(WarehouseAllItemsPacket) - 2);

		offset += 2;
		uint32_t unk = read_u32(data, offset);
		offset += 4;
		uint8_t item_count = read_u8(data, offset);
		offset += 1;

		warehouse_packet.unk = unk;
		warehouse_packet.item_count = item_count;

		for (int i = 0; i < item_count; i++)
		{
			warehouse_packet.item[i].slot = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].type = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].type_id = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].quality = read_u16(data, offset);
			offset += 2;
			warehouse_packet.item[i].gem[0] = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].gem[1] = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].gem[2] = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].gem[3] = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].gem[4] = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].gem[5] = read_u8(data, offset);
			offset += 1;
			warehouse_packet.item[i].count = read_u8(data, offset);
			offset += 1;

			read_bytes(data, offset, &warehouse_packet.item[i].craftname, 20);
			offset += 20;
		}

		user->Send((void*)&warehouse_packet, sizeof(WarehouseItem) * item_count + 7);
	}

	void __fastcall send_item_from_buffer(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);
		size_t offset = 0;

		WarehouseItemPacket item_packet{};
		std::memset(&item_packet.unk, 0, sizeof(WarehouseItemPacket) - 2);

		item_packet.item_count = 1;

		offset += 2;
		item_packet.unk = read_u32(data, offset);
		offset += 4;
		offset += 1;
		item_packet.slot = read_u8(data, offset);
		offset += 1;
		item_packet.type = read_u8(data, offset);
		offset += 1;
		item_packet.type_id = read_u8(data, offset);
		offset += 1;
		item_packet.quality = read_u16(data, offset);
		offset += 2;
		item_packet.gem[0] = read_u8(data, offset);
		offset += 1;
		item_packet.gem[1] = read_u8(data, offset);
		offset += 1;
		item_packet.gem[2] = read_u8(data, offset);
		offset += 1;
		item_packet.gem[3] = read_u8(data, offset);
		offset += 1;
		item_packet.gem[4] = read_u8(data, offset);
		offset += 1;
		item_packet.gem[5] = read_u8(data, offset);
		offset += 1;
		item_packet.count = read_u8(data, offset);
		offset += 1;

		read_bytes(data, offset, &item_packet.craftname, 20);

		user->Send((void*)&item_packet, sizeof(WarehouseItemPacket));
	}

	const uintptr_t warehouse_all_items_return = 0x00492770;

	NAKED void warehouse_all_items_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x2C]
			mov ecx, ebp
			call packets::items::warehouse::send_all_items_from_buffer
			popad
			jmp warehouse_all_items_return
		}
	}

	const uintptr_t warehouse_item_return = 0x00492736;

	NAKED void warehouse_item_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x34]
			mov ecx, ebp
			call packets::items::warehouse::send_item_from_buffer
			popad
			jmp warehouse_item_return
		}
	}

	const uintptr_t move_item_inventory_to_warehouse_return = 0x00469934;

	NAKED void move_item_inventory_to_warehouse_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x40]
			mov ecx, edi
			call packets::items::warehouse::send_item_from_buffer
			popad
			jmp move_item_inventory_to_warehouse_return
		}
	}

	const uintptr_t move_item_warehouse_to_inventory_return = 0x004693D8;

	NAKED void move_item_warehouse_to_inventory_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x40]
			mov ecx, edi
			call packets::items::warehouse::send_item_from_buffer
			popad
			jmp move_item_warehouse_to_inventory_return
		}
	}

	const uintptr_t move_item_warehouse_to_warehouse_return = 0x00469BEC;

	NAKED void move_item_warehouse_to_warehouse_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x30]
			mov ecx, esi
			call packets::items::warehouse::send_item_from_buffer
			popad
			jmp move_item_warehouse_to_warehouse_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x00492763, warehouse_all_items_hook, 6);
		utils::memory::hook((void*)0x00492725, warehouse_item_hook, 5);
		utils::memory::nop((void*)0x0049271F, 2);
		utils::memory::hook((void*)0x00469926, move_item_inventory_to_warehouse_hook, 6);
		utils::memory::hook((void*)0x004693C6, move_item_warehouse_to_inventory_hook, 6);
		utils::memory::hook((void*)0x00469BDE, move_item_warehouse_to_warehouse_hook, 6);
	}
}
