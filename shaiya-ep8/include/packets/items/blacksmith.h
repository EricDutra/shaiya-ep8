#pragma once
#include "include/shaiya/CUser.h"
#include "include/packets/packet.h"

using namespace shaiya;

namespace packets::items::blacksmith
{
#pragma pack(push, 1)

	struct EnchantResultPacket
	{
		PacketType opcode = PacketType::EnchantResult;
		uint8_t success_flag = 0;
		uint8_t lapisia_bag = 0;
		uint8_t lapisia_slot = 0;
		uint8_t lapisia_count = 0;
		uint8_t item_bag = 0;
		uint8_t item_slot = 0;
		uint32_t gold = 0;
		uint8_t unk[2] = {};
		char craftname[20] = {};
		uint8_t unk2 = 0;
	};

	struct LinkResultPacket
	{
		PacketType opcode = PacketType::LinkResult;
		uint8_t success_flag = 0;
		uint8_t lapis_bag = 0;
		uint8_t lapis_slot = 0;
		uint8_t lapis_count = 0;
		uint8_t item_bag = 0;
		uint8_t item_slot = 0;
		uint8_t can_break_equipment = 0;
		uint32_t lapis_id = 0;
		uint32_t gold = 0;
		uint8_t hammer_bag = 0;
		uint8_t hammer_slot = 0;
	};

	struct ExtractResultPacket
	{
		PacketType opcode = PacketType::ExtractResult;
		uint8_t success_flag = 0;
		uint8_t item_bag = 0;
		uint8_t item_slot = 0;
		uint8_t lapis_index = 0;
		uint8_t lapis_extracted_bag[6] = {};
		uint8_t lapis_extracted_slot[6] = {};
		uint32_t lapis_extracted_id[6] = {};
		uint8_t lapis_extracted_count[6] = {};
		uint32_t gold = 0;
	};

#pragma pack(pop)

	void send_enchant_result(CUser* user, uint8_t success_flag, uint8_t lapisia_bag, uint8_t lapisia_slot, uint8_t lapisia_count, uint8_t item_bag, uint8_t item_slot, uint32_t gold, const char* craftname);
	void send_link_result(CUser* user, uint8_t success_flag, uint8_t lapis_bag, uint8_t lapis_slot, uint8_t lapis_count, uint8_t item_bag, uint8_t item_slot, uint8_t can_break, uint32_t lapis_id, uint32_t gold, uint8_t hammer_bag, uint8_t hammer_slot);
	void send_extract_result(CUser* user, uint8_t success_flag, uint8_t item_bag, uint8_t item_slot, uint8_t lapis_index, const uint8_t* bags, const uint8_t* slots, const uint32_t* ids, const uint8_t* counts, uint32_t gold);
	void hook();
}
