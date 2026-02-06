#include "include/shaiya/CUser.h"
#include "include/packets/items/inventory.h"
#include "include/shaiya/DBAgent.h"
#include "include/utils/logger.h"

namespace shaiya
{
	void CUser::MoveItem(uint8_t curr_bag, uint8_t curr_slot, uint8_t dest_bag, uint8_t dest_slot)
	{
		CItem* curr_item = this->inventory[curr_bag][curr_slot];
		CItem* dest_item = this->inventory[dest_bag][dest_slot];

		if (curr_item == nullptr)
			return;

		this->inventory[dest_bag][dest_slot] = curr_item;
		this->inventory[curr_bag][curr_slot] = nullptr;

		packets::items::inventory::MoveItemPacket packet{};

		packet.opcode = packets::PacketType::MoveItem;

		packet.bag = curr_bag + 1;
		packet.slot = curr_slot;

		if (dest_item)
		{
			this->inventory[curr_bag][curr_slot] = dest_item;

			packet.type = dest_item->type;
			packet.type_id = dest_item->typeId;
			packet.count = dest_item->count;
			packet.quality = dest_item->quality;
			packet.gem_first_item[0] = dest_item->gem[0];
			packet.gem_first_item[1] = dest_item->gem[1];
			packet.gem_first_item[2] = dest_item->gem[2];
			packet.gem_first_item[3] = dest_item->gem[3];
			packet.gem_first_item[4] = dest_item->gem[4];
			packet.gem_first_item[5] = dest_item->gem[5];

			std::memcpy(&packet.craftname_first_item, &dest_item->craftname, 20);
		}

		packet.bag2 = dest_bag + 1;
		packet.slot2 = dest_slot;
		packet.type2 = curr_item->type;
		packet.type_id2 = curr_item->typeId;
		packet.count2 = curr_item->count;
		packet.quality2 = curr_item->quality;
		packet.gem_second_item[0] = curr_item->gem[0];
		packet.gem_second_item[1] = curr_item->gem[1];
		packet.gem_second_item[2] = curr_item->gem[2];
		packet.gem_second_item[3] = curr_item->gem[3];
		packet.gem_second_item[4] = curr_item->gem[4];
		packet.gem_second_item[5] = curr_item->gem[5];

		std::memcpy(&packet.craftname_second_item, &curr_item->craftname, 20);

		packet.gold = gold;

		this->Send((void*)&packet, sizeof(packets::items::inventory::MoveItemPacket));

		#pragma pack(push, 1)
		struct DBAgentMoveItemPacket
		{
			uint16_t opcode;
			uint32_t user_id;
			uint8_t current_bag;
			uint8_t current_slot;
			uint8_t current_count;
			uint8_t destination_bag;
			uint8_t destination_slot;
			uint8_t destination_count;
		};
		#pragma pack(pop)

		DBAgentMoveItemPacket db_packet{};

		db_packet.opcode = 0x0703;

		db_packet.user_id = this->userId;
		db_packet.current_bag = curr_bag + 1;
		db_packet.current_slot = curr_slot;
		db_packet.current_count = curr_item->count;
		db_packet.destination_bag = dest_bag + 1;
		db_packet.destination_slot = dest_slot;
		db_packet.destination_count = dest_item ? dest_item->count : 0;

		DBAgent::Send((void*)&db_packet, sizeof(DBAgentMoveItemPacket));
	}

	void CUser::SendItem(CItem* item, uint8_t bag, uint8_t slot)
	{
		CharacterItem character_item{};

		character_item.opcode = PacketType::CharacterItem;

		character_item.item_count = 1;
		character_item.bag = bag;
		character_item.slot = slot;
		character_item.type = item->type;
		character_item.type_id = item->typeId;
		character_item.quality = item->quality;
		character_item.is_dyed = 0;
		character_item.gem[0] = item->gem[0];
		character_item.gem[1] = item->gem[1];
		character_item.gem[2] = item->gem[2];
		character_item.gem[3] = item->gem[3];
		character_item.gem[4] = item->gem[4];
		character_item.gem[5] = item->gem[5];
		character_item.count = item->count;

		memcpy(&character_item.craftname, &item->craftname, 20);

		this->Send((void*)&character_item, sizeof(CharacterItem));
	}

	using send_fn = void(__thiscall*)(CUser* this_ptr, void* packet, size_t size);

	void CUser::Send(void* packet_ptr, size_t packet_size)
	{
		static send_fn SConnectionSend = reinterpret_cast<send_fn>(0x004ED0E0);

		SConnectionSend(this, packet_ptr, packet_size);
	}
}