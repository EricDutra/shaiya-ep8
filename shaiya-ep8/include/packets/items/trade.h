#pragma once
#include "include/shaiya/CUser.h"
#include "include/packets/packet.h"

using namespace shaiya;
using namespace packets;

namespace packets::items::trade
{
#pragma pack(push, 1)

	struct TradeReceiveItemPacket
	{
		PacketType opcode = PacketType::TradeReceiveItem;
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint32_t created_time = 0;
		uint32_t end_time = 0;
		uint8_t unk[22];
		uint8_t is_dyed = 0;
		uint8_t unk2[26];
		uint32_t gem[6];
		char craftname[20];
	};

	struct DuelItemPacket
	{
		PacketType opcode = PacketType::DuelItem;
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint32_t created_time = 0;
		uint32_t end_time = 0;
		uint8_t unk[22];
		uint8_t is_dyed = 0;
		uint8_t unk2[26];
		uint32_t gem[6];
		char craftname[20];
	};

#pragma pack(pop)

	void send_add_item_trade(CUser* user, CItem* item, uint8_t bag, uint8_t slot);
	void send_receive_item(CUser* user, CItem* item, uint8_t slot);
	void send_duel_item(CUser* user, CItem* item, uint8_t slot);
	void hook();
}
