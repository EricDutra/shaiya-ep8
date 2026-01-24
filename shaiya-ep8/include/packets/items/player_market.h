#pragma once
#include "include/shaiya/CUser.h"
#include "include/packets/packet.h"

using namespace shaiya;

namespace packets::items::player_market
{
#pragma pack(push, 1)

	struct PlayerMarketItem
	{
		uint8_t slot = 0;
		uint32_t price = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint32_t created_time = 0;
		uint32_t end_time = 0;
		uint8_t unk[49];
		uint32_t gem[6];
		char craftname[20];
		uint8_t unk2 = 0;
	};

	struct OldPlayerMarketItem
	{
		uint8_t slot = 0;
		uint32_t price = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint8_t gem[6];
		char craftname[20];
		uint8_t unk = 0;
	};

	struct PlayerMarketItemPacket
	{
		PacketType opcode = PacketType::PlayerMarketItems;
		uint8_t item_count = 0;
		PlayerMarketItem item[20];
	};

	struct OldPlayerMarketItemPacket
	{
		PacketType opcode = PacketType::PlayerMarketItems;
		uint8_t item_count = 0;
		OldPlayerMarketItem item[20];
	};

	struct BuyPlayerMarketItemPacket
	{
		PacketType opcode = PacketType::BuyPlayerMarketItem;
		uint8_t buy_status = 0;
		uint32_t current_player_gold = 0;
		uint8_t market_item_slot = 0;
		uint8_t unk = 0;
		uint8_t player_bag = 0;
		uint8_t player_slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint32_t gem[6];
		char craftname[20];
		uint8_t unk2 = 0;
	};

	struct OldBuyPlayerMarketItemPacket
	{
		PacketType opcode = PacketType::BuyPlayerMarketItem;
		uint8_t buy_status = 0;
		uint32_t current_player_gold = 0;
		uint8_t market_item_slot = 0;
		uint8_t unk = 0;
		uint8_t player_bag = 0;
		uint8_t player_slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint8_t gem[6];
		char craftname[20];
		uint8_t unk2 = 0;
	};

#pragma pack(pop)

	void send_items(CUser* user, uint8_t item_count);
	void send_buy_result(CUser* user, uint8_t buy_status, uint32_t gold, uint8_t market_slot, uint8_t bag, uint8_t slot, CItem* item);
	void hook();
}
