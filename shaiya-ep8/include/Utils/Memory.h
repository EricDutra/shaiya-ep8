#pragma once
#include <Windows.h>
#include <cstdint>

namespace Utils
{
	namespace Memory
	{
		bool WriteBytes(void* address, const void* bytes, size_t size);
		bool Nop(void* address, size_t size);
		bool Detour(void* src, void* dst, size_t size);
		bool Protect(void* address, size_t size, DWORD newProtect, DWORD* oldProtect);
	}
}