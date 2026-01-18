#include "include/packets/charname_check.h"

namespace packets
{
	namespace charname_check
	{
		void check(CUser* user, Packet* packet)
		{
			// dummy
			Response response{};
			response.opcode = packets::PacketType::CheckCharnameAvailable;
			response.available = true;

			user->Send((void*)&response, sizeof(Response));
		}
	}
}