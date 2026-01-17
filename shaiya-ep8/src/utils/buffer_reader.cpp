#include <cstring>
#include "include/utils/buffer_reader.h"

namespace utils
{
	namespace buffer_reader
	{
		uint32_t read_u32(const uint8_t* data, size_t offset)
		{
			uint32_t v;
			std::memcpy(&v, data + offset, sizeof(v));
			return v;
		}

		uint16_t read_u16(const uint8_t* data, size_t offset)
		{
			uint16_t v;
			std::memcpy(&v, data + offset, sizeof(v));
			return v;
		}

		uint8_t read_u8(const uint8_t* data, size_t offset)
		{
			return data[offset];
		}

		void read_bytes(const uint8_t* data, size_t offset, void* out, size_t size)
		{
			std::memcpy(out, data + offset, size);
		}
	}
}