#include "include/utils/win32_lean.h"
#include "include/utils/logger.h"
#include "include/database/config.h"
#include "include/packets/handler.h"
#include "include/packets/character/list.h"
#include "include/packets/character/details.h"
#include "include/packets/character/status.h"
#include "include/game/expand_inventory_slots.h"
#include "include/game/expand_item_quality_memory.h"
#include "include/game/expand_user_memory.h"
#include "include/game/world.h"
#include "include/packets/items/inventory.h"
#include "include/packets/items/warehouse.h"
#include "include/packets/items/trade.h"
#include "include/packets/items/blacksmith.h"
#include "include/packets/items/guild_warehouse.h"
#include "include/packets/items/player_market.h"

void init()
{
    utils::logger::init("Log\\shaiya-ep8.log");
    
    database::config::init();

    packets::handler::hook();
    packets::character::list::hook();
    packets::character::details::hook();
    packets::character::status::hook();
	packets::items::inventory::hook();
	packets::items::warehouse::hook();
	packets::items::trade::hook();
	packets::items::blacksmith::hook();
	packets::items::guild_warehouse::hook();
	packets::items::player_market::hook();
	game::expand_inventory_slots::apply();
	game::expand_item_quality_memory::apply();
	game::expand_user_memory::apply();
	game::world::hook();

    utils::logger::info("Shaiya EP8 DLL initialized");
    utils::logger::info("https://github.com/EricDutra/shaiya-ep8");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hModule);
            init();
            break;
    }

    return TRUE;
}