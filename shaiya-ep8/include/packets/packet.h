#include <cstdint>

namespace packets
{
	struct Packet
	{
		uint16_t opcode;
		uint8_t data[512];
	};
}