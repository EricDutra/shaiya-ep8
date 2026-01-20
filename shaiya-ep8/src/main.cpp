#include "include/utils/win32_lean.h"
#include "include/utils/logger.h"
#include "include/database/config.h"
#include "include/packets/handler.h"
#include "include/packets/character/list.h"
#include "include/packets/character/details.h"
#include "include/packets/character/status.h"

void init()
{
    utils::logger::init("Log\\shaiya-ep8.log");
    
    database::config::init();

    packets::handler::hook();
    packets::character::list::hook();
    packets::character::details::hook();
    packets::character::status::hook();

    utils::logger::info("Shaiya EP8 (https://github.com/EricDutra/shaiya-ep8) DLL initialized");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
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