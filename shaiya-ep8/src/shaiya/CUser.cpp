#include "include/shaiya/CUser.h"

namespace shaiya
{
	using send_fn = void(__thiscall*)(CUser* this_ptr, void* packet, size_t size);

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

	void CUser::Send(void* packet_ptr, size_t packet_size)
	{
		static send_fn SConnectionSend = reinterpret_cast<send_fn>(0x004ED0E0);

		SConnectionSend(this, packet_ptr, packet_size);
	}
}