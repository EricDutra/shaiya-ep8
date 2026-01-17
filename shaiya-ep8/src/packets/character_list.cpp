#include "include/packets/character_list.h"
#include "include/utils/memory.h"
#include "include/utils/buffer_reader.h"

namespace packets
{
	namespace character_list
	{
		void send(CUser* user, Packet* old_packet)
		{
			Character character{};

			user->Send((void*)old_packet, sizeof(Character));
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