#pragma once
#include <cstdint>

namespace utils
{
	namespace buffer_reader
	{
		uint32_t read_u32(const uint8_t* data, size_t offset);
		uint16_t read_u16(const uint8_t* data, size_t offset);
		uint8_t  read_u8(const uint8_t* data, size_t offset);
		void read_bytes(const uint8_t* data, size_t offset, void* out, size_t size);
	}
}