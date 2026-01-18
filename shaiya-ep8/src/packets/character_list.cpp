#include "include/packets/character_list.h"
#include "include/utils/memory.h"
#include "include/utils/buffer_reader.h"

namespace packets
{
	namespace character_list
	{
		void __fastcall send(CUser* user, void* old_packet)
		{
			Character character{};

			character.opcode = packets::PacketType::CharacterList;

			const uint8_t* data = reinterpret_cast<const uint8_t*>(old_packet);

			character.char_id = utils::buffer_reader::read_u32(data, 0);
			character.creation_time = utils::buffer_reader::read_u32(data, 4);
			character.rename_flag = utils::buffer_reader::read_u8(data, 8);
			character.slot = utils::buffer_reader::read_u8(data, 9);
			character.family = utils::buffer_reader::read_u8(data, 10);
			character.mode = utils::buffer_reader::read_u8(data, 11);
			character.hair = utils::buffer_reader::read_u8(data, 12);
			character.face = utils::buffer_reader::read_u8(data, 13);
			character.height = utils::buffer_reader::read_u8(data, 14);
			character.job = utils::buffer_reader::read_u8(data, 15);
			character.gender = utils::buffer_reader::read_u8(data, 16);
			character.level = utils::buffer_reader::read_u16(data, 17);
			character.strength = utils::buffer_reader::read_u16(data, 19);
			character.dexterity = utils::buffer_reader::read_u16(data, 21);
			character.resistance = utils::buffer_reader::read_u16(data, 23);
			character.intelligence = utils::buffer_reader::read_u16(data, 25);
			character.wisdom = utils::buffer_reader::read_u16(data, 27);
			character.luck = utils::buffer_reader::read_u16(data, 29);
			character.map = utils::buffer_reader::read_u16(data, 37);

			character.delete_flag = (utils::buffer_reader::read_u32(data, 39) > 0) ? 1 : 0;

			// equipment types
			character.helmet_type = utils::buffer_reader::read_u8(data, 43);
			character.armor_type = utils::buffer_reader::read_u8(data, 44);
			character.pants_type = utils::buffer_reader::read_u8(data, 45);
			character.glove_type = utils::buffer_reader::read_u8(data, 46);
			character.boot_type = utils::buffer_reader::read_u8(data, 47);
			character.weapon_type = utils::buffer_reader::read_u8(data, 48);
			character.shield_type = utils::buffer_reader::read_u8(data, 49);
			character.cape_type = utils::buffer_reader::read_u8(data, 50);

			// equipment type IDs
			character.helmet_type_id = utils::buffer_reader::read_u8(data, 51);
			character.armor_type_id = utils::buffer_reader::read_u8(data, 52);
			character.pants_type_id = utils::buffer_reader::read_u8(data, 53);
			character.glove_type_id = utils::buffer_reader::read_u8(data, 54);
			character.boot_type_id = utils::buffer_reader::read_u8(data, 55);
			character.weapon_type_id = utils::buffer_reader::read_u8(data, 56);
			character.shield_type_id = utils::buffer_reader::read_u8(data, 57);
			character.cape_type_id = utils::buffer_reader::read_u8(data, 58);

			// name (19 bytes)
			utils::buffer_reader::read_bytes(data, 65, character.name, 19);

			user->Send((void*)&character, sizeof(Character));
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