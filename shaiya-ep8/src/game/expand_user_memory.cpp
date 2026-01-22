#include "include/game/expand_user_memory.h"
#include "include/utils/memory.h"
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace game::expand_user_memory
{
	void apply()
	{
		uint32_t CUser_size = sizeof(CUser);
		utils::memory::write_bytes((void*)0x00411F74, &CUser_size, 4);
	}
}