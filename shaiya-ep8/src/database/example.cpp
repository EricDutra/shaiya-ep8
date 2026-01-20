#include "include/database/example.h"
#include "include/database/config.h"
#include <cstdio>

namespace database
{
	namespace example
	{
		bool test_connection()
		{
			config::init();
			Connection conn;
			return conn.connect("ShaiyaDB");
		}

		bool load_user_data(int32_t user_id)
		{
			config::init();
			Connection conn;
			if (!conn.connect("ShaiyaDB"))
				return false;

			char query[256];
			snprintf(query, sizeof(query),
				"SELECT UserUID, UserName, UserLevel FROM Users WHERE UserUID = %d",
				user_id);

			if (!conn.execute(query))
				return false;

			if (conn.fetch())
			{
				int32_t uid;
				char username[32];
				int32_t level;

				conn.get_int(1, &uid);
				conn.get_string(2, username, sizeof(username));
				conn.get_int(3, &level);
			}

			return true;
		}

		bool save_character_position(int32_t char_id, float x, float y, float z)
		{
			config::init();
			Connection conn;
			if (!conn.connect("ShaiyaDB"))
				return false;

			char query[512];
			snprintf(query, sizeof(query),
				"UPDATE Characters SET PosX = %f, PosY = %f, PosZ = %f WHERE CharID = %d",
				x, y, z, char_id);

			return conn.execute(query);
		}

		bool multiple_queries_example()
		{
			config::init();
			Connection conn;
			if (!conn.connect("ShaiyaDB"))
				return false;

			if (!conn.execute("SELECT COUNT(*) FROM Users"))
				return false;

			if (conn.fetch())
			{
				int32_t user_count;
				conn.get_int(1, &user_count);
			}

			if (!conn.execute("SELECT TOP 10 CharID, CharName FROM Characters"))
				return false;

			while (conn.fetch())
			{
				int32_t char_id;
				char char_name[32];
				conn.get_int(1, &char_id);
				conn.get_string(2, char_name, sizeof(char_name));
			}

			char query[256];
			snprintf(query, sizeof(query), "UPDATE Characters SET Level = Level + 1 WHERE CharID = %d", 1000);
			conn.execute(query);

			return true;
		}

		SkinItems get_skin_items(uint32_t char_id)
		{
			SkinItems skinItems = {0};

			config::init();
			Connection conn;
			if (!conn.connect("ShaiyaDB"))
				return skinItems;

			char query[256];
			snprintf(query, sizeof(query), "EXEC dbo.usp_Read_Char_Items_Skin_R %u", char_id);

			if (!conn.execute(query))
				return skinItems;

			if (conn.fetch())
			{
				conn.get_int(1, &skinItems.petType);
				conn.get_int(2, &skinItems.petTypeID);
				conn.get_int(3, &skinItems.costumeType);
				conn.get_int(4, &skinItems.costumeTypeID);
				conn.get_int(5, &skinItems.wingType);
				conn.get_int(6, &skinItems.wingTypeID);
			}

			return skinItems;
		}
	}
}
