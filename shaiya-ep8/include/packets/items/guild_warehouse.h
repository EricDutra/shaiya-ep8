#pragma once
#include "include/shaiya/CUser.h"
#include "include/shaiya/CGuild.h"
#include "include/packets/packet.h"

using namespace shaiya;
using namespace packets;

namespace packets::items::guild_warehouse
{
#pragma pack(push, 1)

	struct GuildWarehouseAddRemoveItemPacket
	{
		PacketType opcode = PacketType::GuildWarehouseItemList;
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint16_t quality = 0;
		uint32_t gems[6];
		uint8_t count = 0;
		uint8_t unk[22];
		uint8_t dyed = 0;
		uint8_t unk2[26];
		char craftname[20];
	};

	struct GuildWarehouseFakeItemListPacket
	{
		PacketType opcode = PacketType::GuildWarehouseItemList;
		uint8_t item_count = 1;
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint16_t quality = 0;
		uint32_t gems[6];
		uint8_t count = 0;
		uint8_t unk[22];
		uint8_t dyed = 0;
		uint8_t unk2[26];
		char craftname[20];
	};

	struct GuildWarehouseOldItemUnit
	{
		uint8_t slot;
		uint8_t type;
		uint8_t type_id;
		uint16_t quality;
		uint8_t gems[6];
		uint8_t count;
		char craftname[20];
		uint8_t unk;
	};

	struct GuildWarehouseOldItemListPacket
	{
		uint16_t opcode;
		uint8_t item_count;
		GuildWarehouseOldItemUnit item_unit[240];
	};

	struct GuildWarehouseOldAddItem
	{
		uint16_t opcode;
		uint8_t slot;
		uint8_t type;
		uint8_t type_id;
		uint16_t quality;
		uint8_t gems[6];
		uint8_t count;
		char craftname[20];
		uint8_t unk;
	};

	struct UpdateUserInfoPacket
	{
		PacketType opcode = PacketType::UpdateUserInfo;
		uint8_t id = 0;
		uint32_t info = 0;
	};

#pragma pack(pop)

	void send_items(CUser* user, uint8_t item_count);
	void send_add_item(CUser* user, CItem* item, uint8_t slot);
	void send_remove_item(CUser* user, CItem* item, uint8_t slot);
	void send_add_item_to_all(CUser* user, CGuild* guild, CItem* item, uint8_t slot);
	void send_move_item(CGuild* guild, CItem* src_item, uint8_t src_bag, uint8_t src_slot, CItem* dst_item, uint8_t dst_bag, uint8_t dst_slot);
	void hook();
}
