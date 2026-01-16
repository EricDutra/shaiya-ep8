#include "include/shaiya/CUser.h"

namespace shaiya
{
	void CUser::Send(void* packet_ptr, size_t packet_size)
	{
		uintptr_t SConnectionSend = 0x004ED0E0;

		__asm {
			pushfd
			pushad
			push packet_size
			push packet_ptr
			mov ecx, this
			call SConnectionSend
			popad
			popfd
		}
	}
}