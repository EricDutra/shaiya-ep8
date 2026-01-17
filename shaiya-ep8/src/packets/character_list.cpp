#include "include/packets/character_list.h"
#include "include/utils/memory.h"
#include "include/utils/buffer_reader.h"

namespace packets
{
	namespace character_list
	{
		void __fastcall send(CUser* user, void* old_packet)
		{
			Character packet{};

			packet.opcode = 0x0101;

			const uint8_t* data = reinterpret_cast<const uint8_t*>(old_packet);

			packet.char_id = utils::buffer_reader::read_u32(data, 0);
			packet.creation_time = utils::buffer_reader::read_u32(data, 4);
			packet.rename_flag = utils::buffer_reader::read_u8(data, 8);
			packet.slot = utils::buffer_reader::read_u8(data, 9);
			packet.family = utils::buffer_reader::read_u8(data, 10);
			packet.mode = utils::buffer_reader::read_u8(data, 11);
			packet.hair = utils::buffer_reader::read_u8(data, 12);
			packet.face = utils::buffer_reader::read_u8(data, 13);
			packet.height = utils::buffer_reader::read_u8(data, 14);
			packet.job = utils::buffer_reader::read_u8(data, 15);
			packet.gender = utils::buffer_reader::read_u8(data, 16);
			packet.level = utils::buffer_reader::read_u16(data, 17);
			packet.strength = utils::buffer_reader::read_u16(data, 19);
			packet.dexterity = utils::buffer_reader::read_u16(data, 21);
			packet.resistance = utils::buffer_reader::read_u16(data, 23);
			packet.intelligence = utils::buffer_reader::read_u16(data, 25);
			packet.wisdom = utils::buffer_reader::read_u16(data, 27);
			packet.luck = utils::buffer_reader::read_u16(data, 29);
			packet.map = utils::buffer_reader::read_u16(data, 37);

			packet.delete_flag = (utils::buffer_reader::read_u32(data, 39) > 0) ? 1 : 0;

			// equipment types
			packet.helmet_type = utils::buffer_reader::read_u8(data, 43);
			packet.armor_type = utils::buffer_reader::read_u8(data, 44);
			packet.pants_type = utils::buffer_reader::read_u8(data, 45);
			packet.glove_type = utils::buffer_reader::read_u8(data, 46);
			packet.boot_type = utils::buffer_reader::read_u8(data, 47);
			packet.weapon_type = utils::buffer_reader::read_u8(data, 48);
			packet.shield_type = utils::buffer_reader::read_u8(data, 49);
			packet.cape_type = utils::buffer_reader::read_u8(data, 50);

			// equipment type IDs
			packet.helmet_type_id = utils::buffer_reader::read_u8(data, 51);
			packet.armor_type_id = utils::buffer_reader::read_u8(data, 52);
			packet.pants_type_id = utils::buffer_reader::read_u8(data, 53);
			packet.glove_type_id = utils::buffer_reader::read_u8(data, 54);
			packet.boot_type_id = utils::buffer_reader::read_u8(data, 55);
			packet.weapon_type_id = utils::buffer_reader::read_u8(data, 56);
			packet.shield_type_id = utils::buffer_reader::read_u8(data, 57);
			packet.cape_type_id = utils::buffer_reader::read_u8(data, 58);

			// name (19 bytes)
			utils::buffer_reader::read_bytes(data, 65, packet.name, 19);

			user->Send((void*)&packet, sizeof(Character));
		}

		uintptr_t send_character_list_return = 0x0047B9B8;

		NAKED void send_character_list_hook()
		{
			__asm {
				mov [esp + 0xCF], al

				pushad
				mov edx, esi
				mov ecx, ebp
				call packets::character_list::send
				popad

				add esp, 0x08

				jmp send_character_list_return
			}
		}

		void hook()
		{
			utils::memory::hook((void*)0x0047B9AC, send_character_list_hook, 7);
		}
	}
}