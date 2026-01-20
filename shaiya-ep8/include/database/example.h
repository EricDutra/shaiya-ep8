#pragma once
#include "include/database/connection.h"
#include <cstdint>

namespace database
{
	namespace example
	{
		struct SkinItems
		{
			int32_t petType;
			int32_t petTypeID;
			int32_t costumeType;
			int32_t costumeTypeID;
			int32_t wingType;
			int32_t wingTypeID;
		};

		bool test_connection();
		bool load_user_data(int32_t user_id);
		bool save_character_position(int32_t char_id, float x, float y, float z);
		bool multiple_queries_example();
		SkinItems get_skin_items(uint32_t char_id);
	}
}
