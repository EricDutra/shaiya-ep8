#pragma once
#include "include/shaiya/CUser.h"
#include "include/packets/packet.h"

using namespace shaiya;
using namespace packets;

namespace packets::items::inventory
{
#pragma pack(push, 1)

	struct AddInventoryItemPacket
	{
		PacketType opcode = PacketType::AddInventoryItem;
		uint8_t bag = 0;
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint32_t unk = 0;
		uint32_t gem[6];
		uint8_t unk2[23];
		uint32_t is_dyed = 0;
		uint8_t unk3[23];
		char craftname[20];
	};

	struct MoveInventoryItemPacket
	{
		PacketType opcode = PacketType::MoveInventoryItem;
		uint8_t bag = 0;
		uint8_t slot = 0;
		uint8_t type = 0;
		uint8_t type_id = 0;
		uint8_t count = 0;
		uint16_t quality = 0;
		uint8_t unk[50];
		uint32_t gem_first_item[6];
		char craftname_first_item[20];
		uint8_t unk2 = 0;
		uint8_t bag2 = 0;
		uint8_t slot2 = 0;
		uint8_t type2 = 0;
		uint8_t type_id2 = 0;
		uint8_t count2 = 0;
		uint16_t quality2 = 0;
		uint8_t unk3[50];
		uint32_t gem_second_item[6];
		char craftname_second_item[20];
		uint8_t unk4 = 0;
		uint32_t gold = 0;
	};

	struct UpdateItemStatePacket
	{
		PacketType opcode = PacketType::UpdateItemState;
		uint8_t bag;
		uint8_t slot;
		uint8_t type;
		uint8_t type_id;
		uint8_t count;
	};

#pragma pack(pop)

	void send_add_item(CUser* user, uint8_t bag, uint8_t slot, CItem* item);
	void send_move_item(CUser* user, uint8_t src_bag, uint8_t src_slot, CItem* src_item, uint8_t dst_bag, uint8_t dst_slot, CItem* dst_item, uint32_t gold);
	void move_item(CUser* user, uint8_t current_bag, uint8_t current_slot, uint8_t destination_bag, uint8_t destination_slot);
	void sort_items(CUser* user);
	void send_all(CUser* user);
	void __fastcall send_add_item_from_buffer(CUser* user, void* buffer);
	void __fastcall send_move_item_from_buffer(CUser* user, void* buffer);
	void hook();
}
