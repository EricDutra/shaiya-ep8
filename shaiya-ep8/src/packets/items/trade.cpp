#include "include/packets/items/trade.h"
#include "include/packets/items/inventory.h"
#include "include/packets/packet.h"
#include "include/utils/memory.h"
#include "include/utils/buffer_reader.h"
#include <cstring>

using namespace utils::buffer_reader;

namespace packets::items::trade
{
	void send_add_item_trade(CUser* user, CItem* item, uint8_t bag, uint8_t slot)
	{
		inventory::AddItemPacket packet{};
		std::memset(&packet.bag, 0, sizeof(inventory::AddItemPacket) - 2);

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

		user->Send((void*)&packet, sizeof(inventory::AddItemPacket));
	}

	void send_receive_item(CUser* user, CItem* item, uint8_t slot)
	{
		TradeReceiveItemPacket packet{};
		std::memset(&packet.slot, 0, sizeof(TradeReceiveItemPacket) - 2);

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

		user->Send((void*)&packet, sizeof(TradeReceiveItemPacket));
	}

	void send_duel_item(CUser* user, CItem* item, uint8_t slot)
	{
		DuelItemPacket packet{};
		std::memset(&packet.slot, 0, sizeof(DuelItemPacket) - 2);

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

		user->Send((void*)&packet, sizeof(DuelItemPacket));
	}

	void __fastcall send_add_item_trade_from_packet(CUser* user, void* packet)
	{
		const uint8_t* data = static_cast<const uint8_t*>(packet);
		size_t offset = 0;

		inventory::AddItemPacket response_packet{};
		std::memset(&response_packet.bag, 0, sizeof(inventory::AddItemPacket) - 2);

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

		user->Send((void*)&response_packet, sizeof(inventory::AddItemPacket));
	}

	void __fastcall send_receive_item_from_packet(CUser* user, void* packet)
	{
		const uint8_t* data = static_cast<const uint8_t*>(packet);
		size_t offset = 0;

		TradeReceiveItemPacket response_packet{};
		std::memset(&response_packet.slot, 0, sizeof(TradeReceiveItemPacket) - 2);

		response_packet.slot = read_u8(data, 2);
		response_packet.type = read_u8(data, 3);
		response_packet.type_id = read_u8(data, 4);
		response_packet.count = read_u8(data, 5);
		response_packet.quality = read_u16(data, 6);
		response_packet.gem[0] = read_u8(data, 8);
		response_packet.gem[1] = read_u8(data, 9);
		response_packet.gem[2] = read_u8(data, 10);
		response_packet.gem[3] = read_u8(data, 11);
		response_packet.gem[4] = read_u8(data, 12);
		response_packet.gem[5] = read_u8(data, 13);

		read_bytes(data, 14, &response_packet.craftname, 20);

		user->Send((void*)&response_packet, sizeof(TradeReceiveItemPacket));
	}

	void __fastcall send_duel_item_from_packet(CUser* user, void* packet)
	{
		const uint8_t* data = static_cast<const uint8_t*>(packet);
		size_t offset = 0;

		DuelItemPacket response_packet{};
		std::memset(&response_packet.slot, 0, sizeof(DuelItemPacket) - 2);

		response_packet.slot = read_u8(data, 2);
		response_packet.type = read_u8(data, 3);
		response_packet.type_id = read_u8(data, 4);
		response_packet.count = read_u8(data, 5);
		response_packet.quality = read_u16(data, 6);
		response_packet.gem[0] = read_u8(data, 8);
		response_packet.gem[1] = read_u8(data, 9);
		response_packet.gem[2] = read_u8(data, 10);
		response_packet.gem[3] = read_u8(data, 11);
		response_packet.gem[4] = read_u8(data, 12);
		response_packet.gem[5] = read_u8(data, 13);

		read_bytes(data, 14, &response_packet.craftname, 20);

		user->Send((void*)&response_packet, sizeof(DuelItemPacket));
	}

	const uintptr_t trade_item_return = 0x0047EF7B;

	NAKED void trade_item_hook()
	{
		__asm {
			lea edx, [esp + 0xB4]
			pushad
			mov ecx, edi
			call packets::items::trade::send_add_item_trade_from_packet
			popad
			jmp trade_item_return
		}
	}

	const uintptr_t trade_receive_item_return = 0x0047DF34;

	NAKED void trade_receive_item_hook()
	{
		__asm {
			lea eax, [esp + 0x1C]
			pushad
			mov edx, eax
			mov ecx, esi
			call packets::items::trade::send_receive_item_from_packet
			popad
			jmp trade_receive_item_return
		}
	}

	const uintptr_t duel_item_return = 0x0048C753;

	NAKED void duel_item_hook()
	{
		__asm {
			pushad
			lea edx, [esp + 0x6C]
			call packets::items::trade::send_duel_item_from_packet
			popad
			add esp, 0x08
			jmp duel_item_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x0047EF6A, trade_item_hook, 9);
		utils::memory::hook((void*)0x0047DF22, trade_receive_item_hook, 6);
		utils::memory::hook((void*)0x0048C74E, duel_item_hook, 5);
	}
}
