#pragma once
#include <cstdint>

namespace utils
{
	namespace buffer_reader
	{
		uint32_t ReadU32(const uint8_t* data, size_t offset);
		uint16_t ReadU16(const uint8_t* data, size_t offset);
		uint8_t  ReadU8(const uint8_t* data, size_t offset);
		void ReadBytes(const uint8_t* data, size_t offset, void* out, size_t size);
	}
}