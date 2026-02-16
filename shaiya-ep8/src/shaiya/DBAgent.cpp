#include <cstdint>
#include "include/shaiya/DBAgent.h"
#include "include/utils/logger.h"

namespace shaiya::DBAgent
{
	using send_fn = void(__thiscall*)(void* ptr, void* packet, size_t size);

	void Send(void* packet_ptr, size_t packet_size)
	{
		static send_fn SConnectionSend = reinterpret_cast<send_fn>(0x004ED0E0);

		void* DBAgentConnection = (void*)0x010A2628;

		SConnectionSend(DBAgentConnection, packet_ptr, packet_size);
	}
}