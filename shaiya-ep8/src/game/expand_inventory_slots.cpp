#include <cstdint>
#include "include/game/expand_inventory_slots.h"
#include "include/utils/memory.h"

namespace game::expand_inventory_slots
{
	void apply()
	{
		uint8_t max_slot = 17;

		utils::memory::write_bytes((void*)0x00468A2B, &max_slot, 1);
		utils::memory::write_bytes((void*)0x00468B5D, &max_slot, 1);
		utils::memory::write_bytes((void*)0x00468722, &max_slot, 1);
		utils::memory::write_bytes((void*)0x00468955, &max_slot, 1);
		utils::memory::write_bytes((void*)0x0046862D, &max_slot, 1);
		utils::memory::write_bytes((void*)0x00461528, &max_slot, 1);
		utils::memory::write_bytes((void*)0x004688B0, &max_slot, 1);
	}
}