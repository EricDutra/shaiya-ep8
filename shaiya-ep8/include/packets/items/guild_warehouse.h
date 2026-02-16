#pragma once
#include "include/shaiya/CUser.h"
#include "include/shaiya/CGuild.h"
#include "include/packets/packet.h"

using namespace shaiya;
using namespace packets;

namespace packets::items::guild_warehouse
{
#pragma pack(push, 1)

	struct GuildWarehouseItemPacket
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

	struct GuildWarehouseItemListPacket
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

	struct GuildWarehouseOldItem
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
		GuildWarehouseOldItem item[240];
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

#pragma pack(pop)

	//void send_items(CUser* user, uint8_t item_count);
	
	void hook();
}
