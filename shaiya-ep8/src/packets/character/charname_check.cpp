#include <string>
#include "include/packets/character/charname_check.h"
#include "include/database/connection.h"
#include "include/utils/logger.h"

namespace packets::character::charname_check
{
	static bool is_valid_charname(const char* name)
	{
		if (!name) return false;

		size_t len = strlen(name);
		if (len < 3 || len > 18) return false;

		for (size_t i = 0; name[i] != '\0'; i++)
		{
			char c = name[i];
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
				  (c >= '0' && c <= '9') || c == '_' || c == '.' || c == '-'))
				return false;
		}

		return true;
	}

	void check(CUser* user, Packet* packet)
	{
		std::string charname((char*)&packet->data[0]);

		Response response{};

		response.opcode = packets::PacketType::CheckCharnameAvailable;

		response.available = true;

		if (!is_valid_charname(charname.c_str()))
		{
			utils::logger::warning("Character name validation failed: '%s'", charname.c_str());
			response.available = false;
			user->Send((void*)&response, sizeof(Response));
			return;
		}

		database::Connection conn;
		if (conn.connect("PS_GameData"))
		{
			if (conn.prepare("SELECT CharID FROM PS_GameData.dbo.Chars WHERE CharName = ?;"))
			{
				conn.bind_string(1, charname.c_str(), charname.length());

				if (conn.execute_prepared() && conn.fetch())
				{
					response.available = false;
				}
			}
		}

		user->Send((void*)&response, sizeof(Response));
	}
}