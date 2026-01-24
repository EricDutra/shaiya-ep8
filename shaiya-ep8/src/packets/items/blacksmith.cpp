#include "include/packets/items/blacksmith.h"
#include "include/packets/packet.h"
#include "include/utils/buffer_reader.h"
#include "include/utils/memory.h"
#include <cstring>

using namespace utils::buffer_reader;

namespace packets::items::blacksmith
{
	void send_enchant_result(CUser* user, uint8_t success_flag, uint8_t lapisia_bag, uint8_t lapisia_slot, uint8_t lapisia_count, uint8_t item_bag, uint8_t item_slot, uint32_t gold, const char* craftname)
	{
		EnchantResultPacket packet{};
		std::memset(&packet.success_flag, 0, sizeof(EnchantResultPacket) - 2);

		packet.success_flag = success_flag;
		packet.lapisia_bag = lapisia_bag;
		packet.lapisia_slot = lapisia_slot;
		packet.lapisia_count = lapisia_count;
		packet.item_bag = item_bag;
		packet.item_slot = item_slot;
		packet.gold = gold;

		std::memcpy(&packet.craftname, craftname, 20);

		user->Send((void*)&packet, sizeof(EnchantResultPacket));
	}

	void send_link_result(CUser* user, uint8_t success_flag, uint8_t lapis_bag, uint8_t lapis_slot, uint8_t lapis_count, uint8_t item_bag, uint8_t item_slot, uint8_t can_break, uint32_t lapis_id, uint32_t gold, uint8_t hammer_bag, uint8_t hammer_slot)
	{
		LinkResultPacket packet{};
		std::memset(&packet.success_flag, 0, sizeof(LinkResultPacket) - 2);

		packet.success_flag = success_flag;
		packet.lapis_bag = lapis_bag;
		packet.lapis_slot = lapis_slot;
		packet.lapis_count = lapis_count;
		packet.item_bag = item_bag;
		packet.item_slot = item_slot;
		packet.can_break_equipment = can_break;
		packet.lapis_id = lapis_id;
		packet.gold = gold;
		packet.hammer_bag = hammer_bag;
		packet.hammer_slot = hammer_slot;

		user->Send((void*)&packet, sizeof(LinkResultPacket));
	}

	void send_extract_result(CUser* user, uint8_t success_flag, uint8_t item_bag, uint8_t item_slot, uint8_t lapis_index, const uint8_t* bags, const uint8_t* slots, const uint32_t* ids, const uint8_t* counts, uint32_t gold)
	{
		ExtractResultPacket packet{};
		std::memset(&packet.success_flag, 0, sizeof(ExtractResultPacket) - 2);

		packet.success_flag = success_flag;
		packet.item_bag = item_bag;
		packet.item_slot = item_slot;
		packet.lapis_index = lapis_index;

		for (int i = 0; i < 6; i++)
		{
			packet.lapis_extracted_bag[i] = bags[i];
			packet.lapis_extracted_slot[i] = slots[i];
			packet.lapis_extracted_id[i] = ids[i];
			packet.lapis_extracted_count[i] = counts[i];
		}

		packet.gold = gold;

		user->Send((void*)&packet, sizeof(ExtractResultPacket));
	}

	void __fastcall send_enchant_result_from_old_packet(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);
		size_t offset = 0;

		EnchantResultPacket enchant_packet{};
		std::memset(&enchant_packet.success_flag, 0, sizeof(EnchantResultPacket) - 2);

		enchant_packet.success_flag = read_u8(data, 2);
		enchant_packet.lapisia_bag = read_u8(data, 3);
		enchant_packet.lapisia_slot = read_u8(data, 4);
		enchant_packet.lapisia_count = read_u8(data, 5);
		enchant_packet.item_bag = read_u8(data, 9);
		enchant_packet.item_slot = read_u8(data, 10);
		enchant_packet.gold = read_u32(data, 11);

		read_bytes(data, 15, &enchant_packet.craftname, 20);

		user->Send((void*)&enchant_packet, sizeof(EnchantResultPacket));
	}

	void __fastcall send_link_result_from_old_packet(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);
		size_t offset = 0;

		LinkResultPacket link_packet{};
		std::memset(&link_packet.success_flag, 0, sizeof(LinkResultPacket) - 2);

		link_packet.success_flag = read_u8(data, 2);
		link_packet.lapis_bag = read_u8(data, 3);
		link_packet.lapis_slot = read_u8(data, 4);
		link_packet.lapis_count = read_u8(data, 5);
		link_packet.item_bag = read_u8(data, 6);
		link_packet.item_slot = read_u8(data, 7);
		link_packet.can_break_equipment = read_u8(data, 8);
		link_packet.lapis_id = read_u8(data, 9);
		link_packet.gold = read_u32(data, 14);
		link_packet.hammer_bag = read_u8(data, 18);
		link_packet.hammer_slot = read_u8(data, 19);

		user->Send((void*)&link_packet, sizeof(LinkResultPacket));
	}

	void __fastcall send_extract_result_from_old_packet(CUser* user, void* buffer)
	{
		const uint8_t* data = static_cast<const uint8_t*>(buffer);
		size_t offset = 0;

		ExtractResultPacket extract_packet{};
		std::memset(&extract_packet.success_flag, 0, sizeof(ExtractResultPacket) - 2);

		extract_packet.success_flag = read_u8(data, 2);
		extract_packet.item_bag = read_u8(data, 3);
		extract_packet.item_slot = read_u8(data, 4);
		extract_packet.lapis_index = read_u8(data, 5);

		size_t packet_index = 6;

		for (int i = 0; i < 6; i++)
		{
			extract_packet.lapis_extracted_bag[i] = read_u8(data, packet_index);
			packet_index++;
		}

		for (int i = 0; i < 6; i++)
		{
			extract_packet.lapis_extracted_slot[i] = read_u8(data, packet_index);
			packet_index++;
		}

		for (int i = 0; i < 6; i++)
		{
			extract_packet.lapis_extracted_id[i] = read_u8(data, packet_index);
			packet_index++;
		}

		for (int i = 0; i < 6; i++)
		{
			extract_packet.lapis_extracted_count[i] = read_u8(data, packet_index);
			packet_index++;
		}

		extract_packet.gold = read_u32(data, packet_index);

		user->Send((void*)&extract_packet, sizeof(ExtractResultPacket));
	}

	const uintptr_t enchant_success_result_return = 0x0046CF8E;

	NAKED void enchant_success_result_hook()
	{
		__asm {
			lea edx, [esp + 0xA28]
			pushad
			mov ecx, ebp
			call packets::items::blacksmith::send_enchant_result_from_old_packet
			popad
			jmp enchant_success_result_return
		}
	}

	const uintptr_t enchant_fail_result_return = 0x0046D28B;

	NAKED void enchant_fail_result_hook()
	{
		__asm {
			lea edx, [esp + 0xA28]
			pushad
			mov ecx, ebp
			call packets::items::blacksmith::send_enchant_result_from_old_packet
			popad
			jmp enchant_fail_result_return
		}
	}

	const uintptr_t link_success_result_return = 0x0046E914;

	NAKED void link_success_result_hook()
	{
		__asm {
			pushad
			call packets::items::blacksmith::send_link_result_from_old_packet
			popad
			add esp, 0x08
			jmp link_success_result_return
		}
	}

	const uintptr_t link_fail_result_return = 0x0046EC7D;

	NAKED void link_fail_result_hook()
	{
		__asm {
			pushad
			mov edx, eax
			call packets::items::blacksmith::send_link_result_from_old_packet
			popad
			add esp, 0x08
			jmp link_fail_result_return
		}
	}

	const uintptr_t extract_success_result_return = 0x00471564;

	NAKED void extract_success_result_hook()
	{
		__asm {
			pushad
			call packets::items::blacksmith::send_extract_result_from_old_packet
			popad
			add esp, 0x08
			jmp extract_success_result_return
		}
	}

	const uintptr_t extract_fail_result_return = 0x00470915;

	NAKED void extract_fail_result_hook()
	{
		__asm {
			pushad
			mov edx, eax
			call packets::items::blacksmith::send_extract_result_from_old_packet
			popad
			add esp, 0x08
			jmp extract_fail_result_return
		}
	}

	const uintptr_t extract_fail_result2_return = 0x0047179B;

	NAKED void extract_fail_result2_hook()
	{
		__asm {
			pushad
			call packets::items::blacksmith::send_extract_result_from_old_packet
			popad
			add esp, 0x08
			jmp extract_fail_result2_return
		}
	}

	void hook()
	{
		utils::memory::hook((void*)0x0046CF7D, enchant_success_result_hook, 9);
		utils::memory::hook((void*)0x0046D27A, enchant_fail_result_hook, 9);
		utils::memory::hook((void*)0x0046E90F, link_success_result_hook, 5);
		utils::memory::hook((void*)0x0046EC78, link_fail_result_hook, 5);
		utils::memory::hook((void*)0x0047155F, extract_success_result_hook, 5);
		utils::memory::hook((void*)0x00470910, extract_fail_result_hook, 5);
		utils::memory::hook((void*)0x00471796, extract_fail_result2_hook, 5);
	}
}
