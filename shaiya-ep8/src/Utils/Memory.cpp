#include "include/Utils/Memory.h"
#include <cstring>

namespace Utils
{
	namespace Memory
	{
		bool Protect(void* address, size_t size, DWORD newProtect, DWORD* oldProtect)
		{
			return VirtualProtect(address, size, newProtect, oldProtect) != 0;
		}

		bool WriteBytes(void* address, const void* bytes, size_t size)
		{
			DWORD oldProtect;
			if (!Protect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect))
				return false;

			std::memcpy(address, bytes, size);

			Protect(address, size, oldProtect, &oldProtect);
			return true;
		}

		bool Nop(void* address, size_t size)
		{
			DWORD oldProtect;
			if (!Protect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect))
				return false;

			std::memset(address, 0x90, size);

			Protect(address, size, oldProtect, &oldProtect);
			return true;
		}

		bool Detour(void* src, void* dst, size_t size)
		{
			if (size < 5)
				return false;

			DWORD oldProtect;
			if (!Protect(src, size, PAGE_EXECUTE_READWRITE, &oldProtect))
				return false;

			std::memset(src, 0x90, size);

			uintptr_t relativeAddress = (uintptr_t)dst - (uintptr_t)src - 5;

			*(BYTE*)src = 0xE9;
			*(uintptr_t*)((uintptr_t)src + 1) = relativeAddress;

			Protect(src, size, oldProtect, &oldProtect);
			return true;
		}
	}
}