#include <cstdint>
#include "include/game/expand_item_quality_memory.h"
#include "include/utils/memory.h"

namespace game::expand_item_quality_memory
{
	void apply()
	{
		uint32_t item_quality_offset = 0x62B8;

		utils::memory::write_bytes((void*)0x0046754C, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00467587, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046798C, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x004679C7, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00468665, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x004686B6, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x004687CB, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00468813, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00468996, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00468A6A, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00468ABA, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00469C64, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00469CA4, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046C2DC, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046C317, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046C50C, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046C547, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046D3D8, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046D413, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046DB52, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046DB99, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046EDE7, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0046EE22, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00470A32, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00470A78, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x004718B1, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x004718F1, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00471DC5, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00472092, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x00473912, &item_quality_offset, 4);
		utils::memory::write_bytes((void*)0x0047AE7B, &item_quality_offset, 4);
	}
}