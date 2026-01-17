#include "include/shaiya/CUser.h"

namespace shaiya
{
	using send_fn = void(__thiscall*)(CUser* this_ptr, void* packet, size_t size);

	void CUser::Send(void* packet_ptr, size_t packet_size)
	{
		static send_fn SConnectionSend = reinterpret_cast<send_fn>(0x004ED0E0);

		SConnectionSend(this, packet_ptr, packet_size);
	}
}