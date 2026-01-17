#include <cstring>
#include "include/utils/buffer_reader.h"

namespace utils
{
	namespace buffer_reader
	{
		uint32_t ReadU32(const uint8_t* data, size_t offset)
		{
			uint32_t v;
			std::memcpy(&v, data + offset, sizeof(v));
			return v;
		}

		uint16_t ReadU16(const uint8_t* data, size_t offset)
		{
			uint16_t v;
			std::memcpy(&v, data + offset, sizeof(v));
			return v;
		}

		uint8_t  ReadU8(const uint8_t* data, size_t offset)
		{
			return data[offset];
		}
	}
}