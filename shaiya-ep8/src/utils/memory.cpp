#include <cstring>
#include "include/utils/memory.h"

namespace utils
{
	namespace memory
	{
		bool protect(void* address, size_t size, DWORD new_protect, DWORD* old_protect)
		{
			return VirtualProtect(address, size, new_protect, old_protect) != 0;
		}

		bool write_bytes(void* address, const void* bytes, size_t size)
		{
			DWORD old_protect;
			if (!protect(address, size, PAGE_EXECUTE_READWRITE, &old_protect))
				return false;

			std::memcpy(address, bytes, size);

			protect(address, size, old_protect, &old_protect);
			return true;
		}

		bool nop(void* address, size_t size)
		{
			DWORD old_protect;
			if (!protect(address, size, PAGE_EXECUTE_READWRITE, &old_protect))
				return false;

			std::memset(address, 0x90, size);

			protect(address, size, old_protect, &old_protect);
			return true;
		}

		bool hook(void* src, void* dst, size_t size)
		{
			if (size < 5)
				return false;

			DWORD old_protect;
			if (!protect(src, size, PAGE_EXECUTE_READWRITE, &old_protect))
				return false;

			std::memset(src, 0x90, size);

			uintptr_t relative_address = (uintptr_t)dst - (uintptr_t)src - 5;

			*(BYTE*)src = 0xE9;
			*(uintptr_t*)((uintptr_t)src + 1) = relative_address;

			protect(src, size, old_protect, &old_protect);
			return true;
		}
	}
}