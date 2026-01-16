#pragma once
#include <Windows.h>
#include <cstdint>

namespace utils
{
	namespace memory
	{
		bool write_bytes(void* address, const void* bytes, size_t size);
		bool nop(void* address, size_t size);
		bool hook(void* src, void* dst, size_t size);
		bool protect(void* address, size_t size, DWORD new_protect, DWORD* old_protect);
	}
}