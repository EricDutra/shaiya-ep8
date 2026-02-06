#include "include/packets/items/player_market.h"
#include "include/packets/packet.h"
#include "include/utils/buffer_reader.h"
#include "include/utils/memory.h"
#include <cstring>

using namespace utils::buffer_reader;

namespace packets::items::player_market
{
	void send_items(CUser* user, uint8_t item_count)
	{
		PlayerMarketItemPacket packet{};
		std::memset(&packet.item_count, 0, sizeof(PlayerMarketItemPacket) - 2);

		packet.item_count = item_count;

		user->Send((void*)&packet, sizeof(PlayerMarketItemPacket));
	}

	void send_buy_result(CUser* user, uint8_t buy_status, uint32_t gold, uint8_t market_slot, uint8_t bag, uint8_t slot, CItem* item)
	{
		BuyPlayerMarketItemPacket packet{};
		std::memset(&packet.buy_status, 0, sizeof(BuyPlayerMarketItemPacket) - 2);

		packet.buy_status = buy_status;
		packet.current_player_gold = gold;
		packet.market_item_slot = market_slot;
		packet.player_bag = bag;
		packet.player_slot = slot;
		packet.type = item->type;
		packet.type_id = item->typeId;
		packet.count = item->count;
		packet.quality = item->quality;

		for (int i = 0; i < 6; i++)
		{
			packet.gem[i] = item->gem[i];
		}

		std::memcpy(&packet.craftname, &item->craftname, 20);

		user->Send((void*)&packet, sizeof(BuyPlayerMarketItemPacket));
	}

	void __fastcall send_items_from_packet(CUser* user, void* packet)
	{
		const uint8_t* data = static_cast<const uint8_t*>(packet);
		size_t offset = 2;

		uint8_t item_count = read_u8(data, offset);
		offset += 1;

		PlayerMarketItemPacket response_packet{};
		std::memset(&response_packet.item_count, 0, sizeof(PlayerMarketItemPacket) - 2);

		response_packet.item_count = item_count;

		for (int i = 0; i < item_count; i++)
		{
			response_packet.item[i].slot = read_u8(data, offset);
			offset += 1;

			response_packet.item[i].price = read_u32(data, offset);
			offset += 4;

			response_packet.item[i].type = read_u8(data, offset);
			offset += 1;

			response_packet.item[i].type_id = read_u8(data, offset);
			offset += 1;

			response_packet.item[i].count = read_u8(data, offset);
			offset += 1;

			response_packet.item[i].quality = read_u16(data, offset);
			offset += 2;

			for (int j = 0; j < 6; j++)
			{
				response_packet.item[i].gem[j] = read_u8(data, offset);
				offset += 1;
			}

			read_bytes(data, offset, &response_packet.item[i].craftname, 20);
			offset += 20;

			offset += 1;
		}

		uint16_t packet_size = response_packet.item_count * sizeof(PlayerMarketItem);
		packet_size += 3;

		user->Send((void*)&response_packet, packet_size);
	}

	void __fastcall send_buy_result_from_packet(CUser* user, void* packet)
	{
		const uint8_t* data = static_cast<const uint8_t*>(packet);
		size_t offset = 2;

		BuyPlayerMarketItemPacket response_packet{};
		std::memset(&response_packet.buy_status, 0, sizeof(BuyPlayerMarketItemPacket) - 2);

		response_packet.buy_status = read_u8(data, offset);
		offset += 1;

		response_packet.current_player_gold = read_u32(data, offset);
		offset += 4;

		response_packet.market_item_slot = read_u8(data, offset);
		offset += 1;

		response_packet.unk = read_u8(data, offset);
		offset += 1;

		response_packet.player_bag = read_u8(data, offset);
		offset += 1;

		response_packet.player_slot = read_u8(data, offset);
		offset += 1;

		response_packet.type = read_u8(data, offset);
		offset += 1;

		response_packet.type_id = read_u8(data, offset);
		offset += 1;

		response_packet.count = read_u8(data, offset);
		offset += 1;

		response_packet.quality = read_u16(data, offset);
		offset += 2;

		for (int i = 0; i < 6; i++)
		{
			response_packet.gem[i] = read_u8(data, offset);
			offset += 1;
		}

		read_bytes(data, offset, &response_packet.craftname, 20);
		offset += 20;

		user->Send((void*)&response_packet, sizeof(BuyPlayerMarketItemPacket));
	}

	const uintptr_t player_market_items_return = 0x00487350;

	NAKED void player_market_items_hook()
	{
		__asm {
			pushad
			mov edx, eax
			call packets::items::player_market::send_items_from_packet
			popad
			add esp, 0x08
			jmp player_market_items_return
		}
	}

	const uintptr_t buy_player_market_item_return = 0x00487E93;

	NAKED void buy_player_market_item_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x88]
			call packets::items::player_market::send_buy_result_from_packet
			popad
			add esp, 0x08
			jmp buy_player_market_item_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x00487E8E, buy_player_market_item_hook, 5);
	}
}
