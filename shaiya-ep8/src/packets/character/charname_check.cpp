#include "include/packets/character/charname_check.h"

namespace packets::character::charname_check
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