#pragma once
#include "include/shaiya/CUser.h"
#include "include/packets/packet.h"

using namespace shaiya;

namespace packets::items::warehouse
{
#pragma pack(push, 1)

	struct WarehouseItem
	{
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint16_t quality = 0;
		uint32_t gem[6];
		uint8_t count = 0;
		uint8_t unk[57];
		char craftname[20];
		uint8_t unk2 = 0;
	};

	struct WarehouseAllItemsPacket
	{
		PacketType opcode = PacketType::WarehouseItems;
		uint32_t unk = 0;
		uint8_t item_count = 0;
		WarehouseItem item[240];
	};

	struct WarehouseItemPacket
	{
		PacketType opcode = PacketType::WarehouseItems;
		uint32_t unk = 0;
		uint8_t item_count = 1;
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint16_t quality = 0;
		uint32_t gem[6];
		uint8_t count = 0;
		uint8_t unk2[57];
		char craftname[20];
		uint8_t unk3 = 0;
	};

#pragma pack(pop)

	void send_all_items(CUser* user, uint32_t unk_value, uint8_t item_count);
	void send_item(CUser* user, uint32_t unk_value, CItem* item, uint8_t slot);
	void hook();
}
